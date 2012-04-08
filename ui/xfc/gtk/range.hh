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
 
/// @file xfc/gtk/range.hh
/// @brief A GtkRange C++ wrapper interface.
///
/// Provides Range, a widget that is the base class for widgets that show an adjustable range,
/// such as Scale and Scrollbar.

#ifndef XFC_GTK_RANGE_HH
#define XFC_GTK_RANGE_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_RANGE_H__
#include <gtk/gtkrange.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Range range.hh xfc/gtk/range.hh
/// @brief A GtkRange C++ wrapper class.
///
/// Range is the base class for widgets that show an adjustable range, such as Scale and Scrollbar.
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class Range : public Widget
{
	friend class G::Object;
	
	Range(const Range&);
	Range& operator=(const Range&);
	
protected:
/// @name Constructors
/// @{

	Range();
	///< Construct a new Range.

	explicit Range(GtkRange *range, bool owns_reference = false);
	///< Construct a new Range from an existing GtkRange.
	///< @param range A pointer to a GtkRange.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>range</EM> can be a newly created GtkRange or an existing
	///< GtkRange (see G::Object::Object).
	
	virtual ~Range() = 0;
	///< Destructor.
	
/// @}
/// @name Signal Prototypes

	typedef G::Signal<void> ValueChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ValueChangedSignalType> ValueChangedSignalProxy;
	static const ValueChangedSignalType value_changed_signal;
	///< Value changed signal (see signal_value_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, double> AdjustBoundsSignalType;
	typedef G::SignalProxy<TypeInstance, AdjustBoundsSignalType> AdjustBoundsSignalProxy;
	static const AdjustBoundsSignalType adjust_bounds_signal;
	///< Adjust bounds signal (see signal_adjust_bounds()). Calls a slot with the signature:
	///< @code
	///< void function(double new_value);
	///< // new_value: The new range value.
	///< @endcode
	
/// @}

public:
	typedef GtkRange CObjectType;

/// @name Accessors
/// @{

	GtkRange* gtk_range() const;
	///< Get a pointer to the GtkRange structure.
	
	operator GtkRange* () const;
	///< Conversion operator; safely converts a Range to a GtkRange pointer.
	
	UpdateType get_policy() const;
	///< Gets the update policy of range (see set_update_policy()).
	///< @return The current update policy. 

	Adjustment* get_adjustment() const;
	///< Get the Adjustment which is the "model" object for Range (see set_adjustment() for details).
	///< @return The Adjustemnt.
	///<
	///< The return value does not have a reference added, so it should not be unreferenced.

	bool get_inverted() const;
	///< Gets the value set by set_inverted().
	///< @return <EM>true</EM> if the range is inverted. 
 
	double get_value() const;
	///< Gets the current value of the range.

/// @}
/// @name Methods
/// @{

	void set_round_digits(int round_digits);
	///< Set the number of digits to round off the value to, or -1 for no rounding.
	
	void set_update_policy(UpdateType policy);
	///< Sets the update policy for the range. 
	///< @param policy The update policy. 
	///<	
	///< UPDATE_CONTINUOUS means that anytime the range slider is moved, the range value will
	///< change and the value_changed signal will be emitted. UPDATE_DELAYED means that the value
	///< will be updated after a brief timeout where no slider motion occurs, so updates are spaced
	///< by a short time rather than continuous. UPDATE_DISCONTINUOUS means that the value will
	///< only be updated when the user releases the button and ends the slider drag operation.

	void set_adjustment(Adjustment *adjustment);
	///< Sets the adjustment to be used as the "model" object for this range widget. 
	///< @param adjustment The Adjustment.
	///<
	///< The adjustment indicates the current range value, the minimum and maximum
	///< range values, the step/page increments used for keybindings and scrolling, and
	///< the page size. The page size is normally 0 for Scale and non-zero for Scrollbar,
	///< and indicates the size of the visible area of the widget being scrolled. The
	///< page size affects the size of the scrollbar slider.

	void set_inverted(bool setting);
	///< Sets whether the lower to higher values should be inverted.
	///< @param setting Set <EM>true</EM> to invert the range.
	///<
	///< Ranges normally move from lower to higher values as the slider moves from top to bottom
	///< or left to right. Inverted ranges have higher values at the top or on the left rather than
	///< on the bottom or right.

	void set_increments(double step, double page);
	///< Sets the step and page sizes for the range.
	///< @param step The step size. 
	///< @param page The page size. 
	///<	
	///< The step size is used when the user clicks the Scrollbar arrows or moves GtkScale via
	///< arrow keys. The page size is used for example when moving via Page Up or Page Down keys.

	void set_range(double min, double max);
	///< Sets the allowable values in the Range, and clamps the range value to be between min and max.
	///< @param min The minimum range value.
	///< @param max The maximum range value.
	///< 
	///< If the range has a non-zero page size, it is clamped between min and max - page-size.

	void set_value(double value);
	///< Sets the current value of the range; if the value is outside the minimum or maximum 
	///< range values, it will be clamped to fit inside them. 
	///< @param value The new value of the range. 
	///<
	///< The range emits the "value_changed" signal if the value changes.

/// @}
/// @name Signal Proxies
/// @{

	const ValueChangedSignalProxy signal_value_changed();
	///< Connect to the value_changed_signal; emitted when the range value changes.

	const AdjustBoundsSignalProxy signal_adjust_bounds();
	///< Connect to the adjust_bounds_signal; emitted when the bounds of the range might need
	///< adjusting when a new range value is set.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/range.inl>

#endif // XFC_GTK_RANGE_HH

