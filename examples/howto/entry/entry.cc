#include "entry.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/stockid.hh>
#include <iostream>

EntryWindow::EntryWindow()
{
	set_title("XFC Entry");
	set_size_request(200, 100);

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);
	vbox->show();

	entry = new Gtk::Entry;
	entry->set_max_length(50);
	entry->signal_activate().connect(sigc::mem_fun(this, &EntryWindow::on_enter));

	entry->set_text("hello");
	int tmp_pos = entry->gtk_entry()->text_length;
	entry->insert_text(" world", tmp_pos);
	entry->select_region(0, entry->gtk_entry()->text_length);
	vbox->pack_start(*entry);
	entry->show();

	Gtk::HBox *hbox = new Gtk::HBox;
	vbox->add(*hbox);
	hbox->show();

	Gtk::CheckButton *check = new Gtk::CheckButton("Editable");
	hbox->pack_start(*check);
	check->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &EntryWindow::on_entry_toggle_editable), check));
	check->set_active(true);
	check->show();

	check = new Gtk::CheckButton("Visible");
	hbox->pack_start(*check);
	check->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &EntryWindow::on_entry_toggle_visible), check));
	check->set_active(true);
	check->show();

	Gtk::Button *button = new Gtk::Button(Gtk::StockId::CLOSE);
	button->signal_clicked().connect(sigc::mem_fun(this, &EntryWindow::dispose));
	vbox->pack_start(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	button->show();
}

EntryWindow::~EntryWindow()
{
}

void
EntryWindow::on_enter()
{
	using namespace std;

	String text = entry->get_text();
	cout << "Entry contents: " << text.c_str() << endl;
}

void
EntryWindow::on_entry_toggle_editable(Gtk::CheckButton *button)
{
	entry->set_editable(button->get_active());
}

void
EntryWindow::on_entry_toggle_visible(Gtk::CheckButton *button)
{
	entry->set_visibility(button->get_active());
}

int main(int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	EntryWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

