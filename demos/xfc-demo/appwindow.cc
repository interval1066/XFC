/*  Application main window
 *
 *  Demonstrates a typical application window, with a menubar, toolbar and statusbar.
 */

#include "demowindow.hh"
#include <xfc/gtk/aboutdialog.hh>
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/iconfactory.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/statusbar.hh>
#include <xfc/gtk/stock.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/uimanager.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <iostream>
#include <xfc-config.h>

using namespace Xfc;

class AppWindow : public Gtk::Window
{
	static Pointer<Gtk::IconFactory> icon_factory;
	Pointer<Gtk::ActionGroup> action_group;
	Pointer<Gtk::UIManager> manager;
	
	Gtk::Statusbar *statusbar;
	Gtk::TextBuffer *buffer;

	void add_actions();
	void update_statusbar();
	void mark_set(const GtkTextIter*, GtkTextMark*);
	
protected:
	void on_about();
	void on_activate_email(Gtk::AboutDialog& about, const String& link);	
	void on_activate_url(Gtk::AboutDialog& about, const String& link);	
	void on_activate_action(Gtk::Action *action);
	void on_activate_radio_action(Gtk::RadioAction& current);
	bool on_update_resize_grip(const Gdk::EventWindowState& event);
	
public:
	AppWindow();
	~AppWindow();

	static void register_stock_icons();
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
"  <toolbar  name='ToolBar'>"
"    <toolitem action='Open'/>"
"    <toolitem action='Quit'/>"
"    <separator action='Sep1'/>"
"    <toolitem action='Logo'/>"
"  </toolbar>"
"</ui>";

Pointer<Gtk::IconFactory> AppWindow::icon_factory;

AppWindow::AppWindow()
{
	set_title("Application Window");
	set_default_size(200, 200);
	Gtk::Table *table = new Gtk::Table(1, 4);
	add(*table);

	// Register our stock items
	register_stock_icons();
	
	// Create the menubar and toolbar
	action_group = new Gtk::ActionGroup("AppWindowActions");
	add_actions();	
	
	manager = new Gtk::UIManager;
	manager->insert_action_group(*action_group);
	add_accel_group(manager->get_accel_group());
	
	// Load XML description of the menus from a string.
	G::Error error;	
	if (!manager->add_ui_from_string(ui_info, -1, &error))
	{
		std::cout << "building menus failed: << " << error.message() << std::endl;
	}

	Gtk::Widget *menubar = manager->get_widget("/MenuBar");
	menubar->show();
	table->attach(*menubar, 0, 1, 0, 1, Gtk::EXPAND | Gtk::FILL, 0);
	
	Gtk::Toolbar *toolbar = static_cast<Gtk::Toolbar*>(manager->get_widget("/ToolBar"));
	toolbar->set_tooltips (true);
	toolbar->show();
	table->attach(*toolbar, 0, 1, 1, 2, Gtk::EXPAND | Gtk::FILL, 0);
	
	// Create document
	Gtk::ScrolledWindow *scrolled_window = new Gtk::ScrolledWindow;
	scrolled_window->set_policy_automatic();
	scrolled_window->set_shadow_type(Gtk::SHADOW_IN);
	table->attach(*scrolled_window, 0, 1, 2, 3);
	Gtk::TextView *contents = new Gtk::TextView;
	contents->grab_focus();	
	scrolled_window->add(*contents); 

	// Create statusbar
	statusbar = new Gtk::Statusbar;
	table->attach(*statusbar, 0, 1, 3, 4, Gtk::EXPAND | Gtk::FILL, 0);
	
	// Show text widget info in the statusbar
	buffer = contents->get_buffer();
	buffer->signal_changed().connect(sigc::mem_fun(this, &AppWindow::update_statusbar));
	buffer->signal_mark_set().connect(sigc::mem_fun(this, &AppWindow::mark_set));
	signal_window_state_event().connect(sigc::mem_fun(this, &AppWindow::on_update_resize_grip));
	update_statusbar();

	show_all();
}

AppWindow::~AppWindow()
{
}

void
AppWindow::on_activate_action(Gtk::Action *action)
{
	String name = action->get_name();
	String type_name = action->type_name(); 
	Gtk::MessageDialog dialog(Gtk::MESSAGE_INFO, Gtk::BUTTONS_CLOSE, this);
	dialog.format_message("You activated action: \"%s\" of type \"%s\"", name.c_str(), type_name.c_str());
	if (dialog.run() == Gtk::RESPONSE_CLOSE)
		dialog.dispose();
}

void
AppWindow::on_activate_radio_action(Gtk::RadioAction& current)
{
	if (current.get_active()) 
	{
		String name = current.get_name();
		String type_name = current.type_name(); 
		int value = current.get_current_value();
		Gtk::MessageDialog dialog(Gtk::MESSAGE_INFO, Gtk::BUTTONS_CLOSE, this);
		dialog.format_message("You activated radio action: \"%s\" of type \"%s\".\nCurrent value: %d",
		                      name.c_str(), type_name.c_str(), value);
		if (dialog.run() == Gtk::RESPONSE_CLOSE)
			dialog.dispose();
	}
}

void 
AppWindow::on_about()
{
	const char *license =
	"This library is free software; you can redistribute it and/or\n"
	"modify it under the terms of the GNU Lesser General Public License as\n"
	"published by the Free Software Foundation; either version 2 of the\n"
	"License, or (at your option) any later version.\n"
	"\n"
	"This library is distributed in the hope that it will be useful,\n"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"
	"Lesser General Public License for more details.\n"
	"\n"
	"You should have received a copy of the GNU Lesser General Public\n"
	"License along with the XFC Library; see the file COPYING.  If not,\n"
	"write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,\n"
	"Boston, MA 02111-1307, USA.\n";

	std::vector<String> authors;
	authors.push_back("Jeff Franks <jcfranks@xfce.org>");
	
	Pointer<Gdk::Pixbuf> transparent;
	String filename = DemoWindow::find_file("gtk-logo-rgb.gif");
	if (!filename.null())
	{
		Pointer<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create(filename);
		transparent = pixbuf->add_alpha(true, 0xff, 0xff, 0xff);
	}
	
	Gtk::AboutDialog::set_email_hook(sigc::mem_fun(this, &AppWindow::on_activate_email));	
	Gtk::AboutDialog::set_url_hook(sigc::mem_fun(this, &AppWindow::on_activate_url));
	show_about_dialog(transparent, "XFC Code Demos", PACKAGE_VERSION, 
	                  "Program to demonstrate a GTK+ application window.",
	                  "Copyright (C) 2004-2005 The XFC Development Team",	
	                  "http://xfc.xfce.org", &authors, &authors, license);
}

void 
AppWindow::on_activate_email(Gtk::AboutDialog& about, const String& link)
{
	std::cout << "send mail to " << link << std::endl;
}	

void 
AppWindow::on_activate_url(Gtk::AboutDialog& about, const String& link)
{
	std::cout << "show url " << link << std::endl;
}	

void
AppWindow::update_statusbar()
{
	statusbar->pop(); // clears any previous message
	int count = buffer->get_char_count();
	Gtk::TextIter iter = buffer->get_iter_at_mark(*buffer->get_insert());
	int row = iter.get_line();
	int col = iter.get_line_offset();
	String msg = String::format("Cursor at row %d column %d - %d chars in document", row, col, count);
	statusbar->push(msg);
}

void
AppWindow::mark_set(const GtkTextIter*, GtkTextMark*)
{
	update_statusbar();
}

bool
AppWindow::on_update_resize_grip(const Gdk::EventWindowState& event)
{
	Gdk::WindowStateField state = Gdk::WINDOW_STATE_MAXIMIZED | Gdk::WINDOW_STATE_FULLSCREEN; 	
	if (event.changed_mask() & state)
		statusbar->set_has_resize_grip(!(event.new_window_state() & state));
	return true;
}
		    
void
AppWindow::register_stock_icons()
{
	// Register our custom toolbar icons, so they can be themed.
	Gtk::StockItem item("demo-gtk-logo", "_GTK!");
	Gtk::Stock::add(item);

	// Add our custom icon factory to the list of defaults
	icon_factory = new Gtk::IconFactory;
	icon_factory->add_default();

	// DemoWindow::find_file() looks in the the current directory first, then looks in the location where the file is installed.
	Pointer<Gdk::Pixbuf> pixbuf;
	String filename = DemoWindow::find_file("gtk-logo-rgb.gif");
	if (!filename.null())
	pixbuf = Gdk::Pixbuf::create(filename);

	// Register icon to accompany stock item
	if (pixbuf)
	{
		Pointer<Gdk::Pixbuf> transparent = pixbuf->add_alpha(true, 0xff, 0xff, 0xff);
		Pointer<Gtk::IconSet> icon_set = new Gtk::IconSet(*transparent);
		icon_factory->add("demo-gtk-logo", *icon_set);
	}
	else
		g_warning ("failed to load GTK logo for toolbar");
}

void
AppWindow::add_actions()
{
	using namespace	Gtk;
	using namespace sigc;
	
	// Create Action entries	
	action_group->add("FileMenu", "_File");
	action_group->add("PreferencesMenu", "_Preferences");
	action_group->add("ColorMenu", "_Color");
	action_group->add("ShapeMenu", "_Shape");
	action_group->add("HelpMenu", "_Help");

	Action *action = action_group->add("New", "_New", StockId::NEW, AccelKey("<control>N"), "Create a new file");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));
	action = action_group->add("Open", "_Open", StockId::OPEN, AccelKey("<control>O"), "Open a file");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));
	action = action_group->add("Save", "_Save", StockId::SAVE, AccelKey("<control>S"), "Save current file");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));
	action = action_group->add("SaveAs", "Save _As...", StockId::SAVE, "Save to a file");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));
	action = action_group->add("Quit", "_Quit", StockId::QUIT, AccelKey("<control>Q"), "Quit");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));
	action = action_group->add("About", "_About", AccelKey("<control>A"), "About");	
	action->signal_activate().connect(mem_fun(this, &AppWindow::on_about));
	action = action_group->add("Logo", StockId("demo-gtk-logo"), "GTK+");	
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));

	// Create ToggleAction entries	
	action = action_group->add("Bold", "_Bold", StockId::BOLD, AccelKey("<control>B"), false, "Bold");
	action->signal_activate().connect(bind(mem_fun(this, &AppWindow::on_activate_action), action));

	// Create RadioAction color entries
	RadioActions ras;
	ras.add("Red", "_Red", AccelKey("<control>R"), COLOR_RED, "Blood"),
	ras.add("Green", "_Green", AccelKey("<control>G"), COLOR_GREEN, "Grass");
	ras.add("Blue", "_Blue", AccelKey("<control>B"), COLOR_BLUE, "Center justify the text");
	action_group->add_actions(ras, COLOR_RED, mem_fun(this, &AppWindow::on_activate_radio_action));	

	// Create RadioAction shape entries
	ras.clear();
	ras.add("Square", "_Square", AccelKey("<control>S"), SHAPE_SQUARE, "Square"),
	ras.add("Rectangle", "_Rectangle", AccelKey("<control>R"), SHAPE_RECTANGLE, "Rectangle");
	ras.add("Oval", "_Oval", AccelKey("<control>0"), SHAPE_OVAL, "Egg");
	action_group->add_actions(ras, SHAPE_SQUARE, mem_fun(this, &AppWindow::on_activate_radio_action));	
}

Gtk::Window*
do_appwindow(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new AppWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

