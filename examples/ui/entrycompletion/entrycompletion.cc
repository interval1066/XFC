#include "entrycompletion.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrendererpixbuf.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/entrycompletion.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <xfc/glib/main.hh>
#include <iostream>

// Note: using inline RGB data is always a better idea than using inline XPMs.

static const char  *book_closed_xpm[] = {
"16 16 6 1",
"       c None s None",
".      c black",
"X      c red",
"o      c yellow",
"O      c #808080",
"#      c white",
"                ",
"       ..       ",
"     ..XX.      ",
"   ..XXXXX.     ",
" ..XXXXXXXX.    ",
".ooXXXXXXXXX.   ",
"..ooXXXXXXXXX.  ",
".X.ooXXXXXXXXX. ",
".XX.ooXXXXXX..  ",
" .XX.ooXXX..#O  ",
"  .XX.oo..##OO. ",
"   .XX..##OO..  ",
"    .X.#OO..    ",
"     ..O..      ",
"      ..        ",
"                "
};

SimpleCompletionModel::SimpleCompletionModel()
: Gtk::ListStore(1, G_TYPE_STRING)
{
	Gtk::TreeIter iter = append();
	set_value(iter, 0, "total");
	iter = append();
	set_value(iter, 0, "totally");
	iter = append();
	set_value(iter, 0, "toto");
	iter = append();
	set_value(iter, 0, "tottery");
	iter = append();
	set_value(iter, 0, "totterer");
	iter = append();
	set_value(iter, 0, "Totten trust");
	iter = append();
	set_value(iter, 0, "totipotent");
	iter = append();
	set_value(iter, 0, "totipotency");
	iter = append();
	set_value(iter, 0, "totemism");
	iter = append();
	set_value(iter, 0, "totem pole");
	iter = append();
	set_value(iter, 0, "Totara");
	iter = append();
	set_value(iter, 0, "totalizer");
	iter = append();
	set_value(iter, 0, "totalizator");
	iter = append();
	set_value(iter, 0, "totalitarianism");
	iter = append();
	set_value(iter, 0, "total parenteral nutrition");
	iter = append();
	set_value(iter, 0, "total eclipse");
	iter = append();
	set_value(iter, 0, "Totipresence");
	iter = append();
	set_value(iter, 0, "Totipalmi");
}

CompletionModel::CompletionModel()
: Gtk::ListStore(2, GDK_TYPE_PIXBUF, G_TYPE_STRING)
{
	Pointer<Gdk::Pixbuf> pixbuf = new Gdk::Pixbuf(book_closed_xpm);
	Gtk::TreeIter iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "amber");

	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "ambient");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "ambidextrous");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "ambiguity");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "amble");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "ameba");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "ameliorate");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "amelioration");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "American Pie");
	
	iter = append();
	set_value(iter, 0, pixbuf);
	set_value(iter, 1, "Amelia Earhart");
}

Window::Window()
{
	set_title("Completion Example");
	set_border_width(5);
	
        Gtk::VBox *vbox = new Gtk::VBox(false, 2);
	vbox->set_border_width(5);
	add(*vbox);
	
	Gtk::Label *label = new Gtk::Label;
	label->set_markup("Try entering <b>total</b> for example:");
	vbox->pack_start(*label, false, false);
	
	// Create the first entry
	Gtk::Entry *entry = new Gtk::Entry;
	vbox->pack_start(*entry, false, false);
	
	// Create a tree model and use it as the completion model
	Pointer<Gtk::ListStore> completion_model = new SimpleCompletionModel;
	
	// Create the completion object and assign it to the entry
	Gtk::EntryCompletion *completion = entry->create_completion(*completion_model);
	
	// Use model column 0 as the text column
	completion->set_text_column(0);
	
	// The second completion example uses a custom match function
	label = new Gtk::Label;
	label->set_markup("Custom match function, try entering <b>amber</b> for example:");
	vbox->pack_start(*label, false, false, 5);

	// Create the second entry
	entry = new Gtk::Entry;
	vbox->pack_start(*entry, false, false);
	
	// Create a tree model and use it as the completion model
	completion_model = new CompletionModel;
	
	// Create the completion object and assign it to the entry
	completion = entry->create_completion(*completion_model);
	completion->set_minimum_key_length(2);
	
	Gtk::CellRenderer *cell = new Gtk::CellRendererPixbuf;
	completion->pack_start(*cell, false);
	completion->add_attribute(*cell, "pixbuf", 0); 
	
	// Use model column 1 as the text column
	cell = new Gtk::CellRendererText;
	completion->pack_start(*cell, false);
	completion->add_attribute(*cell, "text", 1); 
	
	completion->set_match_func(sigc::bind(sigc::mem_fun(this, &Window::on_match), completion->get_model()));
	completion->signal_match_selected().connect(sigc::bind(sigc::mem_fun(this, &Window::on_match_selected), completion->get_entry()));
	completion->insert_action_text(100, "action!");
	completion->insert_action_text(101, "another action!");
	completion->signal_action_activated().connect(sigc::mem_fun(this, &Window::on_activated));

	// The third completion example uses a dynamic completion model
	label = new Gtk::Label;
	label->set_markup("Dynamic completion, try entering <b>total</b> for example:");
	vbox->pack_start(*label, false, false, 5);

	// Create the third entry
	entry = new Gtk::Entry;
	vbox->pack_start(*entry, false, false);
	
	// Create the completion object
	completion = new Gtk::EntryCompletion;
	
	/* Assign the completion to the entry */
	entry->set_completion(completion);
	
	// Create a tree model and use it as the completion model
	completion_model = new Gtk::ListStore(1, G_TYPE_STRING);
	completion->set_model(*completion_model);
	
	// Use model column 0 as the text column
	completion->set_text_column(0);
	
	// Fill the completion dynamically
	G::timeout_signal.connect(sigc::bind(sigc::mem_fun(this, &Window::on_animation_timer), completion_model.get()), 1000);
	vbox->show_all();
}

Window::~Window()
{
}

bool 
Window::on_match(const String& key, const Gtk::TreeIter& iter, Gtk::TreeModel *model)
{
	bool result = false;	
	String item;	
	if (model->get_value(iter, 1, item))
	{
		std::cout << "comparing: " << key << " " << item << std::endl;
		if (item.compare(0, key.size(), key) == 0)
			result = true;
	}
	return result;
}

void
Window::on_activated(int index)
{
	std::cout << "action activated: " << index << std::endl;
}

bool
Window::on_match_selected(const Gtk::TreeModel& model, const Gtk::TreeIter& iter, Gtk::Entry *entry)
{
	String item = model.get_value(iter, 1);
	entry->set_text(item);
	entry->set_position(-1);
	return true;
}

static const char *dynamic_completions[] = {
  "total",
  "totally",
  "toto",
  "tottery",
  "totterer",
  "Totten trust",
  "totipotent",
  "totipotency",
  "totemism",
  "totem pole",
  "Totara",
  "totalizer",
  "totalizator",
  "totalitarianism",
  "total parenteral nutrition",
  "total eclipse",
  "Totipresence",
  "Totipalmi",
};

int
Window::on_animation_timer(Gtk::ListStore *model)
{
	static int timer_count = 0;
	int n_completions = G_N_ELEMENTS(dynamic_completions);
	Gtk::TreeIter iter;
		
	if ((timer_count / n_completions) % 2 == 0)
	{
		int n = timer_count % n_completions;
		Gtk::TreeIter iter = model->append();
		model->set_value(iter, 0, dynamic_completions[n]);
	}
	else
	{
		Gtk::TreeIter iter;
		if (model->get_iter_first(iter))
			model->remove(iter);
	}
	
	timer_count++;
	return true;
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

