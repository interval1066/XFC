#include <xfc/main.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class MessageList : public Gtk::ScrolledWindow
{
public:
	MessageList();
	virtual ~MessageList();
};

class TextWindow : public Gtk::ScrolledWindow
{
public:
	TextWindow();
	virtual ~TextWindow();
};

class PanedWindow : public Gtk::Window
{
public:
	PanedWindow();
	virtual ~PanedWindow();
};

