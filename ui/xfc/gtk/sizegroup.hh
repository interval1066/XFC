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
 
/// @file xfc/gtk/sizegroup.hh
/// @brief A GtkSizeGroup C++ wrapper interface.
///
/// Provides SizeGroup, a mechanism for grouping a number of widgets together so they all request
/// the same amount of space. This is typically useful when you want a column of widgets to have
/// the same size, but you can't use a Table widget.

#ifndef XFC_GTK_SIZE_GROUP_HH
#define XFC_GTK_SIZE_GROUP_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

namespace Xfc {

namespace Gtk {

class Widget;

/// @class SizeGroup sizegroup.hh xfc/gtk/sizegroup.hh
/// @brief A GtkSizeGroup C++ wrapper class.
///
/// SizeGroup provides a mechanism for grouping a number of widgets together so they all request
/// the same amount of space. This is typically useful when you want a column of widgets to have
/// the same size, but you can't use a Table widget.
///
/// In detail, the size requested for each widget in a SizeGroup is the maximum of the sizes that
/// would have been requested for each widget in the size group if they were not in the size group.
/// The mode of the size group (see set_mode()) determines whether this applies to the horizontal
/// size, the vertical size, or both sizes. Note that size groups only affect the amount of space
/// requested, not the size that the widgets finally receive. If you want the widgets in a SizeGroup
/// to actually be the same size, you need to pack them in such a way that they get the size they
/// request and not more. For example, if you are packing your widgets into a table, you would not
/// include the FILL flag.
///
/// SizeGroup objects are referenced by each widget in the size group, so once you have added all
/// widgets to a SizeGroup, you can drop the initial reference to the size group with unref(). If
/// the widgets in the size group are subsequently destroyed, then they will be removed from the
/// size group and drop their references on the size group; when all widgets have been removed,
/// the size group will be freed.
///
/// Widgets can be part of multiple size groups; GTK+ will compute the horizontal size of a widget
/// from the horizontal requisition of all widgets that can be reached from the widget by a chain
/// of size groups of type SIZE_GROUP_HORIZONTAL or SIZE_GROUP_BOTH, and the vertical size from
/// the vertical requisition of all widgets that can be reached from the widget by a chain of size
/// groups of type SIZE_GROUP_VERTICAL or SIZE_GROUP_BOTH.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class SizeGroup : public G::Object
{
	friend class G::Object;

	SizeGroup(const SizeGroup&);
	SizeGroup& operator=(const SizeGroup&);
	
protected:
/// @name Constructors
/// @{

	explicit SizeGroup(GtkSizeGroup *size_group, bool owns_reference = true);
	///< Construct a new SizeGroup from an existing GtkSizeGroup.
	///< @param size_group A pointer to a GtkSizeGroup.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>size_group</EM> can be a newly created GtkSizeGroup or an existing
	///< GtkSizeGroup (see G::Object::Object).

/// @}

public:
	typedef GtkSizeGroup CObjectType;

/// @name Constructors
/// @{

	explicit SizeGroup(SizeGroupMode mode = SIZE_GROUP_HORIZONTAL);
	///< Constructs a new size group with a reference count of 1 that the caller owns.
	///< @param mode The mode for the new size group.
	
	virtual ~SizeGroup();
	/// < Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkSizeGroup* gtk_size_group() const;
	///< Get a pointer to the GtkSizeGroup structure.

	operator GtkSizeGroup* () const;
	///< Conversion operator; safely converts a SizeGroup to a GtkSizeGroup pointer.

	SizeGroupMode get_mode() const;
	///< Gets the current mode of the size group (see set_mode()).
	///< @return The current mode of the size group.

/// @}
/// @name Methods
/// @{

	void set_mode(SizeGroupMode mode);
	///< Sets the SizeGroupMode of the size group. 
	///< @param mode The mode to set for the size group.
	///<
	///< The mode of the size group determines whether the widgets in the size group
	///< should all have the same horizontal requisition (SIZE_GROUP_MODE_HORIZONTAL),
	///< all have the same vertical requisition (SIZE_GROUP_MODE_VERTICAL), or should all
	///< have the same requisition in both directions (SIZE_GROUP_MODE_BOTH).

	void add_widget(Widget& widget);
	///< Adds a widget to the SizeGroup.
	///< @param widget The Widget to add.
	///<
	///< In the future, the requisition of the widget will be determined as the
	///< maximum of its requisition and the requisition of the other widgets in the
	///< size group. Whether this applies horizontally, vertically, or in both 
	///< directions depends on the mode of the size group (see set_mode()).

	void remove_widget(Widget& widget);
	///< Removes a widget from the SizeGroup.
	///< @param widget The Widget to remove.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/sizegroup.inl>

#endif // XFC_GTK_SIZE_GROUP_HH

