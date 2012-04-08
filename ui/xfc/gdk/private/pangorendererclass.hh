/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  pangorendererclass.hh - Private interface
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

#ifndef XFC_GDK_PANGO_RENDERER_CLASS_HH
#define XFC_GDK_PANGO_RENDERER_CLASS_HH

#include <xfc/pango/private/rendererclass.hh>

namespace Xfc {

namespace Gdk {

class PangoRendererClass
{
public:
	static void init(GdkPangoRendererClass *g_class);
	
	static GType get_type();

	static void* create(GdkScreen *screen);
};

} // namespace Gdk

} // namespace Xfc

#endif // XFC_GDK_PANGO_RENDERER_CLASS_HH

