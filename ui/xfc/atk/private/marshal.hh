/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  marshal.hh - Private interface
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

#ifndef XFC_ATK_MARSHALL_HH
#define XFC_ATK_MARSHALL_HH

#ifndef XFC_G_MARSHALL_HH
#include <xfc/glib/private/marshal.hh>
#endif

#ifndef __ATK_H__
#include <atk/atkobject.h>
#endif

namespace Xfc {

namespace Atk {

// Atk::Marshal provides the signal callback functions used by ATK Objects
// to translate GObject signal notifications into sigc::slot calls.

class Marshal
{
public:
	static void void_int_pvoid_callback(void*, unsigned int, void*);

	static void void_patkpropertyvalues_callback(void*, AtkPropertyValues*);

	static void void_string_bool_callback(void*, const char*, bool);

	static void void_ppvoid_callback(void*, void**);
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_MARSHALL_HH

