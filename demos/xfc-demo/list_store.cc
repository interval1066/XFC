/* Tree View/List Store
 *
 * The Gtk::ListStore is used to store data in list form, to be used
 * later on by a Gtk::TreeView to display it. This demo builds a
 * simple Gtk::ListStore and displays it. See the Stock Browser
 * demo for a more advanced example.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/cellrenderertoggle.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

struct Bug
{
	bool fixed;
	unsigned int number;
	String severity;
	String description;

	Bug(bool fixed_, unsigned int number_, const char *severity_, const char *description_);
};

struct BugList : public Gtk::ListStore
{
	std::vector<Bug> data;

	BugList();
	~BugList();

	void add_items();
};

class ListStoreWindow : public Gtk::Window
{
	Pointer<BugList> model;
	Pointer<Gtk::TreeView> tree_view;

	void on_fixed_toggled(const String& path_str);

public:
	ListStoreWindow();
	~ListStoreWindow();

	void add_columns();
};
//!

const int COLUMN_FIXED = 0;
const int COLUMN_NUMBER = 1;
const int COLUMN_SEVERITY = 2;
const int COLUMN_DESCRIPTION = 3;
const int NUM_COLUMNS = 4;

// Bug

Bug::Bug(bool fixed_, unsigned int number_, const char *severity_, const char *description_)
: fixed(fixed_), number(number_), severity(severity_), description(description_)
{
}

// BugList

BugList::BugList()
: Gtk::ListStore(NUM_COLUMNS, G_TYPE_BOOLEAN, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING)
{
	add_items();
	int count = data.size();
	for (int i = 0; i < count; i++)
	{
		Gtk::TreeIter iter = append();
		set_value(iter, COLUMN_FIXED, data[i].fixed);
		set_value(iter, COLUMN_NUMBER, data[i].number);
		set_value(iter, COLUMN_SEVERITY, data[i].severity);
		set_value(iter, COLUMN_DESCRIPTION, data[i].description);
	}
}

BugList::~BugList()
{
}

void
BugList::add_items()
{
	data.push_back(Bug(false, 60482, "Normal", "scrollable notebooks and hidden tabs"));
	data.push_back(Bug(false, 60620, "Critical", "gdk_window_clear_area (gdkwindow-win32.c) is not thread-safe"));
	data.push_back(Bug(false, 50214, "Major", "Xft support does not clean up correctly"));
	data.push_back(Bug(true,  52877, "Major", "GtkFileSelection needs a refresh method. "));
	data.push_back(Bug(false, 56070, "Normal", "Can't click button after setting in sensitive"));
	data.push_back(Bug(true,  56355, "Normal", "GtkLabel - Not all changes propagate correctly"));
	data.push_back(Bug(false, 50055, "Normal", "Rework width/height computations for TreeView"));
	data.push_back(Bug(false, 58278, "Normal", "gtk_dialog_set_response_sensitive () doesn't work"));
	data.push_back(Bug(false, 55767, "Normal", "Getters for all setters"));
	data.push_back(Bug(false, 56925, "Normal", "Gtkcalender size"));
	data.push_back(Bug(false, 56221, "Normal", "Selectable label needs right-click copy menu"));
	data.push_back(Bug(true,  50939, "Normal", "Add shift clicking to GtkTextView"));
	data.push_back(Bug(false, 6112,  "Enhancement", "netscape-like collapsable toolbars"));
	data.push_back(Bug(false, 1, "Normal", "First bug :=)"));
}

// ListStoreWindow

ListStoreWindow::ListStoreWindow()
{
	set_title("Gtk::ListStore demo");
	set_border_width(8);
	set_default_size(280, 250);

	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	add(*vbox);

	Gtk::Label *label = new Gtk::Label("This is the bug list (note: not based on real data, it would be nice to have a nice ODBC interface to bugzilla or so, though).");
	vbox->pack_start(*label, false, false);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	sw->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	vbox->pack_start(*sw);

	// Create model
	model = new BugList;

	// Create TreeView
	tree_view = new Gtk::TreeView(*model);
	tree_view->set_rules_hint(true);
	tree_view->set_search_column(COLUMN_DESCRIPTION);
	sw->add(*tree_view);

	// Add columns to the tree view
	add_columns();
	show_all();
}

ListStoreWindow::~ListStoreWindow()
{
}

void
ListStoreWindow::add_columns()
{
	// Column for fixed toggles
	Gtk::CellRendererToggle *toggle_renderer = new Gtk::CellRendererToggle;
	toggle_renderer->signal_toggled().connect(sigc::mem_fun(this, &ListStoreWindow::on_fixed_toggled));
	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Fixed?", *toggle_renderer, "active", COLUMN_FIXED);

	// Set this column to a fixed sizing (of 50 pixels)
	column->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
	column->set_fixed_width(50);
	tree_view->append_column(*column);

	// Column for bug numbers
	Gtk::CellRendererText *renderer = new Gtk::CellRendererText;
	column = new Gtk::TreeViewColumn("Bug number", *renderer, "text", COLUMN_NUMBER);
	column->set_sort_column_id(COLUMN_NUMBER);
	tree_view->append_column(*column);

	// Column for severities
	renderer = new Gtk::CellRendererText;
	column = new Gtk::TreeViewColumn("Severity", *renderer, "text", COLUMN_SEVERITY);
	column->set_sort_column_id(COLUMN_SEVERITY);
	tree_view->append_column(*column);

	// Column for description
	renderer = new Gtk::CellRendererText;
	column = new Gtk::TreeViewColumn("Description", *renderer, "text", COLUMN_DESCRIPTION);
	column->set_sort_column_id(COLUMN_DESCRIPTION);
	tree_view->append_column(*column);
}

void

ListStoreWindow::on_fixed_toggled(const String& path_str)
{
	Gtk::TreeIter iter;
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);

	// Get toggled iter
	model->get_iter(iter, *path);
	bool fixed;
	model->get_value(iter, COLUMN_FIXED, fixed);

	// Do something with the value
	fixed ^= 1;

	// Set new value
	model->set_value(iter, COLUMN_FIXED, fixed);
}

Gtk::Window*
do_list_store(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ListStoreWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

