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

/// @file xfc/gtk/expander.hh
/// @brief A GtkExpander C++ wrapper interface.
///
/// Provides Expander, a container which can hide its child.

#ifndef XFC_GTK_EXPANDER_HH
#define XFC_GTK_EXPANDER_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_EXPANDER_H__
#include <gtk/gtkexpander.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Expander expander.hh xfc/gtk/expander.hh
/// @brief A GtkExpander C++ wrapper class.
///
/// An Expander allows the user to hide or show its child by clicking on an expander
/// triangle similar to the triangles used in a Gtk::TreeView. Normally you use an 
/// expander as you would use any other descendant of Gtk::Bin; you create the child
/// widget and use Gtk::Container::add() to add it to the expander. When the expander
/// is toggled, it will take care of showing and hiding the child automatically. 
/// 
/// <HR><B>Special Usage</B>
///
/// There are situations in which you may prefer to show and hide the expanded widget yourself,
/// such as when you want to actually create the widget at expansion time. In this case, create
/// a Gtk::Expander but do not add a child to it. The expander widget has an expanded property
/// which can be used to monitor its expansion state. You should watch this property with a 
/// signal connection as follows: 
///
/// @code
/// Gtk::Expander *expander = new Gtk::Expander("_More Options", true);
/// expander->signal_notify("expanded").connect(this, &MyExpander::on_expanded);
/// 
/// ...
/// 
/// void 
/// MyExpander::on_expanded(GParamSpec *param_spec)
/// {
/// 	if (get_expanded())
/// 	{
/// 		// Show or create widgets
/// 	}
/// 	else
/// 	{
/// 		// Hide or destroy widgets
/// 	}
/// }
/// @endcode

class Expander : public Bin
{
	friend class G::Object;

	Expander(const Expander&);
	Expander& operator=(const Expander&);

protected:
/// @name Constructors
/// @{

	explicit Expander(GtkExpander *expander, bool owns_reference = false);
	///< Construct a new Expander from an existing GtkExpander.
	///< @param expander A pointer to a GtkExpander.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>expander</EM> can be a newly created GtkExpander or an existing 
	///< GtkExpander (see G::Object::Object).

/// @}

public:
	typedef GtkExpander CObjectType;

/// @name Constructors
/// @{

	Expander(const char *label, bool use_underline = false);
	Expander(const String& label, bool use_underline = false);
	///< Constructs a new expander using label as the text of the label.
	///< @param label The text of the label.
	///< @param use_underline Whether a character preceded by an underscore is underlined.
	///<	 
	///< If characters in label are preceded by an underscore and <EM>use_underline</EM>
	///< is true, they are underlined. If <EM>use_underline</EM> is true and you need a 
	///< literal underscore character in a label, use '__' (two underscores). The first 
	///< underlined character represents a keyboard accelerator called a mnemonic. Pressing
	///< Alt and that key activates the button.

	virtual ~Expander();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkExpander* gtk_expander() const;
	///< Get a pointer to the GtkExpander structure.

	operator GtkExpander* () const;
	///< Conversion operator; safely converts an Expander to a GtkExpander pointer.

	bool get_expanded() const;
	///< Queries the expander and returns its current state (see set_expanded()). 
	///< @return <EM>true</EM> if the child widget is revealed, <EM>false</EM> if not. 
	
	int get_spacing() const;
	///< Gets the value set by set_spacing().
	///< @return The spacing between the expander and child in pixels.
	
	String get_label() const;
	///< Fetches the text from the label of the expander, as set by set_label(). 
	///< @return The text of the label widget.
	///<	
	///< If the label text has not been set the return value will be a null String.
	///< This will be the case if you create an empty Gtk::Button to use as a container.

	bool get_use_underline() const;
	///< Determines whether an embedded underline in the expander label indicates
	///< a mnemonic (see set_use_underline()).
	///< @return <EM>true</EM> if an embedded underline in the expander label indicates
	///< a mnemonic accelerator key.
	 
	bool get_use_markup() const;
	///< Determines whether the label's text is interpreted as marked up with the 
	///< Pango text markup language (see set_use_markup()).
	///< @return <EM>true</EM> if the label's text will be parsed for markup.
	 
	Widget* get_label_widget() const;
	///< Retrieves the label widget for the frame (see set_label_widget()).
	///< @return The label widget, or null if there is none. 

/// @}
/// @name Methods
/// @{

	void set_expanded(bool expanded);
	///< Sets the state of the expander.
	///< @param expanded Whether the child widget is revealed.
	///<
	///< Set <EM>expanded</EM> true if you want the child widget to be revealed, 
	///< and false if you want the child widget to be hidden.

	void set_spacing(int spacing);
	///< Sets the spacing field of expander, which is the number of pixels
	///< to place between expander and the child.
	///< @param spacing The distance between the expander and child in pixels.
	
	void set_label(const char *label);
	void set_label(const String& label);
	///< Sets the text of the label of the expander to <EM>label</EM>. 
	///< @param label A text string. 
	///<
	///< This will also clear any previously set labels.
	
	void set_use_underline(bool use_underline);
	///< If true, an underline in the text of the expander label indicates the 
	///< next character should be used for the mnemonic accelerator key.
	///< @param use_underline Set <EM>true</EM> if underlines in the text indicate mnemonics.
	 
	void set_use_markup(bool use_markup);
	///< Sets whether the text of the label contains markup in Pango's text markup language
	///< (see Gtk::Label::set_markup()).
	///< @param use_markup Set <EM>true</EM> if the label's text should be parsed for markup.
	 
	void set_label_widget(Widget *label_widget);
	///< Set the label widget for the expander. 
	///< @param label_widget The new label widget.
	///<	
	///< This is the widget that will appear embedded alongside the expander arrow.
	 
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/expander.inl>

#endif // XFC_GTK_EXPANDER_HH

