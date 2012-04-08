/* Text Widget/Multiple Views
 *
 * The Gtk::TextView widget displays a Gtk::TextBuffer. One Gtk::TextBuffer
 * can be displayed by multiple Gtk::TextViews. This demo has two views
 * displaying a single buffer, and shows off the widget's text
 * formatting features.
 *
 */

#include "demowindow.hh"
#include <xfc/gtk/alignment.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/entry.hh>
#include <xfc/gtk/eventbox.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/menuitem.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/paned.hh>
#include <xfc/gtk/scale.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/widgetsignals.hh>
#include <xfc/gdk/bitmap.hh>
#include <xfc/gdk/color.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>

using namespace Xfc;

class EasterEggWindow : public Gtk::Window, protected Gtk::WidgetSignals
{
	static void recursive_attach_view(int depth, Gtk::TextView& view, Gtk::TextChildAnchor& anchor);

protected:
	virtual bool on_delete_event(const Gdk::EventAny& event);

public:
	EasterEggWindow();
	~EasterEggWindow();
};

class TextViewWindow : public Gtk::Window
{
	Gtk::TextBuffer *buffer_;
	EasterEggWindow *window;

	static bool find_anchor(Gtk::TextIter& iter);

	void create_tags();
	void insert_text();
	void on_easter_egg();

public:
	TextViewWindow();
	~TextViewWindow();

	void attach_widgets(Gtk::TextView& view);
};
//!

// EasterEggWindow

EasterEggWindow::EasterEggWindow()
: Gtk::WidgetSignals(this)
{
	Pointer<Gtk::TextBuffer> buffer = new Gtk::TextBuffer;
	Gtk::TextIter iter = buffer->get_start_iter();

	buffer->insert(iter, "This buffer is shared by a set of nested text views.\n Nested view:\n", -1);
	Gtk::TextChildAnchor *anchor = buffer->create_child_anchor(iter);
	buffer->insert(iter, "\nDon't do this in real applications, please.\n", -1);

	Gtk::TextView *view = new Gtk::TextView(*buffer);
	recursive_attach_view(0, *view, *anchor);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_policy_automatic();
	sw->add(*view);
	add(*sw);

	set_default_size(300, 400);
	show_all();
}

EasterEggWindow::~EasterEggWindow()
{
}

void
EasterEggWindow::recursive_attach_view(int depth, Gtk::TextView& view, Gtk::TextChildAnchor& anchor)
{
	if (depth > 4)
		return;

	Gtk::TextView *child_view = new Gtk::TextView(*view.get_buffer());

	// Event box is to add a black border around each child view
	Gtk::EventBox *event_box = new Gtk::EventBox;
	Gdk::Color color("black");
	event_box->modify_bg(Gtk::STATE_NORMAL, &color);

	Gtk::Alignment *align = new Gtk::Alignment(0.5, 0.5, 1.0, 1.0);
	align->set_border_width(1);

	event_box->add(*align);
	align->add(*child_view);

	view.add_child_at_anchor(*event_box, anchor);

	recursive_attach_view(depth + 1, *child_view, anchor);
}

bool
EasterEggWindow::on_delete_event(const Gdk::EventAny& event)
{
	hide();
	return true;
}

// TextViewWindow

TextViewWindow::TextViewWindow()
: window(0)
{
	set_title("TextView");
	set_border_width(0);
	set_default_size(450, 450);

	Gtk::VPaned *vpaned = new Gtk::VPaned;
	vpaned->set_border_width(5);
	add(*vpaned);

	// For convenience, we just use the autocreated buffer from the first text view; you could also
	//  create the buffer by itself with 'new Gtk::TextBuffer()', then later create a view widget.
	Gtk::TextView *view1 = new Gtk::TextView;
	buffer_ = view1->get_buffer();
	Gtk::TextView *view2 = new Gtk::TextView(*buffer_);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	vpaned->add1(*sw);

	sw->add(*view1);
	sw = new Gtk::ScrolledWindow;
	sw->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	vpaned->add2(*sw);

	sw->add(*view2);

	create_tags();
	insert_text();

	attach_widgets(*view1);
	attach_widgets(*view2);

	show_all();
}

TextViewWindow::~TextViewWindow()
{
	if (window)
		window->dispose();
}

#define gray50_width 2
#define gray50_height 2

static char gray50_bits[] = { 0x02, 0x01 };

void
TextViewWindow::create_tags()
{
	// Create a bunch of tags. Note that it's also possible to create tags with 'new Gtk::TextTag()' then
	// add them to the tag table for the buffer, Gtk::TextBuffer::create_tag() is just a convenience
	// function. Also note that you don't have to give tags a name; pass null for the name to create an
	// anonymous tag. In any real app, another useful optimization would be to create a Gtk::TextTagTable
	// in advance, and reuse the same tag table for all the buffers with the same tag set, instead of creating
	// new copies of the same tags for every buffer. Tags are assigned default priorities in order of addition
	// to the tag table. That is, tags created later that affect the same text property affected by an earlier
	// tag will override the earlier tag. You can modify tag priorities with Gtk::TextTag::set_priority().

	Gtk::TextTag *tag = buffer_->create_tag("heading");
	tag->property_weight().set(Pango::WEIGHT_BOLD);
	tag->property_size().set(15 * PANGO_SCALE);
	
	tag = buffer_->create_tag("italic");
	tag->property_style().set(Pango::STYLE_ITALIC);
	
	tag = buffer_->create_tag("bold");
	tag->property_weight().set(Pango::WEIGHT_BOLD);
	
	tag = buffer_->create_tag("big"); 
	tag->property_size().set(20 * PANGO_SCALE); // points times the PANGO_SCALE factor
	
	tag = buffer_->create_tag("xx-small");
	tag->property_scale().set(PANGO_SCALE_XX_SMALL);	
	
	tag = buffer_->create_tag("x-large");
	tag->property_scale().set(PANGO_SCALE_X_LARGE);
		
	tag = buffer_->create_tag("monospace");
	tag->property_family().set(String("monospace"));
		
	tag = buffer_->create_tag("blue_foreground");
	tag->property_foreground().set(String("blue"));	
	
	tag = buffer_->create_tag("red_background");
	tag->property_background().set(String("red"));	

	Pointer<Gdk::Bitmap> stipple = new Gdk::Bitmap(gray50_bits, gray50_width, gray50_height);
	tag = buffer_->create_tag("background_stipple");
	tag->property_background_stipple().set(stipple);
	tag = buffer_->create_tag("foreground_stipple");
	tag->property_foreground_stipple().set(stipple);

	tag = buffer_->create_tag("big_gap_before_line");
	tag->property_pixels_above_lines().set(30);	
	
	tag = buffer_->create_tag("big_gap_after_line");
	tag->property_pixels_below_lines().set(30);	
	
	tag = buffer_->create_tag("double_spaced_line");
	tag->property_pixels_inside_wrap().set(10);	
	
	tag = buffer_->create_tag("not_editable");
	tag->property_editable().set(false);	
	
	tag = buffer_->create_tag("word_wrap");
	tag->property_wrap_mode().set(Gtk::WRAP_WORD);
		
	tag = buffer_->create_tag("char_wrap");
	tag->property_wrap_mode().set(Gtk::WRAP_CHAR);
		
	tag = buffer_->create_tag("no_wrap");
	tag->property_wrap_mode().set(Gtk::WRAP_NONE);
		
	tag = buffer_->create_tag("center");
	tag->property_justification().set(Gtk::JUSTIFY_CENTER);
		
	tag = buffer_->create_tag("right_justify");
	tag->property_justification().set(Gtk::JUSTIFY_RIGHT);
		
	tag = buffer_->create_tag("wide_margins");
	tag->property_left_margin().set(50);	
	tag->property_right_margin().set(50);	
	
	tag = buffer_->create_tag("strikethrough");
	tag->property_strikethrough().set(true);
	
	tag = buffer_->create_tag("underline");
	tag->property_underline().set(Pango::UNDERLINE_SINGLE);
		
	tag = buffer_->create_tag("double_underline");
	tag->property_underline().set(Pango::UNDERLINE_DOUBLE);
		
	tag = buffer_->create_tag("superscript");
	tag->property_rise().set(10 * PANGO_SCALE);	// 10 pixels
	tag->property_size().set(8 * PANGO_SCALE); // 8 points
	
	tag = buffer_->create_tag("subscript");
	tag->property_rise().set(-10 * PANGO_SCALE); // 10 pixels
	tag->property_size().set(8 * PANGO_SCALE);	// 8 points
	
	tag = buffer_->create_tag("rtl_quote");
	tag->property_wrap_mode().set(Gtk::WRAP_WORD);
	tag->property_direction().set(Gtk::TEXT_DIR_RTL);
	tag->property_indent().set(30);
	tag->property_left_margin().set(20);
	tag->property_right_margin().set(20);
}

void
TextViewWindow::insert_text()
{
	// DemoWindow::find_file() looks in the the current directory first, then looks in the location where the file is installed.
	Pointer<Gdk::Pixbuf> pixbuf;
	String filename = DemoWindow::find_file("gtk-logo-rgb.gif", 0);
	if (!filename.null())
		pixbuf = Gdk::Pixbuf::create(filename);

	if (!pixbuf)
	{
		Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
		dialog.set_message("Failed to load image file gtk-logo-rgb.gif\n");
		dialog.set_position(Gtk::WIN_POS_CENTER);
		dialog.run();
		dialog.dispose();
		return;
	}

	Pointer<Gdk::Pixbuf> scaled = pixbuf->scale_simple(32, 32, Gdk::INTERP_BILINEAR);
	pixbuf = scaled;

	// get start of buffer; each insertion will revalidate the iterator to point to just after the inserted text.
	Gtk::TextIter iter = buffer_->get_iter_at_offset(0);

	buffer_->insert(iter, "The text widget can display text with all kinds of nifty attributes. It also supports multiple views of the same buffer; this demo is showing the same buffer in two places.\n\n");
	
	buffer_->insert_with_tag_by_name(iter, "Font styles. ", -1, "heading");

	buffer_->insert(iter, "For example, you can have ");
	buffer_->insert_with_tag_by_name(iter, "italic", -1, "italic");
	buffer_->insert(iter, ", ");
	buffer_->insert_with_tag_by_name(iter, "bold", -1, "bold");
	buffer_->insert(iter, ", or ");
	buffer_->insert_with_tag_by_name(iter, "monospace (typewriter)", -1, "monospace");
	buffer_->insert(iter, ", or ");
	buffer_->insert_with_tag_by_name(iter, "big", -1, "big");
	buffer_->insert(iter, " text. ");
	buffer_->insert(iter, "It's best not to hardcode specific text sizes; you can use relative sizes as with CSS, such as ");
	buffer_->insert_with_tag_by_name(iter, "xx-small", -1, "xx-small");
	buffer_->insert(iter, " or ");
	buffer_->insert_with_tag_by_name(iter, "x-large", -1, "x-large");
	buffer_->insert(iter, " to ensure that your program properly adapts if the user changes the default font size.\n\n");

	buffer_->insert_with_tag_by_name(iter, "Colors. ", -1, "heading");

	buffer_->insert(iter, "Colors such as ");
	buffer_->insert_with_tag_by_name(iter, "a blue foreground", -1, "blue_foreground");
	buffer_->insert(iter, " or ", -1);
	buffer_->insert_with_tag_by_name(iter, "a red background", -1, "red_background");
	buffer_->insert(iter, " or even ");
	
	std::vector<String> tag_names;
	tag_names.push_back("red_background");	
	tag_names.push_back("background_stipple");	
	buffer_->insert_with_tags_by_name(iter, "a stippled red background", -1, tag_names);

	buffer_->insert(iter, " or ");
	tag_names.clear();
	tag_names.push_back("blue_foreground");
	tag_names.push_back("red_background");
	tag_names.push_back("foreground_stipple");
	buffer_->insert_with_tags_by_name(iter, "a stippled blue foreground on solid red background", -1, tag_names);
	buffer_->insert(iter, " (select that to read it) can be used.\n\n");

	buffer_->insert_with_tag_by_name(iter, "Underline, strikethrough, and rise. ", -1, "heading");

	buffer_->insert_with_tag_by_name(iter,"Strikethrough", -1, "strikethrough");
	buffer_->insert(iter, ", ");
	buffer_->insert_with_tag_by_name(iter, "underline", -1, "underline");
	buffer_->insert(iter, ", ");
	buffer_->insert_with_tag_by_name(iter, "double underline", -1, "double_underline");
	buffer_->insert(iter, ", ");
	buffer_->insert_with_tag_by_name(iter, "superscript", -1, "superscript");
	buffer_->insert(iter, ", and ");
	buffer_->insert_with_tag_by_name(iter, "subscript", -1, "subscript");
	buffer_->insert(iter, " are all supported.\n\n");

	buffer_->insert_with_tag_by_name(iter, "Images. ", -1, "heading");

	buffer_->insert(iter, "The buffer can have images in it: ");
	buffer_->insert_pixbuf(iter, *pixbuf);
	buffer_->insert_pixbuf(iter, *pixbuf);
	buffer_->insert_pixbuf(iter, *pixbuf);
	buffer_->insert(iter, " for example.\n\n");

	buffer_->insert_with_tag_by_name(iter, "Spacing. ", -1, "heading");

	buffer_->insert(iter, "You can adjust the amount of space before each line.\n");

	tag_names.clear();
	tag_names.push_back("big_gap_before_line");
	tag_names.push_back("wide_margins");
	buffer_->insert_with_tags_by_name(iter, "This line has a whole lot of space before it.\n", -1, tag_names);
	
	tag_names.clear();
	tag_names.push_back("big_gap_after_line");
	tag_names.push_back("wide_margins");
	buffer_->insert_with_tags_by_name(iter, "You can also adjust the amount of space after each line; this line has a whole lot of space after it.\n", -1, tag_names);
	
	tag_names.clear();
	tag_names.push_back("double_spaced_line");
	tag_names.push_back("wide_margins");
	buffer_->insert_with_tags_by_name(iter, "You can also adjust the amount of space between wrapped lines; this line has extra space between each wrapped line in the same paragraph. To show off wrapping, some filler text: the quick brown fox jumped over the lazy dog. Blah blah blah blah blah blah blah blah blah.\n", -1, tag_names);

	buffer_->insert(iter, "Also note that those lines have extra-wide margins.\n\n");

	buffer_->insert_with_tag_by_name(iter, "Editability. ", -1, "heading");

	buffer_->insert_with_tag_by_name(iter, "This line is 'locked down' and can't be edited by the user - just try it! You can't delete this line.\n\n", -1, "not_editable");

	buffer_->insert_with_tag_by_name(iter, "Wrapping. ", -1, "heading");

	buffer_->insert(iter, "This line (and most of the others in this buffer) is word-wrapped, using the proper Unicode algorithm. Word wrap should work in all scripts and languages that GTK+ supports. Let's make this a long paragraph to demonstrate: blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah\n\n");

	buffer_->insert_with_tag_by_name(iter, "This line has character-based wrapping, and can wrap between any two character glyphs. Let's make this a long paragraph to demonstrate: blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah blah\n\n", -1, "char_wrap");

	buffer_->insert_with_tag_by_name(iter, "This line has all wrapping turned off, so it makes the horizontal scrollbar appear.\n\n\n", -1, "no_wrap");

	buffer_->insert_with_tag_by_name(iter, "Justification. ", -1, "heading");

	buffer_->insert_with_tag_by_name(iter,  "\nThis line has center justification.\n", -1, "center");

	buffer_->insert_with_tag_by_name(iter, "This line has right justification.\n", -1, "right_justify");

	buffer_->insert_with_tag_by_name(iter, "\nThis line has big wide margins. Text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text.\n", -1, "wide_margins");

	buffer_->insert_with_tag_by_name(iter, "Internationalization. ", -1, "heading");

	buffer_->insert(iter, "You can put all sorts of Unicode text in the buffer.\n\nGerman (Deutsch S\xC3\xBC""d) Gr\xC3\xBC\xC3\x9F Gott\nGreek (\xCE\x95\xCE\xBB\xCE\xBB\xCE\xB7\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xAC) \xCE\x93\xCE\xB5\xCE\xB9\xCE\xAC \xCF\x83\xCE\xB1\xCF\x82\nHebrew\t\xD7\xA9\xD7\x9C\xD7\x95\xD7\x9D\nJapanese (\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E)\n\nThe widget properly handles bidirectional text, word wrapping, DOS/UNIX/Unicode paragraph separators, grapheme boundaries, and so on using the Pango internationalization framework.\n");

	buffer_->insert(iter, "Here's a word-wrapped quote in a right-to-left language:\n");
	buffer_->insert_with_tag_by_name(iter, "\xD9\x88\xD9\x82\xD8\xAF \xD8\xA8\xD8\xAF\xD8\xA3 \xD8\xAB\xD9\x84\xD8\xA7\xD8\xAB \xD9\x85\xD9\x86 \xD8\xA3\xD9\x83\xD8\xAB\xD8\xB1 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA4\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD8\xAA\xD9\x82\xD8\xAF\xD9\x85\xD8\xA7 \xD9\x81\xD9\x8A \xD8\xB4\xD8\xA8\xD9\x83\xD8\xA9 \xD8\xA7\xD9\x83\xD8\xB3\xD9\x8A\xD9\x88\xD9\x86 \xD8\xA8\xD8\xB1\xD8\xA7\xD9\x85\xD8\xAC\xD9\x87\xD8\xA7 \xD9\x83\xD9\x85\xD9\x86\xD8\xB8\xD9\x85\xD8\xA7\xD8\xAA \xD9\x84\xD8\xA7 \xD8\xAA\xD8\xB3\xD8\xB9\xD9\x89 \xD9\x84\xD9\x84\xD8\xB1\xD8\xA8\xD8\xAD\xD8\x8C \xD8\xAB\xD9\x85 \xD8\xAA\xD8\xAD\xD9\x88\xD9\x84\xD8\xAA \xD9\x81\xD9\x8A \xD8\xA7\xD9\x84\xD8\xB3\xD9\x86\xD9\x88\xD8\xA7\xD8\xAA \xD8\xA7\xD9\x84\xD8\xAE\xD9\x85\xD8\xB3 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA7\xD8\xB6\xD9\x8A\xD8\xA9 \xD8\xA5\xD9\x84\xD9\x89 \xD9\x85\xD8\xA4\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD9\x85\xD8\xA7\xD9\x84\xD9\x8A\xD8\xA9 \xD9\x85\xD9\x86\xD8\xB8\xD9\x85\xD8\xA9\xD8\x8C \xD9\x88\xD8\xA8\xD8\xA7\xD8\xAA\xD8\xAA \xD8\xAC\xD8\xB2\xD8\xA1\xD8\xA7 \xD9\x85\xD9\x86 \xD8\xA7\xD9\x84\xD9\x86\xD8\xB8\xD8\xA7\xD9\x85 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA7\xD9\x84\xD9\x8A \xD9\x81\xD9\x8A \xD8\xA8\xD9\x84\xD8\xAF\xD8\xA7\xD9\x86\xD9\x87\xD8\xA7\xD8\x8C \xD9\x88\xD9\x84\xD9\x83\xD9\x86\xD9\x87\xD8\xA7 \xD8\xAA\xD8\xAA\xD8\xAE\xD8\xB5\xD8\xB5 \xD9\x81\xD9\x8A \xD8\xAE\xD8\xAF\xD9\x85\xD8\xA9 \xD9\x82\xD8\xB7\xD8\xA7\xD8\xB9 \xD8\xA7\xD9\x84\xD9\x85\xD8\xB4\xD8\xB1\xD9\x88\xD8\xB9\xD8\xA7\xD8\xAA \xD8\xA7\xD9\x84\xD8\xB5\xD8\xBA\xD9\x8A\xD8\xB1\xD8\xA9. \xD9\x88\xD8\xA3\xD8\xAD\xD8\xAF \xD8\xA3\xD9\x83\xD8\xAB\xD8\xB1 \xD9\x87\xD8\xB0\xD9\x87 \xD8\xA7\xD9\x84\xD9\x85\xD8\xA4\xD8\xB3\xD8\xB3\xD8\xA7\xD8\xAA \xD9\x86\xD8\xAC\xD8\xA7\xD8\xAD\xD8\xA7 \xD9\x87\xD9\x88 \xC2\xBB\xD8\xA8\xD8\xA7\xD9\x86\xD9\x83\xD9\x88\xD8\xB3\xD9\x88\xD9\x84\xC2\xAB \xD9\x81\xD9\x8A \xD8\xA8\xD9\x88\xD9\x84\xD9\x8A\xD9\x81\xD9\x8A\xD8\xA7.\n\n", -1, "rtl_quote");

	buffer_->insert(iter, "You can put widgets in the buffer: Here's a button: ");
	buffer_->create_child_anchor(iter);
	buffer_->insert(iter, " and a menu: ");
	buffer_->create_child_anchor(iter);
	buffer_->insert(iter, " and a scale: ");
	buffer_->create_child_anchor(iter);
	buffer_->insert(iter, " and an animation: ");
	buffer_->create_child_anchor(iter);
	buffer_->insert(iter, " finally a text entry: ");
	buffer_->create_child_anchor(iter);
	buffer_->insert(iter, ".\n");

	buffer_->insert(iter, "\n\nThis demo doesn't demonstrate all the GtkTextBuffer features; it leaves out, for example: invisible/hidden text (doesn't work in GTK 2, but planned), tab stops, application-drawn areas on the sides of the widget for displaying breakpoints and such...");

	// Apply word_wrap tag to whole buffer
	Gtk::TextIter start, end;
	buffer_->get_bounds(start, end);
	buffer_->apply_tag_by_name("word_wrap", start, end);
}

bool
TextViewWindow::find_anchor(Gtk::TextIter& iter)
{
	while (iter.forward_char())
	{
		if (iter.get_child_anchor())
			return true;
	}
	return false;
}

void
TextViewWindow::on_easter_egg()
{
	if (!window)
		window = new EasterEggWindow;
	else
		window->present();
}

void
TextViewWindow::attach_widgets(Gtk::TextView& view)
{
	Gtk::TextBuffer *buffer = view.get_buffer();
	Gtk::TextIter iter = buffer->get_start_iter();

	int i = 0;
	while (find_anchor(iter))
	{
		Gtk::Widget *widget;
		Gtk::TextChildAnchor *anchor = iter.get_child_anchor();

		if (i == 0)
		{
			Gtk::Button *button = new Gtk::Button("Click Me");
			button->signal_clicked().connect(sigc::mem_fun(this, &TextViewWindow::on_easter_egg));
			widget = button;
        }
		else if (i == 1)
		{
  			Gtk::ComboBoxText *combo_box = new Gtk::ComboBoxText;       
			combo_box->append("Option 1");
			combo_box->append("Option 2");
			combo_box->append("Option 3");
			widget = combo_box;
		}
		else if (i == 2)
		{
			widget = new Gtk::HScale(0.0, 100.0);
			widget->set_size_request(70, -1);
		}
		else if (i == 3)
		{
			String filename = DemoWindow::find_file("floppybuddy.gif");
			Gtk::Image *image = new Gtk::Image(filename);
			widget = image;
		}
		else if (i == 4)
		{
			widget = new Gtk::Entry;
		}
		else
		{
			widget = 0; // avoids a compiler warning
			g_assert_not_reached();
		}

		view.add_child_at_anchor(*widget, *anchor);
		widget->show_all();
		++i;
	}
}

Gtk::Window*
do_textview(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new TextViewWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

