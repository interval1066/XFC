/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The Xfce Develeopement Team.
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
 
/// @file xfc/gtk/notebook.hh
/// @brief A GtkNotebook C++ wrapper interface.
///
/// Provides Notebook, a Container widget whose children are pages that can be switched
/// between using tab labels along one edge.

#ifndef XFC_GTK_NOTEBOOK_HH
#define XFC_GTK_NOTEBOOK_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_NOTEBOOK_H__
#include <gtk/gtknotebook.h>
#endif

namespace Xfc {

namespace Gtk {

class Label;

/// @enum NotebookTab
/// NotebookTab defines the notebook tab which received the focus when a home or end key
/// is pressed on the keyboard.

enum NotebookTab
{
	NOTEBOOK_TAB_FIRST = GTK_NOTEBOOK_TAB_FIRST, 
	///< The first tab in the notebook page list (GDK_Home or GDK_KP_Home).

	NOTEBOOK_TAB_LAST = GTK_NOTEBOOK_TAB_LAST 
	///< The last tab in the notebook page list (GKD_End or GDK_KP_End).
};

/// @class Notebook notebook.hh xfc/gtk/notebook.hh
/// @brief A GtkNotebook C++ wrapper class.
///
/// The Notebook widget is a Container whose children are pages that can be switched
/// between using tab labels along one edge. There are many configuration options for
/// Notebook. Among other things, you can choose on which edge the tabs appear
/// (see set_tab_pos()), whether, if there are too many tabs to fit the noteobook 
/// should be made bigger or scrolling arrows added (see set_scrollable()), and whether
/// there will be a popup menu allowing the users to switch pages. (see popup_enable(),
/// popup_disable()).
///
/// <B>See also:</B> the <A HREF="../../howto/html/notebooks.html">Notebook</A> HOWTO and example.

class Notebook : public Container
{
	friend class G::Object;

	Notebook(const Notebook&);
	Notebook& operator=(const Notebook&);

protected:
/// @name Constructors
/// @{

	explicit Notebook(GtkNotebook *notebook, bool owns_reference = false);
	///< Construct a new Notebook from an existing GtkNotebook.
	///< @param notebook A pointer to a GtkNotebook.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>notebook</EM> can be a newly created GtkNotebook or an existing
	///< GtkNotebook (see G::Object::Object).

/// @}
/// @name Signal Prototypes

	typedef G::Signal<void, Widget&, unsigned int> SwitchPageSignalType;
	typedef G::SignalProxy<TypeInstance, SwitchPageSignalType> SwitchPageSignalProxy;
	static const SwitchPageSignalType switch_page_signal;
	///< Switch page signal (see signal_switch_page()). Calls a slot with the signature:
	///< @code
	///< void function(Widget& page_child, unsigned int page_num);
	///< // page_child: The child widget that is the contents of the new current page.
	///< // page_num: The index of the new current page.
	///< @endcode

/// @}

public:
	typedef GtkNotebook CObjectType;

/// @name Constructors
/// @{

	Notebook();
	///< Construct a new notebook with no pages.

	virtual ~Notebook();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkNotebook* gtk_notebook() const;
	///< Get a pointer to the GtkNotebook structure.

	operator GtkNotebook* () const;
	///< Conversion operator; safely converts a Notebook to a GtkNotebook pointer.

	int get_current_page() const;
	///< Returns the page number of the current page.
	///< @return The index (starting from 0) of the current page in the notebook. 
	///<
	///< If the notebook has no pages, then -1 will be returned.

	Widget* get_current_nth_page() const;
	///< Returns the child widget contained in the current page.
	///< @return The child widget, or null if the notebook has no pages.

	Widget* get_nth_page(int page_num) const;
	///< Returns the child widget contained in page number <EM>page_num</EM>.
	///< @param page_num The index of a page in the noteobok, or -1 to get the last page.
	///< @return The child widget, or null if page_num is out of bounds.

	int get_n_pages() const;
	///< Returns the number of pages in the notebook.

	int page_num(const Widget& child) const;
	///< Finds the index of the page which contains the given child widget.
	///< @param child A Widget.
	///< @return The index of the page containing child, or -1 if child is not in the notebook.

	bool get_show_border() const;
	///< Returns whether a bevel will be drawn around the notebook pages (see set_show_border()).
	///< @return <EM>true</EM> if the bevel is drawn.

	bool get_show_tabs() const;
	///< Returns whether the tabs of the notebook are shown (see set_show_tabs()).
	///< @return  <EM>true</EM> if the tabs are shown.

	PositionType get_tab_pos() const;
	///< Gets the edge at which the tabs for switching pages in the notebook are drawn.
	///< @return The edge at which the tabs are drawn.

	bool get_scrollable() const;	
	///< Returns whether the tab label area has arrows for scrolling (see set_scrollable()).
	///< @return <EM>true</EM> if arrows for scrolling are present.

	Label* get_tab_label(const Widget& child) const;
	///< Returns the tab label widget for the page containing child.
	///< @param child The page.
	///< @return The tab label.
	///<
	///< null is returned if child is not in notebook or if no tab label has specifically
	///< been set for <EM>child</EM>.

	Label* get_tab_label(int page_num) const;
	///< Returns the tab label widget for the page with the index <EM>page_num</EM>.
	///< @param page_num The index of a page in the noteobok, or -1 to get the last page.
	///< @return The tab label.
	///<
	///< null is returned if child is not in notebook or if no tab label has specifically
	///< been set for <EM>child</EM>.

	String get_tab_label_text(const Widget& child) const;
	///< Retrieves the text of the tab label for the page containing child.
	///< @param child A widget contained in a page of notebook.
	///< @return The text of the tab label, or a null String if the tab label widget is not a Label.

	String get_tab_label_text(int page_num) const;
	///< Retrieves the text of the tab label for the page with the index <EM>page_num</EM>.
	///< @param page_num The index of a page in the noteobok, or -1 to get the last page.
	///< @return The text of the tab label, or a null String if the tab label widget is not a Label.

	Label* get_menu_label(const Widget& child) const;
	///< Retrieves the menu label widget of the page containing child.
	///< @param child A widget contained in a page of notebook.
	///< @return The menu label, or null if the page does not have a menu label other than the default.

	Label* get_menu_label(int page_num) const;
	///< Retrieves the menu label widget of the page with the index <EM>page_num</EM>.
	///< @param page_num The index of a page in the noteobok, or -1 to get the last page.
	///< @return The menu label, or null if the page does not have a menu label other than the default.

	String get_menu_label_text(const Widget& child) const;
	///< Retrieves the text of the menu label for the page containing child.
	///< @param child The child widget of a page of the notebook.
	///< @return The text of the menu label, or a null String if the widget does not have a menu label
	///<         other than the default menu label, or the menu label widget is not a Label.

	String get_menu_label_text(int page_num) const;
	///< Retrieves the text of the menu label for the page with the index <EM>page_num</EM>.
	///< @param page_num The index of a page in the noteobok, or -1 to get the last page.
	///< @return The text of the menu label, or a null String if the widget does not have a menu label
	///<         other than the default menu label, or the menu label widget is not a Label.

	void query_tab_label_packing(const Widget& child, bool *expand, bool *fill, PackType *pack_type) const;
	///< Query the packing attributes for the tab label for the page containing child.
	///< @param child The child widget.
	///< @param expand The location to store the expand value (or null).
	///< @param fill The location to store the fill value (or null).
	///< @param pack_type The location to store the pack_type (or null).

/// @}
/// @name Methods
/// @{

	int append_page(Widget& child, Widget *tab_label = 0, Widget *menu_label = 0);
	///< Appends a page to the notebook, specifying the widget to use as the label in the tab
	///< and the widget to use as the label in the popup menu.
	///< @param child The Widget to use as the contents of the page.
	///< @param tab_label The Widget to be used as the label for the page, or null
	///<                  to use the default label, 'page N'.
	///< @param menu_label The widget to use as a label for the page-switch menu, if that is enabled.
	///< @return The index (starting from 0) of the appended page in the notebook, or -1 if it fails. 
	///<
	///< If null, and tab_label is a Label or null, then the menu label will be a newly created
	///< label with the same text as tab_label; If tab_label is not a Label, menu_label must be
	///< specified if the page-switch menu is to be used.

	int append_page(Widget& child, const char *tab_label, const char *menu_label = 0);
	int append_page(Widget& child, const String& tab_label, const String& menu_label = 0);
	///< Appends a page to the notebook with the specified tab label text and the popup menu label text.
	///< @param child The Widget to use as the contents of the page.
	///< @param tab_label The tab label text.
	///< @param menu_label The menu_label text.
	///< @return The index (starting from 0) of the appended page in the notebook, or -1 if it fails. 
	///<
	///< This method creates default tab and menu labels.

	int prepend_page(Widget& child, Widget *tab_label = 0, Widget *menu_label = 0);
	///< Prepends a page to the notebook, specifying the widget to use as the label in the tab
	///< and the widget to use as the label in the popup menu.
	///< @param child The Widget to use as the contents of the page.
	///< @param tab_label The Widget to be used as the label for the page, or null
	///<                  to use the default label, 'page N'.
	///< @param menu_label The widget to use as a label for the page-switch menu, if that is enabled.
	///< @return The index (starting from 0) of the prepended page in the notebook, or -1 if it fails. 
	///<
	///< If null, and tab_label is a Label or null, then the menu label will be a newly created
	///< label with the same text as tab_label; If tab_label is not a Label, menu_label must be
	///< specified if the page-switch menu is to be used.

	int prepend_page(Widget& child, const char *tab_label, const char *menu_label = 0);
	int prepend_page(Widget& child, const String& tab_label, const String& menu_label = 0);
	///< Prepends a page to the notebook with the specified tab label text and the popup menu label text.
	///< @param child The Widget to use as the contents of the page.
	///< @param tab_label The tab label text.
	///< @param menu_label The menu_label text.
	///< @return The index (starting from 0) of the prepended page in the notebook, or -1 if it fails. 
	///<
	///< This method creates default tab and menu labels.

	int insert_page(Widget& child, int position, Widget *tab_label = 0, Widget *menu_label = 0);
	///< Insert a page into the notebook, specifying the widget to use as the label in the tab
	///< and the widget to use as the label in the popup menu.
	///< @param child The Widget to use as the contents of the page.
	///< @param position The index (starting at 0) at which to insert the page.
	///< @param tab_label The Widget to be used as the label for the page, or null
	///<                  to use the default label, 'page N'.
	///< @param menu_label The widget to use as a label for the page-switch menu, if that is enabled.
	///< @return The index (starting from 0) of the inserted page in the notebook, or -1 if it fails. 
	///<
	///< If null, and tab_label is a Label or null, then the menu label will be a newly created
	///< label with the same text as tab_label; If tab_label is not a Label, menu_label must be
	///< specified if the page-switch menu is to be used. A position value of 0 prepends the new page
	///< before all the others. A position value of -1 will append the new page after all the others.

	int insert_page(Widget& child, int position, const char *tab_label, const char *menu_label = 0);
	int insert_page(Widget& child, int position, const String& tab_label, const String& menu_label = 0);
	///< Insert a page into the notebook with the specified tab label text and the popup menu label text.
	///< @param child The Widget to use as the contents of the page.
	///< @param position The index (starting at 0) at which to insert the page.
	///< @param tab_label The tab label text.
	///< @param menu_label The menu_label text.
	///< @return The index (starting from 0) of the inserted page in the notebook, or -1 if it fails. 
	///<
	///< This method creates default tab and menu labels. A position value of 0 prepends the 
	///< new page before all the others. A position value of -1 will append the new page after
	///< all the others.

	void remove_page(int page_num);
	///< Removes the page from the notebook with the index <EM>page_num</EM>.
	///< @param page_num The index of a notebook page, starting from 0. If -1, the last page will be removed.

	void set_current_page(int page_num);
	///< Switches to the page number <EM>page_num</EM>.
	///< @param page_num The index of the page to switch to, starting from 0.
	///< 
	///< If <EM>page_num</EM> is negative, the last page will be used. If <EM>page_num</EM>
	///< is greater than the number of pages in the notebook, nothing will be done.

	void next_page();
	///< Switches to the next page. Nothing happens if the current page is the last page.

	void prev_page();
	///< Switches to the previous page. Nothing happens if the current page is the first page.

	void set_show_border(bool show_border);
	///< Sets whether a bevel will be drawn around the notebook pages. 
	///< @param show_border <EM>true</EM> if a bevel should be drawn around the notebook.
	///<
	///< This only has a visual effect when the tabs are not shown (see set_show_tabs()).

	void set_show_tabs(bool show_tabs);
	///< Sets whether to show the tabs for the notebook or not.
	///< @param show_tabs <EM>true</EM> if the tabs should be shown.

	void set_tab_pos(PositionType pos);
	///< Sets the edge at which the tabs for switching pages in the notebook are drawn.
	///< @param pos The edge to draw the tabs at.

	void set_scrollable(bool scrollable);
	///< Sets whether the tab label area will have arrows for scrolling if there are
	///< too many tabs to fit in the area.
	///< @param scrollable <EM>true</EM> if scroll arrows should be added.

	void popup_enable();
	///< Enables the popup menu: if the user clicks with the right mouse button on the bookmarks,
	///< a menu with all the pages will be popped up.

	void popup_disable();
	///< Disables the popup menu.

	void set_tab_label(Widget& child, Widget *tab_label);
	///< Changes the tab label for the page containing child.
	///< @param child The child widget.
	///< @param tab_label The tab label widget to use, or null for default tab label.

	void set_tab_label_text(Widget& child, const char *tab_text);
	void set_tab_label_text(Widget& child, const String& tab_text);
	///< Creates a new label widget and sets it as the tab label for the page containing child.
	///< @param child The child widget.
	///< @param tab_text The label text.

	void set_menu_label(Widget& child, Widget *menu_label);
	///< Changes the menu label for the page containing child.
	///< @param child The child widget.
	///< @param menu_label The menu label, or null for default.

	void set_menu_label_text(Widget& child, const char *menu_text);
	void set_menu_label_text(Widget& child, const String& menu_text);
	///< Creates a new label widget and sets it as the menu label for the page containing child.
	///< @param child The child widget.
	///< @param menu_text The label text.

	void set_tab_label_packing(Widget& child, bool expand, bool fill, PackType pack_type);
	///< Sets the packing parameters for the tab label of the page containing child 
	///< (see Gtk::Box::pack_start() for the exact meaning of the parameters).
	///< @param child The child widget
	///< @param expand Whether to expand the bookmark or not.
	///< @param fill Whether the bookmark should fill the allocated area or not.
	///< @param pack_type The position of the bookmark.

	void reorder_child(Widget& child, int position);
	///< Reorders the page containing child, so that it appears in position position.
	///< @param child The child to move.
	///< @param position The new position, or -1 to move to the end.
	///<
	///< If position is greater than or equal to the number of children in the list or negative,
	///< child will be moved to the end of the list.

/// @}
/// @name Signal Proxies
/// @{

	const SwitchPageSignalProxy signal_switch_page();
	///< Connect to the switch_page_signal; emitted when the user or a function
	///< changes the current page.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/notebook.inl>

#endif // XFC_GTK_NOTEBOOK_HH

