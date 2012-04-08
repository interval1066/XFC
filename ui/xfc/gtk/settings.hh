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
 
/// @file xfc/gtk/settings.hh
/// @brief A GtkSettings C++ wrapper interface.
///
/// Provides Settings, an object that holds the current settings for a screen.

#ifndef XFC_GTK_SETTINGS_HH
#define XFC_GTK_SETTINGS_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_SETTINGS_H__
#include <gtk/gtksettings.h>
#endif

namespace Xfc {

namespace Gdk {
class Screen;
}

namespace Gtk {

/// @class Settings settings.hh xfc/gtk/settings.hh
/// @brief A GtkSettings C++ wrapper class.
///
/// The Settings object holds the current settings for a GDK screen.

class Settings : public G::Object
{
	friend class G::Object;

	Settings(const Settings&);
	Settings& operator=(const Settings&);
	
protected:
/// @name Constructors
/// @{

	explicit Settings(GtkSettings *settings, bool owns_reference = true);
	///< Construct a new Settings from an existing GtkSettings.
	///< @param settings A pointer to a GtkSettings.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>settings</EM> can be a newly created GtkSettings or an existing
	///< GtkSettings (see G::Object::Object).

/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<int> GtkDoubleClickTimePropertyType;
	typedef G::PropertyProxy<G::Object, GtkDoubleClickTimePropertyType> GtkDoubleClickTimePropertyProxy;
	static const GtkDoubleClickTimePropertyType gtk_double_click_time_property;
	///< Maximum time allowed between two clicks for them to be considered a double click
	///< (see property_gtk_double_click_time()).

	typedef G::Property<int> GtkDoubleClickDistancePropertyType;
	typedef G::PropertyProxy<G::Object, GtkDoubleClickDistancePropertyType> GtkDoubleClickDistancePropertyProxy;
	static const GtkDoubleClickDistancePropertyType gtk_double_click_distance_property;
	///< Maximum distance allowed between two clicks for them to be considered a double click
	///< (see property_gtk_double_click_distance()).
	
	typedef G::Property<bool> GtkCursorBlinkPropertyType;
	typedef G::PropertyProxy<G::Object, GtkCursorBlinkPropertyType> GtkCursorBlinkPropertyProxy;
	static const GtkCursorBlinkPropertyType gtk_cursor_blink_property;
	///< Whether the cursor should blink (see property_gtk_cursor_blink()).

	typedef G::Property<int> GtkCursorBlinkTimePropertyType;
	typedef G::PropertyProxy<G::Object, GtkCursorBlinkTimePropertyType> GtkCursorBlinkTimePropertyProxy;
	static const GtkCursorBlinkTimePropertyType gtk_cursor_blink_time_property;
	///< Length of the cursor blink cycle, in milleseconds (see property_gtk_cursor_blink_time()).

	typedef G::Property<bool> GtkSplitCursorPropertyType;
	typedef G::PropertyProxy<G::Object, GtkSplitCursorPropertyType> GtkSplitCursorPropertyProxy;
	static const GtkSplitCursorPropertyType gtk_split_cursor_property;
	///< Whether two cursors should be displayed for mixed left-to-right and right-to-left text
	///< (see property_gtk_split_cursor()).

	typedef G::Property<String> GtkThemeNamePropertyType;
	typedef G::PropertyProxy<G::Object, GtkThemeNamePropertyType> GtkThemeNamePropertyProxy;
	static const GtkThemeNamePropertyType gtk_theme_name_property;
	///< Name of theme RC file to load (see property_gtk_theme_name()).

	typedef G::Property<String> GtkIconThemeNamePropertyType;
	typedef G::PropertyProxy<G::Object, GtkIconThemeNamePropertyType> GtkIconThemeNamePropertyProxy;
	static const GtkIconThemeNamePropertyType gtk_icon_theme_name_property;
	///< Name of icon theme to use (see property_gtk_icon_theme_name()).

	typedef G::Property<String> GtkKeyThemeNamePropertyType;
	typedef G::PropertyProxy<G::Object, GtkKeyThemeNamePropertyType> GtkKeyThemeNamePropertyProxy;
	static const GtkKeyThemeNamePropertyType gtk_key_theme_name_property;
	///< Name of key theme RC file to load (see property_gtk_key_theme_name()).

	typedef G::Property<String> GtkMenuBarAccelPropertyType;
	typedef G::PropertyProxy<G::Object, GtkMenuBarAccelPropertyType> GtkMenuBarAccelPropertyProxy;
	static const GtkMenuBarAccelPropertyType gtk_menu_bar_accel_property;
	///< Keybinding to activate the menu bar (see property_gtk_menu_bar_accel()).

	typedef G::Property<int> GtkDndDragThresholdPropertyType;
	typedef G::PropertyProxy<G::Object, GtkDndDragThresholdPropertyType> GtkDndDragThresholdPropertyProxy;
	static const GtkDndDragThresholdPropertyType gtk_dnd_drag_threshold_property;
	///< Number of pixels the cursor can move before dragging (see property_gtk_dnd_drag_threshold()).

	typedef G::Property<String> GtkFontNamePropertyType;
	typedef G::PropertyProxy<G::Object, GtkFontNamePropertyType> GtkFontNamePropertyProxy;
	static const GtkFontNamePropertyType gtk_font_name_property;
	///< Name of default font to use (see property_gtk_font_name()).

	typedef G::Property<String> GtkIconSizesPropertyType;
	typedef G::PropertyProxy<G::Object, GtkIconSizesPropertyType> GtkIconSizesPropertyProxy;
	static const GtkIconSizesPropertyType gtk_icon_sizes_property;
	///< List of icon sizes (gtk-menu=16,16;gtk-button=20,20...) (see property_gtk_icon_sizes()).

	typedef G::Property<String> GtkModulesPropertyType;
	typedef G::PropertyProxy<G::Object, GtkModulesPropertyType> GtkModulesPropertyProxy;
	static const GtkModulesPropertyType gtk_modules_property;
	///< List of currently active GTK modules (see property_gtk_modules()).

	typedef G::Property<int> GtkXftAntialiasPropertyType;
	typedef G::PropertyProxy<G::Object, GtkXftAntialiasPropertyType> GtkXftAntialiasPropertyProxy;
	static const GtkXftAntialiasPropertyType gtk_xft_antialias_property;
	///< Whether to antialias Xft fonts; 0=no, 1=yes, -1=default (see property_gtk_xft_antialias()).

	typedef G::Property<int> GtkXftHintingPropertyType;
	typedef G::PropertyProxy<G::Object, GtkXftHintingPropertyType> GtkXftHintingPropertyProxy;
	static const GtkXftHintingPropertyType gtk_xft_hinting_property;
	///< Whether to hint Xft fonts; 0=no, 1=yes, -1=default (see property_gtk_xft_hinting()).

	typedef G::Property<String> GtkXftHintStylePropertyType;
	typedef G::PropertyProxy<G::Object, GtkXftHintStylePropertyType> GtkXftHintStylePropertyProxy;
	static const GtkXftHintStylePropertyType gtk_xft_hintstyle_property;
	///< What degree of hinting to use; none, slight, medium, or full (see property_gtk_xft_hintstyle()).

	typedef G::Property<String> GtkXftRGBAPropertyType;
	typedef G::PropertyProxy<G::Object, GtkXftRGBAPropertyType> GtkXftRGBAPropertyProxy;
	static const GtkXftRGBAPropertyType gtk_xft_rgba_property;
	///< Type of subpixel antialiasing; none, rgb, bgr, vrgb, vbgr (see property_gtk_xft_rgba()).

	typedef G::Property<int> GtkXftDPIPropertyType;
	typedef G::PropertyProxy<G::Object, GtkXftDPIPropertyType> GtkXftDPIPropertyProxy;
	static const GtkXftDPIPropertyType gtk_xft_dpi_property;
	///< Resolution for Xft, in 1024 * dots/inch. -1 to use default value (see property_gtk_xft_dpi()).

	typedef G::Property<bool> GtkAlternativeButtonOrderPropertyType;
	typedef G::PropertyProxy<G::Object, GtkAlternativeButtonOrderPropertyType> GtkAlternativeButtonOrderPropertyProxy;
	static const GtkAlternativeButtonOrderPropertyType gtk_alternative_button_order_property;
	///< Whether buttons in dialogs should use the alternative button order (see property_gtk_alternative_button_order()).

/// @}

public:
	typedef GtkSettings CObjectType;

/// @name Constructors
/// @{

	virtual ~Settings();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkSettings* gtk_settings() const;
	///< Get a pointer to the GtkSettings structure.

	operator GtkSettings* () const;
	///< Conversion operator; safely converts a Settings to a GtkSettings pointer.

/// @}
/// @name Accessors
/// @{

	static Settings* get(const Gdk::Screen *screen = 0);
	///< Gets the Settings object for the specified screen, creating it if necessary.
	///< @param screen A Gdk::Screen, or null for the default screen.
	///< @return A Settings object.
	///<
	///< <B>Note:</B> The default GDK screen is the only screen in the absence of MultiHead support.

/// @}
/// @name Property Proxies
/// @{

	const GtkDoubleClickTimePropertyProxy property_gtk_double_click_time();
	///< Maximum time allowed between two clicks for them to be considered a double click,
	///< in milliseconds (int : Read / Write).

	const GtkDoubleClickDistancePropertyProxy property_gtk_double_click_distance();
	///< Maximum distance allowed between two clicks for them to be considered a double click,
	///< in pixels (int : Read / Write).
	
	const GtkCursorBlinkPropertyProxy property_gtk_cursor_blink();
	///< Whether the cursor should blink (bool : Read / Write).

	const GtkCursorBlinkTimePropertyProxy property_gtk_cursor_blink_time();
	///< Length of the cursor blink cycle, in milleseconds (int : Read / Write).

	const GtkSplitCursorPropertyProxy property_gtk_split_cursor();
	///< Whether two cursors should be displayed for mixed left-to-right and right-to-left text
	///< (bool : Read / Write).

	const GtkThemeNamePropertyProxy property_gtk_theme_name();
	///< Name of theme RC file to load (String : Read / Write).

	const GtkIconThemeNamePropertyProxy property_gtk_icon_theme_name();
	///< Name of icon theme to use (String : Read / Write).

	const GtkKeyThemeNamePropertyProxy property_gtk_key_theme_name();
	///< Name of key theme RC file to load (String : Read / Write).

	const GtkMenuBarAccelPropertyProxy property_gtk_menu_bar_accel();
	///< Keybinding to activate the menu bar (String : Read / Write).

	const GtkDndDragThresholdPropertyProxy property_gtk_dnd_drag_threshold();
	///< Number of pixels the cursor can move before dragging (int : Read / Write).

	const GtkFontNamePropertyProxy property_gtk_font_name();
	///< Name of default font to use (String : Read / Write).

	const GtkIconSizesPropertyProxy property_gtk_icon_sizes();
	///< List of icon sizes (gtk-menu=16,16;gtk-button=20,20...) (String : Read / Write).

	const GtkModulesPropertyProxy property_gtk_modules();
	///< List of currently active GTK modules (String : Read / Write).

	const GtkXftAntialiasPropertyProxy property_gtk_xft_antialias();
	///< Whether to antialias Xft fonts; 0=no, 1=yes, -1=default (int : Read / Write).

	const GtkXftHintingPropertyProxy property_gtk_xft_hinting();
	///< Whether to hint Xft fonts; 0=no, 1=yes, -1=default (int : Read / Write).
	
	const GtkXftHintStylePropertyProxy property_gtk_xft_hintstyle();
	///< What degree of hinting to use; none, slight, medium, or full (String : Read / Write).

	const GtkXftRGBAPropertyProxy property_gtk_xft_rgba();
	///< Type of subpixel antialiasing; none, rgb, bgr, vrgb, vbgr (String : Read / Write).

	const GtkXftDPIPropertyProxy property_gtk_xft_dpi();
	///< Resolution for Xft, in 1024 * dots/inch. -1 to use default value (int : Read / Write).

	const GtkAlternativeButtonOrderPropertyProxy property_gtk_alternative_button_order();
	///< Whether buttons in dialogs should use the alternative button order (bool : Read / Write).

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/settings.inl>

#endif // XFC_GTK_SETTINGS_HH

