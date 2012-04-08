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
 
/// @file xfc/gtk/scale.hh
/// @brief A GtkScale, GtkHScale and GtkVScale C++ wrapper interface.
///
/// Provides Scale, a widget used only for deriving the subclasses HScale and VScale.

#ifndef XFC_GTK_SCALE_HH
#define XFC_GTK_SCALE_HH

#ifndef XFC_GTK_RANGE_HH
#include <xfc/gtk/range.hh>
#endif

#ifndef __GTK_HSCALE_H__
#include <gtk/gtkhscale.h>
#endif

#ifndef __GTK_VSCALE_H__
#include <gtk/gtkvscale.h>
#endif

namespace Xfc {

namespace Pango {
class Layout;
}

namespace Gtk {

/// @class Scale scale.hh xfc/gtk/scale.hh
/// @brief A GtkScale C++ wrapper class.
///
/// The Scale widget is an abstract class, used only for deriving the subclasses HScale and VScale.
///
/// A Scale is a slider control used to select a numeric value. To use it, you'll probably want to
/// investigate the methods on its base class, Range, in addition to the methods for Scale itself.
/// To set the value of a scale, you would normally use Gtk::Range::set_value(). To detect changes
/// to the value, you would normally connect to the <EM>value_changed</EM> signal. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class Scale : public Range
{
	friend class G::Object;

	Scale(const Scale&);
	Scale& operator=(const Scale&);

protected:
/// @name Constructors
/// @{

	Scale();
	///< Construct a new Scale.

	explicit Scale(GtkScale *scale, bool owns_reference = false);
	///< Construct a new Scale from an existing GtkScale.
	///< @param scale A pointer to a GtkScale.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>scale</EM> can be a newly created GtkScale or an existing
	///< GtkScale (see G::Object::Object).

	virtual ~Scale() = 0;
	///< Destructor.

/// @}
/// @name Signal Prototpyes

	typedef G::Signal<char*, double> FormatValueSignalType;
	typedef G::SignalProxy<TypeInstance, FormatValueSignalType> FormatValueSignalProxy;
	static const FormatValueSignalType format_value_signal;
	///< Format value signal (see signal_format_value()). Calls a slot with the signature:
	///< @code
	///< char* function(double value);
	///< // value: The scale value to format.
	///< // return: An allocated string representing value.
	///< @endcode
	
/// @}

public:
	typedef GtkScale CObjectType;

/// @name Accessors
/// @{

	GtkScale* gtk_scale() const;
	///< Get a pointer to the GtkScale structure.

	operator GtkScale* () const;
	///< Conversion operator; safely converts a Scale to a GtkScale pointer.

	int get_digits() const;
	///< Gets the number of decimal places that are displayed in the value. 

	bool get_draw_value() const;
	///< Returns whether the current value is displayed as a string next to the slider. 

	PositionType get_value_pos() const;
	///< Gets the position in which the current value is displayed. 
	/// @return The position in which the current value is displayed. 
 
	Pango::Layout* get_layout() const;
	///< Gets the Pango::Layout used to display the scale. 
	///< @return The Pango::Layout for this scale, or null if set_draw_value() is set to false. 

	void get_layout_offsets(int *x, int *y) const;
	///< Obtains the coordinates where the scale will draw the Pango::Layout 
	///< representing the text in the scale. 
	///< @param x The location to store X offset of layout, or null. 
	///< @param y The location to store Y offset of layout, or null.
	///<	
	///< Remember when using Pango::Layout you need to convert to and from pixels using
	///< PANGO_PIXELS() or PANGO_SCALE. If set_draw_value() is set to false, the return 
	///< values are undefined.

/// @}
/// @name Methods
/// @{

	void set_digits(int digits);
	///< Sets the number of decimal places that are displayed in the value. 
	///< @param digits The number of decimal places to display, e.g. use 1 to display 1.0, 2 to display 1.00 etc.
	///<
	///< Also causes the value of the adjustment to be rounded off to this number of digits,
	///< so the retrieved value matches the value the user saw. 
 
	void set_draw_value(bool draw_value);
	///< Specifies whether the current value is displayed as a string next to the slider. 
	///< @param draw_value Set <EM>true</EM> to display the current value.
 
 	void set_value_pos(PositionType pos);
	///< Sets the position in which the current value is displayed. 
	///< @param pos The position in which the current value is displayed. 
 
/// @}
/// @name Signal Proxies
/// @{

	const FormatValueSignalProxy signal_format_value();
	///< Connect to the format_value_signal; emitted to format the scale value before it gets displayed.
	
/// @}
};

/// @class HScale scale.hh xfc/gtk/scale.hh
/// @brief A GtkHScale C++ wrapper class.
///
/// The HScale widget is used to allow the user to select a value using a horizontal slider.
/// The position to show the current value, and the number of decimal places shown can be
/// set using the parent Scale class's methods.
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class HScale : public Scale
{
	friend class G::Object;

	HScale(const HScale&);
	HScale& operator=(const HScale&);

protected:
/// @name Constructors
/// @{

	explicit HScale(GtkHScale *hscale, bool owns_reference = false);
	///< Construct a new HScale from an existing GtkHScale.
	///< @param hscale A pointer to a GtkHScale.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hscale</EM> can be a newly created GtkHScale or an existing
	///< GtkHScale (see G::Object::Object).

/// @}
	
public:
	typedef GtkHScale CObjectType;

/// @name Constructors
/// @{

	HScale();
	///< Construct a new horizontal scale.

	explicit HScale(Adjustment& adjustment);
	///< Construct a new horizontal scale with the specified adjustement.
	///< @param adjustment The Adjustment which sets the range of the scale.

	HScale(double min, double max, double step = 1.0);
	///< Construct a new horizontal scale that lets the user input a number between min and max
	///< (including min and max) with the increment step.
	///< @param min The minimum value.
	///< @param max The maximum value.
	///< @param step The step increment (tick size) used with keyboard shortcuts.
	///<
	///< The <EM>step</EM> must be nonzero; it's the distance the slider moves when using
	///< the arrow keys to adjust the scale value.

	virtual ~HScale();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkHScale* gtk_hscale() const;
	///< Get a pointer to the GtkHScale structure.
	
	operator GtkHScale* () const;
	///< Conversion operator; safely converts a HScale to a GtkHScale pointer.
	
/// @}
};

/// @class VScale scale.hh xfc/gtk/scale.hh
/// @brief A GtkVScale C++ wrapper class.
///
/// The VScale widget is used to allow the user to select a value using a vertical slider.
/// The position to show the current value, and the number of decimal places shown can be
/// set using the parent Scale class's methods.
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class VScale : public Scale
{
	friend class G::Object;

	VScale(const VScale&);
	VScale& operator=(const VScale&);
	
protected:
/// @name Constructors
/// @{

	explicit VScale(GtkVScale *vscale, bool owns_reference = false);
	///< Construct a new VScale from an existing GtkVScale.
	///< @param vscale A pointer to a GtkVScale.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vscale</EM> can be a newly created GtkVScale or an existing
	///< GtkVScale (see G::Object::Object).
	
/// @}

public:
	typedef GtkVScale CObjectType;

/// @name Constructors
/// @{

	VScale();
	///< Construct a new vertical scale.

	explicit VScale(Adjustment& adjustment);
	///< Construct a new vertical scale with the specified adjustement.
	///< @param adjustment The Adjustment which sets the range of the scale.

	VScale(double min, double max, double step = 1.0);
	///< Construct a new vertical scale that lets the user input a number between min and max
	///< (including min and max) with the increment step.
	///< @param min The minimum value.
	///< @param max The maximum value.
	///< @param step The step increment (tick size) used with keyboard shortcuts.
	///<
	///< The <EM>step</EM> must be nonzero; it's the distance the slider moves when using
	///< the arrow keys to adjust the scale value.

	virtual ~VScale();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkVScale* gtk_vscale() const;
	///< Get a pointer to the GtkVScale structure.
	
	operator GtkVScale* () const;
	///< Conversion operator; safely converts a VScale to a GtkVScale pointer.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/scale.inl>

#endif // XFC_GTK_SCALE_HH

