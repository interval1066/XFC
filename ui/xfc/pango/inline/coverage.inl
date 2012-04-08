/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  coverage.inl - Pango::Coverage inline functions
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

inline PangoCoverage*
Xfc::Pango::Coverage::pango_coverage() const
{
	return coverage_;
}

inline Xfc::Pango::Coverage::operator PangoCoverage* () const
{
	return this ? coverage_ : 0;
}

inline Xfc::Pango::CoverageLevel
Xfc::Pango::Coverage::get(int index) const
{
	return (CoverageLevel)pango_coverage_get(coverage_, index);
}

inline void
Xfc::Pango::Coverage::set(int index, CoverageLevel level)
{
	pango_coverage_set(coverage_, index, (PangoCoverageLevel)level);
}

inline void
Xfc::Pango::Coverage::to_bytes(unsigned char **bytes, int *n_bytes)
{
	pango_coverage_to_bytes(coverage_, bytes, n_bytes);
}

