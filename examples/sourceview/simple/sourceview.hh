/**
   Simple example on how to open an sourceview and to set some text into it
*/

#include <xfc/main.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class SourceViewWindow : public Gtk::Window
{
public:
	SourceViewWindow();
	virtual ~SourceViewWindow();
};

