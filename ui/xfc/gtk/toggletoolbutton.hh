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

/// @file xfc/gtk/toggletoolbutton.hh
/// @brief A GtkToggleToolButton C++ wrapper interface.
///
/// Provides ToggleToolButton, a Gtk::ToolItem subclass that displays toggle tool buttons. 

#ifndef XFC_GTK_TOGGLE_TOOL_BUTTON_HH
#define XFC_GTK_TOGGLE_TOOL_BUTTON_HH

#ifndef XFC_GTK_TOOL_BUTTON_HH
#include <xfc/gtk/toolbutton.hh>
#endif

#ifndef __GTK_TOGGLE_TOOL_BUTTON_H__
#include <gtk/gtktoggletoolbutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToggleToolButton toggletoolbutton.hh xfc/gtk/toggletoolbutton.hh
/// @brief A GtkToggleToolButton C++ wrapper class.
///
/// A ToggleToolButton is a ToolItem that contains a toggle button. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTO.

class ToggleToolButton : public ToolButton
{
	friend class G::Object;

	ToggleToolButton(const ToggleToolButton&);
	ToggleToolButton& operator=(const ToggleToolButton&);

protected:
/// @name Constructors
/// @{

	explicit ToggleToolButton(GtkToggleToolButton *button, bool owns_reference = false);
	///< Construct a new ToggleToolButton from an existing GtkToggleToolButton.
	///< @param button A pointer to a GtkToggleToolButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button</EM> can be a newly created GtkToggleToolButton or an existing
	///< GtkToggleToolButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ToggledSignalType;
	typedef G::SignalProxy<TypeInstance, ToggledSignalType> ToggledSignalProxy;
	static const ToggledSignalType toggled_signal;
	///< Toggled signal (see signal_toggled()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkToggleToolButton CObjectType;

/// @name Constructors
/// @{
	
	ToggleToolButton();
	///< Constructs an empty toggle tool button.

	ToggleToolButton(const StockId& stock_id);
	///< Constructs a new toggle tool button containing the image and text from a stock item.
	///< @param stock_id The ID of the stock item (see set_stock_id()).
	///<
	///< It is an error if <EM>stock_id</EM> is not a name of a stock item.

	virtual ~ToggleToolButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkToggleToolButton* gtk_toggle_tool_button() const;
	///< Get a pointer to the GtkToggleToolButton structure.

	operator GtkToggleToolButton* () const;
	///< Conversion operator; safely converts an ToggleToolButton to a GtkToggleToolButton pointer.

	bool get_active() const;
	///< Queries a toggle tool button and returns its current state. 
	///< @return <EM>true</EM> if the toggle button is pressed in and <EM>false</EM> if it is raised.

/// @}
/// @name Methods
/// @{

	void set_active(bool is_active);
	///< Sets the status of the toggle tool button. 
	///< @param is_active Whether the button should be active or not.
	///<	
	///< Set to <EM>true</EM> if you want the toggle tool button to be 'pressed in', and 
	///< <EM>false</EM> to raise it. This action causes the toggled signal to be emitted.
	
/// @}
/// @name Signal Proxies
/// @{

	const ToggledSignalProxy signal_toggled();
	///< Connect to the toggled_signal; emitted whenever the toggle tool button changes state.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/toggletoolbutton.inl>

#endif // XFC_GTK_TOGGLE_TOOL_BUTTON_HH

