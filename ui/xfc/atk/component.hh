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

/// @file xfc/atk/component.hh
/// @brief An AtkComponent C++ wrapper interface.
///
/// Provides Component, an interface provided by UI components which occupy a physical area on the screen.

#ifndef XFC_ATK_COMPONENT_HH
#define XFC_ATK_COMPONENT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_ATK_UTIL_HH
#include <xfc/atk/util.hh>
#endif

#ifndef __ATK_COMPONENT_H__
#include <atk/atkcomponent.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @class Component component.hh xfc/atk/component.hh
/// @brief An AtkComponent C++ wrapper class.
///
/// Component should be implemented by most if not all UI elements with an actual
/// on-screen presence, i.e. components which can be said to have a screen-coordinate
/// bounding box. Virtually all widgets will need to have Component implementations 
/// provided for their corresponding Object class. In short, only UI elements which
/// are <B>not</B> GUI elements will omit this ATK interface.
/// 
/// A possible exception might be textual information with a transparent background,
/// in which case text glyph bounding box information is provided by Text.

class Component : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Component();
	///< Constructs a new Component object.

	virtual ~Component() = 0;
	///< Destructor.
	
/// @}

public:
/// @name Accessors
/// @{

	AtkComponent* atk_component() const;
	///< Get a pointer to the AtkComponent structure.

	operator AtkComponent* () const;
	///< Conversion operator; safely converts a Component to an AtkComponent pointer.

	Object* ref_accessible_at_point(int x, int y, CoordType coord_type) const;
	///< Gets the accessible child, if one exists, at the coordinate point specified by x and y.
	///< @param x The X coordinate.
	///< @param y The Y coordinate.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///<                   or to the components top level window.
	///< @return A pointer to the accessible child, if one exists.

	void get_extents(int *x, int *y, int *width, int *height, CoordType coord_type) const;
	///< Gets the rectangle which gives the extent of the component.
	///< @param x The return location to store the x coordinate of the component.
	///< @param y The return location to store the y coordinate of the component.
	///< @param width The return location for the width of the component.
	///< @param height The return location for the height of the component.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///< or to the components top level window

	void get_position(int *x, int *y, CoordType coord_type) const;
	///< Gets the position of component in the form of a point specifying the
	///< component's top-left corner.
	///< @param x The return location to store the x coordinate of the component.
	///< @param y The return location to store the y coordinate of the component.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///< or to the components top level window.

	void get_size(int *width, int *height) const;
	///< Gets the size of the component in terms of width and height.
	///< @param width The return location for the width of the component.
	///< @param height The return location for the height of the component.

	Layer get_layer() const;
	///< Gets the layer of the component.
	///< @return A Layer which is the layer of the component.

	int get_mdi_zorder() const;
	///< Gets the zorder of the component. 
	///< @return An integer which is the zorder of the component, i.e. the depth at which
	///< the component is shown in relation to other components in the same container.
	///<
	///< The value G_MININT will be returned if the layer of the component is not LAYER_MDI or LAYER_WINDOW.

/// @}
/// @name Methods
/// @{

	unsigned int add_focus_handler(AtkFocusHandler handler);
	///< Add the specified handler to the set of functions to be called when the
	///< component receives focus events (in or out).
	///< @param handler The AtkFocusHandler to be attached to the component.
	///< @return A handler id which can be used in remove_focus_handler(),
	///< or zero if the handler was already added.
	///<
	///< If the handler is already added it is not added again.

	bool contains(int x, int y, CoordType coord_type) const;
	///< Checks whether the specified point is within the extent of the component.
	///< @param x The X coordinate.
	///< @param y The Y coordinate.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///<                   or to the components top level window.
	///< @return <EM>true</EM> if the specified point is within the extent of the component,
	///< <EM>false</EM> if not.

	bool grab_focus();
	///< Grabs the focus for the component.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.

	void remove_focus_handler(unsigned int handler_id);
	///< Remove the handler specified by handler_id from the list of functions
	///< to be executed when the component receives focus events (in or out).
	///< @param handler_id The id of the focus handler to be removed from the component.

	bool set_extents(int x, int y, int width, int height, CoordType coord_type);
	///< Sets the extents of the component.
	///< @param x The X coordinate.
	///< @param y The Y coordinate.
	///< @param width The width to set for the component.
	///< @param height The height to set for the component.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///<                   or to the components top level window.
	///< @return <EM>true</EM> if the extents were set, <EM>false</EM> if not.

	bool set_position(int x, int y, CoordType coord_type);
	///< Sets the postition of the component.
	///< @param x The X coordinate.
	///< @param y The Y coordinate.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///<                   or to the components top level window.
	///< @return <EM>true</EM> if the position was set, <EM>false</EM> if not.

	bool set_size(int width, int height);
	///< Set the size of the component in terms of width and height.
	///< @param width The width to set for the component.
	///< @param height The height to set for the component.
	///< @return <EM>true</EM> if the size was set, <EM>false</EM> if not.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/component.inl>

#endif // XFC_ATK_COMPONENT_HH


