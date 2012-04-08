/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourcetagstyle.cc - A GtkSourceTagStyle C++ wrapper implementation
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

#include "sourcetagstyle.hh"
#include <xfc/gdk/color.hh>

using namespace Xfc;

/*  Gtk::SourceTagStyle
 */

Gtk::SourceTagStyle::SourceTagStyle()
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, gtk_source_tag_style_new(), false)
{
}

Gtk::SourceTagStyle::SourceTagStyle(const char *foregound)
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, gtk_source_tag_style_new(), false)
{
	set_foreground(foregound);
}

Gtk::SourceTagStyle::SourceTagStyle(const Gdk::Color& foregound)
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, gtk_source_tag_style_new(), false)
{
	set_foreground(foregound);
}

Gtk::SourceTagStyle::SourceTagStyle(GtkSourceTagStyle *style)
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, style)
{
}

Gtk::SourceTagStyle::SourceTagStyle(GtkSourceTagStyle *style, bool copy)
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, style, copy)
{
}

Gtk::SourceTagStyle::SourceTagStyle(const SourceTagStyle& src)
: G::Boxed(GTK_TYPE_SOURCE_TAG_STYLE, src.g_boxed(), true)
{
}

Gtk::SourceTagStyle::~SourceTagStyle()
{
}

Gtk::SourceTagStyle&
Gtk::SourceTagStyle::operator=(const SourceTagStyle& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Gtk::SourceTagStyle::operator GtkSourceTagStyle* () const
{
	return this ? gtk_source_tag_style() : 0;
}

bool
Gtk::SourceTagStyle::is_default() const
{
	return gtk_source_tag_style()->is_default;
}

Gdk::Color
Gtk::SourceTagStyle::get_foreground() const
{
	return Gdk::Color(&gtk_source_tag_style()->foreground);
}

Gdk::Color
Gtk::SourceTagStyle::get_background() const
{
	return Gdk::Color(&gtk_source_tag_style()->background);
}

bool
Gtk::SourceTagStyle::get_italic() const
{
	return gtk_source_tag_style()->italic;
}

bool
Gtk::SourceTagStyle::get_bold() const
{
	return gtk_source_tag_style()->bold;
}

bool
Gtk::SourceTagStyle::get_underline() const
{
	return gtk_source_tag_style()->underline;
}

bool
Gtk::SourceTagStyle::get_strikethrough() const
{
	return gtk_source_tag_style()->strikethrough;
}

void
Gtk::SourceTagStyle::set_foreground(const char *spec)
{
	gdk_color_parse(spec, const_cast<GdkColor*>(&gtk_source_tag_style()->foreground));
	gtk_source_tag_style()->mask |= GTK_SOURCE_TAG_STYLE_USE_FOREGROUND;
}

void
Gtk::SourceTagStyle::set_foreground(const Gdk::Color& color)
{
	gtk_source_tag_style()->foreground = *color.gdk_color();
	gtk_source_tag_style()->mask |= GTK_SOURCE_TAG_STYLE_USE_FOREGROUND;
}

void
Gtk::SourceTagStyle::unset_foreground()
{
	gtk_source_tag_style()->mask &= ~GTK_SOURCE_TAG_STYLE_USE_FOREGROUND;
}

void
Gtk::SourceTagStyle::set_background(const char *spec)
{
	gdk_color_parse(spec, const_cast<GdkColor*>(&gtk_source_tag_style()->background));
	gtk_source_tag_style()->mask |= GTK_SOURCE_TAG_STYLE_USE_BACKGROUND;
}

void
Gtk::SourceTagStyle::set_background(const Gdk::Color& color)
{
	gtk_source_tag_style()->background = *color.gdk_color();
	gtk_source_tag_style()->mask |= GTK_SOURCE_TAG_STYLE_USE_BACKGROUND;
}

void
Gtk::SourceTagStyle::unset_background()
{
	gtk_source_tag_style()->mask &= ~GTK_SOURCE_TAG_STYLE_USE_BACKGROUND;
}

void
Gtk::SourceTagStyle::set_italic(bool italic)
{
	gtk_source_tag_style()->italic = italic;
}

void
Gtk::SourceTagStyle::set_bold(bool bold)
{
	gtk_source_tag_style()->bold = bold;
}

void
Gtk::SourceTagStyle::set_underline(bool underline)
{
	gtk_source_tag_style()->underline = underline;
}

void
Gtk::SourceTagStyle::set_strikethrough(bool strikethrough)
{
	gtk_source_tag_style()->strikethrough = strikethrough;
}

