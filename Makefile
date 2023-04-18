# Makefile - Main build script
#
#  Copyright (c) <year>, <author(s)-name>  <email(s)>
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


bootloader.bin : %.bin : %.o
	ld -melf_i386 --oformat=binary -Ttext=0x7c00  $< -o $@

bootloader.o : %.o : %.S
	as --32 $< -o $@


.PHONY: clean

clean:
	rm -f *.bin *.o
