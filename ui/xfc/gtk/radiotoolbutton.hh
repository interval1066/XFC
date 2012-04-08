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

/// @file xfc/gtk/radiotoolbutton.hh
/// @brief A GtkRadioToolButton C++ wrapper interface.
///
/// Provides RadioToolButton, a Gtk::ToolItem subclass that displays a radio button. 

#ifndef XFC_GTK_RADIO_TOOL_BUTTON_HH
#define XFC_GTK_RADIO_TOOL_BUTTON_HH

#ifndef XFC_GTK_TOGGLE_TOOL_BUTTON_HH
#include <xfc/gtk/toggletoolbutton.hh>
#endif

#ifndef __GTK_RADIO_TOOL_BUTTON_H__
#include <gtk/gtkradiotoolbutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class RadioToolButton radiotoolbutton.hh xfc/gtk/radiotoolbutton.hh
/// @brief A GtkRadioToolButton C++ wrapper class.
///
/// A RadioToolButton is a ToolItem that contains a radio button, that is, a button that is
/// part of a group of toggle buttons where only one button can be active at a time. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTO.

class RadioToolButton : public ToggleToolButton
{
	friend class G::Object;

	RadioToolButton(const RadioToolButton&);
	RadioToolButton& operator=(const RadioToolButton&);

protected:
/// @name Constructors
/// @{

	explicit RadioToolButton(GtkRadioToolButton *button, bool owns_reference = false);
	///< Construct a new RadioToolButton from an existing GtkRadioToolButton.
	///< @param button A pointer to a GtkRadioToolButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button</EM> can be a newly created GtkRadioToolButton or an existing
	///< GtkRadioToolButton (see G::Object::Object).

/// @}

public:
	typedef GtkRadioToolButton CObjectType;
	
	typedef GSList Group;
	///< The radio tool button group.
	
/// @name Constructors
/// @{
	
	RadioToolButton();
	///< Constructs an empty radio tool button that is the first member of a new group.

	explicit RadioToolButton(const RadioToolButton *group);
	///< Constructs a new radio tool button that is a member of a <EM>group</EM>.
	///< @param group An existing RadioToolButton, or null to start a new group.
	
	RadioToolButton(const RadioToolButton *group, const StockId& stock_id);
	///< Constructs a new radio tool button that is a member of a <EM>group</EM>.
	///< @param group An existing RadioToolButton, or null to start a new group.
	///< @param stock_id The stock item ID.
	///< 	
	///< The new radio tool button will contain an icon and label from the stock item 
	///< indicated by <EM>stock_id</EM>.

	virtual ~RadioToolButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkRadioToolButton* gtk_radio_tool_button() const;
	///< Get a pointer to the GtkRadioToolButton structure.

	operator GtkRadioToolButton* () const;
	///< Conversion operator; safely converts an RadioToolButton to a GtkRadioToolButton pointer.

	Group* get_group() const;
	///< Gets the radio button group the button belongs to.
	///< @return The group button belongs to.
		
/// @}
/// @name Methods
/// @{

	void set_group(Group *group);
	///< Adds the button to <EM>group</EM>, removing it from the group it belonged to before.
	///< @param group An existing radio button group.
		
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/radiotoolbutton.inl>

#endif // XFC_GTK_RADIO_TOOL_BUTTON_HH

