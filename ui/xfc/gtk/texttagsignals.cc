/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  texttagsignals.cc - Gtk::TextTag and Gtk::TextTagTable virtual signal handlers
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
 
#include "texttag.hh"
#include "texttagsignals.hh"
#include "textiter.hh"
#include "private/texttagclass.hh"
#include "../gdk/events.hh"

using namespace Xfc;

/*  Gtk::TextTagSignals
 */

Gtk::TextTagSignals::TextTagSignals(TextTag *tag)
: G::ObjectSignals(tag)
{
}

Gtk::TextTagSignals::~TextTagSignals()
{
}

bool
Gtk::TextTagSignals::on_event(G::Object& event_object, Gdk::Event& event, const TextIter& iter)
{
	GtkTextTagClass *g_class = TextTagClass::get_parent_class(instance_);
	bool result = false;
	if (g_class && g_class->event)
		result = g_class->event((GtkTextTag*)instance_, event_object.g_object(), event.gdk_event(), iter.gtk_text_iter());
	return result;
}

/*  Gtk::TextTagTableSignals
 */

Gtk::TextTagTableSignals::TextTagTableSignals(TextTagTable *table)
: G::ObjectSignals(table)
{
}

Gtk::TextTagTableSignals::~TextTagTableSignals()
{
}
	
void
Gtk::TextTagTableSignals::on_tag_changed(TextTag& tag, bool size_changed)
{
	GtkTextTagTableClass *g_class = TextTagTableClass::get_parent_class(instance_);
	if (g_class && g_class->tag_changed)
		g_class->tag_changed((GtkTextTagTable*)instance_, tag.gtk_text_tag(), size_changed);
}

void
Gtk::TextTagTableSignals::on_tag_added(TextTag& tag)
{
	GtkTextTagTableClass *g_class = TextTagTableClass::get_parent_class(instance_);
	if (g_class && g_class->tag_added)
		g_class->tag_added((GtkTextTagTable*)instance_, tag.gtk_text_tag());
}

void
Gtk::TextTagTableSignals::on_tag_removed(TextTag& tag)
{
	GtkTextTagTableClass *g_class = TextTagTableClass::get_parent_class(instance_);
	if (g_class && g_class->tag_removed)
		g_class->tag_removed((GtkTextTagTable*)instance_, tag.gtk_text_tag());
}

