/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  progressbar.cc - GtkProgressBar C++ wrapper implementation
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
 
#include "progressbar.hh"
#include "private/progressbarclass.hh"

using namespace Xfc;

/*  Gtk::ProgressBar
 */

Gtk::ProgressBar::ProgressBar(GtkProgressBar *progress_bar, bool reference)
: Widget((GtkWidget*)progress_bar, reference)
{
}

Gtk::ProgressBar::ProgressBar()
: Widget((GtkWidget*)ProgressBarClass::create())
{
}

Gtk::ProgressBar::ProgressBar(ProgressBarOrientation orientation)
: Widget((GtkWidget*)ProgressBarClass::create())
{
	set_orientation(orientation);
}

Gtk::ProgressBar::~ProgressBar()
{
}
	
String
Xfc::Gtk::ProgressBar::get_text() const
{
	return gtk_progress_bar_get_text(gtk_progress_bar());
}

void
Gtk::ProgressBar::set_text(const String& text)
{
	gtk_progress_bar_set_text(gtk_progress_bar(), text.c_str());
}

/*  Gtk::ProgressBarClass
 */

void
Gtk::ProgressBarClass::init(GtkProgressBarClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::ProgressBarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_PROGRESS_BAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ProgressBarClass::create()
{
	return g_object_new(get_type(), 0);
}

