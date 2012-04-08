/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  context.inl - Pango::Context inline functions
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

inline PangoContext*
Xfc::Pango::Context::pango_context() const
{
	return reinterpret_cast<PangoContext*>(instance_);
}

inline Xfc::Pango::Context::operator PangoContext* () const
{
	return this ? pango_context() : 0;
}

inline PangoLanguage*
Xfc::Pango::Context::get_language() const
{
	return pango_context_get_language(pango_context());
}

inline Xfc::Pango::Direction
Xfc::Pango::Context::get_base_dir() const
{
	return (Direction)pango_context_get_base_dir(pango_context());
}

inline void
Xfc::Pango::Context::set_language(PangoLanguage *language)
{
	pango_context_set_language(pango_context(), language);
}

inline void
Xfc::Pango::Context::set_base_dir(Direction direction)
{
	pango_context_set_base_dir(pango_context(), (PangoDirection)direction);
}

