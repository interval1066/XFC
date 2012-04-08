/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/gtk/bin.hh
/// @brief A GtkBin C++ wrapper interface.
///
/// The Bin widget is a container with just one child. It is not very useful itself,
/// but it is useful for deriving subclasses, since it provides common code needed
/// for handling a single child widget.

#ifndef XFC_GTK_BIN_HH
#define XFC_GTK_BIN_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_BIN_H__
#include <gtk/gtkbin.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Bin bin.hh xfc/gtk/bin.hh
/// @brief A GtkBin C++ wrapper class.
///
/// The Bin widget is a container with just one child. It is not very useful itself,
/// but it is useful for deriving subclasses, since it provides common code needed
/// for handling a single child widget. Many widgets are subclasses of Bin, including
/// Window, Button, Frame, HandleBox, and ScrolledWindow.

class Bin : public Container
{
	friend class G::Object;
	
	Bin(const Bin&);
	Bin& operator=(const Bin&);
	
protected:
/// @name Constructors
/// @{

	explicit Bin(GtkBin *bin, bool owns_reference = false);
	///< Construct a new Bin from an existing GtkBin.
	///< @param bin A pointer to a GtkBin.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>bin</EM> can be a newly created GtkBin or an existing
	///< GtkBin. (see G::Object::Object).
	
/// @}
public:
	typedef GtkBin CObjectType;

/// @name Constructors
/// @{
	virtual ~Bin();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkBin* gtk_bin() const;
	///< Get a pointer to the GtkBin structure.

	operator GtkBin* () const;
	///< Conversion operator; safely converts a Bin to a GtkBin pointer.

	Widget* get_child() const;
	///< Gets the child of the bin, or null if the bin contains no child widget.
	///< @return A pointer to the child of the Bin.
	///< The returned widget does not have a reference added, so you do not need to unref it.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/bin.inl>

#endif // XFC_GTK_BIN_HH

