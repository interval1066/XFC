/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  editablesignals.cc - Gtk::Editable virtual signal handlers
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
 
#include <gtk/gtkeditable.h>
#include "editablesignals.hh"
#include "private/editableclass.hh"

using namespace Xfc;

/*  Gtk::EditableSignals
 */

Gtk::EditableSignals::~EditableSignals()
{
}
	
void
Gtk::EditableSignals::on_insert_text(const String& text, int *position)
{
	GtkEditableClass *g_iface = EditableClass::get_parent_iface(instance_);
	if (g_iface && g_iface->insert_text)
		g_iface->insert_text((GtkEditable*)instance_, text.c_str(), text.size(), position);
}

void
Gtk::EditableSignals::on_delete_text(int start_pos, int end_pos)
{
	GtkEditableClass *g_iface = EditableClass::get_parent_iface(instance_);
	if (g_iface && g_iface->delete_text)
		g_iface->delete_text((GtkEditable*)instance_, start_pos, end_pos);
}

void
Gtk::EditableSignals::on_changed()
{
	GtkEditableClass *g_iface = EditableClass::get_parent_iface(instance_);
	if (g_iface && g_iface->changed)
		g_iface->changed((GtkEditable*)instance_);
}

