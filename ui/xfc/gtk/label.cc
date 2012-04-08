/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  label.cc - GtkLabel C++ wrapper implementation
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
 
#include "label.hh"
#include "labelsignals.hh"
#include "menu.hh"
#include "private/labelclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Label
 */

Gtk::Label::Label(GtkLabel* label, bool owns_reference)
: Misc((GtkMisc*)label, owns_reference)
{
}

Gtk::Label::Label()
: Misc((GtkMisc*)LabelClass::create())
{
}

Gtk::Label::Label(const char *str, bool use_underline)
: Misc((GtkMisc*)LabelClass::create())
{
	set_text(str);
	set_use_underline(use_underline);
}

Gtk::Label::Label(const String& str, bool use_underline)
: Misc((GtkMisc*)LabelClass::create())
{
	set_text(str);
	set_use_underline(use_underline);
}

Gtk::Label::~Label()
{
}

String
Gtk::Label::get_text() const
{
	return gtk_label_get_text(gtk_label());
}

Pango::AttrList*
Gtk::Label::get_attributes() const
{
	return G::Boxed::wrap<Pango::AttrList>(PANGO_TYPE_ATTR_LIST, gtk_label_get_attributes(gtk_label()));
}

String 
Gtk::Label::get_label() const
{
	return gtk_label_get_label(gtk_label());
}

Gtk::Widget*
Gtk::Label::get_mnemonic_widget () const
{
	return G::Object::wrap<Widget>(gtk_label_get_mnemonic_widget(gtk_label()));
}

Pango::Layout*
Gtk::Label::get_layout() const
{
	return G::Object::wrap<Pango::Layout>(gtk_label_get_layout(gtk_label()));
}

void
Gtk::Label::set_text(const String& str)
{
	gtk_label_set_text(gtk_label(), str.c_str());
}

void
Gtk::Label::set_attributes(Pango::AttrList *attrs)
{
	gtk_label_set_attributes(gtk_label(), *attrs);
}

void
Gtk::Label::set_markup(const String& str)
{
	gtk_label_set_markup(gtk_label(), str.c_str());
}

void
Gtk::Label::set_label(const String& str)
{
	gtk_label_set_label(gtk_label(), str.c_str());
}

void
Gtk::Label::set_markup_with_mnemonic(const String& str)
{
	gtk_label_set_markup_with_mnemonic(gtk_label(), str.c_str());
}

void
Gtk::Label::set_mnemonic_widget(Widget *widget)
{
	gtk_label_set_mnemonic_widget(gtk_label(), *widget);
}

void
Gtk::Label::set_text_with_mnemonic(const String& str)
{
	gtk_label_set_text_with_mnemonic(gtk_label(), str.c_str());
}

void
Gtk::Label::set_justify(Justification jtype)
{
	gtk_label_set_justify(gtk_label(), (GtkJustification)jtype);
}

void
Gtk::Label::set_pattern(const String& pattern)
{
	gtk_label_set_pattern(gtk_label(), pattern.c_str());
}

/*  Gtk::LabelClass
 */

void
Gtk::LabelClass::init(GtkLabelClass *g_class)
{
	MiscClass::init((GtkMiscClass*)g_class);
	g_class->populate_popup = &populate_popup_proxy;
}

GtkLabelClass*
Gtk::LabelClass::get_parent_class(void *instance)
{
	return static_cast<GtkLabelClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::LabelClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_LABEL, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::LabelClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::LabelClass::populate_popup_proxy(GtkLabel *label, GtkMenu *menu)
{
	LabelSignals *signals = dynamic_cast<LabelSignals*>(G::ObjectSignals::pointer((GObject*)label));
	if (signals)
		signals->on_populate_popup(*G::Object::wrap<Gtk::Menu>(menu));
	else
	{
		GtkLabelClass *g_class = get_parent_class(label);
		if (g_class && g_class->populate_popup)
			g_class->populate_popup(label, menu);
	}
}

/*  Gtk::Label Signals
 */

const Gtk::Label::PopulatePopupSignalType Gtk::Label::populate_popup_signal("populate_popup", (GCallback)&Marshal::void_menu_callback);

