#include "calendar.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/buttonbox.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/separator.hh>
#include <xfc/pango/font.hh>
#include <cstring>

const int CalendarWindow::DEF_PAD;
const int CalendarWindow::DEF_PAD_SMALL;
const int CalendarWindow::TM_YEAR_BASE;

CalendarWindow::CalendarWindow()
{
	using namespace sigc;
	
	for (int i = 0; i < 5; i++)
		settings.push_back(false);

	set_title("Calendar Example");
	set_border_width(5);
	set_resizable(false);

	Gtk::VBox *vbox = new Gtk::VBox(false, DEF_PAD);
	add(*vbox);

	// The top part of the window, Calendar, flags and fontsel.
	Gtk::HBox *hbox = new Gtk::HBox(false, DEF_PAD);
	vbox->pack_start(*hbox, true, true, DEF_PAD);
	Gtk::HButtonBox *hbbox = new Gtk::HButtonBox;
	hbox->pack_start(*hbbox, false, false, DEF_PAD);
	hbbox->set_layout(Gtk::BUTTONBOX_SPREAD);
	hbbox->set_spacing(5);

	// Calendar widget
	Gtk::Frame *frame = new Gtk::Frame("Calendar");
	hbbox->pack_start(*frame, false, true, DEF_PAD);
	calendar = new Gtk::Calendar;
	set_flags();
	calendar->mark_day(19);
	frame->add(*calendar);
	calendar->signal_month_changed().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "month_changed: "));
	calendar->signal_day_selected().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "day_selected: "));
	calendar->signal_day_selected_double_click().connect(mem_fun(this, &CalendarWindow::on_day_selected_double_click));
	calendar->signal_prev_month().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "prev_month: "));
	calendar->signal_next_month().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "next_month: "));
	calendar->signal_prev_year().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "prev_year: "));
	calendar->signal_next_year().connect(bind(mem_fun(this, &CalendarWindow::set_signal_strings), "next_year: "));

	Gtk::VSeparator *separator = new Gtk::VSeparator;
	hbox->pack_start(*separator, false, true);
	Gtk::VBox *vbox2 = new Gtk::VBox(false, DEF_PAD);
	hbox->pack_start(*vbox2, DEF_PAD);

	// Build the Right frame with the flags in
	frame = new Gtk::Frame("Flags");
	vbox2->pack_start(*frame, true, true, DEF_PAD);
	Gtk::VBox *vbox3 = new Gtk::VBox(true, DEF_PAD_SMALL);
	frame->add(*vbox3);

	struct { char *label; } flags[] = {
		{ "Show Heading" },
		{ "Show Day Names" },
		{ "No Month Change" },
		{ "Show Week Numbers" },
		{ "Week Start Monday" }
	};

	for (int i = 0; i < 5; i++)
	{
		Gtk::CheckButton *toggle = new Gtk::CheckButton(flags[i].label);
		toggle->signal_toggled().connect(bind(mem_fun(this, &CalendarWindow::on_toggle_flag), toggle));
		vbox3->pack_start(*toggle);
		checkboxes.push_back(toggle);
	}

	// Build the right font-button
	Gtk::Button *button = new Gtk::Button("Font...");
	button->signal_clicked().connect(mem_fun(this, &CalendarWindow::on_select_font));
	vbox2->pack_start(*button, false, false);

	// Build the Signal-event part.
	frame = new Gtk::Frame("Signal events");
	vbox->pack_start(*frame, true, true, DEF_PAD);

	vbox2 = new Gtk::VBox(true, DEF_PAD_SMALL);
	frame->add(*vbox2);

	hbox = new Gtk::HBox(false, 3);
	vbox2->pack_start(*hbox, false);
	Gtk::Label *label = new Gtk::Label("Signal:");
	hbox->pack_start(*label, false);
	last_signal = new Gtk::Label("");
	hbox->pack_start(*last_signal, false);

	hbox = new Gtk::HBox(false, 3);
	vbox2->pack_start(*hbox, false);
	label = new Gtk::Label("Previous signal:");
	hbox->pack_start(*label, false);
	previous_signal = new Gtk::Label("");
	hbox->pack_start(*previous_signal, false);

	hbox = new Gtk::HBox(false, 3);
	vbox2->pack_start(*hbox, false);
	label = new Gtk::Label("Second previous signal:");
	hbox->pack_start(*label, false);
	previous2_signal = new Gtk::Label("");
	hbox->pack_start(*previous2_signal, false);

	hbbox = new Gtk::HButtonBox;
	vbox->pack_start(*hbbox, false, false);
	hbbox->set_layout(Gtk::BUTTONBOX_END);

	button = new Gtk::Button("Close");
	button->signal_clicked().connect(mem_fun(this, &CalendarWindow::dispose));
	hbbox->add(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	show_all();
}

CalendarWindow::~CalendarWindow()
{
}

void
CalendarWindow::set_flags()
{
	int options = 0;
	for (int i = 0; i < 5; i++)
	{
		if (settings[i])
			options = options + (1 << i);
	}
	if (calendar)
    		calendar->set_display_options(options);
}

void
CalendarWindow::on_toggle_flag(Gtk::CheckButton *toggle)
{
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (checkboxes[i] == toggle)
		j = i;
	}
	settings[j] = !settings[j];
	set_flags();
}

void
CalendarWindow::on_select_font()
{
	static Gtk::FontSelectionDialog *font_dialog = 0;

	if (!font_dialog)
	{
		font_dialog = new Gtk::FontSelectionDialog("Font Selection Dialog");
		font_dialog->set_position(Gtk::WIN_POS_MOUSE);
		signal_destroy().connect(sigc::mem_fun(font_dialog, &Gtk::FontSelectionDialog::dispose));
		font_dialog->ok_button()->signal_clicked().connect(bind(sigc::mem_fun(this, &CalendarWindow::on_font_selection_ok), font_dialog));
		font_dialog->cancel_button()->signal_clicked().connect(sigc::mem_fun(*font_dialog, &Gtk::FontSelectionDialog::hide));
	}

	if (!font_dialog->is_visible())
		font_dialog->show();
	else
		font_dialog->hide();
}

void
CalendarWindow::on_font_selection_ok(Gtk::FontSelectionDialog *font_dialog)
{
	String font_name = font_dialog->get_font_name();
	if (calendar)
	{
		Pango::FontDescription font_desc(font_name);
 		calendar->modify_font(&font_desc);
	}
	font_dialog->hide();
}

void
CalendarWindow::on_day_selected_double_click()
{
	set_signal_strings("day_selected_double_click: ");

	struct tm tm;
	memset (&tm, 0, sizeof (tm));

	calendar->get_date(&tm.tm_year, &tm.tm_mon, &tm.tm_mday);
	tm.tm_year -= TM_YEAR_BASE;

	if (calendar->marked_date()[tm.tm_mday - 1] == 0)
		calendar->mark_day(tm.tm_mday);
	else
		calendar->unmark_day(tm.tm_mday);
}

String
CalendarWindow::date_to_string()
{
	struct tm tm;
	memset(&tm, 0, sizeof (tm));

	calendar->get_date(&tm.tm_year, &tm.tm_mon, &tm.tm_mday);
	tm.tm_year -= TM_YEAR_BASE;
	time_t time = mktime(&tm);

	char buffer[256];
	strftime(buffer, 255, "%x", gmtime(&time));
	return buffer;
}

void
CalendarWindow::set_signal_strings(const char *str)
{
	String text = previous_signal->get_text();
	previous2_signal->set_text(text);
	text = last_signal->get_text();
	previous_signal->set_text(text);
	text = str;
	text.append(date_to_string());
	last_signal->set_text(text);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	CalendarWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

