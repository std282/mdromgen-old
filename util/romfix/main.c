#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MDROM_OFFSET_CHECKSUM 0x18E
#define MDROM_OFFSET_ENDROM   0x1A4
#define MDROM_OFFSET_START    0x200

static FILE* fopen_safe(const char* name, const char* params);
static FILE* freopen_safe(const char* name, const char* params, FILE* old);
static void fseek_safe(FILE* f, long off, int whence);
static void fputc_safe(int ch, FILE* f);
static void fwrite_be_16(uint16_t val, FILE* to);
static void fwrite_be_32(uint32_t val, FILE* to);
static uint16_t read_be_16(FILE* from, uint32_t* const size);
static uint16_t compute_checksum(FILE* f, uint32_t* const size_rest);

static _Noreturn void handle_file_error(FILE* f);

int main(int argc, char* argv[argc + 1])
{
    if (argc != 2) {
        fputs("bad usage; expected single argument with path to ROM\n", stderr);
        return EXIT_FAILURE;
    }

    FILE* rom_file = fopen_safe(argv[1], "rb");
    fseek_safe(rom_file, MDROM_OFFSET_START, SEEK_SET);
    uint32_t rom_size = MDROM_OFFSET_START;
    uint16_t const checksum = compute_checksum(rom_file, &rom_size);
    rom_file = freopen_safe(argv[1], "rb+", rom_file);
    fseek_safe(rom_file, MDROM_OFFSET_CHECKSUM, SEEK_SET);
    fwrite_be_16(checksum, rom_file);
    fseek_safe(rom_file, MDROM_OFFSET_ENDROM, SEEK_SET);
    fwrite_be_32(rom_size, rom_file);
    fclose(rom_file);
}

// Opens file. If fails, terminates the program.
FILE* fopen_safe(const char* name, const char* params)
{
    FILE* const ret = fopen(name, params);
    if (ret == NULL) {
        fputs("error: specified file does not exist\n", stderr);
        exit(EXIT_FAILURE);
    }

    return ret;
}

// Re-opens file. If fails, terminates the program.
FILE* freopen_safe(const char* name, const char* params, FILE* old)
{
    FILE* const ret = freopen(name, params, old);
    if (ret == NULL) {
        fputs("error: failure upon reopening for writing\n", stderr);
        exit(EXIT_FAILURE);
    }

    return ret;
}


// Calls fseek, terminates program if it fails.
static void fseek_safe(FILE* f, long off, int whence)
{
    int const res = fseek(f, off, whence);
    if (res != 0) {
        handle_file_error(f);
    }
}

// Calls fputc, terminates program if it fails.
static void fputc_safe(int ch, FILE* f)
{
    int const out = fputc(ch, f);
    if (out == EOF) {
        handle_file_error(f);
    }
}

// Writes 16-bit big endian number.
void fwrite_be_16(uint16_t val, FILE* to)
{
    uint8_t const* bytes = (void*) &val;
    
    for (unsigned i = 0; i < sizeof(val); i++) {
        fputc_safe(bytes[sizeof(val) - i - 1], to);
    }
}

// Writes 32-bit big endian number.
void fwrite_be_32(uint32_t val, FILE* to)
{
    uint8_t const* bytes = (void*) &val;

    for (unsigned i = 0; i < sizeof(val); i++) {
        fputc_safe(bytes[sizeof(val) - i - 1], to);
    }
}

// Prints message about file error and terminates the program.
_Noreturn void handle_file_error(FILE* f)
{
    if (ferror(f) != 0) {
        fputs("error: file error happened\n", stderr);
    } 
    else if (feof(f) != 0) {
        fputs("error: unexpected EOF happened\n", stderr);
    }
    else {
        fputs("error: false call to handle_file_error\n", stderr);
    }

    exit(EXIT_FAILURE);
}

// Returns SEGA ROM checksum, given that file 
uint16_t compute_checksum(FILE* f, uint32_t* const size_rest)
{
    uint16_t res = 0;

    while (!feof(f)) {
        res += read_be_16(f, size_rest);
    }

    return res;
}

// Reads big-endian 16-bit value from stream.
uint16_t read_be_16(FILE* from, uint32_t* const size)
{
    int msb = fgetc(from);
    if (msb == EOF) {
        msb = 0;
    }
    else {
        (*size)++;
    }

    int lsb = fgetc(from);
    if (lsb == EOF) {
        lsb = 0;
    }
    else {
        (*size)++;
    }

    if (ferror(from) != 0) {
        handle_file_error(from);
    }

    return (uint16_t) ((msb << 8) + lsb);
}
