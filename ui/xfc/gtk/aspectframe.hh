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
 
/// @file xfc/gtk/aspectframe.hh
/// @brief A GtkAspectFrame C++ wrapper interface.
///
/// Provides AspectFrame, a widget that is useful when you want pack a widget so that it can
/// resize but always retains the same aspect ratio.

#ifndef XFC_GTK_ASPECT_FRAME_HH
#define XFC_GTK_ASPECT_FRAME_HH

#ifndef XFC_GTK_FRAME_HH
#include <xfc/gtk/frame.hh>
#endif

#ifndef __GTK_ASPECT_FRAME_H__
#include <gtk/gtkaspectframe.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class AspectFrame aspectframe.hh xfc/gtk/aspectframe.hh
/// @brief A GtkAspectFrame C++ wrapper class.
///
/// The AspectFrame is useful when you want pack a widget so that it can resize but always retains
/// the same aspect ratio. For instance, one might be drawing a small preview of a larger image.
/// AspectFrame derives from Frame, so it can draw a label and a frame around the child. The frame
/// will be "shrink-wrapped" to the size of the child. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/aspectframes.html">AspectFrame</A> HOWTO and example.

class AspectFrame : public Frame
{
	friend class G::Object;

	AspectFrame(const AspectFrame&);
	AspectFrame& operator=(const AspectFrame&);
	
protected:
/// @name Constructors
/// @{

	explicit AspectFrame(GtkAspectFrame *aspect_frame, bool owns_reference = false);
	///< Construct a new AspectFrame from an existing GtkAspectFrame.
	///< @param aspect_frame A pointer to a GtkAspectFrame.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>aspect_frame</EM> can be a newly created GtkAspectFrame or an existing
	///< GtkAspectFrame. (see G::Object::Object).

/// @}

public:
	typedef GtkAspectFrame CObjectType;

/// @name Constructors
/// @{

	AspectFrame();
	///< Construct an AspectFrame with xalign 0.5, yalign 0.5, ratio 1.0 and obey_child true.

	AspectFrame(float xalign, float yalign);
	///< Construct an AspectFrame with the specified xalign and yalign values.
	///< @param xalign The horizontal alignment of the child within the allocation of the
	///<               AspectFrame; this ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param yalign The vertical alignment of the child within the allocation of the
	///<               AspectFrame. This ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///<
	///< This constructor takes the aspect ratio from the requistion of the child. This is the
	///< same as setting obey_child to true.

	AspectFrame(float xalign, float yalign, float ratio);
	///< Construct an AspectFrame with the specified xalign, yalign and ratio values.
	///< @param xalign The horizontal alignment of the child within the allocation of the
	///<               AspectFrame; this ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param yalign The vertical alignment of the child within the allocation of the
	///<               AspectFrame. This ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param ratio  The desired aspect ratio.
	///<
	///< This constructor takes the aspect ratio from <EM>ratio</EM> and sets obey_child to false.

	AspectFrame(const char *label, float xalign, float yalign, float ratio);
	AspectFrame(const String& label, float xalign, float yalign, float ratio);
	///< Construct a labelled AspectFrame with the specified xalign, yalign and ratio values.
	///< @param label The label text.
	///< @param xalign The horizontal alignment of the child within the allocation of the
	///<               AspectFrame; this ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param yalign The vertical alignment of the child within the allocation of the
	///<               AspectFrame. This ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param ratio  The desired aspect ratio.
	///<
	///< This constructor takes the aspect ratio from <EM>ratio</EM> and sets obey_child to false.

	virtual ~AspectFrame();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkAspectFrame* gtk_aspect_frame() const;
	///< Get a pointer to the GtkAspectFrame structure.

	operator GtkAspectFrame* () const;
	///< Conversion operator; safely converts an AspectFrame to a GtkAspectFrame pointer.

/// @}
/// @name Methods
/// @{

	void set(float xalign, float yalign, float ratio, bool obey_child);
	///< Sets the parameters for an existing AspectFrame.
	///< @param xalign The horizontal alignment of the child within the allocation of the
	///<               AspectFrame; this ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param yalign The vertical alignment of the child within the allocation of the
	///<               AspectFrame. This ranges from 0.0 (left aligned) to 1.0 (right aligned).
	///< @param ratio  The desired aspect ratio.
	///< @param obey_child If <EM>true</EM>, ratio is ignored, and the aspect ratio is taken
	///<                   from the requistion of the child.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/aspectframe.inl>

#endif // XFC_GTK_ASPECT_FRAME_HH

