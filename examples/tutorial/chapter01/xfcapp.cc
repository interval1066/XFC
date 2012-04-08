#include "xfcapp.hh"

XfcApp::XfcApp()
{
	set_title("XfcApp");
}

XfcApp::~XfcApp()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	XfcApp window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

