#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/widgetsignals.hh>

using namespace Xfc;

class HelloWorld : public Gtk::Window, protected Gtk::WidgetSignals
{
protected:
	virtual bool on_delete_event(const Gdk::EventAny& event);
	void on_hello();

public:
	HelloWorld();
	~HelloWorld();
};

