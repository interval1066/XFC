#include <xfc/gtk/window.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/textview.hh>
#include <xfc/gtk/treestore.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/glib/error.hh>

using namespace Xfc;

class DemoTreeView : public Gtk::TreeView
{
	Pointer<Gtk::TreeStore> model;

protected:
	void on_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn& column);
	void on_demo_destroy(Gtk::TreePath *path);
	void on_selection_changed();

public:
	DemoTreeView();
	~DemoTreeView();
};

class DemoTextView : public Gtk::ScrolledWindow
{
public:
	DemoTextView(Pointer<Gtk::TextBuffer> &buffer, bool is_source);
	~DemoTextView();
};

class DemoWindow : public Gtk::Window
{
	Gtk::TreeView *tree_view;

	static Pointer<Gtk::TextBuffer> info_buffer;
	static Pointer<Gtk::TextBuffer> header_buffer;
	static Pointer<Gtk::TextBuffer> source_buffer;

	static char *current_file;

	void set_default_icon();
	static void fontify(Pointer<Gtk::TextBuffer>& buffer);

public:
	DemoWindow();
	~DemoWindow();

	static String find_file(const char *base, G::Error *error = 0);
	static void load_file(const char *filename);
};

