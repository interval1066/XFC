/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderersignals.cc - Gtk::CellRenderer virtual signal handlers
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
 
#include "cellrenderer.hh"
#include "cellrenderersignals.hh"
#include "celleditable.hh"
#include "private/cellrendererclass.hh"

using namespace Xfc;

/*  Gtk::CellRendererSignals
 */

Gtk::CellRendererSignals::CellRendererSignals(CellRenderer *cell)
: ObjectSignals(cell)
{
}

Gtk::CellRendererSignals::~CellRendererSignals() 
{
}
	
void
Gtk::CellRendererSignals::on_editing_canceled()
{
	GtkCellRendererClass *g_class = CellRendererClass::get_parent_class(instance_);
	if (g_class && g_class->editing_canceled)
		g_class->editing_canceled((GtkCellRenderer*)instance_);
}

void 
Gtk::CellRendererSignals::on_editing_started(CellEditable *editable, const String& path)
{
	GtkCellRendererClass *g_class = CellRendererClass::get_parent_class(instance_);
	if (g_class && g_class->editing_started)
		g_class->editing_started((GtkCellRenderer*)instance_, *editable, path.c_str());
}

