#include "mergemenus.hh"
#include <xfc/gtk/accelmap.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/cellrenderertoggle.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/handlebox.hh>
#include <xfc/gtk/item.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/glib/error.hh>
#include <xfc/glib/main.hh>
#include <iostream>

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1 
#endif

struct { const char *filename; unsigned int merge_id; } merge_ids[] = 
{
	{ "merge-1.ui", 0 },
	{ "merge-2.ui", 0 },
  	{ "merge-3.ui", 0 }
};

TreeView::TreeView(Gtk::UIManager& manager)
{
	store = new Gtk::ListStore(1, GTK_TYPE_ACTION);
	store->set_sort_func(0, sigc::mem_fun(this, &TreeView::compare));
	store->set_sort_column_id(0, Gtk::SORT_ASCENDING);
	set_model(store);
	
	std::vector<Gtk::ActionGroup*> action_groups;
	manager.get_action_groups(action_groups);
	for (unsigned int i = 0; i < action_groups.size(); i++)
	{
		std::vector<Gtk::Action*> actions;
		action_groups[i]->list_actions(actions);
		
		for (unsigned int j = 0; j < actions.size(); j++)
		{
			Gtk::TreeIter iter = store->append();
			store->set_object(iter, 0, actions[j]);
		}
	}
	
	Gtk::CellRenderer *cell = new Gtk::CellRendererText;	
	append_column("Action", *cell, sigc::mem_fun(this, &TreeView::set_name));
	get_column(0)->set_sort_column_id(0);
	
	Gtk::CellRendererToggle *toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_sensitivity_toggled));
	append_column("Sensitive", *toggle_cell,  sigc::mem_fun(this, &TreeView::set_sensitive));
	
	toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_visibility_toggled));
	append_column("Visible", *toggle_cell,  sigc::mem_fun(this, &TreeView::set_visible));
}

int 
TreeView::compare(const Gtk::TreeIter& a, const Gtk::TreeIter& b)
{
	G::Value a_value, b_value;
	store->get_value(a, 0, a_value);	
	store->get_value(b, 0, b_value);	
	
	Pointer<Gtk::Action> a_action;	
	a_value.get(a_action);
	Pointer<Gtk::Action> b_action;	
	b_value.get(b_action);
	
	int result = 0;	
	if (a_action && b_action)
	{	
		String a_name = a_action->get_name();
		String b_name = b_action->get_name();
		if (a_name.null() && b_name.null()) 
			result = 0;
		else if (a_name.null())
			result = -1;
		else if (b_name.null())
			result = 1;
		else 
			result = a_name.compare(b_name);
	}
	return result;	
}

void  
TreeView::set_name(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter)
{
	Gtk::Action *action;
	tree_model.get_object(iter, 0, action);
	String name = action->get_name();
	static_cast<Gtk::CellRendererText&>(cell).property_text().set(name);	
	action->unref();
}

void 
TreeView::set_sensitive(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter)
{
	Gtk::Action *action;
	tree_model.get_object(iter, 0, action);
	bool sensitive = action->get_sensitive();
	static_cast<Gtk::CellRendererToggle&>(cell).set_active(sensitive);	
	action->unref();
}

void
TreeView::set_visible(Gtk::CellRenderer& cell, const Gtk::TreeModel& tree_model, const Gtk::TreeIter& iter)
{
	Gtk::Action *action;
	tree_model.get_object(iter, 0, action);
	bool visible = action->get_visible();
	static_cast<Gtk::CellRendererToggle&>(cell).property_active().set(visible);	
	action->unref();
}

void
TreeView::on_sensitivity_toggled(const String& path_str)
{
	Gtk::TreeIter iter;	
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	store->get_iter(iter, *path);
	Gtk::Action *action;
	store->get_object(iter, 0, action);
	bool sensitive = action->get_sensitive();
	action->property_sensitive().set(!sensitive);	
	store->row_changed(*path, iter);
	action->unref();
}

void
TreeView::on_visibility_toggled(const String& path_str)
{
	Gtk::TreeIter iter;	
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	store->get_iter(iter, *path);
	Gtk::Action *action;
	store->get_object(iter, 0, action);
	bool visible = action->get_visible();
	action->property_visible().set(!visible);	
	store->row_changed(*path, iter);
	action->unref();
}

Window::Window()
{
	set_title("Merge Menu Test");
	set_default_size(-1, 400);
	
	group = new Gtk::ActionGroup("TestActions");
	add_actions();
		
	group->get_action("EmptyMenu1Action")->property_hide_if_empty().set(false);
	group->get_action("EmptyMenu2Action")->property_hide_if_empty().set(true);

	Gtk::Table *table = new Gtk::Table(2, 2);
	table->set_row_spacings(2);
	table->set_col_spacings(2);
	table->set_border_width(2);
	add(*table);
	
	Gtk::Frame *frame = new Gtk::Frame("Menus and Toolbars");
	table->attach(*frame, 0, 2, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
	
	menu_box = new Gtk::VBox;
	menu_box->set_border_width(2);
	frame->add(*menu_box);
	
	statusbar = new Gtk::Statusbar;
	menu_box->pack_end(*statusbar, false, false);
	
	area = new Gtk::DrawingArea;
	area->set_events(Gdk::BUTTON_PRESS_MASK);
	area->set_size_request(-1, 40);
	menu_box->pack_end(*area, false, false);
	area->show();
	
	Gtk::Button *button = new Gtk::Button;
	menu_box->pack_end(*button, false, false);
	group->get_action("AboutAction")->connect_proxy(*button);
	button->show();
	
	button = new Gtk::CheckButton;
	menu_box->pack_end(*button, false, false);
	group->get_action("BoldAction")->connect_proxy(*button);
	button->show();
	
	manager = new Gtk::UIManager;
	manager->signal_connect_proxy().connect(mem_fun(this, &Window::on_connect_proxy));
	area->signal_button_press_event().connect(mem_fun(this, &Window::on_area_press));
	
	manager->insert_action_group(*group);
	manager->signal_add_widget().connect(sigc::mem_fun(this, &Window::on_add_widget));
	
	add_accel_group(manager->get_accel_group());
	
	frame = new Gtk::Frame("UI Files");
	table->attach(*frame, 0, 1, 0, 1, Gtk::FILL, Gtk::FILL | Gtk::EXPAND);
	
	Gtk::VBox *vbox = new Gtk::VBox(false, 2);
	vbox->set_border_width(2);
	frame->add(*vbox);
	
	 for (unsigned int i = 0; i < G_N_ELEMENTS(merge_ids); i++)
	{
		Gtk::CheckButton *check_button = new Gtk::CheckButton(merge_ids[i].filename);
		check_button->set_data("mergenum", GINT_TO_POINTER(i));
		check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_toggle_merge), check_button));
		vbox->pack_start(*check_button, false, false);
		check_button->set_active(true);
	}
	
	button = new Gtk::CheckButton("Tearoffs");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_toggle_tearoffs));
	vbox->pack_end(*button, false, false);
	
	button = new Gtk::CheckButton("Dynamic");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_toggle_dynamic));
	vbox->pack_end(*button, false, false);
	
	button = new Gtk::Button("Activate path");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_activate_path));
	vbox->pack_end(*button, false, false);

	button = new Gtk::Button("Dump Tree");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_dump_tree));
	vbox->pack_end(*button, false, false);

	button = new Gtk::Button("Dump Toplevels");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_dump_toplevels));
	vbox->pack_end(*button, false, false);

	button = new Gtk::Button("Dump Accels");
	button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_dump_accels));
	vbox->pack_end(*button, false, false);
		
	TreeView *tree_view = new TreeView(*manager);
	Gtk::ScrolledWindow *view = new Gtk::ScrolledWindow;
	view->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	view->add(*tree_view);
	table->attach(*view, 1, 2, 0, 1);
	table->show_all();
}

Window::~Window()
{
}

void 
Window::on_activate_action(Gtk::Action *action)
{
	using namespace std;
	
	cout << "Action " << action->get_name() << " (type=" << action->type_name() << ") activated" << endl;
}

void 
Window::on_toggle_action(Gtk::ToggleAction *action)
{
	using namespace std;
	
	cout << "ToggleAction " << action->get_name() << " (type=" << action->type_name() << ") toggled ";
	cout << "(active=" << action->get_active() << ")" << endl;
}
	
void 
Window::on_radio_action_changed(Gtk::RadioAction& action)
{
	using namespace std;
	
	cout << "RadioAction " << action.get_name() << " (type=" << action.type_name() << ") activated ";
	cout << "(active=" << action.get_active() << ") ";
	cout << "(value=" << action.get_current_value() << ")" << endl;
}

bool
Window::on_area_press(const Gdk::EventButton& event)
{
	area->grab_focus();
	
	if (event.button() == 3 && event.type() == Gdk::BUTTON_PRESS)
	{
		Gtk::Widget *widget = manager->get_widget("/FileMenu");
		if (widget->is_a(GTK_TYPE_MENU))
		{
			Gtk::Menu *menu = static_cast<Gtk::Menu*>(widget);
			menu->popup(3, event.time());	
			return true;
		}
	}	
	return false;
}

void 
Window::on_set_tip(Gtk::Widget *widget)
{
	Gtk::Action *data = reinterpret_cast<Gtk::Action*>(widget->get_data("action-status"));
	if (data) 
	{
		String tooltip;
		data->property_tooltip().get(tooltip);
		statusbar->push(!tooltip.null() ? tooltip : "");
	}
}
	
void 
Window::on_unset_tip()
{
	statusbar->pop();
}

namespace { // action_destroy_notify

void action_destroy_notify(Gtk::Action *action)
{
	action->unref();
}

} // namespace

void 
Window::on_connect_proxy(Gtk::Action& action, Gtk::Widget& proxy)
{
	if (!proxy.is_a(GTK_TYPE_MENU_ITEM))
		return;
		
	Gtk::Action *data = reinterpret_cast<Gtk::Action*>(proxy.get_data("action-status"));
	if (data)
	{
		data->unref();
		proxy.set_data("action-status", &action);		
		action.ref();
	}
	else
	{
		proxy.set_data("action-status", &action, (GDestroyNotify)&action_destroy_notify);		
		action.ref();
		
		Gtk::Item *item = static_cast<Gtk::Item*>(&proxy);
		item->signal_select().connect(sigc::bind(sigc::mem_fun(this, &Window::on_set_tip), &proxy));
		item->signal_deselect().connect(sigc::mem_fun(this, &Window::on_unset_tip));
	}
}

void
Window::on_add_widget(Gtk::Widget& widget) 
{
	if (widget.is_a(GTK_TYPE_TOOLBAR))
	{
		Gtk::HandleBox *handle_box = new Gtk::HandleBox;
		handle_box->add(widget);
		handle_box->show();
		menu_box->pack_start(*handle_box, false, false);
		widget.signal_destroy().connect(sigc::mem_fun(handle_box, &Gtk::HandleBox::dispose));
	}
	else
		menu_box->pack_start(widget, false, false);
	
	widget.show();
}

void
Window::on_toggle_merge(Gtk::CheckButton *button)
{
	int mergenum = GPOINTER_TO_INT(button->get_data("mergenum"));
	
	if (button->get_active())
	{
		G::Error error;
		std::cout << "merging " << merge_ids[mergenum].filename << std::endl;
		merge_ids[mergenum].merge_id = manager->add_ui_from_file(merge_ids[mergenum].filename, &error);
		if (error.get())
		{
			Gtk::MessageDialog dialog(Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, this);
			dialog.format_message("could not merge %s: %s", merge_ids[mergenum].filename, error.message());
			dialog.signal_response().connect(sigc::hide(sigc::mem_fun(dialog, &Gtk::Dialog::dispose)));
			dialog.show();
		}
	}
	else
	{
		std::cout << "unmerging " << merge_ids[mergenum].filename;
		std::cout << " merge_id=" << merge_ids[mergenum].merge_id << std::endl;
		manager->remove_ui(merge_ids[mergenum].merge_id);
	}
}

void
Window::on_toggle_tearoffs()
{
	bool add_tearoffs = manager->get_add_tearoffs();
	manager->set_add_tearoffs(!add_tearoffs);
}

void
Window::on_activate_path()
{
	Gtk::Action *action = manager->get_action("/menubar/HelpMenu/About");
	if (action)
		action->activate();
	else 
		std::cout << "no action found" << std::endl;
}

int
Window::delayed_toggle_dynamic()
{
	static Gtk::ActionGroup *dynamic = 0;
	static unsigned int merge_id = 0;
	
	if (!dynamic)
	{
		dynamic = new Gtk::ActionGroup("dynamic");
		manager->insert_action_group(*dynamic);
		Gtk::Action *action = new Gtk::Action("dyn1", "Dynamic action 1", Gtk::StockId::COPY);
		dynamic->add_action(*action);
		action = new Gtk::Action("dyn2", "Dynamic action 2", Gtk::StockId::EXECUTE);
		dynamic->add_action(*action);
	}
	
	if (!merge_id)
	{
		merge_id = manager->new_merge_id();
		manager->add_ui(merge_id, "/toolbar1/ToolbarPlaceholder", "dyn1", "dyn1");
		manager->add_ui_separator(merge_id, "/toolbar1/ToolbarPlaceholder", "dynsep");
		manager->add_ui(merge_id, "/toolbar1/ToolbarPlaceholder", "dyn2", "dyn2");
		manager->add_ui(merge_id, "/menubar/EditMenu", "dyn2", "dyn2");
		manager->add_ui(merge_id, "/menubar/EditMenu", "dyn1menu", "dyn1", Gtk::UI_MANAGER_MENU);
		manager->add_ui(merge_id, "/menubar/EditMenu/dyn1menu", "dyn1", "dyn1", Gtk::UI_MANAGER_MENUITEM);
		manager->add_ui(merge_id, "/menubar/EditMenu/dyn1menu", "dyn2", "dyn2", Gtk::UI_MANAGER_AUTO, true);
	}
	else 
	{
		manager->remove_ui(merge_id);
		merge_id = 0;
	}
	return false;
}

void
Window::on_toggle_dynamic()
{
	G::timeout_signal.connect(sigc::mem_fun(this, &Window::delayed_toggle_dynamic), 2000);
}

void
Window::on_dump_tree()
{
	String dump = manager->get_ui();
	std::cout << dump << std::endl;
}

void
Window::on_dump_accels()
{
	Gtk::AccelMap::save(STDOUT_FILENO);
}

void
Window::print_toplevels(Gtk::Widget& widget)
{
	std::cout << widget.type_name() << std::endl;  
}

void
Window::on_dump_toplevels()
{
	std::vector<Widget*> toplevels;	
	manager->get_toplevels(toplevels, Gtk::UI_MANAGER_MENUBAR | Gtk::UI_MANAGER_TOOLBAR | Gtk::UI_MANAGER_POPUP);
	for (unsigned int i = 0; i < toplevels.size(); i++)
	{	
		print_toplevels(*toplevels[i]);
	}
}

void
Window::add_actions()
{	
	using namespace	Gtk;
	using namespace sigc;
	
	// Create Action entries	
	group->add("FileMenuAction", "_File");
	group->add("EditMenuAction", "_Edit");
	group->add("HelpMenuAction", "_Help");
	group->add("JustifyMenuAction", "_Justify");
	group->add("EmptyMenu1Action", "Empty 1");
	group->add("EmptyMenu2Action", "Empty 2");
	group->add("Test", "Test");
	
	Action *action = group->add("QuitAction", StockId::QUIT, AccelKey("<control>q"), "Quit");	
	action->signal_activate().connect(mem_fun(this, &Window::dispose));
	action = group->add("NewAction", StockId::NEW, AccelKey("<control>n"), "Create something");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("New2Action", StockId::NEW, AccelKey("<control>m"), "Create something else");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("OpenAction", StockId::OPEN, "Open it");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("CutAction", StockId::CUT, AccelKey("<control>x"), "Cut");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("CopyAction", StockId::COPY, AccelKey("<control>c"), "Copy");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("PasteAction", StockId::PASTE, AccelKey("<control>v"), "Paste");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));
	action = group->add("AboutAction", "_About", "About");	
	action->signal_activate().connect(bind(mem_fun(this, &Window::on_activate_action), action));

	// Create ToggleAction entries	
	ToggleAction *ta = group->add("BoldAction", "_Bold", StockId::BOLD, false, "Change to bold face");
	ta->signal_activate().connect(bind(mem_fun(this, &Window::on_toggle_action), ta));

	// Create RadioAction justify entries
	RadioActions ras;
	ras.add("justify-left", StockId::JUSTIFY_LEFT, AccelKey("<control>L"), JUSTIFY_LEFT, "Left justify the text"),
	ras.add("justify-right", StockId::JUSTIFY_RIGHT, AccelKey("<control>R"), JUSTIFY_RIGHT, "Right justify the text");
	ras.add("justify-center", StockId::JUSTIFY_CENTER, AccelKey("<control>E"), JUSTIFY_CENTER, "Center justify the text");
	ras.add("justify-fill", StockId::JUSTIFY_FILL, AccelKey("<control>J"), JUSTIFY_FILL, "Fill justify the text");
	group->add_actions(ras, JUSTIFY_RIGHT, mem_fun(this, &Window::on_radio_action_changed));	
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();
	
	run();
	return 0;
}

