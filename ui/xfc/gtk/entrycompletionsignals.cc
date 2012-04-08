/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entrycompletionsignals.cc - Gtk::EntryCompletion virtual signal handlers
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

#include "entrycompletion.hh"
#include "entrycompletionsignals.hh"
#include "treemodel.hh"
#include "private/entrycompletionclass.hh"

using namespace Xfc;

/*  Gtk::EntryCompletionSignals
 */

Gtk::EntryCompletionSignals::EntryCompletionSignals(EntryCompletion *completion)
: G::ObjectSignals(completion)
{
}

Gtk::EntryCompletionSignals::~EntryCompletionSignals()
{
}

bool
Gtk::EntryCompletionSignals::on_match_selected(const TreeModel& model, const TreeIter& iter)
{
	bool result = false;	
	GtkEntryCompletionClass *g_class = EntryCompletionClass::get_parent_class(instance_);
	if (g_class && g_class->match_selected)
		result = g_class->match_selected((GtkEntryCompletion*)instance_, model.gtk_tree_model(), iter.gtk_tree_iter());
	return result;
}

void
Gtk::EntryCompletionSignals::on_action_activated(int index)
{
	GtkEntryCompletionClass *g_class = EntryCompletionClass::get_parent_class(instance_);
	if (g_class && g_class->action_activated)
		g_class->action_activated((GtkEntryCompletion*)instance_, index);
}

bool
Gtk::EntryCompletionSignals::on_insert_prefix(const String& prefix)
{
	bool result = false;	
	GtkEntryCompletionClass *g_class = EntryCompletionClass::get_parent_class(instance_);
	if (g_class && g_class->insert_prefix)
		result = g_class->insert_prefix((GtkEntryCompletion*)instance_, prefix.c_str());
	return result;
}

