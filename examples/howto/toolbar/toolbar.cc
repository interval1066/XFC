/*  Gtk::Toolbar Tutorial
 *
 *  This tutorial example shows you how to build a toolbar without using
 *  the Gtk::UIManager interface or stock items. It's an old example that 
 *  has been updated to use the new Gtk::Toolbar/Gtk::TooItem API. 
 */
 
#include "toolbar.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/handlebox.hh>
#include <xfc/gtk/tooltips.hh>

ToolbarDialog::ToolbarDialog()
{
	set_title("Toolbar Example");
	set_size_request(600, 300);
	set_resizable(true);

	// To make it nice we'll put the toolbar into the handle box so it can be detached from the main window.
	Gtk::HandleBox *handlebox = new Gtk::HandleBox;
	client_area()->pack_start(*handlebox, false, false, 5);

	// The toolbar will be horizontal, with both icons and text, and we'll also pack it into our handlebox.
	toolbar = new Gtk::Toolbar(Gtk::ORIENTATION_HORIZONTAL, Gtk::TOOLBAR_BOTH);
	handlebox->add(*toolbar);

	// We need an icon with a mask (one for each button) and an image widget to put the icon in,
	// so we'll create a separate image widget for each button).
	Gtk::Image *image = new Gtk::Image("gtk.xpm");

	// Create our first button, a "close" button. To destroy any widget/window in response
	// to a button click just create a slot by calling sigc::mem_fun() using the inherited
	// dispose method and connect it to the button.
	Gtk::ToolButton *tool_button = new Gtk::ToolButton(*image, "Close");
	tool_button->signal_clicked().connect(sigc::mem_fun(this, &ToolbarDialog::dispose)); 	
	toolbar->append(*tool_button, "Closes this app");
	tool_button->show();
			
	// Append a separator after the close button. append_separator() is a convenience method
	// that is equivalent to creating a new Gtk::SeparatorToolItem and adding to the toolbar
	// with a call to Gtk::Toolbar::append().
	toolbar->append_separator();

	// Now, let's make our radio button group. Note, rather than set up a separate method to change
	// the toolbar style we use "sigc::bind" to bind the toolbar style each radio button respresents directly
	// to Gtk::Toolbar::set_style() method.
	image = new Gtk::Image("gtk.xpm");
	Gtk::RadioToolButton *radio_button = 0;	
	radio_button = new Gtk::RadioToolButton(radio_button);
	radio_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(toolbar, &Gtk::Toolbar::set_style), Gtk::TOOLBAR_ICONS)); 	
	radio_button->set_contents(*image, "Icon");
	toolbar->append(*radio_button, "Only icons in toolbar");
	radio_button->show_all();
	
	// The following radio buttons refer to previous radio button as the group
	image = new Gtk::Image("gtk.xpm");
	radio_button = new Gtk::RadioToolButton(radio_button);
	radio_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(toolbar, &Gtk::Toolbar::set_style), Gtk::TOOLBAR_TEXT)); 	
	radio_button->set_contents(*image, "Text");
	toolbar->append(*radio_button, "Only texts in toolbar");
	radio_button->show_all();
	
	image = new Gtk::Image("gtk.xpm");
	radio_button = new Gtk::RadioToolButton(radio_button);
	radio_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(toolbar, &Gtk::Toolbar::set_style), Gtk::TOOLBAR_BOTH)); 	
	radio_button->set_contents(*image, "Both");
	radio_button->set_active(true);
	toolbar->append(*radio_button, "Icons and texts in toolbar");
	radio_button->show_all();
	
	// Append a separator	
	toolbar->append_separator();

	// Here we have just a simple toggle button. The on_toggle_button() method just checks 
	// the toggle button's active state and enabless/disables the tooltips accordingly.
	image = new Gtk::Image("gtk.xpm");
	toggle_button = new Gtk::ToggleToolButton;
	toggle_button->signal_clicked().connect(sigc::mem_fun(this, &ToolbarDialog::on_toggle_button)); 	
	toggle_button->set_contents(*image, "Tooltips");
	toggle_button->set_active(true);
	toolbar->append(*toggle_button, "Toolbar with or without tips");
	toggle_button->show();
		
	toolbar->append_separator();

	// Now we pack a widget into toolbar, we only have to create it and append it with an appropriate tooltip.
	Gtk::Entry *entry = new Gtk::Entry;
	Gtk::ToolItem *tool_item = new Gtk::ToolItem(*entry);
	toolbar->append(*tool_item, "Only icons in toolbar");
	tool_item->show();

	// The Entry isn't created within the toolbar, so we must still show it.
	entry->show();

	// That's it ! let's show everything.
	toolbar->show();
	handlebox->show();
}

ToolbarDialog::~ToolbarDialog()
{
}

void 
ToolbarDialog::on_toggle_button() 
{ 
	toolbar->set_tooltips(toggle_button->get_active()); 
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ToolbarDialog dialog;
	dialog.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	dialog.show();

	run();
	return 0;
}

