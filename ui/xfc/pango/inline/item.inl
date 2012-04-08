/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  item.inl - Pango::Item inline functions
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

/*  Pango::Analysis
 */

inline PangoAnalysis*
Xfc::Pango::Analysis::pango_analysis() const
{
	return const_cast<PangoAnalysis*>(&analysis_);
}

inline guint8
Xfc::Pango::Analysis::level() const
{
	return analysis_.level;
}

inline PangoLanguage*
Xfc::Pango::Analysis::language() const
{
	return analysis_.language;
}

/*  Pango::Item
 */

inline PangoItem*
Xfc::Pango::Item::pango_item() const
{
	return reinterpret_cast<PangoItem*>(item_);
}

inline Xfc::Pango::Item::operator PangoItem* () const
{
	return this ? pango_item()  : 0;
}

inline int
Xfc::Pango::Item::offset() const
{
	return pango_item()->offset;
}

inline int
Xfc::Pango::Item::length() const
{
	return pango_item()->length;
}

inline int
Xfc::Pango::Item::num_chars() const
{
	return pango_item()->num_chars;
}

