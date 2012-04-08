#include "notebook.hh"
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/table.hh>

// Notebook

Notebook::Notebook()
{
	set_tab_pos(Gtk::POS_TOP);
	show();
}

Notebook::~Notebook()
{
}

void
Notebook::on_rotate_book()
{
	// This function rotates the position of the tabs
	set_tab_pos((Gtk::PositionType)((gtk_notebook()->tab_pos + 1) % 4));
}

void
Notebook::on_tabsborder_book()
{
	// Add/Remove the page tabs and the borders
	int tval = false;
	int bval = false;

	if (!get_show_tabs())
		tval = true;
	if (!get_show_border())
		bval = true;

	set_show_tabs(tval);
	set_show_border(bval);
}

void
Notebook::on_remove_book()
{
	// Remove a page from the notebook
    int page = get_current_page();
    remove_page(page);

	// Need to refresh the widget -- This forces the widget to redraw itself.
    queue_draw();
}

// NotebookWindow

NotebookWindow::NotebookWindow()
{
	set_title("Notebook Example");
	set_border_width(10);

	Gtk::Table *table = new Gtk::Table(3, 6);
	add(*table);

	// Create a new notebook, place the position of the tabs
	Notebook *notebook = new Notebook;
	table->attach(*notebook, 0, 6, 0, 1);

	// Let's append a bunch of pages to the notebook
	Gtk::Label *label;
	for (int i = 0; i < 5; i++)
	{
		String s1 = String::format("Append Frame %d", i + 1);
		String s2 = String::format("Page %d", i + 1);

		Gtk::Frame *frame = new Gtk::Frame(s1);
		frame->set_border_width(10);
		frame->set_size_request(100, 75);

		label = new Gtk::Label(s1);
		frame->add(*label);

		label = new Gtk::Label(s2);
		notebook->append_page(*frame, label);
	}

	// Now let's add a page to a specific spot
	Gtk::CheckButton *checkbutton = new Gtk::CheckButton("Check me please!");
	checkbutton->set_size_request(100, 75);

	label = new Gtk::Label("Add page");
	notebook->insert_page(*checkbutton, 2, label);

	// Now finally let's prepend pages to the notebook
	for (int i = 0; i < 5; i++)
	{
		String s1 = String::format("Prepend Frame %d", i + 1);
		String s2 = String::format("PPage %d", i + 1);

		Gtk::Frame *frame = new Gtk::Frame(s1);
		frame->set_border_width(10);
		frame->set_size_request(100, 75);

		label = new Gtk::Label(s1);
		frame->add(*label);

		label = new Gtk::Label(s2);
		notebook->prepend_page(*frame, label);
	}

	// Set what page to start at (page 4)
	notebook->set_current_page(3);

	// Create a bunch of buttons
	Gtk::Button *button = new Gtk::Button("close");
	button->signal_clicked().connect(sigc::mem_fun(this, &NotebookWindow::dispose));
	table->attach(*button, 0, 1, 1, 2);

	button = new Gtk::Button("next page");
	button->signal_clicked().connect(sigc::mem_fun(notebook, &Notebook::next_page));
	table->attach(*button, 1, 2, 1, 2);

	button = new Gtk::Button("prev page");
	button->signal_clicked().connect(sigc::mem_fun(notebook, &Notebook::prev_page));
	table->attach(*button, 2, 3, 1, 2);

	button = new Gtk::Button("tab position");
	button->signal_clicked().connect(sigc::mem_fun(notebook, &Notebook::on_rotate_book));
	table->attach(*button, 3, 4, 1, 2);

	button = new Gtk::Button("tabs/border on/off");
	button->signal_clicked().connect(sigc::mem_fun(notebook, &Notebook::on_tabsborder_book));
	table->attach(*button, 4, 5, 1, 2);

	button = new Gtk::Button("remove page");
	button->signal_clicked().connect(sigc::mem_fun(notebook, &Notebook::on_remove_book));
	table->attach(*button, 5, 6, 1, 2);

	table->show_all();
}

NotebookWindow::~NotebookWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	NotebookWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}
