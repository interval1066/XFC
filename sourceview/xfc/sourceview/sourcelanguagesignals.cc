#include "sourcelanguage.hh"
#include "sourcelanguagesignals.hh"
#include "private/sourcelanguageclass.hh"

using namespace Xfc;

/*  Gtk::SourceLanguage signal hadlers
 */

void
Gtk::SourceLanguageSignals::on_tag_style_changed(const String& name)
{
	GtkSourceLanguageClass *g_class = SourceLanguageClass::get_parent_class(instance_);
	if (g_class->tag_style_changed)
		g_class->tag_style_changed((GtkSourceLanguage*)instance_, name.c_str());
}

