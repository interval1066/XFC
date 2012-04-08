/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  markup.inl - G::MarkupParser inline functions
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

inline GMarkupParseContext*
Xfc::G::MarkupParseContext::g_markup_parse_context() const
{
	return context_;
}


inline Xfc::G::MarkupParseContext::operator GMarkupParseContext* () const
{
	return this ? context_ : 0;
}

inline void
Xfc::G::MarkupParseContext::get_position(int *line_number, int *char_number) const
{
	g_markup_parse_context_get_position(context_, line_number, char_number);
}

