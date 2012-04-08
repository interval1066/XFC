#include <xfc/main.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/spinbutton.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class SpinButtonWindow : public Gtk::Window
{
	Gtk::SpinButton *spinner1;
	Gtk::Label *val_label;

protected:
	void on_change_digits(Gtk::SpinButton *spin);
	void on_toggle_snap(Gtk::CheckButton *button);
	void on_toggle_numeric(Gtk::CheckButton *button);
	void on_get_value(bool value_as_int);

public:
	SpinButtonWindow();
	virtual ~SpinButtonWindow();
};

