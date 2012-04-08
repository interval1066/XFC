#include <xfc/main.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class Window : public Gtk::Window
{
	static volatile int yes_or_no;
	Gtk::Label *label;

protected:
	void on_argument(int what);

public:
	Window();
	virtual ~Window();
};

