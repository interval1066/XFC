#include <xfc/main.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/selection.hh>
#include <xfc/gtk/togglebutton.hh>
#include <xfc/gtk/togglebuttonsignals.hh>
#include <xfc/gtk/invisible.hh>
#include <xfc/gtk/widgetsignals.hh>
#include <xfc/gtk/dialog.hh>

using namespace Xfc;

// RetrieveSelectionButton

class RetrieveSelectionButton : public Gtk::Button, protected Gtk::WidgetSignals
{
protected:
	void on_get_target(Gtk::Entry *entry);
	virtual void on_selection_received(const Gtk::SelectionData& selection_data, unsigned int time);

public:
	RetrieveSelectionButton(Gtk::Entry *entry);
	virtual ~RetrieveSelectionButton();
};

// SupplySelectionButton

class SupplySelectionButton : public Gtk::ToggleButton, protected Gtk::ToggleButtonSignals
{
	static std::vector<Gtk::TargetEntry> target_entries;
	
	Gtk::Invisible *selection_widget;
	String target_string;

protected:
	virtual void on_toggled();
	void selection_get(Gtk::SelectionData& selection_data, unsigned int info, unsigned int time);
	bool selection_clear_event(const Gdk::EventSelection& event);

public:
	SupplySelectionButton();
	virtual ~SupplySelectionButton();
};

// SelectionTest

class SelectionTest : public Gtk::Dialog
{
public:
	SelectionTest();
	virtual ~SelectionTest();
};

