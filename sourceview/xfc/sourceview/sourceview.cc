/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourceview.cc - GtkSourceView C++ wrapper implementation
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "sourceview.hh"
#include "private/sourceviewclass.hh"
#include <xfc/gdk-pixbuf/pixbuf.hh>

using namespace Xfc;

Gtk::SourceView::SourceView(GtkSourceView *view, bool reference)
: TextView((GtkTextView*)view, reference)
{
}

Gtk::SourceView::SourceView()
: TextView((GtkTextView*)SourceViewClass::create())
{
	set_buffer(new Gtk::SourceBuffer);
}

Gtk::SourceView::SourceView(SourceBuffer& buffer)
: TextView((GtkTextView*)SourceViewClass::create())
{
	set_buffer(&buffer);
}

Gtk::SourceView::~SourceView()
{
}

Gtk::SourceView::operator GtkSourceView* () const
{ 
	return this ? gtk_source_view() : 0;
}

bool
Gtk::SourceView::is_gtk_source_view() const
{
	return is_a(GTK_TYPE_SOURCE_VIEW);
}

Gtk::SourceBuffer*
Gtk::SourceView::get_source_buffer() const
{
	return static_cast<SourceBuffer*>(get_buffer());
}

bool
Gtk::SourceView::get_show_line_numbers() const
{
	return gtk_source_view_get_show_line_numbers(gtk_source_view());
}

bool
Gtk::SourceView::get_show_line_markers() const
{
	return gtk_source_view_get_show_line_markers(gtk_source_view());
}

unsigned int
Gtk::SourceView::get_tabs_width() const
{
	return gtk_source_view_get_tabs_width(gtk_source_view());
}

bool
Gtk::SourceView::get_auto_indent() const
{
	return gtk_source_view_get_auto_indent(gtk_source_view());
}

bool
Gtk::SourceView::get_insert_spaces_instead_of_tabs() const
{
	return gtk_source_view_get_insert_spaces_instead_of_tabs(gtk_source_view());
}

bool
Gtk::SourceView::get_show_margin() const
{
	return gtk_source_view_get_show_margin(gtk_source_view());
}

unsigned int
Gtk::SourceView::get_margin() const
{
	return gtk_source_view_get_margin(gtk_source_view());
}

Pointer<Gdk::Pixbuf>
Gtk::SourceView::get_marker_pixbuf(const String& marker_type) const
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_source_view_get_marker_pixbuf(gtk_source_view(), marker_type.c_str()));
}

bool
Gtk::SourceView::get_smart_home_end() const
{
	return gtk_source_view_get_smart_home_end(gtk_source_view());
}

void
Gtk::SourceView::set_show_line_numbers(bool show)
{
	gtk_source_view_set_show_line_numbers(gtk_source_view(), show);
}

void
Gtk::SourceView::set_show_line_markers(bool show)
{
	gtk_source_view_set_show_line_markers(gtk_source_view(), show);
}

void
Gtk::SourceView::set_tabs_width(unsigned int width)
{
	gtk_source_view_set_tabs_width(gtk_source_view(), width);
}

void
Gtk::SourceView::set_auto_indent(bool enable)
{
	gtk_source_view_set_auto_indent(gtk_source_view(), enable);
}

void
Gtk::SourceView::set_insert_spaces_instead_of_tabs(bool enable)
{
	gtk_source_view_set_insert_spaces_instead_of_tabs(gtk_source_view(), enable);
}

void
Gtk::SourceView::set_show_margin(bool show)
{
	gtk_source_view_set_show_margin(gtk_source_view(), show);
}

void
Gtk::SourceView::set_margin(unsigned int margin)
{
	gtk_source_view_set_margin(gtk_source_view(), margin);
}

void
Gtk::SourceView::set_marker_pixbuf(const String& marker_type, Gdk::Pixbuf *pixbuf)
{
	gtk_source_view_set_marker_pixbuf(gtk_source_view(), marker_type.c_str(), *pixbuf);
}

void Gtk::SourceView::set_smart_home_end(bool enable)
{
	gtk_source_view_set_smart_home_end(gtk_source_view(), enable);
}

void Gtk::SourceView::set_source_buffer( SourceBuffer *buffer )
{
    set_buffer( buffer );
}

/*  Gtk::SourceViewClass
 */

void
Gtk::SourceViewClass::init(GtkSourceViewClass *g_class)
{
	TextViewClass::init((GtkTextViewClass*)g_class);
}

GType
Gtk::SourceViewClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_VIEW, (GClassInitFunc)init);
	}
	return type;
}

void*
Gtk::SourceViewClass::create()
{
	return g_object_new(get_type(), 0);
}

GtkSourceViewClass*
Gtk::SourceViewClass::get_parent_class(void *instance)
{
        return static_cast<GtkSourceViewClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

/*  Properties
 */

const Gtk::SourceView::ShowLineNumbersPropertyType Gtk::SourceView::show_line_numbers_property("show_line_numbers");

const Gtk::SourceView::ShowLineMarkersPropertyType Gtk::SourceView::show_line_markers_property("show_line_markers");

const Gtk::SourceView::TabsWidthPropertyType Gtk::SourceView::tabs_width_property("tabs_width");

const Gtk::SourceView::AutoIndentPropertyType Gtk::SourceView::auto_indent_property("auto_indent");

const Gtk::SourceView::InsertSpacesPropertyType Gtk::SourceView::insert_spaces_property("insert_spaces_instead_of_tabs");

const Gtk::SourceView::ShowMarginPropertyType Gtk::SourceView::show_margin_property("show_margin");

const Gtk::SourceView::MarginPropertyType Gtk::SourceView::margin_property("margin");

const Gtk::SourceView::SmartHomeEndPropertyType Gtk::SourceView::smart_home_end_property("smart_home_end");

