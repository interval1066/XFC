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

/// @file xfc/gtk/tooltips.hh
/// @brief A GtkTooltips C++ wrapper interface.
///
/// Provides Tooltips, an object that contains a message that appears next to a widget
/// when the mouse pointer is held over it for a short amount of time.

#ifndef XFC_GTK_TOOLTIPS_HH
#define XFC_GTK_TOOLTIPS_HH

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

#ifndef __GTK_TOOLTIPS_H__
#include <gtk/gtktooltips.h>
#endif

namespace Xfc {

namespace Gtk {

class Tooltips;
class Widget;

/// @class TooltipsData tooltips.hh xfc/gtk/tooltips.hh
/// @brief A GtkTooltipsData C++ wrapper class.
///
/// TooltipsData stores the data associated with a widget (see Gtk::Tooltips::data_get()). 
///
/// <B>See also:</B> the <A HREF="../../howto/html/tooltips.html">Tooltip Object</A> HOWTO.
 
class TooltipsData
{
	GtkTooltipsData data_;
public:
/// @name Accessors
/// @{

	GtkTooltipsData* gtk_tooltips_data() const;
	///< Get a pointer to the GtkTooltipsData structure.

	Tooltips* tooltips() const;
	///< The Tooltips group that this tooltip belongs to.

	String tip_text() const;
	///< The string containing the tooltip message itself.

	String tip_private() const;
	///< The string that is not shown as the default tooltip. This message may be more
	///< informative and go towards forming a context-sensitive help system for your
	///< application. 
	
/// @}
};

/// @class Tooltips tooltips.hh xfc/gtk/tooltips.hh
/// @brief A GtkTooltips C++ wrapper class.
///
/// Tooltips are the messages that appear next to a widget when the mouse pointer
/// is held over it for a short amount of time. They are especially helpful for
/// adding more verbose descriptions of things such as buttons in a toolbar.
///
/// An individual tooltip belongs to a group of tooltips. A group is created with
/// the default constructor Tooltips(). Every tooltip in the group can then be
/// turned off with a call to disable() and enabled with enable(). To assign a tip
/// to a particular Widget, set_tip() is used. 
///
/// Note, Tooltips can only be set on widgets which have their own X window. To
/// check if a widget has its own window use Gtk::Widget::has_no_window(). To 
/// add a tooltip to a widget that doesn't have its own window, place the widget
/// inside an EventBox and add a tooltip to that instead.
///
/// The default appearance of all tooltips in a program is determined by the 
/// current GTK+ theme that the user has selected. Information about the tooltip
/// (if any) associated with an arbitrary widget can be retrieved using data_get(). 

class Tooltips : public Object
{
	friend class G::Object;

	Tooltips(const Tooltips&);
	Tooltips& operator=(const Tooltips&);
	
protected:
/// @name Constructors
/// @{

	explicit Tooltips(GtkTooltips *tooltips, bool owns_reference = false);
	///< Construct a new Tooltips from an existing GtkTooltips.
	///< @param tooltips A pointer to a GtkTooltips.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tooltips</EM> can be a newly created GtkTooltips or an existing
	///< GtkTooltips (see G::Object::Object).
	
/// @}
	
public:
	typedef GtkTooltips CObjectType;

/// @name Constructors
/// @{

	Tooltips();
	///< Constructs an empty group of tooltips.
	
	virtual ~Tooltips();
	///< Destructor.
	
/// @}	
/// @name Accessors
/// @{

	GtkTooltips* gtk_tooltips() const;
	///< Get a pointer to the GtkTooltips structure.
	
	operator GtkTooltips* () const;
	///< Conversion operator; safely converts a Tooltips to a GtkTooltips pointer.

	bool is_enabled() const;
	///< Returns true if tooltips are enabled.

/// @}

	static TooltipsData* data_get(Widget& widget);
	///< Retrieves any TooltipsData previously associated with the given widget.
	///< @param widget A Widget. 
	///< @return A TooltipsData object, or null if the widget has no tooltip.
		
/// @name Methods
/// @{

	void enable();
	///< Allows the user to see your tooltips as they navigate your application.
	
	void disable();
	///< Causes all tooltips in tooltips to become inactive. Any widgets that have
	///< tips associated with that group will no longer display their tips until
	///< they are enabled again with enable().

	void set_tip(Widget& widget, const char *tip_text, const char *tip_private = 0);
	void set_tip(Widget& widget, const String& tip_text, const String& tip_private = 0);
	///< Adds a tooltip containing the message <EM>tip_text</EM> to the specified Widget.
	///< @param widget The Widget you wish to associate the tip with. 
	///< @param tip_text A string containing the tip itself. 
	///< @param tip_private A string of any further information that may be useful if the user gets stuck. 
		
	void unset_tip(Widget& widget);
	///< Unsets any previously set tooltip associated with <EM>widget</EM>.
	///< @param widget A Widget.

	void force_window();
	///< Ensures that the window used for displaying the given tooltips is created. Applications
	///< should never have to call this method, since GTK+ takes care of this.
	 	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/tooltips.inl>

#endif // XFC_GTK_TOOLTIPS_HH

