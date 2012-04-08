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
 
/// @file xfc/gtk/viewport.hh
/// @brief A GtkViewport C++ wrapper interface.
/// 
/// Provides Viewport, a widget that allows you to see part of a child widget and scroll
/// the contents of the child.

#ifndef XFC_GTK_VIEWPORT_HH
#define XFC_GTK_VIEWPORT_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_VIEWPORT_H__
#include <gtk/gtkviewport.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Viewport viewport.hh xfc/gtk/viewport.hh
/// @brief A GtkViewport C++ wrapper class.
///
/// The Viewport widget provides you with the capability to see part of a child widget
/// and scroll the contents of the child. It is normally not accessed directly but used
/// by other widgets, particularly the ScrollWindow, for child widgets that do not have
/// their own scrolling capability.
///
/// <B>See also:</B> the <A HREF="../../howto/html/viewports.html">Viewport</A> and
/// <A HREF="../../howto/html/scrolledwindows.html">ScrolledWindow</A> HOWTOs.

class Viewport : public Bin
{
	friend class G::Object;

	Viewport(const Viewport&);
	Viewport& operator=(const Viewport&);

protected:
/// @name Constructors
/// @{

	explicit Viewport(GtkViewport *viewport, bool owns_reference = false);
	///< Construct a new Viewport from an existing GtkViewport.
	///< @param viewport A pointer to a GtkViewport.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>viewport</EM> can be a newly created GtkViewport or an existing
	///< GtkViewport (see G::Object::Object).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Adjustment*, Adjustment*> SetScrollAdjustmentsSignalType;
	typedef G::SignalProxy<TypeInstance, SetScrollAdjustmentsSignalType> SetScrollAdjustmentsSignalProxy;
	static const SetScrollAdjustmentsSignalType set_scroll_adjustments_signal;
	///< Set scroll adjustments signal (see signal_set_scroll_adjustments()). Calls a slot with the signature:
	///< @code
	///< void function(Adjustment *hadjustment, Adjustment *vadjustment);
	///< // hadjustment: The horizontal adjustment.
	///< // vadjustment: The vertical adjustment.
	///< @endcode
	
/// @}

public:
	typedef GtkViewport CObjectType;

/// @name Constructors
/// @{

	Viewport();
	///< Construct a new viewport.

	Viewport(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Construct a new viewport with the given adjustments.
	///< @param hadjustment The horizontal adjustment. 
	///< @param vadjustment The vertical adjustment. 
	
	virtual ~Viewport();
	///< Destructor.
	
/// @}	
/// @name Accessors
/// @{

	GtkViewport* gtk_viewport() const;
	///< Get a pointer to the GtkViewport structure.
	
	operator GtkViewport* () const;
	///< Conversion operator; safely converts a Viewport to a GtkViewport pointer.

	Adjustment* get_hadjustment() const;
	///< Returns the horizontal adjustment of the viewport. If the adjustment has not
	///< been set a default adjustment with all values set to zero will be returned.

	Adjustment* get_vadjustment() const;
	///< Returns the vertical adjustment of the viewport. If the adjustment has not
	///< been set a default adjustment with all values set to zero will be returned.

	ShadowType get_shadow_type() const;
	///< Returns the shadow type of the viewport (see set_shadow_type()).

/// @}
/// @name Methods
/// @{

	void set_hadjustment(Adjustment *adjustment);
	///< Sets the horizontal adjustment of the viewport.
	///< @param adjustment An Adjustment.
	 	
	void set_vadjustment(Adjustment *adjustment);
	///< Sets the vertical adjustment of the viewport.
	///< @param adjustment An Adjustment.
	
	void set_shadow_type(ShadowType type);
	///< Sets the shadow type of the viewport.
	///< @param type The new shadow type.
	
/// @}	
/// @name Signal Proxies
/// @{
	
	const SetScrollAdjustmentsSignalProxy signal_set_scroll_adjustments();
	///< Connect to the set_scroll_adjustments_signal; emitted when a viewport is added to
	///< a scrolling aware parent.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/viewport.inl>

#endif // XFC_GTK_VIEWPORT_HH

