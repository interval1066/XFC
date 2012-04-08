#include <xfc/main.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/statusbar.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/uimanager.hh>

using namespace Xfc;

class TreeView : public Gtk::TreeView
{
	Pointer<Gtk::ListStore> store;
	
	int compare(const Gtk::TreeIter& a, const Gtk::TreeIter& b);
	void set_name(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter);
	void set_sensitive(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter);
	void set_visible(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter);

protected:
	void on_sensitivity_toggled(const String& path_str);
	void on_visibility_toggled(const String& path_str);
					
public:
	TreeView(Gtk::UIManager& manager);
};

class Window : public Gtk::Window
{
	Pointer<Gtk::ActionGroup> group;
	Pointer<Gtk::UIManager> manager;
	
	Gtk::DrawingArea *area;
	Gtk::Statusbar *statusbar;
	Gtk::VBox *menu_box;

	void add_actions();
	int  delayed_toggle_dynamic();
	void print_toplevels(Gtk::Widget& widget);
		
protected: 
	void on_activate_action(Gtk::Action *action);
	void on_toggle_action(Gtk::ToggleAction *action);
	void on_radio_action_changed(Gtk::RadioAction& action);
	void on_connect_proxy(Gtk::Action& action, Gtk::Widget& proxy);
	void on_set_tip(Gtk::Widget *widget);
	void on_unset_tip();
	bool on_area_press(const Gdk::EventButton& event);
	void on_add_widget(Gtk::Widget& widget);
	void on_toggle_merge(Gtk::CheckButton *button);
	void on_toggle_tearoffs();
	void on_activate_path();
	void on_toggle_dynamic();
	void on_dump_tree();
	void on_dump_accels();
	void on_dump_toplevels();
		
public:
	Window();
	virtual ~Window();
};

