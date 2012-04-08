/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  iconsource.inl - Gtk::IconSource inline functions
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

inline GtkIconSource*
Xfc::Gtk::IconSource::gtk_icon_source() const
{
	return reinterpret_cast<GtkIconSource*>(boxed_);
}

inline Xfc::Gtk::IconSource::operator GtkIconSource* () const
{
	return this ? gtk_icon_source() : 0;
}

inline bool
Xfc::Gtk::IconSource::get_size_wildcarded() const
{
	return gtk_icon_source_get_size_wildcarded(gtk_icon_source());
}

inline bool
Xfc::Gtk::IconSource::get_state_wildcarded() const
{
	return gtk_icon_source_get_state_wildcarded(gtk_icon_source());
}

inline bool
Xfc::Gtk::IconSource::get_direction_wildcarded() const
{
	return gtk_icon_source_get_direction_wildcarded(gtk_icon_source());
}

inline Xfc::Gtk::TextDirection
Xfc::Gtk::IconSource::get_direction() const
{
	return (TextDirection)gtk_icon_source_get_direction(gtk_icon_source());
}

inline Xfc::Gtk::StateType
Xfc::Gtk::IconSource::get_state() const
{
	return (StateType)gtk_icon_source_get_state(gtk_icon_source());
}

inline Xfc::Gtk::IconSize
Xfc::Gtk::IconSource::get_size() const
{
	return (IconSize)gtk_icon_source_get_size(gtk_icon_source());
}

inline void
Xfc::Gtk::IconSource::set_filename(const char *filename)
{
	gtk_icon_source_set_filename(gtk_icon_source(), filename);
}

inline void
Xfc::Gtk::IconSource::set_icon_name(const char *icon_name)
{
	gtk_icon_source_set_icon_name(gtk_icon_source(), icon_name);
}

inline void
Xfc::Gtk::IconSource::set_direction_wildcarded(bool setting)
{
	gtk_icon_source_set_direction_wildcarded(gtk_icon_source(), setting);
}

inline void
Xfc::Gtk::IconSource::set_state_wildcarded(bool setting)
{
	gtk_icon_source_set_state_wildcarded(gtk_icon_source(), setting);
}

inline void
Xfc::Gtk::IconSource::set_size_wildcarded(bool setting)
{
	gtk_icon_source_set_size_wildcarded(gtk_icon_source(), setting);
}

inline void
Xfc::Gtk::IconSource::set_direction(TextDirection direction)
{
	gtk_icon_source_set_direction(gtk_icon_source(), (GtkTextDirection)direction);
}

inline void
Xfc::Gtk::IconSource::set_state(StateType state)
{
	gtk_icon_source_set_state(gtk_icon_source(), (GtkStateType)state);
}

inline void
Xfc::Gtk::IconSource::set_size(IconSize size)
{
	gtk_icon_source_set_size(gtk_icon_source(), (GtkIconSize)size);
}

