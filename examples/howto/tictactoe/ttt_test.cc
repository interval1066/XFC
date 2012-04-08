#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <iostream>
#include "tictactoe.hh"

using namespace Xfc;

class TictactoeTest : public Gtk::Window
{
	Tictactoe *ttt;

protected:
	void on_win();

public:
	TictactoeTest();
	virtual ~TictactoeTest();
};

TictactoeTest::TictactoeTest()
{
	set_title("Tictactoe");
	set_border_width(10);

	ttt = new Tictactoe;

	add(*ttt);
	ttt->tictactoe_signal.connect(sigc::mem_fun(this, &TictactoeTest::on_win));
	ttt->show();
}

TictactoeTest::~TictactoeTest()
{
}

void
TictactoeTest::on_win()
{
	using namespace std;

	cout << "Yay, you won!" << endl;
	ttt->clear();
}

XFC_MAIN(TictactoeTest)

