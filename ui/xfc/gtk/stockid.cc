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
 
#include "stockid.hh"

using namespace Xfc;

/*  Gtk::StockId
 */

Gtk::StockId::StockId()
: stock_id_(0)
{
}

Gtk::StockId::StockId(const char *stock_id)
: stock_id_(g_strdup(stock_id))
{
}

Gtk::StockId::StockId(const String& stock_id)
: stock_id_(g_strdup(stock_id.c_str()))
{
}

Gtk::StockId::StockId(const StockId& src)
: stock_id_(g_strdup(src.stock_id_))
{
}	

Gtk::StockId::~StockId()
{
	if (stock_id_)
		g_free(stock_id_);
}

Gtk::StockId& 
Gtk::StockId::operator=(const StockId& src)
{
	if (src.stock_id_ == stock_id_)
		return *this;
	
	if (stock_id_)
		g_free(stock_id_);
			
	stock_id_ = g_strdup(src.stock_id_);
	return *this;
}
	
String 
Gtk::StockId::str() const
{
	return stock_id_;
}

/*  Gtk::StockId pre-registered stock identifiers
 */

const Gtk::StockId Gtk::StockId::DIALOG_AUTHENTICATION (GTK_STOCK_DIALOG_AUTHENTICATION);
const Gtk::StockId Gtk::StockId::DIALOG_INFO (GTK_STOCK_DIALOG_INFO);
const Gtk::StockId Gtk::StockId::DIALOG_WARNING (GTK_STOCK_DIALOG_WARNING);
const Gtk::StockId Gtk::StockId::DIALOG_ERROR (GTK_STOCK_DIALOG_ERROR);
const Gtk::StockId Gtk::StockId::DIALOG_QUESTION (GTK_STOCK_DIALOG_QUESTION);
const Gtk::StockId Gtk::StockId::DND (GTK_STOCK_DND);
const Gtk::StockId Gtk::StockId::DND_MULTIPLE (GTK_STOCK_DND_MULTIPLE);
const Gtk::StockId Gtk::StockId::ABOUT (GTK_STOCK_ABOUT);
const Gtk::StockId Gtk::StockId::ADD (GTK_STOCK_ADD);
const Gtk::StockId Gtk::StockId::APPLY (GTK_STOCK_APPLY);
const Gtk::StockId Gtk::StockId::BOLD (GTK_STOCK_BOLD);
const Gtk::StockId Gtk::StockId::CANCEL (GTK_STOCK_CANCEL);
const Gtk::StockId Gtk::StockId::CDROM (GTK_STOCK_CDROM);
const Gtk::StockId Gtk::StockId::CLEAR (GTK_STOCK_CLEAR);
const Gtk::StockId Gtk::StockId::CLOSE (GTK_STOCK_CLOSE);
const Gtk::StockId Gtk::StockId::COLOR_PICKER (GTK_STOCK_COLOR_PICKER);
const Gtk::StockId Gtk::StockId::CONNECT (GTK_STOCK_CONNECT);
const Gtk::StockId Gtk::StockId::CONVERT (GTK_STOCK_CONVERT);
const Gtk::StockId Gtk::StockId::COPY (GTK_STOCK_COPY);
const Gtk::StockId Gtk::StockId::CUT (GTK_STOCK_CUT);
const Gtk::StockId Gtk::StockId::DELETE (GTK_STOCK_DELETE);
const Gtk::StockId Gtk::StockId::DIRECTORY (GTK_STOCK_DIRECTORY);
const Gtk::StockId Gtk::StockId::DISCONNECT (GTK_STOCK_DISCONNECT);
const Gtk::StockId Gtk::StockId::EDIT (GTK_STOCK_EDIT);
const Gtk::StockId Gtk::StockId::EXECUTE (GTK_STOCK_EXECUTE);
const Gtk::StockId Gtk::StockId::FILE (GTK_STOCK_FILE);
const Gtk::StockId Gtk::StockId::FIND (GTK_STOCK_FIND);
const Gtk::StockId Gtk::StockId::FIND_AND_REPLACE (GTK_STOCK_FIND_AND_REPLACE);
const Gtk::StockId Gtk::StockId::FLOPPY (GTK_STOCK_FLOPPY);
const Gtk::StockId Gtk::StockId::GOTO_BOTTOM (GTK_STOCK_GOTO_BOTTOM);
const Gtk::StockId Gtk::StockId::GOTO_FIRST (GTK_STOCK_GOTO_FIRST);
const Gtk::StockId Gtk::StockId::GOTO_LAST (GTK_STOCK_GOTO_LAST);
const Gtk::StockId Gtk::StockId::GOTO_TOP (GTK_STOCK_GOTO_TOP);
const Gtk::StockId Gtk::StockId::GO_BACK (GTK_STOCK_GO_BACK);
const Gtk::StockId Gtk::StockId::GO_DOWN (GTK_STOCK_GO_DOWN);
const Gtk::StockId Gtk::StockId::GO_FORWARD (GTK_STOCK_GO_FORWARD);
const Gtk::StockId Gtk::StockId::GO_UP (GTK_STOCK_GO_UP);
const Gtk::StockId Gtk::StockId::HARDDISK (GTK_STOCK_HARDDISK);
const Gtk::StockId Gtk::StockId::HELP (GTK_STOCK_HELP);
const Gtk::StockId Gtk::StockId::HOME (GTK_STOCK_HOME);
const Gtk::StockId Gtk::StockId::INDEX (GTK_STOCK_INDEX);
const Gtk::StockId Gtk::StockId::INDENT (GTK_STOCK_INDENT);
const Gtk::StockId Gtk::StockId::UNINDENT (GTK_STOCK_UNINDENT);
const Gtk::StockId Gtk::StockId::ITALIC (GTK_STOCK_ITALIC);
const Gtk::StockId Gtk::StockId::JUMP_TO (GTK_STOCK_JUMP_TO);
const Gtk::StockId Gtk::StockId::JUSTIFY_CENTER (GTK_STOCK_JUSTIFY_CENTER);
const Gtk::StockId Gtk::StockId::JUSTIFY_FILL (GTK_STOCK_JUSTIFY_FILL);
const Gtk::StockId Gtk::StockId::JUSTIFY_LEFT (GTK_STOCK_JUSTIFY_LEFT);
const Gtk::StockId Gtk::StockId::JUSTIFY_RIGHT (GTK_STOCK_JUSTIFY_RIGHT);
const Gtk::StockId Gtk::StockId::MISSING_IMAGE (GTK_STOCK_MISSING_IMAGE);
const Gtk::StockId Gtk::StockId::MEDIA_FORWARD (GTK_STOCK_MEDIA_FORWARD);
const Gtk::StockId Gtk::StockId::MEDIA_NEXT (GTK_STOCK_MEDIA_NEXT);
const Gtk::StockId Gtk::StockId::MEDIA_PAUSE (GTK_STOCK_MEDIA_PAUSE);
const Gtk::StockId Gtk::StockId::MEDIA_PLAY (GTK_STOCK_MEDIA_PLAY);
const Gtk::StockId Gtk::StockId::MEDIA_PREVIOUS (GTK_STOCK_MEDIA_PREVIOUS);
const Gtk::StockId Gtk::StockId::MEDIA_RECORD (GTK_STOCK_MEDIA_RECORD);
const Gtk::StockId Gtk::StockId::MEDIA_REWIND (GTK_STOCK_MEDIA_REWIND);
const Gtk::StockId Gtk::StockId::MEDIA_STOP (GTK_STOCK_MEDIA_STOP);
const Gtk::StockId Gtk::StockId::NETWORK (GTK_STOCK_NETWORK);
const Gtk::StockId Gtk::StockId::NEW (GTK_STOCK_NEW);
const Gtk::StockId Gtk::StockId::NO (GTK_STOCK_NO);
const Gtk::StockId Gtk::StockId::OK (GTK_STOCK_OK);
const Gtk::StockId Gtk::StockId::OPEN (GTK_STOCK_OPEN);
const Gtk::StockId Gtk::StockId::PASTE (GTK_STOCK_PASTE);
const Gtk::StockId Gtk::StockId::PREFERENCES (GTK_STOCK_PREFERENCES);
const Gtk::StockId Gtk::StockId::PRINT (GTK_STOCK_PRINT);
const Gtk::StockId Gtk::StockId::PRINT_PREVIEW (GTK_STOCK_PRINT_PREVIEW);
const Gtk::StockId Gtk::StockId::PROPERTIES (GTK_STOCK_PROPERTIES);
const Gtk::StockId Gtk::StockId::QUIT (GTK_STOCK_QUIT);
const Gtk::StockId Gtk::StockId::REDO (GTK_STOCK_REDO);
const Gtk::StockId Gtk::StockId::REFRESH (GTK_STOCK_REFRESH);
const Gtk::StockId Gtk::StockId::REMOVE (GTK_STOCK_REMOVE);
const Gtk::StockId Gtk::StockId::REVERT_TO_SAVED (GTK_STOCK_REVERT_TO_SAVED);
const Gtk::StockId Gtk::StockId::SAVE (GTK_STOCK_SAVE);
const Gtk::StockId Gtk::StockId::SAVE_AS (GTK_STOCK_SAVE_AS);
const Gtk::StockId Gtk::StockId::SELECT_COLOR (GTK_STOCK_SELECT_COLOR);
const Gtk::StockId Gtk::StockId::SELECT_FONT (GTK_STOCK_SELECT_FONT);
const Gtk::StockId Gtk::StockId::SORT_ASCENDING (GTK_STOCK_SORT_ASCENDING);
const Gtk::StockId Gtk::StockId::SORT_DESCENDING (GTK_STOCK_SORT_DESCENDING);
const Gtk::StockId Gtk::StockId::SPELL_CHECK (GTK_STOCK_SPELL_CHECK);
const Gtk::StockId Gtk::StockId::STOP (GTK_STOCK_STOP);
const Gtk::StockId Gtk::StockId::STRIKETHROUGH (GTK_STOCK_STRIKETHROUGH);
const Gtk::StockId Gtk::StockId::UNDELETE (GTK_STOCK_UNDELETE);
const Gtk::StockId Gtk::StockId::UNDERLINE (GTK_STOCK_UNDERLINE);
const Gtk::StockId Gtk::StockId::UNDO (GTK_STOCK_UNDO);
const Gtk::StockId Gtk::StockId::YES (GTK_STOCK_YES);
const Gtk::StockId Gtk::StockId::ZOOM_100 (GTK_STOCK_ZOOM_100);
const Gtk::StockId Gtk::StockId::ZOOM_FIT (GTK_STOCK_ZOOM_FIT);
const Gtk::StockId Gtk::StockId::ZOOM_IN (GTK_STOCK_ZOOM_IN);
const Gtk::StockId Gtk::StockId::ZOOM_OUT (GTK_STOCK_ZOOM_OUT);

