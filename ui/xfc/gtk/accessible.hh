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

/// @file xfc/gtk/accessible.hh
/// @brief GtkAccessible C++ wrapper interface.

#ifndef XFC_GTK_ACCESSIBLE_HH
#define XFC_GTK_ACCESSIBLE_HH

#ifndef XFC_ATK_OBJECT_HH
#include <xfc/atk/object.hh>
#endif

#ifndef __GTK_ACCESSIBLE_H__
#include <gtk/gtkaccessible.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Accessible accessible.hh xfc/gtk/accessible.hh
/// @brief A GtkAccessible C++ wrapper class.

class Accessible : public Atk::Object
{
	friend class G::Object;

	Accessible(const Accessible&);
	Accessible& operator=(const Accessible&);

protected:
/// @name Constructors
/// @{

	explicit Accessible(GtkAccessible *accessible, bool owns_reference = true);
	///< Construct a new Accessible from an existing GtkAccessible.
	///< @param accessible A pointer to a GtkAccessible.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>accessible</EM> can be a newly created GtkAccessible or an existing
	///< GtkAccessible. (see G::Object::Object).

/// @}

public:
	typedef GtkAccessible CObjectType;

/// @name Constructors
/// @{

	virtual ~Accessible();
	///< Destructor

/// @}
/// @name Accessors
/// @{

	GtkAccessible* gtk_accessible() const;
	///< Get a pointer to the GtkAccessible structure.

	operator GtkAccessible* () const;
	///< Conversion operator; safely converts an Accessible to a GtkAccessible pointer.

/// @}
/// @name Methods
/// @{

	void connect_widget_destroyed();
	///< This method specifies the callback function to be called when the widget corresponding
	///< to a GtkAccessible is destroyed.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/accessible.inl>

#endif // XFC_GTK_ACCESSIBLE_HH

