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
 
/// @file xfc/pango/glyph.hh
/// @brief A PangoGlyphString C++ wrapper interface.
///
/// Provides GlyphString, an objects for storing information about glyphs.

#ifndef XFC_PANGO_GLYPH_HH
#define XFC_PANGO_GLYPH_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_PANGO_TYPES_HH
#include <xfc/pango/types.hh>
#endif

#ifndef __PANGO_GLYPH_H__
#include <pango/pango-glyph.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {
	
class Analysis;
class Font;
class Rectangle;

/// GlyphUnit is a convenient typedef for PangoGlyphUnit.
/// The GlyphUnit type is used to store dimensions within Pango. Dimensions are stored
/// in 1/PANGO_SCALE of a device unit. (A device unit might be a pixel for screen display,
/// or a point on a printer.) PANGO_SCALE is currently 1024, and is unlikely to change,
/// but you should not depend on its exact value. The PANGO_PIXELS() macro can be used
/// to convert from glyph units into device units with correct rounding.

typedef PangoGlyphUnit GlyphUnit;

/// @class GlyphGeometry glyph.hh xfc/pango/glyph.hh
/// @brief A PangoGlyphGeometry C++ wrapper class.
///
/// GlyphGeometry contains the width and positioning information for a single glyph.
/// Distances are in 1/64ths of a point.

class GlyphGeometry
{
	PangoGlyphGeometry geometry_;

public:
	PangoGlyphGeometry* pango_glyph_geometry() const;
	///< Get a pointer to the PangoGlyphGeometry structure.

	GlyphUnit width() const;
	///< Returns the logical width of the character.

	GlyphUnit x_offset() const;
	///< Returns the horizontal offset from nominal character position.

	GlyphUnit y_offset() const;
	///< Returns the vertical offset from nominal character position.
};

/// @class GlyphVisAttr glyph.hh xfc/pango/glyph.hh
/// @brief A PangoGlyphVisAttr C++ wrapper class.
///
/// GlyphVisAttr is used to communicate information between the shaping phase
/// and the rendering phase. It's contents are still evolving.

class GlyphVisAttr
{
	PangoGlyphVisAttr attr_;

public:
	PangoGlyphVisAttr* pango_glyph_vis_attr() const;
	///< Get a pointer to the PangoGlyphVisAttr structure.

	bool is_cluster_start() const;
	///< Returns <EM>true</EM> for the first logical glyph in each cluster. Clusters are stored
	///< in visual order, within the cluster, glyphs are always ordered in logical order, since
	///< visual order is meaningless; that is, in Arabic text, accent glyphs follow the glyphs
	///< for the base character.
};

/// @class GlyphInfo glyph.hh xfc/pango/glyph.hh
/// @brief A PangoGlyphInfo C++ wrapper class.
///
/// GlyphInfo represents a single glyph together with positioning information and visual attributes.

class GlyphInfo
{
	PangoGlyphInfo info_;

public:
	PangoGlyphInfo* pango_glyph_info() const { return const_cast<PangoGlyphInfo*>(&info_); }
	///< Get a pointer to the PangoGlyphInfo structure.

	Glyph glpyh() const;
	///< Returns the glyph itself.

	const GlyphGeometry& geometry() const;
	///< Returns the glyph geometry object containing width and positioning information for the glyph.

	const GlyphVisAttr& attr() const;
	///< Returns the GlyphVisAttr which is used to communicate information
	///< between the shaping phase and the rendering phase.
};

/// @class GlyphString glyph.hh xfc/pango/glyph.hh
/// @brief A PangoGlyphString C++ wrapper class.
///
/// GlyphString is used to store strings of glyphs with geometry and visual attribute information.
/// The storage for the glyph information is owned by the structure which simplifies memory management.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class GlyphString : public G::Boxed
{
public:
/// @name Constructors
/// @{

	GlyphString();
	///< Constructs a new glyph string with a reference count of 1 that the caller owns.

	GlyphString(const char *text, int length, const Analysis& analysis);
	///< Given a segment of text and the corresponding Analysis structure returned
	///< from Pango::Context::itemize(), convert the characters in <EM>text</EM> into glyphs.
	///< @param text The text to process.
	///< @param length The length of the text in bytes.
	///< @param analysis The Analysis structure from Pango::Context::Itemize().
	///<
	///< You may also pass in only a substring of the item from Pango::Context::itemize().
	///< This constructor calls pango_shape(). There is no shape() method. The GlyphString is 
	///< created with a reference count of 1 that the caller owns.

	GlyphString(const String& text, const Analysis& analysis);
	///< Given a segment of text and the corresponding Analysis structure returned
	///< from Pango::Context::itemize(), convert the characters in <EM>text</EM> into glyphs.
	///< @param text The text to process.
	///< @param analysis The Analysis structure from Pango::Context::Itemize().
	///<
	///< You may also pass in only a substring of the item from Pango::Context::itemize().
	///< This constructor calls pango_shape(). There is no shape() method. The GlyphString is 
	///< created with a reference count of 1 that the caller owns.

	explicit GlyphString(PangoGlyphString *string);
	///< Constructs a new glyph string from an existing PangoGlyphString.
	///< @param string A pointer to a PangoGlyphString.
	///<
	///< The <EM>string</EM> can be a newly created PangoGlyphString or an existing
	///< PangoGlyphString. The glyph string object created is a temporary object.
	///< It doesn't take over the ownership of PangoGlyphString and PangoGlyphString
	///< is not freed by the destructor. The GlyphString is created with a reference count
	///< of 1 that the caller owns.

	GlyphString(PangoGlyphString *string, bool copy);
	///< Constructs a new glyph string from an existing PangoGlyphString.
	///< @param string A pointer to a PangoGlyphString.
	///< @param copy Whether the GlyphString object should make a copy of PangoGlyphString or not.
	///<
	///< The <EM>string</EM> can be a newly created PangoGlyphString or an existing
	///< PangoGlyphString. If <EM>copy</EM> is true GlyphString will make a copy
	///< of PangoGlyphString. If <EM>copy</EM> is false GlyphString wont make
	///< a copy but instead takes over the ownership of PangoGlyphString. Either way,
	///< the destructor will free PangoGlyphString when the GlyphString object is
	///< destroyed. This constructor is used by G::Boxed::wrap() to wrap PangoGlyphString
	///< objects in a C++ wrapper. The GlyphString is created with a  reference count of 1
	///< that the caller owns.

	GlyphString(const GlyphString& src);
	///< Copy constructor.
	///< @param src The source GlyphString.

	virtual ~GlyphString();
	///< Destructor.

	GlyphString& operator=(const GlyphString& src);
	///< Assignment operator.
	///< @param src The source GlyphString.

/// @}
/// @name Accessors
/// @{

	PangoGlyphString* pango_glyph_string() const;
	///< Get a pointer to the PangoGlyphString structure.

	operator PangoGlyphString* () const;
	///< Conversion operator; safely converts a GlyphString to a PangoGlyphString pointer.

	int size() const;
	///< Returns the number of glyphs in the string.
	
	std::vector<GlyphInfo> glyphs() const;
	///< Returns a vector of GlyphInfo that holds one GlyphInfo object for each glyph in the string.

	int* log_clusters() const;
	///< For each glyph, returns the byte index of the starting character for the cluster.
	///< The indices are relative to the start of the text corresponding to the GlyphString.

	void extents(const Font& font, Rectangle *ink_rect, Rectangle *logical_rect, int start = 0, int end = -1) const;
	///< Compute the logical and ink extents of a sub-portion the glyph string,
	///< or the entire glyph string.
	///< @param font A Font.
	///< @param ink_rect The rectangle used to store the extents of the glyph string as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the glyph string,
	///<                    or null to indicate that the result is not needed.
	///< @param start The start index in bytes, or 0 for the start of the string.
	///< @param end The end index in bytes, or -1 for the end of the string.
	///<
	///< The extents are relative to the start of the glyph string range (the origin of
	///< their coordinate system is at the start of the range, not at the start of the
	///< entire glyph string).
	///<
	///< See the documentation for Pango::Font::get_glyph_extents() for details
	///< about the interpretation of the rectangles. 

	void get_logical_widths(const char *text, int length, int embedding_level, std::vector<int>& logical_widths) const;
	///< Given a GlyphString resulting from pango_shape() and the corresponding text,
	///< determine the screen width corresponding to each character.
	///< @param text The text corresponding to the glyphs.
	///< @param length The length of the text in bytes.
	///< @param embedding_level The embedding level of the string.
	///< @param logical_widths A reference to a vector of int to be filled in with the resulting character widths.
	///<
	///< When multiple characters compose a single cluster, the width of the entire cluster is
	///< divided equally among the characters.

	void get_logical_widths(const String& text, int embedding_level, std::vector<int>& logical_widths) const;
	///< Given a GlyphString resulting from pango_shape() and the corresponding text,
	///< determine the screen width corresponding to each character.
	///< @param text The text corresponding to the glyphs.
	///< @param embedding_level The embedding level of the string.
	///< @param logical_widths A reference to a vector of int to be filled in with the resulting character widths.
	///<
	///< When multiple characters compose a single cluster, the width of the entire cluster is
	///< divided equally among the characters.

/// @}
/// @name Methods
/// @{

	void set_size(int length);
	///< Resize a glyph string to the given length.
	///< @param length The new length of the string.

	int index_to_x(const char *text, int length, const Analysis& analysis, int index, bool trailing);
	///< Converts from a character position to an x position.
	///< @param text The text for the run.
	///< @param length The length of the text in bytes.
	///< @param analysis The analysis information returned from Pango::Context::itemize().
	///< @param index The byte index within text.
	///< @param trailing Whether we should compute the result for the beginning or end of the character.
	///< @return The x position.
	///<
	///< X position is measured from the left edge of the run. Character positions are
	///< computed by dividing up each cluster into equal portions.

	int index_to_x(const String& text, const Analysis& analysis, int index, bool trailing);
	///< Converts from a character position to an x position.
	///< @param text The text for the run.
	///< @param analysis The analysis information returned from Pango::Context::itemize().
	///< @param index The byte index within text.
	///< @param trailing Whether we should compute the result for the beginning or end of the character.
	///< @return The x position.
	///<
	///< X position is measured from the left edge of the run. Character positions are
	///< computed by dividing up each cluster into equal portions.

	void x_to_index(const char *text, int length, const Analysis& analysis, int x_pos, int *index, bool *trailing);
	///< Convert from an x offset to character position.
	///< @param text The text for the run.
	///< @param length The length of the text in bytes.
	///< @param analysis The analysis information returned from Pango::Context::itemize().
	///< @param x_pos The x offset (in GlyphUnit).
	///< @param index The location to store calculated byte index within the text.
	///< @param trailing The location to store whether the user clicked on the leading
	///<                 or trailing edge of the character.
	///<
	///< Character positions are computed by dividing up each cluster into equal portions.
	///< In scripts where positioning within a cluster is not allowed (such as Thai), the
	///< returned value may not be a valid cursor position; the caller must combine the result
	///< with the logical attributes for the text to compute the valid cursor position.

	void x_to_index(const String& text, const Analysis& analysis, int x_pos, int *index, bool *trailing);
	///< Convert from an x offset to character position.
	///< @param text The text for the run.
	///< @param analysis The analysis information returned from Pango::Context::itemize().
	///< @param x_pos The x offset (in GlyphUnit).
	///< @param index The location to store calculated byte index within the text.
	///< @param trailing The location to store whether the user clicked on the leading
	///<                 or trailing edge of the character.
	///<
	///< Character positions are computed by dividing up each cluster into equal portions.
	///< In scripts where positioning within a cluster is not allowed (such as Thai), the
	///< returned value may not be a valid cursor position; the caller must combine the result
	///< with the logical attributes for the text to compute the valid cursor position.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/glyph.inl>

#endif // XFC_PANGO_GLYPH_HH

