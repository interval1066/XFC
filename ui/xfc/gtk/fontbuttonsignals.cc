/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  fontbuttonsignals.cc - Gtk::FontButton virtual signal handlers
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

#include "fontbutton.hh"
#include "fontbuttonsignals.hh"
#include "private/fontbuttonclass.hh"

using namespace Xfc;

/*  Gtk::FontButtonSignals
 */

Gtk::FontButtonSignals::FontButtonSignals(FontButton *font_button)
: ButtonSignals(font_button)
{
}

Gtk::FontButtonSignals::~FontButtonSignals()
{
}

void
Gtk::FontButtonSignals::on_font_set()
{
	GtkFontButtonClass *g_class = FontButtonClass::get_parent_class(instance_);
	if (g_class && g_class->font_set)
		g_class->font_set((GtkFontButton*)instance_);
}

