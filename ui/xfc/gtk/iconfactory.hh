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

/// @file xfc/gtk/iconfactory.hh
/// @brief A GtkIconFactory C++ wrapper interface.
///
/// Provides IconFactory, an object that manages a collection of IconSets.

#ifndef XFC_GTK_ICON_FACTORY_HH
#define XFC_GTK_ICON_FACTORY_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ICON_SET_HH
#include <xfc/gtk/iconset.hh>
#endif

#ifndef XFC_GTK_STOCK_ID_HH
#include <xfc/gtk/stockid.hh>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

class Settings;

/// @name Icon Size Methods
/// @{

bool icon_size_lookup(IconSize size, int *width, int *height, Settings *settings = 0);
///< Obtains the pixel size of a semantic icon size, possibly modified by user preferences
///< for a particular Settings.
///< @param size An icon size.
///< @param width The location to store icon width.
///< @param height The location to store icon height.
///< @param settings A Settings object, used to determine which set of user preferences
///<                 to use, or null to use the settings for the default screen.
///< @return <EM>true</EM> if size was a valid size.
///<
///< Normally size would be ICON_SIZE_MENU, ICON_SIZE_BUTTON, etc. This method isn't
///< normally needed, Gtk::Widget::render_icon() is the usual way to get an icon for
///< rendering, then just look at the size of the rendered pixbuf. The rendered pixbuf
///< may not even correspond to the width/height returned by size_lookup(), because themes
///< are free to render the pixbuf however they like, including changing the usual size.
///<
///< <B>Note:</B> The default GDK screen is the only screen in the absence of MultiHead support.

IconSize icon_size_register(const char *name, int width, int height);
IconSize icon_size_register(const String& name, int width, int height);
///< Registers a new icon size, along the same lines as ICON_SIZE_MENU, etc.
///< @param name The name of the icon size.
///< @param width The icon width.
///< @param height The icon height.
///< @return The integer value for the size, as an IconSize.

void icon_size_register_alias(const char *alias, IconSize target);
void icon_size_register_alias(const String& alias, IconSize target);
///< Registers <EM>alias</EM> as another name for <EM>target</EM>.
///< @param alias An alias for target.
///< @param target An existing icon size.
///<
///< Calling size_from_name() with <EM>alias</EM> as the argument will return <EM>target</EM>.

IconSize icon_size_from_name(const char *name);
IconSize icon_size_from_name(const String& name);
///< Looks up the icon size associated with <EM>name</EM>.
///< @param name The name to look up.
///< @return The icon size with the given name.

String icon_size_get_name(IconSize size);
///< Gets the canonical name of the given icon size.
///< @param size An IconSize.
///< @return The name of the given icon size.

/// @}

/// @class IconFactory iconfactory.hh xfc/gtk/iconfactory.hh
/// @brief A GtkIconFactory C++ wrapper class.
///
/// An icon factory manages a collection of IconSets; an IconSet manages a set of variants
/// of a particular icon (i.e. a IconSet contains variants for different sizes and widget
/// states). Icons in an icon factory are named by a stock ID, which is a simple string
/// identifying the icon. Each Style has a list of IconFactorys derived from the current
/// theme; those icon factories are consulted first when searching for an icon. If the
/// theme doesn't set a particular icon, GTK+ looks for the icon in a list of default icon
/// factories, maintained by IconFactory's add_default() and remove_default() methods.
/// Applications with icons should add a default icon factory with their icons, which will
/// allow themes to override the icons for the application (see application.cc in the
/// gfc-demo demo program).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class IconFactory : public G::Object
{
	friend class G::Object;

	IconFactory(const IconFactory&);
	IconFactory& operator=(const IconFactory&);
	
protected:
/// @name Constructors
/// @{

	explicit IconFactory(GtkIconFactory *icon_factory, bool owns_reference = true);
	///< Construct a new IconFactory from an existing GtkIconFactory.
	///< @param icon_factory A pointer to a GtkIconFactory.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>icon_factory</EM> can be a newly created GtkIconFactory or an existing
	///< GtkIconFactory (see G::Object::Object).

/// @}
	
public:
	typedef GtkIconFactory CObjectType;

/// @name Constructors
/// @{

	IconFactory();
	///< Construct a new IconFactory with a reference count of 1 that the caller owns.
	
	virtual ~IconFactory();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkIconFactory* gtk_icon_factory() const;
	///< Get a pointer to the GtkIconFactory structure.

	operator GtkIconFactory* () const;
	///< Conversion operator; safely converts an IconFactory to a GtkIconFactory pointer.

/// @}
/// @name Methods
/// @{

	void add(const StockId& stock_id, IconSet& icon_set);
	///< Adds the given icon_set to the icon factory, under the name stock_id.
	///< @param stock_id The stock icon identifier.
	///< @param icon_set The icon set.
	///<
	///< The <EM>stock_id</EM> should be namespaced for your application, e.g.
	///< "myapp-whatever-icon". Normally applications create an IconFactory, then
	///< add it to the list of default factories with add_default(). Then they pass
	///< the stock_id to widgets such as Image to display the icon. Themes can
	///< provide an icon with the same name (such as "myapp-whatever-icon") to 
	///< override your application's default icons. If an icon already existed in
	///< factory for stock_id, it is unreferenced and replaced with the new icon_set.

	Pointer<IconSet> lookup(const StockId& stock_id);
	///< Looks up <EM>stock_id</EM> in the icon factory, returning an icon set
	///< if found, otherwise null. 
	///< @param stock_id The stock icon identifier.
	///< @return The icon set of stock_id.
	///<
	///< For display to the user, use Gtk::Style::lookup_icon_set() for the widget that
	///< will display the icon instead of using this method directly, so that themes are
	///< taken into account.
	
	void add_default();
	///< Adds the IconFactory to the list of icon factories searched by Gtk::Style::lookup_icon_set().
	///< This means that, for example, a stock Image widget will be able to find icons in  an icon
	///< factory. There will normally be an icon factory added for each library or application that
	///< comes with icons. The default icon factories can be overridden by themes.

	void remove_default();
	///< Removes the IconFactory from the list of default icon factories. 

/// @}
/// @name Methods
/// @{
	
	static Pointer<IconSet> lookup_default(const StockId& stock_id);
	///< Looks for an icon set in the list of default icon factories.
	///< @param stock_id The stock icon identifier.
	///< @return The icon set of stock_id.
	///<
	///< For display to the user, use Gtk::Style::lookup_icon_set() for the widget that
	///< will display the icon instead of using this method directly, so that themes are
	///< taken into account.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/iconfactory.inl>

#endif // XFC_GTK_ICON_FACTORY_HH

