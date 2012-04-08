/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellrenderercombo.cc - GtkCellRendererCombo C++ wrapper implementation
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
 
#include "cellrenderercombo.hh"
#include "private/cellrenderercomboclass.hh"
#include "treemodel.hh"

using namespace Xfc;

/*  Gtk::CellRendererCombo
 */

Gtk::CellRendererCombo::CellRendererCombo(GtkCellRendererCombo *cell, bool owns_reference)
: CellRendererText((GtkCellRendererText*)cell, owns_reference)
{
}

Gtk::CellRendererCombo::CellRendererCombo()
: CellRendererText((GtkCellRendererText*)CellRendererComboClass::create())
{
}

Gtk::CellRendererCombo::~CellRendererCombo()
{
}

/*  Gtk::CellRendererComboClass
 */

void
Gtk::CellRendererComboClass::init(GtkCellRendererComboClass *g_class)
{
	CellRendererTextClass::init((GtkCellRendererTextClass*)g_class);
}

GType
Gtk::CellRendererComboClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER_COMBO, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererComboClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::CellRendererCombo properties
 */

const Gtk::CellRendererCombo::ModelPropertyType Gtk::CellRendererCombo::model_property("model");

const Gtk::CellRendererCombo::TextColumnPropertyType Gtk::CellRendererCombo::text_column_property("text_column");

const Gtk::CellRendererCombo::HasEntryPropertyType Gtk::CellRendererCombo::has_entry_property("has_entry");

