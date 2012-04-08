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

//! @file xfc/sourceview/sourcetagstyle.hh
//! @brief A GtkSourceTagStyle C++ wrapper interface.

#ifndef XFC_GTK_SOURCE_TAG_STYLE_HH
#define XFC_GTK_SOURCE_TAG_STYLE_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef __GTK_SOURCE_TAG_STYLE_H__
#include <gtksourceview/gtksourcetagstyle.h>
#endif

namespace Xfc {

namespace Gdk {
class Color;
}

namespace Gtk {

//! @class SourceTagStyle sourcetagstyle.h inti/gtk-sourceview/sourcetagstyle.h
//! @brief A GtkSourceTagStyle C++ wrapper class.

class SourceTagStyle : public G::Boxed
{
public:
//! @name Constructors
//! @{

	SourceTagStyle();
	//!< Constructs a new tag style.

	SourceTagStyle(const char *foregound);
	//!< Constructs a new tag style with the specified foreground color.

	SourceTagStyle(const Gdk::Color& foregound);
	//!< Constructs a new tag style with the specified foreground color.

	explicit SourceTagStyle(GtkSourceTagStyle *style);
	//!< Construct a new tag style from an existing GtkSourceTagStyle.
	//!< @param style A pointer to a GtkSourceTagStyle.
	//!<
	//!< <BR>The <EM>style</EM> can be a newly created GtkSourceTagStyle or an existing
	//!< GtkSourceTagStyle. The SourceTagStyle object created is a temporary object. It doesn't
	//!< take over the ownership of GtkSourceTagStyle and GtkSourceTagStyle is not freed by the
	//!< destructor.

	SourceTagStyle(GtkSourceTagStyle *style, bool copy);
	//!< Construct a new tag style from an existing GtkSourceTagStyle.
	//!< @param style A pointer to a GtkSourceTagStyle.
	//!< @param copy Whether the SourceTagStyle object should make a copy of GtkSourceTagStyle or not.
	//!<
	//!< <BR>The <EM>style</EM> can be a newly created GtkSourceTagStyle or an existing GtkSourceTagStyle.
	//!< If <EM>copy</EM> is true SourceTagStyle will make a copy of GtkSourceTagStyle. If <EM>copy</EM>
	//!< is false SourceTagStyle wont make a copy but instead takes over the ownership of GtkSourceTagStyle.
	//!< Either way, the destructor will free GtkSourceTagStyle when the SourceTagStyle object is destroyed.
	//!< This constructor is used by G::Boxed::wrap() to wrap GtkSourceTagStyle objects in a C++ wrapper.

	SourceTagStyle(const SourceTagStyle& src);
	//!< Copy constructor.
	//!< @param src The source tag style.

	~SourceTagStyle();
	//!< Destructor.

	SourceTagStyle& operator=(const SourceTagStyle& src);
	//!< Assignment operator.
	//!< @param src The source tag style.

//! @}
//! @name Accessors
//! @{

	GtkSourceTagStyle* gtk_source_tag_style() const { return (GtkSourceTagStyle*)boxed_; }
	//!< Get a pointer to the GtkSourceTagStyle structure.

	operator GtkSourceTagStyle* () const;
	//!< Conversion operator; safely converts a SourceTagStyle to a GdkSourceTagStyle pointer.

	bool is_default() const;
	//!< Returns true if this is the default tag style;

	Gdk::Color get_foreground() const;
	//!< Returns the tag style foreground color.

	Gdk::Color get_background() const;
	//!< Returns the tag style background color.

	bool get_italic() const;
	//!< Returns true if the tag style text is italic.

	bool get_bold() const;
	//!< Returns true if the tag style text is bold.

	bool get_underline() const;
	//!< Returns true if the tag style text is underlined.

	bool get_strikethrough() const;
	//!< Returns true if the tag style text is struck through.

//! @}
//! @name Methods
//! @{

	void set_foreground(const char *spec);
	//!< Set the tag style text foreground color from a textual specification.
	//!< @param spec The textual specification of the foreground color.

	void set_foreground(const Gdk::Color& color);
	//!< Set the tag style text foreground color.
	//!< @param color The foreground color.

	void unset_foreground();
	//!< Unset the tag style foreground color.

	void set_background(const char *spec);
	//!< Set the tag style text background color from a textual specification.
	//!< @param spec The textual specification of the background color.

	void set_background(const Gdk::Color& color);
	//!< Set the tag style text background color.
	//!< @param color The background color.

	void unset_background();
	//!< Unset the tag style background color.

	void set_italic(bool italic);
	//!< Set whether the tag style text use italics.

	void set_bold(bool bold);
	//!< Set whether the tag style text should be bold.

	void set_underline(bool underline);
	//!< Set whether the tag style text should be underlined.

	void set_strikethrough(bool strikethrough);
	//!< Set whether the tag style text should be struck through.

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_TAG_STYLE_H
