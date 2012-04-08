#include "actions.hh"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/eventbox.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/glib/error.hh>
#include <iostream>

// XML menu and toolbar description

static const char *ui_info = 
"<ui>"
"  <menubar name='MenuBar'>"
"    <menu action='File'>"
"      <menuitem action='New'/>"
"      <menuitem action='Open'/>"
"      <menuitem action='Save'/>"
"      <menuitem action='SaveAs'/>"
"      <separator/>"
"      <menuitem action='Quit'/>"
"    </menu>"
"    <menu action='Options'>"
"      <menuitem action='Test'/>"
"    </menu>"
"    <menu action='Help'>"
"      <menuitem action='About'/>"
"    </menu>"
"  </menubar>"
"  <toolbar  name='ToolBar'>"
"    <toolitem action='New'/>"
"    <toolitem action='Open'/>"
"    <toolitem action='Save'/>"
"    <toolitem action='SaveAs'/>"
"    <separator action='Sep1'/>"
"    <toolitem action='Quit'/>"
"  </toolbar>"
"</ui>";

ActionWindow::ActionWindow()
{
	set_title("Action Example");
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

	// Create the action group and add actions to it.	
	group = new Gtk::ActionGroup("Actions");
	add_actions();
	
	// Create the user interfcace anager	
	manager = new Gtk::UIManager;
	manager->insert_action_group(*group);
	add_accel_group(manager->get_accel_group());

	// Load XML description of the menus from a string.
	G::Error error;	
	if (!manager->add_ui_from_string(ui_info, -1, &error))
	{
		std::cout << "building menus failed: << " << error.message() << std::endl;
	}

	// Retrieve a pointer to the menubar.	
	Gtk::Widget *menubar = manager->get_widget("/MenuBar");
	vbox->pack_start(*menubar, false, false);
	
	// Retrieve a pointer to the toolbar.	
	Gtk::Toolbar *toolbar = static_cast<Gtk::Toolbar*>(manager->get_widget("/ToolBar"));
	toolbar->set_style(Gtk::TOOLBAR_ICONS);	
	toolbar->set_tooltips (true);
	vbox->pack_start(*toolbar, false, false);
	
	// Retrieve a pointer to the 'File' menu to use as the popup client menu.	
	Gtk::Menu *file_menu = static_cast<Gtk::Menu*>(manager->get_widget("/MenuBar/File/New")->get_parent());
	
	// Bind the file menu to the button_press event and use it as the popup menu.
	eventbox->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(this, &ActionWindow::on_button_press), file_menu));
	
	// Add a label that tells the user to click the mouse button inside the client area.
	Gtk::Label *label = new Gtk::Label("Click mouse button here...");
	vbox->pack_start(*label);

	// Show everything
	eventbox->show_all();
}

ActionWindow::~ActionWindow()
{
}

bool
ActionWindow::on_button_press(const Gdk::EventButton& event, Gtk::Menu *menu)
{
	menu->popup(event.button(), event.time());
	return true;
}

void
ActionWindow::menu_item_selected(const char *parent, const char *item)
{
	std::cout << "You activated the \"" << parent << "\" action: \"" << item << "\"" << std::endl;
}

void
ActionWindow::on_file_new()
{
	menu_item_selected("File", "New");
}

void
ActionWindow::on_file_open()
{
	menu_item_selected("File", "Open");
}

void
ActionWindow::on_file_save()
{
	menu_item_selected("File", "Save");
}

void
ActionWindow::on_file_save_as()
{
	menu_item_selected("File", "Save As");
}

void
ActionWindow::on_file_quit()
{
	dispose();
}

void
ActionWindow::on_options_test()
{
	menu_item_selected("Options", "Test");
}

void
ActionWindow::on_help_about()
{
	menu_item_selected("Help", "About");
}

void 
ActionWindow::add_actions()
{
	using namespace	Gtk;
	using namespace sigc;
	
	// Create Action menu entries	
	group->add("File", "_File");
	group->add("Options", "_Options");
	group->add("Help", "_Help");
	
	Action *action = group->add("New", "_New", StockId::NEW, AccelKey("<control>N"), "Create new file");	
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_file_new));
	action = group->add("Open", "_Open", StockId::OPEN, AccelKey("<control>O"), "Open file");
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_file_open));
	action = group->add("Save", "_Save", StockId::SAVE, AccelKey("<control>S"), "Save current file");
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_file_save));
	action = group->add("SaveAs", "Save _As", StockId::SAVE, "Save to file");
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_file_save_as));
	action = group->add("Quit", "_Quit", StockId::QUIT, AccelKey("<control>Q"), "Quit");	
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_file_quit));
	action = group->add("Test", "Test", "Test");	
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_options_test));
	action = group->add("About", "_About", AccelKey("<control>A"), "About");	
	action->signal_activate().connect(mem_fun(this, &ActionWindow::on_help_about));
}

XFC_MAIN(ActionWindow)

