/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gtk/progressbar.hh
/// @brief A GtkProgressBar C++ wrapper interface.
///
/// Provides ProgressBar, a widget that is typically used to display the progress
/// of a long running operation.

#ifndef XFC_GTK_PROGRESS_BAR_HH
#define XFC_GTK_PROGRESS_BAR_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef XFC_PANGO_LAYOUT_HH
#include <xfc/pango/layout.hh>
#endif

#ifndef __GTK_PROGRESS_BAR_H__
#include <gtk/gtkprogressbar.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum ProgressBarOrientation
/// Represents the possible orientations and growth directions for the visible progress bar.

enum ProgressBarOrientation
{
	PROGRESS_LEFT_TO_RIGHT = GTK_PROGRESS_LEFT_TO_RIGHT, 
	///< A horizontal progress bar growing from left to right.

	PROGRESS_RIGHT_TO_LEFT = GTK_PROGRESS_RIGHT_TO_LEFT, 
	///< A horizontal progress bar growing from right to left.

	PROGRESS_BOTTOM_TO_TOP = GTK_PROGRESS_BOTTOM_TO_TOP, 
	///< A vertical progress bar growing from bottom to top.

	PROGRESS_TOP_TO_BOTTOM = GTK_PROGRESS_TOP_TO_BOTTOM
	  ///< A vertical progress bar growing from top to bottom.
};

/// @class ProgressBar progressbar.hh xfc/gtk/progressbar.hh
/// @brief A GtkProgressBar C++ wrapper class.
///
/// The ProgressBar is typically used to display the progress of a long running operation.
/// It provides a visual clue that processing is underway. The ProgressBar can be used in
/// two different modes: percentage mode and activity mode.
///
/// When an application can determine how much work needs to take place (e.g. read a fixed
/// number of bytes from a file) and can monitor its progress, it can use the ProgressBar
/// in percentage mode and the user sees a growing bar indicating the percentage of the
/// work that has been completed. In this mode, the application is required to call 
/// set_fraction() periodically to update the progress bar. 
///
/// When an application has no accurate way of knowing the amount of work to do, it can use
/// the ProgressBar in activity mode, which shows activity by a block moving back and forth
/// within the progress area. In this mode, the application is required to call pulse() 
/// perodically to update the progress bar.
///
/// There is quite a bit of flexibility provided to control the appearance of the ProgressBar.
/// Functions are provided to control the orientation of the bar, optional text can be 
/// displayed along with the bar, and the step size used in activity mode can be set.
///
/// <B>See also:</B> the <A HREF="../../howto/html/progressbar.html">ProgressBar</A> HOWTO and example.

class ProgressBar : public Widget
{
	friend class G::Object;

	ProgressBar(const ProgressBar&);
	ProgressBar& operator=(const ProgressBar&);
	
protected:
/// @name Constructors
/// @{

	explicit ProgressBar(GtkProgressBar *progress_bar, bool owns_reference = false);
	///< Construct a new ProgressBar from an existing GtkProgressBar.
	///< @param progress_bar A pointer to a GtkProgressBar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>progress_bar</EM> can be a newly created GtkProgressBar or an existing
	///< GtkProgressBar (see G::Object::Object).

/// @}

public:
	typedef GtkProgressBar CObjectType;

/// @name Constructors
/// @{

	ProgressBar();
	///< Construct a new progress bar.

	explicit ProgressBar(ProgressBarOrientation orientation);
	///< Construct a new progress bar with the specified orientation.
	///< @param orientation The orientation of the progress bar.

	virtual ~ProgressBar();
	/// Destructor.

/// @}
/// @name Accessors
/// @{

	GtkProgressBar* gtk_progress_bar() const;
	///< Get a pointer to the GtkProgressBar structure.

	operator GtkProgressBar* () const;
	///< Conversion operator; safely converts a ProgressBar to a GtkProgressBar pointer.

	String get_text() const;
	/// Retrieves the text displayed superimposed on the progress bar, if any, otherwise null.

	double get_fraction() const;
	///< Returns the current fraction of the task that's been completed.
	///< @return A fraction from 0.0 to 1.0.

	double get_pulse_step() const;
	///< Retrieves the pulse step set with set_pulse_step().
	///< @return A fraction from 0.0 to 1.0.

	ProgressBarOrientation get_orientation() const;
	///< Retrieves the current progress bar orientation.

	Pango::EllipsizeMode get_ellipsize() const;
	///< Gets the preferred place to ellipsize the string, if the progressbar 
	///< does not have enough room to display the entire string.
	///< @return A Pango::EllipsizeMode.

/// @}
/// @name Methods
/// @{

	void pulse();
	///< Indicates that some progress is made, but you don't know how much. Causes the
	///< progress bar to enter "activity mode", where a block bounces back and forth.
	///< Each call to pulse() causes the block to move by a little bit (the amount of
	///< movement per pulse is determined by set_pulse_step()).

	void set_text(const char *text);
	void set_text(const String& text);
	///< Causes the given text to appear superimposed on the progress bar.
	///< @param text A text string.

	void set_fraction(double fraction);
	///< Causes the progress bar to "fill in" the given fraction of the bar.
	///< @param fraction The fraction of the task that's been completed.
	///<
	///< The fraction should be between 0.0 and 1.0, inclusive.

	void set_pulse_step(double fraction);
	///< Sets the fraction of total progress bar length to move the bouncing block
	///< for each call to pulse().
	///< @param fraction The fraction between 0.0 and 1.0.

	void set_orientation(ProgressBarOrientation orientation);
	///< Causes the progress bar to switch to a different orientation (left-to-right,
	///< right-to-left, top-to-bottom, or bottom-to-top).
	///< @param orientation The orientation of the progress bar.

	void set_ellipsize(Pango::EllipsizeMode mode);
	///< Sets the mode used to ellipsize (add an ellipsis: "...") the text if 
	///< there is not enough space to render the entire string.
	///< @param mode A Pango::EllipsizeMode.
	


/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/progressbar.inl>

#endif // XFC_GTK_PROGRESS_BAR_HH

