#include <xfc/main.hh>
#include <xfc/gtk/treestore.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class TreeViewWindow : public Gtk::Window
{
	Pointer<Gtk::TreeStore> model;
	Gtk::TreeView *tree_view;

protected:
	void on_selection();
	void on_toggled(const String& path_str);

public:
	TreeViewWindow();
	virtual ~TreeViewWindow();
};

