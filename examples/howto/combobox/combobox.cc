/*  ComboboxText Example
 *
 *  This example creates a combobox with a single list of text strings.
 *  It uses the convenience class Gtk::ComboBoxText which replaces the
 *  deprecated Gtk::OptionMenu. A more advanced combobox example can be
 *  found in the <tests/combobox> subdirectory which shows you how to 
 *  add images and use the new combobox grid mode.
 */
 
#include "combobox.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/treemodel.hh>
#include <iostream>

Window::Window()
: Gtk::WidgetSignals(this)
{
	set_title("ComboBox Example");	
	set_border_width(10);
	Gtk::VBox *vbox = new Gtk::VBox;
        add(*vbox);

	// A Gtk::ComboBoxText widget
        combobox = new Gtk::ComboBoxText;
	for (int i = 0; i < 6; i++)
	{
		String s = String::format("Item Number %i", i);
		combobox->append(s);       
	}
	combobox->set_active(0);
	vbox->add(*combobox);
	vbox->show_all();
}

Window::~Window()
{
}

bool 
Window::on_delete_event(const Gdk::EventAny&)
{
	Gtk::TreeIter iter;
	if (combobox->get_active_iter(iter))
	{
		String text;
		combobox->get_model()->get_value(iter, 0, text);	
		std::cout << "You selected: " << text << std::endl;
	}
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

