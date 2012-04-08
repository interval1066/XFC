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
 
/// @file xfc/gtk/boxchild.hh
/// @brief A GtkBoxChild C++ wrapper interface.
///
///< Provides BoxChild, an object that describes how a child widget is to be packed into a box.

#ifndef XFC_GTK_BOX_CHILD_HH
#define XFC_GTK_BOX_CHILD_HH

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_BOX_H__
#include <gtk/gtkbox.h>
#endif

namespace Xfc {

namespace Gtk {

class Widget;

/// @class BoxChild boxchild.hh xfc/gtk/boxchild.hh
/// @brief A GtkBoxChild C++ wrapper class.
///
/// BoxChild is an object that describes how a child widget is to be packed into a box.
/// Use Gtk::Box::query_child_packing() and Gtk::Box::set_child_packing() to 
/// query and reset the padding, expand, fill, and pack fields.

class BoxChild
{
	friend class none;

	BoxChild();
	BoxChild(const BoxChild&);
	BoxChild& operator=(const BoxChild&);
	
	GtkBoxChild child_;

public:
/// @name Accessors
/// @{

	GtkBoxChild* gtk_box_child() const;
	///< Get a pointer to the GtkBoxChild structure.

	Widget* widget() const;
	///< Gets the child widget, packed into the Box.
	///< @return The child packed into the Box.
	///< The returned widget does not have a reference added, so you do not need to unref it.

	bool expand() const;
	///< Get the child widget expand flag.
	///< @return <EM>true</EM> if extra space should be given to the child widget.
	///<
	///< The expand flag indicates whether extra space should be given to this child.
	///< Any extra space given to the parent Box is divided up among all children with
	///< this attribute set to <EM>true</EM>; set when packed, <EM>true</EM> by default.

	bool fill() const;
	///< Get the child widget fill flag.
	/// @return <EM>true</EM> if extra space given to this child is allocated to the child.
	///<
	///< Indicates whether any extra space given to this child due to its expand attribute
	///< being set is actually allocated to the child, rather than being used as padding around
	///< the widget; set when packed, true by default.

	unsigned int padding() const;
	///< Gets the number of extra pixels to put between the child widget and its neighbors.
	///< @return The number of extra pixels.
	///<
	///< The padding is the number of extra pixels between this child and its neighbors,
	///< set when packed, zero by default.

	PackType pack() const;
	///< Gets the child widget PackType.
	///< @return The PackType.
	///<
	///< The PackType indicates whether the child is packed with reference to the start
	///< (top/left) or end (bottom/right) of the Box.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/boxchild.inl>

#endif // XFC_GTK_BOX_CHILD_HH


