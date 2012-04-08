/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gtk/textview.hh
/// @brief A GtkTextView C++ wrapper interface.
///
/// Provides TextView, a widget which can display a TextBuffer.

#ifndef XFC_GTK_TEXT_VIEW_HH
#define XFC_GTK_TEXT_VIEW_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef XFC_GTK_TEXT_BUFFER_HH
#include <xfc/gtk/textbuffer.hh>
#endif

#ifndef GTK_TEXT_VIEW_H
#include <gtk/gtktextview.h>
#endif

namespace Xfc {

namespace Pango {
class TabArray;
}

namespace Gtk {

class Menu;

/// @enum TextWindowType
/// TextWindowType indentifies the possible windows that correspond to an area of the text view.
/// These are the overall widget window, the border windows on the left, right, top, bottom, 
/// and the window that displays the text buffer. 

enum TextWindowType
{
	TEXT_WINDOW_PRIVATE = GTK_TEXT_WINDOW_PRIVATE, ///< Private.
	TEXT_WINDOW_WIDGET = GTK_TEXT_WINDOW_WIDGET, ///< The overall widget window.
	TEXT_WINDOW_TEXT = GTK_TEXT_WINDOW_TEXT, ///< The window displaying the text buffer.
	TEXT_WINDOW_LEFT = GTK_TEXT_WINDOW_LEFT, ///< The border window on the left.
	TEXT_WINDOW_RIGHT = GTK_TEXT_WINDOW_RIGHT, ///< The border window on the right.
	TEXT_WINDOW_TOP = GTK_TEXT_WINDOW_TOP, ///< The border window on the top.
	TEXT_WINDOW_BOTTOM = GTK_TEXT_WINDOW_BOTTOM ///< The border window on the bottom.
};

/// @class TextView textview.hh xfc/gtk/textview.hh
/// @brief A GtkTextView C++ wrapper class.
///
/// TextView is a widget which can display a TextBuffer. Each text buffer can be displayed
/// by any number of views.
///
/// To use TextView in your application you only need to include the header file <xfc/gtk/textview.hh>.
/// This header file includes <xfc/gtk/textbuffer.hh> which includes all the other header files that
/// TextView needs.
///
/// <B>See also:</B> the <A HREF="../../howto/html/textview.html">TextView Widget</A> HOWTO and example.

class TextView : public Container
{
	friend class G::Object;

	TextView(const TextView&);
	TextView& operator=(const TextView&);

protected:
/// @name Constructors
/// @{

	explicit TextView(GtkTextView *text_view, bool owns_reference = false);
	///< Construct a new TextView from an existing GtkTextView.
	///< @param text_view A pointer to a GtkTextView.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>text_view</EM> can be a newly created GtkTextView or an existing
	///< GtkTextView (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Adjustment*, Adjustment*> SetScrollAdjustmentsSignalType;
	typedef G::SignalProxy<TypeInstance, SetScrollAdjustmentsSignalType> SetScrollAdjustmentsSignalProxy;
	static const SetScrollAdjustmentsSignalType set_scroll_adjustments_signal;
	///< Set scroll adjustments signal (see signal_set_scroll_adjustments()). Calls a slot with the signature:
	///< @code
	///< void function(Adjustment *hadjustment, Adjustment *vadjustment);
	///< // hadjustment: The horizontal adjustment.
	///< // vadjustment: The vertical adjustment.
	///< @endcode

	typedef G::Signal<void, Menu&> PopulatePopupSignalType;
	typedef G::SignalProxy<TypeInstance, PopulatePopupSignalType> PopulatePopupSignalProxy;
	static const PopulatePopupSignalType populate_popup_signal;
	///< Populate popup signal (see signal_populate_popup()). Calls a slot with the signature:
	///< @code
	///< void function(Menu& popup_menu);
	///< // menu: The popup menu.
	///< @endcode

	typedef G::Signal<void> SetAnchorSignalType;
	typedef G::SignalProxy<TypeInstance, SetAnchorSignalType> SetAnchorSignalProxy;
	static const SetAnchorSignalType set_anchor_signal;
	///< Set anchor signal (see signal_set_anchor()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, const String&> InsertAtCursorSignalType;
	typedef G::SignalProxy<TypeInstance, InsertAtCursorSignalType> InsertAtCursorSignalProxy;
	static const InsertAtCursorSignalType insert_at_cursor_signal;
	///< Insert at cursor signal (see signal_insert_at_cursor()). Calls a slot with the signature:
	///< @code
	///< void function(const String& str);
	///< // str: The new text to insert.
	///< @endcode
	
/// @}

public:
	typedef GtkTextView CObjectType;

/// @name Constructors
/// @{

	TextView();
	///< Constructs a new text view widget. If you don't call set_buffer() before using the text view,
	///< an empty default buffer will be created for you. The buffer can be retrieved with
	///< get_buffer().

	explicit TextView(TextBuffer& buffer);
	///< Constructs a new text view widget displaying the buffer <EM>buffer</EM>. 
	///< @param buffer A TextBuffer.
	///<
	///< One buffer can be shared among many widgets. The text view adds its own reference
	///< count to the buffer; it does not take over an existing reference.

	virtual ~TextView();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkTextView* gtk_text_view() const;
	///< Get a pointer to the GtkTextView structure.

	operator GtkTextView* () const;
	///< Conversion operator; safely converts a TextView to a GtkTextView pointer.

	TextBuffer* get_buffer() const;
	///< Returns the TextBuffer being displayed by this text view. The reference count on the
	///< buffer is not incremented; the caller of this method won't own a new reference.

	void get_visible_rect(Gdk::Rectangle& visible_rect);
	///< Fills <EM>visible_rect</EM> with the currently visible region of the buffer,
	///< in buffer coordinates.
	///< @param visible_rect The rectangle to fill.
	///<
	///< Convert to window coordinates with buffer_to_window_coords().

	Gdk::Rectangle get_visible_rect() const;
	///< Returns a rectangle filled with the currently visible region of the buffer,
	///< in buffer coordinates. Convert to window coordinates with buffer_to_window_coords().

	bool get_cursor_visible() const;
	///< Find out whether the cursor is being displayed.
	///< @return Whether the insertion mark is visible.
	 
	void get_iter_location(const TextIter& iter, Gdk::Rectangle& location);
	///< Gets a rectangle which roughly contains the character at <EM>iter</EM>.
	///< @param iter A TextIter.
	///< @param location The bounds of the character at iter.
	///<
	///< The rectangle position is in buffer coordinates; use buffer_to_window_coords()
	///< to convert these coordinates to coordinates for one of the windows in the text view.

	Gdk::Rectangle get_iter_location(const TextIter& iter) const;
	///< Returns a rectangle which roughly contains the character at <EM>iter</EM>.
	///< @param iter A TextIter.
	///<
	///< The rectangle position is in buffer coordinates; use buffer_to_window_coords()
	///< to convert these coordinates to coordinates for one of the windows in the text view.

	TextIter get_iter_at_location(int x, int y) const;
	///< Retrieves the iterator at buffer coordinates x and y.
	///< @param x The x position, in buffer coordinates.
	///< @param y The y position, in buffer coordinates.
	///< @return A TextIter.
	///<
	///< Buffer coordinates are coordinates for the entire buffer, not just the
	///< currently displayed portion. If you have coordinates from an event, you
	///< have to convert those to buffer coordinates with window_to_buffer_coords().

	TextIter get_iter_at_position(int *trailing, int x, int y);
	///< Retrieves the iterator pointing to the character at buffer coordinates x and y.
	///< @param trailing The location to store an integer indicating where in the grapheme the user clicked.
	///< @param x The x position, in buffer coordinates. 
	///< @param y The y position, in buffer coordinates.
	///< @return A TextIter 
	///< 	
	///< On return <EM>trailing</EM> will either be zero, or the number of characters in the
	///< grapheme. 0 represents the trailing edge of the grapheme. Buffer  coordinates are
	///< coordinates for the entire buffer, not just the currently-displayed portion. If you
	///< have coordinates from an event, you have to convert those to buffer coordinates with
	///< window_to_buffer_coords(). 
	///<
	///< Note that this method is different from get_iter_at_location(), which 
	///< returns cursor locations, i.e. positions between characters.
	
	void get_line_yrange(const TextIter& iter, int *y, int *height) const;
	///< Gets the y coordinate of the top of the line containing <EM>iter</EM>,
	///< and the height of the line. 
	///< @param iter A TextIter.
	///< @param y The return location for a y coordinate.
	///< @param height The return location for a height.
	///<
	///< The coordinate is a buffer coordinate; convert to window coordinates with 
	///< buffer_to_window_coords().

	int get_line_y(const TextIter& iter) const;
	///< Gets the y coordinate of the top of the line containing <EM>iter</EM>.
	///< @param iter A TextIter.
	///< @return The y coordinate, as a buffer coordinate.
	
	int get_line_height(const TextIter& iter) const;
	///< Gets the height of the line containing <EM>iter</EM>.
	///< @param iter A TextIter.
	///< @return The height of the line.

	void get_line_at_y(TextIter& target_iter, int y, int *line_top) const;
	///< Gets the TextIter at the start of the line containing the coordinate y.
	///< @param target_iter A TextIter.
	///< @param y A Y coordinate.
	///< @param line_top The return location for top coordinate of the line.
	///<
	///< <EM>y</EM> is in buffer coordinates, convert from window coordinates with
	///< window_to_buffer_coords(). If non-null, <EM>line_top</EM> will be filled with
	///< the coordinate of the top edge of the line.

	TextIter get_line_at_y(int y) const;
	///< Returns the TextIter at the start of the line containing the coordinate y.
	///< @param y A Y coordinate.
	///<
	///< <EM>y</EM> is in buffer coordinates, convert from window coordinates with
	///< window_to_buffer_coords().

	Gdk::Window* get_window(TextWindowType window_type) const;
	///< Retrieves the Gdk::Window corresponding to an area of the text view; possible windows
	///< include the overall widget window, child windows on the left, right, top, bottom, and
	///< the window that displays the text buffer. 
	///< @param window_type The window to get. 
	///< @return A Gdk::Window, or null. 
	///<	
	///< Windows are null and nonexistent if their width or height is 0, and are nonexistent 
	///< before the widget has been realized.

	TextWindowType get_window_type(const Gdk::Window& window) const;
	///< Usually used to find out which window an event corresponds to. 
	///< @param window A window type. 
	///< @return The window type.
	///< 
	///< If you connect to an event signal on the TextView, this method should be called on
	///< event->window to see which window it was.

	int get_border_window_size(TextWindowType type) const;
	///< Gets the width of the specified border window (see set_border_window_size()).
	///, @param type The window to return the size from 
	///< @return The width of the window. 
 
	WrapMode get_wrap_mode() const;
	///< Gets the line wrapping for the view.
	///< @return The line wrap setting.
	 
	bool get_editable() const;
	///< Returns the default editability of the TextView. 
	///< @return Whether text is editable by default.
	///<	
	///< Tags in the buffer may override this setting for some ranges of text.
	 
	bool get_overwrite() const;
	///< Determines whether the text view is in overwrite mode or not.
	///< @return Whether the text view is in overwrite mode or not.

	bool get_accepts_tab() const;
	///< Determines whether pressing the Tab key inserts a tab characters (see set_accepts_tab()).
	///< @return <EM>true</EM> if pressing the Tab key inserts a tab character, <EM>false</EM>
	///< if pressing the Tab key moves the keyboard focus.

	int get_pixels_above_lines() const;
	///< Returns the default number of pixels to put above paragraphs.
	///< Tags in the buffer may override the default.
	
	int get_pixels_below_lines() const;
	///< Returns the default number of blank pixels below paragraphs.
	///< Tags in the buffer may override the default.
	
	int get_pixels_inside_wrap() const;
	///< Returns the default number of pixels of blank space between wrapped lines.
	///< Tags in the buffer may override the default.
	
	Justification get_justification() const;
	///< Returns the default justification of paragraphs in the text view. 
	///< Tags in the buffer may override the default.

	int get_left_margin() const;
	///< Returns the default left margin size of paragraphs in the text_view. 
	///< Tags in the buffer may override the default.
	
	int get_right_margin() const;
	///< Returns the default right margin for text in the text view. 
	///< Tags in the buffer may override the default.

	int get_indent() const;
	///< Gets the default indentation of paragraphs in the text view. 
	///< @return The number of pixels of indentation.
	///< 	
	///< Tags in the view's buffer may override the default. The indentation may be negative.
	
	Pointer<Pango::TabArray> get_tabs() const;
	///< Gets the default tabs for the text view. 
	///< @return A copy of default tab array, or null if "standard" tabs are used.
	///<	
	///< Tags in the buffer may override the defaults. The returned array will be null
	///< if "standard" (8-space) tabs are used. 
	
	Pointer<TextAttributes> get_default_attributes() const;
	///< Obtains a copy of the default text attributes. 
	///< @return A copy of the TextAttributes.
	///< 	
	///< These are the attributes used for text unless a tag overrides them. You'd typically
	///< pass the default attributes in to Gtk::TextIter::get_attributes() in order to get the
	///< attributes in effect at a given text position. 
	
/// @}
/// @name Methods
/// @{

	void set_buffer(TextBuffer *buffer);
	///< Sets <EM>buffer</EM> as the buffer being displayed by text_view.
	///< @param buffer A TextBuffer.
	///<
	///< The previous buffer displayed by the text view is unreferenced, and a reference
	///< is added to buffer. If you owned a reference to buffer before passing it to this 
	///< method, you must remove that reference yourself; TextView will not "adopt" it.

	bool scroll_to_iter(const TextIter& iter, double within_margin, bool use_align, double xalign, double yalign);
	///< Scrolls the text view so that <EM>iter</EM> is on the screen in the position indicated
	///< by <EM>xalign</EM> and <EM>yalign</EM>. 
	///< @param iter A TextIter.
	///< @param within_margin The margin as a (0.0,0.5) fraction of screen size.
	///< @param use_align Whether to use alignment arguments (if false, just get the iter onscreen).
	///< @param xalign The horizontal alignment of <EM>iter</EM> within visible area.
	///< @param yalign The vertical alignment of <EM>iter</EM> within visible area.
	///< @return <EM>true</EM> if scrolling occurred.
	///<
	///< An alignment of 0.0 indicates left or top, 1.0 indicates right or bottom, 0.5 means center.
	///< If <EM>use_align</EM> is false, the text scrolls the minimal distance to get the iter onscreen,
	///< possibly not scrolling at all. The effective screen for purposes of this method is reduced by
	///< a margin of size <EM>within_margin</EM>. 
	///<
	///< Note this method uses the currently computed height of the lines in the text buffer. The line
	///< heights are computed in an idle handler; so this method may not have the desired effect if it's
	///< called before the height computations. To avoid oddness, consider using scroll_to_mark() which
	///< saves a point to be scrolled to after line validation.

	void scroll_to_mark(const TextMark& mark, double within_margin, bool use_align, double xalign, double yalign);
	///< Scrolls the text view so that mark is on the screen in the position indicated by
	///< <EM>xalign</EM> and <EM>yalign</EM>.
	///< @param mark A TextMark.
	///< @param within_margin The margin as a (0.0,0.5) fraction of screen size.
	///< @param use_align Whether to use alignment arguments (if false, just get the mark onscreen).
	///< @param xalign The horizontal alignment of <EM>mark</EM> within visible area.
	///< @param yalign The vertical alignment of <EM>mark</EM> within visible area.
	///<
	///< An alignment of 0.0 indicates left or top, 1.0 indicates right or bottom, 0.5 means center.
	///< If <EM>use_align</EM> is false, the text scrolls the minimal distance to get the mark onscreen,
	///< possibly not scrolling at all. The effective screen for purposes of this method is reduced by
	///< a margin of size <EM>within_margin</EM>.

	void scroll_mark_onscreen(const TextMark& mark);
	///< Scrolls the text view the minimum distance such that mark is contained within
	///< the visible area of the widget.
	///< @param mark A mark in the buffer for the text view.

	bool move_mark_onscreen(const TextMark& mark);
	///< Moves a mark within the buffer so that it's located within the currently-visible text area.
	///< @param mark A TextMark.
	///< @return <EM>true</EM> if the mark moved (wasn't already onscreen).

	bool place_cursor_onscreen();
	///< Moves the cursor to the currently visible region of the buffer, it it isn't there already.
	///< @return <EM>true</EM> if the cursor had to be moved.

	void set_cursor_visible(bool setting);
	///< Toggles whether the insertion point is displayed. 
	///< @param setting Whether to show the insertion cursor.
	///< 	
	///< A buffer with no editable text probably shouldn't have a visible cursor, 
	///< so you may want to turn the cursor off.
 	
	void buffer_to_window_coords(TextWindowType window_type, int buffer_x, int buffer_y, int *window_x, int *window_y);
	///< Converts coordinate (buffer_x, buffer_y) to coordinates for the window
	///< <EM>window_type</EM>, and stores the result in (window_x, window_y).
	///< @param window_type A TextWindowType, except TEXT_WINDOW_PRIVATE.
	///< @param buffer_x The buffer x coordinate.
	///< @param buffer_y The buffer y coordinate.
	///< @param window_x The return location for the window x coordinate.
	///< @param window_y The return location for the window y coordinate.
	///<
	///< Note that you can't convert coordinates for a nonexisting window (see set_border_window_size()).

	void window_to_buffer_coords(TextWindowType window_type, int window_x, int window_y, int *buffer_x, int *buffer_y);
	///< Converts coordinates on the window identified by <EM>window_type</EM> to buffer
	///< coordinates, storing the result in (buffer_x,buffer_y).
	///< @param window_type A TextWindowType, except TEXT_WINDOW_PRIVATE.
	///< @param window_x The window x coordinate.
	///< @param window_y The window y coordinate.
	///< @param buffer_x The return location for the buffer x coordinate.
	///< @param buffer_y The return location for the buffer y coordinate.
	///<
	///< Note that you can't convert coordinates for a nonexisting window (see set_border_window_size()).

	void set_border_window_size(TextWindowType window_type, int size);
	///< Sets the width of TEXT_WINDOW_LEFT or TEXT_WINDOW_RIGHT, or the height of TEXT_WINDOW_TOP
	///< or TEXT_WINDOW_BOTTOM. 
	///< @param window_type The window to affect.
	///< @param size The width or height of the window. 
	///<	
	///< Automatically destroys the corresponding window if the size is set to 0, and 
	///< creates the window if the size is set to non-zero. This method can only be used
	///< for the "border windows," it doesn't work with TEXT_WINDOW_WIDGET, TEXT_WINDOW_TEXT, or
	///< TEXT_WINDOW_PRIVATE.

	bool forward_display_line(TextIter& iter);
	///< Moves the given <EM>iter</EM> forward by one display (wrapped) line. 
	///< @param iter A TextIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was moved and is not on the end iterator. 
	///<	
	///< A display line is different from a paragraph. Paragraphs are separated by newlines
	///< or other paragraph separator characters. Display lines are created by line-wrapping a
	///< paragraph. If wrapping is turned off, display lines and paragraphs will be the same.
	///< Display lines are divided differently for each view, since they depend on the view's
	///< width; paragraphs are the same in all views, since they depend on the contents of the
	///< TextBuffer.

	bool backward_display_line(TextIter& iter);
	///< Moves the given <EM>iter</EM> backward by one display (wrapped) line. 
	///< @param iter A TextIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was moved and is not on the end iterator. 
	///<	
	///< A display line is different from a paragraph. Paragraphs are separated by newlines
	///< or other paragraph separator characters. Display lines are created by line-wrapping a
	///< paragraph. If wrapping is turned off, display lines and paragraphs will be the same.
	///< Display lines are divided differently for each view, since they depend on the view's
	///< width; paragraphs are the same in all views, since they depend on the contents of the
	///< TextBuffer.

	bool forward_display_line_end(TextIter& iter);
	///< Moves the given <EM>iter</EM> forward to the next display line end. 
	///< @param iter A TextIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was moved and is not on the end iterator. 
	///<	
	///< A display line is different from a paragraph. Paragraphs are separated by newlines
	///< or other paragraph separator characters. Display lines are created by line-wrapping a
	///< paragraph. If wrapping is turned off, display lines and paragraphs will be the same.
	///< Display lines are divided differently for each view, since they depend on the view's
	///< width; paragraphs are the same in all views, since they depend on the contents of the
	///< TextBuffer.

	bool backward_display_line_start(TextIter& iter);
	///< Moves the given <EM>iter</EM> backward to the next display line start. 
	///< @param iter A TextIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was moved and is not on the end iterator. 
	///<	
	///< A display line is different from a paragraph. Paragraphs are separated by newlines
	///< or other paragraph separator characters. Display lines are created by line-wrapping a
	///< paragraph. If wrapping is turned off, display lines and paragraphs will be the same.
	///< Display lines are divided differently for each view, since they depend on the view's
	///< width; paragraphs are the same in all views, since they depend on the contents of the
	///< TextBuffer.

	bool starts_display_line(const TextIter& iter);
	///< Determines whether <EM>iter</EM> is at the start of a display line (see forward_display_line()
	///< for an explanation of display lines vs. paragraphs).
	///< @param iter A TextIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> begins a wrapped line. 
 
	bool move_visually(TextIter& iter, int count);
	///< Moves <EM>iter</EM> up or down by <EM>count</EM> display (wrapped) lines (see forward_display_line()
	///< for an explanation of display lines vs. paragraphs).
	///< @param iter A TextIter. 
	///< @param count THe number of lines to move. 
	///< @return <EM>true</EM> if <EM>iter</EM> moved and is not on the end iterator. 

	void add_child_at_anchor(Widget& child, TextChildAnchor& anchor);
	///< Adds a child widget in the text buffer, at the given anchor.
	///< @param child A Widget. 
	///< @param anchor A TextChildAnchor in the TextBuffer for text_view.
	 
	void add_child_in_window(Widget& child, TextWindowType which_window, int xpos, int ypos);
	///< Adds a child at fixed coordinates in one of the text widget's windows. 
	///< @param child A Widget. 
	///< @param which_window Which window the child should appear in. 
	///< @param xpos The X position of child in window coordinates. 
	///< @param ypos the Y position of child in window coordinates.
	///<	
	///< The window must have nonzero size (see set_border_window_size()). Note that the child
	///< coordinates are given relative to the Gdk::Window in question, and that these coordinates
	///< have no sane relationship to scrolling. When placing a child in TEXT_WINDOW_WIDGET, 
	///< scrolling is irrelevant, the child floats above all scrollable areas. But when placing a
	///< child in one of the scrollable windows (border windows or text window), you'll need to 
	///< compute the child's correct position in buffer coordinates any time scrolling occurs or 
	///< buffer changes occur, and then call move_child() to update the child's position. 
	///< Unfortunately there's no good way to detect that scrolling has occurred, using the current
	///< API; a possible hack would be to update all child positions when the scroll adjustments
	///< change or the text buffer changes. See bug 64518 on bugzilla.gnome.org for status of 
	///< fixing this issue.
	 
	void move_child(const Widget& child, int xpos, int ypos);
	///< Updates the position of a child, as for add_child_in_window().
	///< @param child The child widget already added to the text view. 
	///< @param xpos The new X position in window coordinates. 
	///< @param ypos The new Y position in window coordinates.

	void set_wrap_mode(WrapMode wrap_mode);
	///< Sets the line wrapping for the view.
	///< @param wrap_mode A WrapMode.
	 
	void set_editable(bool setting);
	///< Sets the default editability of the TextView. You can override this default setting
	///< with tags in the buffer, using the "editable" attribute of tags.
	///< @param setting Whether the text view is editable.

	void set_overwrite(bool overwrite);
	///< Changes the text view overwrite mode.
	///< @param overwrite Set <EM>true</EM> to turn on overwrite mode, <EM>false</EM> to turn it of.

	void set_accepts_tab(bool accepts_tab);
	///< Sets the behavior of the text widget when the Tab key is pressed.
	///< @param accepts_tab Set <EM>true</EM> if pressing the Tab key should insert a tab character, and
	///<                    <EM>false</EM>, if pressing the Tab key should move the keyboard focus.
	///<
	///< If <EM>accepts_tab</EM> is true a tab character is inserted. If <EM>accepts_tab</EM>
	///< is false the keyboard focus is moved to the next widget in the focus chain.

	void set_pixels_above_lines(int pixels_above_lines);
	///< Sets the default number of blank pixels above paragraphs in text_view.
	///< @param pixels_above_lines The pixels above paragraphs.
	///<
	///< Tags in the buffer for text view may override the defaults.

	void set_pixels_below_lines(int pixels_below_lines);
	///< Sets the default number of pixels of blank space to put below paragraphs.
	///< @param pixels_below_lines The pixels below paragraphs.
	///<
	///< May be overridden by tags applied to text_view's buffer.
	
	void set_pixels_inside_wrap(int pixels_inside_wrap);
	///< Sets the default number of pixels of blank space to leave between display/wrapped
	///< lines within a paragraph. 
	///< @param pixels_inside_wrap The default number of pixels between wrapped lines.
	///<
	///< May be overridden by tags in text_view's buffer.

	void set_justification(Justification justification);
	///< Sets the default justification of text in the text view. 
	///< @param justification The justification.
	///<	
	///< Tags in the view's buffer may override the default.

	void set_left_margin(int left_margin);
	///< Sets the default left margin for text in text_view. 
	///< @param left_margin The left margin in pixels.
	///<	
	///< Tags in the buffer may override the default.

	void set_right_margin(int right_margin);
	///< Sets the default right margin for text in the text view. 
	///< @param right_margin The right margin in pixels.
	///< 
	///< Tags in the buffer may override the default.

	void set_indent(int indent);
	///< Sets the default indentation for paragraphs in the text view. 
	///< @param indent The indentation in pixels
	///<	
	///< Tags in the buffer may override the default.

	void set_tabs(const Pango::TabArray& tabs);
	///< Sets the default tab stops for paragraphs in the text view. 
	///< @param tabs The tabs as a Pango::TabArray.
	///<	
	///< Tags in the buffer may override the default.
	 
/// @}
/// @name Signal Proxies
/// @{

	const SetScrollAdjustmentsSignalProxy signal_set_scroll_adjustments();
	///< Connect to the set_scroll_adjustments_signal; emitted when a text view is added to
	///< a scrolling aware parent.

	const PopulatePopupSignalProxy signal_populate_popup();
	///< Connect to the populate_popup_signal; emitted when the text view displays its context-sensitive menu.

	const SetAnchorSignalProxy signal_set_anchor();
	///< Connect to the set_anchor_signal; emitted when the "anchor" is moved (what Emacs
	///< calls the mark) to the cursor position.

	const InsertAtCursorSignalProxy signal_insert_at_cursor();
	///< Connect to the insert_at_cursor_signal; emited when text is inserted into the
	///< buffer at the current cursor position.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/textview.inl>

#endif // XFC_GTK_TEXT_VIEW_HH


