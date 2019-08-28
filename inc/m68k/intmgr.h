#if !defined(INCLUDEGUARD_M68K_INTMGR_H)
#define INCLUDEGUARD_M68K_INTMGR_H

#include <stdint.h>

// Interrupts list.
enum {
    M68KINO_BUSERR = 0,    // bus error
    M68KINO_ADDRERR,       // address error
    M68KINO_ILLEGAL,       // illegal instruction
    M68KINO_ZERODIV,       // zero divide
    M68KINO_CHK,           // CHK instruction (?)
    M68KINO_TRAPV,         // TRAPV instruction (?)
    M68KINO_PRIVVIOL,      // privilege violation
    M68KINO_TRACE,         // trace
    M68KINO_LINE1010,      // line 1010 emulator
    M68KINO_LINE1111,      // line 1111 emulator
    M68KINO_UNINIT = 13,   // unitialized interrupt
    M68KINO_SPURIOUS = 22, // spurious interrupt
    M68KINO_LEVEL_1,       // level 1 interrupt
    M68KINO_LEVEL_2,       // level 2 interrupt
    M68KINO_LEVEL_3,       // level 3 interrupt
    M68KINO_LEVEL_4,       // level 4 interrupt (HBlank)
    M68KINO_LEVEL_5,       // level 5 interrupt
    M68KINO_LEVEL_6,       // level 6 interrupt (VBlank)
    M68KINO_LEVEL_7,       // level 7 interrupt
    M68KINO_TRAP_0,        // trap 0
    M68KINO_TRAP_1,        // trap 1
    M68KINO_TRAP_2,        // trap 2
    M68KINO_TRAP_3,        // trap 3
    M68KINO_TRAP_4,        // trap 4
    M68KINO_TRAP_5,        // trap 5
    M68KINO_TRAP_6,        // trap 6
    M68KINO_TRAP_7,        // trap 7
    M68KINO_TRAP_8,        // trap 8
    M68KINO_TRAP_9,        // trap 9
    M68KINO_TRAP_10,       // trap 10
    M68KINO_TRAP_11,       // trap 11
    M68KINO_TRAP_12,       // trap 12
    M68KINO_TRAP_13,       // trap 13
    M68KINO_TRAP_14,       // trap 14
    M68KINO_TRAP_15,       // trap 15
};

// Interrupt handler type..
typedef void (m68k_ih_t)(void);

// Sets interrupt handler `new_ih` for interrupt number `ino`.
// Returns old interrupt handler.
m68k_ih_t* m68k_setih(uint8_t ino, m68k_ih_t* new_ih);

#endif // INCLUDEGUARD_M68K_INTMGR_H
