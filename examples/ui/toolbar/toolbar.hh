#include <xfc/main.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class TreeView : public Gtk::TreeView
{
	Pointer<Gtk::ListStore> store;

	void set_visible(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void set_expand(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void set_homogeneous(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void set_important(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
		
protected:
	void on_visible_toggled(const String& path_str);
	void on_expand_toggled(const String& path_str);
	void on_homogeneous_toggled(const String& path_str);
	void on_important_toggled(const String& path_str);

public:
	TreeView(Gtk::Toolbar& toolbar);
	
	void add_item(Gtk::ToolItem *item, const char *text);
};

class Window : public Gtk::Window
{
	Gtk::Table *table;	
	Gtk::Toolbar *toolbar;
	
	static Gtk::ToolItem *drag_item;

	void popup_menu_position(int *x, int *y, bool *push_in, Gdk::Point *point);
	
protected: 
	void on_change_orientation(Gtk::CheckButton *button);
	void on_change_show_arrow(Gtk::CheckButton *button);
	void on_set_toolbar_style(Gtk::CheckButton *button);
	void on_change_toolbar_style(Gtk::ComboBox *option_menu);
	void on_reload_clicked();
	void on_bold_toggled(Gtk::ToggleToolButton *button);
	void on_rtl_toggled(Gtk::CheckButton *button);	
	bool on_toolbar_drag_motion(Gtk::DragContext& context, int x, int y, unsigned int time);				
	void on_toolbar_drag_leave(Gtk::DragContext& context, unsigned int time);
	bool on_toolbar_drag_drop(Gtk::DragContext& context, int x, int y, unsigned int time, Gtk::Label *label);
	bool on_popup_context_menu(int x, int y, int button_number);
						
public:
	Window();
	virtual ~Window();
};

