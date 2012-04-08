#include <xfc/main.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class MenuWindow : public Gtk::Window
{
	MenuWindow(const MenuWindow&);
	MenuWindow& operator=(const MenuWindow&);

protected:
	bool on_button_press(const Gdk::EventButton& event, Gtk::Menu *menu);

public:
	MenuWindow();
	virtual ~MenuWindow();

	void menu_item_selected(const char *parent, const char *item);

	void on_file_new();
	void on_file_open();
	void on_file_save();
	void on_file_save_as();
	void on_file_quit();
	void on_options_preferences();
	void on_help_about();
};

