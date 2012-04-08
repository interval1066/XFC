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
 
/// @file xfc/pango/fontset.hh
/// @brief A PangoFontset C++ wrapper interface.
///
/// Provides Fontset, an object that represents a set of Font to use when rendering text..

#ifndef XFC_PANGO_FONTSET_HH
#define XFC_PANGO_FONTSET_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __PANGO_FONT_H__
#include <pango/pango-font.h>
#endif

#ifndef __PANGO_FONTSET_H__
#include <pango/pango-fontset.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

class Font;
class FontMetrics;

/// @class Fontset fontset.hh xfc/pango/fontset.hh
/// @brief A PangoFontset C++ wrapper class.
///
/// A Fontset represents a set of Font to use when rendering text. It is the result
/// of resolving a FontDescription against a particular Context. It has operations
/// for finding the component font for a particular Unicode character, and for
/// finding a composite set of metrics for the entire fontset.

class Fontset : public G::Object
{
	friend class G::Object;

	Fontset(const Fontset&);
	Fontset& operator=(const Fontset&);

protected:
/// @name Constructors
/// @{
	
	explicit Fontset(PangoFontset *fontset, bool owns_reference = true);
	///< Construct a new Fontset from an existing PangoFontset.
	///< @param fontset A pointer to a PangoFontset.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>fontset</EM> can be a newly created PangoFontset or an existing
	///< PangoFontset. (see G::Object::Object).

/// @}

public:
	typedef PangoFontset CObjectType;
	
	typedef sigc::slot<bool, const Font&> ForeachSlot;
	///< Signature of the callback slot to be called for font in the fontset.
	///<
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< bool method(const Font& font);
	///<
	///< // font: A Pango::font.
	///< // return true to stop the iteration.
	///< @endcode

/// @name Constructors
/// @{

	virtual ~Fontset();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	PangoFontset* pango_fontset() const;
	///< Get a pointer to the PangoFontset structure.

	operator PangoFontset* () const;
	///< Conversion operator; safely converts a Fontset to a PangoFontset pointer.

	Pointer<Font> get_font(unsigned int wc) const;
	///< Returns the font in the fontset that contains the best glyph for the unicode character wc.
	///< @param wc A unicode character.
	///< @return A smart pointer to a Font.

	Pointer<FontMetrics> get_metrics() const;
	///< Get overall metric information for the fonts in the fontset.
	///< @return A smart pointer to a FontMetrics object.

/// @}
/// @name Methods
/// @{

	void foreach(const ForeachSlot& each);
	///< Iterates through all the fonts in the fontset, calling <EM>each</EM> for each one.
	///< @param each The callback slot.
	///< @return <EM>true</EM> to stops the iteration.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/fontset.inl>

#endif // XFC_PANGO_FONTSET_HH

