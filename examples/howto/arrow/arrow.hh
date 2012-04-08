#include <xfc/main.hh>
#include <xfc/gtk/arrow.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

// ArrowButton

class ArrowButton : public Gtk::Button
{
	ArrowButton(const ArrowButton&);
	ArrowButton& operator=(const ArrowButton&);

public:
	ArrowButton(Gtk::ArrowType arrow_type, Gtk::ShadowType shadow_type);
	virtual ~ArrowButton();
};

// ArrowWindow

class ArrowWindow : public Gtk::Window
{
	ArrowWindow(const ArrowWindow&);
	ArrowWindow& operator=(const ArrowWindow&);

public:
	ArrowWindow();
	virtual ~ArrowWindow();
};
