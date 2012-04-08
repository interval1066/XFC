#include "fixed.hh"

FixedWindow::FixedWindow() 
: x(30), y(50), fixed(0)
{
	set_title("Fixed Container");
	set_border_width(10);

	// Create a Fixed Container
	fixed = new Gtk::Fixed;
	add(*fixed);
	fixed->show();

	for (int i = 1 ; i <= 3 ; i++)
	{
		// Creates a new button with the label "Press me"
		Gtk::Button *button = new Gtk::Button("Press me");

		// When the button receives the "clicked" signal, it will call the move_button() slot
		// passing it the Fixed Container as its argument.
		button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &FixedWindow::on_move_button), button));

		// This packs the button into the fixed containers window.
		fixed->put(*button, i * 50, i * 50);

		// The final step is to display this newly created widget.
		button->show();
	}
}

FixedWindow::~FixedWindow()
{
}

void
FixedWindow::on_move_button(Gtk::Button *button)
{
	x = (x + 30) % 300;
	y = (y + 50) % 300;
	fixed->move(*button, x, y);
}

XFC_MAIN(FixedWindow)

