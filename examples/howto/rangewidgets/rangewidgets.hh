#include <xfc/main.hh>
#include <xfc/gtk/adjustment.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/scale.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class RangeWidgets : public Gtk::Window
{
	Gtk::Adjustment *adj1;
	Gtk::HScale *hscale;
	Gtk::VScale *vscale;
	Gtk::CheckButton *check_button;

protected:
	void on_draw_value();
	void on_pos_menu_select(Gtk::ComboBox *combobox);
	void on_update_menu_select(Gtk::ComboBox *combobox);
	void on_digits_scale(Gtk::Adjustment *adj);
	void on_page_size(Gtk::Adjustment *adj);

public:
	RangeWidgets();
	~RangeWidgets();
};

