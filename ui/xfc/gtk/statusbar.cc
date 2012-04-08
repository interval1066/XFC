/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  statusbar.cc - GtkStatusbar C++ wrapper implementation
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
#include "private/marshal.hh"
#include "private/statusbarclass.hh"

using namespace Xfc;

/*  Gtk::Statusbar
 */

Gtk::Statusbar::Statusbar(GtkStatusbar *statusbar, bool owns_reference)
: HBox((GtkHBox*)statusbar, owns_reference)
{
}

Gtk::Statusbar::Statusbar() 
: HBox((GtkHBox*)StatusbarClass::create())
{
}

Gtk::Statusbar::~Statusbar()
{
}

unsigned int
Gtk::Statusbar::get_context_id(const String& context_description) const
{
	return gtk_statusbar_get_context_id(gtk_statusbar(), context_description.c_str());
}

unsigned int
Gtk::Statusbar::push(const String& text, unsigned int context_id)
{
	return gtk_statusbar_push(gtk_statusbar(), context_id, text.c_str());
}

/*  Gtk::StatusbarClass
 */

void
Gtk::StatusbarClass::init(GtkStatusbarClass *g_class)
{
	HBoxClass::init((GtkHBoxClass*)g_class);
	g_class->text_pushed = &text_pushed_proxy;
	g_class->text_popped = &text_popped_proxy;
}

GtkStatusbarClass*
Gtk::StatusbarClass::get_parent_class(void *instance)
{
	return static_cast<GtkStatusbarClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::StatusbarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_STATUSBAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::StatusbarClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::StatusbarClass::text_pushed_proxy(GtkStatusbar *statusbar, guint context_id, const gchar *text)
{
	StatusbarSignals *signals = dynamic_cast<StatusbarSignals*>(G::ObjectSignals::pointer((GObject*)statusbar));
	if (signals)
	{
		String tmp_text(text);
		signals->on_text_pushed(context_id, tmp_text);
	}
	else
	{
		GtkStatusbarClass *g_class = get_parent_class(statusbar);
		if (g_class && g_class->text_pushed)
			g_class->text_pushed(statusbar, context_id, text);
	}
}

void
Gtk::StatusbarClass::text_popped_proxy(GtkStatusbar *statusbar, guint context_id, const gchar *text)
{
	StatusbarSignals *signals = dynamic_cast<StatusbarSignals*>(G::ObjectSignals::pointer((GObject*)statusbar));
	if (signals)
	{
		String tmp_text(text);
		signals->on_text_popped(context_id, tmp_text);
	}
	else
	{
		GtkStatusbarClass *g_class = get_parent_class(statusbar);
		if (g_class && g_class->text_popped)
			g_class->text_popped(statusbar, context_id, text);
	}
}

/*  Gtk::Statusbar signals
 */

const Gtk::Statusbar::TextPushedSignalType Gtk::Statusbar::text_pushed_signal("text_pushed", (GCallback)&Marshal::void_uint_string_callback);

const Gtk::Statusbar::TextPoppedSignalType Gtk::Statusbar::text_popped_signal("text_popped", (GCallback)&Marshal::void_uint_string_callback);

