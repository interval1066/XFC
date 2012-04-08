/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filechooser.cc - GtkFileChooser C++ wrapper implementation
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

#include "filechooser.hh"
#include "private/marshal.hh"
#include "widget.hh"
#include "xfc/glib/error.hh"

using namespace Xfc;

/*  Gtk::FileChooser
 */

Gtk::FileChooser::FileChooser()
{
}

Gtk::FileChooser::~FileChooser()
{
}

std::string 
Gtk::FileChooser::get_filename() const
{
	char *filename = gtk_file_chooser_get_filename(gtk_file_chooser());
	std::string s((filename) ? filename : "");	
	g_free(filename);
	return s;
}

bool 
Gtk::FileChooser::get_filenames(std::vector<std::string>& filenames) const
{
	g_return_val_if_fail(filenames.empty(), false);	
	GSList *first = gtk_file_chooser_get_filenames(gtk_file_chooser());
	GSList *next = first;

	while (next)
	{
		char *filename = (char*)next->data;
		filenames.push_back(filename);
		g_free(filename);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !filenames.empty();
}

std::string 
Gtk::FileChooser::get_current_folder() const 
{
	char *name = gtk_file_chooser_get_current_folder(gtk_file_chooser());
	std::string s((name) ? name : "");	
	g_free(name);
	return s;
}

String 
Gtk::FileChooser::get_uri() const
{
	char *uri = gtk_file_chooser_get_uri(gtk_file_chooser());
	String s(uri);
	g_free(uri);
	return s;
}

bool 
Gtk::FileChooser::get_uris(std::vector<String>& uris) const
{
	g_return_val_if_fail(uris.empty(), false);	
	GSList *first = gtk_file_chooser_get_uris(gtk_file_chooser());
	GSList *next = first;

	while (next)
	{
		char *uri = (char*)next->data;
		uris.push_back(uri);
		g_free(uri);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !uris.empty();
}

String 
Gtk::FileChooser::get_current_folder_uri() const
{
	char *uri = gtk_file_chooser_get_current_folder_uri(gtk_file_chooser());
	String s(uri);
	g_free(uri);
	return s;
}

Gtk::Widget* 
Gtk::FileChooser::get_preview_widget() const
{
	GtkWidget *widget = gtk_file_chooser_get_preview_widget(gtk_file_chooser());
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}

std::string 
Gtk::FileChooser::get_preview_filename() const
{
	char *filename = gtk_file_chooser_get_preview_filename(gtk_file_chooser());
	std::string s((filename) ? filename : "");	
	g_free(filename);
	return s;
}
 
String 
Gtk::FileChooser::get_preview_uri() const
{
	char *uri = gtk_file_chooser_get_preview_uri(gtk_file_chooser());
	String s(uri);
	g_free(uri);
	return s;
}
	
Gtk::Widget* 
Gtk::FileChooser::get_extra_widget() const
{
	GtkWidget *widget = gtk_file_chooser_get_extra_widget(gtk_file_chooser());
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}

Gtk::FileFilter* 
Gtk::FileChooser::get_filter() const
{
	GtkFileFilter *filter = gtk_file_chooser_get_filter(gtk_file_chooser());
	return filter ? G::Object::wrap<FileFilter>(filter) : 0;
}

bool 
Gtk::FileChooser::list_filters(std::vector<String>& filters) const
{
	g_return_val_if_fail(filters.empty(), false);	
	GSList *first = gtk_file_chooser_list_filters(gtk_file_chooser());
	GSList *next = first;

	while (next)
	{
		char *filter = (char*)next->data;
		filters.push_back(filter);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !filters.empty();
}

bool 
Gtk::FileChooser::list_shortcut_folders(std::vector<std::string>& folders) const
{
	g_return_val_if_fail(folders.empty(), false);	
	GSList *first = gtk_file_chooser_list_shortcut_folders(gtk_file_chooser());
	GSList *next = first;

	while (next)
	{
		char *name = (char*)next->data;
		folders.push_back(name);
		g_free(name);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !folders.empty();
}

bool 
Gtk::FileChooser::list_shortcut_folder_uris(std::vector<String>& uris) const
{
	g_return_val_if_fail(uris.empty(), false);	
	GSList *first = gtk_file_chooser_list_shortcut_folder_uris(gtk_file_chooser());
	GSList *next = first;

	while (next)
	{
		char *uri = (char*)next->data;
		uris.push_back(uri);
		g_free(uri);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !uris.empty();
}

void
Gtk::FileChooser::set_current_name(const String& name)
{
	set_current_name(name.c_str());
}

bool 
Gtk::FileChooser::set_filename(const std::string& filename)
{
	return set_filename(filename.c_str());
}

bool 
Gtk::FileChooser::select_filename(const std::string& filename)
{
	return select_filename(filename.c_str());
}

void 
Gtk::FileChooser::unselect_filename(const std::string& filename)
{
	unselect_filename(filename.c_str());
}

bool 
Gtk::FileChooser::set_current_folder(const std::string& filename)
{
	return set_current_folder(filename.c_str());
}

bool 
Gtk::FileChooser::set_uri(const String& uri)
{
	return set_uri(uri.c_str());
}

bool 
Gtk::FileChooser::select_uri(const String& uri)
{
	return select_uri(uri.c_str());
}

void 
Gtk::FileChooser::unselect_uri(const String& uri)
{
	unselect_uri(uri.c_str());
}

bool 
Gtk::FileChooser::set_current_folder_uri(const String& uri)
{
	return set_current_folder_uri(uri.c_str());
}

void 
Gtk::FileChooser::set_preview_widget(Widget& preview_widget)
{
	gtk_file_chooser_set_preview_widget(gtk_file_chooser(), preview_widget.gtk_widget());
}

void 
Gtk::FileChooser::set_extra_widget(Widget& extra_widget)
{
	gtk_file_chooser_set_extra_widget(gtk_file_chooser(), extra_widget.gtk_widget());
}
				
void 
Gtk::FileChooser::add_filter(const FileFilter& filter)
{
	gtk_file_chooser_add_filter(gtk_file_chooser(), filter.gtk_file_filter());
}

void 
Gtk::FileChooser::remove_filter(const FileFilter& filter)
{
	gtk_file_chooser_remove_filter(gtk_file_chooser(), filter.gtk_file_filter());
}

void 
Gtk::FileChooser::set_filter(const FileFilter& filter)
{
	gtk_file_chooser_set_filter(gtk_file_chooser(), filter.gtk_file_filter());
}
	
bool 
Gtk::FileChooser::add_shortcut_folder(const char *folder, G::Error *error)
{
	return gtk_file_chooser_add_shortcut_folder(gtk_file_chooser(), folder, *error);
}
	
bool 
Gtk::FileChooser::add_shortcut_folder(const std::string& folder, G::Error *error)
{
	return add_shortcut_folder(folder.c_str(), error);
}
	
bool 
Gtk::FileChooser::remove_shortcut_folder(const char *folder, G::Error *error)
{
	return gtk_file_chooser_remove_shortcut_folder(gtk_file_chooser(), folder, *error);
}
	
bool 
Gtk::FileChooser::remove_shortcut_folder(const std::string& folder, G::Error *error)
{
	return remove_shortcut_folder(folder.c_str(), error);
}

bool 
Gtk::FileChooser::add_shortcut_folder_uri(const char *uri, G::Error *error)
{
	return gtk_file_chooser_add_shortcut_folder_uri(gtk_file_chooser(), uri, *error);
}

bool 
Gtk::FileChooser::add_shortcut_folder_uri(const String& uri, G::Error *error)
{
	return add_shortcut_folder_uri(uri.c_str(), error);
}

bool 
Gtk::FileChooser::remove_shortcut_folder_uri(const char *uri, G::Error *error)
{
	return gtk_file_chooser_remove_shortcut_folder_uri(gtk_file_chooser(), uri, *error);
}
	
bool 
Gtk::FileChooser::remove_shortcut_folder_uri(const String& uri, G::Error *error)
{
	return remove_shortcut_folder_uri(uri.c_str(), error);
}

/*  Gtk::FileChooser signals
 */

const Gtk::FileChooser::CurrentFolderChangedSignalType Gtk::FileChooser::current_folder_changed_signal("current-folder-changed", (GCallback)&G::Marshal::void_callback);

const Gtk::FileChooser::FilerActivatedSignalType Gtk::FileChooser::file_activated_signal("file-activated", (GCallback)&G::Marshal::void_callback);

const Gtk::FileChooser::SelectionChangedSignalType Gtk::FileChooser::selection_changed_signal("selection-changed", (GCallback)&G::Marshal::void_callback);

const Gtk::FileChooser::UpdatePreviewSignalType Gtk::FileChooser::update_preview_signal("update-preview", (GCallback)&G::Marshal::void_callback);

