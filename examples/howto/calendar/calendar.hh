#include <xfc/main.hh>
#include <xfc/gtk/calendar.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/fontselection.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class CalendarWindow : public Gtk::Window
{
	static const int DEF_PAD = 10;
	static const int DEF_PAD_SMALL = 5;
	static const int TM_YEAR_BASE = 1900;

	Pointer<Gtk::Calendar> calendar;
	Pointer<Gtk::Label> last_signal;
	Pointer<Gtk::Label> previous_signal;
	Pointer<Gtk::Label> previous2_signal;

	std::vector<Gtk::CheckButton*> checkboxes;
	std::vector<bool> settings;

	void set_flags();
	void set_signal_strings(const char *str);
	String date_to_string();

protected:
	void on_toggle_flag(Gtk::CheckButton *toggle);
	void on_select_font();
	void on_font_selection_ok(Gtk::FontSelectionDialog *font_dialog);
	void on_day_selected_double_click();

public:
	CalendarWindow();
	virtual ~CalendarWindow();
};

