/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  viewport.cc - GtkViewport C++ wrapper implementation
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

#include "viewport.hh"
#include "viewportsignals.hh"
#include "private/marshal.hh"
#include "private/viewportclass.hh"

using namespace Xfc;

/*  Gtk::Viewport
 */

Gtk::Viewport::Viewport(GtkViewport *viewport, bool owns_reference)
: Bin((GtkBin*)viewport, owns_reference)
{
}

Gtk::Viewport::Viewport() 
: Bin((GtkBin*)ViewportClass::create())
{
}

Gtk::Viewport::Viewport(Adjustment *hadjustment, Adjustment *vadjustment)
: Bin((GtkBin*)ViewportClass::create())
{
	if (hadjustment)
		set_hadjustment(hadjustment);
	if (vadjustment)
		set_vadjustment(vadjustment);
}

Gtk::Viewport::~Viewport()
{
}

Gtk::Adjustment*
Gtk::Viewport::get_hadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_viewport_get_hadjustment(gtk_viewport()));
}

Gtk::Adjustment*
Gtk::Viewport::get_vadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_viewport_get_vadjustment(gtk_viewport()));
}

Gtk::ShadowType
Gtk::Viewport::get_shadow_type() const
{
	return (ShadowType)gtk_viewport_get_shadow_type(gtk_viewport());
}

void 
Gtk::Viewport::set_hadjustment(Adjustment *adjustment)
{
	gtk_viewport_set_hadjustment(gtk_viewport(), *adjustment);
}
	
void 
Gtk::Viewport::set_vadjustment(Adjustment *adjustment)
{
	gtk_viewport_set_vadjustment(gtk_viewport(), *adjustment);
}

/*  Gtk::ViewportClass
 */

void
Gtk::ViewportClass::init(GtkViewportClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->set_scroll_adjustments = &set_scroll_adjustments_proxy;
}

GtkViewportClass*
Gtk::ViewportClass::get_parent_class(void *instance)
{
	return static_cast<GtkViewportClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ViewportClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VIEWPORT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ViewportClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ViewportClass::set_scroll_adjustments_proxy(GtkViewport *viewport, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment)
{
	ViewportSignals *signals = dynamic_cast<ViewportSignals*>(G::ObjectSignals::pointer((GObject*)viewport));
	if (signals)
		signals->on_set_scroll_adjustments(G::Object::wrap<Gtk::Adjustment>(hadjustment),
		                                   G::Object::wrap<Gtk::Adjustment>(vadjustment));
	else
	{
		GtkViewportClass *g_class = get_parent_class(viewport);
		if (g_class && g_class->set_scroll_adjustments)
			g_class->set_scroll_adjustments(viewport, hadjustment, vadjustment);
	}
}

/*  Gtk::Viewport signals
 */

const Gtk::Viewport::SetScrollAdjustmentsSignalType Gtk::Viewport::set_scroll_adjustments_signal("set_scroll_adjustments", (GCallback)&Marshal::void_adjustment_adjustment_callback);
