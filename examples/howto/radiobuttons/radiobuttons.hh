#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/radiobutton.hh>

using namespace Xfc;

class RadioButtonWindow : public Gtk::Window
{
	void on_toggled(const Gtk::RadioButton *button);
	 
public:
	RadioButtonWindow();
	~RadioButtonWindow();
};

