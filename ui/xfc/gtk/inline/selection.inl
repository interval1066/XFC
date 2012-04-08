/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  selection.inl - Gtk::SelectionData, Gtk::TargetEntry and Gtk::TargetList inline functions
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

/*  Gtk::SelectionData
 */

inline GtkSelectionData*
Xfc::Gtk::SelectionData::gtk_selection_data() const
{
	return reinterpret_cast<GtkSelectionData*>(boxed_);
}

inline bool
Xfc::Gtk::SelectionData::is_valid() const
{
	return gtk_selection_data()->length >= 0;
}

inline Xfc::Gdk::Atom
Xfc::Gtk::SelectionData::selection() const
{
	return gtk_selection_data()->selection;
}

inline Xfc::Gdk::Atom
Xfc::Gtk::SelectionData::target() const
{
	return gtk_selection_data()->target;
}

inline Xfc::Gdk::Atom
Xfc::Gtk::SelectionData::type() const
{
	return gtk_selection_data()->type;
}

inline int
Xfc::Gtk::SelectionData::format() const
{
	return gtk_selection_data()->format;
}

inline unsigned char*
Xfc::Gtk::SelectionData::data() const
{
	return gtk_selection_data()->data;
}

inline int
Xfc::Gtk::SelectionData::length() const
{
	return gtk_selection_data()->length;
}

inline void
Xfc::Gtk::SelectionData::set(Gdk::Atom type, int format, const void *data, int length)
{
	gtk_selection_data_set(gtk_selection_data(), type, format, static_cast<const guchar*>(data), length);
}

inline bool
Xfc::Gtk::SelectionData::set_text(const char *str)
{
	return gtk_selection_data_set_text(gtk_selection_data(), str, -1);
}

inline bool
Xfc::Gtk::SelectionData::targets_include_text() const
{
	return gtk_selection_data_targets_include_text(gtk_selection_data());
}

inline bool 
Xfc::Gtk::SelectionData::targets_include_image(bool writable) const
{
	return gtk_selection_data_targets_include_image(gtk_selection_data(), writable);
}

/*  Gtk::TargetEntry
 */

inline GtkTargetEntry*
Xfc::Gtk::TargetEntry::gtk_target_entry() const
{
	return const_cast<GtkTargetEntry*>(&entry_);
}

inline const char*
Xfc::Gtk::TargetEntry::target() const
{
	return entry_.target;
}

inline unsigned int
Xfc::Gtk::TargetEntry::flags() const
{
	return entry_.flags;
}

inline unsigned int
Xfc::Gtk::TargetEntry::info() const
{
	return entry_.info;
}

/*  Gtk::TargetList
 */

inline GtkTargetList*
Xfc::Gtk::TargetList::gtk_target_list() const
{
	return target_list_;
}

inline Xfc::Gtk::TargetList::operator GtkTargetList* () const
{
	return this ? target_list_ : 0;
}

inline void 
Xfc::Gtk::TargetList::add_text_targets(unsigned int info)
{
	gtk_target_list_add_text_targets(gtk_target_list(), info);
}

inline void 
Xfc::Gtk::TargetList::add_image_targets(unsigned int info, bool writable)
{
	gtk_target_list_add_image_targets(gtk_target_list(), info, writable);
}

inline void 
Xfc::Gtk::TargetList::add_uri_targets(unsigned int info)
{
	gtk_target_list_add_uri_targets(gtk_target_list(), info);
}
	
inline void
Xfc::Gtk::TargetList::remove(Gdk::Atom target)
{
	gtk_target_list_remove(target_list_, target);
}

inline bool
Xfc::Gtk::TargetList::find(Gdk::Atom target, unsigned int *info)
{
	return gtk_target_list_find(target_list_, target, info);
}

