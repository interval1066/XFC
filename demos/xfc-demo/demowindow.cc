#include "demos.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/notebook.hh>
#include <xfc/gtk/treestore.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <xfc/pango/font.hh>
#include <xfc/glib/value.hh>
#include <glib/gstdio.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

const int TITLE_COLUMN = 0;
const int FILENAME_COLUMN = 1;
const int SLOT_COLUMN = 2;
const int ITALIC_COLUMN = 3;
const int NUM_COLUMNS = 4;

Pointer<Gtk::TextBuffer> DemoWindow::info_buffer;
Pointer<Gtk::TextBuffer> DemoWindow::header_buffer;
Pointer<Gtk::TextBuffer> DemoWindow::source_buffer;

char *DemoWindow::current_file = 0;

// DemoTreeView

DemoTreeView::DemoTreeView()
{
	Demo *demo = testgtk_demos;

	model = new Gtk::TreeStore(NUM_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_BOOLEAN);
	set_model(model);

	Gtk::TreeSelection *selection = get_selection();
	selection->set_mode(Gtk::SELECTION_BROWSE);

	// this code only supports 1 level of children. If we want more we probably have to use a recursing function.
	while (demo->title)
	{
		Demo *children = demo->children;

		Gtk::TreeIter iter = model->append();
		model->set_value(iter, TITLE_COLUMN, demo->title);
		model->set_value(iter, FILENAME_COLUMN, demo->filename);
		model->set_pointer(iter, SLOT_COLUMN, &demo->do_slot);
		model->set_value(iter, ITALIC_COLUMN, false);
		demo++;

		if (!children)
			continue;

		while (children->title)
		{
			Gtk::TreeIter child_iter = model->append(&iter);
			model->set_value(child_iter, TITLE_COLUMN, children->title);
			model->set_value(child_iter, FILENAME_COLUMN, children->filename);
			model->set_pointer(child_iter, SLOT_COLUMN, &children->do_slot);
			model->set_value(child_iter, ITALIC_COLUMN, false);
			children++;
		}
	}

	Gtk::CellRendererText *cell = new Gtk::CellRendererText;
	cell->property_style().set(Pango::STYLE_ITALIC);

	Gtk::CellColumnAttributes attributes;
	attributes.add("text", TITLE_COLUMN);
	attributes.add("style_set", ITALIC_COLUMN);
	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Widget (double click for demo)", *cell, attributes);
	append_column(*column);
	selection->signal_changed().connect(sigc::mem_fun(this, &DemoTreeView::on_selection_changed));
	signal_row_activated().connect(sigc::mem_fun(this, &DemoTreeView::on_row_activated));
	expand_all();
}

DemoTreeView::~DemoTreeView()
{
}

void
DemoTreeView::on_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn& column)
{
	Gtk::TreeIter iter;
	if (model->get_iter(iter, path))
	{
		bool italic;
		model->get_value(iter, ITALIC_COLUMN, italic);
		DoSlot *do_slot = 0;
		model->get_pointer(iter, SLOT_COLUMN, do_slot);
		if (do_slot)
		{
			Gtk::Window *window = (*do_slot)(get_toplevel());
			if (window)
			{
				Gtk::TreePath *tmp_path = new Gtk::TreePath(path);		
				window->signal_destroy().connect(sigc::bind(sigc::mem_fun(this, &DemoTreeView::on_demo_destroy), tmp_path));
			}
			model->set_value(iter, ITALIC_COLUMN, !italic);
		}
	}
}

void
DemoTreeView::on_demo_destroy(Gtk::TreePath *path)
{
	Gtk::TreeIter iter;
	if (model->get_iter(iter, *path))
	{
		bool italic;
		model->get_value(iter, ITALIC_COLUMN, italic);
		DoSlot *do_slot = 0;
		model->get_pointer(iter, SLOT_COLUMN, do_slot);
		if (do_slot)
		{
			(*do_slot)(0);
			model->set_value(iter, ITALIC_COLUMN, !italic);
		}
	}
	path->unref();
}

void
DemoTreeView::on_selection_changed()
{
	Gtk::TreeIter iter;
	if (!get_selection()->get_selected(&iter))
		return;

	// Example of using G::Value to get a String value.
	G::Value value;
	String filename;
	model->get_value(iter, FILENAME_COLUMN, value);
	if (value.get(filename))
		DemoWindow::load_file(filename.c_str());
}

// DemoTextView

DemoTextView::DemoTextView(Pointer<Gtk::TextBuffer> &buffer, bool is_source)
{
	set_policy_automatic();
	set_shadow_type(Gtk::SHADOW_IN);

	buffer = new Gtk::TextBuffer;
	Gtk::TextView *text_view = new Gtk::TextView(*buffer);
	text_view->set_editable(false);
	text_view->set_cursor_visible(false);
	add(*text_view);

	if (is_source)
	{
		Pointer<Pango::FontDescription> font_desc = new Pango::FontDescription("Courier 12");
		text_view->modify_font(font_desc);
		text_view->set_wrap_mode(Gtk::WRAP_NONE);
	}
	else
	{
		text_view->set_wrap_mode(Gtk::WRAP_WORD);
		text_view->set_pixels_above_lines(2);
		text_view->set_pixels_below_lines(2);
	}
}

DemoTextView::~DemoTextView()
{
}

// DemoWindow

DemoWindow::DemoWindow()
{
	set_title("XFC Code Demos");
	set_default_icon();
	set_default_size(600, 400);

	Gtk::HBox *hbox = new Gtk::HBox;
	add(*hbox);

	tree_view = new DemoTreeView();
	hbox->pack_start(*tree_view, false, false);

	Gtk::Notebook *notebook = new Gtk::Notebook;
	DemoTextView *text_view = new DemoTextView(info_buffer, false);
	Gtk::Label *label = new Gtk::Label("_Info", true);
	notebook->append_page(*text_view, label);
	Gtk::TextTag *tag = info_buffer->create_tag("title");
	tag->property_font().set(String("Sans 18"));

	text_view = new DemoTextView(header_buffer, true);
	label = new Gtk::Label("_Header", true);
	notebook->append_page(*text_view, label);
	tag = header_buffer->create_tag("comment");
	tag->property_font().set(String("DarkBlue"));
	tag = header_buffer->create_tag("type");
	tag->property_foreground().set(String("DarkRed"));	
	tag = header_buffer->create_tag("string");
	tag->property_foreground().set(String("red"));
	tag->property_weight().set(Pango::WEIGHT_BOLD);
	tag = header_buffer->create_tag("control");
	tag->property_foreground().set(String("purple"));	
	tag = header_buffer->create_tag("preprocessor");
	tag->property_style().set(Pango::STYLE_OBLIQUE);	
	tag->property_foreground().set(String("blue"));	
	tag = header_buffer->create_tag("function");
	tag->property_weight().set(Pango::WEIGHT_BOLD);
		
	text_view = new DemoTextView(source_buffer, true);
	label = new Gtk::Label("_Source", true);
	notebook->append_page(*text_view, label);
	tag = source_buffer->create_tag("comment");
	tag->property_foreground().set("DarkBlue"); 	
	tag = source_buffer->create_tag("type");
	tag->property_foreground().set( "DarkRed");
	tag = source_buffer->create_tag("string");
	tag->property_foreground().set("red");	
	tag->property_weight().set(Pango::WEIGHT_BOLD);	
	tag = source_buffer->create_tag("control");
	tag->property_foreground().set("purple");
	tag = source_buffer->create_tag("preprocessor");
	tag->property_style().set(Pango::STYLE_OBLIQUE);	
	tag->property_foreground().set("blue");	
	tag = source_buffer->create_tag("function");
	tag->property_weight().set(Pango::WEIGHT_BOLD);
	tag->property_foreground().set("DarkGreen");	
	
	hbox->pack_start(*notebook);
	hbox->show_all();
	load_file(testgtk_demos[0].filename);
}

DemoWindow::~DemoWindow()
{
	gtk_window_set_default_icon_list(0);
	g_free(current_file);
}


void
DemoWindow::set_default_icon()
{
	Pointer<Gdk::Pixbuf> pixbuf;
	G::Error error;

	String filename = find_file("gtk-logo-rgb.gif", &error);
	if (!filename.null())
		pixbuf = Gdk::Pixbuf::create(filename, &error);

	if (error.get())
    	{
		Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
		dialog.format_message("Failed to read icon file: %s", error.message());
		dialog.set_position(Gtk::WIN_POS_CENTER);
		dialog.run();
		dialog.dispose();
	}

	if (pixbuf)
	{
		Pointer<Gdk::Pixbuf> transparent = pixbuf->add_alpha(true, 0xff, 0xff, 0xff);
		std::vector<Gdk::Pixbuf*> list;
		list.push_back(transparent);
		set_default_icon_list(list);
	}
}

String
DemoWindow::find_file(const char *base, G::Error *error)
{
	if (g_file_test(base, G_FILE_TEST_EXISTS))
		return base;
	else
	{
		char *filename = g_build_filename(DEMOCODEDIR, base, NULL);
		if (!g_file_test(filename, G_FILE_TEST_EXISTS))
		{
			if (error)
				error->set(G_FILE_ERROR, G_FILE_ERROR_NOENT, "Cannot find demo data file \"%s\"", base);
	  		g_free(filename);
			return 0;
		}
		String s(filename);
		g_free(filename);
		return s;
	}
}

namespace {

/* Stupid syntax highlighting.
 *
 * No regex was used in the making of this highlighting.
 * It should only work for simple cases.  This is good, as
 * that's all we should have in the demos.
 *
 * This code should not be used elsewhere, except perhaps as an example of how
 * to iterate through a text buffer.
 */

enum
{
	STATE_NORMAL,
	STATE_IN_COMMENT
};

static const char *tokens[] =
{
	"/*",
	"\"",
	0
};

static const char *types[] =
{
	"namespace",
	"class",
	"struct",
	"enum",
	"public",
	"protected",
	"private",
	"static",
	"using",
	"const",
	"void",
	"bool",
	"char",
	"int",
	"short"
	"long",
	"float",
	"double",
	"unsigned",
	"false",
	"true",
	"FILE ",
	"Pointer",
	"size_t",
	0
};

static const char *control[] =
{
	" if ",
	" while ",
	" else",
	" do ",
	" for ",
	"?",
	":",
	"return ",
	"goto ",
	0
};

gboolean
read_line(FILE *stream, GString *str)
{
	int n_read = 0;

#ifdef HAVE_FLOCKFILE
	flockfile(stream);
#endif

	g_string_truncate(str, 0);

	while (1)
	{
		int c;

#ifdef HAVE_GETC_UNLOCKED
		c = getc_unlocked(stream);
#else
		c = getc(stream);
#endif

		if (c == EOF)
			goto done;
		else
			n_read++;

		switch (c)
		{
			case '\r':
			case '\n':
			{
#ifdef HAVE_GETC_UNLOCKED
				int next_c = getc_unlocked(stream);
#else
				int next_c = getc(stream);
#endif

				if (!(next_c == EOF || (c == '\r' && next_c == '\n') || (c == '\n' && next_c == '\r')))
					ungetc(next_c, stream);

				goto done;
			}
			default:
				g_string_append_c(str, c);
		}
	}

	done:

#ifdef HAVE_FUNFLOCKFILE
	funlockfile(stream);
#endif
	return n_read > 0;
}

void parse_chars(char *text, char **end_ptr, int *state, char **tag, bool start)
{
	while (g_ascii_isspace(*text))
				text++;

	int i;
	char *next_token;

	// Handle comments first
	if (*state == STATE_IN_COMMENT)
	{
		*end_ptr = strstr(text, "*/");
		if (*end_ptr)
		{
			*end_ptr += 2;
			*state = STATE_NORMAL;
			*tag = "comment";
		}
		return;
	}

	*tag = 0;
	*end_ptr = 0;

	// check for comment
	if (text[0] == '/')
    {
		if (text[1] == '*')
			*end_ptr = strstr(text, "*/");
		else if (text[1] == '/')
			*end_ptr = strstr(text, "\n");
		if (*end_ptr)
			*end_ptr += 2;
		else
			*state = STATE_IN_COMMENT;
		*tag = "comment";
		return;
	}

	// check for preprocessor defines
	if (*text == '#' && start)
	{
		*end_ptr = 0;
		*tag = "preprocessor";
		return;
	}

	// functions
	if (start && * text != '\t' && *text != ' ' && *text != '{' && *text != '}')
	{
		if (strstr (text, "("))
		{
			*end_ptr = strstr (text, "(");
			*tag = "function";
			return;
		}
	}

	// check for types
	for (i = 0; types[i] != 0; i++)
		if (!strncmp(text, types[i], strlen(types[i])))
		{
			*end_ptr = text + strlen (types[i]);
			*tag = "type";
			return;
		}

	// check for control
	for (i = 0; control[i] != 0; i++)
		if (!strncmp(text, control[i], strlen(control[i])))
		{
			*end_ptr = text + strlen(control[i]);
			*tag = "control";
			return;
		}

	// check for string
	if (text[0] == '"')
	{
		bool maybe_escape = false;
		*end_ptr = text + 1;
		*tag = "string";
		while (**end_ptr != '\000')
		{
			if (**end_ptr == '\"' && !maybe_escape)
			{
				*end_ptr += 1;
				return;
			}
			if (**end_ptr == '\\')
				maybe_escape = true;
			else
				maybe_escape = false;
			*end_ptr += 1;
		}
		return;
	}

	// not at the start of a tag.  Find the next one.
	for (i = 0; tokens[i] != 0; i++)
	{
		next_token = strstr(text, tokens[i]);
		if (next_token)
		{
			if (*end_ptr)
				*end_ptr = (*end_ptr < next_token) ? *end_ptr : next_token;
			else
				*end_ptr = next_token;
		}
	}

	for (i = 0; types[i] != 0; i++)
	{
		next_token = strstr(text, types[i]);
		if (next_token)
		{
			if (*end_ptr)
				*end_ptr = (*end_ptr < next_token) ? *end_ptr : next_token;
			else
				*end_ptr = next_token;
		}
	}

	for (i = 0; control[i] != 0; i++)
	{
		next_token = strstr(text, control[i]);
		if (next_token)
		{
			if (*end_ptr)
				*end_ptr = (*end_ptr < next_token) ? *end_ptr : next_token;
			else
				*end_ptr = next_token;
		}
	}
}

} // namespace

void
DemoWindow::fontify(Pointer<Gtk::TextBuffer>& buffer)
{
	// While not as cool as c-mode, this will do as a quick attempt at highlighting
	Gtk::TextIter start_iter = buffer->get_iter_at_offset(0);
	Gtk::TextIter next_iter = start_iter;

	while (next_iter.forward_line())
	{
		bool start = true;
		int state = STATE_NORMAL;
		char *text, *start_ptr, *end_ptr, *tag;
		start_ptr = text = gtk_text_iter_get_text(start_iter.gtk_text_iter(), next_iter.gtk_text_iter());

		do
		{
			Gtk::TextIter tmp_iter;
			parse_chars(start_ptr, &end_ptr, &state, &tag, start);
			start = false;
			if (end_ptr)
			{
				tmp_iter = start_iter;
				tmp_iter.forward_chars(end_ptr - start_ptr);
			}
			else
				tmp_iter = next_iter;

			if (tag)
				buffer->apply_tag_by_name(tag, start_iter, tmp_iter);
			start_iter = tmp_iter;
			start_ptr = end_ptr;
		}
		while (end_ptr);

		g_free(text);
		start_iter = next_iter;
	}
}

void
DemoWindow::load_file (const char *filename)
{
	if (current_file && !strcmp(current_file, filename))
		return;

	g_free (current_file);
	current_file = g_strdup(filename);

	Gtk::TextIter start, end;
	info_buffer->get_bounds(start, end);
	info_buffer->delete_range(start, end);
	header_buffer->get_bounds(start, end);
	header_buffer->delete_range(start, end);
	source_buffer->get_bounds(start, end);
	source_buffer->delete_range(start, end);

	G::Error error;
	String full_filename = find_file(filename, &error);
	if (full_filename.null())
	{
		g_warning("%s", error.message());
		return;
	}

	FILE *file = g_fopen(full_filename.c_str(), "r");
	if (!file)
	{
		g_warning("Cannot open %s: %s\n", full_filename.c_str(), g_strerror(errno));
		return;
	}

	start = info_buffer->get_iter_at_offset(0);

	int state = 0;
	bool in_para = false;
	GString *buffer = g_string_new(0);
	while (read_line(file, buffer))
	{
		char *p = buffer->str;
		char *q;
		char *r;

		switch (state)
		{
		case 0:
			// Reading title
			while (*p == '/' || *p == '*' || g_ascii_isspace(*p))
				p++;
			r = p;
			while (*r != '/' && strlen(r))
				r++;
			if (strlen(r) > 0)
				p = r + 1;
			q = p + strlen(p);
			while (q > p && g_ascii_isspace(*(q - 1)))
				q--;

			if (q > p)
			{
				int len_chars = g_utf8_pointer_to_offset(p, q);
				end = start;
				g_assert(strlen(p) >= (unsigned int)(q - p));
				info_buffer->insert(end, String(p, q - p));
				start = end;
				start.backward_chars(len_chars);
				info_buffer->apply_tag_by_name("title", start, end);
				start = end;
				state++;
	   		}
			break;

		case 1:
			// Reading body of info section
			while (g_ascii_isspace(*p))
				p++;
			if (*p == '*' && *(p + 1) == '/')
			{
				start = header_buffer->get_iter_at_offset(0);
				state++;
			}
			else
			{
				while (*p == '*' || g_ascii_isspace (*p))
					p++;
				int len = strlen (p);
				while (g_ascii_isspace(*(p + len - 1)))
					len--;

				if (len > 0)
				{
					if (in_para)
						info_buffer->insert(start, " ");
					g_assert(strlen(p) >= (unsigned int)len);
					info_buffer->insert(start, String(p, len));
					in_para = true;
				}
				else
				{
					info_buffer->insert(start, "\n");
					in_para = false;
				}
			}
			break;

		case 2:
			// Skipping blank lines
			while (g_ascii_isspace(*p))
				p++;
			if (*p)
			{
				p = buffer->str;
				state++;
				// Fall through
	    	}
			else
				break;

		case 3:
			// Reading program's class interface
			if (*p == '/' && *(p + 1) == '/' && *(p + 2) == '!')
			{
				header_buffer->insert(start, "\n");
				start = source_buffer->get_iter_at_offset(0);
				state++;
			}
			else
			{
				int len = strlen(p);
				while (g_ascii_isspace(*(p + len - 1)))
					len--;
				if (len > 0)
				{
					g_assert(strlen(p) >= (unsigned int)len);
					header_buffer->insert(start, String(p, len));
				}
				header_buffer->insert(start, "\n");
			}
			break;

		case 4:
			// Skipping blank lines again
			while (g_ascii_isspace(*p))
				p++;
			if (*p)
			{
				p = buffer->str;
				state++;
				// Fall through
	    	}
			else
				break;

		case 5:
			// Reading program's class implmentation
			source_buffer->insert(start, p);
			source_buffer->insert(start, "\n");
			break;
		}
    }

	fontify(header_buffer);
	fontify(source_buffer);
	g_string_free(buffer, TRUE);
}

