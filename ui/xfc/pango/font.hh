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
 
/// @file xfc/pango/font.hh
/// @brief A C++ wrapper interface for Pango fonts.
///
/// Provides objects representing abstract fonts, such as FontDescription, Font, FontFace and FontFamily.

#ifndef XFC_PANGO_FONT_HH
#define XFC_PANGO_FONT_HH

#ifndef XFC_PANGO_TYPES_HH
#include <xfc/pango/types.hh>
#endif

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __PANGO_FONT_H__
#include <pango/pango-font.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

class Coverage;

/// @enum Pango::Style
/// Specifies the various slant styles possible for a font.

enum Style
{
	STYLE_NORMAL = PANGO_STYLE_NORMAL, ///< The font is upright.
	STYLE_OBLIQUE = PANGO_STYLE_OBLIQUE, ///< The font is slanted, but in a roman style.
	STYLE_ITALIC = PANGO_STYLE_ITALIC ///< The font is slanted in an italic style.
};

/// @enum Variant
///< Specifies the capitalization variant of the font.

enum Variant
{
	VARIANT_NORMAL = PANGO_VARIANT_NORMAL,
	///< A normal font.

	VARIANT_SMALL_CAPS = PANGO_VARIANT_SMALL_CAPS
	///< A font with the lower case characters replaced by smaller variants of the capital characters.
};

/// @enum Weight
/// Specifies the weight (boldness) of a font. This is a numerical value 
/// ranging from 100 to 900, but there are some predefined values:

enum Weight
{
	WEIGHT_ULTALIGHT = PANGO_WEIGHT_ULTRALIGHT, ///< The ultralight weight (= 200).
	WEIGHT_LIGHT = PANGO_WEIGHT_LIGHT, ///< The light weight (=300).
	WEIGHT_NORMAL = PANGO_WEIGHT_NORMAL, ///< The default weight (= 400).
	WEIGHT_SEMIBOLD = PANGO_WEIGHT_SEMIBOLD, ///< The semi bold weight (= 600).
	WEIGHT_BOLD = PANGO_WEIGHT_BOLD, ///< The bold weight (= 700).
	WEIGHT_ULTRABOLD = PANGO_WEIGHT_ULTRABOLD, ///< The ultrabold weight (= 800).
	WEIGHT_HEAVY = PANGO_WEIGHT_HEAVY ///< The heavy weight (= 900).
};

/// @enum Stretch
/// Specifies the width of the font relative to other designs within a family.

enum Stretch
{
	STRETCH_UTLRA_CONDENSED = PANGO_STRETCH_ULTRA_CONDENSED, ///< Ultra condensed width.
	STRETCH_EXTRA_CONDENSED = PANGO_STRETCH_EXTRA_CONDENSED, ///< Extra condensed width.
	STRETCH_CONDENSED = PANGO_STRETCH_CONDENSED,  ///< Condensed width.
	STRETCH_SEMI_CONDENSED = PANGO_STRETCH_SEMI_CONDENSED, ///< Semi condensed width.
	STRETCH_NORMAL = PANGO_STRETCH_NORMAL, ///< Normal width.
	STRETCH_SEMI_EXPANDED = PANGO_STRETCH_SEMI_EXPANDED, ///< Semi expanded width.
	STRETCH_EXPANDED = PANGO_STRETCH_EXPANDED, ///< Expanded width.
	STRETCH_EXTRA_EXPANDED = PANGO_STRETCH_EXTRA_EXPANDED, ///< Extra expanded width.
	STRETCH_ULTRA_EXPANDED = PANGO_STRETCH_ULTRA_EXPANDED ///< Ultra expanded width.
};

/// @enum FontMask
/// The bit flags in a FontMask correspond to fields in a FontDescription that have been set.

enum FontMask
{
	FONT_MASK_FAMILY = PANGO_FONT_MASK_FAMILY, ///< The font family is specified.
	FONT_MASK_STYLE = PANGO_FONT_MASK_STYLE, ///< The font style is specified.
	FONT_MASK_VARIANT = PANGO_FONT_MASK_VARIANT, ///< T font variant is specified.
	FONT_MASK_WEIGHT = PANGO_FONT_MASK_WEIGHT, ///< The font weight is specified.
	FONT_MASK_STRETCH = PANGO_FONT_MASK_STRETCH, ///< The font stretch is specified.
	FONT_MASK_SIZE = PANGO_FONT_MASK_SIZE ///< The font size is specified.
};

/// FontMaskField holds one or more values from the Pango::FontMask enumeration OR'd together.

typedef unsigned int FontMaskField;

/// @class FontDescription font.hh xfc/pango/font.hh
/// @brief A PangoFontDescription C++ wrapper class.
///
/// FontDescription represents the description of an ideal font. These objects
/// are used both to list what fonts are available on the system and also for
/// specifying the characteristics of a font to load.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class FontDescription : public G::Boxed
{
public:
/// @name Constructors
/// @{

	FontDescription();
	///< Construct a new font description with all fields unset. The FontDescription
	///< is created with a reference count of 1 that the caller owns.

	FontDescription(const String& desc);
	///< Creates a new font description from a string representation.
	///< @param desc A string representation of a font description.
	///<
	///< See to_string() for a description of the format of the string representation.
	///< The family list in the string description will only have a terminating comma if
	///< the last word of the list is a valid style option.
	///<
	///< The FontDescription is created with a reference count of 1 that the caller owns.

	FontDescription(const String& family, int size, Style style = STYLE_NORMAL, Weight weight = WEIGHT_NORMAL);
	///< Construct a new font description with the specifed <EM>family, size, style and weight</EM>.
	///< @param family A string representing the family name.
	///< @param size The size for the font description in pango units (see set_size()).
	///< @param style The style for the font description.
	///< @param weight The weight for the font description.
	///<
	///< The FontDescription is created with a reference count of 1 that the caller owns.

	FontDescription(PangoFontDescription *desc);
	///< Construct a new font description from an existing PangoFontDescription.
	///< @param desc A pointer to a PangoFontDescription.
	///<
	///< The <EM>desc</EM> can be a newly created PangoFontDescription or an existing
	///< PangoFontDescription. The font description object created is a temporary object.
	///< It doesn't take over the ownership of PangoFontDescription and PangoFontDescription
	///< is not freed by the destructor.
	///<
	///< The FontDescription is created with a reference count of 1 that the caller owns.

	FontDescription(PangoFontDescription *desc, bool copy);
	///< Construct a new font description from an existing PangoFontDescription.
	///< @param desc A pointer to a PangoFontDescription.
	///< @param copy Whether the FontDescription object should make a copy of PangoFontDescription or not.
	///<
	///< The <EM>desc</EM> can be a newly created PangoFontDescription or an existing
	///< PangoFontDescription. If <EM>copy</EM> is true FontDescription will make a copy
	///< of PangoFontDescription. If <EM>copy</EM> is false FontDescription wont make
	///< a copy but instead takes over the ownership of PangoFontDescription. Either way,
	///< the destructor will free PangoFontDescription when the FontDescription object is
	///< destroyed. This constructor is used by G::Boxed::wrap() to wrap PangoFontDescription
	///< objects in a C++ wrapper.
	///<
	///< The FontDescription is created with a reference count of 1 that the caller owns.

	FontDescription(const FontDescription& src);
	///< Copy constructor.
	///< @param src The source FontDescription.

	virtual ~FontDescription();
	///< Destructor.

	FontDescription& operator=(const FontDescription& src);
	///< Assignment operator.
	///< @param src The source FontDescription.

/// @}
/// @name Accessors
/// @{

	PangoFontDescription* pango_font_description() const;
	///< Get a pointer to the PangoFontDescription structure.

	operator PangoFontDescription* () const;
	///< Conversion operator; safely converts a FontDescription to a PangoFontDescription pointer.

	String get_family() const;
	///< Gets the family name field of a font description (see set_family()).
	///< @return The family name field, or null if not previously set.

	Style get_style() const;
	///< Gets the style field of a font description (see set_style()).
	///< @return The style field for the font description. 
	///<
	///< Use get_set_fields() to find out if the field was explicitely set or not.

	Variant get_variant() const;
	///< Gets the variant field of a font description (see set_variant()).
	///< @return The variant field for the font description. 
	///<
	///< Use get_set_fields() to find out if the field was explicitely set or not.

	Weight get_weight() const;
	///< Gets the weight field of a font description (see set_weight()).
	///< @return The weight field for the font description. 
	///<
	///< Use get_set_fields() to find out if the field was explicitely set or not.

	Stretch get_stretch() const;
	///< Gets the stretch field of a font description (see set_stretch()).
	///< @return The stretch field for the font description. 
	///<
	///< Use get_set_fields() to find out if the field was explicitely set or not.
	
	int get_size() const;
	///< Gets the size field of a font description.
	///< @return The size field for the font description in points or device units. 
	///<
	///< You must call get_size_is_absolute() to find out which is the case. This
	///< method returns 0 if the size field has not previously been set. You can 
	///< use get_set_fields() to find out if the field was explicitely set or not. 	

	bool get_size_is_absolute() const;
	///< Determines whether the size of the font is in points or device units
	///< (see set_size() and set_absolute_size().
	///< @return Whether the the size for the font description is in points or device units. 
	///< 
	///< Use get_set_fields() to find out if the size field of the font description was explicitely set or not.	
	
	FontMaskField get_set_fields() const;
	///< Determines which fields in a font description have been set.
	///< @return A bitmask with Pango::FontMask bits set corresponding to the fields in desc that have been set.

	bool equal(const FontDescription& other) const;
	///< Compares this font description with <EM>other</EM> for equality.
	///< @param other: Another FontDescription.
	///< @return <EM>true</EM> if the two font descriptions are proveably identical.
	///<
	///< Two font descriptions may result in identical fonts being loaded, but still compare false.

	bool operator==(const FontDescription& other) const;
	///< Equality operator; compares this font description with <EM>other</EM> for equality.
	///< @param other: Another FontDescription.
	///< @return <EM>true</EM> if the two font descriptions are proveably identical.
	///<
	///< Two font descriptions may result in identical fonts being loaded, but still compare false.

	bool operator!=(const FontDescription& other) const;
	///< Inequality operator; compares this font description with <EM>other</EM> for inequality.
	///< @param other: Another FontDescription.
	///< @return <EM>true</EM> if the two font descriptions are not identical.
	///<
	///< Two font descriptions may result in identical fonts being loaded, but still compare false.

/// @}
/// @name Methods
/// @{

	unsigned int hash() const;
	///< Computes a hash of a font description object suitable to be used, 
	///< for example, as an argument to g_hash_table_new().
	///< @return The hash value.

	String to_string() const;
	///< Creates a string representation of the font description.
	///< @return The string representation.
	///<
	///< The string representation is in the form "[FAMILY-LIST] [STYLE-OPTIONS] [SIZE]",
	///< where FAMILY-LIST is a comma separated list of families optionally terminated by a comma,
	///< STYLE_OPTIONS is a whitespace separated list of words where each WORD describes one of
	///< style, variant, weight, or stretch, and SIZE is an decimal number (size in points). Any
	///< one of the options may be absent. If FAMILY-LIST is absent, then the family_name field
	///< of the resulting font description will be initialized to null. If STYLE-OPTIONS is missing,
	///< then all style options will be set to the default values. If SIZE is missing, the size
	///< in the resulting font description will be set to 0.

	String to_filename() const;
	///< Creates a filename representation of a font description.
	///< @return A string that can be used as a filename.
	///<
	///< The filename is identical to the result from calling to_string(), but with underscores
	///< instead of characters that are untypical in filenames, and in lower case only.

	void set_family(const char *family);
	void set_family(const String& family);
	///< Sets the family name field of a font description.
	///< @param family A string representing the family name.
	///<
	///< The family name represents a family of related font styles, and will resolve
	///< to a particular FontFamily. In some uses of FontDescription, it is also possible
	///< to use a comma separated list of family names for this field.

	void set_style(Style style);
	///< Sets the style field of a font description. 
	///< @param style The style for the font description.
	///<
	///< The Pango::Style enumeration describes whether the font is slanted and the manner
	///< in which it is slanted; it can be either STYLE_NORMAL, STYLE_ITALIC, or STYLE_OBLIQUE.
	///< Most fonts will either have a italic style or an oblique style, but not both, and font
	///< matching in Pango will match italic specifications with oblique fonts and vice-versa
	///< if an exact match is not found.

	void set_variant(Variant variant);
	///< Sets the variant field of a font description. 
	///< @param variant The variant type for the font description.
	///<
	///< The Variant can either be VARIANT_NORMAL or VARIANT_SMALL_CAPS.

	void set_weight(Weight weight);
	///< Sets the weight field of a font description. 
	///< @param weight The weight for the font description.
	///<
	///< The weight field specifies how bold or light the font should be. In addition to the
	///< values of the Pango::Weight enumeration, other intermediate numeric values are possible.

	void set_stretch(Stretch stretch);
	///< Sets the stretch field of a font description. 
	///< @param stretch The stretch for the font description.
	///<
	///< The stretch field specifies how narrow or wide the font should be.
	
	void set_size(int size);
	///< Sets the size field of a font description in fractional points. 
	///< @param size The size for the font description in points, scaled by PANGO_SCALE.
	///<
	///< This is mutually exclusive with set_absolute_size(). As an example, a size value
	///< of 10 * PANGO_SCALE is a 10 point font. The conversion factor between points and
	///< device units depends on system configuration and the output device. For screen 
	///< display, a logical DPI of 96 is common, in which case a 10 point font corresponds
	///< to a 10 * (96 / 72) = 13.3 pixel font. Use set_absolute_size() if you need a 
	///< particular size in device units.	
	
	void set_absolute_size(double size);
	///< Sets the size field of a font description, in device units. 
	///< @param size The new size, in pango units. 
	///<	
	///< This is mutually exclusive with set_size(). There are PANGO_SCALE Pango units
	///< in one device unit. For an output backend where a device unit is a pixel, a 
	///< size value of 10 * PANGO_SCALE gives a 10 pixel font.
	
	void unset_fields(FontMaskField to_unset);
	///< Unsets some of the fields in a font description. 
	///< @param to_unset The bitmask of Pango::FontMask fields in the desc to unset.
	///<
	///< Note that this merely marks the fields cleared, it does not clear the settings
	///< for those fields.
	
	void merge(const FontDescription& desc_to_merge, bool replace_existing);
	///< Merges the fields that are set in desc_to_merge into the fields in the font description.
	///< @param desc_to_merge The font description to merge from.
	///< @param replace_existing If true, replace fields in the font description with the corresponding
	///<                         values from <EM>desc_to_merge</EM>, even if they are already exist.
	///<
	///< If <EM>replace_existing</EM> is false, only fields in desc that are not already
	///< set are affected. If true, then fields that are already set will be replaced as well.

	bool better_match(const FontDescription& new_match, const FontDescription *old_match = 0) const;
	///< Determines if the style attributes of <EM>new_match</EM> are a closer match
	///< for the font description than <EM>old_match</EM>, or if old_match is null, 
	///< determines if <EM>new_match</EM> is a match at all. 
	///< @param new_match A FontDescription.
	///< @param old_match A FontDescription, or null.
	///<
	///< Approximate matching is done for weight and style; other attributes must match exactly.

/// @}
};

/// @class FontMetrics font.hh xfc/pango/font.hh
/// @brief A PangoFontMetrics C++ wrapper class.
///
/// FontMetrics structure holds the overall metric information for a font. 

class FontMetrics : public G::Boxed
{
public:
/// @name Constructors
/// @{

	explicit FontMetrics(PangoFontMetrics *metrics);
	///< Construct a new font metrics from an existing PangoFontMetrics.
	///< @param metrics A pointer to a PangoFontMetrics.
	///<
	///< The <EM>metrics</EM> can be a newly created PangoFontMetrics or an existing
	///< PangoFontMetrics. The font metrics object created is a temporary object.
	///< It doesn't take over the ownership of PangoFontMetrics and PangoFontMetrics
	///< is not freed by the destructor.

	FontMetrics(PangoFontMetrics *metrics, bool copy);
	///< Construct a new font metrics from an existing PangoFontMetrics.
	///< @param metrics A pointer to a PangoFontMetrics.
	///< @param copy Whether the FontMetrics object should make a copy of PangoFontMetrics or not.
	///<
	///< The <EM>metrics</EM> can be a newly created PangoFontMetrics or an existing
	///< PangoFontMetrics. If <EM>copy</EM> is true FontMetrics will make a copy of 
	///< PangoFontMetrics. If <EM>copy</EM> is false FontMetrics wont make a copy but
	///< instead takes over the ownership of PangoFontMetrics. Either way, the destructor
	///< will free PangoFontMetrics when the FontMetrics object is destroyed. This 
	///< constructor is used by G::Boxed::wrap() to wrap PangoFontMetrics objects in a
	///< C++ wrapper.

	FontMetrics(const FontMetrics& src);
	///< Copy constructor.
	///< @param src The source FontMetrics.

	virtual ~FontMetrics();
	///< Destructor.

	FontMetrics& operator=(const FontMetrics& src);
	///< Assignment operator.
	///< @param src The source FontMetrics.

/// @}
/// @name Accessors
/// @{

	PangoFontMetrics* pango_font_metrics() const;
	///< Get a pointer to the PangoFontMetrics structure.

	operator PangoFontMetrics* () const;
	///< Conversion operator; safely converts a FontMetrics to a PangoFontMetrics pointer.

	int get_ascent() const;
	///< Returns the ascent from a font metrics structure. 
	///< @return The ascent, in pango units. (1 point == PANGO_SCALE pango units.)
	///<
	///< The ascent is the distance from the baseline to the logical top of a line
	///< of text. (The logical top may be above or below the top of the actual drawn
	///< ink. It is necessary to lay out the text to figure where the ink will be.)

	int get_descent() const;
	///< Gets the descent from a font metrics structure. 
	///< @return The descent, in pango units. (1 point == PANGO_SCALE pango units.)
	///<
	///< The descent is the distance from the baseline to the logical bottom of a line of
	///< text. (The logical bottom may be above or below the bottom of the actual drawn ink.
	///< It is necessary to lay out the text to figure where the ink will be.)

	int get_approximate_char_width() const;
	///< Gets the approximate character width for the font metrics structure.
	///< @return The character width, in pango units. (1 point == PANGO_SCALE pango units.)
	///<
	///< This is merely a representative value useful, for example, for determining the initial
	///< size for a window. Actual characters in text will be wider and narrower than this.

	int get_approximate_digit_width() const;
	///< Gets the approximate digit width for the font metrics structure.
	///< @return The digit width, in pango units. (1 point == PANGO_SCALE pango units.)
	///<
	///< This is merely a representative value useful, for example, for determining the initial
	///< size for a window. Actual digits in text can be wider and narrower than this.

	int get_underline_position() const;
	///< Gets the suggested position to draw the underline. 
	///< @return The suggested underline position, in Pango units.	
	///<	
	///< The value returned is the distance above the baseline of the top of the underline. 
	///< Since most fonts have underline positions beneath the baseline, this value is 
	///< typically negative.

	int get_underline_thickness() const;
	///< Gets the suggested thickness to draw for the underline.
	///< @return The suggested underline thickness, in Pango units. 

	int get_strikethrough_position() const;
	///< Gets the suggested position to draw the strikethrough. 
	///< @return The suggested strikethrough position, in Pango units.
	///< 	
	///< The value returned is the distance above the baseline of the top of the strikethrough.

	int get_strikethrough_thickness() const;
	///< Gets the suggested thickness to draw for the strikethrough.
	///< @return The suggested strikethrough thickness, in Pango units.

/// @}
};

/// @class FontFace font.hh xfc/pango/font.hh
/// @brief A PangoFontFace C++ wrapper class.
///
/// The FontFace is used to represent a group of fonts with the same family,
/// slant, weight, width, but varying sizes. 

class FontFace : public G::Object
{
	friend class G::Object;

	FontFace(const FontFace&);
	FontFace& operator=(const FontFace&);
	
protected:
/// @name Constructors
/// @{
	
	explicit FontFace(PangoFontFace *face, bool owns_reference = true);
	///< Construct a new FontFace from an existing PangoFontFace.
	///< @param face A pointer to a PangoFontFace.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>face</EM> can be a newly created PangoFontFace or an existing
	///< PangoFontFace. (see G::Object::Object).

/// @}

public:
	typedef PangoFontFace CObjectType;

/// @name Constructors
/// @{
	
	virtual ~FontFace();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	PangoFontFace* pango_font_face() const;
	///< Get a pointer to the PangoFontFace structure.

	operator PangoFontFace* () const;
	///< Conversion operator; safely converts a FontFace to a PangoFontFace pointer.

	Pointer<FontDescription> describe() const;
	///< Returns the family, style, variant, weight and stretch of a font face.
	///< @return A smart pointer to newly-created FontDescription holding the description of the face.
	///<
	///< The size field of the resulting font description will be unset.
	
	String get_face_name() const;
	///< Gets a name representing the style of this face among the different faces
	///< in the font family for the face. 
	///< @return The face name for the face.
	///<
	///< This name is unique among all faces in the family and is suitable for displaying to users.
	
/// @}
/// @name Methods
/// @{

	bool list_sizes(std::vector<int>& sizes) const;
	///< List the available sizes for a font. 
	///< @param sizes A reference to a vector of int to hold the font sizes.
	///< @return <EM>true</EM> if the vector is not empty.
	///<	
	///< This is only applicable to bitmap fonts. For scalable fonts,
	///< stores null at the location in sizes. The sizes returned are in
	///< pango units and are sorted in ascending order.
	
/// @}
};

/// @class FontFamily font.hh xfc/pango/font.hh
/// @brief A PangoFontFamily C++ wrapper class.
///
/// FontFamily is used to represent a family of related font faces. 
/// The faces in a family share a common design, but differ in slant,
/// weight, width and other aspects.

class FontFamily : public G::Object
{
	friend class G::Object;

	FontFamily(const FontFamily&);
	FontFamily& operator=(const FontFamily&);
	
protected:
/// @name Constructors
/// @{

	explicit FontFamily(PangoFontFamily *family, bool owns_reference = true);
	///< Construct a new FontFamily from an existing PangoFontFamily.
	///< @param family A pointer to a PangoFontFamily.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>family</EM> can be a newly created PangoFontFamily or an existing
	///< PangoFontFamily. (see G::Object::Object).

/// @}

public:
	typedef PangoFontFamily CObjectType;

/// @name Constructors
/// @{

	virtual ~FontFamily();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	PangoFontFamily* pango_font_family() const;
	///< Get a pointer to the PangoFontFamily structure.

	operator PangoFontFamily* () const;
	///< Conversion operator; safely converts a FontFamily to a PangoFontFamily pointer.

	String get_name() const;
	///< Gets the name of the family. 
	///< @return The name of the family.
	///<
	///< The name is unique among all fonts for the font backend and can be used
	///< in a FontDescription to specify that a face from this family is desired.

	bool is_monospace() const;
	///< Determines if the font family is monospace.
	///< @return <EM>true</EM> if the family is monospace.
	///<
	///< A monospace font is a font designed for text display where the the characters
	///< form a regular grid. For Western languages this would mean that the advance width
	///< of all characters are the same, but this categorization also includes Asian fonts
	///< which include double-width characters: characters that occupy two grid cells. 
	///< G::Unichar::iswide() returns a result that indicates whether a character is 
	///< typically double-width in a monospace font. The best way to find out the grid-cell
	///< size is to call Pango::FontMetrics::get_approximate_digit_width(), since the results
	///< of Pango::FontMetrics::get_approximate_char_width() may be affected by double-width
	///< characters.

/// @}
/// @name Methods
/// @{
	
	bool list_faces(std::vector<FontFace*>& faces) const;
	///< Lists the different font faces that make up family. 
	///< @param faces A reference to a vector of FontFace* to hold the font faces.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The faces in a family share a common design, but differ in slant,
	///< weight, width and other aspects.

/// @}
};

/// @class Font font.hh xfc/pango/font.hh
/// @brief A PangoFont C++ wrapper class.
///
/// Font is used to represent a font in a rendering-system-independent matter. 

class Font : public G::Object
{
	friend class G::Object;

	Font(const Font&);
	Font& operator=(const Font&);
	
protected:
/// @name Constructors
/// @{
	
	explicit Font(PangoFont *font, bool owns_reference = true);
	///< Construct a new Font from an existing PangoFont.
	///< @param font A pointer to a PangoFont.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>font</EM> can be a newly created PangoFont or an existing
	///< PangoFont. (see G::Object::Object).

/// @}

public:
	typedef PangoFont CObjectType;

/// @name Constructors
/// @{
	
	virtual ~Font();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	PangoFont* pango_font() const;
	///< Get a pointer to the PangoFont structure.

	operator PangoFont* () const ;
	///< Conversion operator; safely converts a Font to a PangoFont pointer.

	Pointer<FontDescription> describe() const;
	///< Returns a description of the font.
	///< @return A smart pointer to a newly-allocated FontDescription object.

	Pointer<Coverage> get_coverage(PangoLanguage *language) const;
	///< Computes the coverage map for a given font and language tag.
	///< @param language The language tag.
	///< @return A smart pointer to a newly-allocated Coverage object.

	Pointer<FontMetrics> get_metrics(PangoLanguage *language = 0) const;
	///< Gets overall metric information for a font. 
	///< @param language The language tag used to determine which script to get the metrics for,
	///<                 or null to indicate to get the metrics for the entire font.
	///< @return A smart pointer to a FontMetrics object.
	///<
	///< Since the metrics may be substantially different for different scripts,
	///< a language tag can be provided to indicate that the metrics should be
	///< retrieved that correspond to the script(s) used by that language.

	void get_glyph_extents(Glyph glyph, Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Gets the logical and ink extents of a glyph within a font. 
	///< @param glyph The glyph index.
	///< @param ink_rect The rectangle used to store the extents of the glyph as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the glyph,
	///<                     or null to indicate that the result is not needed.
	///<
	///< The coordinate system for each rectangle has its origin at the base line
	///< and horizontal origin of the character with increasing coordinates extending
	///< to the right and down. The macros PANGO_ASCENT(), PANGO_DESCENT(), PANGO_LBEARING(),
	///< and PANGO_RBEARING can be used to convert from the extents rectangle to more
	///< traditional font metrics. The units of the rectangles are in 1/PANGO_SCALE 
	///< of a device unit.

/// @}
/// @name Methods
/// @{

	PangoEngineShape* find_shaper(unsigned int character_code, PangoLanguage *language);
	///< Finds the best matching shaper for a font for a particular language tag and character point.
	///< @param character_code The ISO-10646 character code.
	///< @param language The language tag.
	///< @return The best matching shaper.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/font.inl>

#endif // XFC_PANGO_FONT_HH

