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
 
/// @file xfc/gtk/invisible.hh
/// @brief A GtkInvisible C++ wrapper interface.
///
/// Provides Invisible, a widget which is used internally in GTK+, and probably
/// not useful for application developers.

#ifndef XFC_GTK_INVISIBLE_HH
#define XFC_GTK_INVISIBLE_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_INVISIBLE_H__
#include <gtk/gtkinvisible.h>
#endif

namespace Xfc {

namespace Gtk {

class Screen;

/// @class Invisible invisible.hh xfc/gtk/invisible.hh
/// @brief A GtkInvisible C++ wrapper class.
///
/// The Invisible widget is used internally in GTK+, and is probably not
/// useful for application developers. It is used for reliable pointer
/// grabs and selection handling in the code for drag-and-drop. If you
/// ever need to implement manual drag-and-drop you might find this widget
/// useful.

class Invisible : public Widget
{
	friend class G::Object;

	Invisible(const Invisible&);
	Invisible& operator=(const Invisible&);
	
protected:
/// @name Constructors
/// @{

	explicit Invisible(GtkInvisible *invisible, bool owns_reference = false);
	///< Construct a new Invisible from an existing GtkInvisible.
	///< @param invisible A pointer to a GtkInvisible.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>invisible</EM> can be a newly created GtkInvisible or an existing
	///< GtkInvisible (see G::Object::Object).

/// @}

public:
	typedef GtkInvisible CObjectType;

/// @name Constructors
/// @{

	Invisible();
	///< Construct a new Invisible.

	explicit Invisible(const Gdk::Screen& screen);
	///< Construct a new Invisible object for the specified screen.
	///< @param screen A Screen which identifies on which screen the new Invisible will be created.

	virtual ~Invisible();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkInvisible* gtk_invisible() const;
	///< Get a pointer to the GtkInvisible structure.

	operator GtkInvisible* () const;
	///< Conversion operator; safely converts an Invisible to a GtkInvisible pointer.

	Gdk::Screen* get_screen() const;
	///< Returns the Gdk::Screen object associated with the invisible.
	///< @return The associated Gdk::Screen.
	///<
	///< If no screen was explicitly set this method returns the default screen.

/// @}
/// @name Methods
/// @{

	void set_screen(const Gdk::Screen& screen);
	///< Sets the Gdk::Screen where the Invisible object will be displayed.
	///< @param screen A Gdk::Screen.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/invisible.inl>

#endif // XFC_GTK_INVISIBLE_HH

