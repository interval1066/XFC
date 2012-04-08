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
 
/// @file xfc/gtk/adjustment.hh
/// @brief A GtkAdjustment C++ wrapper interface.
///
/// Provides Adjustment, an object that represents a value which has an associated lower
/// and upper bound, together with step and page increments, and a page size. It is used
/// within several widgets, including SpinButton, Viewport, and Range (which is a base 
/// class for HScrollbar, VScrollbar, HScale, and VScale).

#ifndef XFC_GTK_ADJUSTMENT_HH
#define XFC_GTK_ADJUSTMENT_HH

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

#ifndef __GTK_ADJUSTMENT_H__
#include <gtk/gtkadjustment.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Adjustment adjustment.hh xfc/gtk/adjustment.hh
/// @brief A GtkAdjustment C++ wrapper class.
///
/// The Adjustment object represents a value which has an associated lower and upper bound,
/// together with step and page increments, and a page size. It is used within several
/// widgets, including SpinButton, Viewport, and Range (which is a base class for HScrollbar,
/// VScrollbar, HScale, and VScale).
///
/// The Adjustment object does not update the value itself. Instead it is left up to the
/// owner of the Adjustment to control the value. The owner of the Adjustment typically 
/// calls the value_changed() and changed() methods after changing the value and its bounds.
/// This results in the emission of the <EM>value_changed</EM> or <EM>changed</EM> signal
/// respectively.
///
/// <B>See also:</B> the <A HREF="../../howto/html/adjustments.html">Adjustment</A> and
/// <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTOs and example.

class Adjustment : public Object
{
	friend class G::Object;

	Adjustment(const Adjustment&);
	Adjustment& operator=(const Adjustment&);
	
protected:
/// @name Constructors
/// @{

	explicit Adjustment(GtkAdjustment *adjustment, bool owns_reference = false);
	///< Construct a new Adjustment from an existing GtkAdjustment.
	///< @param adjustment A pointer to a GtkAdjustment.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>adjustment</EM> can be a newly created GtkAdjustment or an existing
	///< GtkAdjustment. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Adjustment changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ValueChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ValueChangedSignalType> ValueChangedSignalProxy;
	static const ValueChangedSignalType value_changed_signal;
	///< Adjustment value changed signal (see signal_value_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkAdjustment CObjectType;

/// @name Constructors
/// @{

	Adjustment();
	///< Construct an empty Adjustment.

	Adjustment(double lower, double upper, double step_increment, double page_increment, double page_size);
	///< Construct a new Adjustment.
	///< @param lower The minimum value.
	///< @param upper The maximum value.
	///< @param step_increment The step increment.
	///< @param page_increment The page increment.
	///< @param page_size The page size.
	///<
	///< The <EM>step_increment</EM> is the increment to use to make minor changes to the value.
	///< In a Scrollbar this increment is used when the mouse is clicked on the arrows at the top
	///< and bottom of the scrollbar, to scroll by a small amount. The <EM>page_increment</EM> is
	///< the increment to use to make major changes to the value. In a Scrollbar this increment is
	///< used when the mouse is clicked in the trough, to scroll by a large amount. The page size
	///< in a Scrollbar is the size of the area which is currently visible.

	Adjustment(double value, double lower, double upper, double step_increment, double page_increment, double page_size);
	///< Construct a new Adjustment.
	///< @param value The initial value.
	///< @param lower The minimum value.
	///< @param upper The maximum value.
	///< @param step_increment The step increment.
	///< @param page_increment The page increment.
	///< @param page_size The page size.
	///<
	///< The step increment is the increment to use to make minor changes to the value.
	///< The page increment is the increment to use to make major changes to the value.

	virtual ~Adjustment();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkAdjustment* gtk_adjustment() const;
	///< Get a pointer to the GtkAdjustment structure.

	operator GtkAdjustment* () const;
	///< Conversion operator; safely converts an Adjustment to a GtkAdjustment pointer.

	double lower() const;
	///< Get the minimum value for the adjustment.

	double upper() const;
	///< Get the maximum value for the adjustment.

	double step_increment() const;
	///< Get the step increment of the adjustment.

	double page_increment() const;
	///< Get the page increment of the adjustment.

	double page_size() const;
	///< Get the page size of the adjustment.

	double get_value() const;
	///< Get the current value of the adjustment.

/// @}
/// @name Methods
/// @{

	void changed();
	///< Emits a <EM>changed</EM> signal from the Adjustment. 
	///< This is typically called by the owner of the Adjustment after it has changed
	///< any of the Adjustment fields other than the value.

	void value_changed();
	///< Emits a <EM>value_changed</EM> signal from the Adjustment. 
	///< This is typically called by the owner of the Adjustment after it has changed
	///< the Adjustment value field.

	void clamp_page(double lower, double upper);	
	///< Updates the Adjustment value to ensure that the range between lower and upper
	///< is in the current page (i.e. between value and value + page_size).
	///< @param lower The lower value.
	///< @param upper The upper value.
	///<
	///< If the range is larger than the page size, then only the start of it will
	///< be in the current page. A <EM>changed</EM> signal will be emitted if the value
	///< is changed.

	void set_value(double value);
	///< Sets the Adjustment value.
	///< @param value The new value.

	void set_range(double lower, double upper, double step_increment, double page_increment, double page_size);
	///< Sets the Adjustment fields other than the value.
	///< @param lower The minimum value.
	///< @param upper The maximum value.
	///< @param step_increment The step increment.
	///< @param page_increment The page increment.
	///< @param page_size The page size.
	///<
	///< The step increment is the increment to use to make minor changes to the value.
	///< The page increment is the increment to use to make major changes to the value.

/// @}
/// @name Signal Proxies
/// @{

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted when one or more of the Adjustment fields
	///< have been changed, other than the value field.

	const ValueChangedSignalProxy signal_value_changed();
	///< Connect to the value_changed_signal; emitted when the Adjustment value field has been changed.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/adjustment.inl>

#endif // XFC_GTK_ADJUSTMENT_HH

