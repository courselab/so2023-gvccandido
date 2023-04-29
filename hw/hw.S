#   hw.S - x86 bare-metal boot using assembly
# 
#   Copyright (c) 2023, Gabriel V C Candido
#
#   This piece of software is a derivative work of SYSeg, by Monaco F. J.
#   SYSeg is distributed under the license GNU GPL v3, and is available
#   at the official repository https://www.gitlab.com/monaco/syseg.
#
#   This file is part of so2023-gvccandido.
#
#   so2023-gvccandido is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

	.code16
	.global _start

_start:
	movb $0x0e, %ah             
	movw $0x00, %bx             # i <- 0
loop:
	movb hello_msg(%bx), %al    # %al <- hello_msg[i]
	                            # we need to use the linker arguments so the
	                            # binary is correctly located at memory and
	                            # offsets are correctly calculated (-Ttext=)
	cmp $0x00, %al              # if (%al == 0) # message is null-terminated
	je halt                     #     goto halt
	int $0x10                   # call BIOS video service
	add $0x01, %bx              # i <- i + 1
	jmp loop

halt:
	hlt                         # interruptions can awake the processor
	jmp halt                    # so we make it go to halt again

hello_msg:
	.string "Hello x86 bare-metal + assembly world!" # GAS makes it null-terminated

padding:
	.fill 510 - (. - _start), 1, 0 # 510 = 512 - 2 bytes from signature

signature:
	.word 0xaa55                # BIOS boot signature
