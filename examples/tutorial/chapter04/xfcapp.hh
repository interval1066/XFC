#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/uimanager.hh>

using namespace Xfc;

class XfcApp : public Gtk::Window
{
	Pointer<Gtk::ActionGroup> action_group;
	Pointer<Gtk::UIManager> manager;
	
	void add_actions();
	
public:
	XfcApp();
	virtual ~XfcApp();
	
	void on_file_new();
	void on_file_open();
	void on_file_save();
	void on_file_save_as();
	void on_file_quit();
	void on_edit_cut();
	void on_edit_copy();
	void on_edit_paste();
	void on_edit_clear();
	void on_edit_preferences();
	void on_help_about();
};

