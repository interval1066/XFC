/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  markup.cc - A C++ interface for GMarkupParser and GMarkupParseContext.
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

#include "markup.hh"
#include "quark.hh"
#include "error.hh"
#include <glib/gmem.h>

namespace Xfc {

namespace G {

/* G::MarkupParserClass
 */

struct MarkupParserClass
{
	static const GMarkupParser parser_object;

	static void start_element_proxy(GMarkupParseContext *context, const gchar *element_name,
	                                const gchar **attribute_names, const gchar **attribute_values,
	                                gpointer user_data, GError  **error);

	static void end_element_proxy(GMarkupParseContext *context, const gchar *element_name,
	                              gpointer user_data, GError **error);

	static void text_proxy(GMarkupParseContext *context, const gchar *text, gsize text_len,
	                       gpointer user_data, GError **error);

	static void passthrough_proxy(GMarkupParseContext *context, const gchar *passthrough_text,
	                              gsize text_len, gpointer user_data, GError **error);

	static void error_proxy(GMarkupParseContext *context, GError *error, gpointer user_data);
};

const GMarkupParser
G::MarkupParserClass::parser_object = {
	&start_element_proxy,
	&end_element_proxy,
	&text_proxy,
	&passthrough_proxy,
	&error_proxy
};

void
MarkupParserClass::start_element_proxy(GMarkupParseContext *context, const gchar *element_name,
                                       const gchar **attribute_names, const gchar **attribute_values,
				       gpointer user_data, GError  **error)
{
	G::MarkupParser *parser = static_cast<G::MarkupParser*>(user_data);
	G::MarkupParseContext tmp_context(context, false);
	String tmp_element_name(element_name);

	int i = 0;
	std::map<const char*, const char*> attributes;
	while (attribute_names[i])
	{
		attributes.insert(std::pair<const char*, const char*>(attribute_names[i], attribute_values[i]));
		++i;
	}

	G::Error tmp_error;
	parser->on_start_element(tmp_context, tmp_element_name, attributes, tmp_error);
	if (tmp_error.get())
		g_set_error(error, tmp_error.domain(), tmp_error.code(), tmp_error.message());
}

void
MarkupParserClass::end_element_proxy(GMarkupParseContext *context, const gchar *element_name,
                                     gpointer user_data, GError **error)
{
	G::MarkupParser *parser = static_cast<G::MarkupParser*>(user_data);
	G::MarkupParseContext tmp_context(context, false);
	String tmp_element_name(element_name);
	G::Error tmp_error;
	parser->on_end_element(tmp_context, tmp_element_name, tmp_error);
	if (tmp_error.get())
		g_set_error(error, tmp_error.domain(), tmp_error.code(), tmp_error.message());
}

void
MarkupParserClass::text_proxy(GMarkupParseContext *context, const gchar *text, gsize text_len,
                              gpointer user_data, GError **error)
{
	G::MarkupParser *parser = static_cast<G::MarkupParser*>(user_data);
	G::MarkupParseContext tmp_context(context, false);
	String tmp_text(text, text_len);
	G::Error tmp_error;
	parser->on_text(tmp_context, tmp_text, tmp_error);
	if (tmp_error.get())
		g_set_error(error, tmp_error.domain(), tmp_error.code(), tmp_error.message());
}

void
MarkupParserClass::passthrough_proxy(GMarkupParseContext *context, const gchar *passthrough_text,
                                     gsize text_len, gpointer user_data, GError **error)
{
	G::MarkupParser *parser = static_cast<G::MarkupParser*>(user_data);
	G::MarkupParseContext tmp_context(context, false);
	String text(passthrough_text, text_len);
	G::Error tmp_error;
	parser->on_passthrough(tmp_context, text, tmp_error);
	if (tmp_error.get())
		g_set_error(error, tmp_error.domain(), tmp_error.code(), tmp_error.message());
}

void
MarkupParserClass::error_proxy(GMarkupParseContext *context, GError *error, gpointer user_data)
{
	G::MarkupParser *parser = static_cast<G::MarkupParser*>(user_data);
	G::MarkupParseContext tmp_context(context, false);
	G::Error tmp_error(error);
	parser->on_error(tmp_context, tmp_error);
}

/*  G::MarkupParser
 */

MarkupParser::MarkupParser()
{
}

MarkupParser::~MarkupParser()
{
}

void
MarkupParser::on_start_element(MarkupParseContext& context, const String& element_name,
                               const std::map<const char*, const char*>& attributes, G::Error& error)
{
}

void
MarkupParser::on_end_element(MarkupParseContext& context, const String& element_name, G::Error& error)
{
}

void
MarkupParser::on_text(MarkupParseContext& context, const String text, G::Error& error)
{
}

void
MarkupParser::on_passthrough(MarkupParseContext& context, const String& passthrough_text, G::Error& error)
{
}

void
MarkupParser::on_error(MarkupParseContext& context, G::Error& error)
{
}

/*  G::MarkupParseContext
 */

MarkupParseContext::MarkupParseContext(MarkupParser& parser)
: context_(g_markup_parse_context_new(&MarkupParserClass::parser_object, (GMarkupParseFlags)0, (void*)&parser, 0)), can_free_(true)
{
}

MarkupParseContext::MarkupParseContext(GMarkupParseContext *context, bool can_free)
: context_(context), can_free_(can_free)
{
}

MarkupParseContext::~MarkupParseContext()
{
	if (context_ && can_free_)
	{
		g_markup_parse_context_free(context_);
		context_ = 0;
	}
}

String
G::MarkupParseContext::get_element() const
{
	return g_markup_parse_context_get_element(context_);
}

bool
MarkupParseContext::parse(const char *text, int length, G::Error *error)
{
	return g_markup_parse_context_parse(context_, text, length, *error);
}

bool
MarkupParseContext::parse(const String& text, G::Error *error)
{
	return g_markup_parse_context_parse(context_, text.c_str(), text.size(), *error);
}

bool
MarkupParseContext::end_parse(G::Error *error)
{
	return g_markup_parse_context_end_parse(context_, *error);
}

String
MarkupParseContext::escape_text(const char *text, int length)
{
	char *tmp_text = g_markup_escape_text(text, length);
	String s(tmp_text);
	g_free(tmp_text);
	return s;
}

String
MarkupParseContext::escape_text(const String& text)
{
	return escape_text(text.c_str(), text.size());
}

} // namespace G

} // namespace Xfc

