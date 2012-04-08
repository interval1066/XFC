#include "sourceprintjob.hh"
#include "sourceprintjobsignals.hh"
#include "private/sourceprintjobclass.hh"

using namespace Xfc;

/*  Gtk::SourcePrintJob signal handlers
 */

void
Gtk::SourcePrintJobSignals::on_begin_page()
{
	GtkSourcePrintJobClass *g_class = SourcePrintJobClass::get_parent_class(instance_);
	if (g_class->begin_page)
		g_class->begin_page((GtkSourcePrintJob*)instance_);
}

void
Gtk::SourcePrintJobSignals::on_finished()
{
	GtkSourcePrintJobClass *g_class = SourcePrintJobClass::get_parent_class(instance_);
	if (g_class->finished)
		g_class->finished((GtkSourcePrintJob*)instance_);
}

