/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

//! @file inti/gtk-sourceview/sourceprintjob.h
//! @brief A GtkSourcePrintJob C++ wrapper interface.
//!
//! Provides SourcePrintJob, an object which knows how to print a Gtk::SourceBuffer with highlighting.

#ifndef XFC_GTK_SOURCE_PRINT_JOB_HH
#define XFC_GTK_SOURCE_PRINT_JOB_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_SOURCE_PRINT_JOB_H__
#include <gtksourceview/gtksourceprintjob.h>
#endif

namespace Xfc {

namespace Gtk {

class SourceBuffer;
class SourceView;
class TextIter;

//! @class SourcePrintJob sourceprintjob.h inti/gtk-sourceview/sourceprintjob.h
//! @brief A GtkSourcePrintJob C++ wrapper class.
//!
//! The SourcePrintJob object is used to print the contents of a SourceBuffer.
//! You can set various configuration options to customize the printed output,
//! and the result is obtained as a GnomePrintJob object, which you can then
//! preview with gnome_print_job_preview_new() or print directly with
//! gnome_print_job_print().
//!
//! The easiest way to construct a new print job is from a SourceView. In this
//! case the print job's buffer, tabs width, highlight, wrap mode, and font will
//! be set to the values currently set in the source view. Other constructors
//! take a SourceBuffer, a GnomePrintConfig object or both. If a GnomePrintConfig
//! is not specified the print job will use the default gnome print configuration.
//! If no font is set the print job will use the default font: 'Monospace Regular 10'.
//!
//! Printing can be done synchronously and asynchronously. Asynchronous methods
//! are provided so you can give the user feedback about what's going on when
//! printing long documents (see the "begin_page" and "finished" signals).
//!
//! The task of a SourcePrintJob is to produce a GnomePrintJob. What this means
//! is that once you get the resulting GnomePrintJob, you might reuse the
//! SourcePrintJob to produce another output (with different configuration
//! options for example) or just unreference it and forget about it. The lifetime
//! of the produced object is independent of that of the producer.
//!
//! Before printing you should at least set the SourceBuffer you want to print
//! (using set_buffer()). Besides that, you might configure word wrapping, font,
//! whether to print hightlighted text as seen in the SourceView, line numbers,
//! basic headers and footers.
//!
//! SourcePrintJob can print basic headers and footers in each page. You can
//! specify strftime() like strings for text on the left, right and center of
//! the top and bottom of the page. You can also make SourcePrintJob draw a
//! separator line between the text document and the header and footer. And
//! you can specify a different font (from that used for the text document).
//!
//! Customization beyond that is possible, but you have to do the printing
//! manually. To do that, you need to connect to the "begin_page" signal of
//! the job and allocate some space in the page using set_text_margins().
//! Whenever SourcePrintJob is about to print a new text page, the signal
//! will be emitted. You can then get the GnomePrintContext being used with
//! get_print_context() and use Gnome Print functions directly. The space
//! you allocate is inside the document margins defined in the specified
//! GnomePrintConfig, but outside all print area used by SourcePrintJob itself.
//!
//! <B>Example:</B> A quick bootstrap code sequence to get you started using SourcePrintJob:
//! @code
//! GnomePrintJob *
//! print_source_buffer_from_view(Gtk::SourceView& view, const String& title)
//! {
//! 	// Create a job using the default print configuration and setup the buffer,
//! 	// font and wrapping with those values set in the source view.
//! 	Pointer<Gtk::SourcePrintJob> job = new Gtk::SourcePrintJob(*view);
//!
//! 	// Print line numbers every 5 lines, using the default font.
//! 	job->set_print_numbers(5);
//!
//! 	// Print a header with the title centered.
//! 	job->set_header_footer_font("Sans Regular 12.0");
//! 	job->set_header_format(0, title, 0, true);
//! 	job->set_print_header(true);
//!
//! 	// Print the page number in the page bottom.
//! 	job->set_footer_format(0, 0, "Page N of Q", true);
//! 	job->set_print_footer(true);
//!
//! 	// Print the whole buffer and return the result (that is, a GnomePrintJob pointer).
//! 	return job->print();
//! }
//! @endcode

class SourcePrintJob : public G::Object
{
	friend class G::Object;

	SourcePrintJob(const SourcePrintJob&);
	SourcePrintJob& operator=(const SourcePrintJob&);

protected:
//! @name Constructors
//! @{

	explicit SourcePrintJob(GtkSourcePrintJob *job, bool reference = false);
	//!< Construct a new SourcePrintJob from an existing GtkSourcePrintJob.
	//!< @param job A pointer to a GtkSourcePrintJob.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>job</EM> can be a newly created GtkSourcePrintJob or an existing
	//!< GtkSourcePrintJob (see G::Object::Object).

//! @}
//  Properties

	typedef G::Property<GnomePrintConfig*, void*> ConfigPropertyType;
	typedef G::PropertyProxy<G::Object, ConfigPropertyType> ConfigPropertyProxy;
	static const ConfigPropertyType config_property;

	typedef G::Property<SourceBuffer*, G::Object*> BufferPropertyType;
	typedef G::PropertyProxy<G::Object, BufferPropertyType> BufferPropertyProxy;
	static const BufferPropertyType buffer_property;

	typedef G::Property<unsigned int> TabsWidthPropertyType;
	typedef G::PropertyProxy<G::Object, TabsWidthPropertyType> TabsWidthPropertyProxy;
	static const TabsWidthPropertyType tabs_width_property;

	typedef G::Property<WrapMode, int> WrapModePropertyType;
	typedef G::PropertyProxy<G::Object, WrapModePropertyType> WrapModePropertyProxy;
	static const WrapModePropertyType wrap_mode_property;

	typedef G::Property<bool> HighlightPropertyType;
	typedef G::PropertyProxy<G::Object, HighlightPropertyType> HighlightPropertyProxy;
	static const HighlightPropertyType highlight_property;

 	typedef G::Property<String> FontPropertyType;
	typedef G::PropertyProxy<G::Object, FontPropertyType> FontPropertyProxy;
	static const FontPropertyType font_property;

	typedef G::Property<String> NumbersFontPropertyType;
	typedef G::PropertyProxy<G::Object, NumbersFontPropertyType> NumbersFontPropertyProxy;
	static const NumbersFontPropertyType numbers_font_property;

	typedef G::Property<unsigned int> PrintNumbersPropertyType;
	typedef G::PropertyProxy<G::Object, PrintNumbersPropertyType> PrintNumbersPropertyProxy;
	static const PrintNumbersPropertyType print_numbers_property;

	typedef G::Property<bool> PrintHeaderPropertyType;
	typedef G::PropertyProxy<G::Object, PrintHeaderPropertyType> PrintHeaderPropertyProxy;
	static const PrintHeaderPropertyType print_header_property;

	typedef G::Property<bool> PrintFooterPropertyType;
	typedef G::PropertyProxy<G::Object, PrintFooterPropertyType> PrintFooterPropertyProxy;
	static const PrintFooterPropertyType print_footer_property;

	typedef G::Property<String> HeaderFooterFontPropertyType;
	typedef G::PropertyProxy<G::Object, HeaderFooterFontPropertyType> HeaderFooterFontPropertyProxy;
	static const HeaderFooterFontPropertyType header_footer_font_property;

//  Signals

	typedef G::Signal0<void> BeginPageSignalType;
	typedef G::SignalProxy<TypeInstance, BeginPageSignalType> BeginPageSignalProxy;
	static const BeginPageSignalType begin_page_signal;

	typedef G::Signal0<void> FinishedSignalType;
	typedef G::SignalProxy<TypeInstance, FinishedSignalType> FinishedSignalProxy;
	static const FinishedSignalType finished_signal;

public:
//! @name Constructors
//! @{

	explicit SourcePrintJob(SourceBuffer *buffer = 0);
	//!< Constructs a new source print job.
	//!< @param buffer The SourceBuffer to print, or null.
	//!<
	//!< <BR>If no GnomePrintConfig is set by calling set_config() the print job
	//!< will use the default gnome print configuration.

	explicit SourcePrintJob(GnomePrintConfig& config, SourceBuffer *buffer = 0);
	//!< Constructs a new source print job with the specified configuration.
	//!< @param config The print job options.
	//!< @param buffer The SourceBuffer to print, or null.

	explicit SourcePrintJob(SourceView& view);
	//!< Convenience constructor that sets several configuration options at once, so that the
	//!< printed output matches the view.
	//!< @param view The SourceView to get the configuration from.
	//!<
	//!< <BR>The configuration options set are the buffer, tabs width, highlighting,
	//!< wrap mode and default font. This is the easiest way to set up a print job.
	//!< If no configuration is set later the default GnomePrintConfig is used.

	virtual ~SourcePrintJob();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourcePrintJob* gtk_source_print_job() const { return reinterpret_cast<GtkSourcePrintJob*>(instance_); }
	//!< Get a pointer to the GtkSourcePrintJob structure.

	operator GtkSourcePrintJob* () const;
	//!< Conversion operator; safely converts a SourcePrintJob to a GtkSourcePrintJob pointer.

	bool is_gtk_source_print_job() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_PRINT_JOB.

	GnomePrintConfig* get_config() const;
	//!< Gets the current GnomePrintConfig the print job will use.
	//!< @return  A pointer to the GnomePrintConfig for the print job.
	//!<
	//!< <BR>If not previously set, this will create a default configuration and return it.

	SourceBuffer* get_buffer() const;
	//!< Gets the SourceBuffer the print job would print.
	//!< @return The SourceBuffer to print.

	unsigned int get_tabs_width() const;
	//!< Gets the configured tabs width in equivalent spaces (the default value is 8).
	//!< @return The tabs width in equivalent spaces.

	WrapMode get_wrap_mode() const;
	//!< Gets the wrapping style for text lines wider than the printable width.
	//!< @return The current wrapping mode for the print job.
	//!<
	//!< <BR>The default is no wrapping.

	bool get_highlight() const;
	//!< Gets whether the job is configured to print the text highlighted with
	//!< colors and font styles.
	//!< @return <EM>true</EM> if the printed output will be highlighted.
	//!<
	//!< <BR>Note that highlighting will happen only if the buffer to print has highlighting activated.

	String get_font() const;
	//!< Gets the default font to be used for the printed text.
	//!< @return A String with the name of the current text font.
	//!<
	//!< <BR>The returned string is of the form "Fontfamily Style Size", for example
	//!< "Monospace Regular 10.0".

	String get_numbers_font() const;
	//!< Gets the font to be used for the line numbers.
	//!< @return A String with the name of the current line numbers font, or null.
	//!<
	//!< <BR>The returned string is of the form "Fontfamily Style Size", for example
	//!< "Monospace Regular 10.0". This function might return a null String if a
	//!< specific font for line numbers has not been set.

	unsigned int get_print_numbers() const;
	//!< Obtains the interval used for line number printing.
	//!< @return The interval of printed line numbers.
	//!<
	//!< <BR>If the return value is 0, no line numbers will be printed. The default
	//!< value is 1 (that is, line numbers are printed on all lines).

	void get_text_margins(double *top, double *bottom, double *left, double *right) const;
	//!< Gets the user set margins for the print job.
	//!< @param top The location to store the top margin.
	//!< @param bottom The location to store the bottom margin.
	//!< @param left The location to store the left margin.
	//!< @param right The location to store the right margin.
	//!<
	//!< <BR>This function retrieves the values previously set by set_text_margins().
	//!< The default for all four margins is 0. Any of the pointers can be null if
	//!< you want to ignore that value.

	GnomePrintJob* get_print_job() const;
	//!< Gets a reference to the GnomePrintJob which the job is printing
	//!< or has recently finished printing.
	//!< @return A new reference to the job's GnomePrintJob, or null.
	//!<
	//!< <BR>Note you need to unref the returned object. You may call this
	//!< method in the middle of an asynchronous printing operation, but the
	//!< returned GnomePrintJob will not be closed until the last page is
	//!< printed and the "finished" signal is emitted.

	unsigned int get_page() const;
	//!< Gets the currently printing page number.
	//!< @return The current page number.
	//!<
	//!< <BR>This method is only valid while printing (either synchronously or asynchronously).

	unsigned int get_page_count() const;
	//!< Obtains the total number of pages the job will print.
	//!< @return The number of pages of the printed job.
	//!<
	//!< <BR>The returned value is only meaninful after pagination has finished.
	//!< In practice, for synchronous printing this means when "begin_page" is
	//!< emitted, or after print_async() has returned.

	GnomePrintContext* get_print_context() const;
	//!< Gets the GnomePrintContext of the current job.
	//!< @return The current GnomePrintContext
	//!<
	//!< <BR>This method is only valid while printing. Normally you would use this
	//!< method to print in the margins set by set_margins() in a handler for the
	//!< "begin_page" signal. The returned object is owned by job.

	bool get_print_header() const;
	//!< Determines if a header is set to be printed for each page.
	//!< @return <EM>true</EM> if the header is set to be printed.
	//!<
	//!< <BR>A header will be printed if this method returns true and some format
	//!< strings have been specified with set_header_format().

 	bool get_print_footer() const;
	//!< Determines if a footer is set to be printed for each page.
	//!< @return <EM>true</EM> if the footer is set to be printed.
	//!<
	//!< <BR>A footer will be printed if this method returns true and some format
	//!< strings have been specified with set_footer_format().

	String get_header_footer_font() const;
	//!< Gets the font to be used for the header and footer.
	//!< @return A String with the name of the current header and footer font, or null.
	//!<
	//!< <BR>The returned string is of the form "Fontfamily Style Size", for example
	//!< "Monospace Regular 10.0". This method might return null if a specific font
	//!< has not been set.

//! @}
//! @name Methods
//! @{

	void set_config(GnomePrintConfig& config);
	//!< Sets the print configuration for the job.
	//!< @param config A GnomePrintConfig object to get printing configuration from.
	//!<
	//!< <BR>If you don't set a configuration object for the print job,
	//!< when needed one will be created with gnome_print_config_default().

	void set_buffer(SourceBuffer& buffer);
	//!< Sets the SourceBuffer the print job will print.
	//!< @param buffer The SourceBuffer to print.
	//!<
	//!< <BR>You need to specify a buffer to print, either by using this method
	//!< or by specifying a buffer when you construct the print job.

	void set_tabs_width(unsigned int tabs_width);
	//!< Sets the tabs width (in equivalent spaces) for the printed text.
	//!< @param tabs_width The number of equivalent spaces for the tabs width.
	//!<
	//!< <BR>The width in printing units will be calculated as the width of a string
	//!< containing tabs_width spaces of the default font. Tab stops are set for the
	//!< full width of printed text.

	void set_wrap_mode(WrapMode wrap);
	//!< Sets the wrap mode for lines of text larger than the printable width.
	//!< @param wrap A WrapMode.

	void set_highlight(bool highlight);
	//!< Sets whether the printed text will be highlighted according to the buffer rules.
	//!< @param highlight Set <EM>true</EM> if the printed text should be highlighted.
	//!<
	//!< <BR>If <EM>highlight</EM> is true both color and font style are applied.

	void set_font(const String& font_name);
	//!< Sets the default font for the printed text.
	//!< @param font_name The name of the font used for the document text.
	//!<
	//!< <BR>The <EM>font_name</EM> should be a full font name GnomePrint can understand.
	//!< The default font name is "Monospace Regular 10";

	void set_numbers_font(const String& font_name);
	//!< Sets the font for printing line numbers on the left margin.
	//!< @param font_name The full name of the font for line numbers, or null.
	//!<
	//!< <BR>If a null String is supplied, the default font (that is,
	//!< the one being used for the text) will be used instead.

	void set_print_numbers(unsigned int interval);
	//!< Sets the interval for printed line numbers.
	//!< @param interval The interval for printed line numbers.
	//!<
	//!< <BR>If <EM>interval</EM> is 0 no numbers will be printed. If greater than 0,
	//!< a number will be printed every <EM>interval</EM> lines (that is, 1 will print
	//!< a number on every line, 2 will print a number on every second line, 3 will
	//!< print a number on every third line, and so on).

	void set_text_margins(double top, double bottom, double left, double right);
	//!< Sets the four user margins for the print job.
	//!< @param top The top user margin.
	//!< @param bottom The bottom user margin.
	//!< @param left The left user margin.
	//!< @param right The right user margin.
	//!<
	//!< <BR>These margins are in addition to the document margins provided in the
	//!< GnomePrintConfig and will not be used for headers, footers or line numbers
	//!< (those are calculated separatedly). You can print in the space allocated by
	//!< these margins by connecting to the "begin_page" signal. The space is around
	//!< the printed text, and inside the margins specified in the GnomePrintConfig.
	//!<
	//!< The margin numbers are given in device units. If any of the given values is
	//!< less than 0, that particular margin is not altered by this function.

	GnomePrintJob* print();
	//!< Produces a GnomePrintJob with the printed document.
	//!< @return A closed GnomePrintJob with the printed document, or null if printing could not be completed.
	//!<
	//!< <BR>The whole contents of the configured SourceBuffer are printed. The returned job
	//!< is already closed and ready to be previewed (using gnome_print_job_preview_new())
	//!< or printed directly. The caller of this method owns a reference to the returned
	//!< object, so job can be destroyed and the output will still be valid, or the document
	//!< can be printed again with different settings.

	GnomePrintJob* print(const TextIter& start, const TextIter& end);
	//!< Produces a GnomePrintJob with the source buffer range from <EM>start</EM> to <EM>end</EM>.
	//!< @param start The start of the region of text to print.
	//!< @param end The end of the region of text to print.
	//!< @return A closed GnomePrintJob with the text from start to end printed,
	//!< or null if job could not print.
	//!<
	//!< <BR>The returned GnomePrintJob pointer is referenced and so must be
	//!< unreferenced when no longer required.

	bool print_async(const TextIter& start, const TextIter& end);
	//!< Starts to print the job asynchronously.
	//!< @param start The start of the region of text to print.
	//!< @param end The end of the region of text to print.
	//!< @return <EM>true</EM> if the print started.
	//!<
	//!< <BR>This method will ready the job for printing and install an idle handler
	//!< that will render one page at a time. This method will not return immediatly,
	//!< as only page rendering is done asynchronously. Text retrieval and paginating
	//!< happens within this method. Also, if highlighting is enabled, the whole
	//!< buffer needs to be highlighted first. To get notification when the job has
	//!< finished, you must connect to the "finished" signal. After this signal is
	//!< emitted you can retrieve the resulting GnomePrintJob with get_print_job().
	//!< You may cancel the job with cancel().

	void cancel();
	//!< Cancels an asynchronous printing operation.
	//!<
	//!< <BR>This will remove any pending print idle handler and unref
	//!< the current GnomePrintJob. Note that if you got a reference to the job's
	//!< GnomePrintJob (using get_print_job()) it will not be destroyed (since you
	//!< hold a reference to it), and it will not be closed either. If you wish to
	//!< show or print the partially printed document you need to close it yourself.
	//!< This method has no effect when called from a non-asynchronous print operation.

	void set_print_header(bool setting);
	//!< Sets whether you want to print a header in each page.
	//!< @param setting Set <EM>true</EM> if you want the header to be printed.
	//!<
	//!< <BR>The default header consists of three pieces of text and an optional
	//!< line separator, configurable with set_header_format(). Note that by
	//!< default the header format is unspecified, and if it's empty it will not
	//!< be printed, regardless of this setting.

	void set_print_footer(bool setting);
	//!< Sets whether you want to print a footer in each page.
	//!< @param setting Set <EM>true</EM> if you want the footer to be printed.
	//!<
	//!< <BR>The default footer consists of three pieces of text and an optional
	//!< line separator, configurable with set_footer_format(). Note that by
	//!< default the footer format is unspecified, and if it's empty it will not
	//!< be printed, regardless of this setting.

	void set_header_footer_font(const String& font_name);
	//!< Sets the font for printing headers and footers.
	//!< @param font_name The full name of the font to be used in headers and footers, or null.
	//!<
	//!< <BR>If a null String is supplied, the default font (that is, the one
	//!< being used for the text) will be used instead. The default font name
	//!< is 'Monospace Regular 10';

	void set_header_format(const char *left, const char *center, const char *right, bool separator);
	void set_header_format(const String& left, const String& center, const String& right, bool separator);
	//!< Sets strftime-like header format strings, to be printed on the left,
	//!< center and right of the top of each page.
	//!< @param left A format string to print on the left of the header.
	//!< @param center A format string to print on the center of the header.
	//!< @param right A format string to print on the right of the header.
	//!< @param separator Set <EM>true</EM> if you want a separator line to be printed.
	//!<
	//!< <BR>The strings may include strftime(3) codes which will be expanded
	//!< at print time. All strftime() codes are accepted (A for the day, F
	//!< for the date, T for the time), with the addition of N for the page
	//!< number and Q for the total page count. <EM>separator</EM> specifies
	//!< if a solid line should be drawn to separate the header from the
	//!< document text. If a null String is given for any of the three
	//!< arguments, that particular string will not be printed. For the header
	//!< to be printed, in addition to specifying format strings, you need to
	//!< enable header printing with set_print_header().

	void set_footer_format(const char *left, const char *center, const char *right, bool separator);
	void set_footer_format(const String& left, const String& center, const String& right, bool separator);
	//!< Sets strftime-like footer format strings, to be printed on the left,
	//!< center and right of the bottom of each page (see set_header_format()).
	//!< @param left A format string to print on the left of the footer.
	//!< @param center A format string to print on the center of the footer.
	//!< @param right A format string to print on the right of the footer.
	//!< @param separator Set <EM>true</EM> if you want a separator line to be printed.

//! @}
//! @name Property Proxies
//! @{

	const ConfigPropertyProxy property_config()
	{
		return ConfigPropertyProxy(this, &config_property);
	}
	//!< The Configuration options for the print job (GnomePrintConfig* : Read / Write).

	const BufferPropertyProxy property_buffer()
	{
		return BufferPropertyProxy(this, &buffer_property);
	}
	//!< The Gtk::SourceBuffer object to print (Gtk::SourceBuffer* : Read / Write).

	const TabsWidthPropertyProxy property_tabs_width()
	{
		return TabsWidthPropertyProxy(this, &tabs_width_property);
	}
	//!< The width in equivalent space characters of tabs (unsigned int : Read / Write).

	const WrapModePropertyProxy property_wrap_mode()
	{
		return WrapModePropertyProxy(this, &wrap_mode_property);
	}
	//!< The word wrapping mode (WrapMode : Read / Write).

	const HighlightPropertyProxy property_highlight()
	{
		return HighlightPropertyProxy(this, &highlight_property);
	}
	//!< Whether to print the document with highlighted syntax (bool : Read / Write).

	const FontPropertyProxy property_font()
	{
		return FontPropertyProxy(this, &font_property);
	}
	//!< The Font name to use for the document text (String : Read / Write).

	const NumbersFontPropertyProxy property_numbers_font()
	{
		return NumbersFontPropertyProxy(this, &numbers_font_property);
	}
	//!< The Font name to use for the line numbers (String : Read / Write).

	const PrintNumbersPropertyProxy property_print_numbers()
	{
		return PrintNumbersPropertyProxy(this, &print_numbers_property);
	}
	//!< The Interval of printed line numbers (0 means no numbers) (unsigned int : Read / Write).

	const PrintHeaderPropertyProxy property_print_header()
	{
		return PrintHeaderPropertyProxy(this, &print_header_property);
	}
	//!< Whether to print a header in each page (bool : Read / Write).

	const PrintFooterPropertyProxy property_print_footer()
	{
		return PrintFooterPropertyProxy(this, &print_footer_property);
	}
	//!< Whether to print a footer in each page (bool : Read / Write).

	const HeaderFooterFontPropertyProxy property_header_footer_font()
	{
		return HeaderFooterFontPropertyProxy(this, &header_footer_font_property);
	}
	//!< The font name to use for the header and footer (String : Read / Write).

//! @}
//! @name Signal Proxies
//! @{

	const BeginPageSignalProxy sig_begin_page()
	{
		return BeginPageSignalProxy(this, &begin_page_signal);
	}
	//!< Connect to the begin_page_signal; emitted whenever the print job is about to print a new text page.

	const FinishedSignalProxy sig_finished()
	{
		return FinishedSignalProxy(this, &finished_signal);
	}
	//!< Connect to the finished_signal; emitted whenever an asynchronous print job has finished.

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_PRINT_JOB_H


