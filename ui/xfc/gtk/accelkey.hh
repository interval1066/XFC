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

/// @file xfc/gtk/accelkey.hh
/// @brief A GtkAccelKey C++ wrapper interface.
///
/// Provides AccelKey, an object that represents an accelerator key and its 
/// modifier and accelerator flags.

#ifndef XFC_GTK_ACCEL_KEY_HH
#define XFC_GTK_ACCEL_KEY_HH

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class AccelKey accelkey.hh xfc/gtk/accelkey.hh
/// @brief An accelerator key value, modifier and flag class.
///
/// AccelKey encapsulates an accelerator key, its accelerator flags (for configuring the accelerator)
/// and its modifier flags (the modifier combination of the accelerator).

class AccelKey
{
	GtkAccelKey key_;

public:
/// @name Constructors
/// @{

	AccelKey();
	///< Construct an empty AccelKey.

	AccelKey(const char *accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	AccelKey(const String& accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	///< Construct an AccelKey from a string representing an accelerator.
	///< @param accelerator A string representing an accelerator.
	///< @param accel_flags A flag mask to configure this accelerator.
	///<
	///< Parses a string representing an accelerator. The format looks like "\<Control\>a" or
	///< "\<Shift\>\<Alt\>F1" or "\<Release\>z" (the last one is for key release). The parser is fairly
	///< liberal and allows lower or upper case, and also abbreviations such as "\<Ctl\>" and "\<Ctrl\>".
	///< If the parse fails, accelerator and its modifiers will be set to 0 (zero).

	AccelKey(unsigned int accel_key, Gdk::ModifierTypeField accel_mods, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	///< Construct an AccelKey with the specified key, modifier and flag values.
	///< @param accel_key Key value of the accelerator.
	///< @param accel_mods Modifier combination of the accelerator.
	///< @param accel_flags A flag mask to configure this accelerator.

	AccelKey(const AccelKey& src);
	///< Copy constructor.

	AccelKey& operator=(const AccelKey& src);
	///< Assignment operator.

/// @}
/// @name Accessors
/// @{

	GtkAccelKey* gtk_accel_key() const;
	///< Get a pointer to the GtkAccelKey structure.

	operator GtkAccelKey* () const;
	///< Conversion operator; safely converts an AccelKey to a GtkAccelKey pointer.

	unsigned int key() const;
	///< Get the key value of the accelerator.

	Gdk::ModifierTypeField mods() const;
	///< Get the modifier flags.

	AccelFlagsField flags() const;
	///< Get the accelerator flags.

/// @}
/// @name Methods
/// @{

	void set(const char *accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	void set(const String& accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	///< Set the accelerator values from a string representation of an accelerator.
	///< @param accelerator A string representing an accelerator.
	///< @param accel_flags A flag mask to configure this accelerator.
	///<
	///< Parses a string representing an accelerator. The format looks like "\<Control\>a" or
	///< "\<Shift\>\<Alt\>F1" or "\<Release\>z" (the last one is for key release). The parser is fairly
	///< liberal and allows lower or upper case, and also abbreviations such as "\<Ctl\>" and "\<Ctrl\>".
	///< If the parse fails, accelerator and its modifiers will be set to 0 (zero).

	void set(unsigned int accel_key, Gdk::ModifierTypeField accel_mods, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
	///< Set the accelerator key, modifier and flag values.
	///< @param accel_key Key value of the accelerator.
	///< @param accel_mods Modifier combination of the accelerator.
	///< @param accel_flags A flag mask to configure this accelerator.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/accelkey.inl>

#endif // XFC_GTK_ACCEL_KEY_HH

