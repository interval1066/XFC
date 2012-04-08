#include <xfc/main.hh>
#include <xfc/gtk/progressbar.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class ProgressBarWindow : public Gtk::Window
{
	Gtk::ProgressBar *progress_bar;
	bool activity_mode;

	sigc::connection timeout_connection;

protected:
	bool on_timeout();
	void on_toggle_show_text();
	void on_toggle_activity_mode();
	void on_toggle_orientation();

public:
	ProgressBarWindow();
	~ProgressBarWindow();
};

