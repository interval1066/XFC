#include "sourcebuffer.hh"
#include "sourcebuffersignals.hh"
#include "private/sourcebufferclass.hh"

using namespace Xfc;

/*  Gtk::SourceBufferSignals class
 */
Gtk::SourceBufferSignals::SourceBufferSignals(SourceBuffer *buffer) : TextBufferSignals(buffer)
{
}

Gtk::SourceBufferSignals::~SourceBufferSignals()
{
}

void
Gtk::SourceBufferSignals::on_can_undo(bool can_undo)
{
    GtkSourceBufferClass *g_class = SourceBufferClass::get_parent_class(instance_);
	if (g_class->can_undo)
		g_class->can_undo((GtkSourceBuffer*)instance_, can_undo);
}

void
Gtk::SourceBufferSignals::on_can_redo(bool can_redo)
{
	GtkSourceBufferClass *g_class = SourceBufferClass::get_parent_class(instance_);
	if (g_class->can_redo)
		g_class->can_redo((GtkSourceBuffer*)instance_, can_redo);
}

void
Gtk::SourceBufferSignals::on_highlight_updated(TextIter& start, TextIter& end)
{
	GtkSourceBufferClass *g_class = SourceBufferClass::get_parent_class(instance_);
	if (g_class->highlight_updated)
		g_class->highlight_updated((GtkSourceBuffer*)instance_, start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::SourceBufferSignals::on_marker_updated(TextIter& where)
{
	GtkSourceBufferClass *g_class = SourceBufferClass::get_parent_class(instance_);
	if (g_class->marker_updated)
		g_class->marker_updated((GtkSourceBuffer*)instance_, where.gtk_text_iter());
}

