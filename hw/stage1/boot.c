/* boot.c - x86 bare-metal boot using C
 
   Copyright (c) 2023, Gabriel V C Candido

   This piece of software is a derivative work of SYSeg, by Monaco F. J.
   SYSeg is distributed under the license GNU GPL v3, and is available
   at the official repository https://www.gitlab.com/monaco/syseg.

   This file is part of so2023-gvccandido

   so2023-gvccandido is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <boot.h>
#include <io.h>

static const int stage2_size=STAGE2_SIZE;
static const int stage2_addr=STAGE2_ADDR;

void __attribute__((naked)) __fatal()
{
	puts("--- stage1 panic, halting");
	__asm__(
	"__fatal_halt:                                                           \n"
	"    hlt                                                                 \n"
	"    jmp  __fatal_halt                                                   \n"
	);
}

void load_stage2()
{
	puts("Loading stage2");

	// %dl should contain the disk we want to read from
	// %dl should also contain the disk we booted from when execution starts
	// thus, as we want to keep reading from the same disk we booted, we do not
	//  set %al here
	__asm__(
	"    mov $0x80, %dl      # use 1st HDD                                   \n"
	"reset.load_stage2:                                                      \n"
	"    mov $0x00, %ah      # set mode to reset drive                       \n"
	"    int $0x13           # call BIOS disk service (sets CF on error)     \n"

	"    jnc load.load_stage2# if (CF == 0) goto load                        \n"
	"    call __fatal                                                        \n"

	"load.load_stage2:                                                       \n"
	"    mov $0x02, %ah      # set mode to read sector                       \n"
	"    mov stage2_size, %al                                                \n"
	"    mov $0x00, %ch      # cylinder <- 0 (this is actually 10 bits)      \n"
	"    mov $0x00, %dh      # head <- 0                                     \n"
	"    mov $0x02, %cl      # sector <- 2 (2 bits go for cylinder)          \n"
	"                        #  first sector is 1, and it was already read by\n"
	"                        #  BIOS and loaded to RAM:                      \n"
	"                        #   it is this very stage1 bootloader :)        \n"
	"    mov stage2_addr, %bx# address to load sector on                     \n"
	"    int $0x13           # call BIOS disk service (sets CF on error)     \n"

	"    jnc end.load_stage2 # if (CF == 0) goto end                         \n"
	"    call __fatal                                                        \n"

	"end.load_stage2:                                                        \n"
	);
}
