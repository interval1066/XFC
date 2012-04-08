/* Paned Widgets
 *
 * The Gtk::HPaned and Gtk::VPaned Widgets divide their content
 * area into two panes with a divider in between that the
 * user can adjust. A separate child is placed into each
 * pane.
 *
 * There are a number of options that can be set for each pane.
 * This test contains both a horizontal (HPaned) and a vertical
 * (VPaned) widget, and allows you to adjust the options for
 * each side of each widget.
 */

#include "demowindow.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/paned.hh>
#include <xfc/gtk/table.hh>

using namespace Xfc;

class PanedOptions : public Gtk::Frame
{
	void on_toggle_resize(Gtk::Widget *child);
	void on_toggle_shrink(Gtk::Widget *child);

public:
	PanedOptions(Gtk::Paned *paned, const char *frame_label, const gchar *label1, const char *label2);
	~PanedOptions();
};

class PanedWindow : public Gtk::Window
{
public:
	PanedWindow();
	~PanedWindow();
};
//!

// PanedFrame

PanedOptions::PanedOptions(Gtk::Paned *paned, const char *frame_label, const gchar *label1, const char *label2)
: Gtk::Frame(frame_label)
{
	using namespace sigc;
	
	set_border_width(4);

	Gtk::Table *table = new Gtk::Table(3, 2, true);
	add(*table);

	Gtk::Label *label = new Gtk::Label(label1);
	table->attach(*label, 0, 1, 0, 1);

	Gtk::CheckButton *check_button = new Gtk::CheckButton("_Resize", true);
	table->attach(*check_button, 0, 1, 1, 2);
	check_button->signal_toggled().connect(bind(mem_fun(this, &PanedOptions::on_toggle_resize), paned->get_child1()));

	check_button = new Gtk::CheckButton("_Shrink", true);
	table->attach(*check_button, 0, 1, 2, 3);
	check_button->set_active(true);
	check_button->signal_toggled().connect(bind(mem_fun(this, &PanedOptions::on_toggle_shrink), paned->get_child1()));

	label = new Gtk::Label(label2);
	table->attach(*label, 1, 2, 0, 1);

	check_button = new Gtk::CheckButton("_Resize", true);
	table->attach(*check_button, 1, 2, 1, 2);
	check_button->set_active(true);
	check_button->signal_toggled().connect(bind(mem_fun(this, &PanedOptions::on_toggle_resize), paned->get_child2()));

	check_button = new Gtk::CheckButton("_Shrink", true);
	table->attach(*check_button, 1, 2, 2, 3);
	check_button->set_active(true);
	check_button->signal_toggled().connect(bind(mem_fun(this, &PanedOptions::on_toggle_shrink), paned->get_child2()));
}

PanedOptions::~PanedOptions()
{
}

void
PanedOptions::on_toggle_resize(Gtk::Widget *child)
{
	Gtk::Paned *paned = dynamic_cast<Gtk::Paned*>(child->get_parent());
	bool is_child1 = (child == paned->get_child1());

	bool resize = is_child1 ? paned->gtk_paned()->child1_resize : paned->gtk_paned()->child2_resize;
	bool shrink = is_child1 ? paned->gtk_paned()->child1_shrink : paned->gtk_paned()->child2_shrink;

	child->ref();
	paned->remove(*child);
	if (is_child1)
		paned->pack1(*child, !resize, shrink);
	else
		paned->pack2(*child, !resize, shrink);
	child->unref();
}

void
PanedOptions::on_toggle_shrink(Gtk::Widget *child)
{
	Gtk::Paned *paned = dynamic_cast<Gtk::Paned*>(child->get_parent());
	bool is_child1 = (child == paned->get_child1());

	bool resize = is_child1 ? paned->gtk_paned()->child1_resize : paned->gtk_paned()->child2_resize;
	bool shrink = is_child1 ? paned->gtk_paned()->child1_shrink : paned->gtk_paned()->child2_shrink;

	child->ref();
	paned->remove(*child);
	if (is_child1)
		paned->pack1(*child, resize, !shrink);
	else
		paned->pack2(*child, resize, !shrink);
	child->unref();
}

// PanedWindow

PanedWindow::PanedWindow()
{
	set_title("Panes");
	set_border_width(0);

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);

	Gtk::VPaned *vpaned = new Gtk::VPaned;
	vbox->pack_start(*vpaned);
	vpaned->set_border_width(5);

	Gtk::HPaned *hpaned = new Gtk::HPaned;
	vpaned->add1(*hpaned);

	Gtk::Frame *frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	frame->set_size_request(60, 60);
	hpaned->add1(*frame);
      
	Gtk::Button *button = new Gtk::Button("_Hi there", true);
	frame->add(*button);

	frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	frame->set_size_request(80, 60);
	hpaned->add2(*frame);

	frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	frame->set_size_request(60, 80);
	vpaned->add2(*frame);

	// Now create toggle buttons to control sizing
	PanedOptions *options = new PanedOptions(hpaned, "Horizontal", "Left", "Right");
	vbox->pack_start(*options, false, false);
	options = new PanedOptions(vpaned, "Vertical", "Top", "Bottom");
	vbox->pack_start(*options, false, false);
	show_all();
}

PanedWindow::~PanedWindow()
{
}

Gtk::Window*
do_panes(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new PanedWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}
