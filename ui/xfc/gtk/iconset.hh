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

/// @file xfc/gtk/iconset.hh
/// @brief A GtkIconSet C++ wrapper interface.
///
/// Provides IconSet, an object that represents a single icon in various sizes and widget states.

#ifndef XFC_GTK_ICON_SET_HH
#define XFC_GTK_ICON_SET_HH

#ifndef XFC_GTK_ICON_SOURCE_HH
#include <xfc/gtk/iconsource.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

class Style;
class Widget;

/// @class IconSet iconfactory.hh xfc/gtk/iconfactory.hh
/// @brief A GtkIconSet C++ wrapper class.
///
/// An IconSet represents a single icon in various sizes and widget states. It can
/// provide a Gdk::Pixbuf for a given size and state on request, and automatically
/// caches some of the rendered Gdk::Pixbuf objects. Normally you would use 
/// Gtk::Widget::render_icon() instead of using IconSet directly. The one case 
/// where you'd use IconSet is to create application-specific icon sets to place
/// in an IconFactory.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class IconSet : public G::Boxed
{
public:
/// @name Constructors
/// @{

	IconSet();
	///< Constructs a new IconSet with a reference count of 1 that the caller owns.

	explicit IconSet(Gdk::Pixbuf& pixbuf);
	///< Constructs a new IconSet with pixbuf as the default/fallback source image. 
	///< @param pixbuf A Gdk::Pixbuf.
	///<
	///< If you don't add any additional IconSource to the icon set, all variants of the
	///< icon will be created from pixbuf, using scaling, pixelation, etc. as required to
	///< adjust the icon size or make the icon look insensitive/prelighted. The IconSet
	///< is created with a reference count of 1 that the caller owns.

	explicit IconSet(GtkIconSet *icon_set);
	///< Constructs a new IconSet from an existing GtkIconSet.
	///< @param icon_set A GtkIconSet.
	///<
	///< This constructor creates a temporary wrapper for a GtkIconSet. It neither
	///< copies the GtkIconSet or takes over its ownership. The IconSet is created with
	///< a reference count of 1 that the caller owns.

	IconSet(GtkIconSet *icon_set, bool copy);
	///< Constructs a new IconSet from an existing GtkIconSet.
	///< @param icon_set A GtkIconSet.
	///< @param copy <EM>true</EM> if a copy of GtkIconSet should be made.
	///<
	///< This constructor either takes over the ownership of the GtkIconSet, or makes
	///< a copy of the GtkIconSet. The IconSet is created with a reference count of 1 that
	///< the caller owns. This constructor is primarily intended for use by the
	///< G::Boxed::wrap() method.

	IconSet(const IconSet& src);
	///< Copy constructor.

	~IconSet();
	///< Destructor.

	IconSet& operator=(const IconSet& src);
	///< Assignment operator.
	
/// @}
/// @name Accessors
/// @{

	GtkIconSet* gtk_icon_set() const;
	///< Get a pointer to the GtkIconSet structure.

	operator GtkIconSet* () const;
	///< Conversion operator; safely converts an IconSet to a GtkIconSet pointer.

	bool get_sizes(std::vector<IconSize>& sizes) const;
	///< Obtains a list of icon sizes this icon set can render.
	///< @param sizes A reference to a vector of IconSize to hold the sizes.
	///< @return <EM>true</EM> if <EM>sizes</EM> contains any sizes; <EM>false</EM> if empty.

/// @}
/// @name Methods
/// @{

	Pointer<Gdk::Pixbuf> render_icon(Style& style, StateType state, IconSize size,
	                                 Widget* widget = 0, const char *detail = 0,
					 TextDirection direction = TEXT_DIR_LTR);
	///< Renders an icon using Gtk::Style::render_icon().
	///< @param style A Style associated with widget.
	///< @param state The widget state.
	///< @param size The icon size.
	///< @param widget The widget that will display the icon, or null.
	///< @param detail The detail to pass to the theme engine, or null.
	///< @param direction The text direction.
	///< @return A Gdk::Pixbuf to be displayed.
	///<
	///< In most cases, Gtk::Widget::render_icon() is better, since it automatically provides
	///< most of the arguments from the current widget settings. This method never returns null;
	///< if the icon can't be rendered (perhaps because an image file fails to load), a default
	///< "missing image" icon will be returned instead. A smart pointer to a Gdk::Pixbuf is 
	///< returned because the returned pixbuf must be unreferenced. This will happen automatically
	///< when the smart pointer goes out of scope.

	void add_source(const IconSource& source);
	///< Add an IconSource to the icon set.
	///< @param source An IconSource.
	///<
	///< Icon sets have a list of IconSource, which they use as base icons for rendering icons
	///< in different states and sizes. 
	///<
	///< Icons are scaled, made to look insensitive, etc. in render_icon(), but IconSet needs base
	///< images to work with. The base images and when to use them are described by a IconSource.
	///< This method copies <EM>source</EM>, so you can reuse the same source immediately without
	///< affecting the icon set. An example of when you'd use this method: a web browser's "Back
	///< to Previous Page" icon might point in a different direction in Hebrew and in English;
	///< it might look different when insensitive; and it might change size depending on toolbar
	///< mode (small/large icons). So a single icon set would contain all those variants of the
	///< icon, and you might add a separate source for each one.
	///<
	///< You should nearly always add a "default" icon source with all fields wildcarded, which will
	///< be used as a fallback if no more specific source matches. IconSet always prefers more specific
	///< icon sources to more generic icon sources. The order in which you add the sources to the icon
	///< set does not matter. When you construct an IconSet with a pixbuf, the icon set creates a default
	///< icon source based on the pixbuf.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/iconset.inl>

#endif // XFC_GTK_ICON_SET_HH

