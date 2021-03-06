#include "xfcapp.hh"
#include "xfcapp.ui"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/eventbox.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/menuitem.hh>
#include <xfc/gtk/stock.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/glib/error.hh>
#include <gconf/gconf-client.h>
#include <iostream>

XfcApp::XfcApp()
{
	// Set the window title and default size	
	set_title("XfcApp");
	set_default_size(400, 300);
	
	// Create the action group and add the actions
	action_group = new Gtk::ActionGroup("XfcAppActions");
	add_actions();	
	
	// Create the user interface manager and insert the action group	
	manager = new Gtk::UIManager;
	manager->insert_action_group(*action_group);
	manager->signal_connect_proxy().connect(sigc::mem_fun(this, &XfcApp::install_menu_hints));
	
	// Associate the user interface manager's AccelGroup with the window
	add_accel_group(manager->get_accel_group());
	
	// Create main vertical box and add to window	
	Gtk::VBox *main_vbox = new Gtk::VBox;
	add(*main_vbox);
	
	// Create custom statusbar (before loading XML description) and pack it at the end of main_vbox	
	statusbar_ = new Statusbar(true);
	main_vbox->pack_end(*statusbar_, false);
	statusbar_->show();
	
	// Load XML description of the menus and toolbar from a definition string.
	G::Error error;	
	if (!manager->add_ui_from_string(ui_info, -1, &error))
	{
		std::cout << "building menus and toolbar failed: << " << error.message() << std::endl;
	}

	// Get a pointer to the menubar and pack it into main_vbox	
	Gtk::Widget *menubar = manager->get_widget("/MenuBar");
	main_vbox->pack_start(*menubar, false);	
	menubar->show();
	
	// Get a pointer to the toolbar and pack it into main_vbox	
	Gtk::Toolbar *toolbar = static_cast<Gtk::Toolbar*>(manager->get_widget("/ToolBar"));
	toolbar->set_tooltips(true);
	main_vbox->pack_start(*toolbar, false);
	toolbar->show();
	
	// Use the GNOME value for 'toolbar_style' to place the progress bar.
	GConfClient *client = gconf_client_get_default();
	String text = gconf_client_get_string(client, "/desktop/gnome/interface/toolbar_style", 0);
	Gtk::ToolbarStyle toolbar_style;
	if (text.compare("text") == 0)
		toolbar_style = Gtk::TOOLBAR_TEXT;
	else if (text.compare("both") == 0)
		toolbar_style = Gtk::TOOLBAR_BOTH;
	else if (text.compare("both_horiz") == 0)
		toolbar_style = Gtk::TOOLBAR_BOTH_HORIZ;
	else
		toolbar_style = Gtk::TOOLBAR_ICONS;
	toolbar->set_style(toolbar_style);

	// Boxes don't receive button events so use an eventbox first and add all other widgets to this.
	Gtk::EventBox *eventbox = new Gtk::EventBox;
	main_vbox->pack_start(*eventbox);
	eventbox->show();

	// Set the events the eventbox is to receive. These can be one or more values from Gdk::EventMask.
	eventbox->set_events(Gdk::BUTTON_PRESS_MASK);
	
	// Add a vertical packing box to eventbox for the client area.
	Gtk::VBox *client_vbox = new Gtk::VBox;
	eventbox->add(*client_vbox);
	client_vbox->show();
	
	// As an example bind the file menu to the button_press event and use it as the popup menu.
	Gtk::MenuItem *item = static_cast<Gtk::MenuItem*>(manager->get_widget("/MenuBar/FileMenu"));
	Gtk::Menu *menu = item->get_submenu();
	eventbox->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(this, &XfcApp::on_button_press), menu));
	
	// Show main_vbox so it's visible	
	main_vbox->show();

	// As an example, set the progress bar to pulse	
	statusbar_->begin_progress(100, true);
}

XfcApp::~XfcApp()
{
	statusbar_->end_progress();
}

void
XfcApp::add_actions()
{
	using namespace Gtk;
	using namespace sigc;

	action_group->add("FileMenu", "_File");
	action_group->add("EditMenu", "_Edit");
	action_group->add("HelpMenu", "_Help");

	Action *action = action_group->add("New", "_New", StockId::NEW, AccelKey("<control>N"), "Create a new file");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_new));
	action = action_group->add("Open", "_Open", StockId::OPEN, AccelKey("<control>O"), "Open a file");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_open));
	action = action_group->add("Save", "_Save", StockId::SAVE, AccelKey("<control>S"), "Save current file");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_save));
	action = action_group->add("SaveAs", "Save _As...", StockId::SAVE, "Save to a file");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_save_as));
	action = action_group->add("Quit", "_Quit", StockId::QUIT, AccelKey("<control>Q"), "Quit");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_quit));
	action = action_group->add("Cut", "C_ut", StockId::CUT, AccelKey("<control>X"), "Cut the selection");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_cut));
	action = action_group->add("Copy", "_Copy", StockId::COPY, AccelKey("<control>C"), "Copy the selection");
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_copy));
	action = action_group->add("Paste", "_Paste", StockId::PASTE, AccelKey("<control>V"), "Paste the clipboard");
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_paste));
	action = action_group->add("Clear", "C_lear", StockId::CLEAR, "Clear the selection");
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_clear));
	action = action_group->add("Preferences", "Prefere_nces", StockId::PREFERENCES, "Configure the application");
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_preferences));
	action = action_group->add("About", "_About", AccelKey("<control>A"), "About");	
	action->signal_activate().connect(mem_fun(this, &XfcApp::on_help_about));
}

void
XfcApp::install_menu_hints(Gtk::Action& action, Gtk::Widget& widget)
{
	using namespace sigc;
		
	if (!widget.is_a(GTK_TYPE_MENU_ITEM))
		return;
		
	Gtk::MenuItem& item = static_cast<Gtk::MenuItem&>(widget);
	String tooltip = action.property_tooltip();
	item.signal_select().connect(bind(mem_fun(statusbar_, &Statusbar::push), tooltip));
	item.signal_deselect().connect(mem_fun(statusbar_, &Statusbar::pop));
}

bool
XfcApp::on_button_press(const Gdk::EventButton& event, Gtk::Menu *menu)
{
	if (event.button() == 3)
		menu->popup(event.button(), event.time());
	return true;
}

void 
XfcApp::on_file_new()
{
	std::cout << "You activated action: New" << std::endl;
}

void 
XfcApp::on_file_open()
{
	std::cout << "You activated action: Open" << std::endl;
}

void 
XfcApp::on_file_save()
{
	std::cout << "You activated action: Save" << std::endl;
}

void 
XfcApp::on_file_save_as()
{
	std::cout << "You activated action: SaveAs" << std::endl;
}

void 
XfcApp::on_file_quit()
{
	dispose();
}

void 
XfcApp::on_edit_cut()
{
	std::cout << "You activated action: Cut" << std::endl;
}

void 
XfcApp::on_edit_copy()
{
	std::cout << "You activated action: Copy" << std::endl;
}

void 
XfcApp::on_edit_paste()
{
	std::cout << "You activated action: Paste" << std::endl;
}

void 
XfcApp::on_edit_clear()
{
	std::cout << "You activated action: Clear" << std::endl;
}

void 
XfcApp::on_edit_preferences()
{
	std::cout << "You activated action: Preferences" << std::endl;
}

void 
XfcApp::on_help_about()
{
	std::cout << "You activated action: About" << std::endl;
}

