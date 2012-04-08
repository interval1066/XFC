/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fontset.cc - PangoFontset C++ wrapper implementation
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
 
#include "fontset.hh"
#include "font.hh"

using namespace Xfc;

/*  Pango::Fontset
 */

Pango::Fontset::Fontset(PangoFontset *fontset, bool owns_reference)
: G::Object((GObject*)fontset, owns_reference)
{
}

Pango::Fontset::~Fontset()
{
}

Pointer<Pango::Font>
Pango::Fontset::get_font(unsigned int wc) const
{
	return G::Object::wrap<Font>(pango_fontset_get_font(pango_fontset(), wc), true);
}

Pointer<Pango::FontMetrics>
Pango::Fontset::get_metrics() const
{
	return G::Boxed::wrap<FontMetrics>(PANGO_TYPE_FONT_METRICS, pango_fontset_get_metrics(pango_fontset()), false);
}

namespace { // foreach_slot_callback

gboolean foreach_slot_callback(PangoFontset*, PangoFont *font, gpointer data)
{
	Pango::Fontset::ForeachSlot& slot = *static_cast<Pango::Fontset::ForeachSlot*>(data);
	return slot(*G::Object::wrap<Pango::Font>(font));
}

} // namespace

void
Pango::Fontset::foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	pango_fontset_foreach(pango_fontset(), &foreach_slot_callback, &tmp_each);
}

