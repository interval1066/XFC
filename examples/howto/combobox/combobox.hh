#include <xfc/main.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/widgetsignals.hh>

using namespace Xfc;

class Window : public Gtk::Window, protected Gtk::WidgetSignals
{
	Gtk::ComboBoxText *combobox;
	
protected:
	virtual bool on_delete_event(const Gdk::EventAny& event);

public:
	Window();
	virtual ~Window();
};

