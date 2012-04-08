/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  iconthemesignals.cc - Gtk::IconTheme virtual signal handlers
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

#include "icontheme.hh"
#include "iconthemesignals.hh"
#include "private/iconthemeclass.hh"

using namespace Xfc;

/*  Gtk::IconThemeSignals
 */

Gtk::IconThemeSignals::IconThemeSignals(IconTheme *icon_theme)
: G::ObjectSignals(icon_theme)
{
}

Gtk::IconThemeSignals::~IconThemeSignals()
{
}

void
Gtk::IconThemeSignals::on_changed()
{
	GtkIconThemeClass *g_class = IconThemeClass::get_parent_class(instance_);
	if (g_class && g_class->changed)
		g_class->changed((GtkIconTheme*)instance_);
}

