/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

/// @file xfc/main.hh
/// @brief Initialization and main processing loop interface
///
/// XFC wraps the GTK+ initialization functions and events into the Main namespace
/// rather than a static class. Before using XFC, you need to initialize it.
/// Initialization connects to the window system display, and parses some standard
/// command line arguments. The init() function initializes XFC. init() exits the
/// application if errors occur; to avoid this, use init_check(). init_check() allows
/// you to recover from a failed XFC initialization - you might start up your 
/// application in text mode instead.
/// 
/// Like all GUI toolkits, XFC uses an event-driven programming model. When the user
/// is doing nothing, XFC sits in the main loop and waits for input. If the user 
/// performs some action - say, a mouse click - then the main loop "wakes up" and
/// delivers an event to XFC. XFC forwards the event to one or more widgets.
///
/// When widgets receive an event, they frequently emit one or more signals. Signals
/// notify your program that "something interesting happened" by invoking slots you've
/// connected to the signal with the signal's connect() method. Slots are callable
/// objects that can be connected to signals. Slots can be used to connect static functions,
/// class methods and function objects to a signal. When your slot is called it invokes
/// your function or method.
///
/// When your methods are invoked, you would typically take some action - for example,
/// when an Open button is clicked you might display a Gtk::FileSelectionDialog. After
/// a callback finishes, XFC will return to the main loop and await more user input.

#ifndef XFC_MAIN_HH
#define XFC_MAIN_HH

#ifndef XFC_POINTER_HH
#include <xfc/pointer.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef SIGCXX_SIGCXX_H
#include <sigc++/sigc++.h>
#endif

#ifndef __GTK_MAIN_H__
#include <gtk/gtkmain.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Error;
class OptionGroup;
}
	
namespace Gdk {
class Event;
class EventKey;
}

namespace Gtk {
class Widget;
class Window;
}

namespace Main {

class Connection;

/// @name Initializers
/// @{

void init(int *argc, char ***argv);
///< Initialize the XFC library.
///< @param argc Address of the argc parameter of your main() function,
///<             changed if any arguments were handled.
///< @param argv Address of the argv parameter of your main() function, any
///<             arguments understood by init() are stripped before returning.
///<
///< Call this method before using any other XFC methods in your GUI applications.
///< It will initialize everything needed to operate the toolkit and parses some
///< standard command line options. argc and argv are adjusted accordingly so your
///< own code will never see those standard arguments.

bool init_check(int *argc, char ***argv);
///< Initialize the XFC library.
///< @param argc Address of the argc parameter of your main() function.
///< @param argv Address of the argv parameter of your main() function.
///< @return <EM>true</EM> if the GUI has been successfully initialized, <EM>false</EM> otherwise.
///<
///< This method does the same work as init() with only a single change: It does not
///< terminate the program if the GUI can't be initialized. Instead it returns <EM>false</EM>
///< on failure. This way the application can fall back to some other means of communication
///< with the user - for example a command line interface.

bool init_with_args(int *argc, char ***argv, const char *parameter_string, G::OptionGroup& group, G::Error *error);
///< Initialize the XFC library.
///< @param argc Address of the argc parameter of your main() function.
///< @param argv Address of the argv parameter of your main() function.
///< @param parameter_string The string to display in the first line of --help output, after programname [OPTION...]. 
///< @param group The option group describing the options of your program.
///< @param error The return location for errors. 
///< @return <EM>true</EM> if the GUI has been successfully initialized, <EM>false</EM> otherwise.
///<
///< This method does the same work as init_check(). Additionally, it allows you to add your own
///< commandline options, and it automatically generates nicely formatted --help output. Note that
///< your program will be terminated after writing out the help output.
///< 
///< <B>Example:</B> Initializing your application with optional commandline arguments
///< @code
///< int repeats = 2;
///< int max_size = 8;
///< bool verbose = false;
///< bool beep = false;
///< bool rand = false;
///<
///< int main (int argc, char *argv[])
///< {
///<     using namespace Main;
///<     G::OptionGroup group;
///<     group->add("repeats", 'r', &repeats, "Average over N repetitions", "N");
///<     group->add("max-size", 'm', &max_size, "Test up to 2^M items", "M");
///<     group->add("verbose", 'v', &verbose, "Be verbose");
///<     group->add("beep", 'b', &beep, "Beep when done");
///<     group->add("rand", 0, &rand, "Randomize the data");
///<
///<     G::Error error;
///<     init_with_args(&argc, &argv, "- test tree model performance", group, &error);
///<     ...
///< }
///< @endcode

void init_add(const sigc::slot<bool>& callback);
///< Register a slot to be called when the mainloop is started.
///< @param callback A slot to invoke when main() is called next.
///<
///< The callback slot should return false to remove it from the list of slots to call,
///< otherwise it might get called again.

#ifdef G_THREADS_ENABLED
void threads_init(GThreadFunctions *vtable = 0);
///< Before you use a thread related method, call this method to initialize the thread system.
///< @param vtable A function table of type GThreadFunctions, that provides the
///< entry points to the thread system to be used.
///<
///< This is a convenience method that calls both G::Thread::init() and gdk_threads_init().
///< G::Thread::init() initializes the GLib thread system and gdk_threads_init() initializes
///< GDK so that it can be used with multiple threads. After calling this method you can call
///< Gdk::Mutex::lock() and Gdk::Mutex::unlock() to lock and unlock critical sections of code.
///<
///< This method should only be called once. Most of the time you can just set vtable to null.
///< You should only call this method with a non-null argument if you really know what you are
///< doing. Do not call threads_init() directly or indirectly as a callback and make sure no
///< mutexes are locked when you make the call. After calling threads_init() the thread system
///< is initialized or the program will abort if no thread system is available in GLib (that is,
///< G_THREADS_IMPL_NONE is defined.
///<
///< If no thread system is available and vtable is null or if not all elements of vtable are
///< non-null, then threads::init() will abort. To Initialize the thread system with errorcheck
///< mutexes, vtable must be null and G_ERRORCHECK_MUTEXES must be defined.
#endif

/// @}
/// @name Accessors
/// @{

GOptionGroup* get_option_group(bool open_default_display = true);
///< Returns a GOptionGroup for the commandline arguments recognized by GTK+ and GDK.
///< @param open_default_display Whether to open the default display when parsing the commandline arguments. 
///< @return A GOptionGroup for the commandline arguments recognized by GTK+. 
///< 
///< You should add this group to your option context with G::OptionContext::add_group(),
///< if you are using G::OptionContext:::parse() to parse your commandline arguments.

PangoLanguage* default_language();
///< Get the default language currently in effect.
///< @return The ISO language code for the default language currently in effect.
///<
///< Note that this can change over the life of an application. The default language
///< is derived from the current locale. It determines, for example, whether XFC uses
///< the right-to-left or left-to-right text direction.

bool events_pending();
///< Checks if any events are pending.
///< @return <EM>true</EM> if any events are pending, <EM>false</EM> otherwise.
///<
///< This can be used to update the GUI and invoke timeouts etc. while doing
///< some time intensive computation.
///
///< <B>Example:</B> Updating the GUI during a long computation.
///< @code
///< // computation going on
///< ...
///< while (events_pending())
///< 	iterate();
///< ...
///< // computation continued
///< @endcode

Pointer<Gdk::Event> get_current_event();
///< Obtains a copy of the event currently being processed by GTK+. 
///< @return A copy of the current event, or null if there is no current event.
///<
///< For example, if you get a "clicked" signal from Gtk::Button, the current event
///< will be the Gdk::EventButton that triggered the "clicked" signal. If there is no 
///< current event, the function returns null.

unsigned int get_current_event_time();
///< If there is a current event and it has a timestamp, return that timestamp, 
///< otherwise return GDK_CURRENT_TIME.
///< @return The timestamp from the current event, or GDK_CURRENT_TIME.

bool get_current_event_state(Gdk::ModifierTypeField *state);
///< If there is a current event and it has a state field, place that state field in <EM>state</EM>
///< and return true, otherwise return false.
///< @param state The location to store the state of the current event. 
///< @return <EM>true</EM> if there was a current event and it had a state field. 

Gtk::Widget* get_event_widget(Gdk::Event& event);
///< Get the widget that originally received the <EM>event</EM>.
///< @param event A reference to a Gdk::Event.
///< @return The widget that originally received event, or null.
///<
///< If <EM>event</EM> is null or the event was not associated with any widget,
///< returns null, otherwise returns the widget that received the event originally.
///< The widget is returned as a smart pointer because there is the possiblity that
///< the widget was wrapped for the first time and needs to be unreferenced.

/// @}
/// @name Main Event Loop
/// @{

void run(Gtk::Window *main_window = 0);
///< Runs the main loop until quit() is called.
///< @param main_window The main application window, or null.
///<
///< If <EM>main_window</EM> is specified its "destroy" signal is automatically 
///< connected to the Main::quit() function and the window is made visible on 
///< the screen. If <EM>main_window</EM> is null you will have to manage showing
///< and destroying the main window yourself.
///<
///< You can nest calls to run(). In that case quit() will make the innermost
///< invocation of the main loop return.

int level();
///< Asks for the current nesting level of the main loop.
///< @return The nesting level of the current invocation of the main loop.
///<
///< This can be useful when connecting a slot to the <EM>quit_signal</EM>.

void quit();
///< Makes the innermost invocation of the main loop return when it regains control.

bool iterate(bool blocking = true);
///< Runs a single iteration of the mainloop.
///< @param blocking Set <EM>true</EM> if you want to block if no events are pending.
///< @return <EM>true</EM> if quit() has been called for the innermost mainloop.
///<
///< If <EM>blocking</EM> is true and no events are waiting to be processed XFC
///< will block until the next event is noticed. If <EM>blocking</EM> is false and
///< no events are available return.

void grab_add(Gtk::Widget& widget);
///< Makes <EM>widget</EM> the current grabbed widget.
///< @param widget The widget that grabs keyboard and pointer events.
///<
///<  This means that interaction with other widgets in the same application
///< is blocked and mouse as well as keyboard events are delivered to this widget.

Gtk::Widget* grab_get_current();
///< Queries the current grab.
///< @return The widget which currently has the grab or null if no grab is active.

void grab_remove(Gtk::Widget& widget);
///< Removes the grab from the given widget.
///< @param widget The widget which gives up the grab.
///< You have to pair calls to grab_add() and grab_remove().

/// @}
/// @name Signals
/// @{

/// @class QuitSignal main.hh xfc/main.hh
/// @brief Quit signal class.

class QuitSignal : public sigc::trackable
{
public:
	typedef sigc::slot<bool> SlotType;
	///< Function signature for handlers connected to this signal.

	sigc::connection connect(const SlotType& slot, unsigned int main_level = 0);
	///< Connect a slot to be called when an instance of the mainloop is left.
	///< @param slot The slot to call.
	///< @param main_level Level at which termination the slot shall be called.
	///< @return A connection object that can be used to break or alter the connection.
	///<
	///< You can pass 0 as the <EM>main_level</EM> to have your slot invoked at the
	///< termination of the current mainloop.
};

/// A namespace instance of the QuitSignal for connecting slots to be invoked at the
/// termination of the current mainloop.
extern QuitSignal quit_signal;

/// @class KeySnooperSignal main.hh xfc/main.hh
/// @brief KeySnooper signal class.

class KeySnooperSignal : public sigc::trackable
{
	std::vector<Connection*> connection_list;

public:
	typedef sigc::slot<bool, Gtk::Widget&, const Gdk::EventKey&> SlotType;
	///< Function signature for handlers connected to this signal.

	~KeySnooperSignal();
	///< Destructor.

	sigc::connection connect(const SlotType& slot);
	///< Connect a slot to be called on all key events before delivering them normally.
	///< @param slot The slot to call.
	///< @return A connection object that can be used to break or alter the connection.
	///<
	///< Connect a user function that will receive keypress events. It is the snooper's
	///< responsiblity to pass the keypress on to the widget, but care must taken that its
	///< not passed twice. The user function should return <EM>false</EM> to prevent further
	///< snooping.
};

/// A namespace instance of the KeySnooperSignal for connecting slots that will receive
/// keypress events.
extern KeySnooperSignal key_snooper_signal;

/// @}

} // namespace Main

} // namespace Xfc

/// XFC_MAIN is a convenience macro that writes a simple main function.

#define XFC_MAIN(MainWidget)\
int main (int argc, char *argv[])\
{\
	Xfc::Main::init(&argc, &argv);\
	MainWidget main_widget;\
	main_widget.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));\
	main_widget.show();\
	Xfc::Main::run();\
	return 0;\
}

#endif // XFC_MAIN_HH

