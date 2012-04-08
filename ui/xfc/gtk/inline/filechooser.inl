/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filechooser.inl - Gtk::FileChooser inline functions
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

inline GtkFileChooser*
Xfc::Gtk::FileChooser::gtk_file_chooser() const
{
	return reinterpret_cast<GtkFileChooser*>(instance_);
}

inline Xfc::Gtk::FileChooser::operator GtkFileChooser* () const
{
	return this ? gtk_file_chooser() : 0;
}

inline Xfc::Gtk::FileChooserAction 
Xfc::Gtk::FileChooser::get_action() const
{
	return (FileChooserAction)gtk_file_chooser_get_action(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::get_local_only() const
{
	return gtk_file_chooser_get_local_only(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::get_select_multiple() const
{
	return gtk_file_chooser_get_select_multiple(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::get_show_hidden() const
{
	return gtk_file_chooser_get_show_hidden(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::get_preview_widget_active() const
{
	return gtk_file_chooser_get_preview_widget_active(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::get_use_preview_label() const
{
	return gtk_file_chooser_get_use_preview_label(gtk_file_chooser());
}

inline void 
Xfc::Gtk::FileChooser::set_action(FileChooserAction action)
{
	gtk_file_chooser_set_action(gtk_file_chooser(), (GtkFileChooserAction)action);
}
	 
inline void 
Xfc::Gtk::FileChooser::set_local_only(bool local_only)
{
	gtk_file_chooser_set_local_only(gtk_file_chooser(), local_only);
}

inline void 
Xfc::Gtk::FileChooser::set_select_multiple(bool select_multiple)
{
	gtk_file_chooser_set_select_multiple(gtk_file_chooser(), select_multiple);
}
		
inline void 
Xfc::Gtk::FileChooser::set_show_hidden(bool show_hidden)
{
	gtk_file_chooser_set_show_hidden(gtk_file_chooser(), show_hidden);
}

inline void 
Xfc::Gtk::FileChooser::set_current_name(const char *name)
{
	gtk_file_chooser_set_current_name(gtk_file_chooser(), name);
}

inline bool 
Xfc::Gtk::FileChooser::set_filename(const char *filename)
{
	return gtk_file_chooser_set_filename(gtk_file_chooser(), filename);
}

inline bool 
Xfc::Gtk::FileChooser::select_filename(const char *filename)
{
	return gtk_file_chooser_select_filename(gtk_file_chooser(), filename);
}

inline void 
Xfc::Gtk::FileChooser::unselect_filename(const char *filename)
{
	gtk_file_chooser_unselect_filename(gtk_file_chooser(), filename);
}

inline void 
Xfc::Gtk::FileChooser::select_all()
{
	gtk_file_chooser_select_all(gtk_file_chooser());
}

inline void 
Xfc::Gtk::FileChooser::unselect_all()
{
	gtk_file_chooser_unselect_all(gtk_file_chooser());
}

inline bool 
Xfc::Gtk::FileChooser::set_current_folder(const char *filename)
{
	return gtk_file_chooser_set_current_folder(gtk_file_chooser(), filename);
}

inline bool 
Xfc::Gtk::FileChooser::set_uri(const char *uri)
{
	return gtk_file_chooser_set_uri(gtk_file_chooser(), uri);
}

inline bool 
Xfc::Gtk::FileChooser::select_uri(const char *uri)
{
	return gtk_file_chooser_select_uri(gtk_file_chooser(), uri);
}
	
inline void 
Xfc::Gtk::FileChooser::unselect_uri(const char *uri)
{
	gtk_file_chooser_unselect_uri(gtk_file_chooser(), uri);
}

inline bool 
Xfc::Gtk::FileChooser::set_current_folder_uri(const char *uri)
{
	return gtk_file_chooser_set_current_folder_uri(gtk_file_chooser(), uri);
}

inline void 
Xfc::Gtk::FileChooser::set_preview_widget_active(bool active)
{
	gtk_file_chooser_set_preview_widget_active(gtk_file_chooser(), active);
}
	
inline void 
Xfc::Gtk::FileChooser::set_use_preview_label(bool use_label)
{
	gtk_file_chooser_set_use_preview_label(gtk_file_chooser(), use_label);
}

inline const Xfc::Gtk::FileChooser::CurrentFolderChangedSignalProxy
Xfc::Gtk::FileChooser::signal_current_folder_changed()
{
	return CurrentFolderChangedSignalProxy(this, &current_folder_changed_signal);
}

inline const Xfc::Gtk::FileChooser::FilerActivatedSignalProxy
Xfc::Gtk::FileChooser::signal_file_activated()
{
	return FilerActivatedSignalProxy(this, &file_activated_signal);
}

inline const Xfc::Gtk::FileChooser::SelectionChangedSignalProxy
Xfc::Gtk::FileChooser::signal_selection_changed()
{
	return SelectionChangedSignalProxy(this, &selection_changed_signal);
}

inline const Xfc::Gtk::FileChooser::UpdatePreviewSignalProxy
Xfc::Gtk::FileChooser::signal_update_preview()
{
	return UpdatePreviewSignalProxy(this, &update_preview_signal);
}

