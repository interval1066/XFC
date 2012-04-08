/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entry.cc - GtkEntry C++ wrapper implementation
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
 
#include "entry.hh"
#include "entrysignals.hh"
#include "entrycompletion.hh"
#include "menu.hh"
#include "private/celleditableiface.hh"
#include "private/editableclass.hh"
#include "private/entryclass.hh"
#include "private/marshal.hh"
#include "../pango/layout.hh"

using namespace Xfc;

/*  Gtk::Entry
 */

Gtk::Entry::Entry(GtkEntry *entry, bool owns_reference)
: Widget((GtkWidget*)entry, owns_reference)
{
}

Gtk::Entry::Entry() 
: Widget((GtkWidget*)EntryClass::create())
{
}

Gtk::Entry::Entry(int max_length) 
: Widget((GtkWidget*)EntryClass::create())
{
	set_max_length(max_length);
}

Gtk::Entry::~Entry()
{
}

String
Gtk::Entry::get_text() const
{
	return gtk_entry_get_text(gtk_entry());
}

G::Unichar
Gtk::Entry::get_invisible_char() const
{
	return gtk_entry_get_invisible_char(gtk_entry());
}

Pango::Layout*
Gtk::Entry::get_layout() const
{
	return G::Object::wrap<Pango::Layout>(gtk_entry_get_layout(gtk_entry()));
}

Gtk::EntryCompletion*
Gtk::Entry::get_completion() const
{
	GtkEntryCompletion *completion = gtk_entry_get_completion(gtk_entry());
	return completion ? G::Object::wrap<EntryCompletion>(completion) : 0;
}

Gtk::EntryCompletion* 
Gtk::Entry::create_completion(TreeModel& model)
{
	EntryCompletion *completion = new EntryCompletion(model);
	set_completion(completion);
	completion->unref();
	return completion;
}

void
Gtk::Entry::set_completion(EntryCompletion *completion)
{
	gtk_entry_set_completion(gtk_entry(), *completion);
}

void
Gtk::Entry::set_invisible_char(G::Unichar ch)
{
	gtk_entry_set_invisible_char(gtk_entry(), ch);
}

void
Gtk::Entry::set_text(const String& text)
{
	gtk_entry_set_text(gtk_entry(), text.c_str());
}

/*  Gtk::EntryClass
 */

void
Gtk::EntryClass::init(GtkEntryClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
	g_class->populate_popup = &populate_popup_proxy;
	g_class->activate = &activate_proxy;
	g_class->insert_at_cursor = &insert_at_cursor_proxy;
}

GtkEntryClass*
Gtk::EntryClass::get_parent_class(void *instance)
{
	return static_cast<GtkEntryClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::EntryClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ENTRY, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_EDITABLE, (GInterfaceInitFunc)&EditableClass::init);
		G::TypeInstance::add_interface(type, GTK_TYPE_CELL_EDITABLE, (GInterfaceInitFunc)&CellEditableIface::init);
	}
	return type;
}

void*
Gtk::EntryClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::EntryClass::populate_popup_proxy(GtkEntry *entry, GtkMenu *menu)
{
	EntrySignals *signals = dynamic_cast<EntrySignals*>(G::ObjectSignals::pointer((GObject*)entry));
	if (signals)
		signals->on_populate_popup(*G::Object::wrap<Gtk::Menu>(menu));
	else
	{
		GtkEntryClass *g_class = get_parent_class(entry);
		if (g_class && g_class->populate_popup)
			g_class->populate_popup(entry, menu);
	}
}

void
Gtk::EntryClass::activate_proxy(GtkEntry *entry)
{
	EntrySignals *signals = dynamic_cast<EntrySignals*>(G::ObjectSignals::pointer((GObject*)entry));
	if (signals)
		signals->on_activate();
	else
	{
		GtkEntryClass *g_class = get_parent_class(entry);
		if (g_class && g_class->activate)
			g_class->activate(entry);
	}
}

void
Gtk::EntryClass::insert_at_cursor_proxy(GtkEntry *entry, const gchar *str)
{
	EntrySignals *signals = dynamic_cast<EntrySignals*>(G::ObjectSignals::pointer((GObject*)entry));
	if (signals)
	{
		std::string tmp_str(str);
		signals->on_insert_at_cursor(tmp_str);
	}
	else
	{
		GtkEntryClass *g_class = get_parent_class(entry);
		if (g_class && g_class->insert_at_cursor)
			g_class->insert_at_cursor(entry, str);
	}
}

/*  Gtk::Entry Signals
 */

const Gtk::Entry::PopulatePopupSignalType Gtk::Entry::populate_popup_signal("populate_popup", (GCallback)&Marshal::void_menu_callback);

const Gtk::Entry::ActviateSignalType Gtk::Entry::activate_signal("activate", (GCallback)&G::Marshal::void_callback);

const Gtk::Entry::InsertAtCursorSignalType Gtk::Entry::insert_at_cursor_signal("insert_at_cursor", (GCallback)&Marshal::void_string_callback);

