/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  dialog.cc - GtkDialog C++ wrapper implementation
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
 
#include "dialog.hh"
#include "dialogsignals.hh"
#include "box.hh"
#include "button.hh"
#include "buttonbox.hh"
#include "stockid.hh"
#include "private/dialogclass.hh"
#include "private/marshal.hh"
#include "../gdk/screen.hh"

using namespace Xfc;

/*  Gtk::Dialog
 */

Gtk::Dialog::Dialog(GtkDialog *dialog, bool owns_reference)
: Window((GtkWindow*)dialog, owns_reference)
{
}

Gtk::Dialog::Dialog()
: Window((GtkWindow*)DialogClass::create())
{
}

Gtk::Dialog::Dialog(const char *title, Window *parent, DialogFlagsField flags)
: Window((GtkWindow*)DialogClass::create())
{
	construct(title, parent, flags);
}

Gtk::Dialog::Dialog(const String& title, Window *parent, DialogFlagsField flags)
: Window((GtkWindow*)DialogClass::create())
{
	construct(title.c_str(), parent, flags);
}

Gtk::Dialog::~Dialog()
{
}

void 
Gtk::Dialog::construct(const char *title, Gtk::Window *parent, Gtk::DialogFlagsField flags)
{
	set_title(title);
	if (parent)
		set_transient_for(parent);
	if (flags & Gtk::DIALOG_MODAL)
		set_modal(true);
	if (flags & Gtk::DIALOG_DESTROY_WITH_PARENT)
		set_destroy_with_parent(true);
	if (flags & Gtk::DIALOG_NO_SEPARATOR)
		set_has_separator(false);
}

Gtk::VBox*
Gtk::Dialog::client_area() const
{
	return G::Object::wrap<VBox>((GtkVBox*)gtk_dialog()->vbox);
}

Gtk::HButtonBox*
Gtk::Dialog::action_area() const
{
	return G::Object::wrap<HButtonBox>((GtkHButtonBox*)gtk_dialog()->action_area);
}

bool 
Gtk::Dialog::alternative_button_order(const Gdk::Screen *screen)
{
	return gtk_alternative_dialog_button_order(*screen);
}

void
Gtk::Dialog::add_action_widget(Widget& child, int response_id)
{
	gtk_dialog_add_action_widget(gtk_dialog(), child.gtk_widget(), response_id);
}

Gtk::Button*
Gtk::Dialog::add_button(const char *button_text, int response_id)
{
	return G::Object::wrap<Button>((GtkButton*)gtk_dialog_add_button(gtk_dialog(), button_text, response_id));
}

Gtk::Button*
Gtk::Dialog::add_button(const String& button_text, int response_id)
{
	return add_button(button_text.c_str(), response_id);
}

Gtk::Button*
Gtk::Dialog::add_button(const StockId& stock_id, int response_id)
{
	return add_button(stock_id.c_str(), response_id);
}

Gtk::Button* 
Gtk::Dialog::add_button(StockButtonType button_type)
{
	const char *stock_id = 0;
	int response_id;
	
	switch (button_type)
	{
	case STOCK_BUTTON_OK:
		stock_id = GTK_STOCK_OK;
		response_id = GTK_RESPONSE_OK;
		break;
		
	case STOCK_BUTTON_CANCEL:
		stock_id = GTK_STOCK_CANCEL;
		response_id = GTK_RESPONSE_CANCEL;
		break;
		
	case STOCK_BUTTON_CLOSE:
		stock_id = GTK_STOCK_CLOSE;
		response_id = GTK_RESPONSE_CLOSE;
		break;
		
	case STOCK_BUTTON_YES:
		stock_id = GTK_STOCK_YES;
		response_id = GTK_RESPONSE_YES;
		break;
		
	case STOCK_BUTTON_NO:
		stock_id = GTK_STOCK_NO;
		response_id = GTK_RESPONSE_NO;
		break;
		
	case STOCK_BUTTON_APPLY:
		stock_id = GTK_STOCK_APPLY;
		response_id = GTK_RESPONSE_APPLY;
		break;
		
	case STOCK_BUTTON_HELP:
		stock_id = GTK_STOCK_HELP;
		response_id = GTK_RESPONSE_HELP;
		break;
		
	default:
		break;
	}
	
	if (stock_id)
		return add_button(stock_id, response_id);
	else
		return 0;
}

/*  Gtk::DialogClass
 */

void
Gtk::DialogClass::init(GtkDialogClass *g_class)
{
	WindowClass::init((GtkWindowClass*)g_class);
	g_class->response = &response_proxy;
	g_class->close = &close_proxy;
}

GtkDialogClass*
Gtk::DialogClass::get_parent_class(void *instance)
{
	return static_cast<GtkDialogClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::DialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_DIALOG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::DialogClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::DialogClass::response_proxy(GtkDialog *dialog, gint response_id)
{
	DialogSignals *signals = dynamic_cast<DialogSignals*>(G::ObjectSignals::pointer((GObject*)dialog));
	if (signals)
		signals->on_response(response_id);
	else
	{
		GtkDialogClass *g_class = get_parent_class(dialog);
		if (g_class && g_class->response)
			g_class->response(dialog, response_id);
	}
}

void
Gtk::DialogClass::close_proxy(GtkDialog *dialog)
{
	DialogSignals *signals = dynamic_cast<DialogSignals*>(G::ObjectSignals::pointer((GObject*)dialog));
	if (signals)
		signals->on_close();
	else
	{
		GtkDialogClass *g_class = get_parent_class(dialog);
		if (g_class && g_class->close)
			g_class->close(dialog);
	}
}

/*  Gtk::Dialog Signals
 */

const Gtk::Dialog::ResponseSignalType Gtk::Dialog::response_signal("response", (GCallback)&G::Marshal::void_int_callback);

const Gtk::Dialog::CloseSignalType Gtk::Dialog::close_signal("close", (GCallback)&G::Marshal::void_callback);

