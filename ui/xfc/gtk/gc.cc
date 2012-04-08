/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
 *
 *  gc.cc - gtk_gc_get and gtk_gc_release C++ wrapper implementation
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
 
#include "gc.hh"
#include "../gdk/color.hh"

using namespace Xfc;

Gtk::GC::GC(int depth, Gdk::Colormap *colormap, const Gdk::GCValues& values)
: Gdk::GC(gtk_gc_get(depth, *colormap, values.gdk_gc_values(), values.gdk_gc_values_mask()))
{
}

Gtk::GC::~GC()
{
	gtk_gc_release(gdk_gc());
}

