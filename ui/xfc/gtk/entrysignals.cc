/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entrysignals.cc - Gtk::Entry virtual signal handlers
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
#include "menu.hh"
#include "private/entryclass.hh"

using namespace Xfc;

/*  Gtk::EntrySignals
 */

Gtk::EntrySignals::EntrySignals(Entry *entry) 
: WidgetSignals(entry)
{
}

Gtk::EntrySignals::~EntrySignals()
{
}

void
Gtk::EntrySignals::on_populate_popup(Menu& menu)
{
	GtkEntryClass *g_class = EntryClass::get_parent_class(instance_);
	if (g_class && g_class->populate_popup)
		g_class->populate_popup((GtkEntry*)instance_, menu.gtk_menu());
}

void
Gtk::EntrySignals::on_activate()
{
	GtkEntryClass *g_class = EntryClass::get_parent_class(instance_);
	if (g_class && g_class->activate)
		g_class->activate((GtkEntry*)instance_);
}

void
Gtk::EntrySignals::on_insert_at_cursor(const String& text)
{
	GtkEntryClass *g_class = EntryClass::get_parent_class(instance_);
	if (g_class && g_class->insert_at_cursor)
		g_class->insert_at_cursor((GtkEntry*)instance_, text.c_str());
}

