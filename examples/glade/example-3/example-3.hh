/* This program displays a couple checkbuttons and shows how to change button labels,
 * how to make widgets sensitive or insensitive, how to determine if a checkbutton
 * is active, how to retrieve a widget pointer and connect it to a signal handler, and
 * how to manually get GTK+ to update widgets without returning to the main event loop.
 *
 * XFC translation of Example-3 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include <xfc/main.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/window.hh>
#include <xfc/glade/xml.hh>

using namespace Xfc;

class OptionWindow : public Gtk::Window
{
	Gtk::CheckButton *ooh_tell_me;
	Gtk::CheckButton *sensitivity;
	Gtk::Button *quit_button;
	
protected:
	bool on_delete_event(const Gdk::EventAny& event);
	void on_sensitivity_toggled();
	void quit();

public:
	OptionWindow(CObjectType *object, const Glade::Xml& xml);
};

