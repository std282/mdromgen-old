#include <megadrive/hardware.h>

#define AT(Sect) __attribute__((section(Sect)))

m68k_byte volatile md_z80_memory[Z80_MEMORY_SZBYTES] AT(".md_zmem");
m68k_word volatile md_z80_busreq                     AT(".md_zbrq");
m68k_word volatile md_z80_reset                      AT(".md_zrst");
m68k_word volatile const md_version                  AT(".md_ver");
m68k_word volatile md_ctr1_data                      AT(".md_c1dat");
m68k_word volatile md_ctr2_data                      AT(".md_c2dat");
m68k_word volatile md_expt_data                      AT(".md_xpdat");
m68k_word volatile md_ctr1_control                   AT(".md_c1ctl");
m68k_word volatile md_ctr2_control                   AT(".md_c2ctl");
m68k_word volatile md_expt_control                   AT(".md_xpctl");
struct md_ctr_serial volatile md_ctr1_serial         AT(".md_c1ser");
struct md_ctr_serial volatile md_ctr2_serial         AT(".md_c2ser");
struct md_ctr_serial volatile md_expt_serial         AT(".md_xpser");
union md_mirrport volatile md_vdp_data               AT(".md_vdat");
union md_mirrport volatile md_vdp_ctrl               AT(".md_vctl");
union md_mirrport volatile md_vdp_hvcount            AT(".md_vhvc");
union md_mirrport volatile md_psg_port               AT(".md_psg");
m68k_long volatile md_tmss_reg                       AT(".md_tmss");
