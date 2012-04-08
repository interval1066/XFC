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
 
/// @file xfc/atk/stateset.hh
/// @brief An AtkStateSet C++ wrapper interface.
///
/// Provides StateSet, an object that determines a component's state set.

#ifndef XFC_ATK_STATE_SET_HH
#define XFC_ATK_STATE_SET_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __ATK_STATE_SET_H__
#include <atk/atkstateset.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Atk {

// @enum Atk::StateType
/// The possible types of states of an object.

enum StateType
{
	STATE_INVALID = ATK_STATE_INVALID,
	///< Indicates an invalid state.

	STATE_ACTIVE = ATK_STATE_ACTIVE, 
	///< Indicates a window is currently the active window.

	STATE_ARMED = ATK_STATE_ARMED,
	///< Indicates that the object is armed.

	STATE_BUSY = ATK_STATE_BUSY,
	///< Indicates the current object is busy.

	STATE_CHECKED = ATK_STATE_CHECKED,
	///< Indicates this object is currently checked.

	STATE_DEFUNCT = ATK_STATE_DEFUNCT,
	///< Indicates the user interface object corresponding to this object no longer exists.

	STATE_EDITABLE = ATK_STATE_EDITABLE, 
	///< Indicates the user can change the contents of this object.

	STATE_ENABLED = ATK_STATE_ENABLED, 
	///< Indicates that this object is enabled.

	STATE_EXPANDABLE = ATK_STATE_EXPANDABLE,
	///< Indicates this object allows progressive disclosure of its children.

	STATE_EXPANDED = ATK_STATE_EXPANDED, 
	///< Indicates this object its expanded.

	STATE_FOCUSABLE = ATK_STATE_FOCUSABLE,
	///< Indicates this object can accept keyboard focus, which means all events resulting
	///< from typing on the keyboard will normally be passed to it when it has focus.

	STATE_FOCUSED = ATK_STATE_FOCUSED,
	///< Indicates this object currently has the keyboard focus.

	STATE_HORIZONTAL = ATK_STATE_HORIZONTAL, 
	///< Indicates the orientation of this object is horizontal.

	STATE_ICONIFIED = ATK_STATE_ICONIFIED,
	///< Indicates this object is minimized and is represented only by an icon.

	STATE_MODAL = ATK_STATE_MODAL, 
	///< Indicates something must be done with this object before the user
	///< can interact with an object in a different window.

	STATE_MULTI_LINE = ATK_STATE_MULTI_LINE, 
	///< Indicates this (text) object can contain multiple lines of text.

	STATE_MULTISELECTABLE = ATK_STATE_MULTISELECTABLE,
	///< Indicates this object allows more than one of its children to be selected at the same time.

	STATE_OPAQUE = ATK_STATE_OPAQUE, 
	///< Indicates this object paints every pixel within its rectangular region.

	STATE_PRESSED = ATK_STATE_PRESSED,
	///< Indicates this object is currently pressed.

	STATE_RESIZABLE = ATK_STATE_RESIZABLE, 
	///< Indicates the size of this object is not fixed.

	STATE_SELECTABLE = ATK_STATE_SELECTABLE,
	///< Indicates this object is the child of an object that allows its children to be selected
	///< and that this child is one of those children that can be selected.

	STATE_SELECTED = ATK_STATE_SELECTED,
	///< Indicates this object is the child of an object that allows its children to be selected
	///< and that this child is one of those children that has been selected.

	STATE_SENSITIVE = ATK_STATE_SENSITIVE,
	///< Indicates this object is sensitive.

	STATE_SHOWING = ATK_STATE_SHOWING, 
	///< Indicates this object, the object's parent, the object's parent's parent, and so on, are all visible.

	STATE_SINGLE_LINE = ATK_STATE_SINGLE_LINE,
	///< Indicates this (text) object can contain only a single line of text.

	STATE_STALE = ATK_STATE_STALE, 
	///< Indicates that the index associated with this object has changed since the user accessed the object.

	STATE_TRANSIENT = ATK_STATE_TRANSIENT,
	///< Indicates this object is transient.

	STATE_VERTICAL = ATK_STATE_VERTICAL,
	///< Indicates the orientation of this object is vertical.

	STATE_VISIBLE = ATK_STATE_VISIBLE,
	///< Indicates this object is visible.

	STATE_MANAGES_DESCENDANTS = ATK_STATE_MANAGES_DESCENDANTS, 
	///< Indicates that "active-descendant-changed" event is sent when children become
	///< 'active' (that is, are selected or navigated to onscreen); used to prevent
	///< the need to enumerate all children in very large containers, like tables.

	STATE_INDETERMINATE = ATK_STATE_INDETERMINATE,
	///< Indicates that a check box is in a state other than checked or not checked.

	STATE_LAST_DEFINED = ATK_STATE_LAST_DEFINED
	///< Not a valid role, used for finding end of enumeration.
};

/// @name StateType Methods
/// @{

StateType state_type_register(const String& name);
///< Register a new object state.
///< @param name A character string describing the new state.
///< @return A State value for the new state.

String state_type_get_name(StateType type);
///< Gets the description string describing the StateType <EM>type</EM>.
///< @param type The StateType whose name is required.
///< @return A string describing the StateType.

StateType state_type_for_name(const String& name);
///< Gets the StateType corresponding to the description string name.
///< @param name A character string state name.
///< @return A StateType corresponding to <EM>name</EM>.

/// @}

/// @class StateSet stateset.hh xfc/atk/stateset.hh
/// @brief An AtkStateSet C++ wrapper class.
///
/// A StateSet determines a component's state set. It is composed of a set of states.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class StateSet : public G::Object
{
	friend class G::Object;

	StateSet(const StateSet&);
	StateSet& operator=(const StateSet&);
	
protected:
/// @name Constructors
/// @{

	explicit StateSet(AtkStateSet *set, bool owns_reference = true);
	///< Construct a new StateSet from an existing AtkStateSet.
	///< @param set A pointer to a AtkStateSet.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>set</EM> can be a newly created AtkStateSet or an existing
	///< AtkStateSet. (see G::Object::Object).

/// @}

public:
	typedef AtkStateSet CObjectType;

/// @name Constructors
/// @{
	
	StateSet();
	///< Constructs a new empty state set with a reference count of 1 that the caller owns.
	
	virtual ~StateSet();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	AtkStateSet* atk_state_set() const;
	///< Get a pointer to the AtkStateSet structure.

	operator AtkStateSet* () const;
	///< Conversion operator; safely converts a StateSet to an AtkStateSet pointer.

	bool is_empty() const;
	///< Checks whether the state set is empty (that is, has no states set).
	///< @return <EM>true</EM> if set has no states set, otherwise <EM>false</EM>.

	bool contains_state(StateType type) const;
	///< Checks whether the state for the specified <EM>type</EM> is in the specified set.
	///< @param type A StateType.
	///< @return <EM>true</EM>if type is the state type is in set.

	bool contains_states(const std::vector<StateType>& types) const;
	///< Checks whether the states specified in <EM>types</EM> are in the specified set.
	///< @param types A vector of StateType
	///< @return <EM>true</EM> if all the states in <EM>types</EM> are in set.

/// @}
/// @name Methods
/// @{

	bool add_state(StateType type);
	///< Add a new state for the specified type to the current state set, if not already present.
	///< @param type A StateType.
	///< @return <EM>true</EM> if the state for type is not already in set.

	void add_states(const std::vector<StateType>& types);
	///< Add the states specified in <EM>types</EM> to the current state set.
	///< @param types A vector of StateType.
	
	void clear_states();
	///< Removes all states from the state set.

	bool remove_state(StateType type);
	///< Removes the state for the specified type from the state set.
	///< @param type A StateType
	///< @return <EM>true</EM> if <EM>type</EM> was in the state set and was removed.

	Pointer<StateSet> and_sets(StateSet& compare_set);
	///< Constructs the intersection of the states in this set and compare_set.
	///< @param compare_set Another StateSet.
	///< @return A new StateSet which is the intersection of the two sets, or null if the intersection is empty.

	Pointer<StateSet> or_sets(StateSet& compare_set);
	///< Constructs the union of the states in this set and compare_set.
	///< @param compare_set Another StateSet.
	///< @return  A new StateSet which is the union of the two sets.

	Pointer<StateSet> xor_sets(StateSet& compare_set);
	///< Constructs the exclusive-or of the states in this set and compare_set.
	///< @param compare_set Another StateSet.
	///< @return A new StateSet which contains the states which are in exactly one of the two sets,
	///< or null if the exclusive-or is empty.
	///<
	///< The set returned by this operation contains the states in exactly one of the two sets.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/stateset.inl>

#endif // XFC_ATK_STATE_SET_HH


