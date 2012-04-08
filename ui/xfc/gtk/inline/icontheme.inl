/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  icontheme.inl - Gtk::IconTheme inline functions
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

/*  Gtk::IconInfo
 */

inline GtkIconInfo*
Xfc::Gtk::IconInfo::gtk_icon_info() const
{
	return reinterpret_cast<GtkIconInfo*>(boxed_);
}

inline Xfc::Gtk::IconInfo::operator GtkIconInfo* () const
{
	return this ? gtk_icon_info() : 0;
}

inline int 
Xfc::Gtk::IconInfo::get_base_size() const
{
	return gtk_icon_info_get_base_size(gtk_icon_info());
}

inline bool
Xfc::Gtk::IconInfo::has_attach_points() const
{
	return gtk_icon_info_get_attach_points(gtk_icon_info(), 0, 0);
}

/*  Gtk::IconTheme
 */

inline GtkIconTheme*
Xfc::Gtk::IconTheme::gtk_icon_theme() const
{
	return reinterpret_cast<GtkIconTheme*>(instance_);
}

inline Xfc::Gtk::IconTheme::operator GtkIconTheme* () const
{
	return this ? gtk_icon_theme() : 0;
}

inline bool 
Xfc::Gtk::IconTheme::has_icon(const char *icon_name) const
{
	return gtk_icon_theme_has_icon(gtk_icon_theme(), icon_name);
}

inline void 
Xfc::Gtk::IconTheme::append_search_path(const char *path)
{
	gtk_icon_theme_append_search_path(gtk_icon_theme(), path);
}
	
inline void 
Xfc::Gtk::IconTheme::prepend_search_path(const char *path)
{
	gtk_icon_theme_prepend_search_path(gtk_icon_theme(), path);
}

inline void 
Xfc::Gtk::IconTheme::set_custom_theme(const char *theme_name)
{
	gtk_icon_theme_set_custom_theme(gtk_icon_theme(), theme_name);
}

inline bool
Xfc::Gtk::IconTheme::rescan_if_needed() 
{
	return gtk_icon_theme_rescan_if_needed(gtk_icon_theme());
}

inline const Xfc::Gtk::IconTheme::ChangedSignalProxy
Xfc::Gtk::IconTheme::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

