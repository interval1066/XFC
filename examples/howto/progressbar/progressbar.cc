#include "progressbar.hh"
#include <xfc/gtk/alignment.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/separator.hh>
#include <xfc/gtk/table.hh>
#include <xfc/glib/main.hh>

ProgressBarWindow::ProgressBarWindow()
: activity_mode(false)
{
	set_resizable(true);
	set_title("ProgressBar Example");
	set_border_width(0);

	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	vbox->set_border_width(10);
	add(*vbox);
	vbox->show();

	// Create a centering alignment object
	Gtk::Alignment *align = new Gtk::Alignment(0.5, 0.5);
	vbox->pack_start(*align, false, false, 5);
	align->show();

	// Create the GtkProgressBar
	progress_bar = new Gtk::ProgressBar;
	align->add(*progress_bar);
	progress_bar->show();

	// Add a timer callback to update the value of the progress bar
	timeout_connection = G::timeout_signal.connect(sigc::mem_fun(this, &ProgressBarWindow::on_timeout), 100);

	Gtk::HSeparator *separator = new Gtk::HSeparator;
	vbox->pack_start(*separator, false, false);
	separator->show();

	// Add table: rows, columns, homogeneous = false (by default)
	Gtk::Table *table = new Gtk::Table(2, 2);
	vbox->pack_start(*table, false);
	table->show();

	// Add a check button to select displaying of the trough text
	Gtk::CheckButton *check = new Gtk::CheckButton("Show text");
	table->attach(*check, 0, 1, 0, 1, Gtk::EXPAND | Gtk::FILL, Gtk::EXPAND | Gtk::FILL, 5, 5);
	check->signal_clicked().connect(sigc::mem_fun(this, &ProgressBarWindow::on_toggle_show_text));
	check->show();

	// Add a check button to toggle activity mode
	check = new Gtk::CheckButton("Activity mode");
	table->attach(*check, 0, 1, 1, 2, Gtk::EXPAND | Gtk::FILL, Gtk::EXPAND | Gtk::FILL, 5, 5);
	check->signal_clicked().connect(sigc::mem_fun(this, &ProgressBarWindow::on_toggle_activity_mode));
	check->show();

	// Add a check button to toggle orientation
	check = new Gtk::CheckButton("Right to Left");
	table->attach(*check, 0, 1, 2, 3, Gtk::EXPAND | Gtk::FILL, Gtk::EXPAND | Gtk::FILL, 5, 5);
	check->signal_clicked().connect(sigc::mem_fun(this, &ProgressBarWindow::on_toggle_orientation));
	check->show();

	// Add a button to exit the program
	Gtk::Button *button = new Gtk::Button("close");
	button->signal_clicked().connect(sigc::mem_fun(this, &ProgressBarWindow::dispose));
	vbox->pack_start(*button, false, false);

	// This makes it so the button is the default.
	button->set_flags(Gtk::CAN_DEFAULT);

	// This grabs this button to be the default button. Simply hitting the "Enter" key
	// will cause this button to activate.
	button->grab_default();
	button->show();
}

ProgressBarWindow::~ProgressBarWindow()
{
	timeout_connection.disconnect();
}

bool
ProgressBarWindow::on_timeout()
{
	if (activity_mode)
		progress_bar->pulse();
	else
	{
		// Calculate the value of the progress bar using the value range set in the adjustment object
		double new_value = progress_bar->get_fraction() + 0.01;

		if (new_value > 1.0)
			new_value = 0.0;

		// Set the new value
		progress_bar->set_fraction(new_value);
	}

	// As this is a timeout sigc::mem_fun, return true so that it continues to get called
	return true;
}

void
ProgressBarWindow::on_toggle_show_text()
{
	// Toggles the text display within the progress bar trough
	String text = progress_bar->get_text();

	if (!text.empty())
		progress_bar->set_text("");
	else
		progress_bar->set_text("some text");
}

void
ProgressBarWindow::on_toggle_activity_mode()
{
	// Toggles the activity mode of the progress bar
	activity_mode = !activity_mode;

	if (activity_mode)
		progress_bar->pulse();
	else
		progress_bar->set_fraction(0.0);
}

void
ProgressBarWindow::on_toggle_orientation()
{
	// Toggles the orientation of the progress bar
	if (progress_bar->get_orientation() == Gtk::PROGRESS_LEFT_TO_RIGHT)
		progress_bar->set_orientation(Gtk::PROGRESS_RIGHT_TO_LEFT);
	else
		progress_bar->set_orientation(Gtk::PROGRESS_LEFT_TO_RIGHT);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ProgressBarWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

