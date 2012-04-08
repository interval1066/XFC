#include "statusbar.hh"
#include <xfc/glib/main.hh>
#include <gconf/gconf-client.h>

Statusbar::Statusbar(bool show_progress)
: activity_mode_(false)
{
	progress_bar_ = new Gtk::ProgressBar;

	// Use the GNOME value for 'status_bar_meter_on_right' to place the progress bar.
	GConfClient *client = gconf_client_get_default();
	if (!gconf_client_get_bool(client, "/desktop/gnome/interface/status_bar_meter_on_right", 0))
		insert_start(*progress_bar_, 0, false, false);
	else
	{
		pack_end(*progress_bar_, false, false);
		set_has_resize_grip(false);
	}
	
	set_spacing(4);
	if (show_progress)	
		progress_bar_->show();
	g_object_unref(client);
}

Statusbar::~Statusbar()
{
}

bool
Statusbar::on_timeout()
{
	// If actvivity mode is true just pulse the progress bar, otherwise emit the "update_progress" signal.	
	if (activity_mode_)
		progress_bar_->pulse();
	else
		update_progress_signal.emit();
	
	return true;
}

Gtk::ProgressBar*
Statusbar::progress_bar() const
{
	return progress_bar_;
}

void 
Statusbar::begin_progress(unsigned int interval, bool activity_mode)
{
	// Add a timer callback to update the value of the progress bar
	timeout_connection = G::timeout_signal.connect(sigc::mem_fun(this, &Statusbar::on_timeout), interval);
	activity_mode_ = activity_mode;
}

void
Statusbar::set_progress(double fraction)
{
	progress_bar_->set_fraction(fraction);
}

void 
Statusbar::end_progress()
{
	// Remove timeout callback
	timeout_connection.disconnect();
}

void 
Statusbar::push(const String& text)
{
	Gtk::Statusbar::push(text);
}

void 
Statusbar::pop()
{
	Gtk::Statusbar::pop();
}

