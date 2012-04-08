/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  comboboxentry.cc - GtkComboBoxEntry C++ wrapper implementation
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

#include "comboboxentry.hh"
#include "private/comboboxentryclass.hh"
#include "entry.hh"
#include "liststore.hh"

using namespace Xfc;

/*  Gtk::ComboBoxEntry
 */

Gtk::ComboBoxEntry::ComboBoxEntry(GtkComboBoxEntry *entry_box, bool owns_reference)
: ComboBox((GtkComboBox*)entry_box, owns_reference)
{
}

Gtk::ComboBoxEntry::ComboBoxEntry()
: ComboBox((GtkComboBox*)ComboBoxEntryClass::create())
{
}

Gtk::ComboBoxEntry::ComboBoxEntry(TreeModel& model, int text_column)
: ComboBox((GtkComboBox*)ComboBoxEntryClass::create())
{
	set_model(model);
	set_text_column(text_column);
}

Gtk::ComboBoxEntry::~ComboBoxEntry()
{
}

String 
Gtk::ComboBoxEntry::get_text() const
{
	return static_cast<Entry*>(get_child())->get_text();
}

/*  Gtk::ComboBoxEntryClass
 */

void
Gtk::ComboBoxEntryClass::init(GtkComboBoxEntryClass *g_class)
{
	ComboBoxClass::init((GtkComboBoxClass*)g_class);
}

GType
Gtk::ComboBoxEntryClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_COMBO_BOX_ENTRY, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ComboBoxEntryClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::ComboBoxEntryText
 */
 
Gtk::ComboBoxEntryText::ComboBoxEntryText()
: ComboBoxEntry((GtkComboBoxEntry*)ComboBoxEntryClass::create())
{
	Pointer<Gtk::ListStore> model = new Gtk::ListStore(1, G_TYPE_STRING);	
	set_model(*model);	
}	
	
Gtk::ComboBoxEntryText::~ComboBoxEntryText()
{
}

void 
Gtk::ComboBoxEntryText::append(const String& text)
{
	append(text.c_str());
}

void 
Gtk::ComboBoxEntryText::prepend(const String& text)
{
	prepend(text.c_str());
}

void 
Gtk::ComboBoxEntryText::insert(int position, const String& text)
{
	insert(position, text.c_str());
}

