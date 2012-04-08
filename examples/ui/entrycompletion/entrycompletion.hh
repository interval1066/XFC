#include <xfc/main.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class SimpleCompletionModel : public Gtk::ListStore
{
public:
	SimpleCompletionModel();
};

class CompletionModel : public Gtk::ListStore
{
public:
	CompletionModel();
};

class Window : public Gtk::Window
{
protected:
	bool on_match(const String& key, const Gtk::TreeIter& iter, Gtk::TreeModel *model);
	void on_activated(int index);
	bool on_match_selected(const Gtk::TreeModel& model, const Gtk::TreeIter& iter, Gtk::Entry *entry);
	int  on_animation_timer(Gtk::ListStore *model);

public:
	Window();
	virtual ~Window();
};

