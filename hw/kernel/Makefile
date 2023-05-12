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

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

PROJECT := kernel
STDLIB_OBJECTS := stdio.o
LINK_OBJECTS := main.o kernel.o
OBJECTS := $(STDLIB_OBJECTS) $(LINK_OBJECTS)
LD_CONFIG := kernel.ld
INCLUDE := .

.PHONY: all clean purge

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c17 -m16 -O0 -fno-pic -fcf-protection=none -ffreestanding -nostdlib
LDFLAGS := -Wl,--orphan-handling=discard
CPPFLAGS := -I$(INCLUDE)

all: $(PROJECT).bin

$(PROJECT).bin: $(OBJECTS) $(LD_CONFIG)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -T $(LD_CONFIG) $(LINK_OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

DEPS_FILES := $(OBJECTS:%.o=%.d)
include $(DEPS_FILES)
%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MT '$(<:%.c=%.o) $@' $< > $@

%.o/diss: %.o
	objdump -M att -d $<

%.bin/diss: %.bin
	objdump -M att -b binary -m i8086 -D $<

clean:
	rm -f *.o *.d

purge: clean
	rm -f *.bin
