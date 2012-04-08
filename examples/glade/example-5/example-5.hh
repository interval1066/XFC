#include <xfc/main.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/image.hh>
#include <xfc/glade/xml.hh>

using namespace Xfc;

class MediaWindow : public Gtk::Window
{
	Gtk::Image *image;
	bool is_playing;

protected:
	void on_button_clicked();

public:
	MediaWindow(CObjectType *object, const Glade::Xml& xml);
	virtual ~MediaWindow();
};

