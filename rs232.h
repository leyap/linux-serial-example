/*
***************************************************************************
*
* Author: Teunis van Beelen
*
* Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014 Teunis van Beelen
*
* teuniz@gmail.com
*
***************************************************************************
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation version 2 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
***************************************************************************
*
* This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
*
***************************************************************************
*/

/* last revision: Januari 31, 2014 */

/* For more info and how to use this libray, visit: http://www.teuniz.net/RS-232/ */


#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>



#ifndef __win32__

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#else
#ifdef _win32
#include <windows.h>
#endif
#endif

int serialBegin (int, int, int);
int serialRead (int, unsigned char *, int);
int serialWriteByte (int, unsigned char);
int serialWrite (int, unsigned char *, int);
void serialClose (int);
void serialPrint (int, const char *);
int serialIsDCDEnabled(int);
int serialIsCTSEnabled(int);
int serialIsDSREnabled(int);
void serialEnableDTR(int);
void serialDisableDTR(int);
void serialEnableRTS(int);
void serialDisableRTS(int);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


