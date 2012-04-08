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

/// @file xfc/gtk/toolbutton.hh
/// @brief A GtkToolButton C++ wrapper interface.
///
/// Provides ToolButton, a Gtk::ToolItem subclass that displays buttons. 

#ifndef XFC_GTK_TOOL_BUTTON_HH
#define XFC_GTK_TOOL_BUTTON_HH

#ifndef XFC_GTK_TOOL_ITEM_HH
#include <xfc/gtk/toolitem.hh>
#endif

#ifndef __GTK_TOOL_BUTTON_H__
#include <gtk/gtktoolbutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToolButton toolbutton.hh xfc/gtk/toolbutton.hh
/// @brief A GtkToolButton C++ wrapper class.
///
/// ToolButton is a ToolItem that contains a button. A ToolButton can be constructed
/// using a custom icon widget or a stock item. 
///
/// The label of a ToolButton is determined by the properties "label_widget", "label",
/// and "stock_id". If "label_widget" is set, then that widget is used as the label.
/// Otherwise, if "label" is set, that string is used as the label. Otherwise, if 
/// "stock_id" is set, the label is determined by the stock item. Otherwise, the 
/// button does not have a label. 
///
/// The icon of a ToolButton is determined by the properties "icon_widget" and "stock_id".
/// If "icon_widget" is set, then that widget is used as the icon. Otherwise, if "stock_id"
/// is set, the icon is determined by the stock item. Otherwise, the button does not have
/// an icon. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTO.

class ToolButton : public ToolItem
{
	friend class G::Object;

	ToolButton(const ToolButton&);
	ToolButton& operator=(const ToolButton&);

protected:
/// @name Constructors
/// @{

	explicit ToolButton(GtkToolButton *tool_button, bool owns_reference = false);
	///< Construct a new ToolButton from an existing GtkToolButton.
	///< @param tool_button A pointer to a GtkToolButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tool_button</EM> can be a newly created GtkToolButton or an existing
	///< GtkToolButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ClickedSignalType;
	typedef G::SignalProxy<TypeInstance, ClickedSignalType> ClickedSignalProxy;
	static const ClickedSignalType clicked_signal;
	///< Clicked signal (see signal_clicked()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkToolButton CObjectType;

/// @name Constructors
/// @{
	
	ToolButton();
	///< Constructs an empty tool button.

	ToolButton(Widget& icon_widget);
	///< Constructs a new tool button using <EM>icon_widget</EM> as the icon.
	///< @param icon_widget A widget that will be used as the icon widget.
	
	ToolButton(const char *label, bool use_underline = false);
	ToolButton(const String& label, bool use_underline = false);
	///< Constructs a new tool button using <EM>label</EM> as the label.
	///< @param label A string that will be used as the label.
	///< @param use_underline Whether the button label has the mnemonic form "_Open". 
	
	ToolButton(Widget& icon_widget, const char *label, bool use_underline = false);
	ToolButton(Widget& icon_widget, const String& label, bool use_underline = false);
	///< Constructs a new tool button using <EM>icon_widget</EM> as the icon and
	///< <EM>label</EM> as the label.
	///< @param icon_widget A widget that will be used as the icon widget.
	///< @param label A string that will be used as the label.
	///< @param use_underline Whether the button label has the mnemonic form "_Open". 
 	
	ToolButton(const StockId& stock_id);
	///< Constructs a new tool button containing the image and text from a stock item.
	///< @param stock_id The ID of the stock item (see set_stock_id()).
	///<
	///< It is an error if <EM>stock_id</EM> is not a name of a stock item.

	virtual ~ToolButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkToolButton* gtk_tool_button() const;
	///< Get a pointer to the GtkToolButton structure.

	operator GtkToolButton* () const;
	///< Conversion operator; safely converts an ToolButton to a GtkToolButton pointer.

	String get_label() const;
	///< Gets the label used by the tool button, or a null String if the tool button 
	///< doesn't have a label, or uses the label from a stock item. 
	///< @return The label, or a null String.

	bool get_use_underline() const;
	///< Determines whether underscores in the label property are used as mnemonics 
	///< on menu items on the overflow menu (see set_use_underline()).
	///< @return <EM>true</EM> if underscores in the label property are used as mnemonics. 
	
	String get_stock_id() const;
	///< Determines the ID of the stock item (see set_stock_id()).
	///< @return The ID of the stock item for the button.
	
	Widget* get_icon_widget() const;
	///< Gets the widget used as the icon widget the button, or null.
	///< @return The widget used as the icon on the button, or null.
	
	Widget* get_label_widget() const;
	///< Gets the the widget used as label on the button (see set_label_widget()).
	///< @return The widget used as the label on the button, or null.
	
/// @}
/// @name Methods
/// @{

	void set_label(const char *label, bool use_underline = false);
	void set_label(const String& label, bool use_underline = false);
	///< Sets <EM>label</EM> as the label used for the tool button. 
	///< @param label A string that will be used as label, or null. 
	///< @param use_underline Whether the button label has the mnemonic form "_Open" 
	///<	
	///< This method sets the 'label' property. The label property only has an effect
	///< if not overridden by a non-null 'label_widget' property. If both the 'label_widget' 
	///< and 'label' properties are null, the label is determined by the 'stock_id' property.
	///< If the 'stock_id' property is also null, the button will not have a label.

	void set_use_underline(bool use_underline);
	///< If set, an underline in the label property indicates that the next character
	///< should be used for the mnemonic accelerator key in the overflow menu. 
	///< @param use_underline Whether the button label has the mnemonic form "_Open" 
	///<	
	///< For example, if the label property is "_Open" and use_underline is <EM>true</EM>,
	///< the label on the tool button will be "Open" and the item on the overflow menu will
	///< have an underlined 'O'. 
	///<
	///< Labels shown on tool buttons never have mnemonics on them; this property only affects
	///< the menu item on the overflow menu.

	void set_stock_id(const StockId& stock_id);
	///< Sets the ID of the stock item. 
	///< @param stock_id The ID of the stock item (such as Gtk::Stock::OK and Gtk::Stock::APPLY).
	///<	
	///< The 'stock_id' property only has an effect if not overridden by non-null 'label'
	///< and 'icon_widget' properties.

	void set_icon_widget(Widget *icon_widget);
	///< Sets <EM>icon_widget</EM> as the widget used as the icon on the button. 
	///< @param icon_widget The widget used as the icon, or null.
	///<	
	///< If <EM>icon_widget</EM> is null the icon is determined by the 'stock_id' property.
	///< If the 'stock_id' property is also null, the button will not have an icon.

	void set_label_widget(Widget *label_widget);
	///< Sets <EM>label_widget</EM> as the widget used as the label for the button.
	///< @param label_widget The widget used as the label, or null.
	///<	 
	///< If <EM>label_widget</EM> is null the 'label' property is used as the label.
	///< If 'label' is also null, the label in the stock item determined by the 'stock_id'
	///< property is used as the label. If 'stock_id' is also null, the button does not 
	///< have a label.
	
	void set_contents(Widget& icon_widget, const char *label, bool use_underline = false);
	void set_contents(Widget& icon_widget, const String& label, bool use_underline = false);
	///< Sets <EM>icon_widget</EM> as the widget used as the icon and <EM>label</EM> as
	///< the label used for the tool button. 
	///< @param icon_widget The widget used as the icon.
	///< @param label A string that will be used as label, or null. 
	///< @param use_underline Whether the button label has the mnemonic form "_Open" 
	///< 
	///< This convenience method is equivalent to calling set_icon_widget() and
	///< set_label() separately. It also calls show() on the <EM>icon_widget</EM>. 	

/// @}
/// @name Signal Proxies
/// @{

	const ClickedSignalProxy signal_clicked();
	///< Connect to the clicked_signal; emitted when the tool button is clicked
	///< with the mouse or activated with the keyboard.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/toolbutton.inl>

#endif // XFC_GTK_TOOL_BUTTON_HH

