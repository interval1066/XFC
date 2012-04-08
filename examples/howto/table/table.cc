#include "table.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/table.hh>
#include <iostream>

TableWindow::TableWindow()
{
	// Set the window title
	set_title("Table");

	// Set the border width of the window.
	set_border_width( 20);

	// Create a 2x2 table
	Gtk::Table *table = new Gtk::Table(2, 2, true);

	// Put the table in the main window
	add(*table);

	// Create first button
	Gtk::Button *button = new Gtk::Button("button 1");
	
	// When the button is clicked, we call the "sigc::mem_fun" function with a pointer to "button 1" as its argument.
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &TableWindow::on_button_clicked), "button 1"));

	// Insert button 1 into the upper left quadrant of the table
	table->attach(*button, 0, 1, 0, 1);

	button->show();

	// Create second button
	button = new Gtk::Button("button 2");

	// When the button is clicked, we call the "sigc::mem_fun" function with a pointer to "button 2" as its argument.
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &TableWindow::on_button_clicked), "button 2"));

	// Insert button 2 into the upper right quadrant of the table
	table->attach(*button, 1, 2, 0, 1);

	button->show();

	// Create "Quit" button
	button = new Gtk::Button("Quit");

	// When the button is clicked, we call the main window's dispose() function and the program exits.
	button->signal_clicked().connect(sigc::mem_fun(this, &TableWindow::dispose));

	// Insert the quit button into the both lower quadrants of the table
	table->attach(*button, 0, 2, 1, 2);

	button->show();
	table->show();
}

TableWindow::~TableWindow()
{
}

void
TableWindow::on_button_clicked(const char *text)
{
    std::cout << "Hello again - " << text << " was pressed" << '\n';
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	TableWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

