#include <xfc/main.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/uimanager.hh>

using namespace Xfc;

class ActionWindow : public Gtk::Window
{
	Pointer<Gtk::ActionGroup> group;
	Pointer<Gtk::UIManager> manager;
	
	void add_actions();

protected:
	bool on_button_press(const Gdk::EventButton& event, Gtk::Menu *menu);

public:
	ActionWindow();
	virtual ~ActionWindow();

	void menu_item_selected(const char *parent, const char *item);

	void on_file_new();
	void on_file_open();
	void on_file_save();
	void on_file_save_as();
	void on_file_quit();
	void on_options_test();
	void on_help_about();
};
