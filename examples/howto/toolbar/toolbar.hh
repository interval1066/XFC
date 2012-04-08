#include <xfc/main.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/radiobutton.hh>
#include <xfc/gtk/toolbar.hh>

using namespace Xfc;

class ToolbarDialog : public Gtk::Dialog
{
	Gtk::Toolbar *toolbar;
	Gtk::ToggleToolButton *toggle_button;

protected:
	void on_toggle_button();

public:
	ToolbarDialog();
	virtual ~ToolbarDialog();
};

