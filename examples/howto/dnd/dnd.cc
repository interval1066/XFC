#include "dnd.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gdk/bitmap.hh>
#include <xfc/gdk/color.hh>
#include <iostream>
#include <ctime>
#include <cstring>

std::vector<Gtk::TargetEntry> SourceButton::target_entries;

enum
{
	//  Define the info fields for the supported targets.
	TEXT_HTML,
	STRING
};

DestinationButton::DestinationButton(const String& label, const Gtk::TargetEntry& entry)
: Gtk::Button(label),
  Gtk::WidgetSignals(this)
{
	// Set up this button as a drag destination.
	drag_dest_set(Gtk::DEST_DEFAULT_ALL, entry, Gdk::ACTION_COPY);
	
	signal_drag_data_received().connect(sigc::mem_fun(this, &DestinationButton::on_drag_data_received));
}

DestinationButton::~DestinationButton()
{
}

void
DestinationButton::on_drag_data_received(Gtk::DragContext& context, int x, int y, const Gtk::SelectionData& data,
	                                     unsigned int info, unsigned int event_time)
{
	using namespace std;

	// Get current time
	time_t now = ::time(0);
	struct tm *now_tm = localtime(&now);
	char now_string[10];
	strftime(now_string, sizeof(now_string), "%T", now_tm);

	// Get button id from enum info
	int id = info + 1;
	
	// Set button label to reflect the dropped data
	String label = String::format(" Drag DESTINATION %i received % s data at %s ", id, data.get_target().c_str(), now_string);
	set_label(label);
	cout << "Destination " << id << ": Received data for the '" << data.get_target() << "' target." << endl;

	// Print the dropped data to the standard output
	switch(info)
	{
	case TEXT_HTML:
		cout << "text/html data = '" << data.data() << "'" <<endl;
		break;

	case STRING:
		cout << "STRING data = '" << data.data() << "'" << endl;
		break;
	}
}

SourceButton::SourceButton(const String& label)
: Gtk::Button(label),
  Gtk::WidgetSignals(this)
{
	// Add text/html and STRING targets to the primary selection.
	target_entries.push_back(Gtk::TargetEntry("text/html", TEXT_HTML, Gtk::TARGET_SAME_APP));
	target_entries.push_back(Gtk::TargetEntry("STRING", STRING));

	// Set up this button as a source for a drap operation
	drag_source_set(Gdk::BUTTON1_MASK, target_entries, Gdk::ACTION_COPY);

	// Create a custom icon to be used for the drags
	Pointer<Gdk::Bitmap> drag_mask;
	Gdk::Pixmap *drag_icon(new Gdk::Pixmap(Gdk::Colormap::get_system(), "gtk.xpm", &drag_mask));
	drag_source_set_icon(Gdk::Colormap::get_system(), drag_icon, drag_mask);
}

SourceButton::~SourceButton()
{
}

void
SourceButton::on_drag_begin(Gtk::DragContext& context)
{
	// Get the current time
	time_t now = time(0);
	char *now_string = ctime(&now);
	
	// Remove terminating new line character.
	now_string[strlen(now_string) - 1] = '\0';

	std::cout << "Source: Drag begun..." << std::endl;

	// Set data strings	for the supported targets
	target_html = String::format("<P>It's now <B>%s</B>.</P>", now_string);
	target_string = String::format("It's now %s.", now_string);
}

void
SourceButton::on_drag_data_get(Gtk::DragContext& context, Gtk::SelectionData& data,
                               unsigned int info, unsigned int time)
{
	std::cout << "Source: Got request for the '" << data.get_target() << "' target." << std::endl;

	// Fill the Gtk::SelectionData with the values to be passed to the requesting destination.
	switch(info)
	{
	case TEXT_HTML :
		data.set(gdk_atom_intern("text/html", TRUE), 8, target_html.c_str(), target_html.size());
		break;

	case STRING :
		data.set(gdk_atom_intern("STRING", TRUE), 8, target_string.c_str(), target_string.size());
		break;
	}
}

void
SourceButton::on_drag_end(Gtk::DragContext& context)
{
	std::cout << "Source: Drag ended!\n" << std::endl;
}

Window::Window()
{
	set_title("Drag and Drop Example");

	Gtk::VBox *vbox = new Gtk::VBox(true, 5);
	vbox->set_border_width(5);
	add(*vbox);

	// Create drag destination button 1
	Gtk::TargetEntry entry("text/html", TEXT_HTML);
	Gtk::Button *button = new DestinationButton(" Drag DESTINATION 1 received nothing ", entry);
	vbox->pack_start(*button);

	// Create drag destination button 2
	entry.set("STRING", STRING);
	button = new DestinationButton(" Drag DESTINATION 2 received nothing ", entry);
	vbox->pack_start(*button);
	
	// Create drag source button
	button = new SourceButton(" Drag SOURCE providing current time ");
	vbox->pack_start(*button);
	vbox->show_all();
}

Window::~Window()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

