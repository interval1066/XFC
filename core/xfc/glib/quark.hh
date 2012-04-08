/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/glib/quark.hh
/// @brief GQuark C++ interface.
///
/// Quarks provide a 2-way association between a string and a unique integer identifier.

#ifndef XFC_G_QUARK_HH
#define XFC_G_QUARK_HH

#ifndef XFC_INTEGER_OBJECT_HH
#include <xfc/integerobject.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_QUARK_H__
#include <glib/gquark.h>
#endif

namespace Xfc {

namespace G {

/// @class Quark quark.hh xfc/glib/quark.hh
/// @brief A GQuark C++ wrapper interface
///
/// Quarks are associations between strings and integer identifiers. Given either the
/// string or the Quark identifier it is possible to retrieve the other. Quarks are used
/// to get and set object properties and used data pointers.

class Quark : public IntegerObject<GQuark>
{
public:
/// @name Constructors
/// @{

	Quark(const char *str);
	///< Construct a Quark from a string
	///< @param str A string.
	///<
	///< Wraps the GQuark identifying the given string. If the string does not currently
	///< have an associated GQuark, a new GQuark is created, using a copy of the string.

	Quark(const String& str);
	///< Construct a Quark from a String
	///< @param str A String.
	///<
	///< Wraps the GQuark identifying the given string. If the string does not currently
	///< have an associated GQuark, a new GQuark is created, using a copy of the string.
	
	Quark(GQuark quark);
	///< Construct a quark from an existing GQuark.
	///< @param quark A GQuark.

	Quark(const Quark& src);
	///< Copy Constructor.
	///< @param src The source Quark.

	Quark& operator=(const Quark& src);
	///< Assignment operator.
	///< @param src The source Quark.

/// @}
/// @name Accessors
/// @{

	operator String() const;
	///< Conversion operator; returns the string associated with the quark
	
/// @}
/// @name Accessors
/// @{

	static Quark try_string(const char *str);
	///< Gets the quark associated with the given string.
	///< @param str A string.
	///< @return The quark, or null if the string has no associated quark.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/quark.inl>

#endif // XFC_G_QUARK_HH


	
