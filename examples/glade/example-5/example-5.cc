/* This program displays a window that contains one widget, a play/pause media button.
 * When the button is clicked the image changes from a play image to a pause image
 * and vice versa.
 *
 * The purpose of this example is to show you how to dynamically switch images on a
 * icon button created with Glade.
 */

#include "example-5.hh"
#include <xfc/gtk/button.hh>
#include <xfc/gtk/stockid.hh>

MediaWindow::MediaWindow(CObjectType *object, const Glade::Xml& xml)
: Gtk::Window(object),
  is_playing(false)
{
	Gtk::Button *button;
	xml.get_widget("MediaButton", button); 		
	if (button)
	{
		button->signal_clicked().connect(sigc::mem_fun(this, &MediaWindow::on_button_clicked));
	}

	xml.get_widget("PlayPauseImage", image); 		
}

MediaWindow::~MediaWindow()
{
}

void
MediaWindow::on_button_clicked()
{
	if (!image)
		return;

	if (!is_playing)
	{
		image->set(Gtk::StockId::MEDIA_PAUSE, Gtk::ICON_SIZE_BUTTON);
		is_playing = true;	
	}
	else
	{
		image->set(Gtk::StockId::MEDIA_PLAY, Gtk::ICON_SIZE_BUTTON);
		is_playing = false;
	}	
}

int main (int argc, char *argv[])
{
	using namespace Main;
	
	init(&argc, &argv);
		
	Pointer<Glade::Xml> xml = Glade::Xml::create("example-5.glade");
	if (!xml)
		return 1;
	
	MediaWindow *window;
	if (xml->get_widget_derived("MediaWindow", window))
	{
		window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
		window->show();
		run();
	}
	return 0;
}

