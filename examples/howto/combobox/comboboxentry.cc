/*  ComboBoxEntryText Example
 *
 *  This example creates a combo box widget with a single list of text strings 
 *  that can be edited. It uses Gtk::ComboBoxEntryText. Alternatively, it could
 *  use Gtk::ComboBoxEntry and create the text model itself. A more advanced 
 *  combobox example can be found in the <tests/combobox>  subdirectory which
 *  shows you how to add images and use the new combobox grid mode.
 */

#include "comboboxentry.hh"
#include <xfc/gtk/box.hh>
#include <iostream>

ComboBoxEntry::ComboBoxEntry()
{
	set_text_column(0);
	for (int i = 0; i < 6; i++)
	{
		String s = String::format("Item Number %i", i);
		append(s);       
	}
	set_active(3);
}

Window::Window()
: Gtk::WidgetSignals(this)
{
	set_title("ComboBoxEntry Example");	
	set_border_width(10);
	Gtk::VBox *vbox = new Gtk::VBox;
        add(*vbox);

	// A Gtk::ComboBoxEntryText widget
        combobox = new ComboBoxEntry;
	vbox->add(*combobox);
	vbox->show_all();
}

Window::~Window()
{
}

bool 
Window::on_delete_event(const Gdk::EventAny&)
{
	std::cout << "You entered: " << combobox->get_text() << std::endl;
	return false;
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

