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
 
//! @file inti/gtk-sourceview/sourcebuffer.h
//! @brief A GtkSourceBuffer C++ wrapper interface.
//!
//! Provides SourceBuffer, a Gtk::TextBuffer object that implements syntax highlighting,
//! bracket matching, markers and support for undo/redo operations.

#ifndef XFC_GTK_SOURCE_BUFFER_H
#define XFC_GTK_SOURCE_BUFFER_H

#ifndef XFC_GTK_TEXT_BUFFER_HH
#include <xfc/gtk/textbuffer.hh>
#endif

#ifndef XFC_GTK_SOURCE_LANGUAGE_HH
#include <xfc/sourceview/sourcelanguage.hh>
#endif

#ifndef XFC_GTK_SOURCE_TAG_HH
#include <xfc/sourceview/sourcetag.hh>
#endif

#ifndef __GTK_SOURCE_BUFFER_H__
#include <gtksourceview/gtksourcebuffer.h>
#endif

namespace Xfc {

namespace Gtk {

class SourceBuffer;
class SourceLanguage;
class SourceMarker;

//! @class SourceMarker sourcebuffer.h inti/gtk-sourceview/sourcebuffer.h
//! @brief A GtkSourceMarker C++ wrapper class.
//!
//! SourceMarker is like a bookmark in a source buffer; it preserves a position
//! in the text across source buffer modifications (see Gtk::TextMark). Typical
//! uses for markers are bookmarks, breakpoints, current executing instruction
//! indication in a source file, etc..

class SourceMarker : public TextMark
{
	friend class G::Object;

	SourceMarker(const SourceMarker&);
	SourceMarker& operator=(const SourceMarker&);

protected:
//! @name Constructors
//! @{

	explicit SourceMarker(GtkSourceMarker *marker, bool reference = false);
	//!< Construct a new SourceMarker from an existing GtkSourceMarker.
	//!< @param marker A pointer to a GtkSourceMarker.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>marker</EM> can be a newly created GtkSourceMarker or an existing
	//!< GtkSourceMarker (see G::Object::Object).

//! @}

public:
//! @name Constructors
//! @{

	virtual ~SourceMarker();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceMarker* gtk_source_marker() const { return reinterpret_cast<GtkSourceMarker*>( instance_ ); }
	//!< Get a pointer to the GtkSourceMarker structure.

	operator GtkSourceMarker* () const;
	//!< Conversion operator; safely converts a SourceMarker to a GtkSourceMarker pointer.

	bool is_gtk_source_marker() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_MARKER.

	String get_marker_type() const;
	//!< Returns a String identifying marker type.

	int get_line() const;
	//!< Returns the line number containing the marker.

	String get_name() const;
	//!< Returns the name of the marker.

	SourceBuffer* get_buffer() const;
	//!< Returns the SourceBuffer this marker is associated with.

	SourceMarker* next() const;
	//!< Move to the next marker in the source buffer.
	//!< @return The next marker.

	SourceMarker* prev() const;
	//!< Move to the previous marker in the source buffer.
	//!< @return The previous marker.

//! @}
//! @name Methods
//! @{

	void set_marker_type(const String& type);
	//!< Set the marker type.
	//!< @param type The marker type.

//! @}
};

//! @class SourceBuffer sourcebuffer.h inti/gtk-sourceview/sourcebuffer.h
//! @brief A GtkSourceBuffer C++ wrapper class.
//!
//! The SourceBuffer object is the text model for SourceView widgets. It extends
//! the Gtk::TextBuffer object by adding features necessary to display and edit
//! source code: syntax highlighting, bracket matching and markers. It also
//! implements support for undo/redo operations. By default syntax highlighting
//! is enabled, but you can disable it with set_highlight(). This can be useful
//! if you're not using SourceLanguage objects to set the highlighting patterns
//! but instead you're manually adding SourceTag objects to the buffer's tag table.

class SourceBuffer : public TextBuffer
{
	friend class G::Object;

	SourceBuffer(const SourceBuffer&);
	SourceBuffer& operator=(const SourceBuffer&);

protected:
//! @name Constructors
//! @{

	explicit SourceBuffer(GtkSourceBuffer *buffer, bool owns_reference = true);
	//!< Construct a new SourceBuffer from an existing GtkSourceBuffer.
	//!< @param buffer A pointer to a GtkSourceBuffer.
	//!< @param reference Set <EM>false</EM> if the initial reference count is floating,
	//!< set <EM>true</EM> if it's not.
	//!<
	//!< <BR>The <EM>buffer</EM> can be a newly created GtkSourceBuffer or an existing
	//!< GtkSourceBuffer (see G::Object::Object).

//! @}
//  Properties

	typedef G::Property<G::Unichar> EscapeCharPropertyType;
	typedef G::PropertyProxy<G::Object, EscapeCharPropertyType> EscapeCharPropertyProxy;
	static const EscapeCharPropertyType escape_char_property;

	typedef G::Property<bool> CheckBracketsPropertyType;
	typedef G::PropertyProxy<G::Object, CheckBracketsPropertyType> CheckBracketsPropertyProxy;
	static const CheckBracketsPropertyType check_brackets_property;

	typedef G::Property<bool> HighlightPropertyType;
	typedef G::PropertyProxy<G::Object, HighlightPropertyType> HighlightPropertyProxy;
	static const HighlightPropertyType highlight_property;

	typedef G::Property<int> MaxUndoLevelsPropertyType;
	typedef G::PropertyProxy<G::Object, MaxUndoLevelsPropertyType> MaxUndoLevelsPropertyProxy;
	static const MaxUndoLevelsPropertyType max_undo_levels_property;

	typedef G::Property<SourceLanguage*, G::Object*> LanguagePropertyType;
	typedef G::PropertyProxy<G::Object, LanguagePropertyType> LanguagePropertyProxy;
	static const LanguagePropertyType language_property;

//  Signals

	typedef G::Signal1<void, bool> CanUndoSignalType;
	typedef G::SignalProxy<TypeInstance, CanUndoSignalType> CanUndoSignalProxy;
	static const CanUndoSignalType can_undo_signal;

	typedef G::Signal1<void, bool> CanRedoSignalType;
	typedef G::SignalProxy<TypeInstance, CanRedoSignalType> CanRedoSignalProxy;
	static const CanRedoSignalType can_redo_signal;

	typedef G::Signal2<void, GtkTextIter*, GtkTextIter*> HighlightUpdatedSignalType;
	typedef G::SignalProxy<TypeInstance, HighlightUpdatedSignalType> HighlightUpdatedSignalProxy;
	static const HighlightUpdatedSignalType highlight_updated_signal;

	typedef G::Signal1<void, GtkTextIter*> MarkerUpdatedSignalType;
	typedef G::SignalProxy<TypeInstance, MarkerUpdatedSignalType> MarkerUpdatedSignalProxy;
	static const MarkerUpdatedSignalType marker_updated_signal;

public:
//! @name Constructors
//! @{

	SourceBuffer(SourceTagTable *table = 0);
	//!< Constructs a new source buffer with a empty default buffer.
	//!< @param table A source tag table, or null to have the text buffer create one for you.

	SourceBuffer(const SourceLanguage& language);
	//!< Constructs a new source buffer which will highlight text according to the specified language.
	//!< @param language The source language.

	virtual ~SourceBuffer();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceBuffer* gtk_source_buffer() const { return reinterpret_cast<GtkSourceBuffer*>(instance_); }
	//!< Get a pointer to the GtkSourceBuffer structure.

	operator GtkSourceBuffer* () const;
	//!< Conversion operator; safely converts a SourceBuffer to a GtkSourceBuffer pointer.

	bool is_gtk_source_buffer() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_BUFFER.

	SourceTagTable* get_source_tag_table() const;
	//!< Get the SourceTagTable associated with the buffer.
	//!< @return The buffer's tag table.

	bool get_check_brackets() const;
	//!<  Determines whether bracket match highlighting is activated for the source buffer.
	//!< @return <EM>true</EM> if the source buffer will highlight matching brackets.

	bool get_highlight() const;
	//!< Determines whether text highlighting is activated in the source buffer.
	//!< @return <EM>true</EM> if highlighting is enabled.

	int get_max_undo_levels() const;
	//!<  Determines the number of undo levels the buffer will track for buffer edits.
	//!< @return The maximum number of possible undo levels.

	SourceLanguage* get_language() const;
	//!< Determines the SourceLanguage used by the buffer.
	//!< @return The SourceLangauge (should not be unreferenced by the user).

	G::Unichar get_escape_char() const;
	//!< Determines the escape character used by the source buffer highlighting engine.
	//!< @return A G::Unichar that holds the UTF-8 escape character the buffer is using.

	bool can_undo() const;
	//!< Determines whether a source buffer can undo the last action.
	//!< @return <EM>true</EM> if it's possible to undo the last action.

	bool can_redo() const;
	//!< Determines whether a source buffer can redo the last undo action.
	//!< @return <EM>true</EM> if buffer changes that were undone can be redone.

	SourceMarker* get_marker(const String& name) const;
	//!<  Looks up the SourceMarker named <EM>name</EM> in the buffer, returning
	//!< null if it doesn't exists.
	//!< @param name The name of the marker to retrieve.
	//!< @return The SourceMarker identified by <EM>name</EM>, or null.

	std::vector<SourceMarker*> get_markers(const TextIter& start, const TextIter& end) const;
	//!< Gets a list of the source markers inside the range delimited by <EM>start</EM> and <EM>end</EM>.
	//!< @param start The beginning of the range.
	//!< @param end The end of the range.
	//!< @return A vector of SourceMarker pointers inside the range.

	SourceMarker* get_first_marker() const;
	//!< Gets the first marker (nearest to the top) in the buffer.
	//!< @return A pointer to the first SourceMarker, or null if there are no markers in the buffer.

	SourceMarker* get_last_marker() const;
	//!< Gets the last marker (nearest to the end) in the buffer.
	//!< @return A pointer to the last SourceMarker, or null if there are no markers in the buffer.

	TextIter get_iter_at_marker(const SourceMarker& marker) const;
	//!< Obtains an initialized iterator to the location of <EM>marker</EM>.
	//!< @return The initialized iterator.

	SourceMarker* get_next_marker(TextIter& iter) const;
	//!< Gets the nearest marker to the right of iter.
	//!< @param iter The location to start searching from.
	//!< @return The SourceMarker nearest to the right of iter, or null if there are no more markers after iter.
	//!<
	//!< <BR>If there are multiple markers at the same position, this function will always return
	//!< the first one (from the internal linked list), even if starting the search exactly at
	//!< its location. You can get the others using Gtk::SourceMarker::next().

	SourceMarker* get_prev_marker(TextIter& iter) const;
	//!< Gets the nearest marker to the left of iter.
	//!< @param iter The location to start searching from.
	//!< @return The SourceMarker nearest to the left of iter, or null if there are no more markers before iter.
	//!<
	//!< <BR>If there are multiple markers at the same position, this function will always return
	//!< the last one (from the internal linked list), even if starting the search exactly at
	//!< its location. You can get the others using Gtk::SourceMarker::prev().

//! @}
//! @name Methods
//! @{

	void set_check_brackets(bool check_brackets);
	//!< Controls the bracket match highlighting function in the buffer.
	//!< @param check_brackets Set <EM>true</EM> if you want matching brackets highlighted.
	//!<
	//!< <BR>If activated, when you position your cursor over a bracket character
	//!< (a parenthesis, a square bracket, etc.) the matching opening or closing
	//!< bracket character will be highlighted. You can specify the style with the
	//!< set_bracket_match_style() method.

	void set_bracket_match_style(const SourceTagStyle& style);
	//!< Sets the style used for highlighting matching brackets.
	//!< @param style The SourceTagStyle that specifies the color and text attributes to use.

	void set_highlight(bool highlight);
	//!< Controls whether text is highlighted in the buffer.
	//!< @param highlight Set <EM>true</EM> if you want to activate highlighting.
	//!<
	//!< <BR>If <EM>highlight</EM> is <EM>true</EM> the text will be highlighted according
	//!< to the patterns installed in the buffer (either set with set_language() or by
	//!< adding individual SourceTags to the buffer's tag table). Otherwise, any current
	//!< highlighted text will be restored to the default buffer style.
	//!<
	//!< Tags not of the SourceTag type will not be removed by this option, and normal
	//!< Gtk::TextTag priority settings apply when highlighting is enabled.
	//!<
	//!< If you're not using a SourceLanguage to set the highlighting patterns
	//!< in the buffer, it is recommended for performance reasons that you add
	//!< all the SourceTags with highlighting disabled and enable highlighting
	//!< when finished.

	void set_max_undo_levels(int max_undo_levels);
	//!< Sets the number of undo levels for user actions the buffer will track.
	//!< @param max_undo_levels The desired maximum number of undo levels.
	//!<
	//!< <BR>If the number of user actions exceeds the limit set by this function,
	//!< older actions will be discarded. A new action is started whenever the
	//!< function Gtk::TextBuffer::begin_user_action() is called. In general,
	//!< this happens whenever the user presses any key which modifies the buffer,
	//!< but the undo manager will try to merge similar consecutive actions, such
	//!< as multiple character insertions into one action. But, inserting a newline
	//!< does start a new action.

	void set_language(const SourceLanguage *language);
	//!< Sets the SourceLanguage the source buffer will use, adding SourceTags with the
	//!< language's patterns and setting the escape character with set_escape_char().
	//!< @param language The SourceLanguage to set, or null.
	//!<
	//!< <BR>Note that this will remove any SourceTags currently in the buffer's tag table.
	//!< The buffer holds a reference to the language set.

	void set_escape_char(G::Unichar escape_char);
	//!< Sets the escape character to be used by the highlighting engine.
	//!< @param escape_char A G::Unichar holding the escape character the buffer should use.
	//!<
	//!< <BR>When performing the initial analysis, the engine will discard a matching
	//!< syntax pattern if it's prefixed with an odd number of escape characters. This
	//!< allows for example to correctly highlight strings with escaped quotes embedded.
	//!< This setting affects only syntax patterns (i.e. those defined in SyntaxTags).

 	void undo();
	//!< Undoes the last user action which modified the buffer. Use can_undo() to check
	//!< whether a call to this method will have any effect. Actions are defined as groups
	//!< of operations between a call to Gtk::TextBuffer's begin_user_action() and
	//!< end_user_action() methods, or sequences of similar edits (inserts or deletes) on
	//!< the same line.

	void redo();
	//!< Redoes the last undo operation. Use can_redo() to check whether a call to this
	//!< method will have any effect.

	void begin_not_undoable_action();
	//!< Marks the beginning of a not undoable action on the buffer, disabling the undo manager.
	//!< Typically you would call this method before initially setting the contents of the buffer
	//!< (e.g. when loading a file in a text editor). You may nest begin_not_undoable_action()
	//!< / end_not_undoable_action() blocks.

	void end_not_undoable_action();
	//!< Marks the end of a not undoable action on the buffer. When the last not undoable block
	//!< is closed through the call to this method, the list of undo actions is cleared and the
	//!< undo manager is re-enabled.

	SourceMarker* create_marker(const String& name, const String& type, const TextIter& where);
	//!< Creates a marker in the buffer of type <EM>type</EM>.
	//!< @param name The name of the marker, or null for an anonymous marker.
	//!< @param type A String defining the marker type, or null.
	//!< @param where The location to place the new marker.
	//!< @return The new SourceMarker object, owned by the buffer.
	//!<
	//!< <BR>A marker is semantically very similar to a Gtk::TextMark, except it has a type
	//!< which is used by the SourceView displaying the buffer to show a pixmap on the left
	//!< margin, at the line the marker is in. Because of this, a marker is generally
	//!< associated to a line and not a character position. Markers are also accessible
	//!< through a position or range in the buffer.
	//!<
	//!< Markers are implemented using Gtk::TextMark, so all characteristics and restrictions
	//!< to marks apply to markers too. These includes life cycle issues and "mark-set" and
	//!< "mark-deleted" signal emissions. Like a Gtk::TextMark, a SourceMarker can be anonymous
	//!< if the passed name is null. Also, the buffer owns the markers so you shouldn't
	//!< unreference it.
	//!<
	//!< Markers always have left gravity and are moved to the beginning of the line when the
	//!< user deletes the line they were in. Also, if the user deletes a region of text which
	//!< contained lines with markers, those are deleted. Typical uses for a marker are bookmarks,
	//!< breakpoints, current executing instruction indication in a source file, etc..

	void move_marker(SourceMarker& marker, const TextIter& where);
	//!< Moves <EM>marker</EM> to the new location <EM>where</EM>.
	//!< @param marker A SourceMarker.
	//!< @param where The new location for <EM>marker</EM> in the buffer.

	void delete_marker(SourceMarker& marker);
	//!< Deletes <EM>marker</EM> from the source buffer.
	//!< @param marker A SourceMarker in the buffer.
	//!<
	//!< <BR>The same conditions as for Gtk::TextMark apply here. The marker is no longer
	//!< accessible from the buffer, but if you held a reference to it, it will not be
	//!< destroyed.

//! @}
//! @name Property Proxies
//! @{

	const EscapeCharPropertyProxy property_escape_char()
	{
		return EscapeCharPropertyProxy(this, &escape_char_property);
	}
	//!< The escape character for syntax delimiters (G::Unichar : Read / Write).

	const CheckBracketsPropertyProxy property_check_brackets()
	{
		return CheckBracketsPropertyProxy(this, &check_brackets_property);
	}
	//!< Whether to check and highlight matching brackets (bool : Read / Write).

	const HighlightPropertyProxy property_highlight()
	{
		return HighlightPropertyProxy(this, &highlight_property);
	}
	//!< Whether to syntax highlight the buffer (bool : Read / Write).

	const MaxUndoLevelsPropertyProxy property_max_undo_levels()
	{
		return MaxUndoLevelsPropertyProxy(this, &max_undo_levels_property);
	}
	//!< Sets the number of undo levels for the buffer (int : Read / Write).

	const LanguagePropertyProxy property_language()
	{
		return LanguagePropertyProxy(this, &language_property);
	}
	//!< The language object to get the highlighting rules from (SourceBuffer* : Read / Write).

//! @}
//! @name Signal Proxies
//! @{

	const CanUndoSignalProxy sig_can_undo()
	{
		return CanUndoSignalProxy(this, &can_undo_signal);
	}
	//!< Connect to the can_undo_signal; emitted whenever there is a change in the buffer's
	//!< ability to undo an operation.

	const CanRedoSignalProxy sig_can_redo()
	{
		return CanRedoSignalProxy(this, &can_redo_signal);
	}
	//!< Connect to the can_redo_signal; emitted whenever there is a change in the buffer's
	//!< ability to redo an operation.

	const HighlightUpdatedSignalProxy sig_highlight_updated()
	{
		return HighlightUpdatedSignalProxy(this, &highlight_updated_signal);
	}
	//!< Connect to the highlight_updated_signal; emitted whenever the syntax highlighting information
	//!< has been updated, so that views can request a redraw if the region changed is visible.

	const MarkerUpdatedSignalProxy sig_marker_updated()
	{
		return MarkerUpdatedSignalProxy(this, &marker_updated_signal);
	}
	//!< Connect to the marker_updated_signal; emitted when a source marker in the buffer is updated.

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_BUFFER_H

