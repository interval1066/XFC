/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  statusbarsignals.cc - Gtk::Statusbar virtual signal handlers
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
 
#include "statusbar.hh"
#include "statusbarsignals.hh"
#include "private/statusbarclass.hh"

using namespace Xfc;

/*  Gtk::StatusbarSignals
 */

Gtk::StatusbarSignals::StatusbarSignals(Statusbar *statusbar)
: ContainerSignals(statusbar)
{
}

Gtk::StatusbarSignals::~StatusbarSignals()
{
}

void
Gtk::StatusbarSignals::on_text_pushed(unsigned int context_id, const String& text)
{
	GtkStatusbarClass *g_class = StatusbarClass::get_parent_class(instance_);
	if (g_class && g_class->text_pushed)
		g_class->text_pushed((GtkStatusbar*)instance_, context_id, text.c_str());
}

void
Gtk::StatusbarSignals::on_text_popped(unsigned int context_id, const String& text)
{
	GtkStatusbarClass *g_class = StatusbarClass::get_parent_class(instance_);
	if (g_class && g_class->text_popped)
		g_class->text_popped((GtkStatusbar*)instance_, context_id, text.c_str());
}

