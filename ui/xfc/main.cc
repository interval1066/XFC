/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
 *
 *  main.cc - Initialization and main processing loop wrapper implementation
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

#include "main.hh"
#include "gdk/events.hh"
#include "gtk/window.hh"
#include "xfc/object.hh"
#include "xfc/utfstring.hh"
#include "xfc/glib/error.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/option.hh"

namespace Xfc {

namespace Main {

/*  Main::Connection
 */

struct Connection : public sigc::connection
{
	typedef void (*PF)(unsigned int);
	PF pf_;
	unsigned int connect_id_;

	Connection(const sigc::slot_base& slot, PF pf)
	: sigc::connection(const_cast<sigc::slot_base&>(slot)), pf_(pf), connect_id_(0)
	{
	}

	static void* notify_handler(void *data)
	{
		Connection *c = static_cast<Connection*>(data);
		if (c)
		{
			(*c->pf_)(c->connect_id_);
			c->connect_id_ = 0;
		}
		return 0;
	}

	static void destroy_handler(void *data)
	{
		Connection *c = static_cast<Connection*>(data);
		if (c)
		{
			c->notify(data);
			delete c;
		}
	}
};

/*  Main::QuitConnection
 */

struct QuitConnection : public Connection
{
	typedef Main::QuitSignal::SlotType QuitSlot;
	QuitSlot slot_;

	QuitConnection(const QuitSlot& slot, PF pf)
	: Connection(slot, pf), slot_(slot)
	{
		slot_.add_destroy_notify_callback(this, &Connection::notify_handler);
	}

	~QuitConnection()
	{
		slot_.remove_destroy_notify_callback(this);
	}
};

/*  Main::KeySnooperConnection
 */

struct KeySnooperConnection : public Connection
{
	typedef KeySnooperSignal::SlotType KeySnoopeSlot;
	KeySnoopeSlot slot_;

	KeySnooperConnection(const
	KeySnoopeSlot& slot, PF pf)
	: Connection(slot, pf), slot_(slot)
	{
		slot_.add_destroy_notify_callback(this, &Connection::notify_handler);
	}

	~KeySnooperConnection()
	{
		slot_.remove_destroy_notify_callback(this);
	}
};

void
init(int *argc, char ***argv)
{
	gtk_init(argc, argv);
}

bool
init_check(int *argc, char ***argv)
{
	return gtk_init_check(argc, argv);
}

bool 
init_with_args(int *argc, char ***argv, const char *parameter_string, G::OptionGroup& main_group, G::Error *error)
{				  
	return gtk_init_with_args(argc, argv, const_cast<char*>(parameter_string), 
                                  (GOptionEntry*)main_group.get_entries(), 0, *error);
}

namespace { // InitAddCallback

struct InitAddCallback
{
	typedef sigc::slot<bool> CallbackSlot;
	CallbackSlot slot_;

	InitAddCallback(const CallbackSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(void *data)
	{
		InitAddCallback *cb = static_cast<InitAddCallback*>(data);
		bool result = cb->slot_();
		delete cb;
		return result;
	}
};

} // namespace

void
init_add(const sigc::slot<bool>& callback)
{
	InitAddCallback *cb = new InitAddCallback(callback);
	gtk_init_add(&InitAddCallback::notify, cb);
}

#ifdef G_THREADS_ENABLED
void
threads_init(GThreadFunctions *vtable)
{
	if (!g_thread_supported())
		g_thread_init(vtable);
	gdk_threads_init();
}
#endif

GOptionGroup* 
get_option_group(bool open_default_display)
{
	return gtk_get_option_group(open_default_display);
}

PangoLanguage*
default_language()
{
	return gtk_get_default_language();
}

bool
events_pending()
{
	return gtk_events_pending() != 0;
}

Pointer<Gdk::Event> 
get_current_event()
{
	return G::Boxed::wrap<Gdk::Event>(GDK_TYPE_EVENT, gtk_get_current_event(), false);	
}

unsigned int 
get_current_event_time()
{
	return gtk_get_current_event_time();
}

bool 
get_current_event_state(Gdk::ModifierTypeField *state)
{
	return gtk_get_current_event_state((GdkModifierType*)state);
}

Gtk::Widget*
get_event_widget(Gdk::Event& event)
{
	GtkWidget *widget = gtk_get_event_widget(event.gdk_event());
	return widget ? G::Object::wrap<Gtk::Widget>(widget) : 0;
}

void
run(Gtk::Window *main_window)
{
	if (main_window)
	{
		main_window->signal_destroy().connect(sigc::ptr_fun(&quit));
		main_window->show();
	}	
	gtk_main();
}

int
level()
{
	return gtk_main_level();
}

void
quit()
{
	gtk_main_quit();
}

bool
iterate(bool blocking)
{
	return gtk_main_iteration_do(blocking);
}

void
grab_add(Gtk::Widget& widget)
{
	gtk_grab_add(widget.gtk_widget());
}

Gtk::Widget*
grab_get_current()
{
	GtkWidget *widget = gtk_grab_get_current();
	return widget ? G::Object::wrap<Gtk::Widget>(widget) : 0;
}

void
grab_remove(Gtk::Widget& widget)
{
	gtk_grab_remove(widget.gtk_widget());
}

/*  QuitSignal
 */

QuitSignal quit_signal;

namespace { // quit_signal_callback

gboolean quit_signal_callback(gpointer data)
{
	QuitConnection *c = static_cast<QuitConnection*>(data);
	return c->slot_();
}

} // namespace

sigc::connection
QuitSignal::connect(const SlotType& slot, unsigned int main_level)
{
	QuitConnection *c = new QuitConnection(slot, &gtk_quit_remove);
	c->connect_id_ = gtk_quit_add_full(main_level, &quit_signal_callback, 0, c, (GtkDestroyNotify)&Connection::destroy_handler);
	return sigc::connection(const_cast<SlotType&>(slot));
}

/*  KeySnooperSignal
 */

KeySnooperSignal key_snooper_signal;

KeySnooperSignal::~KeySnooperSignal()
{
	int count = connection_list.size();
	while (count)
	{
		delete connection_list[count - 1];
		--count;
	}
}

namespace { // key_snooper_signal_callback

gint key_snooper_signal_callback(GtkWidget *widget, GdkEventKey *key, void *data)
{
	KeySnooperConnection *c = static_cast<KeySnooperConnection*>(data);
	Xfc::Gdk::Event tmp_event((GdkEvent*)key);
	return c->slot_(*G::Object::wrap<Gtk::Widget>(widget), *tmp_event.key());
}

} // namespace

sigc::connection
KeySnooperSignal::connect(const SlotType& slot)
{
	KeySnooperConnection *c = new KeySnooperConnection(slot, &gtk_key_snooper_remove);
	c->connect_id_ = gtk_key_snooper_install(&key_snooper_signal_callback, c);
	connection_list.push_back(c);
	return sigc::connection(const_cast<SlotType&>(slot));
}

} // namespace Main

} // namespace Xfc

