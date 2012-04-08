#include <xfc/main.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class ButtonWindow : public Gtk::Window
{
protected:
	virtual void on_clicked();

public:
	ButtonWindow();
	virtual ~ButtonWindow();
};

