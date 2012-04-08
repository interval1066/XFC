/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  iconviewsignals.cc - Gtk::IconView virtual signal handlers
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
 
#include "iconview.hh"
#include "iconviewsignals.hh"
#include "treemodel.hh"
#include "private/iconviewclass.hh"

using namespace Xfc;

Gtk::IconViewSignals::IconViewSignals(IconView *icon_view) 
: ContainerSignals(icon_view)
{
}

Gtk::IconViewSignals::~IconViewSignals()
{
}

void
Gtk::IconViewSignals::on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment)
{
	GtkIconViewClass *g_class = IconViewClass::get_parent_class(instance_);
	if (g_class && g_class->set_scroll_adjustments)
		g_class->set_scroll_adjustments((GtkIconView*)instance_, *hadjustment, *vadjustment);
}

void
Gtk::IconViewSignals::on_item_activated(const TreePath& path)
{
	GtkIconViewClass *g_class = IconViewClass::get_parent_class(instance_);
	if (g_class && g_class->item_activated)
		g_class->item_activated((GtkIconView*)instance_, path.gtk_tree_path());
}

void
Gtk::IconViewSignals::on_selection_changed()
{
	GtkIconViewClass *g_class = IconViewClass::get_parent_class(instance_);
	if (g_class && g_class->selection_changed)
		g_class->selection_changed((GtkIconView*)instance_);
}

