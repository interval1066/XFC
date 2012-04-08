/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  attributes.inl - Pango::Attibute inline functions
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

/*  Pango::Color
 */

inline PangoColor*
Xfc::Pango::Color::pango_color() const
{
	return reinterpret_cast<PangoColor*>(boxed_);
}

inline Xfc::Pango::Color::operator PangoColor* () const
{
	return this ? pango_color() : 0;
}

inline unsigned short
Xfc::Pango::Color::get_red() const
{
	return pango_color()->red;
}

inline unsigned short
Xfc::Pango::Color::get_green() const
{
	return pango_color()->green;
}

inline unsigned short
Xfc::Pango::Color::get_blue() const
{
	return pango_color()->blue;
}

inline void
Xfc::Pango::Color::set_red(unsigned short red)
{
	pango_color()->red = red;
}

inline void
Xfc::Pango::Color::set_green(unsigned short green)
{
	pango_color()->green = green;
}

inline void
Xfc::Pango::Color::set_blue(unsigned short blue)
{
	pango_color()->blue = blue;
}

inline bool
Xfc::Pango::Color::parse(const char *spec)
{
	return pango_color_parse(pango_color(), spec);
}

/*  Pango::Attribute
 */

inline PangoAttribute*
Xfc::Pango::Attribute::pango_attribute() const
{
	return attr_;
}

inline Xfc::Pango::Attribute::operator PangoAttribute* () const
{
	return this ? attr_ : 0;
}

inline Xfc::Pango::AttrType
Xfc::Pango::Attribute::type() const
{
	return (AttrType)attr_->klass->type;
}

inline bool
Xfc::Pango::Attribute::is_language() const
{
	return attr_->klass->type == PANGO_ATTR_LANGUAGE;
}

inline bool
Xfc::Pango::Attribute::is_family() const
{
	return attr_->klass->type == PANGO_ATTR_FAMILY;
}

inline bool
Xfc::Pango::Attribute::is_foreground() const
{
	return attr_->klass->type == PANGO_ATTR_FOREGROUND;
}

inline bool
Xfc::Pango::Attribute::is_background() const
{
	return attr_->klass->type == PANGO_ATTR_BACKGROUND;
}

inline bool
Xfc::Pango::Attribute::is_size() const
{
	return attr_->klass->type == PANGO_ATTR_SIZE;
}

inline bool
Xfc::Pango::Attribute::is_style() const
{
	return attr_->klass->type == PANGO_ATTR_STYLE;
}

inline bool
Xfc::Pango::Attribute::is_weight() const
{
	return attr_->klass->type == PANGO_ATTR_WEIGHT;
}

inline bool
Xfc::Pango::Attribute::is_variant() const
{
	return attr_->klass->type == PANGO_ATTR_VARIANT;
}

inline bool
Xfc::Pango::Attribute::is_stretch() const
{
	return attr_->klass->type == PANGO_ATTR_STRETCH;
}

inline bool
Xfc::Pango::Attribute::is_underline() const
{
	return attr_->klass->type == PANGO_ATTR_UNDERLINE;
}

inline bool
Xfc::Pango::Attribute::is_strikethrough() const
{
	return attr_->klass->type == PANGO_ATTR_STRIKETHROUGH;
}

inline bool
Xfc::Pango::Attribute::is_rise() const
{
	return attr_->klass->type == PANGO_ATTR_RISE;
}

inline bool
Xfc::Pango::Attribute::is_font_description() const
{
	return attr_->klass->type == PANGO_ATTR_FONT_DESC;
}

inline bool
Xfc::Pango::Attribute::is_shape() const
{
	return attr_->klass->type == PANGO_ATTR_SHAPE;
}

inline bool
Xfc::Pango::Attribute::is_scale() const
{
	return attr_->klass->type == PANGO_ATTR_SCALE;
}

inline unsigned int
Xfc::Pango::Attribute::start_index() const
{
	return attr_->start_index;
}

inline unsigned int
Xfc::Pango::Attribute::end_index() const
{
	return attr_->end_index;
}

inline void
Xfc::Pango::Attribute::set_start_index(unsigned int start)
{
	attr_->start_index = start;
}

inline void
Xfc::Pango::Attribute::set_end_index(unsigned int end)
{
	attr_->end_index = end;
}

/*  Pango::AttrString
 */

inline PangoAttrString*
Xfc::Pango::AttrString::pango_attr_string() const
{
	return reinterpret_cast<PangoAttrString*>(attr_);
}

/*  Pango::AttrLanguage
 */

inline PangoAttrLanguage*
Xfc::Pango::AttrLanguage::pango_attr_language() const
{
	return reinterpret_cast<PangoAttrLanguage*>(attr_);
}

inline PangoLanguage*
Xfc::Pango::AttrLanguage::get_language() const
{
	return pango_attr_language()->value;
}

inline void
Xfc::Pango::AttrLanguage::set_language(PangoLanguage *language)
{
	pango_attr_language()->value = language;
}

/*  Pango::AttrColor
 */

inline PangoAttrColor*
Xfc::Pango::AttrColor::pango_attr_color() const
{
	return reinterpret_cast<PangoAttrColor*>(attr_);
}

/*  Pango::AttrInt
 */

inline PangoAttrInt*
Xfc::Pango::AttrInt::pango_attr_int() const
{
	return reinterpret_cast<PangoAttrInt*>(attr_);
}

inline int
Xfc::Pango::AttrInt::value() const
{
	return pango_attr_int()->value;
}

inline void
Xfc::Pango::AttrInt::set_value(int value)
{
	pango_attr_int()->value = value;
}

inline int 
Xfc::Pango::AttrSize::size() const
{
	return pango_attr_size()->size;
}

inline bool 
Xfc::Pango::AttrSize::absolute() const
{
	return pango_attr_size()->absolute;
}

/*  Pango::AttrFontDesc
 */

inline PangoAttrFontDesc*
Xfc::Pango::AttrFontDesc::pango_attr_font_desc() const
{
	return reinterpret_cast<PangoAttrFontDesc*>(attr_);
}

/*  Pango::AttrShape
 */
inline PangoAttrShape*
Xfc::Pango::AttrShape::pango_attr_shape() const
{
	return reinterpret_cast<PangoAttrShape*>(attr_);
}

/*  Pango::AttrFloat
 */

inline PangoAttrFloat*
Xfc::Pango::AttrFloat::pango_attr_float() const
{
	return reinterpret_cast<PangoAttrFloat*>(attr_);
}

inline double
Xfc::Pango::AttrFloat::value() const
{
	return pango_attr_float()->value;
}

inline void
Xfc::Pango::AttrFloat::set_value(double value)
{
	pango_attr_float()->value = value;
}

/*  Pango::AttrStipple
 */

inline GdkPangoAttrStipple*
Xfc::Pango::AttrStipple::gdk_pango_attr_stipple() const
{
	return reinterpret_cast<GdkPangoAttrStipple*>(attr_);
}

/*  Pango::AttrEmbossed
 */

inline GdkPangoAttrEmbossed*
Xfc::Pango::AttrEmbossed::gdk_pango_attr_embossed() const
{
	return reinterpret_cast<GdkPangoAttrEmbossed*>(attr_);
}

inline bool
Xfc::Pango::AttrEmbossed::embossed() const
{
	return gdk_pango_attr_embossed()->embossed != 0;
}

/*  Pango::AttrIterator
 */

inline PangoAttrIterator*
Xfc::Pango::AttrIterator::pango_attr_iterator() const
{
	return iterator_;
}

inline void
Xfc::Pango::AttrIterator::range(int *start, int *end) const
{
	pango_attr_iterator_range(iterator_, start, end);
}

inline bool
Xfc::Pango::AttrIterator::next()
{
	return pango_attr_iterator_next(iterator_);
}

/*  Pango::AttrList
 */

inline PangoAttrList*
Xfc::Pango::AttrList::pango_attr_list() const
{
	return reinterpret_cast<PangoAttrList*>(boxed_);
}

inline Xfc::Pango::AttrList::operator PangoAttrList* () const
{
	return this ? pango_attr_list() : 0;
}

