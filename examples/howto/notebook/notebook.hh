#include <xfc/main.hh>
#include <xfc/gtk/notebook.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class Notebook : public Gtk::Notebook
{
public:
	Notebook();
	virtual ~Notebook();

	void on_rotate_book();
	void on_tabsborder_book();
	void on_remove_book();
};

class NotebookWindow : public Gtk::Window
{
public:
	NotebookWindow();
	virtual ~NotebookWindow();
};

