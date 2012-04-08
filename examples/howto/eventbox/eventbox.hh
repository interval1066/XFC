#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/cursor.hh>

using namespace Xfc;

class EventBoxWindow : public Gtk::Window
{
	Pointer<Gdk::Cursor> hand_cursor;

protected:
	bool on_button_press_event(const Gdk::EventButton&);

public:
	EventBoxWindow();
	virtual ~EventBoxWindow();
};

