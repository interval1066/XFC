#include "toolbar.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertoggle.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/menuitem.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/stockid.hh>
#include <iostream>

Gtk::ToolItem *Window::drag_item = 0;

TreeView::TreeView(Gtk::Toolbar& toolbar)
{
	store = new Gtk::ListStore(2, GTK_TYPE_TOOL_ITEM, G_TYPE_STRING);
	set_model(store);
	
	Gtk::CellRenderer *cell = new Gtk::CellRendererText;	
	Gtk::CellColumnAttributes attributes("text", 1);
	append_column("Tool Item", *cell, attributes);
	
	Gtk::CellRendererToggle *toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_visible_toggled));	
	append_column("Visible", *toggle_cell, sigc::mem_fun(this, &TreeView::set_visible));
	
	toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_expand_toggled));	
	append_column("Expand", *toggle_cell, sigc::mem_fun(this, &TreeView::set_expand));
	
	toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_homogeneous_toggled));	
	append_column("Homogeneous", *toggle_cell, sigc::mem_fun(this, &TreeView::set_homogeneous));
	
	toggle_cell = new Gtk::CellRendererToggle;
	toggle_cell->signal_toggled().connect(sigc::mem_fun(this, &TreeView::on_important_toggled));	
	append_column("Important", *toggle_cell, sigc::mem_fun(this, &TreeView::set_important));
}

void
TreeView::on_visible_toggled(const String& path_str)
{
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	Gtk::TreeIter iter;	
	store->get_iter(iter, *path);
	Gtk::ToolItem *tool_item;
	store->get_object(iter, 0, tool_item);
	tool_item->show(!tool_item->is_visible());	
	tool_item->unref();
	store->row_changed(*path, iter);
}

void
TreeView::set_visible(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	Gtk::ToolItem *tool_item;
	model.get_object(iter, 0, tool_item);
	static_cast<Gtk::CellRendererToggle&>(cell).set_active(tool_item->is_visible());
	tool_item->unref();
}

void
TreeView::on_expand_toggled(const String& path_str)
{
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	Gtk::TreeIter iter;	
	store->get_iter(iter, *path);
	Gtk::ToolItem *tool_item;
	store->get_object(iter, 0, tool_item);
	tool_item->set_expand(!tool_item->get_expand());	
	tool_item->unref();
	store->row_changed(*path, iter);
}

void
TreeView::set_expand(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	Gtk::ToolItem *tool_item;
	model.get_object(iter, 0, tool_item);
	static_cast<Gtk::CellRendererToggle&>(cell).set_active(tool_item->get_expand());
	tool_item->unref();
}

void
TreeView::on_homogeneous_toggled(const String& path_str)
{
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	Gtk::TreeIter iter;	
	store->get_iter(iter, *path);
	Gtk::ToolItem *tool_item;
	store->get_object(iter, 0, tool_item);
	tool_item->set_homogeneous(!tool_item->get_homogeneous());	
	tool_item->unref();
	store->row_changed(*path, iter);
}

void
TreeView::set_homogeneous(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	Gtk::ToolItem *tool_item;
	model.get_object(iter, 0, tool_item);
	static_cast<Gtk::CellRendererToggle&>(cell).set_active(tool_item->get_homogeneous());
	tool_item->unref();
}

void
TreeView::on_important_toggled(const String& path_str)
{
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);
	Gtk::TreeIter iter;	
	store->get_iter(iter, *path);
	Gtk::ToolItem *tool_item;
	store->get_object(iter, 0, tool_item);
	tool_item->set_is_important(!tool_item->get_is_important());	
	tool_item->unref();
	store->row_changed(*path, iter);
}

void
TreeView::set_important(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	Gtk::ToolItem *tool_item;
	model.get_object(iter, 0, tool_item);
	static_cast<Gtk::CellRendererToggle&>(cell).set_active(tool_item->get_is_important());
	tool_item->unref();
}

void
TreeView::add_item(Gtk::ToolItem *item, const char *text)
{
	Gtk::TreeIter iter = store->append();
	store->set_object(iter, 0, item);
	store->set_value(iter, 1, text);
}

Window::Window()
{
	set_title("Toobar Example");
	table = new Gtk::Table(4, 2);
	add(*table);
	
	toolbar = new Gtk::Toolbar;	
	table->attach(*toolbar, 0, 2, 0, 1, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
	
	Gtk::HBox *hbox1 = new Gtk::HBox(false, 3);
	hbox1->set_border_width(5);
	table->attach(*hbox1, 1, 2, 1, 2, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
	
	Gtk::CheckButton *check_button = new Gtk::CheckButton("_Vertical", true);
	hbox1->pack_start(*check_button, false, false);
	check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_change_orientation), check_button));
		
	check_button = new Gtk::CheckButton("_Show Arrow", true);
	check_button->set_active(true);
	hbox1->pack_start(*check_button, false, false);
	check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_change_show_arrow), check_button));

	check_button = new Gtk::CheckButton("_Set Toolbar Style:", true);
	hbox1->pack_start(*check_button, false, false);
	check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_set_toolbar_style), check_button));
	
	// Toolbar style ComboBox	
	Gtk::ComboBoxText *option_menu = new Gtk::ComboBoxText;
	option_menu->append("icons");
	option_menu->append("text");
	option_menu->append("both (vertical)");
	option_menu->append("both (horizontal)");
	option_menu->set_active(toolbar->get_style());  
	option_menu->set_sensitive(false);  
	check_button->set_data("option-menu", option_menu);
	hbox1->pack_start(*option_menu, false, false);
	option_menu->signal_changed().connect(sigc::bind(sigc::mem_fun(this, &Window::on_change_toolbar_style), option_menu));
	
	// TreeView	
	TreeView *tree_view = new TreeView(*toolbar);	
	Gtk::ScrolledWindow *view = new Gtk::ScrolledWindow;
	view->set_policy_automatic();
	view->add(*tree_view);
	table->attach(*view, 1, 2, 2, 3);
	
	// Add tool items to the toolbar and the tree view list	
	Gtk::ToolButton *tool_button = new Gtk::ToolButton(Gtk::StockId::NEW);
	tree_view->add_item(tool_button, "New");
	toolbar->append(*tool_button);
	tool_button->set_expand(true);
	
	tool_button = new Gtk::ToolButton(Gtk::StockId::OPEN);
	tree_view->add_item(tool_button, "Open");
	toolbar->append(*tool_button);
	
	Gtk::SeparatorToolItem *separator_item = new Gtk::SeparatorToolItem;
	tree_view->add_item(separator_item, "-----");
	toolbar->append(*separator_item);
	
	tool_button = new Gtk::ToolButton(Gtk::StockId::REFRESH);
	tool_button->signal_clicked().connect(sigc::mem_fun(this, &Window::on_reload_clicked));
	tree_view->add_item(tool_button, "Refresh");
	toolbar->append(*tool_button);
	
	// Add a custom tool item	
	Gtk::Image *image = new Gtk::Image(Gtk::StockId::DIALOG_WARNING, Gtk::ICON_SIZE_DIALOG);
	Gtk::ToolItem *item = new Gtk::ToolItem;
	item->add(*image);	
	image->show();
	tree_view->add_item(item, "Custom Item");
	toolbar->append(*item);

	tool_button = new Gtk::ToolButton(Gtk::StockId::GO_BACK);
	tree_view->add_item(tool_button, "Back");
	toolbar->append(*tool_button);
	
	separator_item = new Gtk::SeparatorToolItem;
	tree_view->add_item(separator_item, "-----");
	toolbar->append(*separator_item);
	
	tool_button = new Gtk::ToolButton(Gtk::StockId::GO_FORWARD);
	tree_view->add_item(tool_button, "Forward");
	toolbar->append(*tool_button);
	
	Gtk::ToggleToolButton *toggle_item = new Gtk::ToggleToolButton(Gtk::StockId::BOLD);
	toggle_item->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_bold_toggled), toggle_item));
	tree_view->add_item(toggle_item, "Bold");
	toolbar->append(*toggle_item);
	toggle_item->set_sensitive(false);
	
	separator_item = new Gtk::SeparatorToolItem;
	tree_view->add_item(separator_item, "-----");
	toolbar->append(*separator_item);
	separator_item->set_expand(true);
	separator_item->set_draw(false);
	
	Gtk::RadioToolButton *radio_item = 0;	
	radio_item = new Gtk::RadioToolButton(radio_item, Gtk::StockId::JUSTIFY_LEFT);
	tree_view->add_item(radio_item, "Left");
	toolbar->append(*radio_item);
	
	radio_item = new Gtk::RadioToolButton(radio_item, Gtk::StockId::JUSTIFY_CENTER);
	tree_view->add_item(radio_item, "Center");
	toolbar->append(*radio_item);
	
	radio_item = new Gtk::RadioToolButton(radio_item, Gtk::StockId::JUSTIFY_RIGHT);
	tree_view->add_item(radio_item, "Right");
	toolbar->append(*radio_item);
	
	image = new Gtk::Image("apple-red.png");	
	tool_button = new Gtk::ToolButton(*image, "_Apple", true);
	tree_view->add_item(tool_button, "Apple");
	toolbar->append(*tool_button);
	
	// Add the miscelaneous buttons and labels at the bottom of the window.	
	Gtk::HBox *hbox = new Gtk::HBox(false, 5);
	hbox->set_border_width(5);
	table->attach(*hbox, 1, 2, 4, 5, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
	
	Gtk::Button *button = new Gtk::Button("Drag me to the toolbar");
	hbox->pack_start(*button, false, false);
	
	Gtk::Label *label = new Gtk::Label("Drop index:");
	hbox->pack_start(*label, false, false);
	
	label = new Gtk::Label("");
	hbox->pack_start(*label, false, false);
	
	check_button = new Gtk::CheckButton("_Right to left", true);
	check_button->set_active(Gtk::Widget::get_default_direction() == Gtk::TEXT_DIR_RTL);
	check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Window::on_rtl_toggled), check_button));
	hbox->pack_end(*check_button, false, false);
	
	// Setup drag and drop	
	Gtk::TargetEntry target("application/x-toolbar-item", 0);
	button->drag_source_set(Gdk::BUTTON1_MASK, target, Gdk::ACTION_MOVE);
	toolbar->drag_dest_set(Gtk::DEST_DEFAULT_DROP, target, Gdk::ACTION_MOVE);
	toolbar->signal_drag_motion().connect(sigc::mem_fun(this, &Window::on_toolbar_drag_motion));
	toolbar->signal_drag_leave().connect(sigc::mem_fun(this, &Window::on_toolbar_drag_leave));
	toolbar->signal_drag_drop().connect(sigc::bind(sigc::mem_fun(this, &Window::on_toolbar_drag_drop), label));
	
	// Popup context menu	
	toolbar->signal_popup_context_menu().connect(sigc::mem_fun(this, &Window::on_popup_context_menu));
	table->show_all();
}

Window::~Window()
{
}

void
Window::on_change_orientation(Gtk::CheckButton *button)
{
	using namespace Gtk;
	Orientation orientation = button->get_active() ? ORIENTATION_VERTICAL : ORIENTATION_HORIZONTAL;
	
	toolbar->ref();	
	table->remove(*toolbar);
	toolbar->set_orientation(orientation);
	
	if (orientation == Gtk::ORIENTATION_HORIZONTAL)
	{
		table->attach(*toolbar, 0, 2, 0, 1, Gtk::FILL | Gtk::EXPAND, Gtk::FILL);
	}
	else
	{
		table->attach(*toolbar, 0, 1, 0, 4, Gtk::FILL, Gtk::FILL | Gtk::EXPAND);
	}
	toolbar->unref();
}

void
Window::on_change_show_arrow(Gtk::CheckButton *button)
{
	toolbar->set_show_arrow(button->get_active());
}

void
Window::on_set_toolbar_style(Gtk::CheckButton *button)
{
	Gtk::ComboBox *option_menu = reinterpret_cast<Gtk::ComboBox*>(button->get_data("option-menu"));
	
	if (button->get_active())
	{
		int style = option_menu->get_active();
		toolbar->set_style((Gtk::ToolbarStyle)style);
		option_menu->set_sensitive(true);
	}
	else
	{
		toolbar->unset_style();
		option_menu->set_sensitive(false);
	}
}

void
Window::on_change_toolbar_style(Gtk::ComboBox *option_menu)
{
	Gtk::ToolbarStyle style = static_cast<Gtk::ToolbarStyle>(option_menu->get_active());
	toolbar->set_style(style);
}

void
Window::on_reload_clicked()
{
	static Gdk::Atom atom_rcfiles = GDK_NONE;
	
	if (!atom_rcfiles)
		atom_rcfiles = gdk_atom_intern("_GTK_READ_RCFILES", false);
	
	GdkEventClient sev;
	for(int i = 0; i < 5; i++)
	{
		sev.data.l[i] = 0;
	}
	sev.data_format = 32;
	sev.message_type = atom_rcfiles;
	gdk_event_send_clientmessage_toall((GdkEvent *)&sev);
}

void
Window::on_bold_toggled(Gtk::ToggleToolButton *button)
{
	std::cout << "Bold toggled (active=" << button->get_active() << ")" << std::endl;
}

void
Window::on_rtl_toggled(Gtk::CheckButton *button)
{
	if (button->get_active())
		Gtk::Widget::set_default_direction(Gtk::TEXT_DIR_RTL);
	else
		Gtk::Widget::set_default_direction(Gtk::TEXT_DIR_LTR);
}

bool
Window::on_toolbar_drag_motion(Gtk::DragContext& context, int x, int y, unsigned int time)
{
	if (!drag_item)
	{
		// The inital ref() call also sinks the drag_item (see Gtk::Object::ref()).	
		drag_item = new Gtk::ToolButton("A quite long button");
		drag_item->ref(); 
	}
	
	context.drag_status(Gdk::ACTION_MOVE, time);
	int index = toolbar->get_drop_index(x, y);
	toolbar->set_drop_highlight_item(*drag_item, index);
	return true;
}

void
Window::on_toolbar_drag_leave(Gtk::DragContext& context, unsigned int time)
{
	if (drag_item)
	{
		drag_item->unref();
		drag_item = 0;
	}
	
	toolbar->unset_drop_highlight_item();
}

bool
Window::on_toolbar_drag_drop(Gtk::DragContext& context, int x, int y, unsigned int time, Gtk::Label *label)
{
	int drop_index = toolbar->get_drop_index(x, y);	
	String buffer = String::format("%d", drop_index);
	label->set_label(buffer);
	return true;
}

void 
Window::popup_menu_position(int *x, int *y, bool *push_in, Gdk::Point *point)
{
	if (x)
		*x = point->x();
	
	if (y)
		*y = point->y();
	
	if (push_in)
		*push_in = false;
}

bool
Window::on_popup_context_menu(int x, int y, int button_number)
{
	Gtk::Menu *menu = new Gtk::Menu;
	for (int i = 0; i < 5; i++)
	{
		String label = String::format("Item _%d", i);		
		Gtk::MenuItem *item = new Gtk::MenuItem(label, true);
		menu->append(*item);
	}
	menu->show_all();
	
	if (button_number != -1)
	{
		Gdk::Point *point = new Gdk::Point(x, y);
		unsigned int time = Main::get_current_event_time();
		menu->popup(button_number, sigc::bind(sigc::mem_fun(this, &Window::popup_menu_position), point), time);
	}
	else
		menu->popup(0);
	
	return true;
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

