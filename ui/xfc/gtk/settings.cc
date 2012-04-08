/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  settings.cc - GtkSettings C++ wrapper implementation
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
 
#include <gtk/gtktypeutils.h>
#include "settings.hh"
#include "../gdk/screen.hh"

using namespace Xfc;

Gtk::Settings::Settings(GtkSettings *settings, bool owns_reference)
: G::Object((GObject*)settings, owns_reference)
{
}
	
Gtk::Settings::~Settings()
{
}
	
Gtk::Settings*
Gtk::Settings::get(const Gdk::Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return G::Object::wrap<Settings>(gtk_settings_get_for_screen(tmp_screen));
}

/*  Properties
 */

const Gtk::Settings::GtkDoubleClickTimePropertyType Gtk::Settings::gtk_double_click_time_property("gtk-double-click-time");

const Gtk::Settings::GtkDoubleClickDistancePropertyType Gtk::Settings::gtk_double_click_distance_property("gtk-double-click-distance");

const Gtk::Settings::GtkCursorBlinkPropertyType Gtk::Settings::gtk_cursor_blink_property("gtk-cursor-blink");

const Gtk::Settings::GtkCursorBlinkTimePropertyType Gtk::Settings::gtk_cursor_blink_time_property("gtk-cursor-blink-time");

const Gtk::Settings::GtkSplitCursorPropertyType Gtk::Settings::gtk_split_cursor_property("gtk-split-cursor");

const Gtk::Settings::GtkThemeNamePropertyType Gtk::Settings::gtk_theme_name_property("gtk-theme-name");

const Gtk::Settings::GtkIconThemeNamePropertyType Gtk::Settings::gtk_icon_theme_name_property("gtk-icon-theme-name");

const Gtk::Settings::GtkKeyThemeNamePropertyType Gtk::Settings::gtk_key_theme_name_property("gtk-key-theme-name");

const Gtk::Settings::GtkMenuBarAccelPropertyType Gtk::Settings::gtk_menu_bar_accel_property("gtk-menu-bar-accel");

const Gtk::Settings::GtkDndDragThresholdPropertyType Gtk::Settings::gtk_dnd_drag_threshold_property("gtk-dnd-drag-threshold");

const Gtk::Settings::GtkFontNamePropertyType Gtk::Settings::gtk_font_name_property("gtk-font-name");

const Gtk::Settings::GtkIconSizesPropertyType Gtk::Settings::gtk_icon_sizes_property("gtk-icon-sizes");

const Gtk::Settings::GtkModulesPropertyType Gtk::Settings::gtk_modules_property("gtk-modules");

const Gtk::Settings::GtkXftAntialiasPropertyType Gtk::Settings::gtk_xft_antialias_property("gtk-xft-antialias");

const Gtk::Settings::GtkXftHintingPropertyType Gtk::Settings::gtk_xft_hinting_property("gtk-xft-hinting");

const Gtk::Settings::GtkXftHintStylePropertyType Gtk::Settings::gtk_xft_hintstyle_property("gtk-xft-hintstyle");

const Gtk::Settings::GtkXftRGBAPropertyType Gtk::Settings::gtk_xft_rgba_property("gtk-xft-rgba");

const Gtk::Settings::GtkXftDPIPropertyType Gtk::Settings::gtk_xft_dpi_property("gtk-xft-dpi");

const Gtk::Settings::GtkAlternativeButtonOrderPropertyType Gtk::Settings::gtk_alternative_button_order_property("gtk-alternative-button-order");

