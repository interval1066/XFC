/* UI Manager
 *
 * The Gtk::UIManager object allows the easy creation of menus from
 * a list of actions and an XML description of the menu hierarchy.
 */

#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/separator.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/uimanager.hh>
#include <xfc/glib/error.hh>
#include <iostream>

using namespace Xfc;

class UIManagerWindow : public Gtk::Window
{
	Pointer<Gtk::ActionGroup> group;
	Pointer<Gtk::UIManager> manager;

	void add_actions();

protected:	
	bool on_delete_event(const Gdk::EventAny& event);
	void on_activate_action(Gtk::Action *action);
	void on_activate_radio_action(Gtk::RadioAction& current);

public:
	UIManagerWindow();
	~UIManagerWindow();
};
//!

enum 
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE
};

enum 
{
	SHAPE_SQUARE,
	SHAPE_RECTANGLE,
	SHAPE_OVAL
};

static const char *ui_info = 
"<ui>"
"  <menubar name='MenuBar'>"
"    <menu action='FileMenu'>"
"      <menuitem action='New'/>"
"      <menuitem action='Open'/>"
"      <menuitem action='Save'/>"
"      <menuitem action='SaveAs'/>"
"      <separator/>"
"      <menuitem action='Quit'/>"
"    </menu>"
"    <menu action='PreferencesMenu'>"
"      <menu action='ColorMenu'>"
"	<menuitem action='Red'/>"
"	<menuitem action='Green'/>"
"	<menuitem action='Blue'/>"
"      </menu>"
"      <menu action='ShapeMenu'>"
"        <menuitem action='Square'/>"
"        <menuitem action='Rectangle'/>"
"        <menuitem action='Oval'/>"
"      </menu>"
"      <menuitem action='Bold'/>"
"    </menu>"
"    <menu action='HelpMenu'>"
"      <menuitem action='About'/>"
"    </menu>"
"  </menubar>"
"</ui>";

UIManagerWindow::UIManagerWindow()
{
	set_title("UI Manager");
	set_border_width(0);
	signal_delete_event().connect(sigc::mem_fun(this, &UIManagerWindow::on_delete_event));
	
	// Create action group and add actions	
	group = new Gtk::ActionGroup("Actions");
	add_actions();
	
	// Create user interface manager	
	manager = new Gtk::UIManager;
	manager->insert_action_group(*group);
	add_accel_group(manager->get_accel_group());
	
	// Load XML description of the menus from a string.
	G::Error error;	
	if (!manager->add_ui_from_string(ui_info, -1, &error))
	{
		std::cout << "building menus failed: << " << error.message() << std::endl;
	}
	
	Gtk::VBox *box1 = new Gtk::VBox;
	add(*box1);
	
	// Get a pointer to the menubar widget	
	Gtk::Widget *menubar = manager->get_widget("/MenuBar");
	box1->pack_start(*menubar, false, false);
	
	Gtk::Label *label = new Gtk::Label("Type\n<alt>\nto start");
	label->set_size_request(200, 200);
	label->set_alignment(0.5, 0.5);
	box1->pack_start(*label);
	
	Gtk::HSeparator *separator = new Gtk::HSeparator;
	box1->pack_start(*separator, false);
	
	Gtk::VBox *box2 = new Gtk::VBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2, false);
	
	Gtk::Button *button = new Gtk::Button("Close");
	button->signal_clicked().connect(sigc::mem_fun(this, &UIManagerWindow::dispose));
	box2->pack_start(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	show_all();
}

UIManagerWindow::~UIManagerWindow()
{
}

bool 
UIManagerWindow::on_delete_event(const Gdk::EventAny& event)
{
	return true;
}

void
UIManagerWindow::on_activate_action(Gtk::Action *action)
{
	std::cout << "Action \"" << action->get_name() << "\" activated" << std::endl;
}

void
UIManagerWindow::on_activate_radio_action(Gtk::RadioAction& current)
{
	std::cout << "Radio action \"" << current.get_name() << "\" selected" << std::endl;
}

void
UIManagerWindow::add_actions()
{
	using namespace	Gtk;
	using namespace sigc;
	
	// Create Action menu entries	
	group->add("FileMenu", "_File");
	group->add("PreferencesMenu", "_Preferences");
	group->add("ColorMenu", "_Color");
	group->add("ShapeMenu", "_Shape");
	group->add("HelpMenu", "_Help");

	// Create Action entries	
	Action *action = group->add("New", "_New", StockId::NEW, AccelKey("<control>N"), "Create a new file");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));
	action = group->add("Open", "_Open", StockId::OPEN, AccelKey("<control>O"), "Open a file");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));
	action = group->add("Save", "_Save", StockId::SAVE, AccelKey("<control>S"), "Save current file");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));
	action = group->add("SaveAs", "Save _As...", StockId::SAVE, "Save to a file");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));
	action = group->add("Quit", "_Quit", StockId::SAVE, AccelKey("<control>Q"), "Quit");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));
	action = group->add("About", "_About", AccelKey("<control>A"), "About");	
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));

	// Create ToggleAction entries	
	action = group->add("Bold", "_Bold", StockId::BOLD, AccelKey("<control>B"), true, "Bold");
	action->signal_activate().connect(bind(mem_fun(this, &UIManagerWindow::on_activate_action), action));

	// Create RadioAction color entries
	RadioActions ras;
	ras.add("Red", "_Red", AccelKey("<control>R"), COLOR_RED, "Blood"),
	ras.add("Green", "_Green", AccelKey("<control>G"), COLOR_GREEN, "Grass");
	ras.add("Blue", "_Blue", AccelKey("<control>B"), COLOR_BLUE, "Center justify the text");
	group->add_actions(ras, COLOR_GREEN, mem_fun(this, &UIManagerWindow::on_activate_radio_action));	

	// Create RadioAction shape entries
	ras.clear();
	ras.add("Square", "_Square", AccelKey("<control>S"), SHAPE_SQUARE, "Square"),
	ras.add("Rectangle", "_Rectangle", AccelKey("<control>R"), SHAPE_RECTANGLE, "Rectangle");
	ras.add("Oval", "_Oval", AccelKey("<control>0"), SHAPE_OVAL, "Egg");
	group->add_actions(ras, SHAPE_OVAL, mem_fun(this, &UIManagerWindow::on_activate_radio_action));	
}

Gtk::Window*
do_ui_manager(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new UIManagerWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

