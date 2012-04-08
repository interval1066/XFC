/* Dialog and Message Boxes
 *
 * Dialog widgets are used to pop up a transient window for user feedback.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/separator.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class DialogWindow : public Gtk::Window
{
	Gtk::Entry *entry1;
	Gtk::Entry *entry2;

	void on_message_dialog_clicked();
	void on_interactive_dialog_clicked();
	
public:
	DialogWindow();
	~DialogWindow();
};
//!

DialogWindow::DialogWindow()
{
	set_title("Dialogs");
	set_border_width(8);

	Gtk::Frame *frame = new Gtk::Frame("Dialogs");
	add(*frame);

	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(8);
	frame->add(*vbox);

	// Standard message dialog
	Gtk::HBox *hbox = new Gtk::HBox(false, 8);
	vbox->pack_start(*hbox, false, false);
	Gtk::Button *button = new Gtk::Button("_Message Dialog", true);
	button->signal_clicked().connect(sigc::mem_fun(this, &DialogWindow::on_message_dialog_clicked));
	hbox->pack_start(*button, false, false);
	vbox->pack_start(*(new Gtk::HSeparator), false, false);

	// Interactive dialog
	hbox = new Gtk::HBox(false, 8);
	vbox->pack_start(*hbox, false, false);
	Gtk::VBox *vbox2 = new Gtk::VBox;

	button = new Gtk::Button("_Interactive Dialog", true);
	button->signal_clicked().connect(sigc::mem_fun(this, &DialogWindow::on_interactive_dialog_clicked));
	hbox->pack_start(*vbox2, false, false);
	vbox2->pack_start(*button, false, false);

	Gtk::Table *table = new Gtk::Table(2, 2);
	table->set_spacings(4, 4);
	hbox->pack_start(*table, false, false);

	Gtk::Label *label = new Gtk::Label("_Entry 1", true);
	table->attach(*label, 0, 1, 0, 1);

	entry1 = new Gtk::Entry;
	table->attach(*entry1, 1, 2, 0, 1);
	label->set_mnemonic_widget(entry1);

	label = new Gtk::Label("E_ntry 2", true);
	table->attach(*label, 0, 1, 1, 2);

	entry2 = new Gtk::Entry;
	table->attach(*entry2, 1, 2, 1, 2);
	label->set_mnemonic_widget(entry2);
	show_all();
}

DialogWindow::~DialogWindow()
{
}

void
DialogWindow::on_message_dialog_clicked()
{
	using namespace Gtk;

	static int i = 1;
	MessageDialog dialog(MESSAGE_INFO, BUTTONS_OK, this, DIALOG_MODAL | DIALOG_DESTROY_WITH_PARENT);
	dialog.format_message("This message box has been popped up the following\nnumber of times:");
	dialog.format_secondary_text("%d", i);                      
	if (dialog.run())
		dialog.dispose();
	i++;
}

void
DialogWindow::on_interactive_dialog_clicked()
{
	using namespace Gtk;

	Dialog *dialog = new Dialog("Interactive Dialog", this, DIALOG_MODAL| DIALOG_DESTROY_WITH_PARENT);
	dialog->add_button(STOCK_BUTTON_OK);
	dialog->add_button("_Non-stock Button", RESPONSE_CANCEL);

	HBox *hbox = new HBox(false, 8);
	hbox->set_border_width(8);
	dialog->client_area()->pack_start(*hbox, false, false);

	Image *stock = new Image(StockId::DIALOG_QUESTION, ICON_SIZE_DIALOG);
	hbox->pack_start(*stock, false, false);

	Table *table = new Table(2, 2);
	table->set_spacings(4, 4);

	hbox->pack_start(*table);
	Label *label = new Label("_Entry 1", true);
	table->attach(*label, 0, 1, 0, 1);
	Entry *local_entry1 = new Entry;
	local_entry1->set_text(entry1->get_text());
	table->attach(*local_entry1, 1, 2, 0, 1);
	label->set_mnemonic_widget(local_entry1);

	label = new Label("E_ntry 2", true);
	table->attach(*label, 0, 1, 1, 2);

	Entry *local_entry2 = new Entry;
	local_entry2->set_text(entry2->get_text());
	table->attach(*local_entry2, 1, 2, 1, 2);
	label->set_mnemonic_widget(local_entry2);
  
	hbox->show_all();
	if (dialog->run() == RESPONSE_OK)
	{
		entry1->set_text(local_entry1->get_text());
		entry2->set_text(local_entry2->get_text());
	}
	dialog->dispose();
}

Gtk::Window*
do_dialog(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new DialogWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

