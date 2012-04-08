#include <xfc/main.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class CompletionModel : public Gtk::ListStore
{
public:
	CompletionModel();
};

class Window : public Gtk::Window
{
public:
	Window();
	virtual ~Window();
};

