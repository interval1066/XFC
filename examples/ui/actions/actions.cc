#include "actions.hh"
#include <xfc/gtk/accelmap.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/glib/error.hh>
#include <xfc/glib/fileutils.hh>
#include <xfc/glib/timer.hh>
#include <iostream>

Window::Window()
: dag(0), ui_id(0)
{
	set_title("Action Test");
	set_default_size(-1, -1);

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);
	vbox->show();
	
	group = new Gtk::ActionGroup("TestActions");
	add_actions();
	
	manager = new Gtk::UIManager;
	manager->insert_action_group(*group);
	manager->signal_add_widget().connect(sigc::bind(sigc::mem_fun(this, &Window::on_add_widget), vbox));
	add_accel_group(manager->get_accel_group());

	// Load XML description of the menus from a disk file.
	G::Error error;	
	if (!manager->add_ui_from_file("actions.ui", &error))
	{
		std::cout << "building menus failed: << " << error.message() << std::endl;
	}

	Gtk::HBox *hbox = new Gtk::HBox;
	vbox->pack_end(*hbox, false, false);
	hbox->show();
  
	spinbutton = new Gtk::SpinButton(10, 1000, 10);
	hbox->pack_start(*spinbutton, false, false);
	spinbutton->show();
  
	Gtk::Button *button = new Gtk::Button("Add");
	hbox->pack_start(*button, false, false);
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_add_dynamic));
	button->show();
  
	button = new Gtk::Button("Remove");
	hbox->pack_start(*button, false, false);
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_remove_dynamic));
	button->show();
}
 
Window::~Window()
{
}

void 
Window::on_add_widget(Gtk::Widget& widget, Gtk::Box *box)
{
	box->pack_start(widget, false, false);
	widget.show();	  

	if (widget.is_a(GTK_TYPE_TOOLBAR))
	{
		static_cast<Gtk::Toolbar&>(widget).set_show_arrow(true);	
	}  
}

void 
Window::on_activate_action(Gtk::Action *action)
{
	using namespace std;
	
	cout << "Action " << action->get_name() << " (type=" << action->type_name() << ") activated" << endl;
}

void 
Window::on_show_accel_dialog()
{
	std::cout << "Sorry, accel dialog is not implemented" << std::endl;
}

void
Window::on_toggle_action(Gtk::ToggleAction *action)
{
	using namespace std;
	
	cout << "Action " << action->get_name() << " (type=" << action->type_name() << ") activated ";
	cout << "(active=" << action->get_active() << ")" << endl;
}

void
Window::on_toggle_cnp_actions(Gtk::ToggleAction *action)
{
	bool sensitive = action->get_active();
	group->get_action("cut")->property_sensitive().set(sensitive);
	group->get_action("copy")->property_sensitive().set(sensitive);
	group->get_action("paste")->property_sensitive().set(sensitive);
	String text(sensitive ? "Disable Cut and paste ops" : "Enable Cut and paste ops");	
	group->get_action("toggle-cnp")->property_label().set(text);
}

void
Window::on_radio_action(Gtk::RadioAction& action)
{
	using namespace std;
	
	cout << "Action " << action.get_name() << " (type=" << action.type_name() << ") activated ";
	cout << "(active=" << action.get_active() << ") ";
	cout << "(value=" << action.get_current_value() << ")" << endl;
}

void
Window::on_add_dynamic()
{
	if (ui_id || dag)
		return;
  
	int num = spinbutton->get_value_as_int();
	dag = new Gtk::ActionGroup("DynamicActions");
	manager->insert_action_group(*dag);
	ui_id = manager->new_merge_id();
  
	for (int i = 0; i < num; i++)
	{
		String name = String::format("DynAction%u", i);
		String label = String::format("Dynamic Item %d", i);
		Gtk::Action *action = new Gtk::Action(name, label);
		dag->add_action(*action);
		action->unref();
		manager->add_ui(ui_id, "/menubar/DynamicMenu", name, name, Gtk::UI_MANAGER_MENUITEM);
	}
	ensure_update();
}

void
Window::on_remove_dynamic()
{
	if (!ui_id || !dag)
		return;
	
	manager->remove_ui(ui_id);
	ensure_update();
	ui_id = 0;
	manager->remove_action_group(*dag);
	dag->unref();
	dag = 0;
}

void
Window::ensure_update()
{
	G::Timer timer;
	timer.start();
	manager->ensure_update();
	timer.stop();
	double seconds = timer.elapsed();
	std::cout << "Time: " << seconds << 's' << std::endl;
}

void
Window::add_actions()
{	
	using namespace	Gtk;
	using namespace sigc;
	
	// Create Action entries	
	group->add("Menu1Action", "Menu _1");
	group->add("Menu2Action", "Menu _2");
	group->add("Menu3Action", "_Dynamic Menu");
	
	Action *action = group->add("cut", "C_ut", StockId::CUT, AccelKey("<control>X"), "Cut selected text to the clipboard");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("copy", "_Copy", StockId::COPY, AccelKey("<control>C"), "Copy selected text to the clipboard");
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("paste", "_Paste", StockId::PASTE, AccelKey("<control>V"), "Paste text from the clipboard");
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("quit", StockId::QUIT, AccelKey("<control>Q"), "Quit the application");	
	action->signal_activate().connect(mem_fun(this, &Window::dispose));
	action = group->add("customise-accels", "Customise _Accels", "Customise keyboard shortcuts");
	action->signal_activate().connect(mem_fun(this, &Window::on_show_accel_dialog));
	
	// Create ToggleAction entries	
	ToggleAction *ta = group->add("bold", StockId::BOLD, false, "Change to bold face");
	ta->signal_activate().connect(bind(mem_fun(this, &Window::on_toggle_action), ta));
	ta = group->add("toggle-cnp", "Enable Cut/Copy/Paste", true, "Change the sensitivity of the cut, copy and paste actions");
	ta->signal_activate().connect(bind(mem_fun(this, &Window::on_toggle_cnp_actions), ta));

	// Create RadioAction justify entries
	RadioActions ras;
	ras.add("justify-left", "_Left", StockId::JUSTIFY_LEFT, JUSTIFY_LEFT, "Left justify the text"),
	ras.add("justify-right", "_Right", StockId::JUSTIFY_RIGHT, JUSTIFY_RIGHT, "Right justify the text");
	ras.add("justify-center", "C_enter", StockId::JUSTIFY_CENTER, JUSTIFY_CENTER, "Center justify the text");
	ras.add("justify-fill", "_Fill", StockId::JUSTIFY_FILL, JUSTIFY_FILL, "Fill justify the text");
	group->add_actions(ras, JUSTIFY_LEFT, mem_fun(this, &Window::on_radio_action));	

	// Create RadioAction toolbar entries
	ras.clear();
	ras.add("toolbar-icons", "Icons", TOOLBAR_ICONS);
	ras.add("toolbar-text", "Text", TOOLBAR_TEXT);
	ras.add("toolbar-both", "Both", TOOLBAR_BOTH);
	ras.add("toolbar-both-horiz", "Both Horizontal", TOOLBAR_BOTH_HORIZ);
	group->add_actions(ras, TOOLBAR_BOTH, mem_fun(this, &Window::on_radio_action));	
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	if (G::file_test("accels", G::FILE_TEST_IS_REGULAR))
		Gtk::AccelMap::load("accels");
    	
	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	
	Gtk::AccelMap::save("accels");
	return 0;
}

