#include <xfc/main.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class PackBox : public Gtk::HBox
{
public:
	PackBox(bool homogeneous, int spacing, bool expand, bool fill, unsigned int padding);
	~PackBox();
};

class PackBoxWindow : public Gtk::Window
{
public:
	PackBoxWindow(int which);
	~PackBoxWindow();
	
	void example_1(Gtk::VBox *vbox);
	void example_2(Gtk::VBox *vbox);
	void example_3(Gtk::VBox *vbox);
};

