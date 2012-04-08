/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//! @file inti/gtk-sourceview/sourcestylescheme.h
//! @brief A GtkSourceStyleScheme C++ wrapper interface.

#ifndef XFC_GTK_SOURCE_STYLE_SCHEME_H
#define XFC_GTK_SOURCE_STYLE_SCHEME_H

#ifndef XFC_G_TYPE_H
#include <xfc/glib/type.hh>
#endif

#ifndef __GTK_SOURCE_STYLE_SCHEME_H__
#include <gtksourceview/gtksourcestylescheme.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {

class SourceTagStyle;

//! @class SourceStyleScheme sourcestylescheme.h xfc/sourceview/sourcestylescheme.hh
//! @brief A GtkSourceStyleScheme C++ wrapper class.

class SourceStyleScheme : public virtual G::TypeInterface
{
protected:
//! @name Constructors
//! @{

	virtual ~SourceStyleScheme() = 0;
	//!< Destructor.

public:

	typedef G::Signal1<void, const char*> StyleChangedSignalType;
	typedef G::SignalProxy<TypeInstance, StyleChangedSignalType> StyleChangedSignalProxy;
	static const StyleChangedSignalType style_changed_signal;

public:
	static SourceStyleScheme* get_default();
	//!< Returns a pointer to the default scheme object.

//! @name Accessors
//! @{

	GtkSourceStyleScheme* gtk_source_style_scheme() const { return reinterpret_cast<GtkSourceStyleScheme*>(instance_); }
	//!< Get a pointer to the GtkSourceStyleScheme structure.

	operator GtkSourceStyleScheme* () const;
	//!< Conversion operator; safely converts an SourceStyleScheme to a GtkSourceStyleScheme pointer.

	bool is_gtk_source_style_scheme() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_STYLE_SCHEME.

	String get_name() const;
	//!< Returns the name of the scheme.

	SourceTagStyle* get_tag_style(const String& style_name) const;
	//!< Gets the tag style for this scheme.
	//!< @param style_name The name of the source tag style.
	//!< @return The SourceTagStyle for <EM>style_name</EM>.

	bool get_style_names(std::vector<String>& names) const;
	//!< Get a list of the tag style names.
	//!< @param names A reference to a std::vector of String to hold the style names.
	//!< @return <EM>true</EM> if <EM>names</EM> is not empty.

//! @}
//! @name Signal Proxies
//! @{

	const StyleChangedSignalProxy sig_style_changed()
	{
		return StyleChangedSignalProxy(this, &style_changed_signal);
	}
	//!< Connect to the style_changed_signal; emitted whenever the tag style changes.
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_STYLE_SCHEME_H
