/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  textbuffersignals.cc - Gtk::TextBuffer virtual signal handlers
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

#include "textbuffer.hh"
#include "textbuffersignals.hh"
#include "private/textbufferclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

/*  Gtk::TextBufferSignals
 */

Gtk::TextBufferSignals::TextBufferSignals(TextBuffer *buffer)
: G::ObjectSignals(buffer)
{
}
	
Gtk::TextBufferSignals::~TextBufferSignals()
{
}
	
void
Gtk::TextBufferSignals::on_insert_text(TextIter& pos, const String& text)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->insert_text)
		g_class->insert_text((GtkTextBuffer*)instance_, pos.gtk_text_iter(), text.c_str(), text.size());
}

void
Gtk::TextBufferSignals::on_insert_pixbuf(TextIter& pos, Gdk::Pixbuf& pixbuf)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->insert_pixbuf)
		g_class->insert_pixbuf((GtkTextBuffer*)instance_, pos.gtk_text_iter(), pixbuf.gdk_pixbuf());
}

void
Gtk::TextBufferSignals::on_insert_child_anchor(TextIter& pos, TextChildAnchor& anchor)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->insert_child_anchor)
		g_class->insert_child_anchor((GtkTextBuffer*)instance_, pos.gtk_text_iter(), anchor.gtk_text_child_anchor());
}

void
Gtk::TextBufferSignals::on_delete_range(TextIter& start, TextIter& end)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->delete_range)
		g_class->delete_range((GtkTextBuffer*)instance_, start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBufferSignals::on_changed()
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->changed)
		g_class->changed((GtkTextBuffer*)instance_);
}

void
Gtk::TextBufferSignals::on_modified_changed()
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->modified_changed)
		g_class->modified_changed((GtkTextBuffer*)instance_);
}

void
Gtk::TextBufferSignals::on_mark_set(const TextIter& location, TextMark& mark)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->mark_set)
		g_class->mark_set((GtkTextBuffer*)instance_, location.gtk_text_iter(), mark.gtk_text_mark());
}

void
Gtk::TextBufferSignals::on_mark_deleted(TextMark& mark)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->mark_deleted)
		g_class->mark_deleted((GtkTextBuffer*)instance_, mark.gtk_text_mark());
}

void
Gtk::TextBufferSignals::on_apply_tag(TextTag& tag, const TextIter& start_char, const TextIter& end_char)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->apply_tag)
		g_class->apply_tag((GtkTextBuffer*)instance_, tag.gtk_text_tag(), start_char.gtk_text_iter(), end_char.gtk_text_iter());
}

void
Gtk::TextBufferSignals::on_remove_tag(TextTag& tag, const TextIter& start_char, const TextIter& end_char)
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->remove_tag)
		g_class->remove_tag((GtkTextBuffer*)instance_, tag.gtk_text_tag(), start_char.gtk_text_iter(), end_char.gtk_text_iter());
}

void
Gtk::TextBufferSignals::on_begin_user_action()
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->begin_user_action)
		g_class->begin_user_action((GtkTextBuffer*)instance_);
}

void
Gtk::TextBufferSignals::on_end_user_action()
{
	GtkTextBufferClass *g_class = TextBufferClass::get_parent_class(instance_);
	if (g_class && g_class->end_user_action)
		g_class->end_user_action((GtkTextBuffer*)instance_);
}

