/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  textiface.hh - Private interface
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef XFC_ATK_TEXT_IFACE_HH
#define XFC_ATK_TEXT_IFACE_HH

namespace Xfc {

namespace Atk {

class TextIface
{
public:
	static void init(AtkTextIface *g_iface);

	static AtkTextIface* get_parent_iface(void *instance);
	
	static void text_changed_proxy(AtkText *text, gint position, gint length);

	static void text_caret_moved_proxy(AtkText *text, gint location);

	static void text_selection_changed_proxy(AtkText *text);
	
	static void text_attributes_changed_proxy(AtkText *text);
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_TEXT_IFACE_HH
