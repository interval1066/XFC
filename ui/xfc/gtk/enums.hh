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

/// @file xfc/gtk/enums.hh
/// @brief C++ wrappers for GTK enumerations.

#ifndef XFC_GTK_ENUMS_HH
#define XFC_GTK_ENUMS_HH

#ifndef __GTK_ENUMS_H__
#include <gtk/gtkenums.h>
#endif

#ifndef __GTK_ACCEL_GROUP_H__
#include <gtk/gtkaccelgroup.h>
#endif

#ifndef __GTK_SIZE_GROUP_H__
#include <gtk/gtksizegroup.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum AccelFlags
/// Accelerator flags.

enum AccelFlags
{
	ACCEL_VISIBLE = GTK_ACCEL_VISIBLE, ///< Display the accelerator in an AccelLabel.
	ACCEL_LOCKED = GTK_ACCEL_LOCKED, ///< Is the accelerator removable?
	ACCEL_MASK = GTK_ACCEL_MASK ///< Has a value of 0x07.
};

/// AccelFlagsField holds one or more values from the Gtk::AccelFlags enumeration OR'd together.

typedef unsigned int AccelFlagsField;

/// @enum ArrowType
/// Used to indicate the direction in which an Arrow should point.

enum ArrowType
{
	ARROW_UP = GTK_ARROW_UP, ///< Represents an upward pointing arrow.
	ARROW_DOWN = GTK_ARROW_DOWN, ///< Represents a downward pointing arrow.
	ARROW_LEFT = GTK_ARROW_LEFT, ///< Represents a left pointing arrow.
	ARROW_RIGHT = GTK_ARROW_RIGHT ///< Represents a right pointing arrow.
};

/// @enum AttachOptions
/// Denotes the expansion properties that a widget will have when it (or it's parent) is resized.

enum AttachOptions
{
	EXPAND = GTK_EXPAND, 
	///< The widget should expand to take up any extra space in its container that has been allocated.

	SHRINK = GTK_SHRINK, 
	///< The widget should shrink as and when possible.

	FILL = GTK_FILL 
	///< The widget should fill the space allocated to it.
};

/// AttachOptionsField holds one or more values from the Gtk::AttachOptions enumeration OR'd together.

typedef unsigned int AttachOptionsField;

/// @enum CornerType
/// Specifies which corner a child widget should be placed in when packed into a ScrolledWindow.
/// This is effectively the opposite of where the scroll bars are placed. 

enum CornerType
{
	CORNER_TOP_LEFT = GTK_CORNER_TOP_LEFT,
	//< Place the scrollbars on the right and bottom of the widget (default behaviour).

	CORNER_BOTTOM_LEFT = GTK_CORNER_BOTTOM_LEFT,
	///< Place the scrollbars on the top and right of the widget.

	CORNER_TOP_RIGHT = GTK_CORNER_TOP_RIGHT,
	///< Place the scrollbars on the left and bottom of the widget.

	CORNER_BOTTOM_RIGHT = GTK_CORNER_BOTTOM_RIGHT
	///< Place the scrollbars on the top and left of the widget.
};

/// @enum DeleteType
/// Indicates the text deletion type; used by the Entry and Textview widgets.

enum DeleteType
{
	DELETE_CHARS = GTK_DELETE_CHARS, 
	///< Delete characters.

	DELETE_WORD_ENDS = GTK_DELETE_WORD_ENDS,
	///< Delete only the portion of the word to the left/right of cursor if we're in the middle of a word.

	DELETE_WORDS = GTK_DELETE_WORDS,
	///< Delete words.

	DELETE_DISPLAY_LINES = GTK_DELETE_DISPLAY_LINES,
	///< Deletes the entire line of text from an Entry.

	DELETE_DISPLAY_LINE_ENDS = GTK_DELETE_DISPLAY_LINE_ENDS,
	///< Deletes text in an Entry, from the current cursor position to the end of the line.

	DELETE_PARAGRAPH_ENDS = GTK_DELETE_PARAGRAPH_ENDS,
	///< Like C-k in Emacs (or its reverse).

	DELETE_PARAGRPHS = GTK_DELETE_PARAGRAPHS,
	///< Like C-k in pico, kill whole line.

	DELETE_WHITESPACE = GTK_DELETE_WHITESPACE
	///< Like M-\ in Emacs.
};

/// @enum DirectionType
/// Indicates direction; used by widgets such as Menu, Notebook, ScrollWindow and TextView.

enum DirectionType
{
	DIR_TAB_FORWARD = GTK_DIR_TAB_FORWARD, ///< Tab in a forword direction.
	DIR_TAB_BACKWARD = GTK_DIR_TAB_BACKWARD, ///< Tab in a backward direction.
	DIR_UP = GTK_DIR_UP, ///< Up.
	DIR_DOWN = GTK_DIR_DOWN, ///< Down.
	DIR_LEFT = GTK_DIR_LEFT, ///< Left.
	DIR_RIGHT = GTK_DIR_RIGHT ///< Right.
};

/// @enum ExpanderStyle
/// ExpanderStyle is used by Style::draw_expander() to indicate the type of expander to draw.

enum ExpanderStyle
{
	EXPANDER_COLLAPSED = GTK_EXPANDER_COLLAPSED, ///< Expander collapsed.
	EXPANDER_SEMI_COLLAPSED = GTK_EXPANDER_SEMI_COLLAPSED, ///< Expander semi-collapsed.
	EXPANDER_SEMI_EXPANDED = GTK_EXPANDER_SEMI_EXPANDED, ///< Expander semi-expanded.
	EXPANDER_EXPANDED = GTK_EXPANDER_EXPANDED ///< Expander expanded.
};

/// @enum IconSize
/// The Icon size to render.

enum IconSize
{
	ICON_SIZE_INVALID = GTK_ICON_SIZE_INVALID, ///< Invalid
	ICON_SIZE_MENU = GTK_ICON_SIZE_MENU, ///< An icon size suitable for menus.
	ICON_SIZE_SMALL_TOOLBAR = GTK_ICON_SIZE_SMALL_TOOLBAR, ///< An icon size suitable for small toolbars.
	ICON_SIZE_LARGE_TOOLBAR = GTK_ICON_SIZE_LARGE_TOOLBAR, ///< An icon size suitable for large toolbars.
	ICON_SIZE_BUTTON = GTK_ICON_SIZE_BUTTON, ///< An icon size suitable for buttons.
	ICON_SIZE_DND = GTK_ICON_SIZE_DND,  ///< An icon size suitable for drag-and-drop.
	ICON_SIZE_DIALOG = GTK_ICON_SIZE_DIALOG ///< An icon size suitable for dialogs.
};

/// @enum Justification
/// Used for justifying the text inside a Label widget (see also Alignment).

enum Justification
{
	JUSTIFY_LEFT = GTK_JUSTIFY_LEFT, ///< The text is placed at the left edge of the label.
	JUSTIFY_RIGHT = GTK_JUSTIFY_RIGHT, ///< The text is placed at the right edge of the label.
	JUSTIFY_CENTER = GTK_JUSTIFY_CENTER, ///< The text is placed in the center of the label.
	JUSTIFY_FILL = GTK_JUSTIFY_FILL ///< The text is placed is distributed across the label.
};

/// @enum MetricType
/// Used to define the unit type for Ruler.

enum MetricType
{
	PIXELS = GTK_PIXELS, ///< Ruler with pixel units.
	INCHES = GTK_INCHES, ///< Ruler with inch units.
	CENTIMETERS = GTK_CENTIMETERS //Ruler with centimeter units.
};

/// @enum MovementStep
/// Describes the movement of the insertion point (cursor).

enum MovementStep
{
	MOVEMENT_LOGICAL_POSITIONS = GTK_MOVEMENT_LOGICAL_POSITIONS, ///< Move by forward/back graphemes.
	MOVEMENT_VISUAL_POSITIONS = GTK_MOVEMENT_VISUAL_POSITIONS, ///< Move by left/right graphemes.
	MOVEMENT_WORDS = GTK_MOVEMENT_WORDS, ///< Move by forward/back words.
	MOVEMENT_DISPLAY_LINES = GTK_MOVEMENT_DISPLAY_LINES, ///< Move up/down lines (wrapped lines).
	MOVEMENT_DISPLAY_LINE_ENDS = GTK_MOVEMENT_DISPLAY_LINE_ENDS, ///< Move up/down lines (wrapped lines).
	MOVEMENT_PARAGRAPHS = GTK_MOVEMENT_PARAGRAPHS, ///< Move up/down paragraphs (newline-ended lines).
	MOVEMENT_PARAGRAPHS_ENDS = GTK_MOVEMENT_PARAGRAPH_ENDS, ///< Move to either end of a paragraph.
	MOVEMENT_PAGES = GTK_MOVEMENT_PAGES, ///< Move by pages.
	MOVEMENT_BUFFER_ENDS = GTK_MOVEMENT_BUFFER_ENDS, ///< Move to ends of the buffer.
	MOVEMENT_HORIZONTAL_PAGES = GTK_MOVEMENT_HORIZONTAL_PAGES ///< Move horizontally by pages.
};

/// @enum Orientation
/// Used by Range and Toolbar to indicate the orientation of the widget.
///
/// Also used in Style to indicate the orientation of the widget to draw (e.g. draw_slider(), draw_handle()).

enum Orientation
{
	ORIENTATION_HORIZONTAL = GTK_ORIENTATION_HORIZONTAL, ///< Horizontal orientation.
	ORIENTATION_VERTICAL = GTK_ORIENTATION_VERTICAL ///< Vertical orientation.
};

/// @enum PackType
/// Represents the packing location of Box children (see VBox, HBox and ButtonBox).

enum PackType
{
	PACK_START = GTK_PACK_START, ///< The child is packed into the start of the box.
	PACK_END = GTK_PACK_END ///< The child is packed into the end of the box.
};

/// @enum PolicyType
/// Determines when a scroll bar will be visible.

enum PolicyType
{
	POLICY_ALWAYS = GTK_POLICY_ALWAYS, ///< The scrollbar is always visible.
	POLICY_AUTOMATIC = GTK_POLICY_AUTOMATIC, ///< The scrollbar will appear and disappear as necessary.
	POLICY_NEVER = GTK_POLICY_NEVER ///< The scrollbar will never appear.
};

/// @enum PositionType
/// Indicates edge position. Used by HandleBox, Notebook and Scale widgets, and the Style "draw" methods.

enum PositionType
{
	POS_LEFT = GTK_POS_LEFT, ///< Position left.
	POS_RIGHT = GTK_POS_RIGHT, ///< Position right.
	POS_TOP = GTK_POS_TOP, ///< Position top.
	POS_BOTTOM = GTK_POS_BOTTOM ///< Position bottom.
};

/// @enum ReliefStyle
/// Specifies the relief style of the edges a Button.

enum ReliefStyle
{
	RELIEF_NORMAL = GTK_RELIEF_NORMAL, ///< Normal edge thickness.
	RELIEF_HALF = GTK_RELIEF_HALF, ///< Half the normal edge thickness.
	RELIEF_NONE = GTK_RELIEF_NONE ///< No edge.
};

/// @enum ResizeMode
/// Determines whether a resize request will be passed to a container's parent, queued for later
/// execution or executed immediately.

enum ResizeMode
{
	RESIZE_PARENT = GTK_RESIZE_PARENT, ///< Pass resize request to the parent
	RESIZE_QUEUE = GTK_RESIZE_QUEUE, ///< Queue resizes on this widget.
	RESIZE_IMMEDIATE = GTK_RESIZE_IMMEDIATE ///< Perform the resizes now.
};

/// @enum ScrollType
/// Passed as a signal argument by Range, Scrollbar, SpinButton and ScrolledWindow widgets
/// to indicate the way the user has moved the slider or thumb.

enum ScrollType
{
	SCROLL_NONE = GTK_SCROLL_NONE, ///< No thumb movement.
	SCROLL_JUMP = GTK_SCROLL_JUMP, ///< Used by CList, which is deprecated.
	SCROLL_STEP_BACKWARD = GTK_SCROLL_STEP_BACKWARD,
	///< The thumb moved backwards by a small amount in response to a mouse click
	///< on the arrow at the top of a scrollbar.

	SCROLL_STEP_FORWARD = GTK_SCROLL_STEP_FORWARD,
	///< The thumb moved forwards by a small amount in response to a mouse click
	///< on the arrow at the bottom of a scrollbar.

	SCROLL_PAGE_BACKWARD = GTK_SCROLL_PAGE_BACKWARD,
	///< The thumb moved backwards by a large amount in response to a mouse click
	///< in the trough between the thumb and the top arrow.

	SCROLL_PAGE_FORWARD = GTK_SCROLL_PAGE_FORWARD,
	///< The thumb moved forwards by a large amount in response to a mouse click
	///< in the trough between the thumb and the bottom arrow.

	SCROLL_STEP_UP = GTK_SCROLL_STEP_UP, ///< Same as SCROLL_STEP_BACKWARD.
	SCROLL_STEP_DOWN = GTK_SCROLL_STEP_DOWN, ///< Same as SCROLL_STEP_FORWARD.
	SCROLL_PAGE_UP = GTK_SCROLL_PAGE_UP, ///< Same as SCROLL_PAGE_BACKWARD.
	SCROLL_PAGE_DOWN = GTK_SCROLL_PAGE_DOWN, ///< Same as SCROLL_PAGE_FORWARD.
	SCROLL_STEP_LEFT = GTK_SCROLL_STEP_LEFT, ///< Same as SCROLL_STEP_BACKWARD.
	SCROLL_STEP_RIGHT = GTK_SCROLL_STEP_RIGHT, ///< Same as SCROLL_STEP_FORWARD.
	SCROLL_PAGE_LEFT = GTK_SCROLL_PAGE_LEFT, ///< Same as SCROLL_PAGE_BACKWARD.
	SCROLL_PAGE_RIGHT = GTK_SCROLL_PAGE_RIGHT, ///< Same as SCROLL_PAGE_FORWARD.
	SCROLL_START = GTK_SCROLL_START, ///< The user has started to scroll the thumb.
	SCROLL_END = GTK_SCROLL_END ///< The user has finished scrolling the thumb.
};

/// @enum SelectionMode
/// Specifies the selection mode for a TreeView widget. This allows you to set whether
/// only one or more than one item can be selected at a time. Note that setting the 
/// widget's selection mode to one of SELECTION_BROWSE or SELECTION_SINGLE will cause
/// all the items in the TreeView to become deselected.

enum SelectionMode
{
	SELECTION_NONE = GTK_SELECTION_NONE, 
	///< No selection.

	SELECTION_SINGLE = GTK_SELECTION_SINGLE,
	///< The user can select only one item at a time; When you click and drag the mouse,
	///< only the focus changes; The selection changes only when the mouse button is 
	///< released on the same item it was pressed on.

	SELECTION_BROWSE = GTK_SELECTION_BROWSE,
	///< The user can select only one item at a time; The selection changes when the mouse
	///< button is pressed, not when it's released; When you click and drag the mouse, 
	///< both the focus and the selection change.

	SELECTION_MULTIPLE = GTK_SELECTION_MULTIPLE,
	///< The user can select multiple items at the same time.
	
	SELECTION_EXTENDED = GTK_SELECTION_EXTENDED 
	///< Not used any longer.
};

/// @enum ShadowType
/// Used to change the appearance of an outline typically provided by a Frame.

enum ShadowType
{
	SHADOW_NONE = GTK_SHADOW_NONE, ///< No outline.
	SHADOW_IN = GTK_SHADOW_IN, ///< The outline is bevelled inwards.
	SHADOW_OUT = GTK_SHADOW_OUT, ///< The outline is bevelled outwards like a button.
	SHADOW_ETCHED_IN = GTK_SHADOW_ETCHED_IN, ///< The outline itself is an inward bevel.
	SHADOW_ETCHED_OUT = GTK_SHADOW_ETCHED_OUT ///< The outline itself is an outward bevel.
};

/// @enum SizeGroupMode
/// The mode of the size group determines the directions in which the size group effects
/// the requested sizes of its component widgets.

enum SizeGroupMode
{
	SIZE_GROUP_NONE = GTK_SIZE_GROUP_NONE, ///< Group has no effect.
	SIZE_GROUP_HORIZONTAL = GTK_SIZE_GROUP_HORIZONTAL, ///< Group effects horizontal requisition.
	SIZE_GROUP_VERTICAL = GTK_SIZE_GROUP_VERTICAL, ///< Group effects vertical requisition.
	SIZE_GROUP_BOTH = GTK_SIZE_GROUP_BOTH ///< Group effects both horizontal and vertical requisition.
};

/// @enum SortType
/// Determines the direction of a sort.

enum SortType
{
	SORT_ASCENDING = GTK_SORT_ASCENDING, ///< Sorting is in ascending order.
	SORT_DESCENDING = GTK_SORT_DESCENDING ///< Sorting is in descending order.
};

// @enum Gtk::StateType
/// This type indicates the current state of a widget; the state determines how the widget is drawn.
///
/// The StateType enumeration is also used to identify different colors in a Style for drawing, so
/// states can be used for subparts of a widget as well as entire widgets.

enum StateType
{
	STATE_NORMAL = GTK_STATE_NORMAL, 
	///< State during normal operation.

	STATE_ACTIVE = GTK_STATE_ACTIVE, 
	///< State of a currently active widget, such as a depressed button.

	STATE_PRELIGHT = GTK_STATE_PRELIGHT, 
	///< State indicating that the mouse pointer is over the widget and the widget responds to mouse clicks.

	STATE_SELECTED = GTK_STATE_SELECTED,
	///< State of a selected item, such the selected row in a list.

	STATE_INSENSITIVE = GTK_STATE_INSENSITIVE
	///< State indicating that the widget is unresponsive to user actions.
};

/// @enum TextDirection
/// Text direction (right-to-left or left-to-right).

enum TextDirection
{
	TEXT_DIR_NONE = GTK_TEXT_DIR_NONE, 
	///< In TextLayout, means means draw cursors for both left-to-right and right-to-left insertion.

	TEXT_DIR_LTR = GTK_TEXT_DIR_LTR, 
	///< Text direction left-to-right.
	
	TEXT_DIR_RTL = GTK_TEXT_DIR_RTL 
	///< Text direction right-to-left.
};

/// @enum ToolbarStyle
/// ToolbarStyle is used to customize the appearance of a Toolbar. Note that setting the
/// toolbar style overrides the user's preferences for the default toolbar style.

enum ToolbarStyle
{
	TOOLBAR_ICONS = GTK_TOOLBAR_ICONS,
	///< Buttons display only icons in the toolbar.
	
	TOOLBAR_TEXT = GTK_TOOLBAR_TEXT,
	///< Buttons display only text labels in the toolbar.

	TOOLBAR_BOTH = GTK_TOOLBAR_BOTH,
	///< Buttons display text and icons in the toolbar.

	TOOLBAR_BOTH_HORIZ = GTK_TOOLBAR_BOTH_HORIZ
	///< Buttons display icons and text alongside each other, rather than vertically stacked.
};

/// @enum UpdateType
/// Used by Range widgets to set the update policy for the range.

enum UpdateType
{
	UPDATE_CONTINUOUS = GTK_UPDATE_CONTINUOUS,
	///< Anytime the range slider is moved, the range value will change and the
	///< "value_changed" signal will be emitted.

	UPDATE_DISCONTINUOUS = GTK_UPDATE_DISCONTINUOUS,
	///< The range value will only be updated when the user releases the button and ends
	///< the slider drag operation.

	UPDATE_DELAYED = GTK_UPDATE_DELAYED
	///< The range value will be updated after a brief timeout where no slider motion occurs,
	///< so updates are spaced by a short time rather than continuous.
};

/// @enum WindowPosition
/// Window placement can be influenced using this enumeration.

enum WindowPosition
{
	WIN_POS_NONE = GTK_WIN_POS_NONE, ///< No influence is made on placement.
	WIN_POS_CENTER = GTK_WIN_POS_CENTER, ///< Windows should be placed in the center of the screen.
	WIN_POS_MOUSE = GTK_WIN_POS_MOUSE, ///< Windows should be placed at the current mouse position.
	WIN_POS_CENTER_ALWAYS = GTK_WIN_POS_CENTER_ALWAYS, ///< Keep window centered as it changes size, etc.
	WIN_POS_CENTER_ON_PARENT = GTK_WIN_POS_CENTER_ON_PARENT  ///< Center the window on its transient parent.
};

/// @enum WrapMode
/// Describes the type of line wrapping.

enum WrapMode
{
	WRAP_NONE = GTK_WRAP_NONE,
	///< Do not wrap lines; just make the text area wider.
	
	WRAP_CHAR = GTK_WRAP_CHAR,
	///< Wrap text, breaking lines anywhere the cursor can appear
	///< (between characters, usually - if you want to be technical,
	///< between graphemes, see Pango::LogAttr::get_log_attrs()).

	WRAP_WORD = GTK_WRAP_WORD,
	///< Wrap text, breaking lines in between words.

	WRAP_WORD_CHAR = GTK_WRAP_WORD_CHAR
	///< Wrap text, breaking lines in between words, or if that is not enough, also between graphemes.
};

/// Specifies the window type to create.

enum WindowType
{
	WINDOW_TOPLEVEL = GTK_WINDOW_TOPLEVEL,
	///< Windows with type WINDOW_TOPLEVEL (main windows, dialogs) are managed by the
	///< window manager and have a frame by default (nearly all windows should be
	///< WINDOW_TOPLEVEL).

	WINDOW_POPUP = GTK_WINDOW_POPUP
	///< Windows with type WINDOW_POPUP (menus, tooltips) are ignored by the window
	///< manager, window manager keybindings won't work on them, the window manager
	///< won't decorate the window with a frame, and many GTK+ features that rely
	///< on the window manager will not work (such as resize grips, maximization and
	///< minimization).
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ENUMS_HH

