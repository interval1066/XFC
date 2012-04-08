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
 
/// @file xfc/gtk/stockid.hh
/// @brief A GTK+ stock ID C++ wrapper interface.
///
/// Provides StockId, a simple object that wraps the GTK+ stock ID strings and
/// provides ready-to-use static StockIds for pre-registered GTK+ stock items,
/// such as Gtk::StockId::OPEN and Gtk::StockId::EXIT.

#ifndef XFC_GTK_STOCK_ID_HH
#define XFC_GTK_STOCK_ID_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __GTK_STOCK_H__
#include <gtk/gtkstock.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class StockId stockid.hh xfc/gtk/stockid.hh
/// @brief A C++ wrapper class for GTK+ stock IDs.
///
/// StockId is a simple class that has two purposes. First, it is a convenient
/// wrapper class that makes it possible to pass character strings to overloaded
/// constructors and functions that already have a character string argument, 
/// like a label, such as in Gtk::ImageMenuItem. Second, StockId provides
/// a ready-to-use static StockId for each pre-registered GTK+ stock item, such
/// as Gtk::StockId::OPEN and Gtk::StockId::EXIT. The StockId conversion operator
/// implicitly converts a StockId to a 'const char*' so you can pass a StockId 
/// to any function that takes a character string argument.
///
/// StockId is derived from Xfc::StackObject so it can only be created on the
/// stack and not dynamically on the heap. StockId does no memory mamangement. 
/// It's only member is a const char* which points to the StockId's corresponding
/// GTK+ stock ID string. GTK+ keeps a copy of all pre-registered stock ID strings
/// so local string memory management is not required. When you call Gtk::Stock::add()
/// to register a new stock item GTK+ will store a copy of your stock ID string.
///
/// The usual way to use Gtk::StockId is like this:
/// @code
/// void function(const StockId& stockId);
///
/// #include <xfc/gtk/stockid.hh>
///
/// function(Gtk::StockId::OPEN);
///
/// or
///
/// function(Gtk::StockId("my_stock_id"));
///
/// or
///
/// Gtk::StockId stock_id("my_stock_id");
/// function(stock_id);
/// @endcode

class StockId
{
	char *stock_id_;

public:
/// @name Constructors
/// @{	
	
	StockId();
	///< Constructs an empty StockId.

	StockId(const char *stock_id);
	///< Constructs a StockId for the stock ID character string <EM>stock_id</EM>.
	///< @param stock_id The stock id for a stock item.

	StockId(const String& stock_id);
	///< Constructs a StockId for the stock ID character string <EM>stock_id</EM>.
	///< @param stock_id The stock id for a stock item.

	StockId(const StockId& src);
	///< Copy constructor.
	///< @param src Another StockId.
	
	~StockId();
	///< Destructor.
	
	StockId& operator=(const StockId& src);
	///< Assignment operator.
	///< @param src Another StockId.
	///< @return A reference to the modified StockId, after assignment.
	
/// @}	
/// @name Accessors
/// @{	
	
	String str() const;
	///< Returns the stock id as a String.
	///< @return A String.  
	
	const char* c_str() const;
	///< Returns a pointer the stock ID's internal character string.
	///< @return A const pointer to the stock id character string.
	
	operator const char* () const;
	///< Conversion operator; safely converts a StockId to a 'const char' pointer.
	
/// @}	
/// @name Pre-registered Stock IDs (not all are stock items; some are images only)
/// @{
		
	static const StockId DIALOG_AUTHENTICATION; ///< stock indentifier: "gtk-dialog-authentication" 
	static const StockId DIALOG_INFO; ///< stock indentifier: "gtk-dialog-info"
	static const StockId DIALOG_WARNING; ///< stock indentifier: "gtk-dialog-warning"
	static const StockId DIALOG_ERROR; ///< stock indentifier: "gtk-dialog-error"
	static const StockId DIALOG_QUESTION; ///< stock indentifier: "gtk-dialog-question"
	static const StockId DND; ///< stock indentifier: "gtk-dnd"
	static const StockId DND_MULTIPLE; ///< stock indentifier: "gtk-dnd-multiple"
	static const StockId ABOUT; ///< stock indentifier: "gtk-about"
	static const StockId ADD; ///< stock indentifier: "gtk-add"
	static const StockId APPLY; ///< stock indentifier: "gtk-apply"
	static const StockId BOLD; ///< stock indentifier: "gtk-bold"
	static const StockId CANCEL; ///< stock indentifier: "gtk-cancel"
	static const StockId CDROM; ///< stock indentifier: "gtk-cdrom"
	static const StockId CLEAR; ///< stock indentifier: "gtk-clear"
	static const StockId CLOSE; ///< stock indentifier: "gtk-close"
	static const StockId COLOR_PICKER; ///< stock indentifier: "gtk-color-picker"
	static const StockId CONNECT; ///< stock indentifier: "gtk-connect"
	static const StockId CONVERT; ///< stock indentifier: "gtk-convert"
	static const StockId COPY ; ///< stock indentifier: "gtk-copy"
	static const StockId CUT; ///< stock indentifier: "gtk-cut"
	static const StockId DELETE; ///< stock indentifier: "gtk-delete"
	static const StockId DIRECTORY; ///< stock indentifier: "gtk-directory"
	static const StockId DISCONNECT; ///< stock indentifier: "gtk-disconnect"
	static const StockId EDIT; ///< stock indentifier: "gtk-edit"
	static const StockId EXECUTE; ///< stock indentifier: "gtk-execute"
	static const StockId FILE; ///< stock indentifier: "gtk-file"
	static const StockId FIND; ///< stock indentifier: "gtk-find"
	static const StockId FIND_AND_REPLACE; ///< stock indentifier: "gtk-find-and-replace"
	static const StockId FLOPPY; ///< stock indentifier: "gtk-floppy"
	static const StockId GOTO_BOTTOM; ///< stock indentifier: "gtk-goto-bottom" 
	static const StockId GOTO_FIRST; ///< stock indentifier: "gtk-goto-first"
	static const StockId GOTO_LAST; ///< stock indentifier: gtk-goto-last"
	static const StockId GOTO_TOP; ///< stock indentifier: "gtk-goto-top"
	static const StockId GO_BACK; ///< stock indentifier: "gtk-go-back"
	static const StockId GO_DOWN; ///< stock indentifier: "gtk-go-down"
	static const StockId GO_FORWARD; ///< stock indentifier: "gtk-go-forward"
	static const StockId GO_UP; ///< stock indentifier: "gtk-go-up"
	static const StockId HARDDISK; ///< stock indentifier: "gtk-harddisk"
	static const StockId HELP; ///< stock indentifier: "gtk-help"
	static const StockId HOME; ///< stock indentifier: "gtk-home"
	static const StockId INDEX; ///< stock indentifier: "gtk-index"
	static const StockId INDENT; ///< stock indentifier: "gtk-indent"
	static const StockId UNINDENT; ///< stock indentifier: "gtk-unindent"
	static const StockId ITALIC; ///< stock indentifier: "gtk-italic"
	static const StockId JUMP_TO; ///< stock indentifier: "gtk-jump-to"
	static const StockId JUSTIFY_CENTER; ///< stock indentifier: "gtk-justify-center"
	static const StockId JUSTIFY_FILL; ///< stock indentifier: "gtk-justify-fill"
	static const StockId JUSTIFY_LEFT; ///< stock indentifier: "gtk-justify-left"
	static const StockId JUSTIFY_RIGHT; ///< stock indentifier: "gtk-justify-right"
	static const StockId MISSING_IMAGE; ///< stock indentifier: "gtk-missing-image"
	static const StockId MEDIA_FORWARD; ///< stock indentifier: "gtk-media-forward"
	static const StockId MEDIA_NEXT; ///< stock indentifier: "gtk-media-next"
	static const StockId MEDIA_PAUSE; ///< stock indentifier: "gtk-media-pause"
	static const StockId MEDIA_PLAY; ///< stock indentifier: "gtk-media-play"
	static const StockId MEDIA_PREVIOUS; ///< stock indentifier: "gtk-media-previous"
	static const StockId MEDIA_RECORD; ///< stock indentifier: "gtk-media-record"
	static const StockId MEDIA_REWIND; ///< stock indentifier: "gtk-media-rewind"
	static const StockId MEDIA_STOP; ///< stock indentifier: "gtk-media-stop"
	static const StockId NETWORK; ///< stock indentifier: "gtk-network"
	static const StockId NEW; ///< stock indentifier: "gtk-new"
	static const StockId NO; ///< stock indentifier: "gtk-no"
	static const StockId OK; ///< stock indentifier: "gtk-ok"
	static const StockId OPEN; ///< stock indentifier: "gtk-open"
	static const StockId PASTE; ///< stock indentifier: "gtk-paste"
	static const StockId PREFERENCES; ///< stock indentifier: "gtk-preferences"
	static const StockId PRINT; ///< stock indentifier: "gtk-print"
	static const StockId PRINT_PREVIEW; ///< stock indentifier: "gtk-print-preview"
	static const StockId PROPERTIES; ///< stock indentifier: "gtk-properties"
	static const StockId QUIT; ///< stock indentifier: "gtk-quit"
	static const StockId REDO; ///< stock indentifier: "gtk-redo"
	static const StockId REFRESH; ///< stock indentifier: "gtk-refresh"
	static const StockId REMOVE; ///< stock indentifier: "gtk-remove"
	static const StockId REVERT_TO_SAVED; ///< stock indentifier: "gtk-revert-to-saved"
	static const StockId SAVE; ///< stock indentifier: "gtk-save"
	static const StockId SAVE_AS; ///< stock indentifier: "gtk-save-as"
	static const StockId SELECT_COLOR; ///< stock indentifier: "gtk-select-color"
	static const StockId SELECT_FONT; ///< stock indentifier: "gtk-select-font"
	static const StockId SORT_ASCENDING; ///< stock indentifier: "gtk-sort-ascending"
	static const StockId SORT_DESCENDING; ///< stock indentifier: "gtk-sort-descending"
	static const StockId SPELL_CHECK; ///< stock indentifier: "gtk-spell-check"
	static const StockId STOP; ///< stock indentifier: "gtk-stop"
	static const StockId STRIKETHROUGH; ///< stock indentifier: "gtk-strikethrough"
	static const StockId UNDELETE; ///< stock indentifier: "gtk-undelete"
	static const StockId UNDERLINE; ///< stock indentifier: "gtk-undo"
	static const StockId UNDO; ///< stock indentifier: "gtk-yes"
	static const StockId YES; ///< stock indentifier: "gtk-yes"
	static const StockId ZOOM_100; ///< stock indentifier: "gtk-zoom-100"
	static const StockId ZOOM_FIT; ///< stock indentifier: "gtk-zoom-fit"
	static const StockId ZOOM_IN; ///< stock indentifier: "gtk-zoom-in"
	static const StockId ZOOM_OUT; ///< stock indentifier: "gtk-zoom-out"
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/stockid.inl>

#endif // XFC_GTK_STOCK_ID_HH

