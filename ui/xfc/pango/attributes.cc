/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  attributes.cc - PangoAttibute C++ wrapper implementation
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
 
#include "attributes.hh"
#include "font.hh"
#include "../gdk/bitmap.hh"

using namespace Xfc;

/*  Pango::Color
 */
 
Pango::Color::Color()
: G::Boxed(PANGO_TYPE_COLOR, g_new(PangoColor, 1), false)
{
	set(0, 0, 0);
}

Pango::Color::Color(const char *spec)
: G::Boxed(PANGO_TYPE_COLOR, g_new(PangoColor, 1), false)
{
	if (!parse(spec))
		set(0, 0, 0);
}

Pango::Color::Color(unsigned short red, unsigned short green, unsigned short blue)
: G::Boxed(PANGO_TYPE_COLOR, g_new(PangoColor, 1), false)
{
	set(red, green, blue);
}	

Pango::Color::Color(PangoColor *color)
: G::Boxed(PANGO_TYPE_COLOR, color)
{
}

Pango::Color::Color(GdkColor *color, bool copy)
: G::Boxed(PANGO_TYPE_COLOR, color, copy)
{
}

Pango::Color::Color(const Color& src)
: G::Boxed(PANGO_TYPE_COLOR, src.g_boxed(), true)
{
}

Pango::Color::~Color()
{
}

Pango::Color& 
Pango::Color::operator=(const Color& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

void
Pango::Color::set(unsigned short red, unsigned short green, unsigned short blue)
{
	pango_color()->red = red;
	pango_color()->green = green;
	pango_color()->blue = blue;
}

/*  Pango::Attribute
 */
 
Pango::Attribute::Attribute(PangoAttribute *attr, bool copy)
: attr_(copy ? pango_attribute_copy(attr) : attr)
{
}
	
Pango::Attribute::Attribute(const Attribute& src)
: attr_(pango_attribute_copy(src.pango_attribute()))
{
}

Pango::Attribute::~Attribute()
{
	if (attr_)
	{
		pango_attribute_destroy((PangoAttribute*)attr_);
		attr_ = 0;
	}		
}

Pango::Attribute& 
Pango::Attribute::operator=(const Attribute& src)
{
	if (src.attr_ == attr_)
		return *this;
		
	pango_attribute_destroy((PangoAttribute*)attr_);
	attr_ = pango_attribute_copy(src.pango_attribute());
	return *this;
}

const PangoAttrClass* 
Pango::Attribute::pango_attr_class() const 
{ 
	return pango_attribute()->klass; 
}
		
bool
Pango::Attribute::equal(const Attribute& other) const
{
	return pango_attribute_equal(attr_, other.pango_attribute());
}

bool
Pango::Attribute::operator==(const Attribute& other) const

{
	return equal(other);
}

bool 
Pango::Attribute::operator!=(const Attribute& other) const
{
	return !equal(other);
}

void
Pango::Attribute::set_index(unsigned int start, unsigned int end)
{
	attr_->start_index = start;
	attr_->end_index = end;
}

/*  Pango::AttrString
 */

Pango::AttrString::AttrString(PangoAttribute *attribute, bool copy)
: Attribute(attribute, copy)
{
}

String
Pango::AttrString::get_string() const
{
	return pango_attr_string()->value;
}

void
Pango::AttrString::set_string(const char *str)
{
	g_free(pango_attr_string()->value);
	pango_attr_string()->value = g_strdup(str);
}

void
Pango::AttrString::set_string(const String& str)
{
	set_string(str);
}

/*  Pango::AttrLanguage
 */

Pango::AttrLanguage::AttrLanguage(PangoLanguage *language)
: Attribute(pango_attr_language_new(language), false)
{
}

/*  Pango::AttrFamily
 */

Pango::AttrFamily::AttrFamily(const String& font_family)
: AttrString(pango_attr_family_new(font_family.c_str()), false)
{
}		

/*  Pango::AttrColor
 */

Pango::AttrColor::AttrColor(PangoAttribute *attribute, bool copy)
: Attribute(attribute, copy)
{
}

Pango::Color 
Pango::AttrColor::color() const
{
	return Color(&pango_attr_color()->color);
}
	
void
Pango::AttrColor::set_color(const Color& color)
{
	pango_attr_color()->color.red = color.get_red();
	pango_attr_color()->color.green = color.get_green();
	pango_attr_color()->color.blue = color.get_blue();
}

/*  Pango::AttrForeground
 */

Pango::AttrForeground::AttrForeground(unsigned short red, unsigned short green, unsigned short blue)
: AttrColor(pango_attr_foreground_new(red, green, blue), false)
{
}

/*  Pango::AttrBackground
 */

Pango::AttrBackground::AttrBackground(unsigned short red, unsigned short green, unsigned short blue)
: AttrColor(pango_attr_background_new(red, green, blue), false)
{
}

/*  Pango::AttrInt
 */

Pango::AttrInt::AttrInt(PangoAttribute *attribute, bool copy)
: Attribute(attribute, copy)
{
}

/*  Pango::AttrSize
 */

Pango::AttrSize::AttrSize(int size, bool absolute)
: Attribute(absolute ? pango_attr_size_new_absolute(size) : pango_attr_size_new(size), false)
{
}
	
/*  Pango::AttrStyle
 */

Pango::AttrStyle::AttrStyle(Style style)
: AttrInt(pango_attr_style_new((PangoStyle)style), false)
{
}

Pango::Style
Pango::AttrStyle::style() const
{
	return (Style)value();
}

void
Pango::AttrStyle::set_style(Style style)
{
	set_value((int)style);
}

/*  Pango::AttrWeight
 */

Pango::AttrWeight::AttrWeight(Weight weight)
: AttrInt(pango_attr_weight_new((PangoWeight)weight), false)
{
}

Pango::Weight
Pango::AttrWeight::weight() const
{
	return (Weight)value();
}

void
Pango::AttrWeight::set_weight(Weight weight)
{
	set_value((int)weight);
}

/*  Pango::AttrVariant
 */

Pango::AttrVariant::AttrVariant(Variant variant)
: AttrInt(pango_attr_variant_new((PangoVariant)variant), false)
{
}

Pango::Variant
Pango::AttrVariant::variant() const
{
	return (Variant)value();
}

void
Pango::AttrVariant::set_variant(Variant variant)
{
	set_value((int)variant);
}

/*  Pango::AttrStretch
 */

Pango::AttrStretch::AttrStretch(Stretch stretch)
: AttrInt(pango_attr_stretch_new((PangoStretch)stretch), false)
{
}

Pango::Stretch
Pango::AttrStretch::stretch() const
{
	return (Stretch)value();
}

void
Pango::AttrStretch::set_stretch(Stretch stretch)
{
	set_value((int)stretch);
}

/*  Pango::AttrUnderline
 */

Pango::AttrUnderline::AttrUnderline(Underline underline)
: AttrInt(pango_attr_underline_new((PangoUnderline)underline), false)
{
}

Pango::Underline
Pango::AttrUnderline::underline() const
{
	return (Underline)value();
}

void
Pango::AttrUnderline::set_underline(Underline underline)
{
	set_value((int)underline);
}

/*  Pango::AttrStrikethrough
 */

Pango::AttrStrikethrough::AttrStrikethrough(bool strikethrough)
: AttrInt(pango_attr_strikethrough_new(strikethrough), false)
{
}

bool
Pango::AttrStrikethrough::strikethrough() const
{
	return value() != 0;
}

void
Pango::AttrStrikethrough::set_strikethrough(bool strikethrough)
{
	set_value((int)strikethrough);
}

/*  Pango::AttrRise
 */

Pango::AttrRise::AttrRise(int rise)
: AttrInt(pango_attr_rise_new(rise), false)
{
}		

/*  Pango::AttrFontDesc
 */

Pango::AttrFontDesc::AttrFontDesc(const FontDescription& desc)
: Attribute(pango_attr_font_desc_new(desc.pango_font_description()), false)
{
}

Pointer<Pango::FontDescription>
Pango::AttrFontDesc::font_description() const
{
	return G::Boxed::wrap<FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, pango_attr_font_desc()->desc);
}

void
Pango::AttrFontDesc::set_font_description(const FontDescription& desc)
{
	pango_font_description_free(pango_attr_font_desc()->desc);
	pango_attr_font_desc()->desc = pango_font_description_copy(desc.pango_font_description());
}

/*  Pango::AttrShape
 */

Pango::AttrShape::AttrShape(const Rectangle& ink_rect, const Rectangle& logical_rect)
: Attribute(pango_attr_shape_new(ink_rect.pango_rectangle(), logical_rect.pango_rectangle()), false)
{
}

const Pango::Rectangle&
Pango::AttrShape::ink_rect() const
{
	return reinterpret_cast<Rectangle&>(pango_attr_shape()->ink_rect);
}

const Pango::Rectangle&
Pango::AttrShape::logical_rect() const
{
	return reinterpret_cast<Rectangle&>(pango_attr_shape()->logical_rect);
}

void
Pango::AttrShape::set_rects(const Rectangle& ink_rect, const Rectangle& logical_rect)
{
	pango_attr_shape()->ink_rect = *ink_rect.pango_rectangle();
	pango_attr_shape()->logical_rect = *logical_rect.pango_rectangle();
}

void
Pango::AttrShape::set_ink_rect(const Rectangle& rect)
{
	pango_attr_shape()->ink_rect = *rect.pango_rectangle();
}

void
Pango::AttrShape::set_ink_rect(int x, int y, int width, int height)
{
	pango_attr_shape()->ink_rect.x = x;
	pango_attr_shape()->ink_rect.y = y;
	pango_attr_shape()->ink_rect.width = width;
	pango_attr_shape()->ink_rect.height = height;
}

void
Pango::AttrShape::set_logical_rect(const Rectangle& rect)
{
	pango_attr_shape()->logical_rect = *rect.pango_rectangle();
}

void
Pango::AttrShape::set_logical_rect(int x, int y, int width, int height)
{
	pango_attr_shape()->logical_rect.x = x;
	pango_attr_shape()->logical_rect.y = y;
	pango_attr_shape()->logical_rect.width = width;
	pango_attr_shape()->logical_rect.height = height;
}

/*  Pango::AttrFloat
 */

Pango::AttrFloat::AttrFloat(PangoAttribute *attribute, bool copy)
: Attribute(attribute, copy)
{
}

/*  Pango::AttrScale
 */

Pango::AttrScale::AttrScale(double scale_factor)
: AttrFloat(pango_attr_scale_new(scale_factor), false)
{
}		

/*  Pango::AttrFallback
 */

Pango::AttrFallback::AttrFallback(bool enable_fallback)
: AttrInt(pango_attr_fallback_new(enable_fallback), false)
{
}		

/*  Pango::AttrLetterSpacing
 */

Pango::AttrLetterSpacing::AttrLetterSpacing(int letter_spacing)
: AttrInt(pango_attr_letter_spacing_new(letter_spacing), false)
{
}

/*  Pango::AttrUnderlineColor
 */

Pango::AttrUnderlineColor:: AttrUnderlineColor(unsigned short red, unsigned short green, unsigned short blue)
: AttrColor(pango_attr_underline_color_new(red, green, blue), false)
{
}

/*  Pango::AttrStrikethroughColor
 */
	
Pango::AttrStrikethroughColor::AttrStrikethroughColor(unsigned short red, unsigned short green, unsigned short blue)
: AttrColor(pango_attr_strikethrough_color_new(red, green, blue), false)
{
}

/*  Pango::AttrStipple
 */

Pango::AttrStipple::AttrStipple(Gdk::Bitmap& stipple)
: Attribute(gdk_pango_attr_stipple_new(stipple.gdk_bitmap()), false)
{
}

Gdk::Bitmap*
Pango::AttrStipple::stipple() const
{
	return G::Object::wrap<Gdk::Bitmap>(gdk_pango_attr_stipple()->stipple);
}

/*  Pango::AttrEmbossed
 */

Pango::AttrEmbossed::AttrEmbossed(bool embossed)
: Attribute(gdk_pango_attr_embossed_new(embossed), false)
{
}

/*  Pango::AttrIterator
 */

Pango::AttrIterator::AttrIterator(PangoAttrIterator *iterator)
: iterator_(iterator)
{
}

Pango::AttrIterator::AttrIterator(const AttrIterator& src)
: iterator_(pango_attr_iterator_copy(src.pango_attr_iterator()))
{
}

Pango::AttrIterator&
Pango::AttrIterator::operator=(const AttrIterator& src)
{
	if (src.iterator_ == iterator_)
		return *this;

	if (iterator_)
		pango_attr_iterator_destroy(iterator_);

	iterator_ = pango_attr_iterator_copy(src.iterator_);
	return *this;
}

Pango::AttrIterator::~AttrIterator()
{
	if (iterator_)
	{
		pango_attr_iterator_destroy(iterator_);
		iterator_ = 0;
	}
}

int
Pango::AttrIterator::start_index() const
{
	int start;
	pango_attr_iterator_range(iterator_, &start, 0);
	return start;
}

int
Pango::AttrIterator::end_index() const
{
	int end;
	pango_attr_iterator_range(iterator_, 0, &end);
	return end;
}

Pointer<Pango::Attribute>
Pango::AttrIterator::get(AttrType type)
{
	return new Attribute(pango_attr_iterator_get(iterator_, (PangoAttrType)type), true);
}

void
Pango::AttrIterator::get_font(FontDescription& desc, PangoLanguage **language, std::vector<Pointer<Attribute> > *nonfont_attributes) const
{
	GSList *extra_attrs = 0;
	pango_attr_iterator_get_font(pango_attr_iterator(), desc.pango_font_description(), language, &extra_attrs);
	if (nonfont_attributes)
	{
		GSList *next = extra_attrs;
		while (next)
		{
			Pointer<Attribute> tmp_attribute(new Attribute((PangoAttribute*)next->data, true));
			nonfont_attributes->push_back(tmp_attribute);
			next = g_slist_next(next);
		}
		g_slist_free(extra_attrs);
	}
}

bool 
Pango::AttrIterator::get_attrs(std::vector<Pointer<Attribute> >& attrs) const
{
	g_return_val_if_fail(attrs.empty(), false);
	GSList *first = pango_attr_iterator_get_attrs(pango_attr_iterator());
	GSList *next = first;

	while (next)
	{
		Pointer<Attribute> tmp_attr(new Attribute((PangoAttribute*)next->data, false));
		attrs.push_back(tmp_attr);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !attrs.empty();
}

/*  Pango::AttrList
 */

Pango::AttrList::AttrList()
: G::Boxed(PANGO_TYPE_ATTR_LIST, pango_attr_list_new(), false)
{
}

Pango::AttrList::AttrList(PangoAttrList *list)
: G::Boxed(PANGO_TYPE_ATTR_LIST, list)
{
}

Pango::AttrList::AttrList(PangoAttrList *list, bool copy)
: G::Boxed(PANGO_TYPE_ATTR_LIST, list, copy)
{
}

Pango::AttrList::AttrList(const AttrList& src)
: G::Boxed(PANGO_TYPE_ATTR_LIST, src.g_boxed(), true)
{
}

Pango::AttrList::~AttrList()
{
}

Pango::AttrList&
Pango::AttrList::operator=(const AttrList& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Pointer<Pango::AttrIterator>
Pango::AttrList::get_iterator() const
{
	return new AttrIterator(pango_attr_list_get_iterator(pango_attr_list()));
}

void
Pango::AttrList::insert(Attribute& attr, bool before)
{
	before ? pango_attr_list_insert_before(pango_attr_list(), attr) : pango_attr_list_insert(pango_attr_list(), attr);
}

void
Pango::AttrList::change(Attribute& attr)
{
	pango_attr_list_change(pango_attr_list(), attr.pango_attribute());
}

void
Pango::AttrList::splice(AttrList& other, int pos, int length)
{
	pango_attr_list_splice(pango_attr_list(), other.pango_attr_list(), pos, length);
}

namespace { // attr_filter_slot_callback

gboolean attr_filter_slot_callback(PangoAttribute *attr, gpointer data)
{
	Pango::AttrList::AttrFilterSlot& slot = *static_cast<Pango::AttrList::AttrFilterSlot*>(data);
	Pointer<Pango::Attribute> tmp_attr(new Pango::Attribute(attr, true));
	return slot(*tmp_attr);
}

} // attr_filter_slot_callback

Pointer<Pango::AttrList> 
Pango::AttrList::filter(const AttrFilterSlot& slot)
{
	AttrFilterSlot tmp_slot(slot);
	return new AttrList(pango_attr_list_filter(pango_attr_list(), &attr_filter_slot_callback, &tmp_slot), false);
}

