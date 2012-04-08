#include "sourcetag.hh"
#include "sourcetagsignals.hh"
#include "private/sourcetagclass.hh"

using namespace Xfc;

/*  Gtk::SourceTagTable signal handlers
 */

void
Gtk::SourceTagTableSignals::on_changed()
{
	GtkSourceTagTableClass *g_class = SourceTagTableClass::get_parent_class(instance_);
	if (g_class->changed)
		g_class->changed((GtkSourceTagTable*)instance_);
}
