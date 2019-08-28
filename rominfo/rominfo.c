#include <stdint.h>

#define AT(Sect) __attribute__((section(Sect)))

struct {
    char     system_type[16];
    char     crght_reldate[16];
    char     title_domestic[48];
    char     title_overseas[48];
    char     serial_number[14];
    uint16_t checksum;
    char     supported_devices[16];
    uint32_t rom_address_range[2];
    uint32_t ram_address_range[2];
    char     extra_memory[12];
    char     modem[12];
    char     reserved_1[40];
    char     region[3];
    char     reserved_2[13];
} const __rominfo AT(".info") = {
    .system_type       = "SEGA GENESIS    ",
    .crght_reldate     = "(C)SEGA 2019.AUG",
    .title_domestic    = "NAZVANIE IGRY NA YAZYKE AVTORA IGRY             ",
    .title_overseas    = "GAME NAME IN ENGLISH                            ",
    .serial_number     = "GM 00000000-00",
    .checksum          = 0xDEAD, // [1]
    .supported_devices = "J               ",
    .rom_address_range = { 0x000200, 0xDEADFACE /* [1] */ },
    .ram_address_range = { 0xFF0000, 0xFFFFFF },
    .extra_memory      = "            ",
    .modem             = "            ",
    .reserved_1        = "                                        ",
    .region            = "JUE",
    .reserved_2        = "             ",
};

/**
 * [1]: These fields are to be patched after ROM generation.
 */

_Static_assert(
    sizeof(__rominfo) == 256,
    "size of ROM info structure must be exactly 256 bytes; something is wrong here"
);
