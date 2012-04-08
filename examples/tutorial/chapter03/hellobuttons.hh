#include <xfc/main.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class HelloButtons : public Gtk::Window
{
protected:
	void on_clicked(const char *text);

public:
	HelloButtons();
	virtual ~HelloButtons();
};

