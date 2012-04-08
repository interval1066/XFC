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

/// @file xfc/gtk/entrycompletion.hh
/// @brief A GtkEntryCompletion C++ wrapper interface.
///
/// Provides EntryCompletion, an object that implements completion functionality for Gtk::Entry. 

#ifndef XFC_GTK_ENTRY_COMPLETION_HH
#define XFC_GTK_ENTRY_COMPLETION_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_CELL_LAYOUT_HH
#include <xfc/gtk/celllayout.hh>
#endif

#ifndef XFC_GTK_ENTRY_HH
#include <xfc/gtk/entry.hh>
#endif

#ifndef __GTK_ENTRY_COMPLETION_H__
#include <gtk/gtkentrycompletion.h>
#endif

namespace Xfc {

namespace Gtk {

class TreeIter;
class TreeModel;

/// @class EntryCompletion entrycompletion.hh xfc/gtk/entrycompletion.hh
/// @brief A GtkEntryCompletion C++ wrapper class.
///
/// EntryCompletion is an auxiliary object to be used in conjunction with Gtk::Entry to
/// provide the completion functionality. It implements the Gtk::CellLayout interface 
/// to allow the user to add extra cells to the Gtk::TreeView with completion matches. 
///
/// "Completion functionality" means that when the user modifies the text in the entry,
/// EntryCompletion checks which rows in the model match the current content of the entry,
/// and displays a list of matches. By default, the matching is done by comparing the entry
/// text case-insensitively against the text column of the model (see set_text_column()), 
/// but this can be overridden with a custom match function (see set_match_func()). 
///
/// When the user selects a completion, the content of the entry is updated. By default,
/// the content of the entry is replaced by the text column of the model, but this can 
/// be overridden by connecting to the "match_selected" signal and updating the entry
/// in the signal handler. Note that you should return <EM>true</EM> from the signal
/// handler to suppress the default behaviour. 
///
/// To add completion functionality to an entry, use Gtk::Entry::set_completion(). In 
/// addition to regular completion matches, which will be inserted into the entry when
/// they are selected, EntryCompletion also allows you to display 'actions' in the popup 
/// window. Their appearance is similar to menuitems, to differentiate them clearly from
/// completion strings. When an action is selected, the "action_activated" signal is emitted. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/entrycompletion.html">Entry Completion</A> HOWTO and example,
/// and the entry completion example in the <tests/entrycompletion> subdirectory.

class EntryCompletion : public G::Object, public CellLayout
{
	friend class G::Object;

	EntryCompletion(const EntryCompletion&);
	EntryCompletion& operator=(const EntryCompletion&);

protected:
/// @name Constructors
/// @{

	explicit EntryCompletion(GtkEntryCompletion *completion, bool owns_reference = true);
	///< Construct a new EntryCompletion from an existing GtkEntryCompletion.
	///< @param completion A pointer to a GtkEntryCompletion.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>completion</EM> can be a newly created GtkEntryCompletion or an existing
	///< GtkEntryCompletion (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<bool, const TreeModel&, const TreeIter&> MatchSelectedSignalType;
	typedef G::SignalProxy<TypeInstance, MatchSelectedSignalType> MatchSelectedSignalProxy;
	static const MatchSelectedSignalType match_selected_signal;
	///< Match selected signal (see signal_match_selected()). Calls a slot with the signature:
	///< @code
	///< bool function(const TreeModel& model, const TreeIter& iter);
	///< // model: The Gtk::TreeModel containing the matches.
	///< // iter: A Gtk::TreeIter positioned at the selected match.
	///< // return: true if the signal has been handled.
	///< @endcode
	
	typedef G::Signal<void, int> ActionActivatedSignalType;
	typedef G::SignalProxy<TypeInstance, ActionActivatedSignalType> ActionActivatedSignalProxy;
	static const ActionActivatedSignalType action_activated_signal;
	///< Action activated selected signal (see signal_action_activated()). Calls a slot with the signature:
	///< @code
	///< void function(const TreeModel& model, const TreeIter& iter);
	///< // index: The index of the activated action.
	///< @endcode
	
	typedef G::Signal<bool, const String&> InsertPrefixSignalType;
	typedef G::SignalProxy<TypeInstance, InsertPrefixSignalType> InsertPrefixSignalProxy;
	static const InsertPrefixSignalType insert_prefix_signal;
	///< Insert prefix signal (see signal_insert_prefix()). Calls a slot with the signature:
	///< @code
	///< bool function(const String& prefix);
	///< @param prefix The common prefix of all possible completions.
	///< @return <EM>true</EM> if the signal has been handled.
	///< @endcode
	///< 
	///< The default behaviour is to make the entry display the whole prefix and select
	///< the newly inserted part. Applications may connect to this signal in order to
	///< insert only a smaller part of the prefix into the entry - e.g. the entry used
	///< in Gtk::FileChooser inserts only the part of the prefix up to the next '/'.
	
/// @}

public:
	typedef GtkEntryCompletion CObjectType;
	
	typedef sigc::slot<bool, const String&, const TreeIter&> MatchSlot;
	///< Signature of the callback slot to be called the row indicated by the TreeIter
	///< matches a given key, and should be displayed as a possible completion for key. 
	///<
	///< <B>Example:</B> Method signature for MatchSlot.
	///< @code
	///< bool method(const String& key, const TreeIter& iter);
	///< // key: The string to match.
	///< // iter: A TreeIter indicating indicating the row to match.
	///< // return: <EM>true</EM> if <EM>iter</EM> should be displayed as a possible completion for <EM>key</EM>. 
	///< @endcode

/// @name Constructors
/// @{

	EntryCompletion();
	///< Constructs a new entry completion object with a reference count of 1 that the caller owns.
	
	EntryCompletion(TreeModel& model);
	///< Constructs a new entry completion object that uses the specified <EM>model</EM>.
	///< @param model The model for the entry completion.
	///<
	///< The new entry completion has a reference count of 1 that the caller owns.
	
	virtual ~EntryCompletion();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkEntryCompletion* gtk_entry_completion() const;
	///< Get a pointer to the GtkEntryCompletion structure.

	operator GtkEntryCompletion* () const;
	///< Conversion operator; safely converts an EntryCompletion to a GtkEntryCompletion pointer.

	Entry* get_entry() const;
	///< Gets the entry widget the completion has been attached to.
	///< @return The entry widget the completion is attached to.
	
	TreeModel* get_model() const;
	///< Gets the model the entry completion is using as a data source. 
	///< @return A Gtk::TreeModel, or null if none is currently being used.

	int get_minimum_key_length() const;
	///< Gets the minimum key length as set for completion.
	///< @return The currently used minimum key length.
	 
	bool get_inline_completion() const;
	///< Determines whether the common prefix of the possible completions
	///< should be automatically inserted in the entry.
	///< @return <EM>true</EM> if inline completion is turned on.
	
	bool get_popup_completion() const;
	///< Determines whether the completions should be presented in a popup window.
	///< @return <EM>true</EM> if popup completion is turned on.
	 
	int get_text_column() const;
	///< Gets the column in the model of completion to get strings from.
	///< @return The column containing the strings. 

/// @}
/// @name Methods
/// @{

	void set_model(TreeModel& model);
	///< Sets the model for the entry completion. 
	///< @param model The Gtk::TreeModel.
	///< 
	///< If the completion already has a model set, it will remove it
	///< before setting the new model.

	void set_match_func(const MatchSlot& slot);
	///< Sets the match callback slot for completion to be <EM>slot</EM>.
	///< @param slot The MatchSlot to use.
	///<	 
	///< The match slot is used to determine if a row should
	///< or should not be in the completion list.

	void set_minimum_key_length(int length);
	///< Requires the length of the search key for completion to be at least length.
	///< @param length The minimum length of the key in order to start completing. 
	///< 	 
	///< This is useful for long lists, where completing using a small key takes a lot of
	///< time and will come up with meaningless results anyway (ie, a too large dataset).

	void complete();
	///< Requests a completion operation, or in other words a refiltering
	///< of the current list with completions, using the current key. The 
	///< completion list view will be updated accordingly.

	void insert_prefix();
	///< Requests a prefix insertion.
	
	void insert_action_text(int index, const char *text);
	void insert_action_text(int index, const String& text);
	///< Inserts an action in completion's action item list at position <EM>index</EM>
	///< with text <EM>text</EM>. 
	///< @param index The index of the item to insert. 
	///< @param text The text of the item to insert. 
	///<	
	///< If you want the action item to have markup, use insert_action_markup().
	
	void insert_action_markup(int index, const char *markup);
	void insert_action_markup(int index, const String& markup);
	///< Inserts an action in completion's action item list at position <EM>index</EM>
	///< with markup <EM>markup</EM>.
	///< @param index The index of the item to insert. 
	///< @param markup The markup of the item to insert. 

	void delete_action(int index);
	///< Deletes the action at <EM>index</EM> from completion's action list.
	////< @param index The index of the item to delete. 
	
	void set_inline_completion(bool inline_completion);
	///< Sets whether the common prefix of the possible completions
	///< should be automatically inserted in the entry.
	///< @param inline_completion Set to <EM>true</EM> to do inline completion.
	
	void set_popup_completion(bool popup_completion);
	///< Sets whether the completions should be presented in a popup window.
	///< @param popup_completion Set to <EM>true</EM> to do popup completion.
	
	void set_text_column(int column);
	///< A convenience method for setting up the most used case of this 
	///< code: a completion list with just strings. 
	///< @param column The column in the model of completion to get strings from.
	///<	
	///< This method will set up the completion to have a list displaying all
	///< (and just) strings in the completion list, and to get those strings from
	///< <EM>column</EM> in the model of completion. It creates and adds a 
	///< Gtk::CellRendererText for the selected column.

/// @}
/// @name Signal Proxies
/// @{
	
	const MatchSelectedSignalProxy signal_match_selected();
	///< Connect to the match_selected_signal; emitted when a match from the list is selected.
	
	const ActionActivatedSignalProxy signal_action_activated();
	///< Connect to the action_activated_signal; emitted when an action is activated.

	const InsertPrefixSignalProxy signal_insert_prefix();
	///< Connect to the insert_prefix_signal; emitted when the inline autocompletion is triggered.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/entrycompletion.inl>

#endif // XFC_GTK_ENTRY_COMPLETION_HH

