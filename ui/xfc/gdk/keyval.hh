/*  XFC: Xfce Foundation Classes (User Interface Library)
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

/// @file xfc/gdk/keyval.hh
/// @brief A C++ interface for GDK key values.
///
/// Provides Keyval, an object that wraps a GDK key value and its associated functions.

#ifndef XFC_GDK_KEYVAL_HH
#define XFC_GDK_KEYVAL_HH

#ifndef XFC_INTEGER_OBJECT_HH
#include <xfc/integerobject.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __GDK_KEYS_H__
#include <gdk/gdkkeys.h>
#endif

namespace Xfc {

namespace Gdk {

/// @class Keyval keyval.hh xfc/gdk/keyval.hh
/// @brief A GDK key value C++ wrapper class.
///
/// The Keyval object represents a GDK key value. Examples of key values are GDK_a,
/// GDK_Enter, GDK_F1, etc. The complete list of key values can be found in the
/// <gdk/gdkkeysyms.h> header file. This header file is not included by XFC,
/// it must be included independently, because the file is quite large.
///
/// A keyval can be converted into a string representation with name(). The reverse,
/// a Keyval can be constructed from string. The case of key values can be determined
/// using is_upper() and is_lower(). Key values can be converted to upper or lower
/// case using to_upper() and to_lower(). When it makes sense, key values can be 
/// converted to and from Unicode characters with to_unicode() and from_unicode().

class Keyval : public IntegerObject<unsigned int>
{
public:
/// @name Constructors
/// @{

	Keyval();
	///< Construct a Keyval with an initial value of GDK_VoidSymbol.

	Keyval(unsigned int keyval);
	///< Construct a Keyval with the value <EM>keyval</EM>.
	///< @param keyval The keyval symbol; examples of keyvals are GDK_a, GDK_Enter, GDK_F1, etc.

	Keyval(const char *keyval_name);
	///< Construct a Keyval from a key name.
	///< @param keyval_name A key name.
	///<
	///< If the key name is not a valid key the Keyval's value will be GDK_VoidSymbol.

	Keyval(const String& keyval_name);
	///< Construct a Keyval from a key name.
	///< @param keyval_name A key name.
	///<
	///< If the key name is not a valid key the Keyval's value will be GDK_VoidSymbol.

	Keyval(const Keyval& src);
	///< Copy Constructor.
	///< @param src The source Keyval.

	Keyval& operator=(const Keyval& src);
	///< Assignment operator.
	///< @param src The source Keyval.

/// @}
/// @name Accessors
/// @{

	bool is_keyval() const;
	///< Returns true if the Keyval's value is not zero and not GDK_VoidSymbol.

	String name() const;
	///< Retrieves a the symbolic name for the key value.
	///< @return A String containing the name of the key, or a null String if this keyval is not a valid key.
	///<
	///< The names are the same as those in the <gdk/gdkkeysyms.h> header file
	///< but without the leading "GDK_".

	bool is_upper() const;
	///< Returns true if the given key value is in upper case, or if the keyval
	///< is not subject to case conversion.

	bool is_lower() const;
	///< Returns true if the given key value is in lower case, or if the keyval
	///< is not subject to case conversion.

/// @}
/// @name Methods
/// @{
	
	void convert_case(Keyval& lower, Keyval& upper);
	///< Obtains the upper-case and lower-case versions of the keyval symbol.
	///< @param lower The return location for lowercase version of the keyval.
	///< @param upper The return location for uppercase version of the keyval symbol.
	///<
	///< Examples of keyvals are GDK_a, GDK_Enter, GDK_F1, etc.
	
	Keyval to_upper() const;
	///< Converts this key value to upper case, if applicable.
	///< @return The upper case form of keyval, or keyval itself if it is already
	///< in upper case or it is not subject to case conversion.

	Keyval to_lower() const;
	///< Converts a key value to lower case, if applicable.
	///< @return The lower case form of keyval, or keyval itself if it is already
	///< in lower case or it is not subject to case conversion.

	G::Unichar to_unicode() const;
	///< Converts the keyval (GDK key symbol) to the corresponding ISO10646 (Unicode) character.
	///< @return The corresponding unicode character, or 0 if there is no corresponding character.

	void from_unicode(const G::Unichar& wc);
	///< Convert from a ISO10646 (Unicode) character to a GDK key symbol.
	///< @param wc A ISO10646 encoded character.
	///<
	///< If successful the keyval will be the corresponding GDK key symbol, if one exists,
	///< or GDK_VoidSymbol if there is no corresponding symbol.
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/keyval.inl>

#endif // XFC_GDK_KEYVAL_HH

