/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
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
 
/// @file xfc/gtk/gc.hh
/// @brief A convenient gtk_gc_get() and gtk_gc_release() C++ wrapper interface.

#ifndef XFC_GTK_GC_HH
#define XFC_GTK_GC_HH

#ifndef XFC_GDK_GC_HH
#include <xfc/gdk/gc.hh>
#endif

#ifndef __GTK_GC_H__
#include <gtk/gtkgc.h>
#endif

namespace Xfc {

namespace Gdk {
class Colormap;
}

namespace Gtk {
	
/// @class GC gc.hh xfc/gtk/gc.hh
/// @brief A convenient gtk_gc_get() and gtk_gc_release() C++ wrapper class.
///
/// GC provides access to a shared pool of Gdk::GC objects. When you construct a new GC, gtk_gc_get()
/// is called with the required depth, colormap and Gdk::GCValues. If a Gdk::GC with the required
/// properties already exists then that is wrapped. If not, a new Gdk::GC is created. The destructor
/// releases for the Gdk::GC when the GC goes out of scope.

class GC : public Gdk::GC
{
public:
/// @name Constructors
/// @{

	GC(int depth, Gdk::Colormap *colormap, const Gdk::GCValues& values);
	///< Construct a new GC with the given depth, colormap and Gdk::GCValues.
	///< @param depth The depth of the GC to create.
	///< @param colormap The Gdk::Colormap.
	///< @param values A Gdk::GCValues object containing settings for the GC.

	virtual ~GC();
	///< Destructor.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_GC_HH

