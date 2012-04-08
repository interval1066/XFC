/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
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

/// @file xfc/convert.hh
/// @brief Miscellaneous XFC conversion functions.

#ifndef XFC_CONVERT_HH
#define XFC_CONVERT_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

/// @name String conversion functions
/// @{
 
std::vector<String>
array_to_vector_of_string(const char *const *strs);
///< A convenience function that converts an array of C strings into a vector of String.
///< @param strs A null-terminated string array containing the C strings to be converted.
///< @return A vector of String containing the converted C strings.

char** 
vector_of_string_to_array(const std::vector<String>& strings);
///< A convenience function that converts a vector of String into an array of C strings.
///< @param strings A vector of String to convert into an array of C strings.
///< @return A null-terminated array of C strings; this array must be deleted when no longer required.
///<
///< The returned C string array is allocated with operator new [] and must be deleted
///< with operator delete [] when no longer required.

/// @}

} // namespace Xfc

#endif // XFC_CONVERT_HH

