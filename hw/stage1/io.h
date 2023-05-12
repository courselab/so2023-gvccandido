/* io.h - I/O implementation for x86 bare-metal booting using C
 
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

#ifndef __IO_H__
#define __IO_H__

#define VIDEO_MEMORY 0x000B8000

#define VIDEO_GRAY_ON_BLACK 0x07
#define VIDEO_GREEN_ON_BLACK 0x02

#define SCREEN_COLS (80)
#define SCREEN_LINES (25)
#define SCREEN_SIZE (SCREEN_LINES * SCREEN_COLS)

// __video_print is really meant to internal use, but is convenient to print
//  disk errors on stage1's __fatal (from boot.c)
void __attribute__((fastcall)) __video_print(const char c);
int puts(const char *s);

#endif // __IO_H__
