/*  XFC: Xfce Foundation Classes (User Interface Library)
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

/// @file xfc/gtk/icontheme.hh
/// @brief A GtkIconTheme C++ wrapper interface.
///
/// Provides IconTheme, an object that provides a facility for looking up icons by name and size.

#ifndef XFC_GTK_ICON_THEME_HH
#define XFC_GTK_ICON_THEME_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __GTK_ICON_THEME_H__
#include <gtk/gtkicontheme.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gdk {
class Pixbuf;
class Point;
class Rectangle;
class Screen;
}

namespace Gtk {

/// @enum IconLookupFlags
/// The flags used to specify options for Gtk::IconTheme::lookup_icon().

enum IconLookupFlags
{
	ICON_LOOKUP_NO_SVG = GTK_ICON_LOOKUP_NO_SVG,
	///< Never return SVG icons, even if gdk-pixbuf supports them; Cannot be used
	///< together with Gtk::ICON_LOOKUP_FORCE_SVG.
	
	ICON_LOOKUP_FORCE_SVG = GTK_ICON_LOOKUP_FORCE_SVG,
	///< Return SVG icons; Cannot be used together with Gtk::ICON_LOOKUP_NO_SVG.
	
	ICON_LOOKUP_USE_BUILTIN = GTK_ICON_LOOKUP_USE_BUILTIN
	///< When passed to Gtk::IconTtheme::lookup_icon() includes builtin icons as well as files.
	///< For a builtin icon, Gtk::IconInfo::get_filename() returns null and you need to call
	///< Gtk::IconInfo::get_builtin_pixbuf().
};

/// IconLookupFlagsField holds one or more values from the Gtk::IconLookupFlags enumeration OR'd together.

typedef unsigned int IconLookupFlagsField;

/// @enum IconThemeError
/// Error codes for Gtk::IconTheme operations.
 
enum IconThemeError
{
	ICON_THEME_NOT_FOUND = GTK_ICON_THEME_NOT_FOUND, ///< The icon specified does not exist in the theme.
	ICON_THEME_FAILED = GTK_ICON_THEME_FAILED ///< An unspecified error occurred.
};

/// @class IconInfo icontheme.hh xfc/gtk/icontheme.hh
/// @brief A GtkIconInfo C++ wrapper class.
///
/// IconInfo contains information found when looking up an icon in an icon theme
/// with Gtk::IconTheme::look_up(). 

class IconInfo : public G::Boxed
{
public:
/// @name Constructors
/// @{
	
	explicit IconInfo(GtkIconInfo *icon_info);
	///< Construct a new IconInfo from an existing GtkIconInfo.
	///< @param icon_info A GtkIconInfo.
	///<
	///< This constructor creates a temporary wrapper for a GtkIconInfo. 
	///< It neither copies the GtkIconInfo or takes over its ownership. The
	///< IconInfo is created with a reference count of 1 that the caller owns.

	IconInfo(GtkIconInfo *icon_info, bool copy);
	///< Construct a new IconInfo from an existing GtkIconInfo.
	///< @param icon_info A GtkIconInfo.
	///< @param copy <EM>true</EM> if a copy of GtkIconInfo should be made.
	///<
	///< This constructor either takes over the ownership of the GtkIconInfo, 
	///< or makes a copy of the GtkIconInfo. The IconInfo is created with a reference
	///< count of 1 that the caller owns. This constructor is primarily intended for
	///< use by the G::Boxed::wrap() method. 

	IconInfo(const IconInfo& src);
	///< Copy constructor.

	~IconInfo();
	///< Destructor.

	IconInfo& operator=(const IconInfo& src);
	///< Assignment operator.

/// @}
/// @name Accessors
/// @{

	GtkIconInfo* gtk_icon_info() const;
	///< Get a pointer to the GtkIconInfo structure.

	operator GtkIconInfo* () const;
	///< Conversion operator; safely converts a IconInfo to a GtkIconInfo pointer.
	
	int get_base_size() const;
	///< Gets the base size for the icon. 
	///< @return The base size, or 0, if no base size is known for the icon. 
	///<	
	///< The base size is a size for the icon that was specified by the icon theme creator.
	///< This may be different than the actual size of image; an example of this is small emblem
	///< icons that can be attached to a larger icon. These icons will be given the same base size
	///< as the larger icons to which they are attached.

	String get_filename() const;
	///< Gets the filename for the icon. 
	///< @return The filename for the icon, or null if get_builtin_pixbuf() should be used instead.
	///<	
	///< If the Gtk::ICON_LOOKUP_USE_BUILTIN flag was passed to Gtk::IconTheme::lookup_icon(),
	///< there may be no filename if a builtin icon is returned; in this case, you should use 
	///< get_builtin_pixbuf().

 	Gdk::Pixbuf* get_builtin_pixbuf() const;
	///< Gets the built-in image for this icon, if any. 
	///< @return The built-in image pixbuf, or null.
	///<	
	///< To allow GTK+ to use built in icon images, you must pass the 
	///< Gtk::ICON_LOOKUP_USE_BUILTIN to Gtk::IconTheme::lookup_icon().
	 
	bool get_embedded_rect(Gdk::Rectangle& rectangle) const;
	///< Gets the coordinates of a rectangle within the icon that can be used for
	///< display of information such as a preview of the contents of a text file
	///< (see set_raw_coordinates() for further information about the coordinate system).
	///< @param rectangle A Gdk::Rectangle in which to store embedded rectangle coordinates.
	///< @returns <EM>true</EM> if the icon has an embedded rectangle.
	///< 
	///< Coordinates are only stored when this function returns true. 

	std::vector<Gdk::Point> get_attach_points() const;
	///< Fetches the set of attach points for an icon. 
	///< @return A vector of Gdk::Point that holds the attach points.
	///<
	///< An attach point is a location in the icon that can be used as anchor points
	///< for attaching emblems or overlays to the icon.

	bool has_attach_points() const;
	///< Determines whether there are any attach points for the icon.
	///< @return <EM>true</EM> if there are any attach points for the icon.
	
	String get_display_name() const;
	///< Gets the display name for an icon. 
	///< @return The display name for the icon, or null if the icon doesn't have a specified display name.
	///<	
	///< A display name is a string to be used in place of the icon name
	///< in a user visible context like a list of icons.

/// @}
/// @name Methods
/// @{

	Pointer<Gdk::Pixbuf> load_icon(G::Error *error = 0);
	///< Renders an icon previously looked up in an icon theme using Gtk::IconTheme::lookup_icon().
	///< @param error The location to store error information on failure, or null. 
	///< @returns A smart pointer to the rendered icon, or null if the icon isn't found. 
	
	///< The size will be based on the size passed to Gtk::IconTheme::lookup_icon(). 
	///< Note that the resulting pixbuf may not be exactly this size; an icon theme may
	///< have icons that differ slightly from their nominal sizes, and in addition GTK+
	///< will avoid scaling icons that it considers sufficiently close to the requested
	///< size (this maintains sharpness).
	///<	
	///< The rendered icon may be a newly created icon or a new reference to an 
	///< internal icon, so you must not modify the icon.

	void set_raw_coordinates(bool raw_coordinates);
	///< Sets whether the coordinates returned by get_embedded_rect() and get_attach_points()
	///< should be returned in their original form as specified in the icon theme, instead of
	///< scaled appropriately for the pixbuf returned by load_icon(). 
	///< @param raw_coordinates Whether the coordinates of embedded rectangles and attached points
	///< should be returned in their original (unscaled) form. 
	///<
	///< Raw coordinates are somewhat strange; they are specified to be with respect to
	///< the unscaled pixmap for PNG and XPM icons, but for SVG icons, they are in a 1000x1000
	///< coordinate space that is scaled to the final size of the icon. You can determine if
	///< the icon is an SVG icon by using get_filename(), and seeing if it is non-null and 
	///< ends in '.svg'. 
	///<
	///< This method is provided primarily to allow compatibility wrappers for older API's,
	///< and is not expected to be useful for applications.

/// @}
};

/// @class IconTheme icontheme.hh xfc/gtk/icontheme.hh
/// @brief A GtkIconTheme C++ wrapper class.
///
/// IconTheme acts as a database of information about an icon theme. Normally, you
/// retrieve the icon theme for a particular screen using Gtk::IconTeme::get_for_screen()
/// and it will contain information about current icon theme for that screen, but you can
/// also create a new IconTheme object and set the icon theme name explicitely using 
/// Gtk::IconTheme::set_custom_theme(). 
///
/// IconTheme provides a facility for looking up icons by name and size. The main reason
/// for using a name rather than simply providing a filename is to allow different icons
/// to be used depending on what icon theme is seleceted by the user. The operation of icon
/// themes on Linux and Unix follows the Icon Theme Specification. There is a default icon
/// theme, named hicolor where applications should install their icons, but more additional
/// application themes can be installed as operating system vendors and users choose. 
///
/// Named icons are similar to the <A HREF="classXFC_1_1Gtk_1_1IconFactory.html">Themeable
/// Stock Images</A>, and the distinction between the two may be a bit confusing. A few 
/// things to keep in mind: Stock images usually are used in conjunction with stock items,
/// such as Gtk::StockId::OK or Gtk::StockId::OPEN. Named icons are easier to set up and
/// therefore are more useful for new icons that an application wants to add, such as 
/// application icons or window icons. 
///
/// Stock images can only be loaded at the symbolic sizes defined by the Gtk::IconSize 
/// enumeration, or by custom sizes defined by Gtk::icon_size_register(), while named
/// icons are more flexible and any pixel size can be specified. Because stock images are
/// closely tied to stock items, and thus to actions in the user interface, stock images
/// may come in multiple variants for different widget states or writing directions. 
///
/// A good rule of thumb is that if there is a stock image for what you want to use,
/// use it, otherwise use a named icon. It turns out that internally stock images are
/// generally defined in terms of one or more named icons. (An example of the more than
/// one case is icons that depend on writing direction; Gtk::StockId::GO_FORWARD uses the
/// two themed icons "gtk-stock-go-forward-ltr" and "gtk-stock-go-forward-rtl".) 
///
/// In many cases, named themes are used indirectly, via Gtk::Image or stock items, 
/// rather than directly, but looking up icons directly is also simple. The IconTheme
/// object acts as a database of all the icons in the current theme. You can create new
/// IconTheme objects, but its much more efficient to use the standard icon theme for 
/// the Gdk::Screen so that the icon information is shared with other people looking up
/// icons. In the case where the default screen is being used, looking up an icon can be
/// as simple as: 
///
/// @code
/// G::Error error;
/// Gtk::IconTheme *icon_theme = Gtk::IconTheme::get_for_screen();
/// Pointer<Gdk::Pixbuf> pixbuf = icon_theme->load_icon("my-icon-name", 48, 0, &error);
/// 
/// if (!pixbuf)
/// {
/// 	g_warning("Couldn't load icon: %s", error.message());
/// }
/// else
/// {
/// 	// Use the pixbuf
/// }
/// @endcode

class IconTheme : public G::Object
{
	friend class G::Object;

	IconTheme(const IconTheme&);
	IconTheme& operator=(const IconTheme&);

protected:
/// @name Constructors
/// @{

	explicit IconTheme(GtkIconTheme *icon_theme, bool owns_reference = true);
	///< Construct a new IconTheme from an existing GtkIconTheme.
	///< @param icon_theme A pointer to a GtkIconTheme.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>icon_theme</EM> can be a newly created GtkIconTheme or an existing
	///< GtkIconTheme (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkIconTheme CObjectType;

/// @name Constructors
/// @{

	IconTheme();
	///< Constructs a new icon theme object with a reference count of 1 that the caller owns.
	///< Icon theme objects are used to lookup up an icon by name in a particular icon theme
	///< Usually, you'll want to use get_for_screen() rather than creating a new icon theme
	///< object for scratch.
	
	virtual ~IconTheme();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkIconTheme* gtk_icon_theme() const;
	///< Get a pointer to the GtkIconTheme structure.

	operator GtkIconTheme* () const;
	///< Conversion operator; safely converts an IconTheme to a GtkIconTheme pointer.

	std::vector<String> get_search_path() const;
	///< Gets the current search path (see set_search_path()).
	///< @return A list of icon theme path directories. 

	String get_example_icon_name() const;
	///< Gets the name of an icon that is representative of the current theme
	///< (for instance, to use when presenting a list of themes to the user).
	///< @return The name of an example icon or null. 
	
	bool has_icon(const char *icon_name) const;
	bool has_icon(const String& icon_name) const;
	///< Checks whether an icon theme includes an icon for a particular name.
	///< @param icon_name The name of an icon. 
	///< @return <EM>true</EM> if icon theme includes an icon for <EM>icon_name</EM>.

	std::vector<int> get_icon_sizes(const char *icon_name) const;
	std::vector<int> get_icon_sizes(const String& icon_name) const;
	///< Returns a vector of integers describing the sizes at which the icon is available without scaling.
	///< @param icon_name The name of an icon. 
	///< @return A vector of int describing the sizes at which the icon is available.
	///< 	 
	///< A size of -1 means that the icon is available in a scalable format.

/// @}
/// @name Accessors
/// @{

	static IconTheme* get_for_screen(const Gdk::Screen *screen = 0);
	///< Gets the icon theme object associated with <EM>screen</EM>.
	///< @param screen A Gdk::Screen, or null for the default screen.
	///< @return A unique IconTheme associated with the given screen. 
	///<	 
	///< If <EM>screen</EM> is null the icon theme for the default screen 
	///< is returned. The icon theme is associated with the screen and can be
	///< used as long as the screen is open.
	///<
	///< If this method has not previously been called for the given screen, a 
	///< new icon theme object will be created and associated with the screen.
	///< Icon theme objects are fairly expensive to create, so using this method
	///< is usually a better choice than constructing a new icon theme object and
	///< setting the screen yourself. By using this method a single icon theme 
	///< object will be shared between users.

/// @}
/// @name Methods
/// @{

	void set_screen(Gdk::Screen *screen);
	///< Sets the screen for an icon theme.
	///< @param screen A Gdk::Screen. 
	///<	 
	///< The screen is used to track the user's currently configured icon theme,
	///< which might be different for different screens.

	void set_search_path(const std::vector<String>& path);
	///< Sets the search path for the icon theme object. 
	///< @param path A vector of directories that are searched for icon themes. 
	///<	
	///< When looking for an icon theme, GTK+ will search for a subdirectory of 
	///< one or more of the directories in path with the same name as the icon theme.
	///< Note, themes from multiple of the path elements are combined to allow themes
	///< to be extended by adding icons in the user's home directory.
	///<
	///< In addition if an icon found isn't found either in the current icon theme or
	///< the default icon theme, and an image file with the right name is found directly
	///< in one of the elements of path, then that image will be used for the icon name.
	///< (This is legacy feature, and new icons should be put into the default icon theme,
	///< which is called DEFAULT_THEME_NAME, rather than directly on the icon path.)

	void append_search_path(const char *path);
	void append_search_path(const String& path);
	///< Appends a directory to the search path (see set_search_path()).
	///< @param path The directory name to append to the icon path. 

	void prepend_search_path(const char *path);
	void prepend_search_path(const String& path);
	///< Prepends a directory to the search path (see set_search_path()).
	///< @param path The directory name to prepend to the icon path. 

	void set_custom_theme(const char *theme_name);
	void set_custom_theme(const String& theme_name);
	///< Sets the name of the icon theme that the IconTheme object uses, 
	///< overriding system configuration. 
	///< @param theme_name The name of icon theme to use instead of the configured theme.
	///<	
	///< This method cannot be called on the icon theme objects returned
	///< from get_for_screen().

	Pointer<IconInfo> lookup_icon(const char *icon_name, int size, IconLookupFlagsField flags);
	Pointer<IconInfo> lookup_icon(const String& icon_name, int size, IconLookupFlagsField flags);
	///< Looks up a named icon and returns a structure containing information
	///< such as the filename of the icon. 
	///< @param icon_name The name of the icon to lookup. 
	///< @param size The desired icon size. 
	///< @param flags The Gtk::IconLookupFlags modifying the behavior of the icon lookup. 
	///< @return An IconInfo object containing information about the icon, or null if no icon was found.
	///<	
	///< The icon can then be rendered into a pixbuf using Gtk::IconInfo::load_icon(). 
	///< Gtk::IconTheme::load_icon() combines these two steps if all you need is the pixbuf.

	Pointer<Gdk::Pixbuf> load_icon(const char *icon_name, int size, IconLookupFlagsField flags, G::Error *error = 0);
	Pointer<Gdk::Pixbuf> load_icon(const String& icon_name, int size, IconLookupFlagsField flags, G::Error *error = 0);
	///< Looks up an icon in an icon theme, scales it to the given size and renders it into a pixbuf.
	///< @param icon_name The name of the icon to lookup. 
	///< @param size The desired icon size.
	///< @param flags The Gtk::IconLookupFlags modifying the behavior of the icon lookup. 
	///< @param error The location to store error information on failure, or null. 
	///< @returns A smart pointer to the rendered icon, or null if the icon isn't found. 
	///<	
	///< This is a convenience method; if more details about the icon are needed, 
	///< use lookup_icon() followed by Gtk::IconInfo::load_icon(). Note the size of 
	///< the resulting icon may not be exactly the requested size (see load_icon()).
	///<
	///< The rendered icon may be a newly created icon or a new reference to an 
	///< internal icon, so you must not modify the icon.

	std::vector<String> list_icons(const char *context = 0);
	std::vector<String> list_icons(const String& context);
	///< Lists the icons in the current icon theme. 
	///< @return A vector of String holding the names of all the icons in the theme.
	///<	
	///< Only a subset of the icons can be listed by providing a context string.
	///< The set of values for the context string is system dependent, but will 
	///< typically include such values as 'apps' and 'mimetypes'.
	///< @param context A string identifying a particular type of icon, or null to list all icons. 

	bool rescan_if_needed();
	///< Checks to see if the icon theme has changed; if it has, any currently cached information
	///< is discarded and will be reloaded next time the icon theme is accessed.
	///< @return <EM>true</EM> if the icon theme has changed and needed to be reloaded.
	
/// @}
/// @name Methods
/// @{

	static void add_builtin_icon(const char *icon_name, int size, Gdk::Pixbuf& pixbuf);
	static void add_builtin_icon(const String& icon_name, int size, Gdk::Pixbuf& pixbuf);
	///< Registers a built-in icon for icon theme lookups. 
	///< @param icon_name The name of the icon to register. 
	///< @param size The size at which to register the icon. 
	///< @param pixbuf A Gdk::Pixbuf that contains the image to use for <EM>icon_name</EM>. 
	///<	
	///< The idea of built-in icons is to allow an application or library that uses
	///< themed icons to function requiring files to be present in the file system. For
	///< instance, the default images for all of GTK+'s stock icons are registered as
	///< built-in icons.
	///<
	///< In general, if you use add_builtin_icon() you should also install the icon 
	///< in the icon theme, so that the icon is generally available. Note different
	///< images can be registered for the same icon name at different sizes. 
 	///<
	///< This method will generally be used with pixbufs loaded inline (see 
	///< Gdk::Pixbuf::create(int, const unsigned char*, bool, G::Error*));

/// @}
/// @name Signal Proxies
/// @{

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted when the current icon theme is switched or
	///< GTK+ detects that a change has occurred in the contents of the current icon theme.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/icontheme.inl>

#endif // XFC_GTK_ICON_THEME_HH

