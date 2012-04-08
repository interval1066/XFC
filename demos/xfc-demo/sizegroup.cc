/* Size Groups
 *
 * Gtk::SizeGroup provides a mechanism for grouping a number of
 * widgets together so they all request the same amount of space.
 * This is typically useful when you want a column of widgets to 
 * have the same size, but you can't use a Gtk::Table widget.
 *
 * Note that size groups only affect the amount of space requested,
 * not the size that the widgets finally receive. If you want the
 * widgets in a Gtk::SizeGroup to actually be the same size, you need
 * to pack them in such a way that they get the size they request
 * and not more. For example, if you are packing your widgets
 * into a table, you would not include the Gtk::FILL flag.
 */

#include "demowindow.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/menuitem.hh>
#include <xfc/gtk/sizegroup.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/table.hh>

using namespace Xfc;

class ComboBox : public Gtk::ComboBoxText
{
public:
	ComboBox(const char **strings);
	~ComboBox();
};

class ComboBoxTable : public Gtk::Table
{
public:
	ComboBoxTable(unsigned int rows, unsigned int columns);
	~ComboBoxTable();

	void add_row(int row, Gtk::SizeGroup *size_group, const char *label_text, const char **options);
};

class SizeGroupWindow : public Gtk::Dialog
{
	Gtk::SizeGroup *size_group; // must be unreferenced
	Gtk::CheckButton *check_button;

	void on_toggle_grouping(Gtk::SizeGroup *size_group);
	
public:
	SizeGroupWindow(Gtk::Window *owner);
	~SizeGroupWindow();
};
//!

// ComboBox

ComboBox::ComboBox(const char **strings)
{
	for (const char **str = strings; *str; str++)
	{
		append(*str);
	}
	set_active(0);
}

ComboBox::~ComboBox()
{
}

// ComboBoxTable

ComboBoxTable::ComboBoxTable(unsigned int rows, unsigned int columns)
: Gtk::Table(rows, columns)
{
}

ComboBoxTable::~ComboBoxTable()
{
}

void 
ComboBoxTable::add_row(int row, Gtk::SizeGroup *size_group, const char *label_text, const char **options)
{
	Gtk::Label *label = new Gtk::Label(label_text, true);
	label->set_alignment(0, 1);
	attach(*label, 0, 1, row, row + 1, Gtk::EXPAND | Gtk::FILL, 0);
  
	ComboBox *combo_box = new ComboBox(options);
	label->set_mnemonic_widget(combo_box);
	size_group->add_widget(*combo_box);
	attach(*combo_box, 1, 2, row, row + 1, 0, 0);
}

// SizeGroupWindow

SizeGroupWindow::SizeGroupWindow(Gtk::Window *owner)
: Gtk::Dialog("Size Groups", owner)
{
	add_button(Gtk::StockId::CLOSE, Gtk::RESPONSE_NONE);	
	signal_response().connect(sigc::hide(sigc::mem_fun(this, &SizeGroupWindow::dispose)));
	set_resizable(false);

	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	client_area()->pack_start(*vbox);
	vbox->set_border_width(5);

	size_group = new Gtk::SizeGroup;

	// Create one frame holding color options
	Gtk::Frame *frame = new Gtk::Frame("Color Options");
	vbox->pack_start(*frame);

	ComboBoxTable *table = new ComboBoxTable(2, 2);
	table->set_border_width(5);
	table->set_row_spacings(5);
	table->set_col_spacings(10);
	frame->add(*table);

	static const char *color_options[] = { "Red", "Green", "Blue", 0 };
	table->add_row(0, size_group, "_Foreground", color_options);
	table->add_row(1, size_group, "_Background", color_options);

	// And another frame holding line style options
	frame = new Gtk::Frame("Line Options");
	vbox->pack_start(*frame, false, false);

	table = new ComboBoxTable(2, 2);
	table->set_border_width(5);
	table->set_row_spacings(5);
	table->set_col_spacings(10);
 	frame->add(*table);
 	
 	static const char *dash_options[] = { "Solid", "Dashed", "Dotted", 0 };
	table->add_row(0, size_group, "_Dashing", dash_options);

   	static const char *end_options[] = { "Square", "Round", "Arrow", 0 };
	table->add_row(1, size_group, "_Line ends", end_options);

	// And a check button to turn grouping on and off
	check_button = new Gtk::CheckButton("_Enable grouping", true);
	vbox->pack_start(*check_button, false, false);
      
	check_button->set_active(true);
	check_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &SizeGroupWindow::on_toggle_grouping), size_group));
	show_all();
}

SizeGroupWindow::~SizeGroupWindow()
{
	size_group->unref();
}

void
SizeGroupWindow::on_toggle_grouping(Gtk::SizeGroup *size_group)
{
	Gtk::SizeGroupMode new_mode;

	// Gtk::SIZE_GROUP_NONE is not generally useful, but is useful here to show the effect
	// of Gtk_SIZE_GROUP_HORIZONTAL by contrast.
	if (check_button->get_active())
		new_mode = Gtk::SIZE_GROUP_HORIZONTAL;
	else
		new_mode = Gtk::SIZE_GROUP_NONE;
  
	size_group->set_mode(new_mode);
}

Gtk::Window*
do_sizegroup(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
		window = new SizeGroupWindow(static_cast<Gtk::Window*>(do_widget));
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}
