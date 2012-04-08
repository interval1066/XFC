/* This program shows a preferences window, which contains radio buttons, 
 * a color selection widget, and a font selection widget.  It does manual
 * signal connection using libsigc++ slots, it pops up a (modal) window
 * to confirm whether the user really wants to exit, and it demonstrates
 * how to use pango markup.
 *
 * XFC translation of Example-4 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include <xfc/main.hh>
#include <xfc/gtk/colorselection.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/fontselection.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/radiobutton.hh>
#include <xfc/gdk/color.hh>
#include <xfc/glade/xml.hh>

using namespace Xfc;

/*  ConfirmationDialog
 */

class ConfirmationDialog : public Gtk::Dialog
{
	Gtk::Label * warning_label;

protected:
	bool on_delete_event(const Gdk::EventAny& event);

public:
	ConfirmationDialog(CObjectType *object, const Glade::Xml& xml);
	virtual ~ConfirmationDialog();
	
	void update_label(const char *font_name, const char *color, const char *location);
};
	
/*  MainWindow
 */

class MainWindow : public Gtk::Window
{
	Gtk::FontSelection *font_sel;
	Gtk::ColorSelection *color_sel;	
	Gdk::Color color;
	ConfirmationDialog *are_you_sure;
	String location;

	void time_to_quit();

protected:
	bool on_delete_event(const Gdk::EventAny& event);
	void on_new_location_selected(Gtk::RadioButton *button);
	void on_new_color_selected();
		
public:
	MainWindow(CObjectType *object, const Glade::Xml& xml);
	virtual ~MainWindow();
};

