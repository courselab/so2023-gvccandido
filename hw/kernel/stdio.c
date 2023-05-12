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

// short is considered to be 2 bytes long
static short *video = (short *) VIDEO_MEMORY;

// uses fastcall so the asm can access the argument easily
void __attribute__((fastcall)) __video_print(const char c)
{
	__asm__(
	"    movb %cl, %al     # %ax <- c (only the low bits for char matters)   \n"
	"    movb $0x0E, %ah   # set BIOS video to teletype writing              \n"
	"    int  $0x10        # call BIOS video service                         \n"
	);
}

void reset_video(const char mode)
{
	video = (short *) VIDEO_MEMORY;
	for (int i = 0; i < SCREEN_SIZE; ++i)
		video[i] = (mode << 8) + ' ';
	video = (short *) VIDEO_MEMORY;
}

int puts(const char *s)
{
	int i = 0;
	while (s[i]) {
		__video_print(s[i]);
		++i;
	}
	__video_print('\r');
	__video_print('\n');
	++i;

	return i;
}
