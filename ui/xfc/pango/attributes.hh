/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/pango/attributes.hh
/// @brief A PangoAttibute C++ wrapper interface.
///
/// Provides Attribute and its derived classes, a group a classes that
/// distinguish between different types of pango attributes.

#ifndef XFC_PANGO_ATTRIBUTES_HH
#define XFC_PANGO_ATTRIBUTES_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef XFC_PANGO_FONT_HH
#include <xfc/pango/font.hh>
#endif

#ifndef __PANGO_ATTRIBUTES_H__
#include <pango/pango-attributes.h>
#endif

#ifndef __GDK_PANGO_H__
#include <gdk/gdkpango.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Bitmap;
}

namespace Pango {

/// @enum Underline
/// Underline is used to specify whether text should be underlined, and if so, the type of underlining.

enum Underline
{
	UNDERLINE_NONE = PANGO_UNDERLINE_NONE,
	///< No underline should be drawn.

	UNDERLINE_SINGLE = PANGO_UNDERLINE_SINGLE,
	///< A single underline should be drawn.

	UNDERLINE_DOUBLE = PANGO_UNDERLINE_DOUBLE,
	///< A double underline should be drawn.

	UNDERLINE_LOW = PANGO_UNDERLINE_LOW,
	///< A single underline should be drawn at a position beneath the ink extents
	///< of the text being underlined; this should be used only for underlining
	///< single characters, such as for keyboard accelerators; UNDERLINE_SINGLE
	///< should be used for extended portions of text.
	
	UNDERLINE_ERROR = PANGO_UNDERLINE_ERROR
	///< A wavy underline should be drawn below; this underline is typically used
	///< to indicate an error such as a possilble mispelling; in some cases an 
	///< contrasting color may automatically be used.
};

/// @enum AttrType
/// Distinguishes between different types of attributes.
/// Along with the predefined values, it is possible to allocate additional values
/// for custom attributes using pango_attr_register_type(). The predefined values
/// are given below. The type of class used to store the attribute is listed in 
/// parentheses after the description.

enum AttrType
{
	ATTR_INVALID = PANGO_ATTR_INVALID, ///< Invalid.
	ATTR_LANGUAGE = PANGO_ATTR_LANGUAGE, ///< Language (AttrLanguage).
	ATTR_FAMILY = PANGO_ATTR_FAMILY, ///< Font family name list (AttrString).
	ATTR_STYLE = PANGO_ATTR_STYLE, ///< Font slant style (AttrInt).
	ATTR_WEIGHT = PANGO_ATTR_WEIGHT, ///< Font weight (AttrInt).
	ATTR_VARIANT = PANGO_ATTR_VARIANT, ///< Font variant (normal or small caps) (AttrInt).
	ATTR_STRETCH = PANGO_ATTR_STRETCH, ///< Font stretch (AttrInt).
	ATTR_SIZE = PANGO_ATTR_SIZE, ///< Font size in points divided by PANGO_SCALE (AttrInt).
	ATTR_FONT_DESC = PANGO_ATTR_FONT_DESC, ///< Font description (AttrFontDesc).
	ATTR_FOREGROUND = PANGO_ATTR_FOREGROUND, ///< Foreground color (AttrColor).
	ATTR_BACKGROUND = PANGO_ATTR_BACKGROUND, ///< Background color (AttrColor).
	ATTR_UNDERLINE = PANGO_ATTR_UNDERLINE, ///< Whether the text has an underline (AttrInt).
	ATTR_STRIKETHROUGH = PANGO_ATTR_STRIKETHROUGH, ///< Whether the text is struck-through (AttrInt).
	ATTR_RISE = PANGO_ATTR_RISE, ///< Baseline displacement (AttrInt).
	ATTR_SHAPE = PANGO_ATTR_SHAPE, ///< Shape (AttrShape).
	ATTR_SCALE = PANGO_ATTR_SCALE, ///< Font size scale factor (AttrScale).
	ATTR_FALLBACK = PANGO_ATTR_FALLBACK, ///< Whether fallback is enabled (AttrInt).
	ATTR_LETTER_SPACING = PANGO_ATTR_LETTER_SPACING, ///< The amount of extra space to add between graphemes.    
	ATTR_UNDERLINE_COLOR = PANGO_ATTR_UNDERLINE_COLOR, ///< The color of underlines.
	ATTR_STRIKETHROUGH_COLOR = PANGO_ATTR_STRIKETHROUGH_COLOR ///< The color of strikethrough lines.
};

/// @class Color attributes.hh xfc/pango/attributes.hh
/// @brief A PangoColor C++ wrapper class.
///

class Color : public G::Boxed
{
public:
/// @name Constructors
/// @{

	Color();
	///< Constructs the default color black with a reference count of 1 that the caller owns.

	explicit Color(const char *spec);
	///< Constructs a color object by filling in the fields from a string specification. 
	///< @param spec A string specifying the new color. 
	///<	
	///< If parsing of the specifier failed the color is set to black. The string can either
	///< be one of a large set of standard names (taken from the X11 rgb.txt file), or it 
	///< can be a hex value in the form '\#rgb' '\#rrggbb' '\#rrrgggbbb' or '\#rrrrggggbbbb' where
	///< 'r', 'g' and 'b' are hex digits of the red, green, and blue components of the color,
	///< respectively. For example, white in the four forms is '\#fff' '\#ffffff' '\#fffffffff'
	///< and '\#ffffffffffff'.

	Color(unsigned short red, unsigned short green, unsigned short blue);
	///< Construct a color with the specified red, green and blue values.
	///< @param red The red component of the color, a value between 0 and 65535.
	///< @param green The green component of the color, a value between 0 and 65535.
	///< @param blue The blue component of the color, a value between 0 and 65535.

	explicit Color(PangoColor *color);
	///< Construct a new color from an existing PangoColor.
	///< @param color A pointer to a PangoColor.
	///<
	///< The <EM>color</EM> can be a newly created PangoColor or an existing
	///< PangoColor. The Color object created is a temporary object. It doesn't
	///< take over the ownership of PangoColor and PangoColor is not freed by the
	///< destructor. Color is created with a reference count of 1 that the caller owns.

	Color(GdkColor *color, bool copy);
	///< Construct a new color from an existing PangoColor.
	///< @param color A pointer to a PangoColor.
	///< @param copy Whether the Color object should make a copy of PangoColor or not.
	///<
	///< The <EM>color</EM> can be a newly created PangoColor or an existing PangoColor.
	///< If <EM>copy</EM> is true Color will make a copy of PangoColor. If <EM>copy</EM>
	///< is false Color wont make a copy but instead takes over the ownership of PangoColor.
	///< Either way, the destructor will free PangoColor when the Color object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap PangoColor objects in a
	///< C++ wrapper. Color is created with a reference count of 1 that the caller owns.

	Color(const Color& src);
	///< Copy constructor.
	///< @param src The source color.

	~Color();
	///< Destructor.

	Color& operator=(const Color& src);
	///< Assignment operator.
	///< @param src The source color.

/// @}
/// @name Accessors
/// @{

	PangoColor* pango_color() const;
	///< Get a pointer to the PangoColor structure.

	operator PangoColor* () const;
	///< Conversion operator; safely converts a Color to a PangoColor pointer.

	unsigned short get_red() const;
	///< Returns the red component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

	unsigned short get_green() const;
	///< Returns the green component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

	unsigned short get_blue() const;
	///< Returns the blue component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

/// @}
/// @name Methods
/// @{

	void set_red(unsigned short red);
	///< Sets the red component of the color.
	///< @param red The red component, a value between 0 and 65535,

	void set_green(unsigned short green);
	///< Sets the green component of the color.
	///< @param green The green component, a value between 0 and 65535,

	void set_blue(unsigned short blue);
	///< Sets the blue component of the color.
	///< @param blue The blue component, a value between 0 and 65535,

	void set(unsigned short red, unsigned short green, unsigned short blue);
	///< Sets the red, green and blue components to the specified values.
	///< @param red The red component of the color, a value between 0 and 65535.
	///< @param green The green component of the color.
	///< @param blue The blue component of the color.

	bool parse(const char *spec);
	///< Fill in the fields of a color from a string specification. 
	///< @param spec A string specifying the new color. 
	///< @return <EM>true</EM> if parsing of the specifier succeeded, otherwise <EM>false</EM>.	
	///<	
	///< The string can either one of a large set of standard names (taken from the X11
	///< rgb.txt file), or it can be a hex value in the form '\#rgb' '\#rrggbb' '\#rrrgggbbb'
	///< or '\#rrrrggggbbbb' where 'r', 'g' and 'b' are hex digits of the red, green, and
	///< blue components of the color, respectively. For example, white in the four forms
	///< is '\#fff' '\#ffffff' '\#fffffffff' and '\#ffffffffffff'.

/// @}
};

/// @class Attribute attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttriubte C++ wrapper class.
///
/// Attribute and its derived classes are used to represent and manipulate sets
/// of attributes applied to a portion of text. Attributed text is used in a 
/// number of places in Pango. It is used as the input to the itemization process
/// and also when creating a Pango::Layout.

class Attribute : public Xfc::Object
{
protected:
	PangoAttribute *attr_;

public:
/// @name Constructors
/// @{

	explicit Attribute(PangoAttribute *attr, bool copy);
	///< Construct a new attribute from an existing PangoAttribute.
	///< @param attr A PangoAttribute.
	///< @param copy Set <EM>true</EM> if a copy of <EM>attr</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>attr</EM> is copied. If false <EM>attr</EM>
	///< is assumed to be a valid attribute that must be freed. Either way Attribute
	///< will own the PangoAttribute and free it when it's no longer required.

	Attribute(const Attribute& src);
	///< Copy constructor.
	///< @param src The source attribute.

	virtual ~Attribute();
	///< Destructor.

	Attribute& operator=(const Attribute& src);
	///< Assignment operator.
	///< @param src The source attribute.

/// @}
/// @name Accessors
/// @{

	PangoAttribute* pango_attribute() const;
	///< Get a pointer to the PangoAttribute structure.

	const PangoAttrClass* pango_attr_class() const;
	///< Get a pointer to the PangoAttrClass structure.

	operator PangoAttribute* () const;
	///< Conversion operator; safely converts an Attribute to a PangoAttribute pointer.

	AttrType type() const;
	///< Returns the attribute type. <B>Note:</B> GDK registers AttrStiple and AttrBitmap as
	///< new attribute types so ATTR_INVALID will be returned for these attributes.

	bool is_language() const;
	///< Returns true if the attribute type is ATTR_LANGUAGE.

	bool is_family() const;
	///< Returns true if the attribute type is ATTR_FAMILY.

	bool is_foreground() const;
	///< Returns true if the attribute type is ATTR_FOREGROUND.

	bool is_background() const;
	///< Returns true if the attribute type is ATTR_BACKGROUND.

	bool is_size() const;
	///< Returns true if the attribute type is ATTR_SIZE.

	bool is_style() const;
	///< Returns true if the attribute type is ATTR_STYLE.

	bool is_weight() const;
	///< Returns true if the attribute type is ATTR_WEIGHT.

	bool is_variant() const;
	///< Returns true if the attribute type is ATTR_VARIANT.

	bool is_stretch() const;
	///< Returns true if the attribute type is ATTR_STRETCH.

	bool is_underline() const;
	///< Returns true if the attribute type is ATTR_UNDERLINE.

	bool is_strikethrough() const;
	///< Returns true if the attribute type is ATTR_STRIKETHROUGH.

	bool is_rise() const;
	///< Returns true if the attribute type is ATTR_RISE.

	bool is_font_description() const;
	///< Returns true if the attribute type is ATTR_FONT_DESC.

	bool is_shape() const;
	///< Returns true if the attribute type is ATTR_SHAPE.

	bool is_scale() const;
	///< Returns true if the attribute type is ATTR_SCALE.

	unsigned int start_index() const;
	///< Returns the starting byte index of the range this attribute applies to.

	unsigned int end_index() const;
	///< Returns the end byte index of the range this attribute applies to
	///< (the character at this index is not included in the range).

	bool equal(const Attribute& other) const;
	///< Compares this attribute with <EM>other</EM> for equality.
	///< @param other The attribute to compare with.
	///< @return <EM>true</EM> if the two attributes have the same value.
	///<
	///< This compares only the actual value of the two attributes and not
	///< the ranges that the attributes apply to.

	bool operator==(const Attribute& other) const;
	///< Equality operator; compares this attribute with <EM>other</EM> for equality.
	///< @param other The attribute to compare with.
	///< @return <EM>true</EM> if the two attributes have the same value.
	///<
	///< This compares only the actual value of the two attributes and not
	///< the ranges that the attributes apply to.

	bool operator!=(const Attribute& other) const;
	///< Inequality operator; compares this attribute with <EM>other</EM> for inequality.
	///< @param other The attribute to compare with.
	///< @return <EM>true</EM> if the two attributes have different values.
	///<
	///< This compares only the actual value of the two attributes and not
	///< the ranges that the attributes apply to.

/// @}
/// @name Methods
/// @{

	void set_start_index(unsigned int start);
	///< Set the starting byte index for the range this attribute applies to.
	///< @param start The start index.

	void set_end_index(unsigned int end);
	///< Set the end byte index for the range this attribute applies to.
	///< @param end The end index.

	void set_index(unsigned int start, unsigned int end);
	///< Set the start and end byte index for the range this attribute applies to.
	///< @param start The start index.
	///< @param end The end index.

/// @}
};

/// @class AttrString attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrString C++ wrapper class.
///
/// AttrString is the base class for string attributes.

class AttrString : public Attribute
{
protected:
/// @name Constructors
/// @{
	explicit AttrString(PangoAttribute *attr, bool copy);
	///< Construct a new string attribute from an existing string PangoAttribute.
	///< @param attr A string PangoAttribute.
	///< @param copy Set <EM>true</EM> if a copy of <EM>attr</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>attr</EM> is copied. If false <EM>attr</EM>
	///< is assumed to be a valid string attribute that must be freed. Either way AttrString
	///< will own the PangoAttribute and free it when it's no longer required.

/// @}

public:
/// @name Accessors
/// @{

	PangoAttrString* pango_attr_string() const;
	///< Get a pointer to the PangoAttrString structure.

	String get_string() const;
	///< Returns the string.

/// @}
/// @name Methods
/// @{
	
	void set_string(const char *str);
	void set_string(const String& str);
	///< Sets the string value for the attribute.
	///< @param str The new string, either a font family or language.
	
/// @}
};

/// @class AttrLanguage attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrLanguage C++ wrapper class.
///
/// AttrLanguage wraps the language attribute (ATTR_LANGUAGE).

class AttrLanguage : public Attribute
{
public:
/// @name Constructors
/// @{
	explicit AttrLanguage(PangoLanguage *language);
	///< Construct a new language tag attribute.
	///< @param language The language tag.

/// @}
/// @name Accessors
/// @{

	PangoAttrLanguage* pango_attr_language() const;
	///< Get a pointer to the PangoAttrLanguage structure.

	PangoLanguage* get_language() const;
	///< Returns the language tag.

/// @}
/// @name Methods
/// @{

	void set_language(PangoLanguage *language);
	///< Sets the language.
	///< @param language The language tag.
	
/// @}
};

/// @class AttrFamily attributes.hh xfc/pango/attributes.hh
/// @brief Pango font family name C++ wrapper class.
///
/// AttrFamily wraps the font family name attribute (ATTR_FAMILY).

class AttrFamily : public AttrString
{
public:
/// @name Constructors
/// @{

	explicit AttrFamily(const String& font_family);
	///< Construct a new font family attribute.
	///< @param font_family The family or comma separated list of families.

/// @}
};

/// @class AttrColor attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrColor C++ wrapper class.
///
/// AttrColor is the base class for the foreground and background color attributes.

class AttrColor : public Attribute
{
protected:
/// @name Constructors
/// @{

	explicit AttrColor(PangoAttribute *attr, bool copy);
	///< Construct a new color attribute from an existing color PangoAttribute.
	///< @param attr An color PangoAttribute.
	///< @param copy Set <EM>true</EM> if a copy of <EM>attr</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>attr</EM> is copied. If false <EM>attr</EM>
	///< is assumed to be a valid color attribute that must be freed. Either way AttrColor
	///< will own the PangoAttribute and free it when it's no longer required.

/// @}

public:
/// @name Accessors
/// @{

	PangoAttrColor* pango_attr_color() const;
	///< Get a pointer to the PangoAttrColor structure.

	Color color() const;
	///< Gets the attibute color.
	///< @return A Pango::Color.
	
/// @}
/// @name Methods
/// @{
	
	void set_color(const Color& color);
	///< Sets the red, green and blue values for the color.
	///< @param color A Pango::Color.

/// @}
};

/// @class AttrForeground attributes.hh xfc/pango/attributes.hh
/// @brief Pango foreground color C++ wrapper class.
///
/// AttrForeground wraps the foreground color attribute (ATTR_FOREGROUND).

class AttrForeground : public AttrColor
{
public:
/// @name Constructors
/// @{

	AttrForeground(unsigned short red, unsigned short green, unsigned short blue);
	///< Construct a new foreground color attribute.
	///< @param red The red value (ranging from 0 to 65535).
	///< @param green The green value.
	///< @param blue The blue value.

/// @}
};

/// @class AttrBackground attributes.hh xfc/pango/attributes.hh
/// @brief A Pango background color C++ wrapper class.
///
/// AttrBackground wraps the background color attribute (ATTR_FOREGROUND).

class AttrBackground : public AttrColor
{
public:
/// @name Constructors
/// @{

	AttrBackground(unsigned short red, unsigned short green, unsigned short blue);
	///< Construct a new background color attribute.
	///< @param red The red value (ranging from 0 to 65535).
	///< @param green The green value.
	///< @param blue The blue value.

/// @}
};

/// @class AttrInt attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrInt C++ wrapper class.
///
/// AttrInt is the base class for the integer attribute types: Style, Weight,
/// Variant, Stretch, Size, Underline, Strikthrough and Rise.

class AttrInt : public Attribute
{
protected:
/// @name Constructors
/// @{

	explicit AttrInt(PangoAttribute *attr, bool copy);
	///< Construct a new integer attribute from an existing integer PangoAttribute.
	///< @param attr An integer PangoAttribute.
	///< @param copy Set <EM>true</EM> if a copy of <EM>attr</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>attr</EM> is copied. If false <EM>attr</EM>
	///< is assumed to be a valid integer attribute that must be freed. Either way AttrInt
	///< will own the PangoAttribute and free it when it's no longer required.

/// @}

public:
/// @name Accessors
/// @{

	PangoAttrInt* pango_attr_int() const;
	///< Get a pointer to the PangoAttrInt structure.

	int value() const;
	///< Returns the integer value.

/// @}
/// @name Methods
/// @{

	void set_value(int value);
	///< Sets the integer value.
	///< @param value The new value.
	
/// @}
};

/// @class AttrSize attributes.hh xfc/pango/attributes.hh
/// @brief Pango size C++ wrapper class.
///
/// AttrSize wraps the size attribute (ATTR_SIZE).

class AttrSize : public Attribute
{
public:
/// @name Constructors
/// @{

	explicit AttrSize(int size, bool absolute = false);
	///< Construct a new font-size attribute.
	///< @param size The font size.
	///< @param absolute Set <EM>false</EM> if <EM>size</EM> is in points and
	///<                 <EM>true</EM> if <EM>size</EM> is in device units.
	///<
	///< If <EM>absolute</EM> is false the font <EM>size</EM> is in PANGO_SCALEths of a point
	///< and the font-size attribute created is in fractional units. If <EM>absolute</EM> is 
	///< true the font <EM>size</EM> is in PANGO_SCALEths of a device unit and the font-size
	///< attribute created is in device units. 
	///<
	///< The PANGO_SCALE macro represents the scale between dimensions used for Pango distances
	///< and device units. (The definition of device units is dependent on the output device; 
	///< it will typically be pixels for a screen, and points for a printer.) PANGO_SCALE is
	///< currently 1024, but this may be changed in the future.
	///<
	///< When setting font sizes, device units are always considered to be points (as in 
	///< "12 point font"), rather than pixels.
	
/// @}
/// @name Accessors
/// @{

	PangoAttrSize* pango_attr_size() const;
	///< Get a pointer to the PangoAttrSize structure.

	int size() const;
	///< Returns the font size.
	
	bool absolute() const;
	///< Returns false if the font size is in fractional units and true if it's in device units.

/// @}
/// @name Methods
/// @{

	void set_size(int size);
	///< Sets the font size.
	///< @param size The new font size.

	void set_absolute(bool absolute);
	///< Sets whether the font size is in fractional units or device units.
	///< @param absolute Set <EM>false</EM> if the size is in points and <EM>true</EM> if it's in device units.

/// @}
};

/// @class AttrStyle attributes.hh xfc/pango/attributes.hh
/// @brief Pango style C++ wrapper class.
///
/// AttrStyle wraps the style attribute (ATTR_STYLE).

class AttrStyle : public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrStyle(Style style = STYLE_NORMAL);
	///< Constructs a new font slant style attribute.
	///< @param style The slant style.

/// @}
/// @name Accessors
/// @{

	Style style() const;
	///< Returns the slant style.

/// @}
/// @name Methods
/// @{

	void set_style(Style style);
	///< Sets the slant style.
	///< @param style The new slant style.

/// @}
};

/// @class AttrWeight attributes.hh xfc/pango/attributes.hh
/// @brief Pango weight C++ wrapper class.
///
/// AttrWeight wraps the weight attribute (ATTR_WEIGHT).

class AttrWeight: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrWeight(Weight weight = WEIGHT_NORMAL);
	///< Construct a new font weight attribute.
	///< @param weight The font weight.

/// @}
/// @name Accessors
/// @{

	Weight weight() const;
	///< Returns the font weight.

/// @}
/// @name Methods
/// @{

	void set_weight(Weight weight);
	///< Sets the font weight.
	///< @param weight The new font weight.

/// @}
};

/// @class AttrVariant attributes.hh xfc/pango/attributes.hh
/// @brief Pango variant C++ wrapper class.
///
/// AttrVariant wraps the variant attribute (ATTR_VARIANT).

class AttrVariant: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrVariant(Variant variant = VARIANT_NORMAL);
	///< Construct a new font variant attribute (normal or small caps).
	///< @param variant The Variant.

/// @}
/// @name Accessors
/// @{

	Variant variant() const;
	///< Returns the variant.

/// @}
/// @name Methods
/// @{

	void set_variant(Variant variant);
	///< Sets the variant.
	///< @param variant The new variant.

/// @}
};

/// @class AttrStretch attributes.hh xfc/pango/attributes.hh
/// @brief Pango stretch C++ wrapper class.
///
/// AttrStretch wraps the stretch attribute (ATTR_STRETCH).

class AttrStretch: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrStretch(Stretch stretch = STRETCH_NORMAL);
	///< Construct a new font stretch attribute.
	/// @param stretch The stretch.

/// @}
/// @name Accessors
/// @{

	Stretch stretch() const;
	///< Returns the stretch.

/// @}
/// @name Methods
/// @{

	void set_stretch(Stretch stretch);
	///< Sets the stretch.
	///< @param stretch The new stretch.
	
/// @}
};

/// @class AttrUnderline attributes.hh xfc/pango/attributes.hh
/// @brief Pango underline C++ wrapper class.
///
/// AttrUnderline wraps the underline attribute (ATTR_UNDERLINE).

class AttrUnderline: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrUnderline(Underline underline = UNDERLINE_SINGLE);
	///< Construct a new underline-style attribute.
	/// @param underline The underline style.

/// @}
/// @name Accessors
/// @{

	Underline underline() const;
	///< Returns the underline style.

/// @}
/// @name Methods
/// @{

	void set_underline(Underline underline);
	///< Sets the underline style.
	/// @param underline The underline style.

/// @}
};

/// @class AttrStrikethrough attributes.hh xfc/pango/attributes.hh
/// @brief Pango strikethrough C++ wrapper class.
///
/// AttrStrikethrough wraps the strikethrough attribute (ATTR_STRIKETHROUGH).

class AttrStrikethrough: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrStrikethrough(bool strikethrough = true);
	///< Construct a new font strike-through attribute.
	///< @param strikethrough Set <EM>true</EM> if the text should be struck-through.

/// @}
/// @name Accessors
/// @{

	bool strikethrough() const;
	///< Returns true if the text is struck-through.

/// @}
/// @name Methods
/// @{

	void set_strikethrough(bool strikethrough);
	///< Sets whether the text should be struck-through.
	///< @param strikethrough Set <EM>true</EM> if the text should be struck-through.

/// @}
};

/// @class AttrRise attributes.hh xfc/pango/attributes.hh
/// @brief Pango rise C++ wrapper class.
///
/// AttrRise wraps the rise attribute (ATTR_RISE).

class AttrRise: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrRise(int rise);
	///< Construct a new baseline displacement attribute.
	///< @param rise The amount that the text should be displaced vertically, in 10'000ths of an em.
	///<
	///< Positive rise values displace the text upwards.

/// @}
};

/// @class AttrFontDesc attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrFontDesc C++ wrapper class.
///
/// AttrFontDesc wraps the font description attribute (ATTR_FONT_DESC).

class AttrFontDesc : public Attribute
{
public:
/// @name Constructors
/// @{

	AttrFontDesc(const FontDescription& desc);
	///< Construct a new font description attribute. 
	///< @param desc The FontDescription.
	///<
	///< This attribute allows the setting of family, style, weight,
	///< variant, stretch, and size simultaneously.

/// @}
/// @name Accessors
/// @{

	PangoAttrFontDesc* pango_attr_font_desc() const;
	///< Get a pointer to the PangoAttrFontDesc structure.
	
	Pointer<FontDescription> font_description() const;
	///< Returns a smart pointer to the font description.

/// @}
/// @name Methods
/// @{

	void set_font_description(const FontDescription& desc);
	///< Set the font description.
	
/// @}
};

/// @class AttrShape attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrShape C++ wrapper class.
///
/// AttrShape wraps the shape attribute (ATTR_SHAPE).

class AttrShape : public Attribute
{
public:
/// @name Constructors
/// @{

	AttrShape(const Rectangle& ink_rect, const Rectangle& logical_rect);
	///< Construct a new shape attribute.
	///< @param ink_rect The ink rectangle to assign to each character.
	///< @param logical_rect The logical rectangle assign to each character.
	///<
	///< A shape is used to impose a particular ink and logical rect on the
	///< result of shaping a particular glyph. This might be used, for instance,
	///< for embedding a picture or a widget inside a Pango::Layout.

/// @}
/// @name Accessors
/// @{

	PangoAttrShape* pango_attr_shape() const;
	///< Get a pointer to the PangoAttrShape structure.

	const Rectangle& ink_rect() const;
	///< Returns the ink rectangle.

	const Rectangle& logical_rect() const;
	///< Returns the logical rectangle.

/// @}
/// @name Methods
/// @{

	void set_rects(const Rectangle& ink_rect, const Rectangle& logical_rect);
	///< Sets the ink and logical rectangles.
	///< @param ink_rect The ink rectangle.
	///< @param logical_rect The logical rectangle.

	void set_ink_rect(const Rectangle& rect);
	///< Sets the ink rectangle.
	///< @param rect The ink rectangle.

	void set_ink_rect(int x, int y, int width, int height);
	///< Sets the ink rectangle.
	///< @param x The X coordinate of the upper-left corner of the ink rectangle.
	///< @param y The Y coordinate of the upper-left corner of the ink rectangle.
	///< @param width The width of the ink rectangle.
	///< @param height The height of the ink rectangle.

	void set_logical_rect(const Rectangle& rect);
	///< Sets the logical rectangle.
	///< @param rect The logical rectangle.

	void set_logical_rect(int x, int y, int width, int height);
	///< Sets the logical rectangle.
	///< @param x The X coordinate of the upper-left corner of the logical rectangle.
	///< @param y The Y coordinate of the upper-left corner of the logical rectangle.
	///< @param width The width of the logical rectangle.
	///< @param height The height of the logical rectangle.
	
/// @}
};

/// @class AttrFloat attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrFloat C++ wrapper class.
///
/// AttrFloat is the base class for float attributes such as Scale.

class AttrFloat : public Attribute
{
protected:
/// @name Constructors
/// @{

	explicit AttrFloat(PangoAttribute *attr, bool copy);
	///< Construct a new float attribute from an existing float PangoAttribute.
	///< @param attr A float PangoAttribute.
	///< @param copy Set <EM>true</EM> if a copy of <EM>attr</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>attr</EM> is copied. If false <EM>attr</EM>
	///< is assumed to be a valid float attribute that must be freed. Either way AttrFloat
	///< will own the PangoAttribute and free it when it's no longer required.

/// @}

public:
// Accessors
	PangoAttrFloat* pango_attr_float() const;
	///< Get a pointer to the PangoAttrFloat structure.
	
	double value() const;
	///< Returns the float value.

// Methods
	void set_value(double value);
	///< Sets the float value.
};

/// @class AttrScale attributes.hh xfc/pango/attributes.hh
/// @brief Pango scale C++ wrapper class.
///
/// AttrScale wraps the font size scale factor attribute (ATTR_SCALE).

class AttrScale : public AttrFloat
{
public:
/// @name Constructors
/// @{

	explicit AttrScale(double scale_factor);
	///< Construct a new font size scale attribute.
	///< @param scale_factor The factor to scale the font by.
	///<
	///< The base font for the affected text will have its size multiplied by <EM>scale_factor</EM>.

/// @}
};

/// @class AttrFallback attributes.hh xfc/pango/attributes.hh
/// @brief Pango fallback C++ wrapper class.
///
/// AttrFallback wraps the fallback attribute (ATTR_FALLBACK).

class AttrFallback: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrFallback(bool enable_fallback);
	///< Construct a new font fallback attribute.
	///< @param enable_fallback Set <EM>true</EM> if we should fall back on other fonts
	///<                        for characters the active font is missing.
	///<
	///< If fallback is disabled, characters will only be used from the closest
	///< matching font on the system. No fallback will be done to other fonts on the
	///< system that might contain the characters in the text.

/// @}
};

/// @class AttrLetterSpacing attributes.hh xfc/pango/attributes.hh
/// @brief Pango letter spacing C++ wrapper class.
///
/// AttrLetterSpacing wraps the letter spacing attribute (ATTR_LETTER_SPACING).

class AttrLetterSpacing: public AttrInt
{
public:
/// @name Constructors
/// @{

	explicit AttrLetterSpacing(int letter_spacing);
	///< Construct a new letter spacing attribute.
	///< @param letter_spacing The amount of extra space to add between graphemes of the text, in Pango units. 

 /// @}
};

/// @class AttrUnderlineColor attributes.hh xfc/pango/attributes.hh
/// @brief Pango underline color C++ wrapper class.
///
/// AttrUnderlineColor wraps the underline color attribute (ATTR_UNDERLINE_COLOR).

class AttrUnderlineColor: public AttrColor
{
public:
/// @name Constructors
/// @{

	explicit AttrUnderlineColor(unsigned short red, unsigned short green, unsigned short blue);
	///< Construct a new underline color attribute.
	///< @param red The red value (ranging from 0 to 65535).
	///< @param green The green value.
	///< @param blue The blue value.
	///<
	///< This attribute modifies the color of underlines. If not set, underlines
	///< will use the foreground color.
 
 /// @}
};

/// @class AttrStrikethroughColor attributes.hh xfc/pango/attributes.hh
/// @brief Pango strikethrough color C++ wrapper class.
///
/// AttrStrikethroughColor wraps the strikethrough color attribute (ATTR_STRIKETHROUGH_COLOR).

class AttrStrikethroughColor: public AttrColor
{
public:
/// @name Constructors
/// @{

	explicit AttrStrikethroughColor(unsigned short red, unsigned short green, unsigned short blue);
	///< Construct a new strikethrough color attribute.
	///< @param red The red value (ranging from 0 to 65535).
	///< @param green The green value.
	///< @param blue The blue value.
	///<
	///< This attribute modifies the color of strikethrough lines. If not set, strikethrough
	///< lines will use the foreground color.
 
 /// @}
};

/// @class AttrStipple attributes.hh xfc/pango/attributes.hh
/// @brief A GdkPangoAttrStipple C++ wrapper class.
///
/// AttrStipple is a Pango text attribute containing a stipple bitmap
/// to be used when rendering the text.

class AttrStipple : public Attribute
{
public:
/// @name Constructors
///
	explicit AttrStipple(Gdk::Bitmap& stipple);
	///< Constructs a new attribute containing a stipple bitmap to be used when rendering the text.
	///< @param stipple A bitmap to be set as the stipple bitmap.

/// @}
/// @name Accessors
/// @{

	GdkPangoAttrStipple* gdk_pango_attr_stipple() const;
	///< Get a pointer to the GdkPangoAttrStipple structure.

	Gdk::Bitmap* stipple() const;
	///< Returns the stipple bitmap. This bitmap is owned by the attribute
	///< and will unreferenced when the attribute is destroyed.

/// @}
};

/// @class AttrEmbossed attributes.hh xfc/pango/attributes.hh
/// @brief A GdkPangoAttrEmbossed C++ wrapper class.
///
/// AttrEmbossed is a Pango text attribute containing an embossed bitmap
/// to be used when rendering the text. This type is specific to GDK and
/// therefore has a Pango::AttrType of ATTR_INVALID.

class AttrEmbossed : public Attribute
{
public:
/// @name Constructors
/// @{

	explicit AttrEmbossed(bool embossed);
	///< Construct a new attribute containing an embossed bitmap to be used when rendering the text.
	///< @param embossed Set <EM>true</EM> if the bitmap is to be set as embossed.

/// @}
/// @name Accessors
/// @{
	GdkPangoAttrEmbossed* gdk_pango_attr_embossed() const;
	///< Get a pointer to the GdkPangoAttrEmbossed structure.

	bool embossed() const;
	///< Returns true if the bitmap is set as embossed.

/// @}
};

/// @class AttrIterator attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrIterator C++ wrapper class.
///
/// AttrIterator is used to represent an iterator through an AttrList.
/// A new iterator is created with Pango::AttrList::get_iterator().
/// Once the iterator is created, it can be advanced through the style
/// changes in the text using next(). At each style change, the range
/// of the current style segment and the attributes currently in effect
/// can be queried.

class AttrIterator : public Xfc::Object
{
	PangoAttrIterator *iterator_;

public:
/// @name Constructors
/// @{

	explicit AttrIterator(PangoAttrIterator *iterator);
	///< Constructs a new attribute iterator from an existing PangoAttrIterator.
	///< @param iterator A PangoAttrIterator.
	///<
	///< AttrIterator takes over the ownership of the PangoAttrIterator and
	///< calls pango_attr_iterator_destroy() when it's no longer required.

	AttrIterator(const AttrIterator& src);
	///< Copy constructor.
	///< @param src The source iterator.

	~AttrIterator();
	///< Destructor.

	AttrIterator& operator=(const AttrIterator& src);
	///< Assignment operator.
	///< @param src The source iterator.

/// @}
/// @name Accessors
/// @{

	PangoAttrIterator* pango_attr_iterator() const;
	///< Get a pointer to the PangoAttrIterator structure.

	operator PangoAttrIterator* () const { return this ? pango_attr_iterator() : 0; }
	///< Conversion operator; safely converts an AttrIterator to a PangoAttrIterator pointer.

	int start_index() const;
	///< Returns the start index of the current range.

	int end_index() const;
	///< Returns the end index of the current range.

	void range(int *start, int *end) const;
	///< Get the range of the current segment.
	///< @param start The location to store the start of the range.
	///< @param end The location to store the end of the range.

	Pointer<Attribute> get(AttrType type);
	///< Find the current attribute of a particular type at the iterator location. 
	///< @param type The type of attribute to find.
	///< @return The current attribute of the given type, or null if no attribute
	///< of that type applies to the current location.
	///<
	///< When multiple attributes of the same type overlap, the attribute whose
	///< range starts closest to the current location is used.

	void get_font(FontDescription& desc, PangoLanguage **language, std::vector<Pointer<Attribute> > *extra_attrs) const;
	///< Get the font and other attributes at the current iterator position.
	///< @param desc A FontDescription to fill in with the current values. 
	///< @param language If non-null, location to store the language tag for item, or null if none is found.
	///< @param extra_attrs If non-null, a vector in which to store a list of non-font attributes at the
	///< current position; only the highest priority value of each attribute will be added to this list.
	///<
	///< The family name in <EM>desc</EM> will be set by Pango using pango_font_description_set_family_static()
	///< using values from an attribute in the AttrList associated with the iterator, so if you plan to keep
	///< it around, you must call: desc.set_family(desc.get_family()).

	bool get_attrs(std::vector<Pointer<Attribute> >& attrs) const;
	///< Gets a list all attributes at the current position of the iterator.
	///< @param attrs A reference to a vector of Pointer<Attribute> to hold the list of attributes.
	///< @return <EM>true</EM> if the vector is not empty.

/// @}
/// @name Methods
/// @{
	bool next();
	///< Advance the iterator until the next change of style.
	///< @return <EM>false</EM> if the iterator is at the end of the list, otherwise <EM>true</EM>.

/// @}
};

/// @class AttrList attributes.hh xfc/pango/attributes.hh
/// @brief A PangoAttrList C++ wrapper class.
///
/// AttrList represents a list of attributes that apply to a section of text.
/// The attributes are, in general, allowed to overlap in an arbitrary fashion,
/// however, if the attributes are manipulated only through change(), the 
/// overlap between properties will meet stricter criteria.
///
/// Since the wrapped PangoAttrList structure is stored as a linear list, it
/// is not suitable for storing attributes for large amounts of text. In general,
/// you should not use a single AttrList for more than one paragraph of text.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class AttrList : public G::Boxed
{
public:
	typedef sigc::slot<bool, const Attribute&> AttrFilterSlot;
	///< Signature of the callback slot used by filter() to filter out
	///< a subset of attributes for a list.
	///< <B>Example:</B> Method signature for AttrFilterSlot.
	///< @code
	///< bool method(const Attibute& attr);
	///<
	///< // attr: A Pango::Attribute.
	///< // return: true if the attribute should be filtered out.
	///< @endcode

/// @name Constructors
/// @{

	AttrList();
	///< Constructs a new empty attribute list with a reference count of 1 that the caller owns.

	explicit AttrList(PangoAttrList *list);
	///< Constructs a new attribute list from an existing PangoAttrList.
	///< @param list A pointer to a PangoAttrList.
	///<
	///< The <EM>list</EM> can be a newly created PangoAttrList or an existing
	///< PangoAttrList. The AttrList object created is a temporary object. It doesn't
	///< take over the ownership of PangoAttrList and PangoAttrList is not freed by
	///< the destructor. The AttrList is created with a reference count of 1 that the
	///< caller owns.

	AttrList(PangoAttrList *list, bool copy);
	///< Constructs a new attribute list from an existing PangoAttrList.
	///< @param list A pointer to a PangoAttrList.
	///< @param copy Whether the AttrList object should make a copy of PangoAttrList or not.
	///<
	///< The <EM>list</EM> can be a newly created PangoAttrList or an existing PangoAttrList.
	///< If <EM>copy</EM> is true AttrList will make a copy of PangoAttrList. If <EM>copy</EM>
	///< is false AttrList wont make a copy but instead takes over the ownership of PangoAttrList.
	///< Either way, the destructor will free PangoAttrList when the AttrList object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap PangoAttrList objects in a C++ wrapper.
	///<
	///< The AttrList is created with a reference count of 1 that the caller owns.
	
	AttrList(const AttrList& src);
	///< Copy constructor.
	///< @param src The source attribute list.

	~AttrList();
	///< Destructor.

	AttrList& operator=(const AttrList& src);
	///< Assignment operator.
	///< @param src The source attribute list.

/// @}
/// @name Accessors
/// @{

	PangoAttrList* pango_attr_list() const;
	///< Get a pointer to the PangoAttrList structure.

	operator PangoAttrList* () const;
	///< Conversion operator; safely converts an AttrList to a PangoAttrList pointer.

	Pointer<AttrIterator> get_iterator() const;
	///< Creates an iterator initialized to the beginning of the list.
	///< @return A smart pointer to a new attribute iterator.
	///<
	///< The list must not be modified until the smart pointer has gone out of scope
	///< (i.e. the iterator has been destroyed).

/// @}
/// @name Methods
/// @{

	void insert(Attribute& attr, bool before = false);
	///< Insert the given <EM>attribute</EM> into the list.
	///< @param attr The attribute to insert. Ownership of this value is assumed by the list.
	///< @param before Set <EM>true</EM> if <EM>attr</EM> should be inserted before other attributes.
	///<
	///< If <EM>before</EM> is false <EM>attr</EM> will be inserted after all
	///< other attributes with a matching start_index. If <EM>before</EM> is true
	///< <EM>attr</EM> will be inserted before all other attributes with a matching
	///< start_index.

	void change(Attribute& attr);
	///< Insert the given attribute into the list.
	///< @param attr The attribute to insert. Ownership of this value is assumed by the list.
	///<
	///< It will replace any attributes of the same type on that segment
	///< and be merged with any adjoining attributes that are identical. This
	///< function is slower than insert() for creating an attribute list in
	///< order (potentially much slower for large lists). However, insert()
	///< is not suitable for continually changing a set of attributes since
	///< it never removes or combines existing attributes.

	void splice(AttrList& other, int pos, int length);
	///< This method splices the <EM>other</EM> attribute list into this list.
	///< @param other Another attribute list.
	///< @param pos The position in list at which to insert <EM>other</EM>.
	///< @param length The length of the spliced segment.
	///<
	///< This operation is equivalent to stretching every attribute that
	///< applies at position pos in list by an amount len, and then calling
	///< change() with a copy of each attribute in other in sequence (offset
	///< in position by pos).
	///<
	///< This operation proves useful for, for instance, inserting a preedit
	///< string in the middle of an edit buffer.
	///<
	///< <B>Note:</B> <EM>length</EM> must be specified since the attributes in
	///< <EM>other</EM> may only be present at some subsection of this range.

	Pointer<AttrList> filter(const AttrFilterSlot& slot);
	///< Given an AttrList and callback slot, this method removes any elements
	///< of list for which <EM>slot</EM> returns <EM>true</EM> and inserts them
	///< into a new list.
	///< @param slot A callback slot; returns <EM>true</EM> if an atttribute should be filtered out.
	///< @return A smart pointer to a newly allocated AttrList, or null if no attributes
	///< of the given types were found.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/attributes.inl>

#endif // XFC_PANGO_ATTRIBUTES_HH

