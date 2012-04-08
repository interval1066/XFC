/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  editable.cc - GtkEditable C++ wrapper implementation
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
 
#include "editable.hh"
#include "editablesignals.hh"
#include "private/editableclass.hh"
#include "private/marshal.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Gtk::Editable
 */

Gtk::Editable::Editable()
{
}
	
Gtk::Editable::~Editable()
{
}
	
String
Gtk::Editable::get_chars(int start_pos, int end_pos) const
{
	return gtk_editable_get_chars(gtk_editable(), start_pos, end_pos);
}

void
Gtk::Editable::insert_text(const String& new_text, int& position)
{
	gtk_editable_insert_text(gtk_editable(), new_text.c_str(), new_text.size(), &position);
}

/*  Gtk::EditableClass
 */

void
Gtk::EditableClass::init(GtkEditableClass *g_iface)
{
	g_iface->insert_text = &insert_text_proxy;
	g_iface->delete_text = &delete_text_proxy;
	g_iface->changed = &changed_proxy;
}

GtkEditableClass*
Gtk::EditableClass::get_parent_iface(void *instance)
{
	return static_cast<GtkEditableClass*>(g_type_interface_peek_parent(GTK_EDITABLE_GET_CLASS(instance)));
}

void
Gtk::EditableClass::insert_text_proxy(GtkEditable *editable, const gchar *text, gint length, gint *position)
{
	EditableSignals *signals = dynamic_cast<EditableSignals*>(G::ObjectSignals::pointer((GObject*)editable));
	if (signals)
	{
		std::string tmp_text(text, length);
		signals->on_insert_text(tmp_text, position);
	}
	else
	{
		GtkEditableClass *g_iface = get_parent_iface(editable);
		if (g_iface && g_iface->insert_text)
			g_iface->insert_text(editable, text, length, position);
	}
}

void
Gtk::EditableClass::delete_text_proxy(GtkEditable *editable, gint start_pos, gint end_pos)
{
	EditableSignals *signals = dynamic_cast<EditableSignals*>(G::ObjectSignals::pointer((GObject*)editable));
	if (signals)	
		signals->on_delete_text(start_pos, end_pos);
	else
	{
		GtkEditableClass *g_iface = get_parent_iface(editable);
		if (g_iface && g_iface->delete_text)
			g_iface->delete_text(editable, start_pos, end_pos);
	}
}

void
Gtk::EditableClass::changed_proxy(GtkEditable *editable)
{
	EditableSignals *signals = dynamic_cast<EditableSignals*>(G::ObjectSignals::pointer((GObject*)editable));
	if (signals)	
		signals->on_changed();
	else
	{
		GtkEditableClass *g_iface = get_parent_iface(editable);
		if (g_iface && g_iface->changed)
			g_iface->changed(editable);
	}
}

/*  Gtk::Editable Signals
 */

const Gtk::Editable::InsertTextSignalType Gtk::Editable::insert_text_signal("insert_text", (GCallback)&Marshal::void_string_int_pint_callback);

const Gtk::Editable::DeleteTextSignalType Gtk::Editable::delete_text_signal("delete_text", (GCallback)&G::Marshal::void_int_int_callback);

const Gtk::Editable::ChangedSignalType Gtk::Editable::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

