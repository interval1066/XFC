/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  completion.inl - G::Completion inline functions
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

inline GCompletion*
Xfc::G::Completion::g_completion() const
{
	return completion_;
}

inline Xfc::G::Completion::operator GCompletion* () const
{
	return this ? completion_ : 0;
}

