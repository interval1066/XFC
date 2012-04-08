/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  selection.cc - GtkSelectionData, GtkTargetEntry and GtkTargetList C++ wrapper implementation
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
 
#include "selection.hh"
#include "treemodel.hh"
#include "xfc/gdk/display.hh"
#include "xfc/gdk-pixbuf/pixbuf.hh"
#include "xfc/glib/object.hh"
#include <gtk/gtktreednd.h>

using namespace Xfc;

/*  Gtk::SelectionData
 */

Gtk::SelectionData::SelectionData(GtkSelectionData *data)
: G::Boxed(GTK_TYPE_SELECTION_DATA, data)
{
}

Gtk::SelectionData::SelectionData(GtkSelectionData *data, bool copy)
: G::Boxed(GTK_TYPE_SELECTION_DATA, data, copy)
{
}

Gtk::SelectionData::~SelectionData()
{
}

String
Gtk::SelectionData::get_selection() const
{
	char *selection = gdk_atom_name(gtk_selection_data()->selection);
	String s(selection);
	g_free(selection);
	return s;
}

String
Gtk::SelectionData::get_target() const
{
	char *target = gdk_atom_name(gtk_selection_data()->target);
	String s(target);
	g_free(target);
	return s;
}

String
Gtk::SelectionData::get_type() const
{
	char *type = gdk_atom_name(gtk_selection_data()->type);
	String s(type);
	g_free(type);
	return s;
}

Gdk::Display*
Gtk::SelectionData::display() const
{
	return G::Object::wrap<Gdk::Display>(gtk_selection_data()->display);
}

String
Gtk::SelectionData::get_text() const
{
	unsigned char *text = gtk_selection_data_get_text(gtk_selection_data());
	String s((char*)text);
	g_free(text);
	return s;
}

Pointer<Gdk::Pixbuf> 
Gtk::SelectionData::get_pixbuf() const
{
	GdkPixbuf *pixbuf = gtk_selection_data_get_pixbuf(gtk_selection_data());
	return pixbuf ? G::Object::wrap<Gdk::Pixbuf>(pixbuf, true) : 0;
}
	
std::vector<String> 
Gtk::SelectionData::get_uris() const
{
	std::vector<String> uris;
	
	int i = 0;
	char **tmp_uris = gtk_selection_data_get_uris(gtk_selection_data());
	
	while (tmp_uris[i] && *tmp_uris[i])
	{
		String s(tmp_uris[i]);
		uris.push_back(s);
		++i;
	}
	
	g_strfreev(tmp_uris);
	return uris;
}

bool
Gtk::SelectionData::get_targets(std::vector<Gdk::Atom>& targets) const
{
	g_return_val_if_fail(targets.empty(), false);
	GdkAtom *tmp_targets = 0;
	int n_atoms = 0;

	bool result = gtk_selection_data_get_targets(gtk_selection_data(), &tmp_targets, &n_atoms);
	if (result)
	{
		int i = 0;
		while (i < n_atoms)
		{
			targets.push_back(tmp_targets[i]);
			++i;
		}
		g_free(tmp_targets);
	}
	return result;
}
	
bool 
Gtk::SelectionData::get_targets(std::vector<String>& targets) const
{
	g_return_val_if_fail(targets.empty(), false);
	GdkAtom *tmp_targets = 0;
	int n_atoms = 0;

	bool result = gtk_selection_data_get_targets(gtk_selection_data(), &tmp_targets, &n_atoms);
	if (result)
	{
		int i = 0;
		while (i < n_atoms)
		{
			char *name = gdk_atom_name(tmp_targets[i]);
			targets.push_back(name);
			g_free(name);
			++i;
		}
		result = !targets.empty();
		g_free(tmp_targets);
	}
	return result;
}

bool
Gtk::SelectionData::set_text(const String& str)
{
	return gtk_selection_data_set_text(gtk_selection_data(), str.c_str(), str.size());
}

bool 
Gtk::SelectionData::set_pixbuf(Gdk::Pixbuf& pixbuf)
{
	return gtk_selection_data_set_pixbuf(gtk_selection_data(), pixbuf.gdk_pixbuf());
}
	
bool 
Gtk::SelectionData::set_uris(const std::vector<String>& uris)
{
	g_return_val_if_fail(!uris.empty(), false);
	int count = uris.size();
	char **tmp_uris = new char*[count];

	int i = 0;	
	while (i < count)
	{
		tmp_uris[i] = const_cast<char*>(uris[i].c_str());
		++i;
	}

	bool result = gtk_selection_data_set_uris(gtk_selection_data(), tmp_uris);
	delete [] tmp_uris;
	return result;
}

bool
Gtk::SelectionData::get_row_drag_data(TreeModel **model, Pointer<TreePath> *path) const
{
	GtkTreeModel *tmp_model = 0;
	GtkTreePath *tmp_path = 0;

	bool result = gtk_tree_get_row_drag_data(gtk_selection_data(), model ? &tmp_model : 0, path ? &tmp_path : 0);

	if (model && tmp_model)
	{
		G::Object *object = G::Object::pointer((GObject*)tmp_model);
		*model = dynamic_cast<TreeModel*>(object);
	}

	if (path && tmp_path)
		*path = G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, tmp_path, false);

	return result;
}
	
bool 
Gtk::SelectionData::set_row_drag_data(TreeModel& tree_model, const TreePath& path)
{
	return gtk_tree_set_row_drag_data(gtk_selection_data(), tree_model.gtk_tree_model(), path.gtk_tree_path());
}

/*  Gtk::TargetEntry
 */
 
Gtk::TargetEntry::TargetEntry()
{
	set(0, 0, 0);
}

Gtk::TargetEntry::TargetEntry(const char *target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags)
{
	set(target_name, unique_id, drag_flags);
}

Gtk::TargetEntry::TargetEntry(const String& target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags)
{
	set(target_name, unique_id, drag_flags);
}

void
Gtk::TargetEntry::set(const char *target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags)
{
	entry_.target = const_cast<char*>(target_name);
	entry_.flags = drag_flags;
	entry_.info = unique_id;
}

void
Gtk::TargetEntry::set(const String& target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags)
{
	set(target_name.c_str(), unique_id, drag_flags);
}

/*  Gtk::TargetList
 */
 
Gtk::TargetList::TargetList()
: target_list_(gtk_target_list_new(0, 0))
{
}

Gtk::TargetList::TargetList(const std::vector<TargetEntry>& targets)
: target_list_(gtk_target_list_new(0, 0))
{
	add(targets);
}

Gtk::TargetList::TargetList(GtkTargetList *target_list)
: target_list_(target_list)
{
}

Gtk::TargetList::~TargetList()
{
	if (target_list_)
	{
		gtk_target_list_unref(target_list_);
		target_list_ = 0;
	}
}

void
Gtk::TargetList::add(Gdk::Atom target, unsigned int flags, unsigned int info)
{
	gtk_target_list_add(gtk_target_list(), target, flags, info);
}

void 
Gtk::TargetList::add(const TargetEntry& entry)
{
	gtk_target_list_add(gtk_target_list(), gdk_atom_intern (entry.target(), FALSE), entry.flags(), entry.info());
}

void 
Gtk::TargetList::add(const std::vector<TargetEntry>& targets)
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}
	
	gtk_target_list_add_table(gtk_target_list(), tmp_targets, count);
	delete [] tmp_targets;
}

