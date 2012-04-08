#include <xfc/main.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class TableWindow : public Gtk::Window
{
protected:
	void on_button_clicked(const char *text);

public:
	TableWindow();
	~TableWindow();
};

