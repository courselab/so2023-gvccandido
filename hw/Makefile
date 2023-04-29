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




##
## Relevent files for this exercise.
##

all: ../tools/hex2bin hw-hex.bin hw-s.bin hw-c.bin

hw-hex.bin : hw.hex
	../tools/hex2bin $< $@

hw-s.bin : hw.S
	as --32 $< -o $@.o
	ld -melf_i386 -Ttext=0x7c00 --oformat=binary $@.o -o $@
	rm $@.o

hw-c.bin : hw.c
	gcc -m16 -O0 -I. -Wall -fno-pic -fcf-protection=none --freestanding -nostdlib -c rt0.c -o rt0.o
	gcc -m16 -O0 -I. -Wall -fno-pic -fcf-protection=none --freestanding -nostdlib -c stdio.c -o stdio.o
	gcc -m16 -O0 -I. -Wall -fno-pic -fcf-protection=none --freestanding -nostdlib -T hw.ld -Wl,--orphan-handling=discard hw.c -o $@
	rm rt0.o stdio.o

../tools/hex2bin : ../tools/hex2bin.c
	gcc $< -o $@

.PHONY: clean

clean:
	rm -rf *.bin *.o *.s hex2bin *.iso

# Create stand-alone distribution

EXPORT_FILES = hw.hex hw.S hw.c Makefile README ../../tools/hex2bin.c ../../tools/debug.h


# Self-contained pack distribution.
#
# make syseg-export     creates a tarball with the essential files, which
#       	        can be distributed independently of the rest of
#			this project.
#
# A pack distribution contain all the items necessary to build and run the
# relevant piece of software. It's useful,a for instance, to bundle
# self-contained subsections of SYSeg meant to be delivered as
# programming exercise assignments or illustrative source code examples.
#		
# In order to select which files should be included in the pack, list them
# in the appropriate variables
# 
# EXPORT_FILES_C    = C files (source, headers, linker scripts)
# EXPORT_FILES_MAKE = Makefiles
# EXPORT_FILES_TEXT = Text files (e.g. README)
# EXPORT_FILES_SH   = Shell scripts (standard /bin/sh)
#
# Except by text files, all other files will have their heading comment
# (the very first comment found in the file) replaced by a corresponding
# standard comments containing boilerplate copyright notice and licensing
# information, with blank fields to be filled in by the pack user.
# Attribution to SYSeg is also included for convenience.

TARNAME=hw-0.1.1



syseg-export export:
	@if ! test -f .dist; then\
	  make do_export;\
	 else\
	  echo "This is a distribution pack already. Nothing to be done.";\
	fi

do_export:
	rm -rf $(TARNAME)
	mkdir $(TARNAME)
	(cd .. && make clean && make)
	for i in $(EXPORT_FILES); do\
	  ../../tools/syseg-export $$i $(TARNAME);\
	done
	touch $(TARNAME)/.dist
	tar zcvf $(TARNAME).tar.gz $(TARNAME)

clean-export:
	rm -f $(TARNAME).tar.gz
	rm -rf $(TARNAME)

.PHONY: syseg-export export clean-export



# Include Make Bintools

# ------------------------------------------------------------
# The following excerpt of code was copied from MakeBintools,
# part of SYSeg, Copyright 2001 Monaco F. J..
# MakeBintools is a collection of handy 'GNU make' rules for
# inspecting and comparing the contents of source and object files.
# Further information: http://gitlab.com/monaco/syseg


##
## Configuration
##


# Inform your preferred graphical diff tool e.g meld, kdiff3 etc.

DIFF_TOOL=meld


##
## You probably don't need to change beyond this line
##

# Disassemble

# ALT = intel | att  (default: att)

ifndef ASM
ifeq (,$(findstring intel, $(MAKECMDGOALS)))
ASM_SYNTAX = att
else
ASM_SYNTAX = intel
endif
else
ASM_SYNTAX= $(ASM)
endif

# BIT = 16 | 32  (default: 32)

ifndef BIT
ifeq (,$(findstring 16, $(MAKECMDGOALS)))
ASM_MACHINE = i386
else
ASM_MACHINE = i8086
endif
else

ifeq ($(BIT),16)
ASM_MACHINE = i8086
else
ASM_MACHINE = i386
endif

endif


intel att 16 32: 
	@echo > /dev/null

diss d diss* d*:  $(IMG)
	@objdump -f $< > /dev/null 2>&1; \
	if test $$? -eq 1   ; then \
	  objdump -M $(ASM_SYNTAX) -b binary -m $(ASM_MACHINE) -D $< ; \
	else \
	  if test $@ = "diss" || test $@ = "d" ; then\
	    objdump -M $(ASM_SYNTAX) -m $(ASM_MACHINE) -d $< ; \
	  else\
	    objdump -M $(ASM_SYNTAX) -m $(ASM_MACHINE) -D $< ; \
	 fi;\
	fi

%/diss %/d %/diss* %/d*: %
	make $(@F) IMG=$< $(filter 16 32 intel att, $(MAKECMDGOALS))

%/i16 %/16i : %
	make --quiet $</diss intel 16
%/i32 %/32i %/i: %
	make --quiet $</diss intel 32
%/a16 %/16a %/16 : %
	make --quiet $</diss att 16
%/a32 %/32a %/32 %/a: %
	make --quiet $</diss att 32

%/i16* %/16i* : %
	make --quiet $</diss* intel 16
%/i32* %/32i* %/i*: %
	make --quiet $</diss* intel 32
%/a16* %/16a* %/16* : %
	make --quiet $</diss* att 16
%/a32* %/32a* %/32* %/a*: %
	make --quiet $</diss* att 32

# Run on the emulator

%/run : %
	@i=$< &&\
	if test $${i##*.} = "img"; then\
	    make run-fd IMG=$<;\
	 else\
	   if test $${i##*.} = "bin"; then\
	     make run-bin IMG=$<;\
	    fi;\
	fi

%/bin : %
	make run-bin IMG=$<

%/fd : %
	make run-fd IMG=$<

run-bin: $(IMG)
	qemu-system-i386 -drive format=raw,file=$< -net none

run-iso: $(IMG)
	qemu-system-i386 -drive format=raw,file=$< -net none

run-fd : $(IMG)
#	qemu-system-i386 -drive if=floppy,format=raw,file=$< -net none
	qemu-system-i386 -drive format=raw,file=$< -net none



# Dump contents in hexadecimal

hex raw dump: $(IMG)
	hexdump -C $<


%/hex %raw %/dump : %
	make --quiet dump IMG=$< 


# Diff-compare


MISSING_DIFF_TOOL="Can't find $(DIFF_TOOL); please edit syseg/tools/bintools.m4"

# Compare objects

objdiff bindiff : $(wordlist 2, 4, $(MAKECMDGOALS))
	if  test -z $$(which $(DIFF_TOOL)); then echo $(MISSING_DIFF_TOOL); exit 1; fi
	if test $(words $^) -lt 4 ; then\
	  bash -c "$(DIFF_TOOL) <(make $(wordlist 1,1,$^)/diss $(ASM) $(BIT)) <(make $(wordlist 2,2,$^)/diss $(ASM) $(BIT))";\
	else\
	  bash -c "$(DIFF_TOOL) <(make $(wordlist 1,1,$^)/diss $(ASM) $(BIT)) <(make $(wordlist 2,2,$^)/diss $(ASM) $(BIT)) <(make $(wordlist 3,3,$^)/diss $(ASM) $(BIT))";\
	fi

# Compare sources

srcdiff : $(wordlist 2, 4, $(MAKECMDGOALS))
	if  test -z $$(which $(DIFF_TOOL)); then echo $(MISSING_DIFF_TOOL); exit 1; fi
	if test $(words $^) -lt 3 ; then\
	  bash -c "$(DIFF_TOOL) $(wordlist 1,1,$^) $(wordlist 2,2,$^)";\
	else\
	  bash -c "$(DIFF_TOOL) $(wordlist 1,1,$^) $(wordlist 2,2,$^) $(wordlist 3,3,$^)";\
	fi

# Compare hex

hexdiff : $(wordlist 2, 4, $(MAKECMDGOALS))
	if  test -z $$(which $(DIFF_TOOL)); then echo $(MISSING_DIFF_TOOL); exit 1; fi
	if test $(words $^) -lt 4 ; then\
	  bash -c "$(DIFF_TOOL) <(make $(wordlist 1,1,$^)/hex $(ASM) $(BIT)) <(make $(wordlist 2,2,$^)/hex $(ASM) $(BIT))";\
	else\
	  bash -c "$(DIFF_TOOL) <(make $(wordlist 1,1,$^)/hex $(ASM) $(BIT)) <(make $(wordlist 2,2,$^)/hex $(ASM) $(BIT)) <(make $(wordlist 3,3,$^)/hex $(ASM) $(BIT))";\
	fi


# Compare objects and sources

diff : $(word 2, $(MAKECMDGOALS))
	@echo $(wordlist 2, 4, $(MAKECMDGOALS))
	@EXT=$(suffix $<);\
	case $$EXT in \
	.bin | .o)\
		make --quiet objdiff $(wordlist 2, 4, $(MAKECMDGOALS))\
		;;\
	.asm | .S.| .s | .i | .c | .h | .hex)\
		make --quiet srcdiff $(wordlist 2, 4, $(MAKECMDGOALS))\
		;;\
	.img )\
		make --quiet hexdiff $(wordlist 2, 4, $(MAKECMDGOALS))\
		;;\
	*)\
		echo "I don't know how to compare filetype $$EXT"\
		;;\
	esac


# Choose between intel|att and 16-bit|32-bot

diffi16 di16 i16:
	make --quiet diff $(wordlist 2, 4, $(MAKECMDGOALS)) ASM=intel BIT=16

diffi32 di32 i32:
	make --quiet diff $(wordlist 2, 4, $(MAKECMDGOALS)) ASM=intel BIT=32

diffa16 da16 a16:
	make --quiet diff $(wordlist 2, 4, $(MAKECMDGOALS)) ASM=att BIT=16

diffa32 da32 a32:
	make --quiet diff $(wordlist 2, 4, $(MAKECMDGOALS)) ASM=att BIT=32

##
## Create bootable USP stick if BIOS needs it
##

%.iso : %.bin
	xorriso -as mkisofs -b $< -o $@ -isohybrid-mbr $< -no-emul-boot -boot-load-size 4 ./

%.img : %.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$< of=$@ seek=0 conv=notrunc



stick: $(IMG)
	@if test -z "$(DEVICE)"; then \
	echo "*** ATTENTION: make IMG=foo.bin DEVICE=/dev/X"; exit 1; fi 
	dd if=$< of=$(DEVICE)

%/stick: %
	make stick IMG=$* DEVICE=$(wordlist 2, 2, $(MAKECMDGOALS))



.PHONY: clean clean-extra intel att 16 32 diss /diss /i16 /i32 /a16 /a32


# End of MakeBintools.
# -------------------------------------------------------------

