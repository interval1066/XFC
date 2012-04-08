/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

/// @file xfc/glib/markup.hh
/// @brief A C++ interface for GMarkupParser and GMarkupParseContext.
///
/// Provides a simple XML Subset Parser that parses a subset of XML.

#ifndef XFC_G_MARKUP_HH
#define XFC_G_MARKUP_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_MARKUP_H__
#include <glib/gmarkup.h>
#endif

#ifndef _CPP_MAP
#include <map>
#endif

namespace Xfc {

namespace G {

class Error;
class MarkupParseContext;
class MarkupParserClass;

/// @class MarkupParser markup.hh xfc/glib/markup.hh
/// A GMarkupParser C++ wrapper interface.
///
/// MarkupParser is an abstract interface class that be can be derived from, or
/// multiplely inherited. It declares five virtual methods that can be overridden.
/// Except for the on_error() method, any of these methods can set an error by
/// calling G::Error::set(); in particular the G_MARKUP_ERROR_UNKNOWN_ELEMENT,
/// G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE, and G_MARKUP_ERROR_INVALID_CONTENT
/// errors are intended to be set from these methods. If you set an error from
/// a virtual method, G::MarkupParseContext::parse() will report that error
/// back to its caller.

class MarkupParser
{
	friend class MarkupParserClass;

	MarkupParser(const MarkupParser&);
	MarkupParser& operator=(const MarkupParser&);

protected:
/// @name Constructors
/// @{

	MarkupParser();
	///< Constructor a new markup parser.

/// @}
/// @name Callback Handlers
/// @{

	virtual void on_start_element(MarkupParseContext& context, const String& element_name,
	                              const std::map<const char*, const char*>& attributes, G::Error& error);
	///< Called when the opening tag of an element is seen.
	///< @param context The MarkupParseContext.
	///< @param element_name The element name.
	///< @param attributes A map of attribute/value pairs.
	///< @param error A reference to a G::Error to set if an error occurs.
	///<
	///< The first value in the attribute map is the attribute name and
	///< the second value is the attribute value. You can retrieve the name
	///< and value of an attribute by doing something like this:
	///< @code
	///< std::map<const char*, const char*>::const_iterator i = attributes.begin();
	///< while (i != attributes.end())
	///< {
	///< 	g_print("The name is %s and the value is %s\n", (*i).first, (*i).second);
	///<	++i;
	///< }
	///< @endcode
	///<
	///< Called for open tags \htmlonly<foo bar="baz">\endhtmlonly.

	virtual void on_end_element(MarkupParseContext& context, const String& element_name, G::Error& error);
	///< Called when the closing tag of an element is seen.
	///< @param context The MarkupParseContext.
	///< @param element_name The element name.
	///< @param error A reference to a G::Error to set if an error occurs.
	///<
	///< Called for close tags \htmlonly</foo>\endhtmlonly.

	virtual void on_text(MarkupParseContext& context, const String text, G::Error& error);
	///< Called when some text is seen (text is always inside an element).
	///< @param context The MarkupParseContext.
	///< @param text The parsed text.
	///< @param error A reference to a G::Error to set if an error occurs.
	///<
	///< Called for character data.

	virtual void on_passthrough(MarkupParseContext& context, const String& passthrough_text, G::Error& error);
	///< Called for comments, processing instructions and doctype declarations; if you're re-writing
	///< the parsed document, write the passthrough text back out in the same position.
	///< @param context The MarkupParseContext.
	///< @param passthrough_text The passthrough text.
	///< @param error A reference to a G::Error to set if an error occurs.
	///<
	///< Called for strings that should be re-saved verbatim in the same
	///< position, but are not otherwise interpretable. At the moment this
	///< includes comments and processing instructions.

	virtual void on_error(MarkupParseContext& context, G::Error& error);
	///< Called when an error occurs.
	///< @param context The MarkupParseContext.
	///< @param error A reference to a G::Error to set if an error occurs.
	///<
	///< Called on error, including ones set by the other virtual methods.

/// @}

public:
/// @name Constructors
/// @{

	virtual ~MarkupParser();
	///< Destructor.

/// @}
};

/// @class MarkupParseContext markup.hh xfc/glib/markup.hh
/// A GMarkupParseContext C++ wrapper interface.
///
/// The markup parser is intended to parse a simple markup format that's a subset of XML.
/// This is a small, efficient, easy-to-use parser. It should not be used if you expect
/// to interoperate with other applications generating full-scale XML. However, it's very
/// useful for application data files, config files, etc. where you know your application
/// will be the only one writing the file. Full-scale XML parsers should be able to parse
/// the subset used by MarkupParseContext, so you can easily migrate to full-scale XML at
/// a later time if the need arises.
///
/// The markup parser is not guaranteed to signal an error on all invalid XML; the parser
/// may accept documents that an XML parser would not. However, invalid XML documents are
/// not considered valid markup documents.
///
/// Simplifications to XML include:
/// - Only UTF-8 encoding is allowed.
/// - No user-defined entities.
/// - Processing instructions, comments and the doctype declaration are "passed through" but are not interpreted in any way.
/// - No DTD or validation.
///
/// The markup format does support:
/// - Elements.
/// - Attributes.
/// - 5 standard entities: &amp; &lt; &gt; &quot; &apos;
/// - Character references.
/// - Sections marked as CDATA.

class MarkupParseContext : public Xfc::Object
{
	MarkupParseContext(const MarkupParseContext&);
	MarkupParseContext& operator=(const MarkupParseContext&);

	GMarkupParseContext *context_;
	bool can_free_;

public:
/// @name Constructors
/// @{

	MarkupParseContext(MarkupParser& parser);
	///< Constructs a new parse context.
	///< @param parser A MarkupParser.
	///<
	///< A parse context is used to parse marked-up documents. You can feed any
	///< number of documents into a context, as long as no errors occur; once an
	///< error occurs, the parse context can't continue to parse text. You have to
	///< delete the parse context and construct a new one. The easiest way to do
	///< this is to use a smart pointer. If an error occurs construct a new parse
	///< context and assign it to the existing smart pointer. The smart pointer will
	///< delete the previous parse context first and then take over the new one.

	MarkupParseContext(GMarkupParseContext *context, bool can_free);
	///< Constructs a new parse context from an existing GMarkupParseContext.
	///< @param context A pointer to a GMarkupParseContext.
	///< @param can_free Set <EM>true</EM> if context should be freed.

	~MarkupParseContext();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GMarkupParseContext* g_markup_parse_context() const;
	///< Get a pointer to the GMarkupParseContext object.

	operator GMarkupParseContext* () const;
	///< Conversion operator; Safely converts a G::MarkupParseContext object into a GMarkupParseContext pointer.

	String get_element() const;
	///< Retrieves the name of the currently open element.
	///< @return The name of the currently open element, or null.

	void get_position(int *line_number, int *char_number) const;
	///< Retrieves the current line number and the number of the character on that line.
	///< @param line_number The return location for a line number, or null;
	///< @param char_number The return location for a char-on-line number, or null;
	///<
	///< Intended for use in error messages; there are no strict semantics
	///< for what constitutes the "current" line number other than "the best
	///< number we could come up with for error messages."

/// @}
/// @name Methods
/// @{

	bool parse(const char *text, int length, G::Error *error);
	///< Feed some data to the MarkupParseContext.
	///< @param text The chunk of text to parse.
	///< @param length The length of <EM>text</EM> in bytes.
	///< @param error The return location for a G::Error.
	///< @return <EM>false</EM> if an error occurred, <EM>true</EM> on success.
	///<
	///< The data need not be valid UTF-8; an error will be signaled if it's invalid.
	///< The data need not be an entire document; you can feed a document into the parser
	///< incrementally, via multiple calls to this function. Typically, as you receive
	///< data from a network connection or file, you feed each received chunk of data into
	///< this function, aborting the process if an error occurs. Once an error is reported,
	///< no further data may be fed to the MarkupParseContext; all errors are fatal.

	bool parse(const String& text, G::Error *error);
	///< Feed some data to the MarkupParseContext.
	///< @param text The chunk of text to parse.
	///< @param error The return location for a G::Error.
	///< @return <EM>false</EM> if an error occurred, <EM>true</EM> on success.
	///<
	///< See parse(const char*, int, G::Error*) for details.

	bool end_parse(G::Error *error);
	///< Signals to the MarkupParseContext that all data has been fed into the parse context with parse().
	///< @param error The return location for a G::Error.
	///< @return <EM>true</EM> on success, <EM>false</EM> if an error was set.
	///<
	///< This method reports an error if the document isn't complete, for example
	///< if elements are still open.

/// @}

	static String escape_text(const char *text, int length);
	///< Escapes text so that the markup parser will parse it verbatim.
	///< @param text Some valid UTF-8 text.
	///< @param length The length of <EM>text</EM> in bytes.
	///< @return A String holding the escaped text.
	///<
	///< Less than, greater than, ampersand, etc. are replaced with the corresponding entities.
	///< This method would typically be used when writing out a file to be parsed with the markup
	///< parser.

	static String escape_text(const String& text);
	///< Escapes text so that the markup parser will parse it verbatim.
	///< @param text Some valid UTF-8 text.
	///< @return A String holding the escaped text.
	///<
	///< Less than, greater than, ampersand, etc. are replaced with the corresponding entities.
	///< This method would typically be used when writing out a file to be parsed with the markup
	///< parser.
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/markup.inl>

#endif // XFC_G_MARKUP_HH

