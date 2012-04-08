/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  handlebox.cc - GtkHandleBox C++ wrapper implementation
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
#include "private/marshal.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::HandleBox
 */

Gtk::HandleBox::HandleBox(GtkHandleBox *handle_box, bool owns_reference)
: Bin((GtkBin*)handle_box, owns_reference)
{
}

Gtk::HandleBox::HandleBox(ShadowType shadow_type)
: Bin((GtkBin*)HandleBoxClass::create())
{
	set_shadow_type(shadow_type);
}

Gtk::HandleBox::~HandleBox()
{
}

Gdk::Window*
Gtk::HandleBox::get_bin_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_handle_box()->bin_window);
}

Gdk::Window*
Gtk::HandleBox::get_float_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_handle_box()->float_window);
}

/*  Gtk::HandleBoxClass
 */

void
Gtk::HandleBoxClass::init(GtkHandleBoxClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->child_attached = &child_attached_proxy;
	g_class->child_detached = &child_detached_proxy;
}

GtkHandleBoxClass*
Gtk::HandleBoxClass::get_parent_class(void *instance)
{
	return static_cast<GtkHandleBoxClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::HandleBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HANDLE_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HandleBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::HandleBoxClass::child_attached_proxy(GtkHandleBox *handle_box, GtkWidget *child)
{
	HandleBoxSignals *signals = dynamic_cast<HandleBoxSignals*>(G::ObjectSignals::pointer((GObject*)handle_box));
	if (signals)
		signals->on_child_attached(*G::Object::wrap<Widget>(child));
	else
	{
		GtkHandleBoxClass *g_class = get_parent_class(handle_box);
		if (g_class && g_class->child_attached)
			g_class->child_attached(handle_box, child);
	}
}

void
Gtk::HandleBoxClass::child_detached_proxy(GtkHandleBox *handle_box, GtkWidget *child)
{
	HandleBoxSignals *signals = dynamic_cast<HandleBoxSignals*>(G::ObjectSignals::pointer((GObject*)handle_box));
	if (signals)
		signals->on_child_detached(*G::Object::wrap<Widget>(child));
	else
	{
		GtkHandleBoxClass *g_class = get_parent_class(handle_box);
		if (g_class && g_class->child_detached)
			g_class->child_detached(handle_box, child);
	}
}

/*  Gtk::HandleBox Signals
 */

const Gtk::HandleBox::ChildAttachedSignalType Gtk::HandleBox::child_attached_signal("child_attached", (GCallback)&Marshal::void_widget_callback2);

const Gtk::HandleBox::ChildDetachedSignalType Gtk::HandleBox::child_detached_signal("child_detached", (GCallback)&Marshal::void_widget_callback2);

