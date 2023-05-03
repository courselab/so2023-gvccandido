#  Makefile - Make script.
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

CFLAGS := -Wall -Wextra -pedantic -std=c17 -m16 -O0 -fno-pic -fcf-protection=none -ffreestanding -nostdlib
INCLUDE := -I.

.PHONY: all clean purge

all: hw.hex.bin hw.S.bin hw.c.bin

hw.hex.bin: hw.hex
	make -C ../tools/
	../tools/hex2bin $< $@

hw.S.bin: hw.S
	as --32 $< -o $<.o
	ld -melf_i386 -Ttext=0x7c00 --oformat=binary $<.o -o $@
	rm $<.o

hw.c.bin: hw.o rt0.o stdio.o
	gcc $(CFLAGS) $(INCLUDE) -T hw.ld -Wl,--orphan-handling=discard $< -o $@

%.o: %.c
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

c_objects := hw.o rt0.o stdio.o
deps := $(c_objects:%.o=%.d)
include $(deps)
%.d: %.c
	gcc $(INCLUDE) -MM -MT '$(<:%.c=%.o) $@' $< > $@

%/run: %
	qemu-system-i386 -drive format=raw,file=$< -net none

%/dump: %
	hexdump -C $<

%.o/diss: %.o
	objdump -M att -d $<

%.bin/diss: %.bin
	objdump -M att -b binary -m i8086 -D $<

%.iso: %.bin
	xorriso -as mkisofs -b $< -o $@ -isohybrid-mbr $< -no-emul-boot -boot-load-size 4 ./

clean:
	rm -f *.o *.d

purge: clean
	rm -f *.bin *.iso
