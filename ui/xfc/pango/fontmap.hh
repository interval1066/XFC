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

/// @file xfc/pango/fontmap.hh
/// @brief A PangoFontMap C++ wrapper interface.
///
/// Provides FontMap, an object that represents the set of fonts available for a particular rendering system.

#ifndef XFC_PANGO_FONTMAP_HH
#define XFC_PANGO_FONTMAP_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __PANGO_FONTMAP_H__
#include <pango/pango-fontmap.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

class Context;
class Font;
class FontDescription;
class FontFamily;
class Fontset;

/// @class FontMap fontmap.hh xfc/pango/fontmap.hh
/// @brief A PangoFontMap C++ wrapper class.
///
/// FontMap represents the set of fonts available for a particular rendering system.
/// This is a virtual object with implementations being specific to particular
/// rendering systems.

class FontMap : public G::Object
{
	friend class G::Object;

	FontMap(const FontMap&);
	FontMap& operator=(const FontMap&);

protected:
/// @name Constructors
/// @{

	explicit FontMap(PangoFontMap *fontmap, bool owns_reference = true);
	///< Construct a new FontMap from an existing PangoFontMap.
	///< @param fontmap A pointer to a PangoFontMap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>fontmap</EM> can be a newly created PangoFontMap or an existing
	///< PangoFontMap. (see G::Object::Object).

/// @}

public:
	typedef PangoFontMap CObjectType;

/// @name Constructors
/// @{
	
	virtual ~FontMap();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	PangoFontMap* pango_font_map() const;
	///< Get a pointer to the PangoFontMap structure.

	operator PangoFontMap* () const;
	///< Conversion operator; safely converts a FontMap to a PangoFontMap pointer.

/// @}
/// @name Methods
/// @{

	Font* load_font(Context *context, const FontDescription& desc);
	///< Load the font in the fontmap that is the closest match for desc.
	///< @param context The Context the font will be used with.
	///< @param desc A FontDescription describing the font to load.
	///< @return The font loaded, or null if no font matched.

	Fontset* load_fontset(Context *context, const FontDescription& desc, PangoLanguage *language);
	///< Load a set of fonts in the fontmap that can be used to render a font matching desc.
	///< @param context The Context the font will be used with.
	///< @param desc A FontDescription describing the font to load.
	///< @param language A PangoLanguage the fonts will be used for.
	///< @return The fontset, or null if no font matched.

	bool list_families(std::vector<FontFamily*>& families) const;
	///< List all families for a fontmap.
	///< @param families A reference to a vector of FontFamily*  to hold the font families.
	///< @return <EM>true</EM> if the vector is not empty.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/fontmap.inl>

#endif // XFC_PANGO_FONTMAP_HH

