#include <xfc/gtk/statusbar.hh>
#include <xfc/gtk/progressbar.hh>

using namespace Xfc;

class Statusbar : public Gtk::Statusbar
{
	Gtk::ProgressBar *progress_bar_;

	bool activity_mode_;
	sigc::connection timeout_connection;
	
	bool on_timeout();

public:
	Statusbar(bool show_progress);
	virtual ~Statusbar();
	
	Gtk::ProgressBar* progress_bar() const;

	void push(const String& text);
	void pop();
	
	void begin_progress(unsigned int interval, bool activity_mode = false);
	void set_progress(double fraction);
	void end_progress();
	
	sigc::signal<void> update_progress_signal;
};

