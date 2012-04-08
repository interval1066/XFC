/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  celleditable.cc - GtkCellEditable C++ wrapper implementation
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

#include "celleditable.hh"
#include "celleditablesignals.hh"
#include "private/celleditableiface.hh"
#include "private/marshal.hh"
#include "../gdk/events.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Gtk::CellEditable
 */

Gtk::CellEditable::CellEditable()
{
}
	
Gtk::CellEditable::~CellEditable()
{
}
	
void
Gtk::CellEditable::start_editing(const Gdk::Event *event)
{
	gtk_cell_editable_start_editing(gtk_cell_editable(), *event);
}

/*  Gtk::CellEditableIface
 */

void
Gtk::CellEditableIface::init(GtkCellEditableIface *g_iface)
{
	g_iface->editing_done = &editing_done_proxy;
	g_iface->remove_widget = &remove_widget_proxy;
}

GtkCellEditableIface*
Gtk::CellEditableIface::get_parent_iface(void *instance)
{
	return static_cast<GtkCellEditableIface*>(g_type_interface_peek_parent(GTK_CELL_EDITABLE_GET_IFACE(instance)));
}

void
Gtk::CellEditableIface::editing_done_proxy(GtkCellEditable *cell_editable)
{	
	CellEditableSignals *signals = dynamic_cast<CellEditableSignals*>(G::ObjectSignals::pointer((GObject*)cell_editable));
	if (signals)
		signals->on_editing_done();
	else
	{
		GtkCellEditableIface *g_iface = get_parent_iface(cell_editable);
		if (g_iface && g_iface->editing_done)
			g_iface->editing_done(cell_editable);
	}
}

void
Gtk::CellEditableIface::remove_widget_proxy(GtkCellEditable *cell_editable)
{
	CellEditableSignals *signals = dynamic_cast<CellEditableSignals*>(G::ObjectSignals::pointer((GObject*)cell_editable));
	if (signals)
		signals->on_remove_widget();
	else
	{
		GtkCellEditableIface *g_iface = get_parent_iface(cell_editable);
		if (g_iface && g_iface->remove_widget)
			g_iface->remove_widget(cell_editable);
	}
}

/*  Gtk::CellEditable signals
 */

const Gtk::CellEditable::EditingDoneSignalType Gtk::CellEditable::editing_done_signal("editing_done", (GCallback)&G::Marshal::void_callback);

const Gtk::CellEditable::RemoveWidgetSignalType Gtk::CellEditable::remove_widget_signal("remove_widget", (GCallback)&G::Marshal::void_callback);

