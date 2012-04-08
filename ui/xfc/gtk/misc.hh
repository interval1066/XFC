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
 
/// @file xfc/gtk/misc.hh
/// @brief A GtkMisc C++ wrapper interface.
///
/// Provides Misc, an abstract widget which is not useful itself, but is used
/// to derive subclasses which have alignment and padding attributes.

#ifndef XFC_GTK_MISC_HH
#define XFC_GTK_MISC_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_MISC_H__
#include <gtk/gtkmisc.h>
#endif

namespace Xfc {

namespace Gtk {

class MiscClass;

/// @class Misc misc.hh xfc/gtk/misc.hh
/// @brief A GtkMisc C++ wrapper class.
///
/// The Misc widget is an abstract widget which is not useful itself, but is used to derive
/// subclasses which have alignment and padding attributes. The horizontal and vertical 
/// padding attributes allows extra space to be added around the widget. The horizontal and
/// vertical alignment attributes enable the widget to be positioned within its allocated 
/// area. Note that if the widget is added to a container in such a way that it expands 
/// automatically to fill its allocated area, the alignment settings will not alter the
/// widgets position.

class Misc : public Widget
{
	friend class G::Object;

	Misc(const Misc&);
	Misc& operator=(const Misc&);
	
protected:
/// @name Constructors
/// @{

	Misc();
	///< Construct a new Misc.

	explicit Misc(GtkMisc *misc, bool owns_reference = false);
	///< Construct a new Misc from an existing GtkMisc.
	///< @param misc A pointer to a GtkMisc.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>misc</EM> can be a newly created GtkMisc or an existing
	///< GtkMisc (see G::Object::Object).

/// @}

public:
	typedef GtkMisc CObjectType;

/// @name Constructors
/// @{

	virtual ~Misc();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkMisc* gtk_misc() const;
	///< Get a pointer to the GtkMisc structure.

	operator GtkMisc* () const;
	///< Conversion operator; safely converts a Misc to a GtkMisc pointer.

	void get_alignment(float *xalign, float *yalign);
	///< Gets the X and Y alignment of the widget within its allocation (see set_alignment()).
	///< @param xalign The location to store X alignment of misc, or null.
	///< @param yalign The location to store Y alignment of misc, or null.

	void get_padding(int *xpad, int *ypad);
	///< Gets the padding in the X and Y directions of the widget (see set_padding()).
	///< @param xpad The location to store padding in the X direction, or null.
	///< @param ypad The location to store padding in the Y direction, or null.

/// @}
/// @name Methods
/// @{

	void set_alignment(float xalign, float yalign);
	///< Sets the alignment of the widget.
	///< @param xalign The horizontal alignment, from 0 (left) to 1 (right).
	///< @param yalign The vertical alignment, from 0 (top) to 1 (bottom).

	void set_padding(int xpad, int ypad);
	///< Sets the amount of space to add around the widget.
	///< @param xpad The amount of space to add on the left and right of the widget, in pixels.
	///< @param ypad The amount of space to add on the top and bottom of the widget, in pixels.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/misc.inl>

#endif // XFC_GTK_MISC_HH

