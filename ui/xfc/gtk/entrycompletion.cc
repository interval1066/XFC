/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entrycompletion.cc - GtkEntryCompletion C++ wrapper implementation
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
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::EntryCompletion
 */

Gtk::EntryCompletion::EntryCompletion(GtkEntryCompletion *completion, bool owns_reference)
: G::Object((GObject*)completion, owns_reference)
{
}

Gtk::EntryCompletion::EntryCompletion()
: G::Object((GObject*)EntryCompletionClass::create())
{
}

Gtk::EntryCompletion::EntryCompletion(TreeModel& model)
: G::Object((GObject*)EntryCompletionClass::create())
{
	set_model(model);
}

Gtk::EntryCompletion::~EntryCompletion()
{
}

Gtk::Entry* 
Gtk::EntryCompletion::get_entry() const
{	
	return G::Object::wrap<Entry>((GtkEntry*)gtk_entry_completion_get_entry(gtk_entry_completion()));
}
	
Gtk::TreeModel* 
Gtk::EntryCompletion::get_model() const
{
	Gtk::TreeModel *tmp_model = 0;
	GtkTreeModel *model = gtk_entry_completion_get_model(gtk_entry_completion());
	if (model)
	{
		G::Object *object = G::Object::pointer((GObject*)model);
		tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_model;
}

void 
Gtk::EntryCompletion::set_model(TreeModel& model)
{
	gtk_entry_completion_set_model(gtk_entry_completion(), model.gtk_tree_model());
}

namespace { // MatchCallback

struct MatchCallback
{
	typedef Gtk::EntryCompletion::MatchSlot MatchSlot;
	MatchSlot slot_;

	MatchCallback(const MatchSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkEntryCompletion*, const char *key, GtkTreeIter *iter, void *data)
	{
		MatchCallback *cb = static_cast<MatchCallback*>(data);
		String s(key);		
		Gtk::TreeIter tmp_iter(iter);
		return cb->slot_(s, tmp_iter);
	}

	static void destroy(void *data)
	{
		MatchSlot *cb = static_cast<MatchSlot*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::EntryCompletion::set_match_func(const MatchSlot& slot)
{
	MatchCallback *cb = new MatchCallback(slot);
	gtk_entry_completion_set_match_func(gtk_entry_completion(), &MatchCallback::notify, cb, &MatchCallback::destroy);
}

void 
Gtk::EntryCompletion::insert_action_text(int index, const String& text)
{
	insert_action_text(index, text.c_str());
}
	
void 
Gtk::EntryCompletion::insert_action_markup(int index, const String& markup)
{
	insert_action_markup(index, markup.c_str());
}

/*  Gtk::EntryCompletionClass
 */

void
Gtk::EntryCompletionClass::init(GtkEntryCompletionClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->match_selected = &match_selected_proxy;
	g_class->action_activated = &action_activated_proxy;
	g_class->insert_prefix = &insert_prefix_proxy;
}

GtkEntryCompletionClass*
Gtk::EntryCompletionClass::get_parent_class(void *instance)
{
	return static_cast<GtkEntryCompletionClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::EntryCompletionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ENTRY_COMPLETION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::EntryCompletionClass::create()
{
	return g_object_new(get_type(), 0);
}

gboolean
Gtk::EntryCompletionClass::match_selected_proxy(GtkEntryCompletion *completion, GtkTreeModel *model, GtkTreeIter *iter)
{
	gboolean result = FALSE;		
	EntryCompletionSignals *signals = dynamic_cast<EntryCompletionSignals*>(G::ObjectSignals::pointer((GObject*)completion));
	if (signals)
	{
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		result = signals->on_match_selected(*tmp_model, tmp_iter);
	}
	else
	{
		GtkEntryCompletionClass *g_class = get_parent_class(completion);
		if (g_class && g_class->match_selected)
			result = g_class->match_selected(completion, model, iter);
	}
	return result;
}

void
Gtk::EntryCompletionClass::action_activated_proxy(GtkEntryCompletion *completion, int index)
{
	EntryCompletionSignals *signals = dynamic_cast<EntryCompletionSignals*>(G::ObjectSignals::pointer((GObject*)completion));
	if (signals)
		signals->on_action_activated(index);
	else
	{
		GtkEntryCompletionClass *g_class = get_parent_class(completion);
		if (g_class && g_class->action_activated)
			g_class->action_activated(completion, index);
	}
}

gboolean 
Gtk::EntryCompletionClass::insert_prefix_proxy(GtkEntryCompletion *completion, const gchar *prefix)
{
	gboolean result = FALSE;		
	EntryCompletionSignals *signals = dynamic_cast<EntryCompletionSignals*>(G::ObjectSignals::pointer((GObject*)completion));
	if (signals)
	{
		String tmp_prefix(prefix);
		result = signals->on_insert_prefix(tmp_prefix);
	}
	else
	{
		GtkEntryCompletionClass *g_class = get_parent_class(completion);
		if (g_class && g_class->insert_prefix)
			result = g_class->insert_prefix(completion, prefix);
	}
	return result;
}
 
/*  Gtk::EntryCompletion signals
 */

const Gtk::EntryCompletion::MatchSelectedSignalType Gtk::EntryCompletion::match_selected_signal("match_selected", (GCallback)&Marshal::bool_treemodel_treeiter_callback);

const Gtk::EntryCompletion::ActionActivatedSignalType Gtk::EntryCompletion::action_activated_signal("action_activated", (GCallback)&Marshal::void_int_callback);

const Gtk::EntryCompletion::InsertPrefixSignalType Gtk::EntryCompletion::insert_prefix_signal("insert_prefix", (GCallback)&Marshal::bool_string_callback);
