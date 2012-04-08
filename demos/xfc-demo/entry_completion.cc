/* Entry Completion
 *
 * Gtk::EntryCompletion provides a mechanism for adding support for
 * completion in a Gtk::Entry widget.
 *
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/entrycompletion.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/stockid.hh>

using namespace Xfc;

class CompletionList : public Gtk::ListStore
{
public:
	CompletionList();
};

class EntryCompletionDialog : public Gtk::Dialog
{
public:
	EntryCompletionDialog();
	~EntryCompletionDialog();
};
//!

CompletionList::CompletionList()
: Gtk::ListStore(1, G_TYPE_STRING)
{
	// Append one word
	Gtk::TreeIter iter = append();
	set_value(iter, 0, "GNOME");
	
	// Append another word
	iter = append();
	set_value(iter, 0, "total");
	
	// And another word
	iter = append();
	set_value(iter, 0, "totally");
}

EntryCompletionDialog::EntryCompletionDialog()
{
	add_button(Gtk::StockId::CLOSE, Gtk::RESPONSE_NONE);
	set_resizable(false);
	signal_response().connect(sigc::hide(sigc::mem_fun(this, &EntryCompletionDialog::dispose)));
	
	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	client_area()->pack_start(*vbox);
	vbox->set_border_width(5);
	
	Gtk::Label *label = new Gtk::Label;
	label->set_markup("Completion demo, try writing <b>total</b> or <b>gnome</b> for example.");
	vbox->pack_start(*label, false, false);
	
	// Create the entry widget
	Gtk::Entry *entry = new Gtk::Entry;
	vbox->pack_start(* entry, false, false);
	
	// Create the completion object
	Pointer<Gtk::EntryCompletion> completion = new Gtk::EntryCompletion;
	
	// Assign the completion to the entry
	entry->set_completion(completion);
	
	// Create a tree model and use it as the completion model
	Pointer<CompletionList> completion_model = new CompletionList;
	completion->set_model(*completion_model);
	
	// Use model column 0 as the text column
	completion->set_text_column(0);
	show_all();
}

EntryCompletionDialog::~EntryCompletionDialog()
{
}

Gtk::Window*
do_entry_completion(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new EntryCompletionDialog;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

