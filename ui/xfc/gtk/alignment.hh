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

/// @file xfc/gtk/alignment.hh
/// @brief A GtkAlignment C++ wrapper interface.
///
/// Provides Alignment, a widget that controls the alignment and size of its child widget.

#ifndef XFC_GTK_ALIGNMENT_HH
#define XFC_GTK_ALIGNMENT_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_ALIGNMENT_H__
#include <gtk/gtkalignment.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Alignment alignment.hh xfc/gtk/alignment.hh
/// @brief A GtkAlignment C++ wrapper class.
///
/// The Alignment widget controls the alignment and size of its child widget.
/// It has four settings: xscale, yscale, xalign, and yalign.
///
/// The scale settings are used to specify how much the child widget should
/// expand to fill the space allocated to the Alignment. The values can range
/// from 0 (meaning the child doesn't expand at all) to 1 (meaning the child
/// expands to fill all of the available space).
///
/// The align settings are used to place the child widget within the available
/// area. The values range from 0 (top or left) to 1 (bottom or right). 
/// Of course, if the scale settings are both set to 1, the alignment settings
/// have no effect.
///
/// <B>See also:</B> the <A HREF="../../howto/html/alignment.html">Alignment Widget</A> and
/// <A HREF="../../howto/html/progressbar.html">ProgressBar</A> HOWTOs and examples.

class Alignment : public Bin
{
	friend class G::Object;

	Alignment(const Alignment&);
	Alignment& operator=(const Alignment&);
	
protected:
/// @name Constructors
/// @{

	explicit Alignment(GtkAlignment *alignment, bool owns_reference = false);
	///< Construct a new Alignment from an existing GtkAlignment.
	///< @param alignment T pointer to a GtkAlignment.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>alignment</EM> can be a newly created GtkAlignment or an existing
	///< GtkAlignment. (see G::Object::Object).

/// @}

public:
	typedef GtkAlignment CObjectType;

/// @name Constructors
/// @{

	Alignment();
	///< Construct an Alignment with the default values 0.5 for xalign and yalign and
	///< 1.0 for xscale and yscale.

	Alignment(float xalign, float yalign, float xscale = 0.0, float yscale = 0.0);
	///< Construct a new Alignment.
	///< @param xalign The horizontal alignment of the child widget, from 0 (left) to 1 (right).
	///< @param yalign The vertical alignment of the child widget, from 0 (top) to 1 (bottom).
	///< @param xscale The amount that the child widget expands horizontally to fill up unused
	///<               space, from 0 to 1. A value of 0 indicates that the child widget should
	///<               never expand. A value of 1 indicates that the child widget will expand
	///<               to fill all of the space allocated for the GtkAlignment.
	///< @param yscale The amount that the child widget expands vertically to fill up unused
	///                space, from 0 to 1. The values are similar to xscale.
	
	virtual ~Alignment();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkAlignment* gtk_alignment() const;
	///< Get a pointer to the GtkAlignment structure.

	operator GtkAlignment* () const;
	///< Conversion operator; safely converts an Alignment to a GtkAlignment pointer.

	void get_padding(unsigned int *top, unsigned int *bottom, unsigned int *left, unsigned int *right) const;
	///< Gets the padding on the different sides of the widget (see set_padding()).
	///< @param top The location to store the padding for the top of the widget, or null.
	///< @param bottom The location to store the padding for the bottom of the widget, or null.
	///< @param left The location to store the padding for the left of the widget, or null.
	///< @param right The ocation to store the padding for the right of the widget, or null.

/// @}
/// @name Methods
/// @{

	void set(float xalign, float yalign, float xscale, float yscale);
	///< Sets the Alignment values.
	///< @param xalign The horizontal alignment of the child widget, from 0 (left) to 1 (right).
	///< @param yalign The vertical alignment of the child widget, from 0 (top) to 1 (bottom).
	///< @param xscale The amount that the child widget expands horizontally to fill up unused
	///<               space, from 0 to 1. A value of 0 indicates that the child widget should
	///<               never expand. A value of 1 indicates that the child widget will expand
	///<               to fill all of the space allocated for the GtkAlignment.
	///< @param yscale The amount that the child widget expands vertically to fill up unused
	///                space, from 0 to 1. The values are similar to xscale.


	void set_padding(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right);
	///< Sets the padding on the different sides of the widget.
	///< @param top The padding at the top of the widget.
	///< @param bottom The padding at the bottom of the widget.
	///< @param left The padding at the left of the widget.
 	///< @param right The padding at the right of the widget.
	///<
	///< The padding adds blank space to the sides of the widget. For instance, this can be used
	///< to indent the child widget towards the right by adding padding on the left.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/alignment.inl>

#endif // XFC_GTK_ALIGNMENT_HH

