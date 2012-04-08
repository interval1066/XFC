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
 
/// @file xfc/atk/object.hh
/// @brief An AtkObject C++ wrapper interface.
///
/// Provides Object, the base object class for the Accessibility Toolkit API.

#ifndef XFC_ATK_OBJECT_HH
#define XFC_ATK_OBJECT_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_ATK_UTIL_HH
#include <xfc/atk/util.hh>
#endif

#ifndef __ATK_OBJECT_H__
#include <atk/atkobject.h>
#endif

namespace Xfc {

namespace Atk {

class RelationSet;
class StateSet;

/// @enum Role
/// Describes the role of an object.

enum Role
{
	ROLE_INVALID = ATK_ROLE_INVALID, 
	///< Invalid role.

	ROLE_ACCEL_LABEL = ATK_ROLE_ACCEL_LABEL, 
	///< A label which represents an accelerator.

	ROLE_ALERT = ATK_ROLE_ALERT, 
	///< An object which is an alert to the user.

	ROLE_ANIMATION = ATK_ROLE_ANIMATION, 
	///< An object which is an animated image.

	ROLE_ARROW = ATK_ROLE_ARROW, 
	///< An arrow in one of the four cardinal directions.

	ROLE_CALENDAR = ATK_ROLE_CALENDAR, 
	///< An object that displays a calendar and allows the user to select a date.

	ROLE_CANVAS = ATK_ROLE_CANVAS, 
	///< An object that can be drawn into and is used to trap events.

	ROLE_CHECK_BOX = ATK_ROLE_CHECK_BOX, 
	///< A choice that can be checked or unchecked and provides a separate indicator for the current state.

	ROLE_CHECK_MENU_ITEM = ATK_ROLE_CHECK_MENU_ITEM, 
	///< A menu item with a check box.

	ROLE_COLOR_CHOOSER = ATK_ROLE_COLOR_CHOOSER,
	///< A specialized dialog that lets the user choose a color.

	ROLE_COLUMN_HEADER = ATK_ROLE_COLUMN_HEADER, 
	///< The header for a column of data.

	ROLE_COMBO_BOX = ATK_ROLE_COMBO_BOX, 
	///< A list of choices the user can select from.

	ROLE_DATE_EDITOR = ATK_ROLE_DATE_EDITOR, 
	///< An object whose purpose is to allow a user to edit a date.

	ROLE_DESKTOP_ICON = ATK_ROLE_DESKTOP_ICON,
	///< An inconifed internal frame within a DESKTOP_PANE.

	ROLE_DESKTOP_FRAME = ATK_ROLE_DESKTOP_FRAME, 
	///< A pane that supports internal frames and iconified versions of those internal frames.

	ROLE_DIAL = ATK_ROLE_DIAL, 
	///< An object whose purpose is to allow a user to set a value.

	ROLE_DIALOG = ATK_ROLE_DIALOG, 
	///< A top level window with title bar and a border.

	ROLE_DIRECTORY_PANE = ATK_ROLE_DIRECTORY_PANE, 
	///< A pane that allows the user to navigate through and select the contents of a directory.

	ROLE_DRAWING_AREA = ATK_ROLE_DRAWING_AREA, 
	///< An object used for drawing custom user interface elements.

	ROLE_FILE_CHOOSER = ATK_ROLE_FILE_CHOOSER, 
	///< A specialized dialog that lets the user choose a file.

	ROLE_FILLER = ATK_ROLE_FILLER, 
	///< A object that fills up space in a user interface.

	ROLE_FONT_CHOOSER = ATK_ROLE_FONT_CHOOSER, 
	///< A specialized dialog that lets the user choose a font.

	ROLE_FRAME = ATK_ROLE_FRAME,
	///< A top level window with a title bar, border, menubar, etc.

	ROLE_GLASS_PANE = ATK_ROLE_GLASS_PANE,
	///< A pane that is guaranteed to be painted on top of all panes beneath it.

	ROLE_HTML_CONTAINER = ATK_ROLE_HTML_CONTAINER, 
	///< A document container for HTML, whose children represent the document content.

	ROLE_ICON = ATK_ROLE_ICON, 
	///< A small fixed size picture, typically used to decorate components.

	ROLE_IMAGE = ATK_ROLE_IMAGE, 
	///< An object whose primary purpose is to display an image.

	ROLE_INTERNAL_FRAME = ATK_ROLE_INTERNAL_FRAME, 
	///< A frame-like object that is clipped by a desktop pane.

	ROLE_LABEL = ATK_ROLE_LABEL, 
	///< An object used to present an icon or short string in an interface.

	ROLE_LAYERED_PANE = ATK_ROLE_LAYERED_PANE, 
	///< A specialized pane that allows its children to be drawn in layers, providing a form of stacking order.

	ROLE_LIST = ATK_ROLE_LIST, 
	///< An object that presents a list of objects to the user and allows the user to select one or more of them.

	ROLE_LIST_ITEM = ATK_ROLE_LIST_ITEM, 
	///< An object that represents an element of a list.

	ROLE_MENU = ATK_ROLE_MENU, 
	///< An object usually found inside a menu bar that contains a list of actions the user can choose from.

	ROLE_MENU_BAR = ATK_ROLE_MENU_BAR, 
	///< An object usually drawn at the top of the primary dialog box of an
	///< application that contains a list of menus the user can choose from.

	ROLE_MENU_ITEM = ATK_ROLE_MENU_ITEM, 
	///< An object usually contained in a menu that presents an action the user can choose.

	ROLE_OPTION_PANE = ATK_ROLE_OPTION_PANE, 
	///< A specialized pane whose primary use is inside a DIALOG.

	ROLE_PAGE_TAB = ATK_ROLE_PAGE_TAB, 
	///< An object that is a child of a page tab list.

	ROLE_PAGE_TAB_LIST = ATK_ROLE_PAGE_TAB_LIST, 
	///< An object that presents a series of panels (or page tabs), one at a time,
	///< through some mechanism provided by the object.

	ROLE_PANEL = ATK_ROLE_PANEL, 
	///< A generic container that is often used to group objects.

	ROLE_PASSWORD_TEXT = ATK_ROLE_PASSWORD_TEXT, 
	///< A text object uses for passwords, or other places where the text content is not shown visibly to the user.

	ROLE_POPUP_MENU = ATK_ROLE_POPUP_MENU, 
	///< A temporary window that is usually used to offer the user a list of choices, 
	///< and then hides when the user selects one of those choices.

	ROLE_PROGRESS_BAR = ATK_ROLE_PROGRESS_BAR, 
	///< An object used to indicate how much of a task has been completed.

	ROLE_PUSH_BUTTON = ATK_ROLE_PUSH_BUTTON, 
	///< An object the user can manipulate to tell the application to do something.

	ROLE_RADIO_BUTTON = ATK_ROLE_RADIO_BUTTON, 
	///< A specialized check box that will cause other radio buttons in the same group
	///< to become unchecked when this one is checked.

	ROLE_RADIO_MENU_ITEM = ATK_ROLE_RADIO_MENU_ITEM, 
	///< A check menu item which belongs to a group; at each instant exactly one
	///< of the radio menu items from a group is selected.

	ROLE_ROOT_PANE = ATK_ROLE_ROOT_PANE, 
	///< A specialized pane that has a glass pane and a layered pane as its children.

	ROLE_ROW_HEADER = ATK_ROLE_ROW_HEADER, 
	///< The header for a row of data.

	ROLE_SCROLL_BAR = ATK_ROLE_SCROLL_BAR, 
	///< An object usually used to allow a user to incrementally view a large amount of data.

	ROLE_SCROLL_PANE = ATK_ROLE_SCROLL_PANE,
	///< An object that allows a user to incrementally view a large amount of information.

	ROLE_SEPARATOR = ATK_ROLE_SEPARATOR, 
	///< An object usually contained in a menu to provide a visible and logical separation of the contents in a menu.

	ROLE_SLIDER = ATK_ROLE_SLIDER, 
	///< An object that allows the user to select from a bounded range.

	ROLE_SPLIT_PANE = ATK_ROLE_SPLIT_PANE, 
	///< A specialized panel that presents two other panels at the same time.

	ROLE_SPIN_BUTTON = ATK_ROLE_SPIN_BUTTON, 
	///< An object used to get an integer or floating point number from the user.

	ROLE_STATUSBAR = ATK_ROLE_STATUSBAR, 
	///< An object which reports messages of minor importance to the user.

	ROLE_TABLE = ATK_ROLE_TABLE, 
	///< An object used to represent information in terms of rows and columns.

	ROLE_TABLE_CELL = ATK_ROLE_TABLE_CELL, 
	///< A cell in a table.

	ROLE_TABLE_COLUMN_HEADER = ATK_ROLE_TABLE_COLUMN_HEADER, 
	///< The header for a column of a table.

	ROLE_TABLE_ROW_HEADER = ATK_ROLE_TABLE_ROW_HEADER, 
	///< The header for a row of a table.

	ROLE_TEAR_OFF_MENU_ITEM = ATK_ROLE_TEAR_OFF_MENU_ITEM, 
	///< A menu item used to tear off and reattach its menu.

	ROLE_TERMINAL = ATK_ROLE_TERMINAL, 
	///< An object that represents an accessible terminal.

	ROLE_TEXT = ATK_ROLE_TEXT, 
	///< An object that presents text to the user.

	ROLE_TOGGLE_BUTTON = ATK_ROLE_TOGGLE_BUTTON, 
	///< A specialized push button that can be checked or unchecked, but does not
	///< provide a separate indicator for the current state.

	ROLE_TOOL_BAR = ATK_ROLE_TOOL_BAR, 
	///< A bar or palette usually composed of push buttons or toggle buttons.

	ROLE_TOOL_TIP = ATK_ROLE_TOOL_TIP, 
	///< An object that provides information about another object.

	ROLE_TREE = ATK_ROLE_TREE, 
	///< An object used to represent hierarchical information to the user.

	ROLE_TREE_TABLE = ATK_ROLE_TREE_TABLE, 
	///< An object capable of expanding and collapsing rows as well as showing multiple columns of data.

	ROLE_UNKNOWN = ATK_ROLE_UNKNOWN, 
	///< The object contains some Accessible information, but its role is not known.

	ROLE_VIEWPORT = ATK_ROLE_VIEWPORT, 
	///< An object usually used in a scroll pane.

	ROLE_WINDOW = ATK_ROLE_WINDOW, 
	///< A top level window with no title or border.

	ROLE_HEADER = ATK_ROLE_HEADER, 
	///< An object that serves as a document header.

	ROLE_FOOTER = ATK_ROLE_FOOTER, 
	///< An object that serves as a document footer.

	ROLE_PARAGRAPH = ATK_ROLE_PARAGRAPH, 
	///< An object which is contains a paragraph of text content.

 	ROLE_RULER = ATK_ROLE_RULER, 
	///< An object which describes margins and tab stops for text objects
	///< which it controls (should have CONTROLLER_FOR relation to such).

	ROLE_APPLICATION = ATK_ROLE_APPLICATION, 
	///< The object is an application object, which may contain ROLE_FRAME objects or other types of accessibles.

	ROLE_AUTOCOMPLETE = ATK_ROLE_AUTOCOMPLETE,
	///< The object is a dialog or list containing items for insertion into an entry widget,
	///< for instance a list of words for completion of a text entry.
	
	ROLE_EDITBAR = ATK_ROLE_EDITBAR, 
	///< The object is an editable text object in a toolbar.
		
	ROLE_LAST_DEFINED = ATK_ROLE_LAST_DEFINED
	///< Not a valid role, used for finding end of the enumeration.
};

/// @name Role Methods
/// @{

Role role_register(const String& name);
///< Registers the role specified by name.
///< @param name A character string describing the new role.
///< @return A Role for the new role.

String role_get_name(Role role);
///< Gets the description string describing the Role <EM>role</EM>.
///< @param role The Role whose name is required.
///< @return A string describing the <EM>role</EM>.

String role_get_localized_name(Role role);
///< Gets the localized description string describing the Role <EM>role</EM>.
///< @param role The Role whose localized name is required.
///< @return A localized string describing the <EM>role</EM>.

Role role_for_name(const String& name);
///< Get the Role type corresponding to a role <EM>name</EM>.
///< @param name A string which is the (non-localized) name of an ATK role.
///< @return The Role type corresponding to the specified name, or ROLE_INVALID if no matching role is found.

/// @}

/// @class Object object.hh xfc/atk/object.hh
/// @brief An AtkObject C++ wrapper class.
///
/// Atk::Object is the primary class for accessibility support via the Accessibility ToolKit (ATK).
/// Objects which are instances of Atk::Object (or instances of Atk::Object-derived types) are 
/// queried for properties which relate basic (and generic) properties of a UI component such as
/// name and description. Instances of Atk::Object may also be queried as to whether they implement
/// other ATK interfaces (e.g. Action, Component, etc.), as appropriate to the role which a given
/// UI component plays in a user interface.
///
/// All UI components in an application which provide useful information or services to the user
/// must provide corresponding Atk::Object instances on request (in GTK+, for instance, usually
/// on a call to Gtk::Widget::get_accessible()), either via ATK support built into the toolkit
/// for the widget class or ancestor class, or in the case of custom widgets, if the inherited
/// Atk::Object implementation is insufficient, via instances of a new Atk::Object subclass.

class Object : public G::Object
{
	friend class G::Object;

	Object(const Object&);
	Object& operator=(const Object&);

protected:
/// @name Constructors
/// @{

	explicit Object(AtkObject *object, bool owns_reference = true);
	///< Construct a new Object from an existing AtkObject.
	///< @param object A pointer to a AtkObject.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>object</EM> can be a newly created AtkObject or an existing
	///< AtkObject. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, unsigned int, void*> ChildrenChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChildrenChangedSignalType> ChildrenChangedSignalProxy;
	static const ChildrenChangedSignalType children_changed_signal;
	///< Children changed signal (see signal_children_changed()). Calls a slot with the signature:
	///< @code
	///< void function(unsigned int change_index, void *changed_child);
	///< // change_index: The index of the added or removed child.
	///< // changed_child: The child which was added or removed.
	///< @endcode

	typedef G::Signal<void, bool> FocusEventSignalType;
	typedef G::SignalProxy<TypeInstance, FocusEventSignalType> FocusEventSignalProxy;
	static const FocusEventSignalType focus_event_signal;
	///< Focus event signal (see signal_focus_event()). Calls a slot with the signature:
	///< @code
	///< void function(bool focus_in);
	///< // focus_in: Indicates whether or not the focus event is is or out.
	///< @endcode

	typedef G::Signal<void, AtkPropertyValues*> PropertyChangeSignalType;
	typedef G::SignalProxy<TypeInstance, PropertyChangeSignalType> PropertyChangeSignalProxy;
	static const PropertyChangeSignalType property_change_signal;
	///< Property change signal (see signal_property_change()). Calls a slot with the signature:
	///< @code
	///< void function(AtkPropertyValues *values);
	///< // values: The new value of the property which changed.
	///< @endcode

	typedef G::Signal<void, const String&, bool> StateChangeSignalType;
	typedef G::SignalProxy<TypeInstance, StateChangeSignalType> StateChangeSignalProxy;
	static const StateChangeSignalType state_change_signal;
	///< State change signal (see signal_state_change()). Calls a slot with the signature:
	///< @code
	///< void function(const String& name, bool state_set);
	///< // name: The name of the state which has changed.
	///< // state_set: Indicates whether the state has been set or unset.
	///< @endcode

	typedef G::Signal<void> VisibleDataChangedSignalType;
	typedef G::SignalProxy<TypeInstance, VisibleDataChangedSignalType> VisibleDataChangedSignalProxy;
	static const VisibleDataChangedSignalType visible_data_changed_signal;
	///< Visible data changed signal (see signal_visible_data_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, void**> ActiveDescendantChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ActiveDescendantChangedSignalType> ActiveDescendantChangedSignalProxy;
	static const ActiveDescendantChangedSignalType active_descendant_changed_signal;
	///< Active descendant changed signal (see signal_active_descendant_changed()). Calls a slot with the signature:
	///< @code
	///< void function(void **child);
	///< // child: The newly focused object.
	///< @endcode
	
/// @}

public:
	typedef AtkObject CObjectType;

/// @name Constructors
/// @{

	virtual ~Object();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	AtkObject* atk_object() const;
	///< Get a pointer to the AtkObject structure.

	operator AtkObject* () const;
	///< Conversion operator; safely converts an Object to an AtkObject pointer.

	String get_name() const;
	///< Gets the accessible name of the object.
	///< @return A character string representing the accessible name of the object.

	String get_description() const;
	///< Gets the accessible description of the object.
	///< @return A character string representing the accessible description of the object.

	Object* get_parent() const;
	///< Gets the accessible parent of the object.
	///< @return An Atk::Object representing the accessible parent of the object.

	int get_n_accessible_children() const;
	///< Gets the number of accessible children of the object.
	///< @return An integer representing the number of accessible children of the object.

	Object* ref_accessible_child(int index) const;
	///< Gets a pointer to the specified accessible child of the object.
	///< @param index An integer representing the position of the child, starting from 0.
	///< @return An Atk::Object representing the specified accessible child of the object.
	///<
	///< The accessible children are zero-based so the first accessible child
	///< is at index 0, the second at index 1 and so on.

	RelationSet* ref_relation_set() const;
	///< Gets the RelationSet associated with the object.
	///< @return A RelationSet representing the relation set of the object.

	Role get_role() const;
	///< Gets the role of the accessible object.
	///< @return A Role which is the role of the accessible object.

	Pointer<StateSet> ref_state_set() const;
	///< Gets a reference to the StateSet of the accessible object.
	///< @return A smart pointer to a StateSet which is the state set of the accessible object.

	int get_index_in_parent() const;
	///< Gets the zero-based index of this accessible object in its parent.
	///< @return An integer which is the index of the accessible object in its parent,
	///< or -1  if the accessible does not have an accessible parent.

/// @}
/// @name Methods
/// @{

	void set_name(const char *name);
	void set_name(const String& name);
	///< Sets the accessible name of the object.
	///< @param name A character string to be set as the accessible name.

	void set_description(const char *description);
	void set_description(const String& description);
	///< Sets the accessible description of the object.
	///< @param description A character string to be set as the accessible description.

	void set_parent(Object& parent);
	///< Sets the accessible parent of the object.
	///< @param parent An Atk::Object to be set as the accessible parent.

	void set_role(Role role);
	///< Sets the role of the accessible object.
	///< @param role A Role to be set as the role.

	void notify_state_change(State state, bool value);
	///< Emits a "state_change" signal for the specified <EM>state</EM>.
	///< @param state A State whose state is changed.
	///< @param value Indicates whether the state is being set on or off.

	bool add_relationship(RelationType relationship, const Object& target);
	///< Adds a relationship of the specified type to the specified target.
	///< @param relationship The RelationType of the relation.
	///< @param target The Atk::Object which is to be the target of the relation.
	///< @return <EM>true</EM> if the relationship was added.

	bool remove_relationship(RelationType relationship, const Object& target);
	///< Removes a relationship of the specified type from the specified target.
	///< @param relationship The RelationType of the relation.
	///< @param target The Atk::Object which is the target of the relation to be removed.
	///< @return <EM>true</EM> if the relationship was removed.

/// @}
/// @name Signal Proxies
/// @{

	const ChildrenChangedSignalProxy signal_children_changed();
	///< Connect to the children_changed_signal; emitted when the number of children of the object changes.

	const FocusEventSignalProxy signal_focus_event();
	///< Connect to the focus_event_signal; emitted when there is a focus event for an object.

	const PropertyChangeSignalProxy signal_property_change();
	///< Connect to the property_change_signal; emitted when the value of an object property changes.

	const StateChangeSignalProxy signal_state_change();
	///< Connect to the state_change_signal; emitted when the state of an object changes.

	const VisibleDataChangedSignalProxy signal_visible_data_changed();
	///< Connect to the visible_data_changed_signal; emitted when there is a change
	///< in the visible data for an object.

	const ActiveDescendantChangedSignalProxy signal_active_descendant_changed();
	///< Connect to the active_descendant_changed_signal; emitted when there is a change
	///< in the 'active' child or children of the object (for instance, when the interior
	///< focus changes in a table or list). This signal should be emitted by objects whose state
	///< includes Atk::STATE_MANAGES_DESCENDANTS.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/object.inl>

#endif // XFC_ATK_OBJECT_HH

