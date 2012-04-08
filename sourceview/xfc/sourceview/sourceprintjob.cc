/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourceprintjob.cc - An object which knows how to print a Gtk::SourceBuffer with highlighting.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "sourceprintjob.hh"
#include "sourceprintjobsignals.hh"
#include "private/sourceprintjobclass.hh"
#include "sourcebuffer.hh"
#include "sourceview.hh"

#include <xfc/gtk/private/marshal.hh>

using namespace Xfc;

/*  Gtk::SourcePrintJob
 */

Gtk::SourcePrintJob::SourcePrintJob(GtkSourcePrintJob *job, bool reference)
: G::Object((GObject*)job, reference)
{
}

Gtk::SourcePrintJob::SourcePrintJob(SourceBuffer *buffer)
: G::Object((GObject*)SourcePrintJobClass::create())
{
	if (buffer)
		set_buffer(*buffer);
}

Gtk::SourcePrintJob::SourcePrintJob(GnomePrintConfig& config, SourceBuffer *buffer)
: G::Object((GObject*)SourcePrintJobClass::create())
{
	set_config(config);
	if (buffer)
		set_buffer(*buffer);
}

Gtk::SourcePrintJob::SourcePrintJob(SourceView& view)
: G::Object((GObject*)SourcePrintJobClass::create())
{
	gtk_source_print_job_setup_from_view(gtk_source_print_job(), view.gtk_source_view());
}

Gtk::SourcePrintJob::~SourcePrintJob()
{
}

Gtk::SourcePrintJob::operator GtkSourcePrintJob* () const
{
	return this ? gtk_source_print_job() : 0;
}

bool
Gtk::SourcePrintJob::is_gtk_source_print_job() const
{
	return is_a(GTK_TYPE_SOURCE_PRINT_JOB);
}

GnomePrintConfig*
Gtk::SourcePrintJob::get_config() const
{
	return gtk_source_print_job_get_config(gtk_source_print_job());
}

Gtk::SourceBuffer*
Gtk::SourcePrintJob::get_buffer() const
{
	return G::Object::wrap<Gtk::SourceBuffer>(gtk_source_print_job_get_buffer(gtk_source_print_job()));
}

unsigned int
Gtk::SourcePrintJob::get_tabs_width() const
{
	return gtk_source_print_job_get_tabs_width(gtk_source_print_job());
}

Gtk::WrapMode
Gtk::SourcePrintJob::get_wrap_mode() const
{
	return (WrapMode)gtk_source_print_job_get_wrap_mode(gtk_source_print_job());
}

bool
Gtk::SourcePrintJob::get_highlight() const
{
	return gtk_source_print_job_get_highlight(gtk_source_print_job());
}

String
Gtk::SourcePrintJob::get_font() const
{
	return gtk_source_print_job_get_font(gtk_source_print_job());
}

String
Gtk::SourcePrintJob::get_numbers_font() const
{
	return gtk_source_print_job_get_numbers_font(gtk_source_print_job());
}

unsigned int
Gtk::SourcePrintJob::get_print_numbers() const
{
	return gtk_source_print_job_get_print_numbers(gtk_source_print_job());
}

void
Gtk::SourcePrintJob::get_text_margins(double *top, double *bottom, double *left, double *right) const
{
	gtk_source_print_job_get_text_margins(gtk_source_print_job(), top, bottom, left, right);
}

GnomePrintJob*
Gtk::SourcePrintJob::get_print_job() const
{
	return gtk_source_print_job_get_print_job(gtk_source_print_job());
}

unsigned int
Gtk::SourcePrintJob::get_page() const
{
	return gtk_source_print_job_get_page(gtk_source_print_job());
}

unsigned int
Gtk::SourcePrintJob::get_page_count() const
{
	return gtk_source_print_job_get_page_count(gtk_source_print_job());
}

GnomePrintContext*
Gtk::SourcePrintJob::get_print_context() const
{
	return gtk_source_print_job_get_print_context(gtk_source_print_job());
}

bool
Gtk::SourcePrintJob::get_print_header() const
{
	return gtk_source_print_job_get_print_header(gtk_source_print_job());
}

bool
Gtk::SourcePrintJob::get_print_footer() const
{
	return gtk_source_print_job_get_print_footer(gtk_source_print_job());
}

String
Gtk::SourcePrintJob::get_header_footer_font() const
{
	return gtk_source_print_job_get_header_footer_font(gtk_source_print_job());
}

void
Gtk::SourcePrintJob::set_config(GnomePrintConfig& config)
{
	gtk_source_print_job_set_config(gtk_source_print_job(), &config);
}

void
Gtk::SourcePrintJob::set_buffer(SourceBuffer& buffer)
{
	gtk_source_print_job_set_buffer(gtk_source_print_job(), buffer.gtk_source_buffer());
}

void
Gtk::SourcePrintJob::set_tabs_width(unsigned int tabs_width)
{
	gtk_source_print_job_set_tabs_width(gtk_source_print_job(), tabs_width);
}

void
Gtk::SourcePrintJob::set_wrap_mode(WrapMode wrap)
{
	gtk_source_print_job_set_wrap_mode(gtk_source_print_job(), (GtkWrapMode)wrap);
}

void
Gtk::SourcePrintJob::set_highlight(bool highlight)
{
	gtk_source_print_job_set_highlight(gtk_source_print_job(), highlight);
}

void
Gtk::SourcePrintJob::set_font(const String& font_name)
{
	gtk_source_print_job_set_font(gtk_source_print_job(), font_name.c_str());
}

void
Gtk::SourcePrintJob::set_numbers_font(const String& font_name)
{
	gtk_source_print_job_set_numbers_font(gtk_source_print_job(), font_name.c_str());
}

void
Gtk::SourcePrintJob::set_print_numbers(unsigned int interval)
{
	gtk_source_print_job_set_print_numbers(gtk_source_print_job(), interval);
}

void
Gtk::SourcePrintJob::set_text_margins(double top, double bottom, double left, double right)
{
	gtk_source_print_job_set_text_margins(gtk_source_print_job(), top, bottom, left, right);
}

GnomePrintJob*
Gtk::SourcePrintJob::print()
{
	return gtk_source_print_job_print(gtk_source_print_job());
}

GnomePrintJob*
Gtk::SourcePrintJob::print(const TextIter& start, const TextIter& end)
{
	return gtk_source_print_job_print_range(gtk_source_print_job(), start.gtk_text_iter(), end.gtk_text_iter());
}

bool
Gtk::SourcePrintJob::print_async(const TextIter& start, const TextIter& end)
{
	return gtk_source_print_job_print_range_async(gtk_source_print_job(), start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::SourcePrintJob::cancel()
{
	gtk_source_print_job_cancel(gtk_source_print_job());
}

void
Gtk::SourcePrintJob::set_print_header(bool setting)
{
	gtk_source_print_job_set_print_header(gtk_source_print_job(), setting);
}

void
Gtk::SourcePrintJob::set_print_footer(bool setting)
{
	gtk_source_print_job_set_print_footer(gtk_source_print_job(), setting);
}

void
Gtk::SourcePrintJob::set_header_footer_font(const String& font_name)
{
	gtk_source_print_job_set_header_footer_font(gtk_source_print_job(), font_name.c_str());
}

void
Gtk::SourcePrintJob::set_header_format(const char *left, const char *center, const char *right, bool separator)
{
	gtk_source_print_job_set_header_format(gtk_source_print_job(), left, center, right, separator);
}

void
Gtk::SourcePrintJob::set_header_format(const String& left, const String& center, const String& right, bool separator)
{
	gtk_source_print_job_set_header_format(gtk_source_print_job(), left.c_str(), center.c_str(), right.c_str(), separator);
}

void
Gtk::SourcePrintJob::set_footer_format(const char *left, const char *center, const char *right, bool separator)
{
	gtk_source_print_job_set_footer_format(gtk_source_print_job(), left, center, right, separator);
}

void
Gtk::SourcePrintJob::set_footer_format(const String& left, const String& center, const String& right, bool separator)
{
	gtk_source_print_job_set_footer_format(gtk_source_print_job(), left.c_str(), center.c_str(), right.c_str(), separator);
}

/*  Gtk::SourcePrintJobClass
 */

void
Gtk::SourcePrintJobClass::init(GtkSourcePrintJobClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->begin_page = &begin_page_proxy;
	g_class->finished = &finished_proxy;
}

GType
Gtk::SourcePrintJobClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_PRINT_JOB, (GClassInitFunc)init);
	}
	return type;
}

void*
Gtk::SourcePrintJobClass::create()
{
	return g_object_new(get_type(), 0);
}

GtkSourcePrintJobClass*
Gtk::SourcePrintJobClass::get_parent_class(void *instance)
{
        return static_cast<GtkSourcePrintJobClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

void
Gtk::SourcePrintJobClass::begin_page_proxy(GtkSourcePrintJob *job)
{
    void *ptr = g_object_get_qdata((GObject*)job, G::ObjectSignals::quark());
	if(ptr)
		static_cast<SourcePrintJobSignals *>(ptr)->on_begin_page();
	else
	{
        GtkSourcePrintJobClass *g_class = get_parent_class(job);
		if (g_class->begin_page)
			g_class->begin_page(job);
	}
}

void
Gtk::SourcePrintJobClass::finished_proxy(GtkSourcePrintJob *job)
{
    void *ptr = g_object_get_qdata((GObject*)job, G::ObjectSignals::quark());
	if (ptr)
		static_cast<SourcePrintJobSignals *>(ptr)->on_finished();
	else
	{
        GtkSourcePrintJobClass *g_class = get_parent_class(job);
		if (g_class->finished)
			g_class->finished(job);
	}
}

/*  Gtk::SourcePrintJob properties
 */

const Gtk::SourcePrintJob::ConfigPropertyType Gtk::SourcePrintJob::config_property("config");

const Gtk::SourcePrintJob::BufferPropertyType Gtk::SourcePrintJob::buffer_property("buffer");

const Gtk::SourcePrintJob::TabsWidthPropertyType Gtk::SourcePrintJob::tabs_width_property("tabs_width");

const Gtk::SourcePrintJob::WrapModePropertyType Gtk::SourcePrintJob::wrap_mode_property("wrap_mode");

const Gtk::SourcePrintJob::HighlightPropertyType Gtk::SourcePrintJob::highlight_property("highlight");

const Gtk::SourcePrintJob::FontPropertyType Gtk::SourcePrintJob::font_property("font");

const Gtk::SourcePrintJob::NumbersFontPropertyType Gtk::SourcePrintJob::numbers_font_property("numbers_font");

const Gtk::SourcePrintJob::PrintNumbersPropertyType Gtk::SourcePrintJob::print_numbers_property("print_numbers");

const Gtk::SourcePrintJob::PrintHeaderPropertyType Gtk::SourcePrintJob::print_header_property("print_header");

const Gtk::SourcePrintJob::PrintFooterPropertyType Gtk::SourcePrintJob::print_footer_property("print_footer");

const Gtk::SourcePrintJob::HeaderFooterFontPropertyType Gtk::SourcePrintJob::header_footer_font_property("header_footer_font");

/*  Gtk::SourceBuffer signals
 */

const Gtk::SourcePrintJob::BeginPageSignalType Gtk::SourcePrintJob::begin_page_signal("begin_page",(GCallback)&G::Marshal::void_callback);

const Gtk::SourcePrintJob::FinishedSignalType Gtk::SourcePrintJob::finished_signal("finished", (GCallback)&G::Marshal::void_callback);

