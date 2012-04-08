#include "statusbar.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>

StatusbarWindow::StatusbarWindow()
{
	set_title("Statusbar Example");
	set_size_request(200, 100);

	Gtk::VBox *vbox = new Gtk::VBox(false, 1);
	add(*vbox);
	vbox->show();

	status_bar = new Gtk::Statusbar;
	vbox->pack_start(*status_bar);
	status_bar->show();

	int context_id = status_bar->get_context_id("Statusbar example");

	Gtk::Button *button = new Gtk::Button("push item");
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &StatusbarWindow::on_push_item), context_id));
	vbox->pack_start(*button, true, true, 2);
	button->show();

	button = new Gtk::Button("pop last item");
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &StatusbarWindow::on_pop_item), context_id));
	vbox->pack_start(*button, true, true, 2);
	button->show();

	// Always display the window as the last step so it all splashes on the screen at once.
	show();
}

StatusbarWindow::~StatusbarWindow()
{
}

void
StatusbarWindow::on_push_item(int context_id)
{
	static int count = 1;
	String text = String::format("Item %d", count++);
	status_bar->push(text, context_id);
}

void
StatusbarWindow::on_pop_item(int context_id)
{
	status_bar->pop(context_id);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	StatusbarWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

