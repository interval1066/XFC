/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
//! @file xfc/sourceview/sourceview.hh
//! @brief A GtkSourceView C++ wrapper interface.
//!
//! Provides SourceView, an object that extends the Gtk::TextView widget by implementing
//! syntax highlighting and other features typical of a source code editor.

#ifndef XFC_GTK_SOURCE_VIEW_HH
#define XFC_GTK_SOURCE_VIEW_HH

#ifndef XFC_GTK_TEXT_VIEW_HH
#include <xfc/gtk/textview.hh>
#endif

#ifndef XFC_GTK_SOURCE_BUFFER_HH
#include <xfc/sourceview/sourcebuffer.hh>
#endif

#ifndef __GTK_SOURCE_VIEW_H__
#include <gtksourceview/gtksourceview.h>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

//! @class SourceView sourceview.h inti/gtk-sourceview/sourceview.h
//! @brief A GtkSourceView C++ wrapper class.
//!
//! SourceView is an enhanced Gtk::TextView widget that implements syntax
//! highlighting and other features typical of a source code editor.

class SourceView : public TextView
{
	friend class G::Object;

	SourceView(const SourceView&);
	SourceView& operator=(const SourceView&);

protected:
//! @name Constructors
//! @{

	explicit SourceView(GtkSourceView *view, bool reference = false);
	//!< Construct a new SourceView from an existing GtkSourceView.
	//!< @param view A pointer to a GtkSourceView.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>view</EM> can be a newly created GtkSourceView or an existing
	//!< GtkSourceView (see G::Object::Object).
	
//! @}
//  Properties

	typedef G::Property<bool> ShowLineNumbersPropertyType;
	typedef G::PropertyProxy<G::Object, ShowLineNumbersPropertyType> ShowLineNumbersPropertyProxy;
	static const ShowLineNumbersPropertyType show_line_numbers_property;

	typedef G::Property<bool> ShowLineMarkersPropertyType;
	typedef G::PropertyProxy<G::Object, ShowLineMarkersPropertyType> ShowLineMarkersPropertyProxy;
	static const ShowLineMarkersPropertyType show_line_markers_property;

	typedef G::Property<unsigned int> TabsWidthPropertyType;
	typedef G::PropertyProxy<G::Object, TabsWidthPropertyType> TabsWidthPropertyProxy;
	static const TabsWidthPropertyType tabs_width_property;

	typedef G::Property<bool> AutoIndentPropertyType;
	typedef G::PropertyProxy<G::Object, AutoIndentPropertyType> AutoIndentPropertyProxy;
	static const AutoIndentPropertyType auto_indent_property;

	typedef G::Property<bool> InsertSpacesPropertyType;
	typedef G::PropertyProxy<G::Object, InsertSpacesPropertyType> InsertSpacesPropertyProxy;
	static const InsertSpacesPropertyType insert_spaces_property;

	typedef G::Property<bool> ShowMarginPropertyType;
	typedef G::PropertyProxy<G::Object, ShowMarginPropertyType> ShowMarginPropertyProxy;
	static const ShowMarginPropertyType show_margin_property;

	typedef G::Property<unsigned int> MarginPropertyType;
	typedef G::PropertyProxy<G::Object, MarginPropertyType> MarginPropertyProxy;
	static const MarginPropertyType margin_property;

	typedef G::Property<bool> SmartHomeEndPropertyType;
	typedef G::PropertyProxy<G::Object, SmartHomeEndPropertyType> SmartHomeEndPropertyProxy;
	static const SmartHomeEndPropertyType smart_home_end_property;

public:
//! @name Constructors
//! @{

	SourceView();
	//!< Constructs a new source view widget with an empty default buffer.

	explicit SourceView(SourceBuffer& buffer);
	//!< Constructs a new source view widget displaying the SourceBuffer <EM>buffer</EM>.
	//!< @param buffer A SourceBuffer.
	//!<
	//!< <BR>One buffer can be shared among many widgets. The source view adds its own
	//!< reference count to the buffer; it does not take over an existing reference.

	virtual ~SourceView();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceView* gtk_source_view() const { return reinterpret_cast<GtkSourceView*>(instance_); }
	//!< Get a pointer to the GtkSourceView structure.

	operator GtkSourceView* () const;
	//!< Conversion operator; safely converts a SourceView to a GtkSourceView pointer.

	bool is_gtk_source_view() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_VIEW.

	SourceBuffer* get_source_buffer() const;
	//!< Returns a pointer to the buffer being displayed by this source view.

	bool get_show_line_numbers() const;
	//!< Returns true if line numbers are displayed.

	bool get_show_line_markers() const;
	//!< Returns true if line marker pixbufs are displayed

	unsigned int get_tabs_width() const;
	//!< Returns the current tab width.

	bool get_auto_indent() const;
	//!< Returns true if auto indentation is enabled.

	bool get_insert_spaces_instead_of_tabs() const;
	//!< Returns true if spaces are inserted instead of tabs.

	bool get_show_margin() const;
	//!< Returns true if the right margin is displayed.

	unsigned int get_margin() const;
	//!< Returns the current position of the right margin.

	Pointer<Gdk::Pixbuf> get_marker_pixbuf(const String& marker_type) const;
	//!< Gets the marker pixbuf.
	//!< @param marker_type A String that indentifies the marker pixbuf.
	//!< @return A smart pointer to a Gdk::Pixbuf.

	bool get_smart_home_end() const;
	//!< Returns true if the HOME and END keys move to the first/last characters
	//!< on a line first before going to the start/end of the line.

//! @}
//! @name Methods
//! @{

	void set_show_line_numbers(bool show);
	//!< Sets whether line numbers are displayed.
	//!< @param show Set <EM>true</EM> to display line numbers.

	void set_show_line_markers(bool show);
	//!< Sets whether line marker pixbufs are displayed.
	//!< @param show Set <EM>true</EM> to display line markers.

	void set_tabs_width(unsigned int width);
	//!< Sets the tab width.
	//!< @param width The new tab width.

	void set_auto_indent(bool enable);
	//!< Enables auto indentation.
	//!< @param enable Set <EM>true</EM> to enable auto indentation.

	void set_insert_spaces_instead_of_tabs(bool enable);
	//!< Sets whether spaces should be inserted instead of tabs.
	//!< @param enable Set <EM>true</EM> to insert spaces.

	void set_show_margin(bool show);
	//!< Sets whether the right margin is displayed.
	//!< @param show Set <EM>true</EM> to display the right margin.

	void set_margin(unsigned int margin);
	//!< Sets the position of the right margin.
	//!< @param margin The new position of the right margin.

	void set_marker_pixbuf(const String& marker_type, Gdk::Pixbuf *pixbuf);
	//!< Sets the line marker pixbuf.
	//!< @param marker_type A String indentifying the marker pixbuf.
	//!< @param pixbuf A Gdk::Pixbuf.

	void set_smart_home_end(bool enable);
	//!< Sets whether the HOME and END keys move to the first/last characters
	//!< on a line first before going to the start/end of the line.
	//!< @param enable Set <EM>true</EM> to enable smart home/end.

    void set_source_buffer( SourceBuffer *buffer );
    //!< Set up an new buffer for the source view
    //!< @param buffer the new source view buffer

//! @}
//! @name Property Proxies
//! @{

	const ShowLineNumbersPropertyProxy property_show_line_numbers()
	{
		return ShowLineNumbersPropertyProxy(this, &show_line_numbers_property);
	}
	//!< Whether to display line numbers (bool : Read / Write).

	const ShowLineMarkersPropertyProxy property_show_line_markers()
	{
		return ShowLineMarkersPropertyProxy(this, &show_line_markers_property);
	}
	//!< Whether to display line marker pixbufs (bool : Read / Write).

	const TabsWidthPropertyProxy property_tabs_width()
	{
		return TabsWidthPropertyProxy(this, &tabs_width_property);
	}
	//!< Set the tab width (unsigned int : Read / Write).

	const AutoIndentPropertyProxy property_auto_indent()
	{
		return AutoIndentPropertyProxy(this, &auto_indent_property);
	}
	//!< Whether to enable auto indentation (bool : Read / Write).

	const InsertSpacesPropertyProxy property_insert_spaces()
	{
		return InsertSpacesPropertyProxy(this, &insert_spaces_property);
	}
	//!< Whether to insert spaces instead of tabs (bool : Read / Write).

	const ShowMarginPropertyProxy property_show_margin()
	{
		return ShowMarginPropertyProxy(this, &show_margin_property);
	}
	//!< Whether to display the right margin (bool : Read / Write).

	const MarginPropertyProxy property_margin()
	{
		return MarginPropertyProxy(this, &margin_property);
	}
	//!< Position of the right margin (unsigned int : Read / Write).

	const SmartHomeEndPropertyProxy property_smart_home_end()
	{
		return SmartHomeEndPropertyProxy(this, &smart_home_end_property);
	}
	//!< The HOME and END keys move to the first/last characters on a line first
	//!< before going to the start/end of the line (bool : Read / Write).
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_VIEW_H

