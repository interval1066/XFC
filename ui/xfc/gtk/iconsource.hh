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

/// @file xfc/gtk/iconsource.hh
/// @brief A GtkIconSource C++ wrapper interface.
///
/// Provides IconSource, an object that contains a Gdk::Pixbuf (or image filename) 
/// that serves as the base image for one or more of the icons in an IconSet, along
/// with a specification for which icons in the icon set will be based on that pixbuf
/// or image file. 

#ifndef XFC_GTK_ICON_SOURCE_HH
#define XFC_GTK_ICON_SOURCE_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_ICON_FACTORY_H__
#include <gtk/gtkiconfactory.h>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

/// @class IconSource iconfactory.hh xfc/gtk/iconfactory.hh
/// @brief A GtkIconSource C++ wrapper class.
///
/// An IconSource contains a Gdk::Pixbuf (or image filename) that serves as the base image
/// for one or more of the icons in an IconSet, along with a specification for which icons
/// in the icon set will be based on that pixbuf or image file. An icon set contains a set
/// of icons that represent "the same" logical concept in different states, different global
/// text directions, and different sizes.
///
/// So for example a web browser's "Back to Previous Page" icon might point in a different
/// direction in Hebrew and in English; it might look different when insensitive; and it 
/// might change size depending on toolbar mode (small/large icons). So a single icon set
/// would contain all those variants of the icon. IconSet contains a list of IconSource 
/// from which it can derive specific icon variants in the set.
///
/// In the simplest case, IconSet contains one source pixbuf from which it derives all variants.
/// The constructor IconSource(Gdk::Pixbuf&) handles this case; if you only have one source 
/// pixbuf, just use that constructor. If you want to use a different base pixbuf for different
/// icon variants, you create multiple icon sources, mark which variants they'll be used to 
/// create, and add them to the icon set with Gtk::IconSet::add_source(). By default, the icon
/// source has all parameters wildcarded. That is, the icon source will be used as the base icon
/// for any desired text direction, widget state, or icon size.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class IconSource : public G::Boxed
{
public:
/// @name Constructors
/// @{

	IconSource();
	///< Construct a new IconSource with a reference count of 1 that the caller owns.

	explicit IconSource(GtkIconSource *source);
	///< Construct a new IconSource from an existing GtkIconSource.
	///< @param source A GtkIconSource.
	///<
	///< This constructor creates a temporary wrapper for a GtkIconSource. It neither
	///< copies the GtkIconSource or takes over its ownership. The IconSource is created with
	///< a reference count of 1 that the caller owns.

	IconSource(GtkIconSource *source, bool copy);
	///< Construct a new IconSource from an existing GtkIconSource.
	///< @param source A GtkIconSource.
	///< @param copy <EM>true</EM> if a copy of GtkIconSource should be made.
	///<
	///< This constructor either takes over the ownership of the GtkIconSource, or makes
	///< a copy of the GtkIconSource. The IconSource is created with a reference count of 1
	///< that the caller owns. This constrcutor is primarily intended for use by the 
	///< G::Boxed::wrap() method.

	IconSource(const IconSource& src);
	///< Copy constructor.

	~IconSource();
	///< Destructor.

	IconSource& operator=(const IconSource& src);
	///< Assignment operator.

/// @}
/// @name Accessors
/// @{

	GtkIconSource* gtk_icon_source() const;
	///< Get a pointer to the GtkIconSource structure.

	operator GtkIconSource* () const;
	///< Conversion operator; safely converts an IconSource to a GtkIconSource pointer.

	String get_filename() const;
	///< Retrieves the source filename.
	///< @return The source filename or a null String if none is set.

	String get_icon_name() const;
	///< Retrieves the source icon name, or null if none is set.
	///< @return The icon name.

	Gdk::Pixbuf* get_pixbuf() const;
	///< Retrieves the source pixbuf, or null if none is set.
	///< The reference count on the pixbuf is not incremented.

	bool get_size_wildcarded() const;
	///< Gets the value set by set_size_wildcarded().
	///< @return <EM>true</EM> if this icon source is a base for any icon size variant.

	bool get_state_wildcarded() const;
	///< Gets the value set by set_state_wildcarded().
	///< return <EM>true</EM> if this icon source is a base for any widget state variant.

	bool get_direction_wildcarded() const;
	///< Gets the value set by set_direction_wildcarded().
	///< @return <EM>true</EM> if this icon source is a base for any text direction variant.

	TextDirection get_direction() const;
	///< Obtains the text direction this icon source applies to.
	///< @return The text direction this source matches.
	///<
	///< The return value is only useful/meaningful if the text direction is not wildcarded.
	
	StateType get_state() const;
	///< Obtains the widget state this icon source applies to. 
	///< @return The widget state this source matches.
	///<
	///< The return value is only useful/meaningful if the widget state is not wildcarded.

	IconSize get_size() const;
	///< Obtains the icon size this icon source applies to.
	///< @return The icon size this source matches.
	///<
	///< The return value is only useful/meaningful if the icon size is not wildcarded.

/// @}
/// @name Methods
/// @{

	void set_filename(const char *filename);
	void set_filename(const String& filename);
	///< Sets the name of an image file to use as a base image when creating icon variants
	///< for IconSet.
	///< @param filename The image file to use.
	///<
	///< The filename must be absolute.

	void set_icon_name(const char *icon_name);
	void set_icon_name(const String& icon_name);
	///< Sets the name of an icon to look up in the current icon theme, to use as a base image
	///< when creating icon variants for Gtk::IconSet.
	///< @param icon_name The name of icon to use.

	void set_pixbuf(Gdk::Pixbuf *pixbuf);
	///< Sets a pixbuf to use as a base image when creating icon variants for IconSet.
	///< @param pixbuf The pixbuf to use as a source.
	///<
	///< If an icon source has both a filename and a pixbuf set, the pixbuf will take priority.

	void set_direction_wildcarded(bool setting);
	///< If the text direction is wildcarded, this source can be used as the base image for
	///< an icon in any TextDirection.
	///< @param setting <EM>true</EM> to wildcard the text direction.
	///<
	///< If the text direction is not wildcarded, then the text direction the icon source 
	///< applies to should be set with set_direction(), and the icon source will only be used
	///< with that text direction. IconSet prefers non-wildcarded sources (exact matches) over
	///< wildcarded sources, and will use an exact match when possible.

	void set_state_wildcarded(bool setting);
	///< If the widget state is wildcarded, this source can be used as the base image for an
	///< icon in any StateType.
	///< @param setting <EM>true</EM> to wildcard the widget state.
	///<
	///< If the widget state is not wildcarded, then the state the source applies to should
	///< be set with set_state() and the icon source will only be used with that specific state.
	///< IconSet prefers non-wildcarded sources (exact matches) over wildcarded sources, and 
	///< will use an exact match when possible. IconSet will normally transform wildcarded source
	///< images to produce an appropriate icon for a given state, for example lightening an image
	///< on prelight, but will not modify source images that match exactly.

	void set_size_wildcarded(bool setting);
	///< If the icon size is wildcarded, this source can be used as the base image for an icon
	///< of any size. 
	///< @param setting <EM>true</EM> to wildcard the icon size.
	///<
	///< If the size is not wildcarded, then the size the source applies to should be set
	///< with set_size() and the icon source will only be used with that specific size. IconSet
	///< prefers non-wildcarded sources (exact matches) over wildcarded sources, and will use
	///< an exact match when possible. IconSet will normally scale wildcarded source images to
	///< produce an appropriate icon at a given size, but will not change the size of source
	///< images that match exactly.
	
	void set_direction(TextDirection direction);
	///< Sets the text direction this icon source is intended to be used with.
	///< @param direction The text direction this source applies to.
	///< 
	///< Setting the text direction on an icon source makes no difference if the text direction
	///< is wildcarded. Therefore, you should usually call set_direction_wildcarded() to un-wildcard
	///< it in addition to calling this method.

	void set_state(StateType state);
	///< Sets the widget state this icon source is intended to be used with.
	///< @param state The widget state this source applies to.
	///<
	///< Setting the widget state on an icon source makes no difference if the state is
	///< wildcarded. Therefore, you should usually call set_state_wildcarded() to un-wildcard
	///< it in addition to calling this method.

	void set_size(IconSize size);
	///< Sets the icon size this icon source is intended to be used with.
	///< @param size The icon size this source applies to.
	///< 
	///< Setting the icon size on an icon source makes no difference if the size is wildcarded.
	///< Therefore, you should usually call set_size_wildcarded() to un-wildcard it in addition to
	///< calling this method.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/iconsource.inl>

#endif // XFC_GTK_ICON_SOURCE_HH

