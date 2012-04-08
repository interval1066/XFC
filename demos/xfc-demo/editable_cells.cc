/* Tree View/Editable Cells
 *
 * This demo demonstrates the use of editable cells in a Gtk::TreeView. If
 * you're new to the Gtk::TreeView widgets and associates, look into
 * the Gtk::ListStore example first.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>
#include <xfc/glib/value.hh>
#include <algorithm>
#include <cstdlib>

using namespace Xfc;

struct Item
{
	int number;
	String product;
	bool editable;
	
	Item(int number_, const char *product_, bool editable_);
};

struct ItemList : public Gtk::ListStore
{
	std::vector<Item> articles;
	
	ItemList();
	~ItemList();
	
	void add_items();
	void add_item(Item& item);
	void remove_item(int index);
};

class EditableCellsWindow : public Gtk::Window
{
	Pointer<ItemList> model;
	Pointer<Gtk::TreeView> tree_view;

	void on_cell_edited(const String& path_string, const String& new_text, int column);

public:
	EditableCellsWindow();
	~EditableCellsWindow();

	void add_columns();

	void on_add_item();
	void on_remove_item();
};
//!

const int COLUMN_NUMBER = 0;
const int COLUMN_PRODUCT = 1;
const int COLUMN_EDITABLE = 2;
const int NUM_COLUMNS = 3;

// Item

Item::Item(int number_, const char *product_, bool editable_)
: number(number_), product(product_), editable(editable_)
{
}

// ItemList

ItemList::ItemList()
: Gtk::ListStore(NUM_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_BOOLEAN)
{
	add_items();
	int count = articles.size();
	for (int i = 0; i < count; i++)
	{
		Gtk::TreeIter iter = append();
		set_value(iter, COLUMN_NUMBER, articles[i].number);
		set_value(iter, COLUMN_PRODUCT, articles[i].product);
		set_value(iter, COLUMN_EDITABLE, articles[i].editable);
	}
}

ItemList::~ItemList()
{
}

void
ItemList::add_items()
{
	articles.push_back(Item(3, "bottles of coke", true));
	articles.push_back(Item(5, "packages of noodles", true));
	articles.push_back(Item(2, "packages of chocolate chip cookies", true));
	articles.push_back(Item(1, "can vanilla ice cream", true));
	articles.push_back(Item(6, "eggs", true));
}

void
ItemList::add_item(Item& item)
{
	articles.push_back(item);
}

void
ItemList::remove_item(int index)
{
	articles.erase(articles.begin() + index);
}

// EditableCellsWindow

EditableCellsWindow::EditableCellsWindow()
{
	set_title("Shopping list");
	set_border_width(5);
	set_default_size(320, 200);

	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	add(*vbox);

	Gtk::Label *label = new Gtk::Label("Shopping list (you can edit the cells!)");
	vbox->pack_start(*label, false, false);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	sw->set_policy_automatic();
	vbox->pack_start(*sw);

	// Create model
	model = new ItemList;

	// Create TreeView
	tree_view = new Gtk::TreeView(*model);
	tree_view->set_rules_hint(true);
	tree_view->get_selection()->set_mode(Gtk::SELECTION_SINGLE);
	add_columns();
	sw->add(*tree_view);

	// Some buttons
	Gtk::HBox *hbox = new Gtk::HBox(true, 4);
      	vbox->pack_start(*hbox, false, false);

	Gtk::Button *button = new Gtk::Button("Add item");
	button->signal_clicked().connect(sigc::mem_fun(this, &EditableCellsWindow::on_add_item));
	hbox->pack_start(*button);

	button = new Gtk::Button("Remove item");
	button->signal_clicked().connect(sigc::mem_fun(this, &EditableCellsWindow::on_remove_item));
	hbox->pack_start(*button);
	show_all();
}

EditableCellsWindow::~EditableCellsWindow()
{
}

void
EditableCellsWindow::add_columns()
{
	// Number column
	Gtk::CellRendererText *renderer = new Gtk::CellRendererText;
	renderer->signal_edited().connect(sigc::bind(sigc::mem_fun(this, &EditableCellsWindow::on_cell_edited), COLUMN_NUMBER));
	Gtk::CellColumnAttributes attributes;
	attributes.add("text", COLUMN_NUMBER);
	attributes.add("editable", COLUMN_EDITABLE);
	tree_view->append_column("Number", *renderer, attributes);

	// Product column
	renderer = new Gtk::CellRendererText;
	renderer->signal_edited().connect(sigc::bind(sigc::mem_fun(this, &EditableCellsWindow::on_cell_edited), COLUMN_PRODUCT));
 	attributes.clear();
	attributes.add("text", COLUMN_PRODUCT);
	attributes.add("editable", COLUMN_EDITABLE);
	tree_view->append_column("Product", *renderer, attributes);
}

void
EditableCellsWindow::on_cell_edited(const String& path_string, const String& new_text, int column)
{
	Gtk::TreeIter iter;
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_string);
	model->get_iter(iter, *path);

	switch (column)
	{
	case COLUMN_NUMBER:
		{
			std::vector<int> indices = path->get_indices();
			int i = indices[0];
			model->articles[i].number = atoi(new_text.c_str());
			model->set_value(iter, column, model->articles[i].number);
      		}
      		break;

	case COLUMN_PRODUCT:
		{
			String old_text;
			model->get_value(iter, column, old_text);
			std::vector<int> indices = path->get_indices();
			int i = indices[0];
			model->articles[i].product = new_text;
			model->set_value(iter, column, model->articles[i].product);
      		}
      		break;
    	}
}

void
EditableCellsWindow::on_add_item()
{
	Item item(0, "Description here", true);
	model->add_item(item);
	Gtk::TreeIter iter = model->append();
	model->set_value(iter, COLUMN_NUMBER, item.number);
	model->set_value(iter, COLUMN_PRODUCT, item.product);
	model->set_value(iter, COLUMN_EDITABLE, item.editable);
}

void
EditableCellsWindow::on_remove_item()
{
	Gtk::TreeIter iter;
	Gtk::TreeSelection *selection = tree_view->get_selection();

	if (selection->get_selected(&iter))
	{
		Pointer<Gtk::TreePath> path = model->get_path(iter);
		model->remove(iter);
		model->remove_item(path->get_indices()[0]);
	}
}

Gtk::Window*
do_editable_cells(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new EditableCellsWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

