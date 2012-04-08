/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  frame.cc - GtkFrame C++ wrapper implementation
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
 
#include "frame.hh"
#include "private/frameclass.hh"
#include <gtk/gtklabel.h>

using namespace Xfc;

/*  Gtk::Frame
 */

Gtk::Frame::Frame(GtkFrame *frame, bool owns_reference)
: Bin((GtkBin*)frame, owns_reference)
{
}

Gtk::Frame::Frame(ShadowType type)
: Bin((GtkBin*)FrameClass::create())
{
	set_shadow_type(type);
}

Gtk::Frame::Frame(const char *label, ShadowType type)
: Bin((GtkBin*)FrameClass::create())
{
	set_label(label);
	set_shadow_type(type);
}

Gtk::Frame::Frame(const String& label, ShadowType type)
: Bin((GtkBin*)FrameClass::create())
{
	set_label(label);
	set_shadow_type(type);
}

Gtk::Frame::~Frame()
{
}

String
Gtk::Frame::get_label() const
{
	return gtk_frame_get_label(gtk_frame());
}

Gtk::Widget*
Gtk::Frame::get_label_widget() const
{
	return G::Object::wrap<Widget>(gtk_frame_get_label_widget(gtk_frame()));
}

void
Gtk::Frame::set_label(const String& label)
{
	gtk_frame_set_label(gtk_frame(), label.c_str());
}

void
Gtk::Frame::set_label_widget(Widget& label_widget)
{
	gtk_frame_set_label_widget(gtk_frame(), label_widget.gtk_widget());
}

/*  Gtk::FrameClass
 */

void
Gtk::FrameClass::init(GtkFrameClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
}

GType
Gtk::FrameClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FRAME, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FrameClass::create()
{
	return g_object_new(get_type(), 0);
}

