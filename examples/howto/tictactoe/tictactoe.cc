#include "tictactoe.hh"
#include <xfc/gtk/table.hh>
#include <xfc/gtk/togglebutton.hh>

using namespace Xfc;

/*  Tictactoe
 */

Tictactoe::Tictactoe()
{
	Gtk::Table *table = new Gtk::Table(3, 3, true);
	add(*table);
	table->show();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buttons[i][j] = new Gtk::ToggleButton;
			table->attach(*buttons[i][j], i, i + 1, j, j + 1);
			buttons[i][j]->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &Tictactoe::on_toggle), buttons[i][j]));
			buttons[i][j]->set_size_request(20, 20);
			buttons[i][j]->show();
		}
	}
}

Tictactoe::~Tictactoe()
{
}

void
Tictactoe::clear()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buttons[i][j]->set_active(false);
		}
	}
}

void
Tictactoe::on_toggle(Gtk::ToggleButton *button)
{
	static int rwins[8][3] = { { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 }, { 0, 1, 2 },
	                         { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 } };

	static int cwins[8][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 }, { 0, 0, 0 }, 
	                         { 1, 1, 1 }, { 2, 2, 2 }, { 0, 1, 2 }, { 2, 1, 0 } };

	bool success, found;
	
	for (int k = 0; k < 8; k++)
	{
		success = true;
		found = false;

		for (int i = 0; i < 3; i++)
		{
			success &= buttons[rwins[k][i]][cwins[k][i]]->get_active();
			found |= buttons[rwins[k][i]][cwins[k][i]] == button;
		}
      
		if (success && found)
		{
			tictactoe_signal.emit();
			break;
		}
	}
}

