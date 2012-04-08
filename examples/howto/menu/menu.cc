#include "menu.hh"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/eventbox.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/menuitem.hh>

MenuWindow::MenuWindow()
{
	set_title("Menu Window");
	set_size_request(300, 200);

	// Boxes don't receive button events so use an eventbox. The eventbox is added first
	// and then all the other widgets added to it.
	Gtk::EventBox *eventbox = new Gtk::EventBox;
	add(*eventbox);

	// Set the events the eventbox is to receive. These can be any number of or'd (|) values
	// from the Gdk::EventMask enumeration.
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);

	// Add the packing box to eventbox
	Gtk::VBox *vbox = new Gtk::VBox(false, 1);
	vbox->set_border_width(1);
	eventbox->add(*vbox);

	// Create the menubar. Menus can be created by using the append, prepend or insert methods
	// in menushell.h to add menu items.
	Gtk::MenuBar *menubar = new Gtk::MenuBar;
	Gtk::AccelGroup *accel_group = add_accel_group();

	// Create the File menu
	Gtk::Menu *menu = new Gtk::Menu(*accel_group);
	menu->append(*(new Gtk::MenuItem("_New", true)), "<control>N", sigc::mem_fun(this, &MenuWindow::on_file_new));
	menu->append(*(new Gtk::MenuItem("_Open", true)), "<control>O", sigc::mem_fun(this, &MenuWindow::on_file_open));
	menu->append(*(new Gtk::MenuItem("_Save", true)), "<control>S", sigc::mem_fun(this, &MenuWindow::on_file_save));
	menu->append(*(new Gtk::MenuItem("Save _As", true)), sigc::mem_fun(this, &MenuWindow::on_file_save_as));
	menu->append_separator();
	menu->append(*(new Gtk::MenuItem("_Quit", true)), "<control>Q", sigc::mem_fun(this, &MenuWindow::on_file_quit));
	menubar->append(*(new Gtk::MenuItem("_File", *menu, true)));

	// Bind the file menu to the button_press event and use it as the popup menu.
	eventbox->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(this, &MenuWindow::on_button_press), menu));

	// Create Options menu
	menu = new Gtk::Menu;
	menu->append(*(new Gtk::MenuItem("_Preferences", true)), sigc::mem_fun(this, &MenuWindow::on_options_preferences));
	menubar->append(*(new Gtk::MenuItem("_Options", *menu, true)));

	// Create Help menu
	menu = new Gtk::Menu;
	menu->append(*(new Gtk::MenuItem("About")), sigc::mem_fun(this, &MenuWindow::on_help_about));
	Gtk::MenuItem *menu_item = new Gtk::MenuItem("_Help", *menu, true);
	menu_item->set_right_justified(true);
	menubar->append(*menu_item);
	
	// Pack the menubar into the vbox
	vbox->pack_start(*menubar, false);

	// Add a label that tells the user to click the mouse button inside the client area.
	Gtk::Label *label = new Gtk::Label("Click mouse button here...");
	vbox->pack_start(*label);

	// Being lazy, just show everything with one call.
	show_all();
}

MenuWindow::~MenuWindow()
{
}

bool
MenuWindow::on_button_press(const Gdk::EventButton& event, Gtk::Menu *menu)
{
	menu->popup(event.button(), event.time());
	return true;
}

void
MenuWindow::menu_item_selected(const char *parent, const char *item)
{
	g_message("Menu: activated the \"%s\" menu item: \"%s\"", parent, item);
}

void
MenuWindow::on_file_new()
{
	menu_item_selected("File", "New");
}

void
MenuWindow::on_file_open()
{
	menu_item_selected("File", "Open");
}

void
MenuWindow::on_file_save()
{
	menu_item_selected("File", "Save");
}

void
MenuWindow::on_file_save_as()
{
	menu_item_selected("File", "Save As");
}

void
MenuWindow::on_file_quit()
{
	dispose();
}

void
MenuWindow::on_options_preferences()
{
	menu_item_selected("Options", "Preferences");
}

void
MenuWindow::on_help_about()
{
	menu_item_selected("Help", "About");
}

// Convenience macro for a simple main function

XFC_MAIN(MenuWindow)

