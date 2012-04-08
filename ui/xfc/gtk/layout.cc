/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  layout.cc - GtkLayout C++ wrapper implmentation
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
#include "private/marshal.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::Layout
 */

Gtk::Layout::Layout(GtkLayout *layout, bool owns_reference)
: Container((GtkContainer*)layout, owns_reference)
{
}

Gtk::Layout::Layout()
: Container((GtkContainer*)LayoutClass::create())
{
}

Gtk::Layout::Layout(Adjustment *hadjustment, Adjustment *vadjustment)
: Container((GtkContainer*)LayoutClass::create())
{
	if (hadjustment)
		set_hadjustment(hadjustment);

	if (vadjustment)
		set_vadjustment(vadjustment);
}

Gtk::Layout::~Layout()
{
}

Gdk::Window*
Gtk::Layout::bin_window() const
{
	return is_realized() ? G::Object::wrap<Gdk::Window>(gtk_layout()->bin_window) : 0;
}

Gtk::Adjustment*
Gtk::Layout::get_hadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_layout_get_hadjustment(gtk_layout()));
}

Gtk::Adjustment*
Gtk::Layout::get_vadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_layout_get_vadjustment(gtk_layout()));
}

void
Gtk::Layout::put(Widget& child_widget, int x, int y)
{
	gtk_layout_put(gtk_layout(), child_widget.gtk_widget(), x, y);
}
  
void 
Gtk::Layout::move(Widget& child_widget, int x, int y)
{
	gtk_layout_move(gtk_layout(), child_widget.gtk_widget(), x, y);
}
  
void 
Gtk::Layout::set_hadjustment(Adjustment *adjustment)
{
	gtk_layout_set_hadjustment(gtk_layout(), *adjustment);
}

void
Gtk::Layout::set_vadjustment(Adjustment *adjustment)
{
	gtk_layout_set_vadjustment(gtk_layout(), *adjustment);
}

/*  Gtk::LayoutClass
 */

void
Gtk::LayoutClass::init(GtkLayoutClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->set_scroll_adjustments = &set_scroll_adjustments_proxy;
}

GtkLayoutClass*
Gtk::LayoutClass::get_parent_class(void *instance)
{
	return static_cast<GtkLayoutClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::LayoutClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_LAYOUT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::LayoutClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::LayoutClass::set_scroll_adjustments_proxy(GtkLayout *layout, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment)
{
	LayoutSignals *signals = dynamic_cast<LayoutSignals*>(G::ObjectSignals::pointer((GObject*)layout));
	if (signals)
	{
		Adjustment *tmp_hadjustment = G::Object::wrap<Adjustment>(hadjustment);
		Adjustment *tmp_vadjustment = G::Object::wrap<Adjustment>(vadjustment);
		signals->on_set_scroll_adjustments(tmp_hadjustment, tmp_vadjustment);
	}
	else
	{
		GtkLayoutClass *g_class = get_parent_class(layout);
		if (g_class && g_class->set_scroll_adjustments)
			g_class->set_scroll_adjustments(layout, hadjustment, vadjustment);
	}
}

/*  Gtk::Layout Signals
 */

const Gtk::Layout::SetScrollAdjustmentsSignalType Gtk::Layout::set_scroll_adjustments_signal("set_scroll_adjustments", (GCallback)&Marshal::void_adjustment_adjustment_callback);

