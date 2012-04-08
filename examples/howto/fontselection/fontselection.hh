#include <xfc/main.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class FontSelectionWindow : public Gtk::Window
{
	Gtk::Label *label;

protected:
	void on_select_font();

public:
	FontSelectionWindow();
	virtual ~FontSelectionWindow();
};

