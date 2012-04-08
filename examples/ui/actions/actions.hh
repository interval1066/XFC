#include <xfc/main.hh>
#include <xfc/ui.hh>
#include <xfc/gtk/spinbutton.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/gtk/uimanager.hh>

using namespace Xfc;

class Window : public Gtk::Window
{
	Pointer<Gtk::ActionGroup> group;
	Pointer<Gtk::UIManager> manager;

	Gtk::ActionGroup *dag;		
	unsigned int ui_id;
		
	Gtk::Toolbar *toolbar;
	Gtk::SpinButton *spinbutton;
		
	void add_actions();
	void ensure_update();	

protected:
	void on_add_widget(Gtk::Widget& widget, Gtk::Box *box);
	void on_activate_action(Gtk::Action *action);
	void on_show_accel_dialog();
	void on_toggle_action(Gtk::ToggleAction *action);
	void on_toggle_cnp_actions(Gtk::ToggleAction *action);
	void on_radio_action(Gtk::RadioAction& action);
	void on_add_dynamic();
	void on_remove_dynamic();
	
public:
	Window();
	virtual ~Window();
};

