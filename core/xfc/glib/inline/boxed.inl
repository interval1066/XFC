/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  boxed.inl - G::Boxed inline functions
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

inline void*
Xfc::G::Boxed::g_boxed() const
{
	return boxed_;
}

template<typename T>
inline T*
Xfc::G::Boxed::wrap(GType boxed_type, void *boxed)
{
	return static_cast<T*>(boxed ? new Boxed(boxed_type, boxed) : 0);
}

template<typename T>
inline T*
Xfc::G::Boxed::wrap(GType boxed_type, void *boxed, bool copy)
{
	return static_cast<T*>(boxed ? new Boxed(boxed_type, boxed, copy) : 0);
}

