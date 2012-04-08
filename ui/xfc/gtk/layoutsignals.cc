/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  layoutsignals.cc - Gtk::Layout virtual signal handlers
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
 
#include "layout.hh"
#include "layoutsignals.hh"
#include "private/layoutclass.hh"

using namespace Xfc;

/*  Gtk::LayoutSignals
 */

Gtk::LayoutSignals::LayoutSignals(Layout *layout)
: ContainerSignals(layout)
{
}

Gtk::LayoutSignals::~LayoutSignals()
{
}

void
Gtk::LayoutSignals::on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment)
{
	GtkLayoutClass *g_class = LayoutClass::get_parent_class(instance_);
	if (g_class && g_class->set_scroll_adjustments)
		g_class->set_scroll_adjustments((GtkLayout*)instance_, *hadjustment, *vadjustment);
}

