/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  version.cc - XFC version information
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include "version.hh"

/*  XFC major, minor and micro version numbers
 */

extern const unsigned int xfc_major_version = XFC_MAJOR_VERSION;
extern const unsigned int xfc_minor_version = XFC_MINOR_VERSION;
extern const unsigned int xfc_micro_version = XFC_MICRO_VERSION;

/*  xfc_check_version
 */

bool xfc_check_version(int major, int minor, int micro)
{
	return (XFC_MAJOR_VERSION > major ||
	       (XFC_MAJOR_VERSION == major && XFC_MINOR_VERSION > minor) ||
	       (XFC_MAJOR_VERSION == major && XFC_MINOR_VERSION == minor && XFC_MICRO_VERSION >= micro));
}

