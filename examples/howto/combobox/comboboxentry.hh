#include <xfc/main.hh>
#include <xfc/gtk/comboboxentry.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/widgetsignals.hh>

using namespace Xfc;

/*  ComboBoxEntry
 */

class ComboBoxEntry : public Gtk::ComboBoxEntryText
{
public:
	ComboBoxEntry();
};

/*  Window
 */

class Window : public Gtk::Window, protected Gtk::WidgetSignals
{
	ComboBoxEntry *combobox;
	
protected:
	virtual bool on_delete_event(const Gdk::EventAny& event);

public:
	Window();
	virtual ~Window();
};

