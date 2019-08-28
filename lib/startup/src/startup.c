#include <stdint.h>

// Asserts that the variable will be places at specified section
#define AT(Sect) __attribute__((section(Sect)))

// First byte of RAM .data section initial state in ROM.
extern char const __data_rom_begin;
// First byte of RAM .data section.
extern char __data_ram_begin;
// One-past-last byte of RAM .data section.
extern char __data_ram_end;
// First byte of RAM .bss section.
extern char __bss_ram_begin;
// One-past-last byte of RAM .bss section.
extern char __bss_ram_end;

// Standard C entrypoint.
extern void main(void);

// Function that initializes RAM.
static void __init_m68k_ram(void);

_Noreturn 
void __start(void)
{
    __init_m68k_ram();
    main();

    while (1) {
        // program is finished, do nothing
    }
}

void __init_m68k_ram(void)
{
    char const* data_ro  = &__data_rom_begin;
    char*       data_rw  = &__data_ram_begin;
    char* const edata_rw = &__data_ram_end;
    char*       bss_rw   = &__bss_ram_begin;
    char* const ebss_rw  = &__bss_ram_end;

    while (data_rw != edata_rw) {
        *data_rw++ = *data_ro++;
    }

    while (bss_rw != ebss_rw) {
        *bss_rw = 0;
    }
}

// Entry point for ROM
void (* const __initial_pc)(void) AT(".initpc") = &__start;

// Initial stack pointer value for ROM
uintptr_t const __initial_sp AT(".initsp") = 0xFFFFFE;
