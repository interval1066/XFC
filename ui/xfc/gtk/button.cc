/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  button.cc - GtkButton C++ wrapper implementation
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
 
#include "button.hh"
#include "buttonsignals.hh"
#include "alignment.hh"
#include "box.hh"
#include "image.hh"
#include "label.hh"
#include "stockid.hh"
#include "private/buttonclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Button
 */

Gtk::Button::Button(GtkButton *button, bool owns_reference)
: Bin((GtkBin*)button, owns_reference)
{
}

Gtk::Button::Button() 
: Bin((GtkBin*)ButtonClass::create())
{
}

Gtk::Button::Button(Widget& image)
: Bin((GtkBin*)ButtonClass::create())
{
	add(image);
	image.show();
}

Gtk::Button::Button(const char *label, bool use_underline)
: Bin((GtkBin*)ButtonClass::create())
{
	set_use_underline(use_underline);
	set_label(label);
}

Gtk::Button::Button(const String& label, bool use_underline)
: Bin((GtkBin*)ButtonClass::create())
{
	set_use_underline(use_underline);
	set_label(label);
}

Gtk::Button::Button(Widget& image, const char *label, bool use_underline)
: Bin((GtkBin*)ButtonClass::create())
{
	set_image(image, label, use_underline);
}

Gtk::Button::Button(Widget& image, const String& label, bool use_underline)
: Bin((GtkBin*)ButtonClass::create())
{
	set_image(image, label, use_underline);
}

Gtk::Button::Button(const StockId& stock_id)
: Bin((GtkBin*)ButtonClass::create())
{
	set_stock_id(stock_id);
}

Gtk::Button::~Button()
{
}

String
Gtk::Button::get_label() const
{
	return gtk_button_get_label(gtk_button());
}

Gtk::Widget* 
Gtk::Button::get_image() const
{
	return G::Object::wrap<Widget>(gtk_button_get_image(gtk_button()));
}

void
Gtk::Button::set_label(const String& label)
{
	gtk_button_set_label(gtk_button(), label.c_str());
}

void 
Gtk::Button::set_stock_id(const StockId& stock_id)
{
	set_use_stock(true);
	set_use_underline(true);
	set_label(stock_id);
}	

void 
Gtk::Button::set_image(Widget& image)
{
	gtk_button_set_image(gtk_button(), image.gtk_widget());
}
	
void 
Gtk::Button::set_image(Widget& image, const char *label, bool use_underline)
{
	set_use_underline(use_underline);	
	set_label(label); 	
	set_image(image);
}
	
void 
Gtk::Button::set_image(Widget& image, const String& label, bool use_underline)
{
	set_image(image, label, use_underline);
}

/*  Gtk::ButtonClass
 */

void
Gtk::ButtonClass::init(GtkButtonClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->pressed = &pressed_proxy;
	g_class->released = &released_proxy;
	g_class->clicked = &clicked_proxy;
	g_class->enter = &enter_proxy;
	g_class->leave = &leave_proxy;
	g_class->activate = &activate_proxy;
}

GtkButtonClass*
Gtk::ButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ButtonClass::pressed_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_pressed();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->pressed)
			g_class->pressed(button);
	}
}

void
Gtk::ButtonClass::released_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_released();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->released)
			g_class->released(button);
	}
}

void
Gtk::ButtonClass::clicked_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_clicked();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->clicked)
			g_class->clicked(button);
	}
}

void
Gtk::ButtonClass::enter_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_enter();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->enter)
			g_class->enter(button);
	}
}

void
Gtk::ButtonClass::leave_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_leave();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->leave)
			g_class->leave(button);
	}
}

void
Gtk::ButtonClass::activate_proxy(GtkButton *button)
{
	ButtonSignals *signals = dynamic_cast<ButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_activate();
	else
	{
		GtkButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->activate)
			g_class->activate(button);
	}
}

/*  Gtk::Button signals
 */

const Gtk::Button::PressedSignalType Gtk::Button::pressed_signal("pressed", (GCallback)&G::Marshal::void_callback);

const Gtk::Button::ReleasedSignalType Gtk::Button::released_signal("released", (GCallback)&G::Marshal::void_callback);

const Gtk::Button::ClickedSignalType Gtk::Button::clicked_signal("clicked", (GCallback)&G::Marshal::void_callback);

const Gtk::Button::EnterSignalType Gtk::Button::enter_signal("enter", (GCallback)&G::Marshal::void_callback);

const Gtk::Button::LeaveSignalType Gtk::Button::leave_signal("leave", (GCallback)&G::Marshal::void_callback);

const Gtk::Button::ActivateSignalType Gtk::Button::activate_signal("activate", (GCallback)&G::Marshal::void_callback);

