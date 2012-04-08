/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  textviewsignals.cc - Gtk::TextView virtual signal handlers
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
 
#include "textview.hh"
#include "textviewsignals.hh"
#include "menu.hh"
#include "private/textviewclass.hh"

using namespace Xfc;

/*  Gtk::TextViewSignals
 */

Gtk::TextViewSignals::TextViewSignals(TextView *text_view)
: ContainerSignals(text_view)
{
}

Gtk::TextViewSignals::~TextViewSignals() 
{
}

void
Gtk::TextViewSignals::on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment)
{
	GtkTextViewClass *g_class = TextViewClass::get_parent_class(instance_);
	if (g_class && g_class->set_scroll_adjustments)
		g_class->set_scroll_adjustments((GtkTextView*)instance_, *hadjustment, *vadjustment);
}

void
Gtk::TextViewSignals::on_populate_popup(Menu& menu)
{
	GtkTextViewClass *g_class = TextViewClass::get_parent_class(instance_);
	if (g_class && g_class->populate_popup)
		g_class->populate_popup((GtkTextView*)instance_, menu.gtk_menu());
}

void
Gtk::TextViewSignals::on_set_anchor()
{
	GtkTextViewClass *g_class = TextViewClass::get_parent_class(instance_);
	if (g_class && g_class->set_anchor)
		g_class->set_anchor((GtkTextView*)instance_);
}

void
Gtk::TextViewSignals::on_insert_at_cursor(const String& str)
{
	GtkTextViewClass *g_class = TextViewClass::get_parent_class(instance_);
	if (g_class && g_class->insert_at_cursor)
		g_class->insert_at_cursor((GtkTextView*)instance_, str.c_str());
}

