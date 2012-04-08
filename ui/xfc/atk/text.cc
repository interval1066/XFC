/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  text.cc - AtkText C++ wrapper implementation
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
 
#include "text.hh"
#include "textsignals.hh"
#include "private/marshal.hh"
#include "private/textiface.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"
#include "xfc/glib/unicode.hh"

using namespace Xfc;

/*  Atk::text_attribute_register
 */

Atk::TextAttribute
Atk::text_attribute_register(const String& name)
{
	return (TextAttribute)atk_text_attribute_register(name.c_str());
}

/*  Atk::text_attribute_get_name
 */

String 
Atk::text_attribute_get_name(TextAttribute attr)
{
	return atk_text_attribute_get_name((AtkTextAttribute)attr);
}

/*  Atk::text_attribute_for_name
 */

Atk::TextAttribute
Atk::text_attribute_for_name(const String& name)
{
	return (TextAttribute)atk_text_attribute_for_name(name.c_str());
}

/*  Atk::text_attribute_get_value
 */

String 
Atk::text_attribute_get_value(TextAttribute attr, int index)
{
	return atk_text_attribute_get_value((AtkTextAttribute)attr, index);
}

namespace { // copy and free AtkAttribute

void copy_attribute(AtkAttribute *dest, const AtkAttribute *src)
{
	dest->name = g_strdup(src->name);
	dest->value = g_strdup(src->value);
}

void free_attribute(AtkAttribute *attrib)
{
	if (attrib->name)
	{
		g_free(attrib->name);
		attrib->name = 0;
	}

	if (attrib->value)
	{
		g_free(attrib->value);
		attrib->value = 0;
	}
}

} // copy and free AtkAttribute

/*  Atk::Attribute
 */

Atk::Attribute::Attribute()
{
	attrib_.name = 0;
	attrib_.value = 0;
}

Atk::Attribute::Attribute(TextAttribute attr, int index)
{
	set(text_attribute_get_name(attr), text_attribute_get_value(attr, index));
}

Atk::Attribute::Attribute(TextAttribute attr, const String& value)
{
	set(text_attribute_get_name(attr), value);
}

Atk::Attribute::Attribute(const String& name, const String& value)
{
	set(name, value);
}

Atk::Attribute::Attribute(const AtkAttribute& attrib)
{
	copy_attribute(&attrib_, &attrib);
}

Atk::Attribute::Attribute(const Attribute& src)
{
	copy_attribute(&attrib_, &src.attrib_);
}

Atk::Attribute::~Attribute()
{
	free_attribute(&attrib_);
}

Atk::Attribute& 
Atk::Attribute::operator=(const Attribute& src)
{
	if (this != &src)
	{
		free_attribute(&attrib_);
		copy_attribute(&attrib_, &src.attrib_);
	}
	return *this;
}

String
Atk::Attribute::name() const
{
	return attrib_.name;
}

String
Atk::Attribute::value() const
{
	return attrib_.value;
}
	
void 
Atk::Attribute::set(const String& name, const String& value)
{
	free_attribute(&attrib_);
	attrib_.name = g_strndup(name.c_str(), name.size());
	attrib_.value = g_strndup(value.c_str(), value.size());
}

/*  Atk::TextRectangle
 */

Atk::TextRectangle::TextRectangle()
{
	set(0, 0, 0, 0);
}

Atk::TextRectangle::TextRectangle(int x, int y, int width, int height)
{
	set(x, y, width, height);
}

Atk::TextRectangle::TextRectangle(const AtkTextRectangle& rectangle)
{
	set(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
Atk::TextRectangle::set(int x, int y, int width, int height)
{
	rectangle_.x = x;
	rectangle_.y = y;
	rectangle_.width = width;
	rectangle_.height = height;
}

/*  Atk::TextRange
 */

Atk::TextRange::TextRange(const AtkTextRange& range)
{
	range_.bounds.x = range.bounds.x;
	range_.bounds.y = range.bounds.y;
	range_.bounds.width = range.bounds.width;
	range_.bounds.height = range.bounds.height;
	range_.start_offset = range.start_offset;
	range_.end_offset = range.end_offset;
	range_.content = g_strdup(range.content);
}

Atk::TextRange::~TextRange()
{
	g_free(range_.content);
}

Atk::TextRectangle
Atk::TextRange::bounds() const
{
	return TextRectangle(range_.bounds);
}

/*  Atk::Text
 */

Atk::Text::Text()
{
}

Atk::Text::~Text()
{
}

String
Atk::Text::get_text(int start_offset, int end_offset) const
{
	char *text = atk_text_get_text(atk_text(), start_offset, end_offset);
	String s(text);
	g_free(text);
	return s;
}

G::Unichar 
Atk::Text::get_character_at_offset(int offset) const
{
	return atk_text_get_character_at_offset(atk_text(), offset);
}

String 
Atk::Text::get_text_after_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const
{
	char *text = atk_text_get_text_after_offset(atk_text(), offset, (AtkTextBoundary)boundary_type, start_offset, end_offset);
	String s(text);
	g_free(text);
	return s;
}

String
Atk::Text::get_text_at_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const
{
	char *text = atk_text_get_text_at_offset(atk_text(), offset, (AtkTextBoundary)boundary_type, start_offset, end_offset);
	String s(text);
	g_free(text);
	return s;
}

String 
Atk::Text::get_text_before_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const
{
	char *text = atk_text_get_text_before_offset(atk_text(), offset, (AtkTextBoundary)boundary_type, start_offset, end_offset);
	String s(text);
	g_free(text);
	return s;
}

std::vector<Atk::Attribute>
Atk::Text::get_run_attributes(int offset, int *start_offset, int *end_offset) const
{
	std::vector<Attribute> attribs;
	GSList *first = atk_text_get_run_attributes(atk_text(), offset, start_offset, end_offset);
	GSList *next = first;

	while (next)
	{
		Attribute attrib(*((AtkAttribute*)next->data));
		attribs.push_back(attrib);
		next = g_slist_next(next);
	}

	atk_attribute_set_free(first);
	return attribs;
}

std::vector<Atk::Attribute>
Atk::Text::get_default_attributes() const
{
	std::vector<Attribute> attribs;
	GSList *first = atk_text_get_default_attributes(atk_text());
	GSList *next = first;

	while (next)
	{
		Attribute attrib(*((AtkAttribute*)next->data));
		attribs.push_back(attrib);
		next = g_slist_next(next);
	}
	
	atk_attribute_set_free(first);
	return attribs;
}
	
String
Atk::Text::get_selection(int selection_num, int *start_offset, int *end_offset) const
{
	return atk_text_get_selection(atk_text(), selection_num, start_offset, end_offset);
}

Atk::TextRectangle
Atk::Text::get_range_extents(int start_offset, int end_offset, CoordType coord_type)
{
	TextRectangle rect;
	atk_text_get_range_extents(atk_text(), start_offset, end_offset, (AtkCoordType)coord_type, rect.atk_text_rectangle());
	return rect;
}

void
Atk::Text::get_range_extents(int start_offset, int end_offset, CoordType coord_type, TextRectangle& rect)
{
	atk_text_get_range_extents(atk_text(), start_offset, end_offset, (AtkCoordType)coord_type, rect.atk_text_rectangle());
}

std::vector<Atk::TextRange>
Atk::Text::get_bounded_ranges(const TextRectangle& rect, CoordType coord_type, TextClipType x_clip_type, TextClipType y_clip_type)
{
	AtkTextRange **ranges = atk_text_get_bounded_ranges(atk_text(), rect.atk_text_rectangle(), (AtkCoordType)coord_type,
                                                            (AtkTextClipType)x_clip_type, (AtkTextClipType)y_clip_type);
	AtkTextRange **first = ranges;
	std::vector<TextRange> tmp_ranges;

	if (ranges)
	{
		while (*ranges)
		{
			AtkTextRange *range = *ranges;
			TextRange tmp_range(*range);
			tmp_ranges.push_back(tmp_range);
			*ranges++;
			g_free(range->content);
			g_free(range);
		}
		g_free(first);
	}
	return tmp_ranges;
}

/*  Atk::TextIface
 */

void
Atk::TextIface::init(AtkTextIface *g_iface)
{
	g_iface->text_changed = &text_changed_proxy;
	g_iface->text_caret_moved = &text_caret_moved_proxy;
	g_iface->text_selection_changed = &text_selection_changed_proxy;
	g_iface->text_attributes_changed = text_attributes_changed_proxy;
}

AtkTextIface*
Atk::TextIface::get_parent_iface(void *instance)
{
	return static_cast<AtkTextIface*>(g_type_interface_peek_parent(ATK_TEXT_GET_IFACE(instance)));
}

void
Atk::TextIface::text_changed_proxy(AtkText *text, gint position, gint length)
{
	TextSignals *signals = dynamic_cast<TextSignals*>(G::ObjectSignals::pointer((GObject*)text));
	if (signals)
		signals->on_text_changed(position, length);
	else
	{
		AtkTextIface *g_iface = get_parent_iface(text);
		if (g_iface && g_iface->text_changed)
			g_iface->text_changed(text, position, length);
	}
}

void
Atk::TextIface::text_caret_moved_proxy(AtkText *text, gint location)
{
	TextSignals *signals = dynamic_cast<TextSignals*>(G::ObjectSignals::pointer((GObject*)text));
	if (signals)
		signals->on_text_caret_moved(location);
	else
	{
		AtkTextIface *g_iface = get_parent_iface(text);
		if (g_iface && g_iface->text_caret_moved)
			g_iface->text_caret_moved(text, location);
	}
}

void
Atk::TextIface::text_selection_changed_proxy(AtkText *text)
{
	TextSignals *signals = dynamic_cast<TextSignals*>(G::ObjectSignals::pointer((GObject*)text));
	if (signals)
		signals->on_text_selection_changed();
	else
	{
		AtkTextIface *g_iface = get_parent_iface(text);
		if (g_iface && g_iface->text_selection_changed)
			g_iface->text_selection_changed(text);
	}
}

void
Atk::TextIface::text_attributes_changed_proxy(AtkText *text)
{
	TextSignals *signals = dynamic_cast<TextSignals*>(G::ObjectSignals::pointer((GObject*)text));
	if (signals)
		signals->on_text_attributes_changed();
	else
	{
		AtkTextIface *g_iface = get_parent_iface(text);
		if (g_iface && g_iface->text_attributes_changed)
			g_iface->text_attributes_changed(text);
	}
}

/*  Atk::Text signals
 */

const Atk::Text::TextChangedSignalType Atk::Text::text_changed_signal("text_changed", (GCallback)&G::Marshal::void_int_int_callback);

const Atk::Text::TextCaretMovedSignalType Atk::Text::text_caret_moved_signal("text_caret_moved", (GCallback)&G::Marshal::void_int_callback);

const Atk::Text::TextSelectionChangedSignalType Atk::Text::text_selection_changed_signal("text_selection_changed", (GCallback)&G::Marshal::void_callback);

const Atk::Text::TextAttributesChangedSignalType Atk::Text::text_attributes_changed_signal("text_attributes_changed", (GCallback)&G::Marshal::void_callback);

