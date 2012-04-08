/* Menus
 *
 * There are several widgets involved in displaying menus. The
 * Gtk::MenuBar widget is a horizontal menu bar, which normally appears
 * at the top of an application. The Gtk::Menu widget is the actual menu
 * that pops up. Both Gtk::MenuBar and Gtk::Menu are derived from
 * Gtk::MenuShell; a Gtk::MenuShell contains menu items
 * (Gtk::MenuItem). Each menu item contains text and/or images and can
 * be selected by the user.
 *
 * There are several kinds of menu item, including plain Gtk::MenuItem,
 * Gtk::CheckMenuItem which can be checked/unchecked, Gtk::RadioMenuItem
 * which is a check menu item that's in a mutually exclusive group,
 * Gtk::SeparatorMenuItem which is a separator bar, Gtk::TearoffMenuItem
 * which allows a GtkMenu to be torn off, and Gtk::ImageMenuItem which
 * can place a Gtk::Image or other widget next to the menu text.
 *
 * A Gtk::MenuItem can have a submenu, which is simply a Gtk::Menu to pop
 * up when the menu item is selected. Typically, all menu items in a menu bar
 * have submenus.
 *
 * Gtk::UIManager provides a higher-level interface for creating menu bars
 * and menus; while you can construct menus manually, most people don't
 * do that. There's a separate demo for Gtk::UIManager.
 */

#include "demowindow.hh"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/checkmenuitem.hh>
#include <xfc/gtk/radiomenuitem.hh>
#include <xfc/gtk/separator.hh>
#include <xfc/gtk/tearoffmenuitem.hh>
#include <gdk/gdkkeysyms.h>
#include <cstdio>

using namespace Xfc;

class Menu : public Gtk::Menu
{
public:
	Menu(int depth, bool tearoff);
	~Menu();
};

class MenuWindow : public Gtk::Window
{
protected:
	virtual bool on_delete_event(const Gdk::EventAny& event) { return true; }

public:
	MenuWindow();
	~MenuWindow();
};
//!

// Menu

Menu::Menu(int depth, bool tearoff)
{
	if (tearoff)
	{
		Gtk::TearoffMenuItem *menuitem = new Gtk::TearoffMenuItem;
		append(*menuitem);
		menuitem->show();
	}

	Gtk::RadioMenuItem *menuitem = 0;
	for (int i = 0, j = 1; i < 5; i++, j++)
	{
		char buf[32];
		sprintf(buf, "item %2d - %d", depth, j);
		menuitem = new Gtk::RadioMenuItem(menuitem, buf);

		append(*menuitem);
 		menuitem->show();
		if (i == 3)
			menuitem->set_sensitive(false);

		depth -= 1;
		if (depth >= 1)
		{
			Gtk::Menu *submenu = new Menu(depth, true);
			menuitem->set_submenu(*submenu);
		}
	}
}

Menu::~Menu()
{
}

// MenuWindow

MenuWindow::MenuWindow()
{
	Pointer<Gtk::AccelGroup> accel_group = new Gtk::AccelGroup;
	add_accel_group(accel_group);
	set_title("Menus");
	set_border_width(0);

	Gtk::VBox *box1 = new Gtk::VBox;
	add(*box1);
	box1->show();
      
	Gtk::MenuBar *menubar = new Gtk::MenuBar;
	box1->pack_start(*menubar, false);
	menubar->show();

	Gtk::Menu *menu = new Menu(2, true);
	Gtk::MenuItem *menuitem = new Gtk::MenuItem("test\nline2");
	menuitem->set_submenu(*menu);
	menubar->append(*menuitem);
	menuitem->show();

	menu = new Menu(3, true);
	menuitem = new Gtk::MenuItem("foo");
	menuitem->set_submenu(*menu);
	menubar->append(*menuitem);
	menuitem->show();

	menu = new Menu(4, true);
	menuitem = new Gtk::MenuItem("bar");
	menuitem->set_submenu(*menu);
	menuitem->set_right_justified(true);
	menubar->append(*menuitem);
	menuitem->show();

	Gtk::VBox *box2 = new Gtk::VBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2, false);
	box2->show();

	Gtk::Button *button = new Gtk::Button("close");
	button->signal_clicked().connect(sigc::mem_fun(this, &Gtk::Object::dispose));
	box2->pack_start(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	button->show();
	show();
}

MenuWindow::~MenuWindow()
{
}

Gtk::Window*
do_menus(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new MenuWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

