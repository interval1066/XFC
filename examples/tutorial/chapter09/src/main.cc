#include <config.h> 
#include <xfc/main.hh>
#include <xfc/i18n.hh>
#include "xfcapp.hh"

int main (int argc, char *argv[])
{
	using namespace Main;

	i18n::set_text_domain_dir(PACKAGE, LOCALEDIR);
	i18n::set_text_domain(PACKAGE);
	
	init(&argc, &argv);

	XfcApp window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

