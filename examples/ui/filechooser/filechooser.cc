#include "filechooser.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/stockid.hh>
#include <iostream>

FileDialog::FileDialog()
: Gtk::FileChooserDialog("Open...", Gtk::FILE_CHOOSER_ACTION_OPEN)
{
	// Add OK and 'Cancel' buttons.	
	button = add_button(Gtk::STOCK_BUTTON_CANCEL);
	button->signal_clicked().connect(sigc::mem_fun(this, &FileDialog::dispose));
	button = add_button(Gtk::STOCK_BUTTON_OK);
	button->signal_clicked().connect(sigc::mem_fun(this, &FileDialog::on_ok));
	
	// Add a Gtk::HBox as the extra widet.	
	Gtk::HBox *hbox = new Gtk::HBox;
	Gtk::Label *label = new Gtk::Label;
	label->set_markup("<i><u>Properties:</u></i>   ");
	hbox->pack_start(*label, false, false);
	
	// Add 'show hidden' and 'select multiple' check boxes to the extra widget.	
	Gtk::CheckButton *check = new Gtk::CheckButton("Show Hidden");
	check->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &FileDialog::on_toggled_show_hidden), check)); 
	hbox->pack_start(*check, false, false);
	check = new Gtk::CheckButton("Muliple Select");
	check->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &FileDialog::on_toggled_select_multiple), check)); 
	hbox->pack_start(*check, false, false, 10);
	
	// Add FileChooser actions 'Open' and 'Save'.	
	Gtk::ComboBoxText *combobox = new Gtk::ComboBoxText;
	combobox->append("Gtk::FILE_CHOOSER_ACTION_OPEN");	
	combobox->append("Gtk::FILE_CHOOSER_ACTION_SAVE");	
	combobox->set_active(0);
	combobox->signal_changed().connect(sigc::bind(sigc::mem_fun(this, &FileDialog::on_action_changed), combobox));
	hbox->pack_start(*combobox, true, true);
		
	// Set the extra widget.	
	set_extra_widget(*hbox);
	hbox->show_all();
}

FileDialog::~FileDialog()
{
}

void
FileDialog::on_ok()
{	
	std::cout << get_filename().c_str() << std::endl;
}

void
FileDialog::on_toggled_show_hidden(Gtk::CheckButton *check_button)
{
	set_show_hidden(check_button->get_active());
}

void 
FileDialog::on_toggled_select_multiple(Gtk::CheckButton *check_button)
{
	set_select_multiple(check_button->get_active());
}

void
FileDialog::on_action_changed(Gtk::ComboBox *combobox)
{
	Gtk::FileChooserAction action = static_cast<Gtk::FileChooserAction>(combobox->get_active());
	set_action(action);
	if (action == Gtk::FILE_CHOOSER_ACTION_OPEN)
		set_title("Open...");
	else
		set_title("Save as...");
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	FileDialog dialog;
	dialog.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	dialog.show();

	run();
	return 0;
}

