/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderertoggle.cc - GtkCellRendererToggle C++ wrapper implementation
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
 
#include "cellrenderertoggle.hh"
#include "cellrenderertogglesignals.hh"
#include "private/cellrenderertoggleclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::CellRendererToggle
 */

Gtk::CellRendererToggle::CellRendererToggle(GtkCellRendererToggle *cell, bool owns_reference)
: CellRenderer((GtkCellRenderer*)cell, owns_reference)
{
}

Gtk::CellRendererToggle::CellRendererToggle()
: CellRenderer((GtkCellRenderer*)CellRendererToggleClass::create())
{
}

Gtk::CellRendererToggle::~CellRendererToggle()
{
}

/*  Gtk::CellRendererToggleClass
 */

void
Gtk::CellRendererToggleClass::init(GtkCellRendererToggleClass *g_class)
{
	CellRendererClass::init((GtkCellRendererClass*)g_class);
	g_class->toggled = &toggled_proxy;
}

GtkCellRendererToggleClass*
Gtk::CellRendererToggleClass::get_parent_class(void *instance)
{
	return static_cast<GtkCellRendererToggleClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CellRendererToggleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER_TOGGLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererToggleClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::CellRendererToggleClass::toggled_proxy(GtkCellRendererToggle *cell_renderer_toggle, const gchar *path)
{
	CellRendererToggleSignals *signals = dynamic_cast<CellRendererToggleSignals*>(G::ObjectSignals::pointer((GObject*)cell_renderer_toggle));
	if (signals)
	{
		std::string tmp_path(path);
		signals->on_toggled(tmp_path);
	}
	else
	{
		GtkCellRendererToggleClass *g_class = get_parent_class(cell_renderer_toggle);
		if (g_class && g_class->toggled)
			g_class->toggled(cell_renderer_toggle, path);
	}
}

/* Gtk::CellRendererToggle properties
 */

const Gtk::CellRendererToggle::ActivePropertyType Gtk::CellRendererToggle::active_property("active");

const Gtk::CellRendererToggle::ActivatablePropertyType Gtk::CellRendererToggle::activatable_property("activatable");

const Gtk::CellRendererToggle::RadioPropertyType Gtk::CellRendererToggle::radio_property("radio");

const Gtk::CellRendererToggle::InconsistentPropertyType Gtk::CellRendererToggle::inconsistent_property("inconsistent");

/*  Gtk::CellRendererToggle signals
 */

const Gtk::CellRendererToggle::ToggledSignalType Gtk::CellRendererToggle::toggled_signal("toggled", (GCallback)&Marshal::void_string_callback);

