#include <xfc/main.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/fixed.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class FixedWindow : public Gtk::Window
{
	int x;
	int y;
	Gtk::Fixed *fixed;

protected:
	void on_move_button(Gtk::Button *button);

public:
	FixedWindow();
	virtual ~FixedWindow();
};

