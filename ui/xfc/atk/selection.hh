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
 
/// @file xfc/atk/selection.hh
/// @brief An AtkSelection C++ wrapper interface.
///
/// Provides Selection, an interface implemented by container objects whose Atk::Object children can be selected.

#ifndef XFC_ATK_SELECTION_HH
#define XFC_ATK_SELECTION_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_SELECTION_H__
#include <atk/atkselection.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @class Selection selection.hh xfc/atk/selection.hh
/// @brief An AtkSelection C++ wrapper class.
///
/// Selection should be implemented by UI components with children which are exposed by
/// Atk::Object::ref_accessible_child() and Atk::Object::get_n_accessible_children(), if
/// the use of the parent UI component ordinarily involves selection of one or more of 
/// the objects corresponding to those Atk::Object children - for example, selectable lists.
///
/// Note that other types of "selection" (for instance text selection) are accomplished
/// a other ATK interfaces - Atk::Selection is limited to the selection/deselection of
/// children.

class Selection : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Selection();
	///< Constructs a new Selection object.
	
	virtual ~Selection() = 0;
	///< Destructor.
	
/// @}
/// @name Signals
/// @{  

	typedef G::Signal<void> SelectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionChangedSignalType> SelectionChangedSignalProxy;
	static const SelectionChangedSignalType selection_changed_signal;
	///< Selection changed signal (see signal_selection_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	AtkSelection* atk_selection() const;
	///< Get a pointer to the AtkSelection structure.

	operator AtkSelection* () const;
	///< Conversion operator; safely converts a Selection to an AtkSelection pointer.

	int get_selection_count() const;
	///< Gets the number of accessible children currently selected. 
	///< @return An integer representing the number of items selected, or 0
	///< if selection does not implement this interface.
	///<
	///< <B>Note:</B> callers should not rely on null or on a zero value
	///< for an indication of whether the Selection interface is implemented,
	///< they should use is_a(ATK_TYPE_SELECTION).

	bool is_child_selected(int i) const;
	///< Determines if the current child of this object is selected.
	///< @param i An integer specifying the child index.
	///< @return <EM>true</EM> if the child is selected, or <EM>false</EM> if selection
	///< does not implement this interface.
	///<
	///< <B>Note:</B> callers should not rely on null or on a zero value
	///< for an indication of whether the Selection interface is implemented,
	///< they should use is_a(ATK_TYPE_SELECTION).

/// @}
/// @name Methods
/// @{

	bool add_selection(int i);
	///< Adds the specified accessible child of the object to the object's selection.
	///< @param i An integer specifying the child index.
	///< @return <EM>true</EM> if success, <EM>false</EM> otherwise.

	bool clear_selection();
	///< Clears the selection in the object so that no children in the object are selected.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.

	Object* ref_selection(int i);
	///< Gets a pointer to the accessible object representing the
	///< specified selected child of the object. 
	///< @param i An integer specifying the index in the selection set (that is, the ith
	///<          selection as opposed to the ith child).
	///< @return An Atk::bject representing the selected accessible , or null if selection
	///< does not implement this interface.
	///<
	///< <B>Note:</B> callers should not rely on null or on a zero value for indication
	///< of whether the Selection interface is implemented, they should use is_a(ATK_TYPE_SELECTION).

	bool remove_selection(int i);
	///< Removes the specified child of the object from the object's selection.
	///< @param i An integer specifying the index in the selection set (that is, the ith 
	///<          selection as opposed to the ith child).
	///< @return <EM>true</EM> if success, <EM>false</EM> otherwise.

	bool select_all_selection();
	///< Causes every child of the object to be selected if the object supports multiple selections.
	///< @return <EM>true</EM> if success, <EM>false</EM> otherwise.

/// @}
/// @name Signal Proxies
/// @{

	const SelectionChangedSignalProxy signal_selection_changed();
	///< Connect to the selection_changed_signal; emitted when an object's selection changes.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/selection.inl>

#endif // XFC_ATK_SELECTION_HH

