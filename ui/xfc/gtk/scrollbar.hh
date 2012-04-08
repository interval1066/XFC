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
 
/// @file xfc/gtk/scrollbar.hh
/// @brief A GtkScrollbar, GtkHScrollbar and GtkVScrollbar C++ wrapper interface.
///
/// Provides Scrollbar, HScrollbar and VScrollbar, widgets that let you scroll other widgets.

#ifndef XFC_GTK_SCROLLBAR_HH
#define XFC_GTK_SCROLLBAR_HH

#ifndef XFC_GTK_RANGE_HH
#include <xfc/gtk/range.hh>
#endif

#ifndef __GTK_HSCROLLBAR_H__
#include <gtk/gtkhscrollbar.h>
#endif

#ifndef __GTK_VSCROLLBAR_H__
#include <gtk/gtkvscrollbar.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Scrollbar scrollbar.hh xfc/gtk/scrollbar.hh
/// @brief A GtkScrollbar C++ wrapper class.
///
/// The Scrollbar widget is an abstract base class for HScrollbar and VScrollbar. It is not very 
/// useful in itself. The position of the thumb in a scrollbar is controlled by the scroll 
/// adjustments. See Adjustment for the fields in an adjustment - for Scrollbar, the "value" field
/// represents the position of the scrollbar, which must be between the <EM>lower</EM> field and 
/// <EM>upper - page_size</EM>. The <EM>page_size</EM> field represents the size of the visible 
/// scrollable area. The <EM>step_increment</EM> and <EM>page_increment</EM> fields are used when
/// the user asks to step down (using the small stepper arrows) or page down (using for example the
/// Page Down key). 
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class Scrollbar : public Range
{
	friend class G::Object;

	Scrollbar(const Scrollbar&);
	Scrollbar& operator=(const Scrollbar&);
	
protected:
/// @name Constructors
/// @{

	explicit Scrollbar(GtkScrollbar *scrollbar, bool owns_reference = false);
	///< Construct a new Scrollbar from an existing GtkScrollbar.
	///< @param scrollbar A pointer to a GtkScrollbar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>scrollbar</EM> can be a newly created GtkScrollbar or an existing
	///< GtkScrollbar(see G::Object::Object).
	
	virtual ~Scrollbar() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkScrollbar CObjectType;

/// @name Accessors
/// @{

	GtkScrollbar* gtk_scrollbar() const;
	///< Get a pointer to the GtkScrollbar structure.

	operator GtkScrollbar* () const;
	///< Conversion operator; safely converts a Scrollbar to a GtkScrollbar pointer.

/// @}
};

/// @class HScrollbar scrollbar.hh xfc/gtk/scrollbar.hh
/// @brief A GtkHScrollbar C++ wrapper class.
///
/// The HScrollbar widget is a widget arranged horizontally creating a scrollbar. See Scrollbar
/// for details on scrollbars. An Adjustment may be added to handle the adjustment of the
/// scrollbar.
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class HScrollbar : public Scrollbar
{
	friend class G::Object;

	HScrollbar(const HScrollbar&);
	HScrollbar& operator=(const HScrollbar&);
	
protected:
/// @name Constructors
/// @{

	explicit HScrollbar(GtkHScrollbar *hscrollbar, bool owns_reference = false);
	///< Construct a new HScrollbar from an existing GtkHScrollbar.
	///< @param hscrollbar A pointer to a GtkScrollbar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hscrollbar</EM> can be a newly created GtkHScrollbar or an existing
	///< GtkHScrollbar (see G::Object::Object).
	
/// @}
	
public:
	typedef GtkHScrollbar CObjectType;

/// @name Constructors
/// @{

	HScrollbar();
	///< Construct a new horizontal scrollbar; the scrollbar will create an adjustment for you.

	explicit HScrollbar(Adjustment& adjustment);
	///< Construct a new horizontal scrollbar with the specified adjustment.
	///< @param adjustment The Adjustment to use.

	virtual ~HScrollbar();
	///< Destructor.
	
/// @}	
/// @name Accessors

	GtkHScrollbar* gtk_hscrollbar() const;
	///< Get a pointer to the GtkHScrollbar structure.
	
	operator GtkHScrollbar* () const;
	///< Conversion operator; safely converts a HScrollbar to a GtkHScrollbar pointer.
	
/// @}
};

/// @class VScrollbar scrollbar.hh xfc/gtk/scrollbar.hh
/// @brief A GtkVScrollbar C++ wrapper class.
///
/// The VScrollbar widget is a widget arranged vertically creating a scrollbar. See Scrollbar
/// for details on scrollbars. An Adjustment may be added to handle the adjustment of the
/// scrollbar.
///
/// <B>See also:</B> the <A HREF="../../howto/html/rangewidgets.html">Range Widget</A> HOWTO and example.

class VScrollbar : public Scrollbar
{
	friend class G::Object;

	VScrollbar(const VScrollbar&);
	VScrollbar& operator=(const VScrollbar&);
	
protected:
/// @name Constructors
/// @{

	explicit VScrollbar(GtkVScrollbar *vscrollbar, bool owns_reference = false);
	///< Construct a new VScrollbar from an existing GtkVScrollbar.
	///< @param vscrollbar A pointer to a GtkVScrollbar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vscrollbar</EM> can be a newly created GtkVScrollbar or an existing
	///< GtkVScrollbar (see G::Object::Object).
	
/// @}

public:
	typedef GtkVScrollbar CObjectType;

/// @name Constructors
/// @{

	VScrollbar();
	///< Construct a new vertical scrollbar; the scrollbar will create an adjustment for you.

	explicit VScrollbar(Adjustment& adjustment);
	///< Construct a new vertical scrollbar with the specified adjustment.
	///< @param adjustment The Adjustment to use.

	virtual ~VScrollbar();
	///< Destructor.
	
/// @}
/// @name Accessors	
/// @{

	GtkVScrollbar* gtk_vscrollbar() const;
	///< Get a pointer to the GtkVScrollbar structure.
	
	operator GtkVScrollbar* () const;
	///< Conversion operator; safely converts a VScrollbar to a GtkVScrollbar pointer.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/scrollbar.inl>

#endif // XFC_GTK_SCROLLBAR_HH

