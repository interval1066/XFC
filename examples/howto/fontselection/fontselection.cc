#include "fontselection.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/fontselection.hh>
#include <xfc/pango/font.hh>
#include <iostream>

FontSelectionWindow::FontSelectionWindow()
{
	// Sets the border width of the window.
	set_title("Font Selecton Example");
	set_border_width(10);

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);

	// Create a label and add it to the vbox
	label = new Gtk::Label("Welcome to XFC");
	label->set_size_request(300, 100);
	vbox->pack_start(*label);

	// Creates a new button and add it to the vbox
	Gtk::Button *button = new Gtk::Button("Select a font");
	vbox->pack_start(*button);

	// When the button receives the "clicked" signal, it calls the on_select_font() slot.
	button->signal_clicked().connect(sigc::mem_fun(this, &FontSelectionWindow::on_select_font));

	// The final step is to display this newly created widgets.
	vbox->show_all();
}

FontSelectionWindow::~FontSelectionWindow()
{
}

void
FontSelectionWindow::on_select_font()
{
	// Create a temporary FontSelectionDialog on the stack
	Gtk::FontSelectionDialog dialog("Select a font");

	// Call Gtk::Dialog::run() which runs a modal dialog
	if (dialog.run())
	{
		// Get the selected font name
		String font_name = dialog.get_font_name();

		// Print the font name to the standard output
		std::cout << "The selected font name is \"" << font_name << "\"" << std::endl;
		
		// Modify the label's font and destroy the dialog
		Pango::FontDescription font_desc(font_name);
		label->modify_font(&font_desc);
		dialog.dispose();
	}
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	FontSelectionWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

