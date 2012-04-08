/* Expander
 *
 * Gtk::Expander allows you to provide additional content that is initially hidden.
 * This is also known as "disclosure triangle".
 *
 */
 
#include <xfc/gtk/box.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/expander.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/stockid.hh>

using namespace Xfc;

class ExpanderDialog : public Gtk::Dialog
{
public:
	ExpanderDialog(Gtk::Window& parent);
	~ExpanderDialog();
};
//!

ExpanderDialog::ExpanderDialog(Window& parent)
: Gtk::Dialog("Gtk::Expander", &parent)
{
	add_button(Gtk::StockId::CLOSE, Gtk::RESPONSE_NONE);
	set_resizable(false);
	signal_response().connect(sigc::hide(sigc::mem_fun(this, &ExpanderDialog::dispose)));
	
	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	client_area()->pack_start(*vbox);
	vbox->set_border_width(5);
	
	Gtk::Label *label = new Gtk::Label("Expander demo. Click on the triangle for details.");
	vbox->pack_start(*label, false, false);
	
	// Create the expander
	Gtk::Expander *expander = new Gtk::Expander("Details");
	vbox->pack_start(*expander, false, false);
	label = new Gtk::Label("Details can be shown or hidden.");
	expander->add(*label);
	show_all();
}

ExpanderDialog::~ExpanderDialog()
{
}

Gtk::Window*
do_expander(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ExpanderDialog(static_cast<Gtk::Window&>(*do_widget));
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

