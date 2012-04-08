#include "sourcestylescheme.hh"
#include "sourcestyleschemesignals.hh"
#include "private/sourcestyleschemeclass.hh"

using namespace Xfc;

/*  Overridable GtkSourceStyleScheme methods
 */

const char*
Gtk::SourceStyleSchemeSignals::do_get_name()
{
	const char *result = 0;
	GtkSourceStyleSchemeClass *g_iface = SourceStyleSchemeClass::get_parent_class(instance_);
	if (g_iface->get_name)
		result = g_iface->get_name((GtkSourceStyleScheme*)instance_);

	return result;
}

GtkSourceTagStyle*
Gtk::SourceStyleSchemeSignals::do_get_tag_style(const char *style_name)
{
	GtkSourceTagStyle *result = 0;
	GtkSourceStyleSchemeClass *g_iface = SourceStyleSchemeClass::get_parent_class(instance_);
	if (g_iface->get_tag_style)
		result = g_iface->get_tag_style((GtkSourceStyleScheme*)instance_, style_name);

	return result;
}

GSList*
Gtk::SourceStyleSchemeSignals::do_get_style_names()
{
	GSList *result = 0;
	GtkSourceStyleSchemeClass *g_iface = SourceStyleSchemeClass::get_parent_class(instance_);
	if (g_iface->get_style_names)
		result = g_iface->get_style_names((GtkSourceStyleScheme*)instance_);
	return result;
}

/*  Signal handlers
 */

void
Gtk::SourceStyleSchemeSignals::on_style_changed(const String& tag_id)
{
	GtkSourceStyleSchemeClass *g_iface = SourceStyleSchemeClass::get_parent_class(instance_);
	if (g_iface->style_changed)
		g_iface->style_changed((GtkSourceStyleScheme*)instance_, tag_id.c_str());
}

