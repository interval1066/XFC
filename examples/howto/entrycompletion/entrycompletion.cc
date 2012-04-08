/*  Entry completion example
 *
 *  This example shows you how to add a completion object to an entry widget. It is a 
 *  very simple example. A more advanced example showing you how to handle images and 
 *  dynamic entry completion can be found in the <tests/entrycompletion> subdirectory. 
 */
 
#include "entrycompletion.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/entrycompletion.hh>
#include <xfc/gtk/label.hh>
#include <iostream>

CompletionModel::CompletionModel()
: Gtk::ListStore(1, G_TYPE_STRING)
{
	// Fill the list with possible completions    
	Gtk::TreeIter iter = append();
	set_value(iter, 0, "total");
	iter = append();
	set_value(iter, 0, "totally");
	iter = append();
	set_value(iter, 0, "toto");
	iter = append();
	set_value(iter, 0, "tottery");
	iter = append();
	set_value(iter, 0, "totterer");
	iter = append();
	set_value(iter, 0, "totipotent");
	iter = append();
	set_value(iter, 0, "totipotency");
	iter = append();
	set_value(iter, 0, "totemism");
	iter = append();
	set_value(iter, 0, "totem pole");
	iter = append();
	set_value(iter, 0, "Totara");
	iter = append();
	set_value(iter, 0, "totalizer");
	iter = append();
	set_value(iter, 0, "totalizator");
	iter = append();
	set_value(iter, 0, "totalitarianism");
	iter = append();
}

Window::Window()
{
	set_title("Completion Example");
	set_border_width(5);
	
        Gtk::VBox *vbox = new Gtk::VBox(false, 2);
	vbox->set_border_width(5);
	add(*vbox);
	
	Gtk::Label *label = new Gtk::Label;
	label->set_markup("Try entering <b>total</b> for example:");
	vbox->pack_start(*label, false, false);
	
	// Add entry widget
	Gtk::Entry *entry = new Gtk::Entry;
	vbox->pack_start(*entry, false, false);
	
	// Create the completion model
	Pointer<Gtk::ListStore> completion_model = new CompletionModel;

	// Create the completion object. 
	Gtk::EntryCompletion *completion = entry->create_completion(*completion_model);
	
	// Use model column 0 as the text column
	completion->set_text_column(0);

	// Show everything	
	vbox->show_all();
}

Window::~Window()
{
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

