/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  settings.inl - Gtk::Settings inline functions
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

inline GtkSettings*
Xfc::Gtk::Settings::gtk_settings() const
{
	return reinterpret_cast<GtkSettings*>(instance_);
}

inline Xfc::Gtk::Settings::operator GtkSettings* () const
{
	return this ? gtk_settings() : 0;
}

inline const Xfc::Gtk::Settings::GtkDoubleClickTimePropertyProxy
Xfc::Gtk::Settings::property_gtk_double_click_time()
{
	return GtkDoubleClickTimePropertyProxy(this, &gtk_double_click_time_property);
}

inline const Xfc::Gtk::Settings::GtkDoubleClickDistancePropertyProxy
Xfc::Gtk::Settings::property_gtk_double_click_distance()
{
	return GtkDoubleClickDistancePropertyProxy(this, &gtk_double_click_distance_property);
}

inline const Xfc::Gtk::Settings::GtkCursorBlinkPropertyProxy
Xfc::Gtk::Settings::property_gtk_cursor_blink()
{
	return GtkCursorBlinkPropertyProxy(this, &gtk_cursor_blink_property);
}

inline const Xfc::Gtk::Settings::GtkCursorBlinkTimePropertyProxy
Xfc::Gtk::Settings::property_gtk_cursor_blink_time()
{
	return GtkCursorBlinkTimePropertyProxy(this, &gtk_cursor_blink_time_property);
}

inline const Xfc::Gtk::Settings::GtkSplitCursorPropertyProxy
Xfc::Gtk::Settings::property_gtk_split_cursor()
{
	return GtkSplitCursorPropertyProxy(this, &gtk_split_cursor_property);
}

inline const Xfc::Gtk::Settings::GtkThemeNamePropertyProxy
Xfc::Gtk::Settings::property_gtk_theme_name()
{
	return GtkThemeNamePropertyProxy(this, &gtk_theme_name_property);
}

inline const Xfc::Gtk::Settings::GtkIconThemeNamePropertyProxy
Xfc::Gtk::Settings::property_gtk_icon_theme_name()
{
	return GtkIconThemeNamePropertyProxy(this, &gtk_icon_theme_name_property);
}

inline const Xfc::Gtk::Settings::GtkKeyThemeNamePropertyProxy
Xfc::Gtk::Settings::property_gtk_key_theme_name()
{
	return GtkKeyThemeNamePropertyProxy(this, &gtk_key_theme_name_property);
}

inline const Xfc::Gtk::Settings::GtkMenuBarAccelPropertyProxy
Xfc::Gtk::Settings::property_gtk_menu_bar_accel()
{
	return GtkMenuBarAccelPropertyProxy(this, &gtk_menu_bar_accel_property);
}

inline const Xfc::Gtk::Settings::GtkDndDragThresholdPropertyProxy
Xfc::Gtk::Settings::property_gtk_dnd_drag_threshold()
{
	return GtkDndDragThresholdPropertyProxy(this, &gtk_dnd_drag_threshold_property);
}

inline const Xfc::Gtk::Settings::GtkFontNamePropertyProxy
Xfc::Gtk::Settings::property_gtk_font_name()
{
	return GtkFontNamePropertyProxy(this, &gtk_font_name_property);
}

inline const Xfc::Gtk::Settings::GtkIconSizesPropertyProxy
Xfc::Gtk::Settings::property_gtk_icon_sizes()
{
	return GtkIconSizesPropertyProxy(this, &gtk_icon_sizes_property);
}

inline const Xfc::Gtk::Settings::GtkModulesPropertyProxy
Xfc::Gtk::Settings::property_gtk_modules()
{
	return GtkModulesPropertyProxy(this, &gtk_modules_property);
}

inline const Xfc::Gtk::Settings::GtkXftAntialiasPropertyProxy
Xfc::Gtk::Settings::property_gtk_xft_antialias()
{
	return GtkXftAntialiasPropertyProxy(this, &gtk_xft_antialias_property);
}

inline const Xfc::Gtk::Settings::GtkXftHintingPropertyProxy
Xfc::Gtk::Settings::property_gtk_xft_hinting()
{
	return GtkXftHintingPropertyProxy(this, &gtk_xft_hinting_property);
}

inline const Xfc::Gtk::Settings::GtkXftHintStylePropertyProxy
Xfc::Gtk::Settings::property_gtk_xft_hintstyle()
{
	return GtkXftHintStylePropertyProxy(this, &gtk_xft_hintstyle_property);
}

inline const Xfc::Gtk::Settings::GtkXftRGBAPropertyProxy
Xfc::Gtk::Settings::property_gtk_xft_rgba()
{
	return GtkXftRGBAPropertyProxy(this, &gtk_xft_rgba_property);
}

inline const Xfc::Gtk::Settings::GtkXftDPIPropertyProxy
Xfc::Gtk::Settings::property_gtk_xft_dpi()
{
	return GtkXftDPIPropertyProxy(this, &gtk_xft_dpi_property);
}

inline const Xfc::Gtk::Settings::GtkAlternativeButtonOrderPropertyProxy
Xfc::Gtk::Settings::property_gtk_alternative_button_order()
{
	return GtkAlternativeButtonOrderPropertyProxy(this, &gtk_alternative_button_order_property);
}

