/* hw.ld - linker config for x86 bare-metal boot using C
 
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

OUTPUT_FORMAT(binary);      /* flat binary */
SECTIONS
{
	. = 0x7C00;             /* go to 0x7C00 */
	.text :
	{
		*(.text)
		*(.rodata)
	}
	. = 0x7C00 + 510;       /* advance 510 bytes */
	.signature :
	{
		BYTE(0x55)
		BYTE(0xAA)
	}
	__END_STACK__ = 0xFFFF; /* end of 64KiB segment (~32KiB for stack) */
}
STARTUP(rt0.o);
INPUT(stdio.o)
