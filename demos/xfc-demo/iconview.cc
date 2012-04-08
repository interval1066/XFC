/* Icon View
 *
 * The Gtk::IconView widget is used to display and manipulate icons.
 * It uses a Gtk::TreeModel for data storage, so having a look at
 * the list store example might be helpful.
 */

#include "demowindow.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/iconview.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <xfc/glib/error.hh>
#include <xfc/glib/fileutils.hh>
#include <xfc/glib/utils.hh>

using namespace Xfc;

class IconViewList : public Gtk::ListStore
{
public:
	IconViewList();
	virtual ~IconViewList();
	
	int sort(const Gtk::TreeIter& a, const Gtk::TreeIter& b);
};

class IconView : public Gtk::IconView
{
	Pointer<Gdk::Pixbuf> file_pixbuf;
	Pointer<Gdk::Pixbuf> folder_pixbuf;
	
	IconViewList *store;
	std::string parent;

public:
	IconView(IconViewList *store_, const char *parent_);
	virtual ~IconView();
	
	bool is_root() const;

	void up();
	void home();
	void fill();
	void item_activated(const Gtk::TreePath& tree_path);	
	
	bool load_pixbufs(G::Error *error);
};

class IconViewWindow : public Gtk::Window
{
	Pointer<IconViewList> store;
	IconView *icon_view;
	Gtk::ToolButton *up_button;

protected:
	void on_up_clicked();
	void on_home_clicked();
	void on_item_activated(const Gtk::TreePath& tree_path);

public:
	IconViewWindow();
	virtual ~IconViewWindow();
};
//!

const int COLUMN_PATH = 0;
const int COLUMN_DISPLAY_NAME = 1;
const int COLUMN_PIXBUF = 2;
const int COLUMN_IS_DIRECTORY = 3;
const int NUM_COLUMNS = 4;

/*  IconViewList
 */ 

IconViewList::IconViewList()
: Gtk::ListStore(NUM_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF, G_TYPE_BOOLEAN)
{
	set_default_sort_func(sigc::mem_fun(this, &IconViewList::sort));
	set_sort_column_id(DEFAULT_SORT_COLUMN_ID, Gtk::SORT_ASCENDING);
}

IconViewList::~IconViewList()
{
}

int 
IconViewList::sort(const Gtk::TreeIter& a, const Gtk::TreeIter& b)
{
	// We need this function because we want to sort folders before files.
	
	bool is_dir_a;
	String name_a;
 	get_value(a, COLUMN_IS_DIRECTORY, is_dir_a);
 	get_value(a, COLUMN_DISPLAY_NAME, name_a);

 	bool is_dir_b;
	String name_b;
 	get_value(b, COLUMN_IS_DIRECTORY, is_dir_b);
 	get_value(b, COLUMN_DISPLAY_NAME, name_b);
 
	int result;	
	if (!is_dir_a && is_dir_b)
		result = 1;
	else if (is_dir_a && !is_dir_b)
		result = -1;
	else
		result = name_a.collate(name_b);
  
	return result;
}

/*  IconView
 */
 
IconView::IconView(IconViewList *store_, const char *parent_)
: store(store_), parent(parent_)
{
	set_model(store_);
}

IconView::~IconView()
{
}

bool
IconView::load_pixbufs(G::Error *error)
{
	// Loads the images for the demo and returns whether the operation succeeded.
	if (file_pixbuf)
		return true; // already loaded earlier

	String filename = DemoWindow::find_file("gnome-fs-regular.png", error);
	if (filename.null())
		return false; // note that "error" was filled in and returned.

	file_pixbuf = Gdk::Pixbuf::create(filename, error);
	if (!file_pixbuf)
		return  false; // note that "error" was filled in  and returned

	filename = DemoWindow::find_file("gnome-fs-directory.png", error);
	if (filename.null())
		return false; // note that "error" was filled in and returned.

	folder_pixbuf = Gdk::Pixbuf::create(filename, error);
	if (!folder_pixbuf)
		return  false; // note that "error" was filled in  and returned

	return true;
}

bool 
IconView::is_root() const
{
	return parent.compare("/") != 0;
}

void
IconView::up()
{
	parent = G::path_get_dirname(parent);
	fill();
}

void
IconView::home()
{
	parent = G::get_home_dir();
	fill();
}

void 
IconView::item_activated(const Gtk::TreePath& tree_path)
{
	Gtk::TreeIter iter;
	std::string path;
	bool is_dir; 
	
	store->get_iter(iter, tree_path);
	store->get_value(iter, COLUMN_PATH, path);
	store->get_value(iter, COLUMN_IS_DIRECTORY, is_dir);

	if (!is_dir)
		return;
  
	// Replace parent with path and re-fill the model
	parent.assign(path);
	fill();
}

void 
IconView::fill()
{
	// First clear the store
	store->clear();
  
	// Now go through the directory and extract all the file information
	G::Error error;	
	G::Dir dir(parent, &error);
	if (error.get())
		return;
	
	const char *name = dir.read_name();
	while (name != 0)
	{
		// We ignore hidden files that start with a '.'
		if (name[0] != '.')
		{
			std::string path = G::build_filename(parent, name);
			bool is_dir = G::file_test(path, G::FILE_TEST_IS_DIR);
			String display_name = String::from_filename(name);
			Gtk::TreeIter iter = store->append();
			store->set_value(iter, COLUMN_PATH, path);
			store->set_value(iter, COLUMN_DISPLAY_NAME, display_name);
			store->set_value(iter, COLUMN_PIXBUF, is_dir ? folder_pixbuf : file_pixbuf);
			store->set_value(iter, COLUMN_IS_DIRECTORY, is_dir);
		}
		name = dir.read_name();      
	}
}

/*  IconViewWindow
 */ 

IconViewWindow::IconViewWindow()
{
	set_title("Gtk::IconView demo");
	set_default_size(650, 400);

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);
	
	Gtk::Toolbar *tool_bar = new Gtk::Toolbar;
	vbox->pack_start(*tool_bar, false, false);
		
	up_button = new Gtk::ToolButton(Gtk::StockId::GO_UP);
	up_button->set_is_important(true);
	up_button->set_sensitive(false);
	up_button->signal_clicked().connect(sigc::mem_fun(this, &IconViewWindow::on_up_clicked));
	tool_bar->append(*up_button);
		
	Gtk::ToolButton *home_button = new Gtk::ToolButton(Gtk::StockId::HOME);
	home_button->set_is_important(true);
	home_button->signal_clicked().connect(sigc::mem_fun(this, &IconViewWindow::on_home_clicked));
	tool_bar->append(*home_button);
		
	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	sw->set_policy_automatic();
	vbox->pack_start(*sw);
		
		// Create the list store and fill it with the contents of '/'
	store = new IconViewList;		
	icon_view = new IconView(store, "/");
	
	G::Error error;
	if (!icon_view->load_pixbufs(&error))
	{
		Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
		dialog.format_message("Unable to open image file 'gtk-logo-rgb.gif': %s", error.message());
		dialog.set_position(Gtk::WIN_POS_CENTER);
		if (dialog.run())
			dialog.dispose();
	}
	else
	{
		icon_view->fill();
		icon_view->set_selection_mode(Gtk::SELECTION_MULTIPLE);
		
		// We now set which model columns that correspont to the text and pixbuf of each item.
		icon_view->set_text_column(COLUMN_DISPLAY_NAME);
		icon_view->set_pixbuf_column(COLUMN_PIXBUF);
		
		// Connect to the "item_activated" signal
		icon_view->signal_item_activated().connect(sigc::mem_fun(this, &IconViewWindow::on_item_activated));
			
		sw->add(*icon_view);
		icon_view->grab_focus();
	}
	show_all();
}

IconViewWindow::~IconViewWindow()
{
}

void
IconViewWindow::on_up_clicked()
{
	icon_view->up();
	
	// Maybe de-sensitize the up button
	up_button->set_sensitive(icon_view->is_root());
}

void
IconViewWindow::on_home_clicked()
{
	icon_view->home();
	
	// Sensitize the up button
	up_button->set_sensitive(true);
}

void 
IconViewWindow::on_item_activated(const Gtk::TreePath& tree_path)
{
	icon_view->item_activated(tree_path);
	
	// Sensitize the up button
	up_button->set_sensitive(true);
}

Gtk::Window*
do_iconview(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new IconViewWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

