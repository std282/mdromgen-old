# SEGA MegaDrive/Genesis GNU-based ROM Generator

This is a setup for generating SEGA MegaDrive/Genesis ROMs using GNU utilities
(gcc, ld, make, objcopy, objdump) using C language programming.

This project is in development. Nevertheless, it is already capable of 
compilation and ROM generation. 

## Preparation

I will assume that user is at least somewhat experienced in C and GNU Make.

Currently, I am not sure whether it's possible to use this on Windows natively.
I am working on Windows 10 Pro with Ubuntu in WSL, and I'm sure any Linux-based
OS user will be able to use the generator properly, given they're capable of
GCC installation.

You need to have next four packages installed:

1. Native GCC (i.e. GNU compiler that generates code for your host system)
2. GNU Make.
3. GCC for M68K.
4. GNU Binutils for M68K.

If you use Ubuntu, it's very likely you already have GCC and Make, so you may open
terminal and execute this line:

```
sudo apt install gcc-8-m68k-linux-gnu binutils-m68k-linux-gnu
```

It is important to have GCC version 8. It should already be in repositories, and it has
much more optimization and code generation options than GCC 7.

## Usage

Just clone this repo in the place you'd like and run ``make`` there. A file _ProjectName.bin_
will appear in your directory. This is a generated SEGA MegaDrive/Genesis ROM, and 
you should be able to run it with any emulator available (e.g. Kega Fusion, Regen, BlastEM).

If everything went OK, you may start writing code in _main.c_ and add more translation
units in _src_ directory. However, if you don't want to change Makefile's innards, do
not add directories in _src_ directory, as GNU Make doesn't scan recursively.

### Some hints

If you open Makefile, you'll see something like this:

```Makefile
# Project name
PROJ := ProjectName

# Set this to 1, if you want to get listings
MAKE_LST := 0

# Set this to 1, if you want to enable optimization
OPTIMIZE := 1

# Set this to 1, if you want to enable link-time optimization
ENABLE_LTO := 0

# Output file dependencies
DEPS := startup
DEPS += intmgr

###############################################################################
# LET GNU MAKE HANDLE THE REST                                                #
###############################################################################
```

_PROJ_ is just a name of generated file.

_MAKE\_LST_, _OPTIMIZE_ and _ENABLE\_LTO_ are self-explanatory, I believe. Be careful
with LTO, though: it reduces ROM size greatly, but may ruin your program altogether. 
It took me quite a bit of time to tame, and I'm still not sure it behaves.

_DEPS_ are list of dependencies of the project. By 'dependency' I mean a static library.
Static library projects are located in _lib_ directory, and they must be named exactly
the same as _DEPS_ entries.

The library project is rather unusual. Its include files are to be searched in
main project folder _inc_. That being said, each library can depend on some other
library or even the main project itself (even though I would recommend against that).

It is a good habit to introduce a separate directory in _inc_ for each new library.

### Dependency 'startup'

This dependency contains entry point in ROM. It performs RAM initialization
(so it's possible to use global variables), calls _main_ and freezes. This library is
essential for ROM functioning.

**You should never remove this dependency, unless you absolutely know what you're doing!**

### Dependency 'intmgr'

This dependency provides interrupt manager functionality. It allows to set interrupt
handlers at runtime.

```c
#include <m68k/intmgr.h>

void vblank_handler(void);
void hblank_handler(void);

void main(void)
{
    m68k_setih(M68KINO_LEVEL_4, &hblank_handler);
    m68k_setih(M68KINO_LEVEL_6, &vblank_handler);
}

// Definition of vblank_handler and hblank_handler...

```

It introduces a little bit of overhead, so you might want to define single
interrupt handler at compile time. It is certainly possible, and soon there will 
be library for that.

## ROM info

If you look inside _rominfo_ directory, you'll find there a file _rominfo.c_.

It contains metadata for ROM, such as system, region and game name. 
Change them with care.

## Tutorials

I might write some later.
