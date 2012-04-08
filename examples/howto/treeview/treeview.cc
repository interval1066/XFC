#include "treeview.hh"
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/cellrenderertoggle.hh>
#include <iostream>

enum
{
   TITLE_COLUMN,
   AUTHOR_COLUMN,
   CHECKED_COLUMN,
   N_COLUMNS
};

TreeViewWindow::TreeViewWindow()
{
	set_title("TreeView Example");

	// We'll create a TreeStore model but this could be any model. The model pointer
	// is a smart pointer because we own the initial reference and it must be freed.
	model = new Gtk::TreeStore(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN);

	// Populate the model with data. First acquire a top-level iterator.
	Gtk::TreeIter parent_iter = model->append();

	// Then, set the cell values
	model->set_value(parent_iter, TITLE_COLUMN, "The Art of Computer Programming");
	model->set_value(parent_iter, AUTHOR_COLUMN, "Donald E. Knuth");
	model->set_value(parent_iter, CHECKED_COLUMN, false);

	// Then, acquire a child iterator and set the values for the child cells
	Gtk::TreeIter child_iter = model->append(&parent_iter);
	model->set_value(child_iter, TITLE_COLUMN, "Volume 1: Fundamental Algorithms");
	model->set_value(child_iter, CHECKED_COLUMN, false);

	child_iter = model->append(&parent_iter);
	model->set_value(child_iter, TITLE_COLUMN, "Volume 2: Seminumerical Algorithms");
	model->set_value(child_iter, CHECKED_COLUMN, false);

	child_iter = model->append(&parent_iter);
	model->set_value(child_iter, TITLE_COLUMN, "Volume 3: Sorting and Searching");
	model->set_value(child_iter, CHECKED_COLUMN, false);

	// Create a TreeView
	tree_view = new Gtk::TreeView(*model);

	// You can't create a TreeSelection, you have to retrieve it from the TreeView.
	Gtk::TreeSelection *selection = tree_view->get_selection();
	selection->set_mode (Gtk::SELECTION_SINGLE);
	selection->signal_changed().connect(sigc::mem_fun(this, &TreeViewWindow::on_selection));

	// Create a text cell render and arbitrarily make it red for demonstration purposes.
	Gtk::CellRendererText *renderer = new Gtk::CellRendererText;
	renderer->property_foreground().set("red");

	// Create first column, associating the "text" attribute of the cell_renderer with the first column of the model
	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Author", *renderer, "text", AUTHOR_COLUMN);

	// Add the column to the view.
	tree_view->append_column(*column);

	// Create second column. The title of the book.
	renderer = new Gtk::CellRendererText;
	column = new Gtk::TreeViewColumn("Title", *renderer, "text", TITLE_COLUMN);
	tree_view->append_column(*column);

	// Create last column. Whether a book is checked out.
	Gtk::CellRendererToggle *toggle_renderer = new Gtk::CellRendererToggle;
	toggle_renderer->signal_toggled().connect(sigc::mem_fun(this, &TreeViewWindow::on_toggled));
	column = new Gtk::TreeViewColumn("Check out", *toggle_renderer, "active", CHECKED_COLUMN);
	tree_view->append_column(*column);

	// Now we can manipulate the view just like any other widget
	add(*tree_view);
	tree_view->show_all();
}


TreeViewWindow::~TreeViewWindow()
{
}

void 
TreeViewWindow::on_selection()
{
    Gtk::TreeIter iter;
	Gtk::TreeSelection *selection = tree_view->get_selection();

	if (selection->get_selected(&iter))
    {
        String title;
	model->get_value(iter, TITLE_COLUMN, title);
        std::cout << "You selected a book with the title \"" << title << "\"" << std::endl;
    }
}

void
TreeViewWindow::on_toggled(const String& path_str)
{
	Gtk::TreeIter iter;
	Pointer<Gtk::TreePath> path = new Gtk::TreePath(path_str);

	// Get toggled iter
	model->get_iter(iter, *path);
	bool checked;
	model->get_value(iter, CHECKED_COLUMN, checked);

	// Do something with the value
	checked ^= 1;

	// Set new value for the CHECKED_COLUMN
	model->set_value(iter, CHECKED_COLUMN, checked);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	TreeViewWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}
