/*  XFC: Xfce Foundation Classes (User Interface Library)
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
 
/// @file xfc/atk/text.hh
/// @brief An AtkText C++ wrapper interface.
///
/// Provides Text, an interface implemented by components with text content.

#ifndef XFC_ATK_TEXT_HH
#define XFC_ATK_TEXT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_ATK_UTIL_HH
#include <xfc/atk/util.hh>
#endif

#ifndef __ATK_TEXT_H__
#include <atk/atktext.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Unichar;
}

namespace Atk {

/// @enum TextAttribute
/// Describes the text attributes supported.
/// Where appropriate each TextAttribute type lists all the possible values, in index order.
/// The first value is 0, the second value is 1, and so on. This is the index you need to
/// specify when constructing an Attribute.  For example, for boolean values "false" is 0
/// and "true" is 1. For wrap mode "none" is 0, "char" is 1, and "word" is 2. You should
/// be able to work the rest out.

enum TextAttribute
{
	TEXT_ATTR_INVALID = ATK_TEXT_ATTR_INVALID,
	///< Invalid attribute.

	TEXT_ATTR_LEFT_MARGIN= ATK_TEXT_ATTR_LEFT_MARGIN,
	///< The pixel width of the left margin.

	TEXT_ATTR_RIGHT_MARGIN = ATK_TEXT_ATTR_RIGHT_MARGIN,
	///< The pixel width of the right margin.

	TEXT_ATTR_INDENT = ATK_TEXT_ATTR_INDENT,
	///< The number of pixels that the text is indented.

	TEXT_ATTR_INVISIBLE = ATK_TEXT_ATTR_INVISIBLE,
	///< Either "false" or "true" indicating whether text is visible or not.

	TEXT_ATTR_EDITABLE = ATK_TEXT_ATTR_EDITABLE,
	///< Either  "false" or "true" indicating whether text is editable or not.

	TEXT_ATTR_PIXELS_ABOVE_LINES = ATK_TEXT_ATTR_PIXELS_ABOVE_LINES,
	///< Pixels of blank space to leave above each newline-terminated line.

	TEXT_ATTR_PIXELS_BELOW_LINES = ATK_TEXT_ATTR_PIXELS_BELOW_LINES,
	///< Pixels of blank space to leave below each newline-terminated line.

	TEXT_ATTR_PIXELS_INSIDE_WRAP = ATK_TEXT_ATTR_PIXELS_INSIDE_WRAP,
	///< Pixels of blank space to leave between wrapped lines inside the same
	///< newline-terminated line (paragraph).

	TEXT_ATTR_BG_FULL_HEIGHT = ATK_TEXT_ATTR_BG_FULL_HEIGHT,
	///< Either false" or "true" indicating whether to make the background color
	///< for each character the height of the highest font used on the current 
	///< line, or the height of the font used for the current character.

	TEXT_ATTR_RISE = ATK_TEXT_ATTR_RISE,
	///< Number of pixels that the characters are risen above the baseline.

	TEXT_ATTR_UNDERLINE = ATK_TEXT_ATTR_UNDERLINE,
	///< The underline style, either "none", "single", "double" or "low".

	TEXT_ATTR_STRIKETHROUGH = ATK_TEXT_ATTR_STRIKETHROUGH,
	///< Either "false" or "true" indicating whether the text is struck-through.

	TEXT_ATTR_SIZE = ATK_TEXT_ATTR_SIZE,
	///< The size of the characters.

	TEXT_ATTR_SCALE = ATK_TEXT_ATTR_SCALE,
	///< A string representation of a double indicating the scale of the characters.

	TEXT_ATTR_WEIGHT = ATK_TEXT_ATTR_WEIGHT,
	///< The weight of the characters.

	TEXT_ATTR_LANGUAGE = ATK_TEXT_ATTR_LANGUAGE,
	///< The language used.

	TEXT_ATTR_FAMILY_NAME = ATK_TEXT_ATTR_FAMILY_NAME,
	///< The font family name.

	TEXT_ATTR_BG_COLOR = ATK_TEXT_ATTR_BG_COLOR,
	///< The background color; an RGB value of the format "%u,%u,%u".

	TEXT_ATTR_FG_COLOR = ATK_TEXT_ATTR_FG_COLOR,
	///< The foreground color; an RGB value of the format "%u,%u,%u".

	TEXT_ATTR_BG_STIPPLE = ATK_TEXT_ATTR_BG_STIPPLE,
	///< Either "false" or "true" indicating if a Gdk::Bitmap is set for stippling the background color.

	TEXT_ATTR_FG_STIPPLE = ATK_TEXT_ATTR_FG_STIPPLE,
	///< Either "false" or "true" indicating if a Gdk::Bitmap is set for stippling the foreground color.

	TEXT_ATTR_WRAP_MODE = ATK_TEXT_ATTR_WRAP_MODE,
	///< The wrap mode of the text, if any; possible values are "none", "char" or "word".

	TEXT_ATTR_DIRECTION = ATK_TEXT_ATTR_DIRECTION,
	///< The direction of the text, if set; possible values are "none", "ltr" or "rtl".

	TEXT_ATTR_JUSTIFICATION = ATK_TEXT_ATTR_JUSTIFICATION,
	///< The justification of the text, if set; possible values are "left", "right", "center" or "fill".

	TEXT_ATTR_STRETCH = ATK_TEXT_ATTR_STRETCH,
	///< The stretch of the text, if set; possible values are "ultra_condensed", "extra_condensed",
	///< "condensed", "semi_condensed", "normal", "semi_expanded", "expanded", "extra_expanded" or
	///< "ultra_expanded".
		
	TEXT_ATTR_VARIANT = ATK_TEXT_ATTR_VARIANT,
	///< The capitalization variant of the text, if set; possible values are "normal" or "small_caps".

	TEXT_ATTR_STYLE = ATK_TEXT_ATTR_STYLE,
	///< The slant style of the text, if set; possible values are "normal", "oblique" or "italic".

	TEXT_ATTR_LAST_DEFINED  = ATK_TEXT_ATTR_LAST_DEFINED
	///< Not a valid text attribute, used for finding the end of the enumeration.
};

/// @enum TextBoundary
/// Specifies text boundary types to use when retrieving regions of text with
/// get_text_after_offset(), get_text_at_offset() and get_text_before_offset().

enum TextBoundary
{
	TEXT_BOUNDARY_CHAR = ATK_TEXT_BOUNDARY_CHAR, ///< Use character boundaries.
	TEXT_BOUNDARY_WORD_START = ATK_TEXT_BOUNDARY_WORD_START, ///< Use word start boundaries.
	TEXT_BOUNDARY_WORD_END = ATK_TEXT_BOUNDARY_WORD_END, ///< Use word end boundaries.
	TEXT_BOUNDARY_SENTENCE_START = ATK_TEXT_BOUNDARY_SENTENCE_START, ///< Use sentence start boundaries.
	TEXT_BOUNDARY_SENTENCE_END = ATK_TEXT_BOUNDARY_SENTENCE_END, ///< Use sentence end boundaries.
	TEXT_BOUNDARY_LINE_START = ATK_TEXT_BOUNDARY_LINE_START, ///< Use line start boundaries.
	TEXT_BOUNDARY_LINE_END = ATK_TEXT_BOUNDARY_LINE_END ///< Use line end boundaries.
};

/// @enum TextClipType
/// Describes the type of clipping required.

enum TextClipType
{
	TEXT_CLIP_NONE = ATK_TEXT_CLIP_NONE, ///< No clipping to be done.
	TEXT_CLIP_MIN = ATK_TEXT_CLIP_MIN, ///< Text clipped by min coordinate is omitted.
	TEXT_CLIP_MAX = ATK_TEXT_CLIP_MAX, ///< Text clipped by max coordinate is omitted.
	ATK_TEXT_CLIP_BOTH = TEXT_CLIP_MAX ///< Only text fully within mix/max bound is retained.
};

/// @name TextAttibute Methods
/// @{

TextAttribute text_attribute_register(const String& name);
///< Associate name with a new TextAttribute.
///< @param name A name string.
///< @return The new TextAttribute associated with <EM>name</EM>.

String text_attribute_get_name(TextAttribute attr);
///< Gets the name corresponding to the TextAttribute
///< @param attr The TextAttribute whose name is required.
///< @return A string containing the name.

TextAttribute text_attribute_for_name(const String& name);
///< Get the TextAttribute type corresponding to a text attribute <EM>name</EM>.
///< @param name A string which is the (non-localized) name of a TextAttribute.
///< @return The TextAttribute enumerated type corresponding to the specified name,
///< or TEXT_ATTR_INVALID if no matching text attribute is found.

String text_attribute_get_value(TextAttribute attr, int index);
///< Gets the value for the index of the text attribute <EM>attr</EM>.
///< @param attr The TextAttribute for which a value is required.
///< @param index The index of the required value.
///< @return A String containing the value, or a null String if there are no values maintained for <EM>attr</EM>.

/// @}

/// @class Attribute text.hh xfc/atk/text.hh
/// @brief A AtkAttribute C++ wrapper class.
///
/// Attribute is a string name/value pair representing a text attribute.

class Attribute
{
	AtkAttribute attrib_;

public:
/// @name Constructors
/// @{

	Attribute();
	///< Construct an empty attribute.

	Attribute(TextAttribute attr, int index);
	///< Construct an new attribute from a TextAttribute and a <EM>value</EM> index.
	///< @param attr The TextAttribute whose name will be used.
	///< @param index The index of the string value required.
	///<
	///< This is a convenience constructor that calls text_attribute_get_name()
	///< and text_attribute_get_value() for you. The <EM>index</EM> is the index of
	///< the required value for those values which are strings.

	Attribute(TextAttribute attr, const String& value);
	///< Construct an new attribute from a TextAttribute and a <EM>value</EM> string.
	///< @param attr The TextAttribute whose name will be used.
	///< @param value A string representation of the value.
	///<
	///< This is a convenience constructor that calls text_attribute_get_name()
	///< for you. Call text_attribute_get_value() for those values which are strings.
	///< For values which are numbers, the string representation of the number should
	///< be in <EM>value</EM>.

 	Attribute(const String& name, const String& value);
	///< Construct an new attribute from an attribute <EM>name</EM> and a <EM>value</EM> string.
	///< @param name The attribute name (call text_attribute_get_name()).
	///< @param value The value of the attribute, represented as a string.
	///<
	///< Call text_attribute_get_value() for those values which are strings.
	///< For values which are numbers, the string representation of the number
	///< should be in <EM>value</EM>.

	Attribute(const AtkAttribute& attrib);
	///< Construct an new attribute from an existing AtkAttribute.
	///< @param attrib An AtkAttribute.

	Attribute(const Attribute& src);
	///< Copy constructor.
	///< @param src The source attribute.

	~Attribute();
	///< Destructor

	Attribute& operator=(const Attribute& src);
	///< Assignment operator.
	///< @param src The source attribute.

/// @}
/// @name Accessors
/// @{

	AtkAttribute* atk_attribute() const;
	///< Get a pointer to the AtkAttribute structure.

	TextAttribute attr() const;
	///< Returns the TextAttribute enumerated type corresponding to the attibute name,
	///< or TEXT_ATTR_INVALID if no matching text attribute is found.

	String name() const;
	///< Returns the name of the attribute.

	String value() const;
	///< Returns the string representation of the attribute value.

/// @}
/// @name Methods
/// @{

	void set(const String& name, const String& value);
	///< Sets the name and value for the attribute.
	///< @param name The attribute name (call text_attribute_get_name()).
	///< @param value The value of the attribute, represented as a string.
	///<
	///< Call text_attribute_get_value() for those values which are strings.
	///< For values which are numbers, the string representation of the number
	///< should be in <EM>value</EM>.

/// @}
};

/// @class TextRectangle text.hh xfc/atk/text.hh
/// @brief An AtkTextRectangle C++ wrapper class.
///
/// TextRectangle represents an object used to store a rectangle used by Atk::Text.
/// It uses default copy, assignment and destruction.

class TextRectangle
{
	AtkTextRectangle rectangle_;

public:
/// @name Constructors
/// @{

	TextRectangle();
	///< Construct a with its x, y, width and height set to 0;

	TextRectangle(int x, int y, int width, int height);
	///< Construct a new text rectangle.
	///< @param x The X coordinate of the text rectangle.
	///< @param y The Y coordinate of the text rectangle.
	///< @param width The width of the text rectangle.
	///< @param height The height of the text rectangle.

	TextRectangle(const AtkTextRectangle& rectangle);
	///< Construct a new text rectangle from an existing AtkTextRectangle.
	///< @param rectangle A AtkTextRectangle.

/// @}
/// @name Accessors
/// @{

	AtkTextRectangle* atk_text_rectangle() const;
	///< Get a pointer to the AtkTextRectangle structure.

	operator AtkTextRectangle* () const;
	///< Conversion operator; safely converts a TextRectangle to a AtkTextRectangle pointer.

	int x() const;
	///< Returns the X coordinate of the top-left corner of the text rectangle.

	int y() const;
	///< Returns the Y coordinate of the top-left corner of the text rectangle.

	int width() const;
	///< Returns the width of the text rectangle.

	int height() const;
	///< Returns the height of the text rectangle.

/// @}
/// @name Methods
/// @{

	void set(int x, int y, int width, int height);
	///< Sets the position and size of the text rectangle.
	///< @param x The new X coordinate of the text rectangle.
	///< @param y The new Y coordinate of the text rectangle.
	///< @param width The new width of the text rectangle.
	///< @param height The new height of the text rectangle.

/// @}
};

/// @class TextRange text.hh xfc/atk/text.hh
/// @brief A AtkTextRange C++ wrapper class.
///
/// TextRange is an object used to describe a text range.

class TextRange
{
	AtkTextRange range_;

public:
/// @name Constructors
/// @{

	TextRange(const AtkTextRange& range);
	///< Construct a new TextRange from  an exisitng AtkTextRange object.

	~TextRange();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	AtkTextRange* atk_text_rectangle() const;
	///< Get a pointer to the AtkTextRange structure.

	TextRectangle bounds() const;
	///< Gets the bounding rectangle for the text range.
	///< @return A TextRectangle giving the bounds of the text range.

	int start_offset() const;
	///< Gets the start offset of the text range.
	///< @return The start offset.

	int end_offset() const;
	///< Gets the end offset of the text range.
	///< @return The end offset.

	const char* content() const;
	///< Gets the text in the text range.
	///< A text string.

/// @}
};

/// @class Text text.hh xfc/atk/text.hh
/// @brief A AtkText C++ wrapper class.
///
/// Text should be implemented by Atk::Objects on behalf of widgets that have text content
/// which is either attributed or otherwise non-trivial. Atk::Objects whose text content is
/// simple, unattributed, and very brief may expose that content via Atk::Object::get_name()
/// instead; however if the text is editable, multi-line, typically longer than three or four
/// words, attributed, selectable, or if the object already uses the 'name' ATK property for
/// other information, the Text interface should be used to expose the text content. In the
/// case of editable text content, EditableText (a subtype of the Text interface) should be
/// implemented instead.
///
/// Text provides not only traversal facilities and change notification for text content,
/// but also caret tracking and glyph bounding box calculations. Note that the text strings
/// are exposed as UTF-8, and are therefore potentially multi-byte, and caret-to-byte offset
/// mapping makes no assumptions about the character length; also bounding box glyph-to-offset
/// mapping may be complex for languages which use ligatures.

class Text  : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Text();
	///< Constructs a new Text object.
	
	virtual ~Text () = 0;
	///< Destructor.
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, int, int> TextChangedSignalType;
	typedef G::SignalProxy<TypeInstance, TextChangedSignalType> TextChangedSignalProxy;
	static const TextChangedSignalType text_changed_signal;
	///< Text changed signal (see signal_text_change()). Calls a slot with the signature:
	///< @code
	///< void function(int position, int length);
	///< // position: The position of the insertion or deletion.
	///< // length: The length of the text inserted or deleted.
	///< @endcode

	typedef G::Signal<void, int> TextCaretMovedSignalType;
	typedef G::SignalProxy<TypeInstance, TextCaretMovedSignalType> TextCaretMovedSignalProxy;
	static const TextCaretMovedSignalType text_caret_moved_signal;
	///< Text caret moved signal (see signal_text_caret_moved()). Calls a slot with the signature:
	///< @code
	///< void function(int location);
	///< // location: The new position of the text caret.
	///< @endcode

	typedef G::Signal<void> TextSelectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, TextSelectionChangedSignalType> TextSelectionChangedSignalProxy;
	static const TextSelectionChangedSignalType text_selection_changed_signal;
	///< Text selection changed signal (see signal_text_selection_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> TextAttributesChangedSignalType;
	typedef G::SignalProxy<TypeInstance, TextAttributesChangedSignalType> TextAttributesChangedSignalProxy;
	static const TextAttributesChangedSignalType text_attributes_changed_signal;
	///< Text attributes changed signal (see signal_text_attributes_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	AtkText* atk_text() const;
	///< Get a pointer to the AtkText structure.

	operator AtkText* () const;
	///< Conversion operator; safely converts a Text to an AtkText pointer.

	String get_text(int start_offset, int end_offset) const;
	///< Gets the specified text.
	///< @param start_offset The start position.
	///< @param end_offset The end position.
	///< @return The text from <EM>start_offset</EM> up to, but not including <EM>end_offset</EM>.

	G::Unichar get_character_at_offset(int offset) const;
	///< Gets the character at the specified offset.
	///< @param offset The character position.
	///< @return The character at <EM>offset</EM>.

	String get_text_after_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const;
	///< Gets the specified text.
	///< @param offset The position
	///< @param boundary_type A TextBoundary.
	///< @param start_offset The location for the start offset of the returned string.
	///< @param end_offset The location for the end offset of the returned string.
	///< @return The text after offset bounded by the specified boundary_type.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_CHAR the character after the offset is returned.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_START the returned string is from the word start
	///< after the offset to the next word start. The returned string will contain the word after the
	///< offset if the offset is inside a word or if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_END the returned string is from the word end
	///< at or after the offset to the next work end. The returned string will contain the word 
	///< after the offset if the offset is inside a word and will contain the word after the word
	///< after the offset if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_SENTENCE_START the returned string is from the
	///< sentence start after the offset to the next sentence start. The returned string will
	///< contain the sentence after the offset if the offset is inside a sentence or if the 
	///< offset is not inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_SENTENCE_END the returned string is from the
	///< sentence end at or after the offset to the next sentence end. The returned string 
	///< will contain the sentence after the offset if the offset is inside a sentence and 
	///< will contain the sentence after the sentence after the offset if the offset is not
	///< inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_START the returned string is from the
	///< line start after the offset to the next line start. 
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_END the returned string is from the
	///< line end at or after the offset to the next line start.

	String get_text_at_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const;
	///< Gets the specified text.
	///< @param offset The position
	///< @param boundary_type A TextBoundary.
	///< @param start_offset The location for the start offset of the returned string.
	///< @param end_offset The location for the end offset of the returned string.
	///< @return The text after offset bounded by the specified boundary_type.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_CHAR the character at the offset is returned.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_START the returned string is from the word
	///< start at or before the offset to the word start after the offset. The returned string will
	///< contain the word at the offset if the offset is inside a word and will contain the word 
	///< before the offset if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_END the returned string is from the word
	///< end before the offset to the word end at or after the offset. The returned string will 
	///< contain the word at the offset if the offset is inside a word and will contain the word
	///< after to the offset if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM>e is TEXT_BOUNDARY_SENTENCE_START the returned string is from
	///< the sentence start at or before the offset to the sentence start after the offset. The 
	///< returned string will contain the sentence at the offset if the offset is inside a sentence 
	///< and will contain the sentence before the offset if the offset is not inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is ATK_TEXT_BOUNDARY_SENTENCE_END the returned string is from
	///< the sentence end before the offset to the sentence end at or after the offset. The returned
	///< string will contain the sentence at the offset if the offset is inside a sentence and will
	///< contain the sentence after the offset if the offset is not inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_START the returned string is from the line
	///< start at or before the offset to the line start after the offset.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_END the returned string is from the
	///< line end before the offset to the line end at or after the offset.

	String get_text_before_offset(int offset, TextBoundary boundary_type, int *start_offset, int *end_offset) const;
	///< Gets the specified text.
	///< @param offset The position
	///< @param boundary_type A TextBoundary.
	///< @param start_offset The location for the start offset of the returned string.
	///< @param end_offset The location for the end offset of the returned string.
	///< @return The text after offset bounded by the specified boundary_type.
	///<
	///< If the boundary_type is TEXT_BOUNDARY_CHAR the character before the offset is returned.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_START the returned string is from the word
	///< start before the word start before the offset to the word start before the offset. The 
	///< returned string will contain the word before the offset if the offset is inside a word and
	///< will contain the word before the word before the offset if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_WORD_END the returned string is from the word
	///< end before the word end at or before the offset to the word end at or before the offset.
	///< The returned string will contain the word before the offset if the offset is inside a word
	///< or if the offset is not inside a word.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_SENTENCE_START the returned string is from the
	///< sentence start before the sentence start before the offset to the sentence start before
	///< the offset. The returned string will contain the sentence before the offset if the offset
	///< is inside a sentence and will contain the sentence before the sentence before the offset
	///< if the offset is not inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_SENTENCE_END the returned string is from the
	///< sentence end before the sentence end at or before the offset to the sentence end at or
	///< before the offset. The returned string will contain the sentence before the offset if
	///< the offset is inside a sentence or if the offset is not inside a sentence.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_START the returned string is from
	///< the line start before the line start at or before the offset to the line start ar or
	///< before the offset.
	///<
	///< If <EM>boundary_type</EM> is TEXT_BOUNDARY_LINE_END the returned string is from the 
	///< line end before the line end before the offset to the line end before the offset.

	int get_caret_offset() const;
	///< Returns the offset position of the caret (cursor).
	
	void get_character_extents(int offset, int *x, int *y, int *width, int *height, CoordType coords) const;
	///< Given an offset, the x, y, width, and height values are filled appropriately.
	///< @param offset A character position.
	///< @param x The location for the x-position of the character at <EM>position</EM>, or null.
	///< @param y The location for the y-position of the character at <EM>position</EM>, or null.
	///< @param width The location for the width of the character at <EM>position</EM>, or null.
	///< @param height The location for the height of the character at <EM>position</EM>, or null.
	///< @param coords Specify whether coordinates are relative to the screen or the widget window.

	std::vector<Attribute> get_run_attributes(int offset, int *start_offset, int *end_offset) const;
	///< Gets a list which consists of the attributes explicitly set at the position
	///< <EM>offset</EM> in the text. 
	///< @param offset The offset at which to get the attributes.
	///< @param start_offset The address to put the start offset of the range, or null.
	///< @param end_offset The address to put the end offset of the range, or null.
	///< @return A vector of Attribute which contains the attributes explicitly set at <EM>offset</EM>.
	///<
	///< <EM>start_offset</EM> and <EM>end_offset</EM> are set to the start and end
	///< of the range around offset where the attributes are invariant. See the enum 
	///< Atk::TextAttribute for the types of text attributes that can be returned. Note
	///< that other attributes may also be returned.

	std::vector<Attribute> get_default_attributes() const;
	///< Gets a list which consists of the default values of attributes for the text.
	///< @return A vector of Attribute which contains the default values of the attributes at <EM>offset</EM>.
	///<
	///< See the enum Atk::TextAttribute for types of text attributes that can be returned.
	///< Note that other attributes may also be returned.
	
	int get_character_count() const;
	///< Gets the character count for the text.
	///< @return The number of characters in the text.

	int get_offset_at_point(int x, int y, CoordType coords) const;
	///< Gets the offset of the character located at coordinates x and y.
 	///< @param x The x-position of a character.
	///< @param y The y-position of a character.
	///< @param coords Specify whether the coordinates are relative to the screen or widget window.
	///< @return The offset to the character which is located at the specified x and y coordinates.
	///<
	///< <EM>x</EM> and <EM>y</EM> are interpreted as being relative to the screen
	///< or this widget's window, depending on coords.

	int get_n_selections() const;
	///< Gets the number of selected regions.
	///< @return The number of selected regions, or -1 if a failure occurred.

	String get_selection(int selection_num, int *start_offset, int *end_offset) const;
	///< Gets the text from the specified selection.
	///< @param selection_num The selection number. 
	///< @param start_offset The location for the start position of the selected region.
	///< @param end_offset The location for the end position of the selected region.
	///< @return The selected text.
	///<
	///< Selected regions are assigned numbers that correspond to how far the region is
	///< from the start of the text. The selected region closest to the beginning of the text
	///< region is assigned the number 0, etc. Note that adding, moving or deleting a selected
	///< region can change the numbering.

	TextRectangle get_range_extents(int start_offset, int end_offset, CoordType coord_type);
	///< Get the bounding box for text within the specified range.
	///< @param start_offset The offset of the first text character in the range.
	///< @param end_offset The offset of the text character after the last character in the range.
	///< @param coord_type Specifies whether coordinates are relative to the screen or widget window.
	///< @return A TextRectangle filled with the boundaries of the text range.

	void get_range_extents(int start_offset, int end_offset, CoordType coord_type, TextRectangle& rect);
	///< Get the bounding box for text within the specified range.
	///< @param start_offset The offset of the first text character in the range.
	///< @param end_offset The offset of the text character after the last character in the range.
	///< @param coord_type Specifies whether coordinates are relative to the screen or widget window.
	///< @param rect A TextRectangle which is filled in by this method.

	std::vector<TextRange> get_bounded_ranges(const TextRectangle& rect, CoordType coord_type,
	                                          TextClipType x_clip_type, TextClipType y_clip_type);
	///< Get the ranges of text in the specified bounding box.
	///< @param rect A TextRectagle giving the dimensions of the bounding box.
	///< @param coord_type Specifies whether coordinates are relative to the screen or widget window.
	///< @param x_clip_type Specifies the horizontal clip type.
	///< @param y_clip_type Specifies the vertical clip type.
	///< @return A vector of TextRange.

/// @}
/// @name Methods
/// @{

	bool add_selection(int start_offset, int end_offset);
	///< Adds the selection bounded by the specified offsets.
	///< @param start_offset The start position of the selected region.
	///< @param end_offset The end position of the selected region.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.

	bool remove_selection(int selection_num);
	///< Removes the specified selection.
	///< @param selection_num The selection number.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.
	///<
	///< Selected regions are assigned numbers that correspond to how far the region is
	///< from the start of the text. The selected region closest to the beginning of the text
	///< region is assigned the number 0, etc. Note that adding, moving or deleting a selected
	///< region can change the numbering.

	bool set_selection(int selection_num, int start_offset, int end_offset);
	///< Changes the start and end offset of the specified selection.
	///< @param selection_num The selection number.
	///< @param start_offset The new start position of the selection.
	///< @param end_offset The new end position of the selection.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.
	///<
	///< Selected regions are assigned numbers that correspond to how far the region is
	///< from the start of the text. The selected region closest to the beginning of the text
	///< region is assigned the number 0, etc. Note that adding, moving or deleting a selected
	///< region can change the numbering.

	bool set_caret_offset(int offset);
	///< Sets the caret (cursor) position to the specified offset.
	///< @param offset A character position.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.

/// @}
/// @name Signal Proxies
/// @{

	const TextChangedSignalProxy signal_text_changed();
	///< Connect to the text_changed_signal; emitted when text is inserted or deleted.

	const TextCaretMovedSignalProxy signal_text_caret_moved();
	///< Connect to the text_caret_moved_signal; emitted when the text caret is moved.

	const TextSelectionChangedSignalProxy signal_text_selection_changed();
	///< Connect to the text_selection_changed_signal; emitted when the text selection changes.

	const TextAttributesChangedSignalProxy signal_text_attributes_changed();
	///< Connect to the text_attributes_changed_signal; emitted when the text attributes change.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/text.inl>

#endif // XFC_ATK_TEXT_HH

