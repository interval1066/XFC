#include <xfc/main.hh>
#include <xfc/gtk/statusbar.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class StatusbarWindow : public Gtk::Window
{
	Gtk::Statusbar *status_bar;

protected:
	void on_push_item(int context_id);
	void on_pop_item(int context_id);

public:
	StatusbarWindow();
	~StatusbarWindow();
};

