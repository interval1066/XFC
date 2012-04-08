/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  glyph.inl - Pango::GlyphString inline functions
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

/*  Pango::GlyphGeometry
 */

inline PangoGlyphGeometry*
Xfc::Pango::GlyphGeometry::pango_glyph_geometry() const
{
	return const_cast<PangoGlyphGeometry*>(&geometry_);
}

inline Xfc::Pango::GlyphUnit
Xfc::Pango::GlyphGeometry::width() const
{
	return geometry_.width;
}

inline Xfc::Pango::GlyphUnit
Xfc::Pango::GlyphGeometry::x_offset() const
{
	return geometry_.x_offset;
}

inline Xfc::Pango::GlyphUnit
Xfc::Pango::GlyphGeometry::y_offset() const
{
	return geometry_.y_offset;
}

/*  Pango::GlyphVisAttr
 */

inline PangoGlyphVisAttr*
Xfc::Pango::GlyphVisAttr::pango_glyph_vis_attr() const
{
	return const_cast<PangoGlyphVisAttr*>(&attr_);
}

inline bool
Xfc::Pango::GlyphVisAttr::is_cluster_start() const
{
	return attr_.is_cluster_start;
}

/*  Pango::GlyphInfo
 */

inline Xfc::Pango::Glyph
Xfc::Pango::GlyphInfo::glpyh() const
{
	return info_.glyph;
}

/*  Pango::GlyphString
 */

inline PangoGlyphString*
Xfc::Pango::GlyphString::pango_glyph_string() const
{
	return reinterpret_cast<PangoGlyphString*>(boxed_);
}

inline Xfc::Pango::GlyphString::operator PangoGlyphString* () const
{
	return this ? pango_glyph_string() : 0;
}

inline int
Xfc::Pango::GlyphString::size() const
{
	return pango_glyph_string()->num_glyphs;
}

inline int*
Xfc::Pango::GlyphString::log_clusters() const
{
	return pango_glyph_string()->log_clusters;
}

inline void
Xfc::Pango::GlyphString::set_size(int length)
{
	pango_glyph_string_set_size(pango_glyph_string(), length);
}



