#if !defined(INCLUDEGUARD_MEGADRIVE_HARDWARE_H)
#define INCLUDEGUARD_MEGADRIVE_HARDWARE_H

#include <m68k/types.h>

#define Z80_MEMORY_SZBYTES 65536

// MD controller serial structure.
struct md_ctr_serial {
    m68k_word transmit;
    m68k_word receive;
    m68k_word control;
};

// MD 16-bit port with next 16 bits as its mirror. It is defined as union, for
// cases when one would like to write or read two words in single instruction.
union md_mirrport {
    m68k_word w;
    m68k_long l;
};

// Z80 address space.
extern m68k_byte volatile md_z80_memory[Z80_MEMORY_SZBYTES];

// Z80 bus request register.
extern m68k_word volatile md_z80_busreq;

// Z80 reset register.
extern m68k_word volatile md_z80_reset;

// MD version register.
extern m68k_word volatile const md_version;

// MD controller 1 data.
extern m68k_word volatile md_ctr1_data;

// MD controller 2 data.
extern m68k_word volatile md_ctr2_data;

// MD extension port data.
extern m68k_word volatile md_expt_data;

// MD controller 1 control register.
extern m68k_word volatile md_ctr1_control;

// MD controller 2 control register.
extern m68k_word volatile md_ctr2_control;

// MD extension port control register.
extern m68k_word volatile md_expt_control;

// MD controller 1 serial structure.
extern struct md_ctr_serial volatile md_ctr1_serial;

// MD controller 2 serial structure.
extern struct md_ctr_serial volatile md_ctr2_serial;

// MD extension port serial structure.
extern struct md_ctr_serial volatile md_expt_serial;

// MD VDP data port.
extern union md_mirrport volatile md_vdp_data;

// MD VDP control port.
extern union md_mirrport volatile md_vdp_ctrl;

// MD VDP H/V count.
extern union md_mirrport volatile md_vdp_hvcount;

// MD PSG port.
extern union md_mirrport volatile md_psg_port;

// MD TMSS register.
extern m68k_long volatile md_tmss_reg;

#endif // INCLUDEGUARD_MEGADRIVE_HARDWARE_H
