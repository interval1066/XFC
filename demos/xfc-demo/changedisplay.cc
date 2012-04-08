/* Change Display
 *
 * Demonstrates migrating a window between different displays and
 * screens. A display is a mouse and keyboard with some number of
 * associated monitors. A screen is a set of monitors grouped
 * into a single physical work area. The neat thing about having
 * multiple displays is that they can be on a completely separate
 * computers, as long as there is a network connection to the
 * computer where the application is running.
 *
 * Only some of the windowing systems where GTK+ runs have the
 * concept of multiple displays and screens. (The X Window System
 * is the main example.) Other windowing systems can only
 * handle one keyboard and mouse, and combine all monitors into
 * a single screen.
 *
 * This is a moderately complex example, and demonstrates:
 *
 *  - Tracking the currently open displays and screens
 *
 *  - Changing the screen for a window
 *
 *  - Letting the user choose a window by clicking on it
 *
 *  - Using Gtk::ListStore and Gtk::TreeView
 *
 *  - Using Gtk::Dialog
 *
 * If you only have one display and one screen this example wont
 * do anything, except segfault when you try to close the display.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/sizegroup.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gdk/cursor.hh>
#include <xfc/gdk/display.hh>
#include <xfc/gdk/displaymanager.hh>
#include <xfc/gdk/screen.hh>

using namespace Xfc;

class Frame : public Gtk::Frame
{
	Gtk::TreeView *tree_view;
	Gtk::TreeSelection *selection_;
	Gtk::VBox *button_vbox;

public:
	Frame(const String& title, Gtk::SizeGroup& size_group);
	~Frame();

	Gtk::TreeSelection *get_selection() const;
	void set_model(Gtk::TreeModel *model);
	Gtk::TreeSelection* add_tree_view_column(Gtk::TreeViewColumn& column);
	void add_button(Gtk::Button& button);
};

class DisplayFrame : public Frame
{
	Gtk::ListStore *model_;
	Gdk::Display *current_display;

	sigc::connection opened_connection;
	std::vector<sigc::connection> closed_connections;

protected:
	void on_display_changed();
	void on_display_opened(GdkDisplay *display);
	void on_display_closed(bool is_error, Gdk::Display *display);

public:
	DisplayFrame(Gtk::SizeGroup& size_group);
	~DisplayFrame();

	void initialize_displays();
	void add_display(Gdk::Display *display);
	void close_display();

	sigc::signal<void, Gdk::Display*> fill_screens_signal; // Custom signal
};

class ScreenFrame : public Frame
{
	Gtk::ListStore *model;
	Gdk::Screen *current_screen;
	
protected:
	void on_screen_selection_changed();
	bool on_button_release_event(const Gdk::EventButton& event, bool *clicked);

public:
	ScreenFrame(Gtk::SizeGroup& size_group);
	~ScreenFrame();

	const Gdk::Screen* get_current_screen() const;
	void fill_screens(Gdk::Display *current_display);
	void query_change_screen();
	Gtk::Window* query_for_toplevel(Gdk::Screen *screen, const char *prompt);
		
	static Gtk::Window* find_toplevel_at_pointer(GdkDisplay *display);
};

class ChangeDisplayWindow : public Gtk::Dialog
{
	Pointer<Gtk::SizeGroup> size_group;
	DisplayFrame *display_frame;
	ScreenFrame *screen_frame;

protected:
	void on_response(int response_id);
	void on_open_display();
	void on_close_display();

public:
	ChangeDisplayWindow(Gtk::Window *owner);
	~ChangeDisplayWindow();
};
//!

// These enumerations provide symbolic names for the columns in the two
// Gtk::ListStore models.

enum
{
	DISPLAY_COLUMN_NAME,
	DISPLAY_COLUMN_DISPLAY,
	DISPLAY_NUM_COLUMNS
};

enum
{
	SCREEN_COLUMN_NUMBER,
	SCREEN_COLUMN_SCREEN,
	SCREEN_NUM_COLUMNS
};

// Frame is the base class for both the Display and Screen frames.

Frame::Frame(const String& title, Gtk::SizeGroup& size_group)
: Gtk::Frame(title)
{
	Gtk::HBox *hbox = new Gtk::HBox(false, 8);
	hbox->set_border_width(8);
	add(*hbox);

	Gtk::ScrolledWindow *scrollwin = new Gtk::ScrolledWindow;
	scrollwin->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	scrollwin->set_shadow_type(Gtk::SHADOW_IN);
	hbox->pack_start(*scrollwin);

	tree_view = new Gtk::TreeView;
	tree_view->set_headers_visible(false);
	scrollwin->add(*tree_view);

	selection_ = tree_view->get_selection();
	selection_->set_mode(Gtk::SELECTION_BROWSE);

	button_vbox = new Gtk::VBox(false, 5);
	hbox->pack_start(*button_vbox, false, false);

	size_group.add_widget(*button_vbox);
}

Frame::~Frame()
{
}

Gtk::TreeSelection*
Frame::get_selection() const 
{ 
	return selection_;
}

void 
Frame::set_model(Gtk::TreeModel *model)
{
	tree_view->set_model(model);
}

Gtk::TreeSelection* 
Frame::add_tree_view_column(Gtk::TreeViewColumn& column)
{
	tree_view->append_column(column);
	return tree_view->get_selection();
}

void 
Frame::add_button(Gtk::Button& button)
{
	button_vbox->pack_start(button, false, false);
}

// DisplayFrame

DisplayFrame::DisplayFrame(Gtk::SizeGroup& size_group)
: Frame("Display", size_group), current_display(0)
{
	model_ = new Gtk::ListStore(DISPLAY_NUM_COLUMNS, G_TYPE_STRING, GDK_TYPE_DISPLAY);
	set_model(model_);

	Gtk::CellRendererText *cell = new Gtk::CellRendererText;
	Gtk::CellColumnAttributes attribute("text", DISPLAY_COLUMN_NAME);
	Gtk::TreeViewColumn *column  = new Gtk::TreeViewColumn("Name", *cell, attribute);
	Gtk::TreeSelection *selection = add_tree_view_column(*column);
	selection->signal_changed().connect(sigc::mem_fun(this, &DisplayFrame::on_display_changed));
}

DisplayFrame::~DisplayFrame()
{
	// Remove the connections we use to track currently open displays.

	opened_connection.disconnect();

	int count = closed_connections.size();
	for (int i = 0; i < count; i++)
	{
		closed_connections[i].disconnect();
	}
}

void
DisplayFrame::initialize_displays()
{
	// Adds all currently open displays to our list of displays, and set up 
	// a signal connection so that we'll be notified when displays are 
	// opened in the future as well.

	Gdk::DisplayManager *manager = Gdk::DisplayManager::get();

	std::vector<Gdk::Display*> displays;
	manager->list_displays(displays);

	int count = displays.size();
	for (int i = 0; i < count; i++)
	{
		add_display(displays[i]);
	}

	opened_connection = manager->signal_display_opened().connect(sigc::mem_fun(this, &DisplayFrame::on_display_opened));
}

void
DisplayFrame::on_display_changed()
{
	// Called when the selected row in the display list changes.
	
	Gtk::TreeModel *model = 0;
	Gtk::TreeIter iter;

	// Update the current_display.
	if (get_selection()->get_selected(&iter, &model))
		model->get_object(iter, DISPLAY_COLUMN_DISPLAY, current_display);
	else
		current_display = 0;

	// Emit the fill_screens_signal to refill the list of screens.
	fill_screens_signal.emit(current_display);
}

void
DisplayFrame::on_display_opened(GdkDisplay *display)
{
	add_display(G::Object::wrap<Gdk::Display>(display));
}

void
DisplayFrame::on_display_closed(bool is_error, Gdk::Display *display)
{
	Gtk::TreeIter iter;

	for (bool valid = model_->get_iter_first(iter); valid; valid = model_->iter_next(iter))
	{
		Gdk::Display *tmp_display = 0;
		model_->get_object(iter, DISPLAY_COLUMN_DISPLAY, tmp_display);
		if (tmp_display == display)
		{
			model_->remove(iter);
			break;
		}
	}
}

void
DisplayFrame::add_display(Gdk::Display *display)
{
	using namespace sigc;
	
	// Add a new display to our list of displays,
	String name = display->get_name();
	Gtk::TreeIter iter = model_->append();
	model_->set_value(iter, DISPLAY_COLUMN_NAME, name);
	model_->set_object(iter, DISPLAY_COLUMN_DISPLAY, display);

	// Connect to the "closed" signal so that we can remove the display from the list of displays again.
	connection c = display->signal_closed().connect(bind(mem_fun(this, &DisplayFrame::on_display_closed), display));
	closed_connections.push_back(c);
}

void
DisplayFrame::close_display()
{
	if (current_display)
		current_display->close();
}

// ScreenFrame

ScreenFrame::ScreenFrame(Gtk::SizeGroup& size_group)
: Frame("Screen", size_group), current_screen(0)
{
	model = new Gtk::ListStore(SCREEN_NUM_COLUMNS, G_TYPE_INT, GDK_TYPE_SCREEN);
	set_model(model);

	Gtk::CellRendererText *cell = new Gtk::CellRendererText;
	Gtk::CellColumnAttributes attribute("text", SCREEN_COLUMN_NUMBER);
	Gtk::TreeViewColumn *column  = new Gtk::TreeViewColumn("Number", *cell, attribute);
	Gtk::TreeSelection *selection = add_tree_view_column(*column);
	selection->signal_changed().connect(sigc::mem_fun(this, &ScreenFrame::on_screen_selection_changed));
}

ScreenFrame::~ScreenFrame()
{
}

const Gdk::Screen*
ScreenFrame::get_current_screen() const
{ 
	return current_screen; 
}

void
ScreenFrame::on_screen_selection_changed()
{
	// Called to update the current_creen when the selected row in the sceen list changes.

	Gtk::TreeModel *model = 0;
	Gtk::TreeIter iter;

	if (get_selection()->get_selected(&iter, &model))
		model->get_object(iter, SCREEN_COLUMN_SCREEN, current_screen);
	else
		current_screen = 0;
}

void
ScreenFrame::fill_screens(Gdk::Display *current_display)
{
	// Fills in the screen list based on the current display.

	model->clear();

	if (current_display)
	{
		int n_screens = current_display->get_n_screens();

		for (int i = 0; i < n_screens; i++)
		{
			Gdk::Screen *screen = current_display->get_screen(i);
			Gtk::TreeIter iter = model->append();
			model->set_value(iter, SCREEN_COLUMN_NUMBER, i);
			model->set_object(iter, SCREEN_COLUMN_SCREEN, screen);

			if (i == 0)
				get_selection()->select_iter(iter);
		}
	}
}

void
ScreenFrame::query_change_screen()
{
	// Prompts the user for a toplevel window to move.
	Gdk::Screen *screen = Gtk::Widget::get_screen();
	Gtk::Window *toplevel = query_for_toplevel(screen, "Please select the toplevel\n"
	                                                   "to move to the new screen");

	// Move to toplevel window to the currently selected screen.
	if (toplevel)
		toplevel->set_screen(*current_screen);
	else
		screen->get_display()->beep();
}

Gtk::Window*
ScreenFrame::query_for_toplevel(Gdk::Screen *screen, const char *prompt)
{
	// After asking the user to click on a window, wait for them click the mouse.
	// When the mouse is released, return the toplevel window under the pointer,
	// or null, if there is none.
	
	Gtk::Window *popup = new Gtk::Window(Gtk::WINDOW_POPUP);
	popup->set_screen(*screen);
	popup->set_modal(true);
	popup->set_position(Gtk::WIN_POS_CENTER);

	Gtk::Frame *frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_OUT);
	popup->add(*frame);

	Gtk::Label *label = new Gtk::Label(prompt);
	label->set_padding(10, 10);
	frame->add(*label);

	popup->show_all();
	
	Gtk::Window *toplevel = 0;
	Gdk::Display *display = screen->get_display();
	Pointer<Gdk::Cursor> cursor = new Gdk::Cursor(GDK_CROSSHAIR, display);
	if (popup->pointer_grab(Gdk::BUTTON_RELEASE_MASK, 0, cursor) == Gdk::GRAB_SUCCESS)
	{
		bool clicked = false;
		popup->signal_button_release_event().connect(sigc::bind(sigc::mem_fun(this, &ScreenFrame::on_button_release_event), &clicked));

		// Process events until clicked is set by on_button_release_event. We pass in
		// may_block = true, since we want to wait if there are no events currently.
      
		while (!clicked)
		{
			g_main_context_iteration(0, TRUE);
		}

		toplevel = find_toplevel_at_pointer(*display);
		if (toplevel == popup)
			toplevel = 0;
	}

	popup->dispose();
	gdk_flush(); // Really release the grab
	return toplevel;
}

bool
ScreenFrame::on_button_release_event(const Gdk::EventButton& event, bool *clicked)
{
	*clicked = true;
	return true;
}

Gtk::Window*
ScreenFrame::find_toplevel_at_pointer(GdkDisplay *display)
{
	// Finds the toplevel window under the mouse pointer, if any.
	
	GtkWidget *widget = 0;
	GdkWindow *pointer_window = gdk_display_get_window_at_pointer(display, 0, 0);

	// The user data field of a GdkWindow is used to store a pointer to the widget that created it.
	if (pointer_window)
		gdk_window_get_user_data(pointer_window, (void**)&widget);


	Gtk::Window *toplevel = 0;
	if (widget)
	{
		GtkWindow *window = (GtkWindow*)gtk_widget_get_toplevel(widget);
		toplevel = G::Object::wrap<Gtk::Window>(window);
	}

	return toplevel;
}

// ChangeDisplayWindow

ChangeDisplayWindow::ChangeDisplayWindow(Gtk::Window *owner)
: Gtk::Dialog("Change Screen or Display", owner, Gtk::DIALOG_NO_SEPARATOR)
{
	// Add the dialog buttons.
	add_button(Gtk::STOCK_BUTTON_CLOSE);
	add_button("Change", Gtk::RESPONSE_OK);
	signal_response().connect(sigc::mem_fun(this, &ChangeDisplayWindow::on_response));	

	set_default_size(300, 400);

	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	vbox->set_border_width(8);
	client_area()->pack_start(*vbox);

	// Create size group.
	size_group = new Gtk::SizeGroup(Gtk::SIZE_GROUP_HORIZONTAL);
	
	// Create frame for the displays and add two left aligned buttons.
	display_frame = new DisplayFrame(*size_group);

	Gtk::Button *button = new Gtk::Button("_Open...", true);
	static_cast<Gtk::Label*>(button->get_child())->set_alignment(0.0, 0.5);
	button->signal_clicked().connect(sigc::mem_fun(this, &ChangeDisplayWindow::on_open_display));
	display_frame->add_button(*button);

	button = new Gtk::Button("_Close", true);
	static_cast<Gtk::Label*>(button->get_child())->set_alignment(0.0, 0.5);
	button->signal_clicked().connect(sigc::mem_fun(this, &ChangeDisplayWindow::on_close_display));
	display_frame->add_button(*button);

	vbox->pack_start(*display_frame);

	// Create frame for the screens
	screen_frame = new ScreenFrame(*size_group);
	vbox->pack_start(*screen_frame);

	// Connect to the fill_screens_signal, emitted by DisplayFrame when the current display changes.
	display_frame->fill_screens_signal.connect(sigc::mem_fun(screen_frame, &ScreenFrame::fill_screens));

	// Initialize the displays and show everything.
	display_frame->initialize_displays();
	show_all();
}

ChangeDisplayWindow::~ChangeDisplayWindow()
{
}

void
ChangeDisplayWindow::on_open_display()
{
	// Called when the user clicks on "Open..." in the display frame. Prompts
	// for a new display, and then opens a connection to that display.

	Gtk::Dialog dialog("Open Display", this, Gtk::DIALOG_MODAL);
	dialog.add_button(Gtk::STOCK_BUTTON_CANCEL);
	dialog.add_button(Gtk::STOCK_BUTTON_OK);
	dialog.set_default_response(Gtk::RESPONSE_OK);
	Gtk::Entry *display_entry = new Gtk::Entry;
	display_entry->set_activates_default(true);
	Gtk::Label *dialog_label = new Gtk::Label("Please enter the name of\nthe new display\n");
	dialog.client_area()->add(*dialog_label);
	dialog.client_area()->add(*display_entry);
	display_entry->grab_focus();
	dialog.get_child()->show_all();

	Gdk::Display *result = 0;
	while (!result)
	{
		int response_id = dialog.run();
		if (response_id != Gtk::RESPONSE_OK)
			break;
		
		String new_screen_name = display_entry->get_chars(0, -1);
		if (new_screen_name.compare("") != 0)
		{
			result = Gdk::Display::open(new_screen_name);
			if (!result)
			{
				String error = String::format("Can't open display :\n\t%s\nplease try another one\n", new_screen_name.c_str());
				dialog_label->set_text(error);
			}
		}
	}
	dialog.dispose();
}

void
ChangeDisplayWindow::on_close_display()
{
	// Called when the user clicks on the "Close" button in the "Display" frame.
	// Closes the selected display. Watch out, if you only have one display open
	// and you click the "Close" button you will get segfault. You can't close 
	// the last display.

	display_frame->close_display();
}

// on_response is called when the user clicks on a button in our dialog
// or closes the dialog through the window manager. Unless the "Change"
// button was clicked, we destroy the dialog.

void
ChangeDisplayWindow::on_response(int response_id)
{
	if (response_id == Gtk::RESPONSE_OK)
		screen_frame->query_change_screen();
	else
		dispose();
}

Gtk::Window*
do_changedisplay(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
		window = new ChangeDisplayWindow(static_cast<Gtk::Window*>(do_widget));
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

