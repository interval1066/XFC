#include <xfc/main.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/buttonbox.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class ButtonBoxFrame : public Gtk::Frame
{
public:
	ButtonBoxFrame(bool horizontal, const char *title, int spacing, Gtk::ButtonBoxStyle layout);
	virtual ~ButtonBoxFrame();
};

class ButtonBoxWindow : public Gtk::Window
{
public:
	ButtonBoxWindow();
	virtual ~ButtonBoxWindow();
};

