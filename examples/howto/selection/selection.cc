#include "selection.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/buttonbox.hh>
#include <xfc/gtk/label.hh>
#include <iostream>

std::vector<Gtk::TargetEntry> SupplySelectionButton::target_entries;

enum
{
	STRING,
	LENGTH
};

// RetrieveSelectionButton

RetrieveSelectionButton::RetrieveSelectionButton(Gtk::Entry *entry)
: Gtk::WidgetSignals(this)
{
	set_label("Retrieve Selection");
	signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &RetrieveSelectionButton::on_get_target), entry));
}

RetrieveSelectionButton::~RetrieveSelectionButton()
{
}

void
RetrieveSelectionButton::on_get_target(Gtk::Entry *entry)
{
	// Get the atom corresponding to the target string entered into the entry widget.
	Gdk::Atom target_atom = gdk_atom_intern(entry->get_text().c_str(), FALSE);
		
	// And request the target for the primary selection.
	selection_convert(GDK_SELECTION_PRIMARY, target_atom);
}

void
RetrieveSelectionButton::on_selection_received(const Gtk::SelectionData& selection_data, unsigned int time)
{
	using namespace std;

	// Print out the values of the selection_data members.
	cout << endl << "The values returned by the Gtk::SelectionData members are..." << endl;
	cout << " * selection() = " << selection_data.get_selection() << endl;
	cout << " * target() = " << selection_data.get_target() << endl;
	cout << " * type() = " << selection_data.get_type() << endl;
	cout << " * format() = " << selection_data.format() << endl;
	cout.setf(ios_base::hex, ios_base::basefield);
	cout << " * data() = 0x" << static_cast<int>(*selection_data.data()) << endl;
	cout.setf(ios_base::dec, ios_base::basefield);
	cout << " * length() = " << selection_data.length() << endl << endl;
	
	// IMPORTANT - Check to see if any data was returned.
	if (!selection_data.is_valid())
    {
		cout << "Couldn't get the target's data." << endl;
		return;
	}

	if (selection_data.get_target() == "TARGETS")
	{
		cout << "The targets supported by the \"" << selection_data.get_selection();
		cout << "\" selection are..." << endl;

		// Retrieve the target names as a vector of String
		std::vector<String> atom_names;
		if (!selection_data.get_targets(atom_names))
			return;

		// Print out the names
		int count = atom_names.size();
		for (int i = 0; i < count; i++)
		{
			cout << " * " << atom_names[i] << endl;
		}
	}
	else if (selection_data.get_target() == "STRING")
	{
		cout << "The 'STRING' data = " << selection_data.data() << endl;
	}
	else if (selection_data.get_target() == "LENGTH")
	{
		cout << "The 'LENGTH' data = " << static_cast<int>(*selection_data.data()) << endl;
	}
}

// SupplySelectionButton

SupplySelectionButton::SupplySelectionButton()
: Gtk::ToggleButtonSignals(this)
{
	set_label("Supply Selection");

	// Add STRING and LENGTH targets to the primary selection.
	target_entries.push_back(Gtk::TargetEntry("STRING", STRING));
	target_entries.push_back(Gtk::TargetEntry("LENGTH", LENGTH));

	// Create the widget that will be used as the selection owner;
	selection_widget = new Gtk::Invisible;
	selection_widget->realize();
	selection_widget->signal_selection_get().connect(sigc::mem_fun(this, &SupplySelectionButton::selection_get));
	selection_widget->signal_selection_clear_event().connect(sigc::mem_fun(this, &SupplySelectionButton::selection_clear_event));
	selection_widget->selection_add_targets(GDK_SELECTION_PRIMARY, target_entries);

	// Define the content the STRING target's data.
	target_string = "This is the data of the STRING target.";
}

SupplySelectionButton::~SupplySelectionButton()
{
}

void
SupplySelectionButton::on_toggled()
{
	using namespace std;

	if (get_active())
	{
		if (selection_widget->selection_owner_set(GDK_SELECTION_PRIMARY, GDK_CURRENT_TIME))
        	cout << "SUCCESSFULLY GOT OWNERSHIP." << endl;
  		else
		{
			// If unable to claim ownership of selection return button to out state.
        	cout << "FAILED TO GET OWNERSHIP." << endl;
			set_active(false);
		}
	}
	else
	{
	// Before clearing the selection by calling selection_owner_unset(),
        // we check if we are the actual owner.
		if (selection_widget->selection_owner_get(GDK_SELECTION_PRIMARY))
		{
			selection_owner_unset(GDK_SELECTION_PRIMARY, GDK_CURRENT_TIME);
			cout << "SUCCESSFULLY CLEARED OWNERSHIP." << endl;
		}
	}
}

void
SupplySelectionButton::selection_get(Gtk::SelectionData& selection_data, unsigned int info, unsigned int time)
{

	using namespace std;

	cout << "Got request for the '" << selection_data.get_target() << "' target." << endl;

	// Set the target data for our registered targets.
	switch (info)
	{
	case STRING:
		selection_data.set
		(
			gdk_atom_intern("STRING", TRUE), // type
			8,                               // format
			target_string.c_str(),           // data
			target_string.size()             // data length
		);
		break;

	case LENGTH:
		{
			int length = target_string.size();
			selection_data.set(gdk_atom_intern("INTEGER", TRUE), 32, &length, sizeof(length));
		}
		break;
	}

}

bool
SupplySelectionButton::selection_clear_event(const Gdk::EventSelection& event)
{
	if (get_active())
	{
		set_active(false);
		std::cout << "FORCEFULLY CLEARED OWNERSHIP." << std::endl;
	}
	return false;
}

// SelectionTest

SelectionTest::SelectionTest()
{
	set_title("Selection Test");
	set_border_width(5);
	set_has_separator(false);
	set_resizable(false);

	// Add label
	Gtk::VBox *vbox = new Gtk::VBox;
	Gtk::HBox *hbox = new Gtk::HBox;
	Gtk::Label *label = new Gtk::Label("Enter target name");
	label->set_justify(Gtk::JUSTIFY_LEFT);
	hbox->pack_start(*label, false, false);
	vbox->pack_start(*hbox);

	// Add entry widget
	Gtk::Entry *entry = new Gtk::Entry;
	entry->set_text("TARGETS");
	vbox->pack_start(*entry);
	client_area()->pack_start(*vbox, true, true, 5);
	client_area()->show_all();

	// Create a button the user can click to get selection targets
	RetrieveSelectionButton *retrieve_button = new RetrieveSelectionButton(entry);
	action_area()->pack_end(*retrieve_button, false, false);
	retrieve_button->show();

	// Add a button the user can toggle to claim ownership of the selection
	SupplySelectionButton *supply_button = new SupplySelectionButton;
	action_area()->pack_end(*supply_button, false, false);
	supply_button->show();

	// Add a button to end the program.
	Gtk::Button *button = new Gtk::Button("Quit");
	action_area()->pack_end(*button, false, false);
	button->signal_clicked().connect(sigc::mem_fun(this, &SelectionTest::dispose));
	button->show();
}

SelectionTest::~SelectionTest()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	SelectionTest window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

