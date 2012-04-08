#include "paned.hh"
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/paned.hh>
#include <xfc/gtk/textview.hh>
#include <xfc/gtk/treeview.hh>

// MessageList

MessageList::MessageList()
{
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	Pointer<Gtk::ListStore> model = new Gtk::ListStore(1, G_TYPE_STRING);
	Gtk::TreeView *tree_view = new Gtk::TreeView(*model);
	add_with_viewport(*tree_view);
	tree_view->show();

	// Add some messages to the window
	for (int i = 0; i < 10; i++)
	{
        	String msg = String::format("Message #%d", i);
        	Gtk::TreeIter iter = model->append();
        	model->set_value(iter, 0, msg);
	}

	Gtk::CellRendererText *cell = new Gtk::CellRendererText;
	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn ("Messages", *cell, "text", 0);
	tree_view->append_column(*column);
}

MessageList::~MessageList()
{
}

// TextWindow

TextWindow::TextWindow()
{
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	
	Gtk::TextView *view = new Gtk::TextView;
	Gtk::TextBuffer *buffer = view->get_buffer();
	add(*view);

	// Add some text to our text widget
	Gtk::TextIter iter = buffer->get_iter_at_offset(0);
	buffer->insert(iter, "From: pathfinder@nasa.gov\n"
	                     "To: mom@nasa.gov\n"
	                     "Subject: Made it!\n"
	                     "\n"
	                     "We just got in this morning. The weather has been\n"
	                     "great - clear but cold, and there are lots of fun sights.\n"
	                     "Sojourner says hi. See you soon.\n"
	                     " -Path\n");
	show_all();
}

TextWindow::~TextWindow()
{
}

// PanedWindow

PanedWindow::PanedWindow()
{
	set_title("Paned Windows");
	set_border_width(10);
	set_size_request(450, 400);

	// Create a vpaned widget and add it to our toplevel window
	Gtk::VPaned *vpaned = new Gtk::VPaned;
	add(*vpaned);
	vpaned->show();

	// Now create the contents of the two halves of the window
	MessageList *list = new MessageList;
	vpaned->add1(*list);
	list->show();

	// Create a scrolled text area that displays a "message"
	TextWindow *text = new TextWindow;
	vpaned->add2(*text);
	show();
}

PanedWindow::~PanedWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	PanedWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

