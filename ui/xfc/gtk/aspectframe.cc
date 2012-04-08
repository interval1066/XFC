/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  aspectframe.cc - GtkAspectFrame C++ wrapper implementation
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
 
#include "aspectframe.hh"
#include "private/aspectframeclass.hh"

using namespace Xfc;

/*  Gtk::AspectFrame
 */

Gtk::AspectFrame::AspectFrame(GtkAspectFrame *aspect_frame, bool owns_reference)
: Frame((GtkFrame*)aspect_frame, owns_reference)
{
}

Gtk::AspectFrame::AspectFrame()
: Frame((GtkFrame*)AspectFrameClass::create())
{
}

Gtk::AspectFrame::AspectFrame(float xalign, float yalign)
: Frame((GtkFrame*)AspectFrameClass::create())
{
	set(xalign, yalign, 1.0, true);
}

Gtk::AspectFrame::AspectFrame(float xalign, float yalign, float ratio)
: Frame((GtkFrame*)AspectFrameClass::create())
{
	set(xalign, yalign, ratio, false);
}

Gtk::AspectFrame::AspectFrame(const char *label, float xalign, float yalign, float ratio)
: Frame((GtkFrame*)AspectFrameClass::create())
{
	set_label(label);
	set(xalign, yalign, ratio, false);
}

Gtk::AspectFrame::AspectFrame(const String& label, float xalign, float yalign, float ratio)
: Frame((GtkFrame*)AspectFrameClass::create())
{
	set_label(label);
	set(xalign, yalign, ratio, false);
}

Gtk::AspectFrame::~AspectFrame()
{
}

/*  Gtk::AspectFrameClass
 */

void
Gtk::AspectFrameClass::init(GtkAspectFrameClass *g_class)
{
	FrameClass::init((GtkFrameClass*)g_class);
}

GType
Gtk::AspectFrameClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ASPECT_FRAME, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AspectFrameClass::create()
{
	return g_object_new(get_type(), 0);
}

