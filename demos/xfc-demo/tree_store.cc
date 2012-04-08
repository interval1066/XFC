/* Tree View/Tree Store
 *
 * The Gtk::TreeStore is used to store data in tree form, to be
 * used later on by a Gtk::TreeView to display it. This demo builds
 * a simple Gtk::TreeStore and displays it. If you're new to the
 * Gtk::TreeView widgets and associates, look into the Gtk::ListStore
 * example first.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/cellrenderertoggle.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/treestore.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

struct HolidayItem
{
	String label;
	bool alex;
	bool havoc;
	bool tim;
	bool owen;
	bool dave;
	bool world_holiday; // shared by the European hackers
	std::vector<HolidayItem> children;

	HolidayItem(const char *label_, bool alex_, bool havoc_, bool tim_, bool owen_, bool dave_, bool world_holday_);
};

struct HolidayTree : public Gtk::TreeStore
{
	std::vector<HolidayItem> toplevel;

	HolidayTree();
	~HolidayTree();

	void add_items();
};

class TreeStoreWindow : public Gtk::Window
{
	Pointer<HolidayTree> model;
	Pointer<Gtk::TreeView> tree_view;

	void on_item_toggled(const String& path_str, int column);

public:
	TreeStoreWindow();
	~TreeStoreWindow();

	void add_columns();
};
//!

const int HOLIDAY_NAME_COLUMN = 0;
const int ALEX_COLUMN = 1;
const int HAVOC_COLUMN = 2;
const int TIM_COLUMN = 3;
const int OWEN_COLUMN = 4;
const int DAVE_COLUMN = 5;
const int VISIBLE_COLUMN = 6;
const int WORLD_COLUMN = 7;
const int NUM_COLUMNS = 8;

// HolidayItem

HolidayItem::HolidayItem(const char *label_, bool alex_, bool havoc_, bool tim_, bool owen_, bool dave_, bool world_holiday_)
: label(label_), alex(alex_), havoc(havoc_), tim(tim_), owen(owen_), dave(dave_), world_holiday(world_holiday_)
{
}

// HolidayTree

HolidayTree::HolidayTree()
: Gtk::TreeStore(NUM_COLUMNS, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN)
{
	add_items();

	// Add data to the tree store
	int count = toplevel.size();
	for (int i = 0; i < count; i++)
	{
		Gtk::TreeIter iter = append();
		set_value(iter, HOLIDAY_NAME_COLUMN, toplevel[i].label);
		set_value(iter, ALEX_COLUMN, false);
		set_value(iter, HAVOC_COLUMN, false);
		set_value(iter, TIM_COLUMN, false);
		set_value(iter, OWEN_COLUMN, false);
		set_value(iter, DAVE_COLUMN, false);
		set_value(iter, VISIBLE_COLUMN, false);
		set_value(iter, WORLD_COLUMN, false);

		// Add children
		int child_count = toplevel[i].children.size();
		for (int j = 0; j < child_count; j++)
		{
			Gtk::TreeIter child_iter = append(&iter);
			set_value(child_iter, HOLIDAY_NAME_COLUMN, toplevel[i].children[j].label);
			set_value(child_iter, ALEX_COLUMN, toplevel[i].children[j].alex);
			set_value(child_iter, HAVOC_COLUMN, toplevel[i].children[j].havoc);
			set_value(child_iter, TIM_COLUMN, toplevel[i].children[j].tim);
			set_value(child_iter, OWEN_COLUMN, toplevel[i].children[j].owen);
			set_value(child_iter, DAVE_COLUMN, toplevel[i].children[j].dave);
			set_value(child_iter, VISIBLE_COLUMN, true);
			set_value(child_iter, WORLD_COLUMN, toplevel[i].children[j].world_holiday);
		}
	}
}

HolidayTree::~HolidayTree()
{
}

void
HolidayTree::add_items()
{
	// Janurary
	toplevel.push_back(HolidayItem("January", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("New Years Day", true, true, true, true, false, true));
	toplevel.back().children.push_back(HolidayItem("Presidential Inauguration", false, true, false, true, false, false));
	toplevel.back().children.push_back(HolidayItem("Martin Luther King Jr. day", false, true, false, true, false, false));

	// Feburary
	toplevel.push_back(HolidayItem("February", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Presidents' Day", false, true, false, true, false, false));
	toplevel.back().children.push_back(HolidayItem("Groundhog Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Valentine's Day", false, false, false, false, true, true));

	// March
	toplevel.push_back(HolidayItem("Mar.hh", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("National Tree Planting Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("St Patrick's Day", false, false, false, false, false, true));

	// April
	toplevel.push_back(HolidayItem("April", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("April Fools' Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Army Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Earth Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Administrative Professionals' Day", false, false, false, false, false, false));

	// May
	toplevel.push_back(HolidayItem("May", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Nurses' Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("National Day of Prayer", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Mothers' Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Armed Forces Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Memorial Day", true, true, true, true, false, true));

	// June
	toplevel.push_back(HolidayItem("June", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("June Fathers' Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Juneteenth (Liberation of Slaves)", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Flag Day", false, true, false, true, false, false));

	// July
	toplevel.push_back(HolidayItem("July", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Parents' Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Independence Day", false, true, false, true, false, false));

	// August
	toplevel.push_back(HolidayItem("August", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Air Force Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Coast Guard Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Friendship Day", false, false, false, false, false, false));

	// September
	toplevel.push_back(HolidayItem("September", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Grandparents' Day", false, false, false, false, false, true));
	toplevel.back().children.push_back(HolidayItem("Citizenship Day or Constitution Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Labor Day", true, true, true, true, false, true));

	// October
	toplevel.push_back(HolidayItem("October", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("National Children's Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Bosses' Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Sweetest Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Mother-in-Law's Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Navy Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Columbus Day", false, true, false, true, false, false));
	toplevel.back().children.push_back(HolidayItem("Halloween", false, false, false, false, false, true));

	// November
	toplevel.push_back(HolidayItem("November", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Marine Corps Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Veterans' Day", true, true, true, true, false, true));
	toplevel.back().children.push_back(HolidayItem("Thanksgiving", false, true, false, true, false, false));

	// December
	toplevel.push_back(HolidayItem("December", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Pearl Harbor Remembrance Day", false, false, false, false, false, false));
	toplevel.back().children.push_back(HolidayItem("Christmas", true, true, true, true, false, true));
	toplevel.back().children.push_back(HolidayItem("Kwanzaa", false, false, false, false, false, false));
}

// TreeStoreWindow

TreeStoreWindow::TreeStoreWindow()
{
	// Create window, etc
	set_title("Card planning sheet");
	set_default_size(650, 400);

	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(8);
	add(*vbox);

	Gtk::Label *label = new Gtk::Label("Jonathan's Holiday Card Planning Sheet");
	vbox->pack_start(*label, false, false);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	sw->set_policy_automatic();
	vbox->pack_start(*sw);

	// Create model
	model = new HolidayTree;

	// Create TreeView
	tree_view = new Gtk::TreeView(*model);
	tree_view->set_rules_hint(true);
	tree_view->get_selection()->set_mode(Gtk::SELECTION_MULTIPLE);
	add_columns();
	sw->add(*tree_view);

	// Expand all rows after the treeview widget has been realized
	tree_view->signal_realize().connect(sigc::mem_fun(*tree_view, &Gtk::TreeView::expand_all));
	show_all();
}

TreeStoreWindow::~TreeStoreWindow()
{
}

void
TreeStoreWindow::add_columns()
{
	using namespace sigc;

	// Column for holiday names
	Gtk::CellRendererText *text_renderer = new Gtk::CellRendererText;
	text_renderer->property_xalign().set(0.0);
	Gtk::CellColumnAttributes attributes("text", HOLIDAY_NAME_COLUMN);
	int col_offset = tree_view->append_column("Holiday", *text_renderer, attributes);
	Gtk::TreeViewColumn *column = tree_view->get_column(col_offset - 1);
	column->set_clickable(true);

	// Alex column
	Gtk::CellRendererToggle *renderer = new Gtk::CellRendererToggle;
	renderer->property_xalign().set(0.0);
	renderer->signal_toggled().connect(bind(mem_fun(this, &TreeStoreWindow::on_item_toggled), ALEX_COLUMN));
	attributes.clear();
	attributes.add("active", ALEX_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	attributes.add("activatable", WORLD_COLUMN);
	col_offset = tree_view->append_column("Alex", *renderer, attributes);
	column = tree_view->get_column(col_offset - 1);
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	column->set_clickable(true);

	// Havoc column
	renderer = new Gtk::CellRendererToggle;
	renderer->property_xalign().set(0.0);
	renderer->signal_toggled().connect(bind(mem_fun(this, &TreeStoreWindow::on_item_toggled), HAVOC_COLUMN));
	attributes.clear();
	attributes.add("active", HAVOC_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	col_offset = tree_view->append_column("Havoc", *renderer, attributes);
	column = tree_view->get_column(col_offset - 1);
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	column->set_clickable(true);

	// Tim column
	renderer = new Gtk::CellRendererToggle;
	renderer->property_xalign().set(0.0);
	renderer->signal_toggled().connect(bind(mem_fun(this, &TreeStoreWindow::on_item_toggled), TIM_COLUMN));
	attributes.clear();
	attributes.add("active", TIM_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	col_offset = tree_view->append_column("Tim", *renderer, attributes);
	column = tree_view->get_column(col_offset - 1);
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	column->set_clickable(true);

	// Owen column
	renderer = new Gtk::CellRendererToggle;
	renderer->property_xalign().set(0.0);
	renderer->signal_toggled().connect(bind(mem_fun(this, &TreeStoreWindow::on_item_toggled), OWEN_COLUMN));
	attributes.clear();
	attributes.add("active", OWEN_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	col_offset = tree_view->append_column("Owen", *renderer, attributes);
	column = tree_view->get_column(col_offset - 1);
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	column->set_clickable(true);

	// Dave column
	renderer = new Gtk::CellRendererToggle;
	renderer->property_xalign().set(0.0);
	renderer->signal_toggled().connect(bind(mem_fun(this, &TreeStoreWindow::on_item_toggled), DAVE_COLUMN));
	attributes.clear();
	attributes.add("active", DAVE_COLUMN);
	attributes.add("visible", VISIBLE_COLUMN);
	col_offset = tree_view->append_column("Dave", *renderer, attributes);
	column = tree_view->get_column(col_offset - 1);
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	column->set_clickable(true);
}

void
TreeStoreWindow::on_item_toggled (const String& path_str, int column)
{
	Gtk::TreeIter iter;
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);

	// Get toggled iter
	model->get_iter(iter, *path);
	bool toggle_item;
	model->get_value(iter, column, toggle_item);

	// Do something with the value
	toggle_item ^= 1;

	// Set new value
	model->set_value(iter, column, toggle_item);
}

Gtk::Window*
do_tree_store(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new TreeStoreWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

