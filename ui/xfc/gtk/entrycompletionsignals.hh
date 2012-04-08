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

/// @file xfc/gtk/entrycompletionsignals.hh
/// @brief Gtk::EntryCompletion virtual signal handlers.
///
/// Provides Gtk::EntryCompletionSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::EntryCompletion objects.

#ifndef XFC_GTK_ENTRY_COMPLETION_SIGNALS_HH
#define XFC_GTK_ENTRY_COMPLETION_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class EntryCompletionSignals entrycompletionsignals.hh xfc/gtk/entrycompletionsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::EntryCompletion.

class EntryCompletionSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	EntryCompletionSignals(EntryCompletion *completion);
	///< Construct a new EntryCompletionSignals object.
	///< @param completion A EntryCompletion object inheriting the EntryCompletionSignals implementation.

	virtual ~EntryCompletionSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual bool on_match_selected(const TreeModel& model, const TreeIter& iter);
	///< Called when a match from the list is selected. 
	///< @param model The Gtk::TreeModel containing the matches.
	///< @param iter A Gtk::TreeIter positioned at the selected match.
	///< @return <EM>true</EM> if the signal has been handled.
	///< 	
	///< The default behaviour is to replace the contents of the entry with
	///< the contents of the text column in the row pointed to by <EM>iter</EM>.	

	virtual void on_action_activated(int index);
	///< Called when an action is activated.
	///< @param index The index of the activated action.

	virtual bool on_insert_prefix(const String& prefix);
	///< Called when the inline autocompletion is triggered.
	///< @param prefix The common prefix of all possible completions.
	///< @return <EM>true</EM> if the signal has been handled.
	///< 
	///< The default behaviour is to make the entry display the whole prefix and select
	///< the newly inserted part. Applications may override this signal handler in order
	///< to insert only a smaller part of the prefix into the entry - e.g. the entry used
	///< in Gtk::FileChooser inserts only the part of the prefix up to the next '/'.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ENTRY_COMPLETION_SIGNALS_HH

