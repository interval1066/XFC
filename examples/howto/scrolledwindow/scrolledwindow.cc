#include "scrolledwindow.hh"
#include <xfc/gtk/buttonbox.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/togglebutton.hh>

ScrolledWindow::ScrolledWindow()
{
	set_title("ScrolledWindow Example");
	set_border_width(0);
	set_size_request(300, 300);
    
	// Create a new scrolled window.
	Gtk::ScrolledWindow *scrolled_window = new Gtk::ScrolledWindow;
	scrolled_window->set_border_width(10);
    
	// The policy is one of Gtk::POLICY AUTOMATIC, or Gtk::POLICY_ALWAYS. Gtk::POLICY_AUTOMATIC will 
	// automatically decide whether you need scrollbars, whereas Gtk::POLICY_ALWAYS will always leave
	// the scrollbars there.  The first one is the horizontal scrollbar, the second, the vertical.
	scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
	
	// The dialog window is created with a vbox (client_area) packed into it.								
	client_area()->pack_start(*scrolled_window);
	scrolled_window->show();
    
	Gtk::Table *table = new Gtk::Table(10, 10);
    
	// Set the spacing to 10 on x and 10 on y
	table->set_row_spacings(10);
	table->set_col_spacings(10);
	
	// Pack the table into the scrolled window
	scrolled_window->add_with_viewport(*table);
	table->show();
    
	// This simply creates a grid of toggle buttons on the table to demonstrate the scrolled window.
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) 
		{
			String text = String::format("button (%d,%d)\n", i, j);
			Gtk::ToggleButton *button = new Gtk::ToggleButton(text);
			table->attach(*button, i, i + 1, j, j + 1);
			button->show();
		}
	}
    
	// Add a "close" button to the bottom of the dialog
	Gtk::Button *button = new Gtk::Button("close");
	button->signal_clicked().connect(sigc::mem_fun(this, &ScrolledWindow::dispose));
	
	// This makes it so the button is the default.
	button->set_flags(Gtk::CAN_DEFAULT);
	action_area()->pack_start(*button);

	// This grabs this button to be the default button. Simply hitting the "Enter" key will activate this button.
	button->grab_default();
	button->show();
}

ScrolledWindow::~ScrolledWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ScrolledWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}
