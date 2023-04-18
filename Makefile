# Makefile - Main build script
#
#  Copyright (c) 2023, Gabriel V C Candido     gvcc15@c3sl.ufpr.br
#  This file is part of <project>
#  <project> is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

.PHONY: all clean purge disassembly run stick

all: bootloader.bin

disassembly: bootloader.bin
	objdump -M att -b binary -m i386 $<

run: bootloader.bin
	qemu-system-i386 -drive file=$<,format=raw -net none

stick: bootloader.iso
	echo dd if=$< of=/dev/sdb

bootloader.iso: bootloader.bin
	dd if=/dev/zero of=bootloader.img bs=1024 count=1440
	dd if=$< of=bootloader.img seek=0 conv=notrunc
	xorriso -as mkisofs -b bootloader.img -o $@ -isohybrid-mbr bootloader.img -no-emul-boot -boot-load-size 4 ./
	rm bootloader.img

bootloader.bin : %.bin : %.o
	ld -melf_i386 --oformat=binary -Ttext=0x7c00 $< -o $@

bootloader.o : %.o : %.S
	as --32 $< -o $@

clean:
	rm -f *.o

purge: clean
	rm -f *.bin
