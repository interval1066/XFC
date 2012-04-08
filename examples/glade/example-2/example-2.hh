/* This program displays a "pulsing" progress bar, adds a timeout function to keep
 * it updated, shows how to obtain an individual widget that libglade created, and
 * overrides the main window's "delete_event" signal handler so that a G::Timer can 
 * be attached to it to report the time wasted.
 *
 * XFC translation of Example-2 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include <xfc/main.hh>
#include <xfc/gtk/progressbar.hh>
#include <xfc/gtk/window.hh>
#include <xfc/glib/timer.hh>
#include <xfc/glade/xml.hh>

using namespace Xfc;

class WasteTimeWindow : public Gtk::Window
{
	Pointer<G::Timer> wasted_time_tracker;	
	Gtk::ProgressBar *progress_bar;
	sigc::connection timeout_connection;

protected:
	bool on_delete_event(const Gdk::EventAny& event);
	bool on_timeout();

public:
	WasteTimeWindow(CObjectType *object, const Glade::Xml& xml);
	virtual ~WasteTimeWindow();
};

