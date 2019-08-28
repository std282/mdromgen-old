MEMORY 
{
    /* Cartridge */
    CART_INITSP (R)     : ORIGIN = 0x000000, LENGTH = 4
    CART_INITPC (R)     : ORIGIN = 0x000004, LENGTH = 4
    CART_INTVEC (R)     : ORIGIN = 0x000008, LENGTH = 248
    CART_INFO   (R)     : ORIGIN = 0x000100, LENGTH = 256

    CART_ROM    (RX)    : ORIGIN = 0x000200, LENGTH = 4M - 0x200

    /* Z80 stuff */
    Z80_MEMORY  (W)     : ORIGIN = 0xA00000, LENGTH = 64K
    Z80_BUSREQ  (W)     : ORIGIN = 0xA11100, LENGTH = 2
    Z80_RESET   (W)     : ORIGIN = 0xA11200, LENGTH = 2

    /* Controllers' ports */
    CN1_DATA    (W)     : ORIGIN = 0xA10002, LENGTH = 2
    CN2_DATA    (W)     : ORIGIN = 0xA10004, LENGTH = 2
    EXP_DATA    (W)     : ORIGIN = 0xA10006, LENGTH = 2
    CN1_CTRL    (W)     : ORIGIN = 0xA10008, LENGTH = 2
    CN2_CTRL    (W)     : ORIGIN = 0xA1000A, LENGTH = 2
    EXP_CTRL    (W)     : ORIGIN = 0xA1000C, LENGTH = 2
    CN1_SERI    (W)     : ORIGIN = 0xA1000E, LENGTH = 6
    CN2_SERI    (W)     : ORIGIN = 0xA10014, LENGTH = 6
    EXP_SERI    (W)     : ORIGIN = 0xA1001A, LENGTH = 6

    /* VDP stuff */
    VDP_DATA    (W)     : ORIGIN = 0xC00000, LENGTH = 4
    VDP_CONTROL (W)     : ORIGIN = 0xC00004, LENGTH = 4
    VDP_HVCOUNT (W)     : ORIGIN = 0xC00008, LENGTH = 8
    
    /* Other */
    PSG         (W)     : ORIGIN = 0xC00011, LENGTH = 8
    MDVERSION   (W)     : ORIGIN = 0xA10000, LENGTH = 2
    MEMMODE     (W)     : ORIGIN = 0xA11000, LENGTH = 2
    TMSS        (W)     : ORIGIN = 0xA14000, LENGTH = 4

    /* M68K RAM */
    M68K_RAM    (W)     : ORIGIN = 0xFF0000, LENGTH = 0xF800
}

/* Setting entry point */
ENTRY(__start)

SECTIONS
{
    /* ROM header sections */
    .initsp : { KEEP(*(.initsp)); } > CART_INITSP
    .initpc : { KEEP(*(.initpc)); } > CART_INITPC
    .intvec : { KEEP(*(.intvec)); } > CART_INTVEC
    .info : { KEEP(*(.info)); } > CART_INFO

    /* Special sections */
    .md_zmem (NOLOAD) : { KEEP(*(.md_zmem)); } > Z80_MEMORY
    .md_zbrq (NOLOAD) : { KEEP(*(.md_zbrq)); } > Z80_BUSREQ
    .md_zrst (NOLOAD) : { KEEP(*(.md_zrst)); } > Z80_RESET
    .md_ver (NOLOAD) : { KEEP(*(.md_ver)); } > MDVERSION
    .md_c1dat (NOLOAD) : { KEEP(*(.md_c1dat)); } > CN1_DATA
    .md_c2dat (NOLOAD) : { KEEP(*(.md_c2dat)); } > CN2_DATA
    .md_xpdat (NOLOAD) : { KEEP(*(.md_xpdat)); } > EXP_DATA
    .md_c1ctl (NOLOAD) : { KEEP(*(.md_c1ctl)); } > CN1_CTRL
    .md_c2ctl (NOLOAD) : { KEEP(*(.md_c2ctl)); } > CN2_CTRL
    .md_xpctl (NOLOAD) : { KEEP(*(.md_xpctl)); } > EXP_CTRL
    .md_c1ser (NOLOAD) : { KEEP(*(.md_c1ser)); } > CN1_SERI
    .md_c2ser (NOLOAD) : { KEEP(*(.md_c2ser)); } > CN2_SERI
    .md_xpser (NOLOAD) : { KEEP(*(.md_xpser)); } > EXP_SERI
    .md_vdat (NOLOAD) : { KEEP(*(.md_vdat)); } > VDP_DATA
    .md_vctl (NOLOAD) : { KEEP(*(.md_vctl)); } > VDP_CONTROL
    .md_vhvc (NOLOAD) : { KEEP(*(.md_vhvc)); } > VDP_HVCOUNT
    .md_psg (NOLOAD) : { KEEP(*(.md_psg)); } > PSG
    .md_tmss (NOLOAD) : { KEEP(*(.md_tmss)); } > TMSS

    /* Generic sections */
    .text : { 
        *(.text);
    } > CART_ROM

    .rodata : { 
        *(.rodata);
        __data_rom_begin = .;
    } > CART_ROM

    .data : {
        __data_ram_begin = .;
        *(.data);
        __data_ram_end = .;
    } > M68K_RAM AT>CART_ROM

    .bss : {
        __bss_ram_begin = .;
        *(.bss);
        __bss_ram_end = .;
    } > M68K_RAM
}
