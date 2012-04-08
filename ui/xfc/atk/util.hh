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
 
/// @file xfc/atk/util.hh
/// @brief An ATK Utility C++ wrapper interface.
///
/// Provides miscellaneous utility classes and functions.

#ifndef XFC_ATK_UTIL_HH
#define XFC_ATK_UTIL_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __ATK_UTIL_H__
#include <atk/atkutil.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// State is a typedef for AtkState.

typedef AtkState State;

/// @enum CoordType
/// Specifies how xy coordinates are to be interpreted. Used by functions such
/// as Atk::Component::get_position() and Atk::Text::get_character_extents().

enum CoordType
{
	XY_SCREEN = ATK_XY_SCREEN, ///< Specifies xy coordinates relative to the screen.
	XY_WINDOW = ATK_XY_WINDOW ///< Specifies xy coordinates relative to the widget's.
};

/// @enum Layer
/// Describes the layer of a component.
///
/// The enumerated "layer values" are used when determining which UI
/// rendering layer a component is drawn into, which can help in making
/// determinations of when components occlude one another.

enum Layer
{
	LAYER_INVALID = ATK_LAYER_INVALID, ///< The object does not have a layer.
	LAYER_BACKGROUND = ATK_LAYER_BACKGROUND, ///< This layer is reserved for the desktop background.
	LAYER_CANVAS = ATK_LAYER_CANVAS, ///< This layer is used for Canvas components.
	LAYER_WIDGET = ATK_LAYER_WIDGET, ///< This layer is normally used for components.
	LAYER_MDI = ATK_LAYER_MDI, ///< This layer is used for layered components.
	LAYER_POPUP = ATK_LAYER_POPUP, ///< This layer is used for popup components, such as menus.
	LAYER_OVERLAY = ATK_LAYER_OVERLAY, ///< This layer is reserved for future use.
	LAYER_WINDOW = ATK_LAYER_WINDOW ///< This layer is used for toplevel windows.
};

/// @enum RelationType
/// Describes the type of the relation.

enum RelationType
{
	RELATION_NULL = ATK_RELATION_NULL, 
	///< No relation.

	RELATION_CONTROLLED_BY = ATK_RELATION_CONTROLLED_BY, 
	///< Indicates an object controlled by one or more target objects.

	RELATION_CONTROLLER_FOR = ATK_RELATION_CONTROLLER_FOR, 
	///< Indicates an object is an controller for one or more target objects.

	RELATION_LABEL_FOR = ATK_RELATION_LABEL_FOR, 
	///< Indicates an object is a label for one or more target objects.

	RELATION_LABELLED_BY = ATK_RELATION_LABELLED_BY, 
	///< Indicates an object is labelled by one or more target objects.

	RELATION_MEMBER_OF = ATK_RELATION_MEMBER_OF, 
	///< Indicates an object is a member of a group of one or more target objects.

	RELATION_NODE_CHILD_OF = ATK_RELATION_NODE_CHILD_OF, 
	///< Indicates an object is a cell in a treetable which is displayed because
	///< a cell in the same column is expanded and identifies that cell.

	RELATION_FLOWS_TO = ATK_RELATION_FLOWS_TO, 
	///< Indicates that the object has content that flows logically to another 
	///< Atk::Object in a sequential way, (for instance text-flow).

	RELATION_FLOWS_FROM = ATK_RELATION_FLOWS_FROM, 
	///< Indicates that the object has content that flows logically from another
	///< Atk::Object in a sequential way, (for instance text-flow).

	RELATION_SUBWINDOW_OF = ATK_RELATION_SUBWINDOW_OF, 
	///< [not sure about this one]

	RELATION_EMBEDS = ATK_RELATION_EMBEDS, 
	///< Indicates that the object visually embeds another object's content, that is
	///< this object's content flows around another's content.

	RELATION_EMBEDDED_BY = ATK_RELATION_EMBEDDED_BY, 
	///< Inverse of %ATK_RELATION_EMBEDS, indicates that this object's content 
	///< is visualy embedded in another object.

	RELATION_POPUP_FOR = ATK_RELATION_POPUP_FOR,
	///< Indicates that an object is a popup for another object.
	
	RELATION_LAST_DEFINED = ATK_RELATION_LAST_DEFINED 
	///< Not a valid relation, used for finding end of the enumeration.
};

/// @name RelationType Methods
/// @{

RelationType relation_type_register(const String& name);
///< Associate name with a new RelationType.
///< @param name A name string.
///< @return A RelationType associated with <EM>name</EM>.

String relation_type_get_name(RelationType type);
///< Gets the description string describing the RelationType <EM>type</EM>.
///< @param type The RelationType whose name is required.
///< @return The string describing the RelationType.

RelationType relation_type_for_name(const String& name);
///< Get the RelationType type corresponding to a relation name.
///< @param name A string which is the (non-localized) name of an ATK relation type.
///< @return The RelationType corresponding to the specified name, or RELATION_NULL if no matching relation type is found.

/// @}
/// @name Toolkit Methods
/// @{

Object* get_root();
///< Returns the root accessible container for the current application.

Object* get_focus_object();
///< Gets the currently focused accessible object.
///< @return The currently focused accessible object for the current application.

String get_toolkit_name();
///< Returns the name string for the GUI toolkit implementing ATK for this application.

String get_toolkit_version();
///< Returns the version string for the GUI toolkit implementing ATK for this application.

/// @}

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_UTIL_HH


