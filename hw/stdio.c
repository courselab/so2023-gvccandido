/* stdio.c - stdio implementation for x86 bare-metal booting using C
 
   Copyright (c) 2023, Gabriel V C Candido

   This piece of software is a derivative work of SYSeg, by Monaco F. J.
   SYSeg is distributed under the license GNU GPL v3, and is available
   at the official repository https://www.gitlab.com/monaco/syseg.

   This file is part of so2023-gvccandido.

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

#include <stdio.h>

int __attribute__((fastcall, naked)) puts(const char *s)
{
	__asm__(
	"    mov  %cx, %bx    # bx <- s # only bx can be used on memory accesses \n"
	"    movb $0x0e, %ah         # %ah <- 0x0e # set BIOS mode to tty        \n"
	"    movw $0x00, %si         # i <- 0                                    \n"
	"loop:                                                                   \n"
	"    movb (%bx, %si), %al    # %al <- s[i]                               \n"
	"    cmp  $0x00, %al         # if (s[i] == 0)                            \n"
	"    je   end                #     goto end                              \n"
	"    int  $0x10              # call BIOS video service                   \n"
	"    add  $0x01, %si         # i <- i + 1                                \n"
	"    jmp  loop                                                           \n"
	"end:                                                                    \n"
	"    movb $0x0a, %al         # %al <- \n                                 \n"
	"    int  $0x10              # call BIOS video service                   \n"
	"    add  $0x01, %si         # i <- i + 1                                \n"
	"    mov  %si, %ax           # return i                                  \n"
	"    ret                                                                 \n"
	);
}
