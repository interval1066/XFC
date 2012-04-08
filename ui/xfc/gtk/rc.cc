/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  rcstyle.cc - GtkRcStyle C++ wrapper implementation
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
 
#include "rc.hh"
#include "settings.hh"
#include "style.hh"
#include "widget.hh"
#include "private/rcclass.hh"
#include "../gdk/color.hh"
#include "../gdk/pixmap.hh"
#include "../pango/font.hh"
#include "xfc/glib/quark.hh"
#include "xfc/glib/scanner.hh"

using namespace Xfc;

/*  Gtk::RC
 */

std::vector<String>
Gtk::RC::get_default_files()
{
	std::vector<String> filenames;
	
	int i = 0;
	char **tmp_filenames = gtk_rc_get_default_files();
	
	while (tmp_filenames[i] && *tmp_filenames[i])
	{
		String s(tmp_filenames[i]);
		filenames.push_back(s);
		++i;
	}
	return filenames;
}

Gtk::Style*
Gtk::RC::get_style_by_paths(const Settings& settings, const char *widget_path, const char *class_path, GType type)
{
	return G::Object::wrap<Style>(gtk_rc_get_style_by_paths(settings.gtk_settings(), widget_path, class_path, type));
}

Gtk::Style*
Gtk::RC::get_style_by_paths(const Settings& settings, const String& widget_path, const String& class_path, GType type)
{
	return get_style_by_paths(settings, widget_path.c_str(), class_path.c_str(), type);
}

String
Gtk::RC::get_theme_dir()
{
	return gtk_rc_get_theme_dir();
}

String 
Gtk::RC::get_module_dir()
{
	return gtk_rc_get_module_dir();
}

String
Gtk::RC::get_im_module_file()
{
	return gtk_rc_get_im_module_file();
}

Gtk::Style*
Gtk::RC::get_style(const Widget& widget)
{
	return G::Object::wrap<Style>(gtk_rc_get_style(widget.gtk_widget()));
}

Pointer<G::Scanner> 
Gtk::RC::get_scanner()
{
	return new G::Scanner(gtk_rc_scanner_new());
}

void
Gtk::RC::add_default_file(const String& filename)
{
	gtk_rc_add_default_file(filename.c_str());
}

void
Gtk::RC::set_default_files(const std::vector<String>& filenames)
{
	g_return_if_fail(!filenames.empty());
	int count = filenames.size();
	char **tmp_filenames = new char*[count];

	int i = 0;	
	while (i < count)
	{
		tmp_filenames[i] = const_cast<char*>(filenames[i].c_str());
		++i;
	}

	gtk_rc_set_default_files(tmp_filenames);
	delete [] tmp_filenames;
}
		
void
Gtk::RC::parse(const String& filename)
{
	gtk_rc_parse(filename.c_str());
}

void
Gtk::RC::parse_string(const String& rc_string)
{
	gtk_rc_parse_string(rc_string.c_str());
}

bool
Gtk::RC::reparse_all_for_settings(const Settings& settings, bool force_load)
{
	return gtk_rc_reparse_all_for_settings(settings.gtk_settings(), force_load);
}

void 
Gtk::RC::reset_styles(const Settings& settings)
{
	gtk_rc_reset_styles(settings.gtk_settings());
}

String
Gtk::RC::find_pixmap_in_path(const Settings& settings, const char *pixmap_file, const G::Scanner *scanner)
{
	return gtk_rc_find_pixmap_in_path(settings.gtk_settings(), *scanner, pixmap_file);
}

String
Gtk::RC::find_pixmap_in_path(const Settings& settings, const String& pixmap_file, const G::Scanner *scanner)
{
	return gtk_rc_find_pixmap_in_path(settings.gtk_settings(), *scanner, pixmap_file.c_str());
}

unsigned int
Gtk::RC::parse_color(const G::Scanner& scanner, Gdk::Color& color)
{
	return gtk_rc_parse_color(scanner.g_scanner(), color.gdk_color());
}

unsigned int
Gtk::RC::parse_state(const G::Scanner& scanner, StateType& state)
{
	return gtk_rc_parse_state(scanner.g_scanner(), (GtkStateType*)&state);
}

/*  Gtk::RcStyle
 */
 
Gtk::RcStyle::RcStyle(GtkRcStyle *rc_style, bool owns_reference)
: G::Object((GObject*)rc_style, owns_reference)
{
}
	
Gtk::RcStyle::RcStyle() 
: G::Object((GObject*)RcStyleClass::create())
{
}

Gtk::RcStyle::~RcStyle() 
{
}

String 
Gtk::RcStyle::name() const
{
	return gtk_rc_style()->name;
}

String 
Gtk::RcStyle::bg_pixmap_name(StateType state_type) const
{
	return gtk_rc_style()->bg_pixmap_name[state_type];
}

Pointer<Pango::FontDescription>
Gtk::RcStyle::font_description() const
{
	return G::Boxed::wrap<Pango::FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, gtk_rc_style()->font_desc, true);
}

Gdk::Color 
Gtk::RcStyle::fg(StateType state_type) const
{
	return Gdk::Color(&gtk_rc_style()->fg[state_type]);
}

Gdk::Color 
Gtk::RcStyle::bg(StateType state_type) const
{
	return Gdk::Color(&gtk_rc_style()->bg[state_type]);
}

Gdk::Color 
Gtk::RcStyle::text(StateType state_type) const
{
	return Gdk::Color(&gtk_rc_style()->text[state_type]);
}

Gdk::Color 
Gtk::RcStyle::base(StateType state_type) const
{
	return Gdk::Color(&gtk_rc_style()->base[state_type]);
}

Pointer<Gtk::RcStyle>
Gtk::RcStyle::copy() const
{
	return G::Object::wrap_new<RcStyle>(gtk_rc_style_copy(gtk_rc_style()), true);
}

void 
Gtk::RcStyle::set_name(const char *name)
{
	char *old_name = gtk_rc_style()->name;	
	if (old_name)
		g_free(old_name);
	
	gtk_rc_style()->name = name ? g_strdup(name) : 0;
}	
	
void 
Gtk::RcStyle::set_name(const String& name)
{
	set_name(name.c_str());
}

void 
Gtk::RcStyle::set_bg_pixmap_name(StateType state_type, const char *name)
{
	char *old_name = gtk_rc_style()->bg_pixmap_name[state_type];	
	if (old_name)
		g_free(old_name);
	
	gtk_rc_style()->bg_pixmap_name[state_type] = name ? g_strdup(name) : 0;
}	
	
void 
Gtk::RcStyle::set_bg_pixmap_name(StateType state_type, const String& name)
{
	set_bg_pixmap_name(state_type, name.c_str());
}	

void 
Gtk::RcStyle::set_font_description(const Pango::FontDescription *font_desc) const
{
	PangoFontDescription *old_font_desc = gtk_rc_style()->font_desc;	
	if (old_font_desc)
		pango_font_description_free(old_font_desc);
	
	gtk_rc_style()->font_desc = font_desc ? pango_font_description_copy(*font_desc) : 0;	
}

void 
Gtk::RcStyle::set_fg(StateType state_type, const Gdk::Color& color)
{
	gtk_rc_style()->fg[state_type] = *color.gdk_color();
	((int&)gtk_rc_style()->color_flags[state_type]) |= int(GTK_RC_FG);
}
	
void 
Gtk::RcStyle::set_bg(StateType state_type, const Gdk::Color& color)
{
	gtk_rc_style()->bg[state_type] = *color.gdk_color();
	((int&)gtk_rc_style()->color_flags[state_type]) |= int(GTK_RC_BG);
}
	
void 
Gtk::RcStyle::set_text(StateType state_type, const Gdk::Color& color)
{
	gtk_rc_style()->text[state_type] = *color.gdk_color();
	((int&)gtk_rc_style()->color_flags[state_type]) |= int(GTK_RC_TEXT);
}
	
void 
Gtk::RcStyle::set_base(StateType state_type, const Gdk::Color& color)
{
	gtk_rc_style()->base[state_type] = *color.gdk_color();
	((int&)gtk_rc_style()->color_flags[state_type]) |= int(GTK_RC_BASE);
}
	
/*  Gtk::RcStyleClass
 */

void
Gtk::RcStyleClass::init(GtkRcStyleClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::RcStyleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RC_STYLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RcStyleClass::create()
{
	return g_object_new(get_type(), 0);
}

