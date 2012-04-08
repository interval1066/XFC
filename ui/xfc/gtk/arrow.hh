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
 
/// @file xfc/gtk/arrow.hh
/// @brief A GtkArrow C++ wrapper interface.
///
/// Provides Arrow, a widget that can be used to draw simple arrows that need to point
/// in one of the four cardinal directions (up, down, left, or right).

#ifndef XFC_GTK_ARROW_HH
#define XFC_GTK_ARROW_HH

#ifndef XFC_GTK_MISC_HH
#include <xfc/gtk/misc.hh>
#endif

#ifndef __GTK_ARROW_H__
#include <gtk/gtkarrow.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Arrow arrow.hh xfc/gtk/arrow.hh
/// @brief A GtkArrow C++ wrapper class.
///
/// Arrow should be used to draw simple arrows that need to point in one of the four
/// cardinal directions (up, down, left, or right). The style of the arrow can be one
/// of shadow in, shadow out, etched in, or etched out.
///
/// Arrow will fill any space alloted to it, but since it is inherited from Misc, it
/// can be padded and/or aligned, to fill exactly the space the programmer desires.
/// The direction or style of an arrow can be changed after creation by using set().
///
/// <B>See also:</B> the <A HREF="../../howto/html/arrow.html">Arrow Widget</A> HOWTO and example.

class Arrow : public Misc
{
	friend class G::Object;

	Arrow(const Arrow&);
	Arrow& operator=(const Arrow&);
	
protected:
/// @name Constructors
/// @{
	
	explicit Arrow(GtkArrow *arrow, bool owns_reference = false);
	///< Construct a new Arrow from an existing GtkArrow.
	///< @param arrow A pointer to a GtkArrow.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>arrow</EM> can be a newly created GtkArrow or an existing
	///< GtkArrow. (see G::Object::Object).

/// @}

public:
	typedef GtkArrow CObjectType;

/// @name Constructors
/// @{

	Arrow();
	///< Construct an Arrow with the arrow type ARROW_RIGHT and the shadow type SHADOW_OUT.

	Arrow(ArrowType arrow_type, ShadowType shadow_type);
	///< Construct an Arrow with the specified direction and style.
	///< @param arrow_type The direction of the arrow, a valid ArrowType.
	///< @param shadow_type The style of the arrow, a valid ShadowType.

	virtual ~Arrow();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkArrow* gtk_arrow() const;
	///< Get a pointer to the GtkArrow structure.

	operator GtkArrow* () const;
	///< Conversion operator; safely converts an Arrow to a GtkArrow pointer.

/// @}
/// @name Methods
/// @{

	void set(ArrowType arrow_type, ShadowType shadow_type);
	///< Sets the direction and style of the Arrow.
	///< @param arrow_type The direction of the arrow, a valid ArrowType.
	///< @param shadow_type The style of the arrow, a valid ShadowType.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/arrow.inl>

#endif // XFC_GTK_ARROW_HH

