/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  handleboxsignals.cc - Gtk::HandleBox virtual signal handlers
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
 
#include "handlebox.hh"
#include "handleboxsignals.hh"
#include "private/handleboxclass.hh"

using namespace Xfc;

/*  Gtk::HandleBoxSignals
 */

Gtk::HandleBoxSignals::HandleBoxSignals(HandleBox *handle_box)
: ContainerSignals(handle_box)
{
}

Gtk::HandleBoxSignals::~HandleBoxSignals()
{
}

void
Gtk::HandleBoxSignals::on_child_attached(Widget& child)
{
	GtkHandleBoxClass *g_class = HandleBoxClass::get_parent_class(instance_);
	if (g_class && g_class->child_attached)
		g_class->child_attached((GtkHandleBox*)instance_, child.gtk_widget());
}

void
Gtk::HandleBoxSignals::on_child_detached(Widget& child)
{
	GtkHandleBoxClass *g_class = HandleBoxClass::get_parent_class(instance_);
	if (g_class && g_class->child_detached)
		g_class->child_detached((GtkHandleBox*)instance_, child.gtk_widget());
}

