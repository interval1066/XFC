/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

/// @file xfc/version.hh
/// @brief XFC version information.

#ifndef XFC_VERSION_HH
#define XFC_VERSION_HH

/// Compile time major version macro.
#define XFC_MAJOR_VERSION (4)

/// Compile time minor version macro.
#define XFC_MINOR_VERSION (3)

/// Compile time micro version macro.
#define XFC_MICRO_VERSION (4)

/// @name Library Version
/// @{

extern const unsigned int xfc_major_version;
///< Major version number.

extern const unsigned int xfc_minor_version;
///< Minor version number.

extern const unsigned int xfc_micro_version;
///< Micro version number.

bool xfc_check_version(int major, int minor, int micro);
///< Check whether an XFC version equal to or greater than major.minor.micro is present.

/// @}

#endif // XFC_VERSION_HH

