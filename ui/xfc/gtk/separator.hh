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
 
/// @file xfc/gtk/separator.hh
/// @brief A GtkSeparator, GtkHSeparator and GtkVSeparator C++ wrapper interface.
///
/// Provides Separator, HSeparator and VSeparator. Separator is an abstract widget class used
/// only for deriving the subclasses HSeparator and VSeparator. HSeparator is a horizontal 
/// separator and VSeparator is a vertical separator used to group widgets within a window.

#ifndef XFC_GTK_SEPARATOR_HH
#define XFC_GTK_SEPARATOR_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_HSEPARATOR_H__
#include <gtk/gtkhseparator.h>
#endif

#ifndef __GTK_VSEPARATOR_H__
#include <gtk/gtkvseparator.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Separator separator.hh xfc/gtk/separator.hh
/// @brief A GtkSeparator C++ wrapper class.
///
/// The Separator widget is an abstract class, used only for deriving the subclasses HSeparator and VSeparator.

class Separator : public Widget
{
	friend class G::Object;

	Separator(const Separator&);
	Separator& operator=(const Separator&);
	
protected:
/// @name Constructors
/// @{

	Separator();
	///< Construct a new Separator.

	explicit Separator(GtkSeparator *separator, bool owns_reference = false);
	///< Construct a new Separator from an existing GtkSeparator.
	///< @param separator A pointer to a GtkSeparator.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>separator</EM> can be a newly created GtkSeparator or an existing
	///< GtkSeparator (see G::Object::Object).

	virtual ~Separator() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkSeparator CObjectType;

/// @name Accessors
/// @{

	GtkSeparator* gtk_separator() const;
	///< Get a pointer to the GtkSeparator structure.

	operator GtkSeparator* () const;
	///< Conversion operator; safely converts a Separator to a GtkSeparator pointer.

/// @}
};

/// @class HSeparator separator.hh xfc/gtk/separator.hh
/// @brief A GtkHSeparator C++ wrapper class.
///
/// The HSeparator widget is a horizontal separator, used to group the widgets within a window.
/// It displays a horizontal line with a shadow to make it appear sunken into the interface.
/// Note, the HSeparator widget cannot used as a separator within menus. To create a separator
/// in a menu use a SeparatorMenuItem widget.

class HSeparator : public Separator
{
	friend class G::Object;

	HSeparator(const HSeparator&);
	HSeparator& operator=(const HSeparator&);
	
protected:
/// @name Constructors
/// @{

	explicit HSeparator(GtkHSeparator *hseparator, bool owns_reference = false);
	///< Construct a new HSeparator from an existing GtkHSeparator.
	///< @param hseparator A pointer to a GtkHSeparator.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hseparator</EM> can be a newly created GtkHSeparator or an existing
	///< GtkHSeparator (see G::Object::Object).

/// @}

public:
	typedef GtkHSeparator CObjectType;

/// @name Constructors
/// @{

	HSeparator();
	///< Construct a new horizontal separator.

	virtual ~HSeparator();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkHSeparator* gtk_hseparator() const;
	///< Get a pointer to the GtkHSeparator structure.

	operator GtkHSeparator* () const;
	///< Conversion operator; safely converts a HSeparator to a GtkHSeparator pointer.

/// @}
};

/// @class VSeparator separator.hh xfc/gtk/separator.hh
/// @brief A GtkVSeparator C++ wrapper class.
///
/// The VSeparator widget is a vertical separator, used to group the widgets within a window.
/// It displays a vertical line with a shadow to make it appear sunken into the interface.

class VSeparator : public Separator
{
	friend class G::Object;

	VSeparator(const VSeparator&);
	VSeparator& operator=(const VSeparator&);
	
protected:
/// @name Constructors
/// @{

	explicit VSeparator(GtkVSeparator *vseparator, bool owns_reference = false);
	///< Construct a new VSeparator from an existing GtkVSeparator.
	///< @param vseparator A pointer to a GtkVSeparator.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vseparator</EM> can be a newly created GtkVSeparator or an existing
	///< GtkVSeparator (see G::Object::Object).

/// @}

public:
	typedef GtkVSeparator CObjectType;

/// @name Constructors
/// @{

	VSeparator();
	///< Construct a new vertical separator.

	virtual ~VSeparator();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkVSeparator* gtk_vseparator() const;
	///< Get a pointer to the GtkVSeparator structure.

	operator GtkVSeparator* () const;
	///< Conversion operator; safely converts a VSeparator to a GtkVSeparator pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/separator.inl>

#endif // XFC_GTK_SEPARATOR_HH

