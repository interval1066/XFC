/* This program displays a simple window and has a simple callback for when the OK button is clicked.
 *
 * XFC translation of Example-1 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/glade/xml.hh>

using namespace Xfc;

class MainWindow : public Gtk::Window
{
protected:
	void ok_button_clicked();

public:
	MainWindow(CObjectType *object, const Glade::Xml& xml);
};

