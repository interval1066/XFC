/* Clipboard
 *
 * Gtk::Clipboard is used for clipboard handling. This demo shows
 * how to copy and paste text to and from the clipboard.
 */

#include "demowindow.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/clipboard.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class ClipboardWindow : public Gtk::Window
{
protected:
	void on_copy_button_clicked(Gtk::Entry *entry);
	void on_paste_button_clicked(Gtk::Entry *entry);
	void on_paste_received(const String& text, Gtk::Entry *entry); 

public:
	ClipboardWindow();
	virtual ~ClipboardWindow();
};
//!

ClipboardWindow::ClipboardWindow()
{
	set_title("Clipboard demo");
	
	Gtk::VBox *vbox = new Gtk::VBox;
	vbox->set_border_width(8);
	add(*vbox);
      
	Gtk::Label *label = new Gtk::Label("\"Copy\" will copy the text\nin the entry to the clipboard");
	vbox->pack_start(*label, false, false);
	
	Gtk::HBox *hbox = new Gtk::HBox(false, 4);
	hbox->set_border_width(8);
	vbox->pack_start(*hbox, false, false);
	
	// Create the first entry
	Gtk::Entry *entry = new Gtk::Entry;
	hbox->pack_start(*entry);
	
	// Create the copy button
	Gtk::Button *button = new Gtk::Button(Gtk::StockId::COPY);
	hbox->pack_start(*button, false, false);
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &ClipboardWindow::on_copy_button_clicked), entry));
	
	label = new Gtk::Label("\"Paste\" will paste the text from the clipboard to the entry");
	vbox->pack_start(*label, false, false);
	
	hbox = new Gtk::HBox(false, 4);
	hbox->set_border_width(8);
	vbox->pack_start(*hbox, false, false);
	
	// Create the second entry
	entry = new Gtk::Entry;
	hbox->pack_start(*entry);
	
	// Create the paste button
	button = new Gtk::Button(Gtk::StockId::PASTE);
	hbox->pack_start(*button, false, false);
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &ClipboardWindow::on_paste_button_clicked), entry));
	
	show_all();
}

ClipboardWindow::~ClipboardWindow()
{
}

void
ClipboardWindow::on_copy_button_clicked(Gtk::Entry *entry)
{
	// Get the clipboard object
	Gtk::Clipboard *clipboard = entry->get_clipboard(GDK_SELECTION_CLIPBOARD);
	
	// Set clipboard text
	clipboard->set_text(entry->get_text());
}

void
ClipboardWindow::on_paste_button_clicked(Gtk::Entry *entry)
{
	// Get the clipboard object
	Gtk::Clipboard *clipboard = entry->get_clipboard(GDK_SELECTION_CLIPBOARD);
	
	// Request the contents of the clipboard, contents_received will be called when we do get the contents.
	clipboard->request_text(sigc::bind(sigc::mem_fun(this, &ClipboardWindow::on_paste_received), entry));
}

void
ClipboardWindow::on_paste_received(const String& text, Gtk::Entry *entry)
{
	// Set the entry text
	entry->set_text(text);
}

Gtk::Window*
do_clipboard(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ClipboardWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

