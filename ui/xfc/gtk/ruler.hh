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
 
/// @file xfc/gtk/ruler.hh
/// @brief A GtkRuler, GtkHRuler and GtkVRuler C++ wrapper interface.
///
/// Provides Ruler, a widget that is the base class for horizontal and vertical rulers.
/// Rulers are used to show the mouse pointer's location in a window.

#ifndef XFC_GTK_RULER_HH
#define XFC_GTK_RULER_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_HRULER_H__
#include <gtk/gtkhruler.h>
#endif

#ifndef __GTK_VRULER_H__
#include <gtk/gtkvruler.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Ruler ruler.hh xfc/gtk/ruler.hh
/// @brief A GtkRuler C++ wrapper class.
///
/// The Ruler widget is a base class for horizontal and vertical rulers. Rulers are used to show
/// the mouse pointer's location in a window. The ruler can either be horizontal or vertical on
/// the window. Within the ruler a small triangle indicates the location of the mouse relative to
/// the horizontal or vertical ruler. See HRuler to learn how to create a new horizontal ruler.
/// See VRuler to learn how to create a new vertical ruler. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/rulers.html">Ruler</A> HOWTO and example.

class Ruler : public Widget
{
	friend class G::Object;

	Ruler(const Ruler&);
	Ruler& operator=(const Ruler&);
	
protected:
/// @name Constructors
/// @{

	Ruler();
	///< Construct a new Ruler.

	explicit Ruler(GtkRuler *ruler, bool owns_reference = false);
	///< Construct a new Ruler from an existing GtkRuler.
	///< @param ruler A pointer to a GtkRuler.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>ruler</EM> can be a newly created GtkRuler or an existing
	///< GtkRuler (see G::Object::Object).
	
	virtual ~Ruler() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkRuler CObjectType;

/// @name Accessors
/// @{

	GtkRuler* gtk_ruler() const;
	///< Get a pointer to the GtkRuler structure.
	
	operator GtkRuler* () const;
	///< Conversion operator; safely converts a Ruler to a GtkRuler pointer.
	
	MetricType get_metric() const;
	///< Gets the units used for a Ruler (see gtk_ruler_set_metric()).
	///< @return The units currently used for the ruler. 

	double get_lower() const;
	///< Gets the lower limit of the ruler.
	
 	double get_upper() const;
 	///< Gets the upper limit of the ruler.
	
	double get_position() const;
	///< Gets the current position of the mark on the ruler.
	
 	void get_range(double *lower, double *upper, double *position, double *max_size = 0);
	///< Retrieves values indicating the range and current position of the ruler (see set_range()).
	///< @param lower The location to store lower limit of the ruler, or null. 
	///< @param upper The location to store upper limit of the ruler, or null. 
	///< @param position The location to store the current position of the mark on the ruler, or null. 
	///< @param max_size The location to store the maximum size of the ruler used when calculating
	///<                 the space to leave for the text, or null.
  	
/// @}
/// @name Methods
/// @{

	void set_metric(MetricType metric);
	///< Sets the ruler to the units defined. 
	///< @param metric The unit of measurement. 
	///<
	///< Available units are PIXELS, INCHES, or CENTIMETERS. The default unit of measurement
	///< is PIXELS. 

 	void set_range(double lower, double upper, double position, double max_size);
	///< Sets the range of the ruler using <EM>lower</EM>, <EM>upper</EM>, <EM>position</EM>,
	///< and <EM>max_size</EM>. 
	///< @param lower The upper limit of the ruler. 
	///< @param upper The lower limit of the ruler. 
	///< @param position The mark on the ruler.
 	///< @param max_size The maximum size of the ruler. 
	
	void draw_ticks();
	///< Draws the tick marks on the ruler.
	
	void draw_pos();
	///< Draws the position mark on the ruler.

/// @}
};

/// @class HRuler ruler.hh xfc/gtk/ruler.hh
/// @brief A GtkHRuler C++ wrapper class.
///
/// The HRuler widget is a widget arranged horizontally creating a ruler that is utilized
/// around other widgets such as a text widget. The ruler is used to show the location of
/// the mouse on the window and to show the size of the window in specified units. The
/// available units of measurement are PIXELS (the default), INCHES and CENTIMETERS. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/rulers.html">Ruler</A> HOWTO and example.

class HRuler : public Ruler
{
	friend class G::Object;

	HRuler(const HRuler&);
	HRuler& operator=(const HRuler&);
	
protected:
/// @name Constructors
/// @{

	explicit HRuler(GtkHRuler *hruler, bool owns_reference = false);
	///< Construct a new HRuler from an existing GtkHRuler.
	///< @param hruler A pointer to a GtkHRuler.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hruler</EM> can be a newly created GtkHRuler or an existing
	///< GtkHRuler (see G::Object::Object).
	
/// @}

public:
	typedef GtkHRuler CObjectType;

/// @name Constructors
/// @{

	HRuler();
	///< Contruct a new horizontal ruler with the default metric type Gtk::PIXELS. 
	
	HRuler(MetricType metric);
	///< Contruct a new horizontal ruler with the metric type set to <EM>metric</EM>. 
	///< @param metric The unit of measurement. 
	///<
	///< Available units are PIXELS, INCHES, or CENTIMETERS.
	
	virtual ~HRuler();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkHRuler* gtk_hruler() const;
	///< Get a pointer to the GtkHRuler structure.
	
	operator GtkHRuler* () const;
	///< Conversion operator; safely converts a HRuler to a GtkHRuler pointer.
	
/// @}
};

/// @class VRuler ruler.hh xfc/gtk/ruler.hh
/// @brief A GtkVRuler C++ wrapper class.
///
/// The VRuler widget is a widget arranged vertically creating a ruler that is utilized
/// around other widgets such as a text widget. The ruler is used to show the location of
/// the mouse on the window and to show the size of the window in specified units. The
/// available units of measurement are PIXELS (the default), INCHES and CENTIMETERS. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/rulers.html">Ruler</A> HOWTO and example.

class VRuler : public Ruler
{
	friend class G::Object;

	VRuler(const VRuler&);
	VRuler& operator=(const VRuler&);
	
protected:
/// @name Constructors
/// @{

	explicit VRuler(GtkVRuler *vruler, bool owns_reference = false);
	///< Construct a new VRuler from an existing GtkVRuler.
	///< @param vruler A pointer to a GtkVRuler.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vruler</EM> can be a newly created GtkVRuler or an existing
	///< GtkVRuler (see G::Object::Object).
	
/// @}

public:
	typedef GtkVRuler CObjectType;

/// @name Constructors
/// @{

	VRuler();
	///< Contruct a new vertical ruler with the default metric type Gtk::PIXELS. 
	
	VRuler(MetricType metric);
	///< Contruct a new vertical ruler with the metric type set to <EM>metric</EM>. 
	///< @param metric The unit of measurement. 
	///<
	///< Available units are PIXELS, INCHES, or CENTIMETERS.
	
	virtual ~VRuler();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkVRuler* gtk_vruler() const;
	///< Get a pointer to the GtkVRuler structure.
	
	operator GtkVRuler* () const;
	///< Conversion operator; safely converts a VRuler to a GtkVRuler pointer.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/ruler.inl>

#endif // XFC_GTK_RULER_HH

