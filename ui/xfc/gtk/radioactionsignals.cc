/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  radioactionsignals.cc - Gtk::RadioAction virtual signal handlers
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

#include "radioaction.hh"
#include "radioactionsignals.hh"
#include "private/radioactionclass.hh"

using namespace Xfc;

/*  Gtk::RadioActionSignals
 */

Gtk::RadioActionSignals::RadioActionSignals(RadioAction *action)
: ToggleActionSignals(action)
{
}

Gtk::RadioActionSignals::~RadioActionSignals()
{
}

void
Gtk::RadioActionSignals::on_changed(RadioAction& current)
{
	GtkRadioActionClass *g_class = RadioActionClass::get_parent_class(instance_);
	if (g_class && g_class->changed)
		g_class->changed((GtkRadioAction*)instance_, current.gtk_radio_action());
}

