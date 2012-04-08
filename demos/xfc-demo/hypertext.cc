/* Text Widget/Hypertext
 *
 * Usually, tags modify the appearance of text in the view, e.g. making it 
 * bold or colored or underlined. But tags are not restricted to appearance. 
 * They can also affect the behavior of mouse and key presses, as this demo 
 * shows.
 */
 
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/textview.hh>
#include <xfc/gtk/textviewsignals.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/cursor.hh>
#include <xfc/gdk/keyval.hh>
#include <xfc/gdk/window.hh>
#include <gdk/gdkkeysyms.h>

using namespace Xfc;

class TextView : public Gtk::TextView, protected Gtk::WidgetSignals
{
	Pointer<Gdk::Cursor> hand_cursor;
	Pointer<Gdk::Cursor> regular_cursor;
	bool hovering_over_link;
	
	Gtk::TextBuffer *buffer;
	
	void insert_link(Gtk::TextIter& iter, const char *text, int page);
	void follow_if_link(Gtk::TextIter& iter);
	void set_cursor_if_appropriate(int x, int y);
	void show_page(int page);
			
protected:
	virtual bool on_key_press_event(const Gdk::EventKey& event);
	virtual bool on_motion_notify_event(const Gdk::EventMotion& event);
	virtual bool on_visibility_notify_event(const Gdk::EventVisibility& event);
	void on_event_after(const Gdk::Event& event);

public:
	TextView();
	~TextView();
};

class HypertextWindow : public Gtk::Window
{
public:
	HypertextWindow();
	~HypertextWindow();
};
//!

// TextView

TextView::TextView()
: Gtk::WidgetSignals(this),
  hovering_over_link(false)
{
	hand_cursor = new Gdk::Cursor(GDK_HAND2);
	regular_cursor = new Gdk::Cursor(GDK_XTERM);
	
	set_wrap_mode(Gtk::WRAP_WORD);
	signal_event_after().connect(sigc::mem_fun(this, &TextView::on_event_after));
	buffer = get_buffer();
	show_page(1);
}

TextView::~TextView()
{
}

bool 
TextView::on_key_press_event(const Gdk::EventKey& event)
{
	if (event.keyval().equal(GDK_Return) || event.keyval().equal(GDK_KP_Enter)) 	
	{
		Gtk::TextIter iter = buffer->get_iter_at_mark(*buffer->get_insert());
		follow_if_link(iter);
	}
	return false;
}

bool 
TextView::on_motion_notify_event(const Gdk::EventMotion& event)
{
	// Update the cursor image if the pointer moved. 
	
	int x, y;
	window_to_buffer_coords(Gtk::TEXT_WINDOW_WIDGET, event.x_int(), event.y_int(), &x, &y);
	set_cursor_if_appropriate(x, y);
	get_pointer(0, 0);
	return false;
}

bool 
TextView::on_visibility_notify_event(const Gdk::EventVisibility& event)
{
	// Update the cursor image if the window becomes visible
	// (e.g. when a window covering it got iconified).
	
	int wx, wy, bx, by;
 	get_pointer(&wx, &wy);
	window_to_buffer_coords(Gtk::TEXT_WINDOW_WIDGET, wx, wy, &bx, &by);
	set_cursor_if_appropriate(bx, by);
	return false;
}

void 
TextView::on_event_after(const Gdk::Event& event)
{
	// Links can also be activated by clicking.
	if (event.type() != Gdk::BUTTON_RELEASE)
		return;
		
	const Gdk::EventButton& tmp_event = static_cast<const Gdk::EventButton&>(event);
	
	if (tmp_event.button() != 1)
		return;
	
	// We shouldn't follow a link if the user has selected something.
	Gtk::TextIter start, end;
	buffer->get_selection_bounds(&start, &end);
	if (start.get_offset() != end.get_offset())
		return;
	
	int x, y;	
	window_to_buffer_coords(Gtk::TEXT_WINDOW_WIDGET, tmp_event.x_int(), tmp_event.y_int(), &x, &y);
	Gtk::TextIter iter = get_iter_at_location(x, y);
	follow_if_link(iter);
}

void
TextView::show_page(int page)
{
	// Fills the buffer with the text and interspersed links. In any real
	// hypertext app, this method would parse a file to identify the links.
	
	buffer->set_text("");
	Gtk::TextIter iter = buffer->get_iter_at_offset(0);
	
	if (page == 1)
	{
		buffer->insert(iter, "Some text to show that simple ");
		insert_link(iter, "hypertext", 3);
		buffer->insert(iter, " can easily be realized with ");
		insert_link(iter, "tags", 2);
		buffer->insert(iter, ".");
	}
	else if (page == 2)
	{
		buffer->insert(iter, 
			      "A tag is an attribute that can be applied to some range of text. "
			      "For example, a tag might be called \"bold\" and make the text inside "
			      "the tag bold. However, the tag concept is more general than that; "
			      "tags don't have to affect appearance. They can instead affect the "
			      "behavior of mouse and key presses, \"lock\" a range of text so the "
			      "user can't edit it, or countless other things.\n");
		insert_link(iter, "Go back", 1);
	}
	else if (page == 3) 
	{
		Gtk::TextTag *tag = buffer->create_tag();
		tag->property_weight().set(Pango::WEIGHT_BOLD);
		buffer->insert_with_tag(iter, "hypertext:\n", -1, *tag);
		buffer->insert(iter, 
			       "machine-readable text that is not sequential but is organized "
			       "so that related items of information are connected.\n");
		insert_link(iter, "Go back", 1);
	}
}

void 
TextView::insert_link(Gtk::TextIter& iter, const char *text, int page)
{
	// Inserts a piece of text into the buffer, giving it the usual appearance of a
	// hyperlink in a web browser: blue and underlined. Additionally, attaches some
	// data on the tag, to make it recognizable as a link. 
	
	Gtk::TextTag *tag = buffer->create_tag();
	tag->property_foreground().set(String("blue"));
	tag->property_underline().set(Pango::UNDERLINE_SINGLE); 
	tag->set_data("page", GINT_TO_POINTER (page));
	buffer->insert_with_tag(iter, text, -1, *tag);
}

void
TextView::follow_if_link(Gtk::TextIter& iter)
{
	// Looks at all tags covering the position of iter in the text view, 
	// and if one of them is a link, follow it by showing the page
	// identified by the data attached to it.
	
	std::vector<Gtk::TextTag*> tags;
	iter.get_tags(tags);	
	for (unsigned int i = 0; i < tags.size(); i++)
	{	
		int page = GPOINTER_TO_INT(tags[i]->get_data("page"));
		if (page != 0)
		{
			show_page(page);
			break;
		}
	}
}

void
TextView::set_cursor_if_appropriate(int x, int y)
{
	// Looks at all tags covering the position (x, y) in the text view, 
	// and if one of them is a link, change the cursor to the "hands" 
	// cursor typically used by web browsers.
	
	bool hovering = false;
	std::vector<Gtk::TextTag*> tags;
	Gtk::TextIter iter = get_iter_at_location(x, y);
	iter.get_tags(tags);	
	
	for (unsigned int i = 0; i < tags.size(); i++)
	{	
		int page = GPOINTER_TO_INT(tags[i]->get_data("page"));
		if (page != 0)
		{
			hovering = true;
			break;
		}
	}


	if (hovering != hovering_over_link)
	{
		hovering_over_link = hovering;
	
		if (hovering_over_link)
			get_window(Gtk::TEXT_WINDOW_TEXT)->set_cursor(*hand_cursor);
		else
			get_window(Gtk::TEXT_WINDOW_TEXT)->set_cursor(*regular_cursor);
	}
}

// HypertextWindow

HypertextWindow::HypertextWindow()
{
	set_title("Hypertext");
	set_default_size(450, 450);
	set_border_width(0);
	
	TextView *text_view = new TextView;
	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_policy_automatic();
	sw->add(*text_view);
	add(*sw);
	show_all();
}

HypertextWindow::~HypertextWindow()
{
}

Gtk::Window*
do_hypertext(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new HypertextWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

