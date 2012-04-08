#include <xfc/main.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class EntryWindow : public Gtk::Window
{
	Pointer<Gtk::Entry> entry;

protected:
	void on_enter();
	void on_entry_toggle_editable(Gtk::CheckButton *button);
	void on_entry_toggle_visible(Gtk::CheckButton *button);

public:
	EntryWindow();
	~EntryWindow();
};

