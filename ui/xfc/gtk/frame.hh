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
 
/// @file xfc/gtk/frame.hh
/// @brief A GtkFrame C++ wrapper interface.
///
/// Provides Frame, a Bin widget that surrounds its child with a decorative frame
/// and an optional label.

#ifndef XFC_GTK_FRAME_HH
#define XFC_GTK_FRAME_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_FRAME_H__
#include <gtk/gtkframe.h>
#endif

namespace Xfc {

namespace Gtk {

class FrameClass;

/// @class Frame frame.hh xfc/gtk/frame.hh
/// @brief A GtkFrame C++ wrapper class.
///
/// The Frame widget is a Bin that surrounds its child with a decorative frame and
/// an optional label. If present, the label is drawn in a gap in the top side of
/// the frame. The position of the label can be controlled with set_label_align().
///
/// <B>See also:</B> the <A HREF="../../howto/html/frames.html">Frame Widget</A> HOWTO and example.

class Frame : public Bin
{
	friend class G::Object;

	Frame(const Frame&);
	Frame& operator=(const Frame&);
	
protected:
/// @name Constructors
/// @{

	explicit Frame(GtkFrame *frame, bool owns_reference = false);
	///< Construct a new Frame from an existing GtkFrame.
	///< @param frame A pointer to a GtkFrame.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>frame</EM> can be a newly created GtkFrame or an existing
	///< GtkFrame (see G::Object::Object).

/// @}

public:
	typedef GtkFrame CObjectType;

/// @name Constructors
/// @{

	explicit Frame(ShadowType type = SHADOW_ETCHED_IN);
	///< Construct a new Frame with the specified ShadowType and no label.
	///< @param type The shadow type.

	explicit Frame(const char *label, ShadowType type = SHADOW_ETCHED_IN);
	explicit Frame(const String& label, ShadowType type = SHADOW_ETCHED_IN);
	///< Construct a new Frame with the specified label and ShadowType.
	///< @param label The label text.
	///< @param type The shadow type.

	virtual ~Frame();
	///< Destructor.
	
/// @}
/// @name Accessors	
/// @{

	GtkFrame* gtk_frame() const;
	///< Get a pointer to the GtkFrame structure.

	operator GtkFrame* () const;
	///< Conversion operator; safely converts a Frame to a GtkFrame pointer.

	String get_label() const;
	///< If the frame has a label widget and it is a Label, return the text in the label widget,
	///< otherwise returns a null String.

	Widget* get_label_widget() const;
	/// Retrieves the label widget for the frame (see set_label_widget()).
	
	void get_label_align(float *xalign, float *yalign) const;
	///< Retrieves the X and Y alignment of the frame's label (see set_label_align()).
	///< @param xalign The location to store X alignment of frame's label, or null.
	///< @param yalign The location to store Y alignment of frame's label, or null.

	ShadowType get_shadow_type() const;
	///< Retrieves the shadow type of the frame (see set_shadow_type()).

/// @}
/// @name Methods
/// @{

	void remove_label();
	///< Removes the current label, if any.

	void set_label(const char *label);
	void set_label(const String& label);
	///< Set the text of the label.
	///< @param label The new label text.

	void set_label_widget(Widget& label_widget);
	///< Set the label widget for the frame. 
	///< @param label_widget The new label widget.
	///<
	///< This is the widget that will appear embedded in the top edge of the frame as a title.
	
	void set_label_align(float xalign, float yalign);
	///< Set the alignment of the Frame widget's label. 
	///< @param xalign The position of the label along the top edge of the widget.
	///< @param yalign The y alignment of the label.
	///<
	///< The default alignment value for a newly created Frame is 0.0. An xalign value
	///< of 0.0 represents left alignment; 1.0 represents right alignment. A yalign value
	///< 0.0 represents below the top edge; 1.0 represents above the top edge.
	
	void set_shadow_type(ShadowType type);
	///< Set the shadow type for the Frame widget.
	///< @param type The new shadow type.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/frame.inl>

#endif // XFC_GTK_FRAME_HH

