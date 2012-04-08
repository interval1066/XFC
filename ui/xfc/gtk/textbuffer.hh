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
 
/// @file xfc/gtk/textbuffer.hh
/// @brief A GtkTextMark, GtkTextChildAnchor and GtkTextBuffer C++ wrapper interface.
///
/// Provides TextMark, an object used to preserve positions across text buffer modifications, 
/// TextChildAnchor, a spot in a TextBuffer where child widgets can be anchored, and TextBuffer,
/// a multiline text editing buffer that can be displayed in a TextView widget.

#ifndef XFC_GTK_TEXT_BUFFER_HH
#define XFC_GTK_TEXT_BUFFER_HH

#ifndef XFC_GTK_TEXT_ITER_HH
#include <xfc/gtk/textiter.hh>
#endif

#ifndef XFC_GTK_TEXT_TAG_HH
#include <xfc/gtk/texttag.hh>
#endif

#ifndef GTK_TEXT_BUFFER_H
#include <gtk/gtktextbuffer.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

class Clipboard;
class Widget;

/// @class TextMark textbuffer.hh xfc/gtk/textbuffer.hh
/// @brief A GtkTextMark C++ wrapper class.
///
/// A TextMark is like a bookmark in a text buffer; it preserves a position in the text across text buffer
/// modifications. You can convert the mark to an iterator using Gtk::TextBuffer::get_iter_at_mark(). Unlike
/// iterators, marks remain valid across buffer mutations, because their behavior is defined when text is 
/// inserted or deleted. When text containing a mark is deleted, the mark remains in the position originally
/// occupied by the deleted text. When text is inserted at a mark, a mark with left gravity will be moved to
/// the beginning of the newly-inserted text, and a mark with right gravity will be moved to the end.
///
/// Marks are reference counted, but the reference count only controls the validity of the memory; marks
/// can be deleted from the buffer at any time with Gtk::TextBuffer::delete_mark(). Once deleted from the
/// buffer, a mark is essentially useless. Marks optionally have names. There are two marks built-in to
/// TextBuffer; these are named "insert" and "selection_bound" and refer to the insertion point and the
/// boundary of the selection which is not the insertion point, respectively. If no text is selected,
/// these two marks will be in the same position. You can manipulate what is selected and where the 
/// cursor appears by moving these marks around. 
/// 
/// TextMarks can optionally have names. These names can be convenient to avoid passing the TextMark
/// object around. Marks are typically created using the Gtk::TextBuffer::create_mark() method.

class TextMark : public G::Object
{
	friend class G::Object;

	TextMark(const TextMark&);
	TextMark& operator=(const TextMark&);
	
protected:
/// @name Constructors
/// @{

	explicit TextMark(GtkTextMark *mark, bool owns_reference = true);
	///< Construct a new TextMark from an existing GtkTextMark.
	///< @param mark A pointer to a GtkTextMark.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>mark</EM> can be a newly created GtkTextMark or an existing
	///< GtkTextMark (see G::Object::Object).

/// @}
	
public:
	typedef GtkTextMark CObjectType;

/// @name Constructors
/// @{

	virtual ~TextMark();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTextMark* gtk_text_mark() const;
	///< Get a pointer to the GtkTextMark structure.

	operator GtkTextMark* () const;
	///< Conversion operator; safely converts a TextMark to a GtkTextMark pointer.

	bool get_visible() const;
	///< Returns true if the mark is visible (that is, a cursor is displayed for it).

	String get_name() const;
	///< Returns the mark name; or a null String for anonymous marks.

	bool get_deleted() const;
	///< Returns true if the mark has been removed from its buffer with delete_mark().
	///< Marks can't be used once deleted.
	
	TextBuffer* get_buffer() const;
	///< Gets the buffer this mark is located inside, or null if the mark is deleted.

	bool get_left_gravity() const;
	///< Determines whether the mark has left gravity.
	
/// @}
/// @name Methods
/// @{

	void set_visible(bool setting);
	///< Sets the visibility of mark; the insertion point is normally visible, that is,
	///< you can see it as a vertical bar. 
	///< @param setting The visibility of mark.
	///<
	///< The text widget uses a visible mark to indicate where a drop will occur
	///< when dragging and dropping text. Most other marks are not visible. Marks are
	///< not visible by default.

/// @}
};

/// @class TextChildAnchor textbuffer.hh xfc/gtk/textbuffer.hh
/// @brief A GtkTextChildAnchor C++ wrapper class.
///
/// A TextChildAnchor is a spot in a TextBuffer where child widgets can be <EM>anchored</EM>,
/// inserted inline, as if they were characters. The anchor can have multiple widgets anchored,
/// to allow for multiple views.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TextChildAnchor : public G::Object
{
	friend class G::Object;

	TextChildAnchor(const TextChildAnchor&);
	TextChildAnchor& operator=(const TextChildAnchor&);

protected:
/// @name Constructors
/// @{

	explicit TextChildAnchor(GtkTextChildAnchor *anchor, bool owns_reference = true);
	///< Construct a new TextChildAnchor from an existing GtkTextChildAnchor.
	///< @param anchor A pointer to a GtkTextChildAnchor.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>anchor</EM> can be a newly created GtkTextChildAnchor or an existing
	///< GtkTextChildAnchor (see G::Object::Object).

/// @}

public:
	typedef GtkTextChildAnchor CObjectType;

/// @name Constructors
/// @{

	TextChildAnchor();
	///< Constructs a new anchor with a reference count of 1 that the caller owns.
	///< Usually you would insert it into a TextBuffer with Gtk::TextBuffer::insert_child_anchor().
	///< To perform the creation and insertion in one step, use the convenience method 
	///< Gtk::TextBuffer::create_child_anchor().
	
	virtual ~TextChildAnchor();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTextChildAnchor* gtk_text_child_anchor() const;
	///< Get a pointer to the GtkTextChildAnchor structure.

	operator GtkTextChildAnchor* () const;
	///< Conversion operator; safely converts a TextChildAnchor to a GtkTextChildAnchor pointer.

	bool get_widgets(std::vector<Widget*>& widgets) const;
	///< Gets a list of all widgets anchored at this child anchor.
	///< @param widgets A reference to a vector of Widget* to hold the list of widgets.
	///< @return <EM>true</EM> if the vector contains any widgets.

	bool get_deleted() const;
	///< Determines whether a child anchor has been deleted from the buffer. 
	///< @return <EM>true</EM> if the child anchor has been deleted from its buffer.
	///<
	///< Keep in mind that the child anchor will be unreferenced when removed from the buffer,
	///< so you need to hold your own reference (with ref()) if you plan to use this method - 
	///< otherwise all deleted child anchors will also be finalized.

/// @}
};

/// @class TextBuffer textbuffer.hh xfc/gtk/textbuffer.hh
/// @brief A GtkTextBuffer C++ wrapper class.
///
/// GTK+ has an extremely powerful framework for multiline text editing. The primary objects involved
/// in the process are TextBuffer, which represents the text being edited, and TextView, a widget
/// which can display a TextBuffer. Each buffer can be displayed by any number of views. One of the
/// important things to remember about text in GTK+ is that it's in the UTF-8 encoding. This means that
/// one character can be encoded as multiple bytes. Character counts are usually referred to as offsets,
/// while byte counts are called indexes. If you confuse these two, things will work fine with ASCII,
/// but as soon as your buffer contains multibyte characters, bad things will happen.
///
/// Text in a buffer can be marked with tags. A tag is an attribute that can be applied to some range
/// of text. For example, a tag might be called "bold" and make the text inside the tag bold. Each tag
/// is stored in a TextTagTable. A tag table defines a set of tags that can be used together. Each 
/// buffer has one tag table associated with it; only tags from that tag table can be used with the
/// buffer. A single tag table can be shared between multiple buffers, however. Tags can have names,
/// which is convenient sometimes (for example, you can name your tag that makes things bold "bold"),
/// but they can also be anonymous (which is convenient if you're creating tags on-the-fly).
///
/// Most text manipulation is accomplished with iterators, represented by a TextIter. An iterator 
/// represents a position between two characters in the text buffer. Because of this, iterators 
/// can't be used to preserve positions across buffer modifications. To preserve a position, the
/// TextMark object is ideal. You can think of a mark as an invisible cursor or insertion point;
/// it floats in the buffer, saving a position. Like tags, marks can be either named or anonymous.
///
/// Text buffers always contain at least one line, but may be empty (that is, buffers can contain
/// zero characters). The last line in the text buffer never ends in a line separator (such as
/// newline); the other lines in the buffer always end in a line separator. Line separators count
/// as characters when computing character counts and character offsets. Note that some Unicode
/// line separators are represented with multiple bytes in UTF-8, and the two-character sequence
/// "\\r\\n" is also considered a line separator.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/textview.html">TextView Widget</A> HOWTO and example.

class TextBuffer : public G::Object
{
	friend class G::Object;

	TextBuffer(const TextBuffer&);
	TextBuffer& operator=(const TextBuffer&);
	
protected:
/// @name Constructors
/// @{

	explicit TextBuffer(GtkTextBuffer *buffer, bool owns_reference = true);
	///< Construct a new TextBuffer from an existing GtkTextBuffer.
	///< @param buffer A pointer to a GtkTextBuffer.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>buffer</EM> can be a newly created GtkTextBuffer or an existing
	///< GtkTextBuffer (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, TextIter&, const String&> InsertTextSignalType;
	typedef G::SignalProxy<TypeInstance, InsertTextSignalType> InsertTextSignalProxy;
	static const InsertTextSignalType insert_text_signal;
	///< Insert text signal (see signal_insert_text()). Calls a slot with the signature:
	///< @code
	///< void function(TextIter& pos, const String& text);
	///< // pos: A position in the buffer.
	///< // text: The text to insert.
	///< @endcode

	typedef G::Signal<void, TextIter&, Gdk::Pixbuf&> InsertPixbufSignalType;
	typedef G::SignalProxy<TypeInstance, InsertPixbufSignalType> InsertPixbufSignalProxy;
	static const InsertPixbufSignalType insert_pixbuf_signal;
	///< Insert pixbuf signal (see signal_insert_pixbuf()). Calls a slot with the signature:
	///< @code
	///< void function(TextIter& pos, Gdk::Pixbuf& pixbuf);
	///< // pos: The location to insert the pixbuf.
	///< // pixbuf: A Gdk::Pixbuf.
	///< @endcode

	typedef G::Signal<void, TextIter&, TextChildAnchor&> InsertChildAnchorSignalType;
	typedef G::SignalProxy<TypeInstance, InsertChildAnchorSignalType> InsertChildAnchorSignalProxy;
	static const InsertChildAnchorSignalType insert_child_anchor_signal;
	///< Insert child anchor signal (see signal_insert_child_anchor()). Calls a slot with the signature:
	///< @code
	///< void function(TextIter& pos, TextChildAnchor& anchor);
	///< // pos: The location to insert the anchor.
	///< // anchor: A TextChildAnchor.
	///< @endcode

	typedef G::Signal<void, TextIter&, TextIter&> DeleteRangeSignalType;
	typedef G::SignalProxy<TypeInstance, DeleteRangeSignalType> DeleteRangeSignalProxy;
	static const DeleteRangeSignalType delete_range_signal;
	///< Delete range signal (see signal_delete_range()). Calls a slot with the signature:
	///< @code
	///< void function(TextIter& start, TextIter& end);
	///< // start: A position in the buffer.
	///< // end: Another position in the buffer.
	///< @endcode

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ModifiedChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ModifiedChangedSignalType> ModifiedChangedSignalProxy;
	static const ModifiedChangedSignalType modified_changed_signal;
	///< Modified changed signal (see signal_modified_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, const TextIter&, TextMark&> MarkSetSignalType;
	typedef G::SignalProxy<TypeInstance, MarkSetSignalType> MarkSetSignalProxy;
	static const MarkSetSignalType mark_set_signal;
	///< Mark set signal (see signal_mark_set()). Calls a slot with the signature:
	///< @code
	///< void function(const TextIter& location, TextMark& mark);
	///< // location: The location for mark in the buffer.
	///< // mark: A TextMark.
	///< @endcode

	typedef G::Signal<void, TextMark&> MarkDeletedSignalType;
	typedef G::SignalProxy<TypeInstance, MarkDeletedSignalType> MarkDeletedSignalProxy;
	static const MarkDeletedSignalType mark_deleted_signal;
	///< Mark deleted signal (see signal_mark_deleted()). Calls a slot with the signature:
	///< @code
	///< void function(TextMark& mark);
	///< // mark: A TextMark.
	///< @endcode

	typedef G::Signal<void, TextTag&, const TextIter&, const TextIter&> ApplyTagSignalType;
	typedef G::SignalProxy<TypeInstance, ApplyTagSignalType> ApplyTagSignalProxy;
	static const ApplyTagSignalType apply_tag_signal;
	///< Apply tag signal (see signal_apply_tag()). Calls a slot with the signature:
	///< @code
	///< void function(TextTag& tag, const TextIter& start_char, const TextIter& end_char);
	///< // tag: A TextTag.
	///< // start_char: One bound of a range to be tagged.
	///< // end_char: The other bound of a range to be tagged.
	///< @endcode

	typedef G::Signal<void, TextTag&, const TextIter&, const TextIter&> RemoveTagSignalType;
	typedef G::SignalProxy<TypeInstance, RemoveTagSignalType> RemoveTagSignalProxy;
	static const RemoveTagSignalType remove_tag_signal;
	///< Remove tag signal (see signal_remove_tag()). Calls a slot with the signature:
	///< @code
	///< void function(TextTag& tag, const TextIter& start_char, const TextIter& end_char);
	///< // tag: A TextTag.
	///< // start_char: One bound of a range to be untagged.
	///< // end_char: The other bound of a range to be untagged.
	///< @endcode

	typedef G::Signal<void> BeginUserActionSignalType;
	typedef G::SignalProxy<TypeInstance, BeginUserActionSignalType> BeginUserActionSignalProxy;
	static const BeginUserActionSignalType begin_user_action_signal;
	///< Begin user action signal (see signal_begin_user_action()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> EndUserActionSignalType;
	typedef G::SignalProxy<TypeInstance, EndUserActionSignalType> EndUserActionSignalProxy;
	static const EndUserActionSignalType end_user_action_signal;
	///< End user action signal (see signal_end_user_action()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Constructors
/// @{
	
	explicit TextBuffer(TextTagTable *table = 0);
	///< Constructs a new text buffer with a reference count of 1 that the caller owns.
	///< @param table A tag table, or null to have the text buffer create one for you.
	
	virtual ~TextBuffer();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	GtkTextBuffer* gtk_text_buffer() const;
	///< Get a pointer to the GtkTextBuffer structure.

	operator GtkTextBuffer* () const;
	///< Conversion operator; safely converts a TextBuffer to a GtkTextBuffer pointer.

	int get_line_count() const;
	///< Obtains the number of lines in the buffer.
	///< @return The number of lines in the buffer.
	///<
	///< This value is cached, so the function is very fast.

	int get_char_count() const;
	///< Gets the number of characters in the buffer.
	///< @return The number of characters in the buffer.
	///<
	///< Note that characters and bytes are not the same, you can't for example expect
	///< the contents of the buffer in string form to be this many bytes long. The character
	///< count is cached, so this method is very fast.
	
	TextTagTable* get_tag_table() const;
	///< Get the TextTagTable associated with this buffer.
	///< @return The buffer's tag table.

	String get_text(const TextIter& start, const TextIter& end, bool include_hidden_chars = false) const;
	///< Returns the text in the range (start,end).
	///< @param start The start of a range.
	///< @param end The end of a range.
	///< @param include_hidden_chars Whether to include invisible text.
	///< @return The text string.
	///<
	///< Undisplayed text is excluded (text marked with tags that set the invisibility attribute)
	///< if <EM>include_hidden_chars</EM> is false. Does not include characters representing embedded
	///< images, so byte and character indexes into the returned string do not correspond to byte and
	///< character indexes into the buffer. Contrast with get_slice().

	String get_slice(const TextIter& start, const TextIter& end, bool include_hidden_chars = false) const;
	///< Returns the text in the range (start,end).
	///< @param start The start of a range.
	///< @param end The end of a range.
	///< @param include_hidden_chars Whether to include invisible text.
	///< @return A text string.
	///<
	///< Excludes undisplayed text (text marked with tags that set the invisibility attribute)
	///< if <EM>include_hidden_chars</EM> is false. The returned string includes a 0xFFFC character
	///< whenever the buffer contains embedded images, so byte and character indexes into the returned
	///< string do correspond to byte and character indexes into the buffer. Contrast with get_text().
	///< Note that 0xFFFC can occur in normal text as well, so it is not a reliable indicator that a
	///< pixbuf or widget is in the buffer.

	TextMark* get_mark(const char *name) const;
	TextMark* get_mark(const String& name) const;
	///< Returns the mark named <EM>name</EM> in the buffer, or null if no such mark exists.
	///< @param name A mark name.
	///< @return A TextMark, or null.

	TextMark* get_insert() const;
	///< Returns the mark that represents the cursor (insertion point). 
	///< @return The insertion point mark.
	///<
	///< Equivalent to calling get_mark() to get the mark named "insert", but slightly
	///< more efficient, and involves less typing.

	TextMark* get_selection_bound() const;
	///< Returns the mark that represents the selection bound. 
	///< @return The selection bound mark.
	///<
	///< Equivalent to calling get_mark() to get the mark named "selection_bound", but slightly
	///< more efficient, and involves less typing. The currently selected text in buffer is the 
	///< region between the "selection_bound" and "insert" marks. If "selection_bound" and "insert"
	///< are in the same place, then there is no current selection. get_selection_bounds() is another
	///< convenient method for handling the selection, if you just want to know whether there's a
	///< selection and what its bounds are.
	
	TextIter get_iter_at_line_offset(int line_number, int char_offset) const;
	///< Obtains an initialized iterator pointing to <EM>char_offset</EM> within the given line.
	///< @param line_number The line number counting from 0.
	///< @param char_offset The char offset from start of line.
	///< @return The initialized iterator.
	///<
	///< The <EM>char_offset</EM> must exist, offsets off the end of the line are not allowed.
	///< Note characters, not bytes; UTF-8 may encode one character as multiple bytes.

	TextIter get_iter_at_line_index(int line_number, int byte_index) const;
	///< Obtains an initialized iterator pointing to <EM>byte_index</EM> within the given line.
	///< @param line_number The line number counting from 0.
	///< @param byte_index The byte index from start of the line.
	///< @return The initialized iterator.
	///<
	///< The <EM>byte_index</EM> must be the start of a UTF-8 character, and must not be
	///< beyond the end of the line. Note bytes, not characters; UTF-8 may encode one character
	///< as multiple bytes.

	TextIter get_iter_at_offset(int char_offset) const;
	///< Obtains an gfcalized iterater to a position <EM>char_offset</EM> chars from the start
	///< of the entire buffer.
	///< @param char_offset The character offset from start of buffer, counting from 0, or -1.
	///< @return The initialized iterator.
	///<
	///< If <EM>char_offset</EM> is -1 or greater than the number of characters in the buffer,
	///< the iterator is initialized to the end iterator, the iterator one past the last valid
	///< character in the buffer.

	TextIter get_iter_at_line(int line_number) const;
	///< Obtains an initialized iterator to the start of the given line.
	///< @param line_number The line number counting from 0.
	///< @return The initialized iterator.

	TextIter get_start_iter() const;
	///< Obtains an initialized iterator to the first position in the text buffer.
	///< @return The initialized <EM>start</EM> iterator.
	///<
	///< This is the same as using get_iter_at_offset() to get the iter at character offset 0.
	
	TextIter get_end_iter() const;
	///< Obtains an initialzied iterator to one past the last valid character in the text buffer.
	///< @return The initialized <EM>end</EM> iterator.
	///<
	///< If dereferenced with Gtk::TextIter::get_char(), the end iterator has a character value of
	///< 0. The entire buffer lies in the range from the first position (call get_start_iter() to get
	///< character position 0 in the buffer) to the end iterator.
	
	void get_bounds(TextIter& start, TextIter& end) const;
	///< Retrieves the first and last iterators in the buffer, that is the entire buffer lies within
	///< the range (start,end).
	///< @param start The iterator to initialize to first position in the buffer.
	///< @param end The iterator to initialize with the end iterator.

	TextIter get_iter_at_mark(TextMark& mark) const;
	///< Obtains an initialized iterator to the current position of mark.
	///< @param mark A TextMark in the buffer.
	///< @return The initialized iterator.

	TextIter get_iter_at_child_anchor(TextChildAnchor& anchor) const;
	///< Obtains an initialized iterator to the location of anchor within the buffer.
	///< @param anchor A child anchor that appears in the buffer.
	///< @return The initialized iterator.

	bool get_modified() const;
	///< Indicates whether the buffer has been modified since the last call to set_modified()
	///< to set the modification flag to false.
	///< @return <EM>true</EM> if the buffer has been modified.
	///<
	///< Used for example to enable a "save" function in a text editor.

	bool get_selection_bounds(TextIter *start = 0, TextIter *end = 0) const;
	///< Returns true if some text is selected; places the bounds of the selection in
	///< <EM>start</EM> and <EM>end</EM>.
	///< @param start The iterator to initialize with selection start.
	///< @param end The iterator to initialize with selection end.
	///< @return Whether the selection has nonzero length.
	///<
	///< If the selection has length 0, then start and end are filled in with the same value.
	///< start and end will be in ascending order. If start and end are null, then they are not
	///< filled in, but the return value still indicates whether any text is selected.

/// @}
/// @name Methods
/// @{

	void begin_user_action();
	///< Called to indicate that the buffer operations between here and a call to
	///< buffer_end_user_action() are part of a single user-visible operation. The
	///< operations between begin_user_action() and end_user_action() can then be
	///< grouped when creating an undo stack. TextBuffer maintains a count of calls
	///< to begin_user_action() that have not been closed with a call to 
	///< end_user_action(), and emits the "begin_user_action" and "end_user_action"
	///< signals only for the outermost pair of calls. This allows you to build user
	///< actions from other user actions.
	///<
	///< The "interactive" buffer mutation methods, such as insert_interactive(), 
	///< automatically call begin/end user action around the buffer operations they
	///< perform, so there's no need to add extra calls if your user action consists
	///< solely of a single call to one of those methods.

	void end_user_action();
	///< Should be paired with a call to begin_user_action() (see that method for a full explanation).

	void set_text(const char *text, int length = -1);
	///< Deletes current contents of buffer, and inserts <EM>text</EM> instead.
	///< @param text The UTF-8 text to insert.
	///< @param length The length of text in bytes, or -1 if <EM>text</EM> is null-terminated.

	void set_text(const String& text);
	///< Deletes current contents of buffer, and inserts <EM>text</EM> instead.
	///< @param text The text to insert.

	void insert(TextIter& iter, const char *text, int length = -1);
	///< Inserts <EM>length</EM> bytes of text at position iter.
	///< @param iter A position in the buffer.
	///< @param text The UTF-8 format text to insert.
	///< @param length The length of text in bytes, or -1.
	///<
	///< If <EM>length</EM> is -1, <EM>text</EM> must be null-terminated and will be
	///< inserted in its entirety. This method emits the "insert_text" signal; insertion
	///< actually occurs in the default handler for the signal. The iter is invalidated
	///< when insertion occurs (because the buffer contents change), but the default 
	///< signal handler revalidates it to point to the end of the inserted text.

	void insert(TextIter& iter, const String& text);
	///< Inserts text at position iter.
	///< @param iter A position in the buffer.
	///< @param text The text to insert.
	///<
	///< Emits the "insert_text" signal; insertion actually occurs in the default handler
	///< for the signal. The iter is invalidated when insertion occurs (because the buffer
	///< contents change), but the default signal handler revalidates it to point to the end
	///< of the inserted text.

	void insert_at_cursor(const char *text, int length = -1);
	///< Simply calls insert(), using the current cursor position as the insertion point.
	///< @param text Some text in UTF-8 format.
	///< @param length The length of <EM>text</EM>, in bytes.

	void insert_at_cursor(const String& text);
	///< Simply calls insert(), using the current cursor position as the insertion point.
	///< @param text Some text to insert.

	bool insert_interactive(TextIter& iter, const char *text, int length, bool default_editable);
	///< Like insert(), but the insertion will not occur if iter is at a non-editable
	///< location in the buffer.
	///< @param iter A position in the buffer.
	///< @param text Some UTF-8 text.
	///< @param length The length of <EM>text</EM> in bytes, or -1.
	///< @param default_editable The default editability of the buffer.
	///< @return Whether <EM>text</EM> was actually inserted.
	///<
	///< Usually you want to prevent insertions at ineditable locations if the insertion
	///< results from a user action (is interactive). <EM>default_editable</EM> indicates the
	///< editability of text that doesn't have a tag affecting editability applied to it.
	///< Typically the result of Gtk::TextView::get_editable() is appropriate here.

	bool insert_interactive(TextIter& iter, const String& text, bool default_editable);
	///< Like insert(), but the insertion will not occur if iter is at a non-editable
	///< location in the buffer.
	///< @param iter A position in the buffer.
	///< @param text Some text.
	///< @param default_editable The default editability of the buffer.
	///< @return Whether <EM>text</EM> was actually inserted.
	///<
	///< Usually you want to prevent insertions at ineditable locations if the insertion
	///< results from a user action (is interactive). <EM>default_editable</EM> indicates the
	///< editability of text that doesn't have a tag affecting editability applied to it.
	///< Typically the result of Gtk::TextView::get_editable() is appropriate here.

	bool insert_interactive_at_cursor(const char *text, int length, bool default_editable);
	///< Calls insert_interactive() to insert <EM>text</EM> at the cursor position.
	///< @param text The text in UTF-8 format.
	///< @param length The length of <EM>text</EM> in bytes, or -1.
	///< @param default_editable The default editability of the buffer.
	///< @return Whether the text was actually inserted.
	///<
	///< <EM>default_editable</EM> indicates the editability of text that doesn't
	///< have a tag affecting editability applied to it. Typically the result of
	///< Gtk::TextView::get_editable() is appropriate here.

	bool insert_interactive_at_cursor(const String& text, bool default_editable);
	///< Calls insert_interactive() to insert <EM>text</EM> at the cursor position.
	///< @param text The text to insert.
	///< @param default_editable The default editability of the buffer.
	///< @return Whether the text was actually inserted.
	///<
	///< <EM>default_editable</EM> indicates the editability of text that doesn't
	///< have a tag affecting editability applied to it. Typically the result of
	///< Gtk::TextView::get_editable() is appropriate here.

	void insert_range(TextIter& iter, const TextIter& start, const TextIter& end);
	///< Copies text, tags, and pixbufs between start and end (the order of start and end
	///< doesn't matter) and inserts the copy at iter.
	///< @param iter A position in the buffer.
	///< @param start A position in a TextBuffer.
	///< @param end Another position in the same buffer as start.
	///<
	///< Used instead of simply getting/inserting text because it preserves images and tags.
	///< If start and end are in a different buffer from buffer, the two buffers must share the
	///< same tag table. Implemented via emissions of the <EM>insert_text</EM> and <EM>apply_tag</EM>
	///< signals, so expect those.

	bool insert_range_interactive(TextIter& iter, const TextIter& start, const TextIter& end, bool default_editable);
	///< Same as insert_range(), but does nothing if the insertion point isn't editable.
	///< @param iter A position in the buffer.
	///< @param start A position in a TextBuffer
	///< @param end Another position in the same buffer as start.
	///< @param default_editable The default editability of the buffer.
	///< @return Whether an insertion was possible at iter.
	///<
	///< The <EM>default_editable</EM> parameter indicates whether the text is editable
	///< at iter if no tags enclosing iter affect editability. Typically the result of
	///< Gtk::TextView::get_editable() is appropriate here.

	void insert_with_tag(TextIter& iter, const char *text, int length, TextTag& tag);
	///< Inserts <EM>text</EM> into the buffer at <EM>iter</EM>, applying the tag to the newly-inserted text.
	///< @param iter An iterator in the buffer.
	///< @param text The UTF-8 text to insert.
	///< @param length The length of <EM>text</EM>, or -1.
	///< @param tag The tag to apply to <EM>text</EM>.
	///<
	///< This method is a convenience function. It is equivalent to calling insert()
	///< and then apply_tag() on the inserted text.

	void insert_with_tag(TextIter& iter, const String& text, TextTag& tag);
	///< Inserts <EM>text</EM> into the buffer at <EM>iter</EM>, applying the tag to the newly-inserted text.
	///< @param iter An iterator in the buffer.
	///< @param text The text to insert.
	///< @param tag The tag to apply to <EM>text</EM>.
	///<
	///< This method is a convenience function. It is equivalent to calling insert()
	///< and then apply_tag() on the inserted text.

	void insert_with_tags(TextIter& iter, const char *text, int length, const std::vector<TextTag*>& tags);
	///< Inserts text into the buffer at iter, applying the list of tags to the newly-inserted text.
	///< @param iter An iterator in the buffer.
	///< @param text The UTF-8 text.
	///< @param length The length of text, or -1.
	///< @param tags A vector of text tags to apply to <EM>text</EM>.
	///<
	///< This is a convenience method and is equivalent to calling insert(), 
	///< and then apply_tag() on the inserted text.

	void insert_with_tags(TextIter& iter, const String& text, const std::vector<TextTag*>& tags);
	///< Inserts text into the buffer at iter, applying the list of tags to the newly-inserted text.
	///< @param iter An iterator in the buffer.
	///< @param text The text to insert.
	///< @param tags A vector of text tags to apply to <EM>text</EM>.
	///<
	///< This is a convenience method and is equivalent to calling insert(), 
	///< and then apply_tag() on the inserted text.
	
	void insert_with_tag_by_name(TextIter& iter, const char *text, int length, const char *tag_name);
	///< Same as insert_with_tag(), but allows you to pass in the tag name instead of a tag object.
	///< @param iter A position in the buffer.
	///< @param text The UTF-8 text.
	///< @param length The length of text, or -1.
	///< @param tag_name The name of the tag to apply to <EM>text</EM>.

	void insert_with_tag_by_name(TextIter& iter, const String& text, const char *tag_name);
	///< Same as insert_with_tag(), but allows you to pass in the tag name instead of a tag object.
	///< @param iter A position in the buffer.
	///< @param text The text to insert.
	///< @param tag_name The name of the tag to apply to <EM>text</EM>.

	void insert_with_tags_by_name(TextIter& iter, const char *text, int length, const std::vector<String>& tag_names);
	///< Same as insert_with_tags(), but allows you to pass in tag names instead of tag objects.
	///< @param iter A position in the buffer.
	///< @param text The UTF-8 text.
	///< @param length The length of text, or -1.
	///< @param tag_names A vector of text tag names to apply to <EM>text</EM>.

	void insert_with_tags_by_name(TextIter& iter, const String& text, const std::vector<String>& tag_names);
	///< Same as insert_with_tags(), but allows you to pass in tag names instead of tag objects.
	///< @param iter A position in the buffer.
	///< @param text The text to insert.
	///< @param tag_names A vector of text tag names to apply to <EM>text</EM>.

	void delete_range(TextIter& start, TextIter& end);
	///< Deletes text between start and end.
	///< @param start A position in the buffer.
	///< @param end Another position in the buffer.
	///<
	///< The order of start and end is not actually relevant; delete_range() will reorder them.
	///< This method actually emits the "delete_range" signal, and the default handler of that
	///< signal deletes the text. Because the buffer is modified, all outstanding iterators become
	///< invalid after calling this method; however, the start and end will be re-initialized to
	///< point to the location where text was deleted.

	bool delete_range_interactive(TextIter& start, TextIter& end, bool default_editable);
	///< Deletes all editable text in the given range.
	///< @param start The start of range to delete.
	///< @param end The end of range.
	///< @param default_editable Whether the buffer is editable by default.
	///< @return Whether some text was actually deleted.
	///<
	///< Calls delete_range() for each editable sub-range of (start,end). <EM>start</EM>
	///< and <EM>end</EM> are revalidated to point to the location of the last deleted range,
	///< or left untouched if no text was deleted.

	void insert_pixbuf(TextIter& iter, Gdk::Pixbuf& pixbuf);
	///< Inserts an image into the text buffer at iter.
	///< @param iter The location to insert the pixbuf.
	///< @param pixbuf A Gdk::Pixbuf.
	///<
	///< The image will be counted as one character in character counts, and when obtaining
	///< the buffer contents as a string, will be represented by the Unicode "object replacement
	///< character" 0xFFFC. Note that the "slice" variants for obtaining portions of the buffer
	///< as a string include this character for pixbufs, but the "text" variants do not. e.g.
	///< see get_slice() and get_text().

	void insert_child_anchor(TextIter& iter, TextChildAnchor& anchor);
	///< Inserts a child widget anchor into the text buffer at iter. 
	///< @param iter The location to insert the anchor.
	///< @param anchor A TextChildAnchor.
	///<
	///< The anchor will be counted as one character in character counts, and when obtaining
	///< the buffer contents as a string, will be represented by the Unicode "object replacement
	///< character" 0xFFFC. Note that the "slice" variants for obtaining portions of the buffer 
	///< as a string include this character for child anchors, but the "text" variants do not.
	///< For example, see get_slice() and get_text(). Consider create_child_anchor() as a more
	///< convenient alternative to this method. The buffer will add a reference to the anchor,
	///< so you can unref it after insertion.

	TextChildAnchor* create_child_anchor(TextIter& iter);
	///< This is a convenience method which simply creates a child anchor and inserts it into
	///< the buffer with insert_child_anchor().
	///< @param iter The location in the buffer.
	///< @return The created child anchor.
	///< 
	///< The new anchor is owned by the buffer; no reference count is returned to the caller
	///< of create_child_anchor().

	TextMark* create_mark(const char *mark_name, const TextIter& where, bool left_gravity);
	TextMark* create_mark(const String& mark_name, const TextIter& where, bool left_gravity);
	///< Creates a mark at position where.
	///< @param mark_name The name for the mark, or null.
	///< @param where The location to place the new mark.
	///< @param left_gravity Whether the mark has left gravity.
	///< @return The new TextMark object.
	///<
	///< If mark_name is null, the mark is anonymous; otherwise, the mark can be retrieved by
	///< name using get_mark(). If a mark has left gravity, and text is inserted at the mark's
	///< current location, the mark will be moved to the left of the newly-inserted text. If
	///< the mark has right gravity (left_gravity = false), the mark will end up on the right
	///< of newly-inserted text. The standard left-to-right cursor is a mark with right gravity
	///< (when you type, the cursor stays on the right side of the text you're typing). The 
	///< caller of this method does not own a reference to the returned TextMark, so you can
	///< ignore the return value if you like. Marks are owned by the buffer and go away when 
	///< the buffer does. Emits the "mark_set" signal as notification of the mark's initial
	///< placement.

	void move_mark(TextMark& mark, const TextIter& where);
	///< Moves <EM>mark</EM> to the new location <EM>where</EM>. 
	///< @param mark A TextMark.
	///< @param where The new location for <EM>mark</EM> in the buffer.
	///<
	///< Emits the <EM>mark_set</EM> signal as notification of the move.

	void move_mark_by_name(const char *name, const TextIter& where);
	void move_mark_by_name(const String& name, const TextIter& where);
	///< Moves the mark named <EM>name</EM> (which must exist) to location <EM>where</EM>
	///< (see move_mark() for details).
	///< @param name The name of a mark.
	///< @param where The new location for <EM>mark</EM>.

	void delete_mark(TextMark& mark);
	///< Deletes <EM>mark</EM>, so that it's no longer located anywhere in the buffer. 
	///< @param mark A TextMark in the buffer.
	///<
	///< Removes the reference the buffer holds to the mark, so if you haven't called
	///< ref() on the mark, it will be freed. Even if the mark isn't freed, most operations
	///< on mark become invalid. There is no way to undelete a mark. Gtk::TextMark::get_deleted()
	///< will return true after this method has been called on a mark, indicating that a mark
	///< no longer belongs to a buffer. The "mark_deleted" signal will be emitted as notification
	///< after the mark is deleted.

	void delete_mark_by_name(const char *name);
	void delete_mark_by_name(const String& name);
	///< Deletes the mark named name; the mark must exist (see delete_mark() for details).
	///< @param name The name of a mark in the buffer.

	void place_cursor(const TextIter& where);
	///< This method moves the "insert" and "selection_bound" marks simultaneously. 
	///< @param where The where to put the cursor.
	///<
	///< If you move them to the same place in two steps with move_mark(), you will temporarily
	///< select a region in between their old and new locations, which can be pretty inefficient
	///< since the temporarily selected region will force stuff to be recalculated. This method
	///< moves them as a unit, which can be optimized.

	void select_range(const TextIter& insert, const TextIter& bound);
	///< Move the "insert" and "selection_bound" marks simultaneously.
	///< @param insert Where to put the "insert" mark.
	///< @param bound Where to put the "selection_bound" mark
	///<
	///< If you move <EM>insert</EM> and <EM>bound</EM> in two steps with move_mark(),
	///< you will temporarily select a region in between their old and new locations, which
	///< can be pretty inefficient since the temporarily-selected region will force stuff
	///< to be recalculated. This function moves them as a unit, which can be optimized.

	void apply_tag(TextTag& tag, const TextIter& start, const TextIter& end);
	///< Emits the "apply_tag" signal on the buffer.
	///< @param tag A TextTag.
	///< @param start One bound of a range to be tagged.
	///< @param end The other bound of a range to be tagged.
	///<
	///< The default handler for the signal applies tag to the given range. The <EM>start</EM>
	///< and <EM>end</EM> do not have to be in order.

	void apply_tag_by_name(const char *name, const TextIter& start, const TextIter& end);
	void apply_tag_by_name(const String& name, const TextIter& start, const TextIter& end);
	///< Calls Gtk::TextTagTable::lookup() on the buffer's tag table to get a TextTag,
	///< then calls apply_tag().
	///< @param name The name of a named TextTag.
	///< @param start One bound of a range to be tagged.
	///< @param end The other bound of a range to be tagged.

	void remove_tag(TextTag& tag, const TextIter& start, const TextIter& end);
	///< Emits the "remove_tag" signal. 
	///< @param tag A TextTag.
	///< @param start One bound of a range to be untagged.
	///< @param end The other bound of a range to be untagged.
	///<
	///< The default handler for the signal removes all occurrences of tag from the given range.
	///< The <EM>start</EM> and <EM>end</EM> don't have to be in order.

	void remove_tag_by_name(const char *name, const TextIter& start, const TextIter& end);
	void remove_tag_by_name(const String& name, const TextIter& start, const TextIter& end);
	///< Calls Gtk::TextTagTable::lookup() on the buffer's tag table to get a TextTag,
	///< then calls remove_tag().
	///< @param name The name of a named TextTag.
	///< @param start One bound of a range to be untagged.
	///< @param end The other bound of a range to be untagged.

	void remove_all_tags(const TextIter& start, const TextIter& end);
	///< Removes all tags in the range between <EM>start</EM> and <EM>end</EM>. 
	///< @param start One bound of a range to be untagged.
	///< @param end The other bound of a range to be untagged.
	///<
	///< Be careful with this method; it could remove tags added in code unrelated to the code
	///< you're currently writing. That is, using this method is probably a bad idea if you have
	///< two or more unrelated code sections that add tags.

	TextTag* create_tag();
	///< Creates an anonymous tag.
	///< @return A new anonymous tag.
	///<	
	///< Equivalent to creating a new TextTag and then adding the tag to the buffer's tag table.
	///< The returned tag is owned by the buffer's tag table, so the reference count will be equal
	///< to one. 
	
	TextTag* create_tag(const char *tag_name);
	TextTag* create_tag(const String& tag_name);
	///< Creates a tag and adds it to the tag table for the buffer.
	///< @param tag_name The name of the new tag.
	///< @return A new tag.
	///<
	///< Equivalent to creating a new TextTag and then adding the tag to the buffer's tag table.
	///< The returned tag is owned by the buffer's tag table, so the reference count will be equal
	///< to one. If <EM>tag_name</EM> is a null String, the tag is anonymous. If <EM>tag_name</EM>
	///< is non-null, a tag called <EM>tag_name</EM> must not already exist in the tag table for 
	///< this buffer. 
	
	void set_modified(bool setting);
	///< Used to keep track of whether the buffer has been modified since the last time it was saved.
	///< @param setting The modification flag setting.
	///<
	///< Whenever the buffer is saved to disk, call set_modified(false). When the buffer is 
	///< modified, it will automatically toggled on the modified bit again. When the modified 
	///< bit flips, the buffer emits a <EM>modified_changed</EM> signal.

	void add_selection_clipboard(Clipboard& clipboard);
	///< Adds <EM>clipboard</EM> to the list of clipboards in which the selection contents
	///< of the buffer are available.
	///< @param clipboard A Clipboard.
	///<
	///< In most cases, clipboard will be the Clipboard of type GDK_SELECTION_PRIMARY
	///< for a view of buffer.

	void remove_selection_clipboard(Clipboard& clipboard);
	///< Removes a Clipboard added with add_selection_clipboard().
	///< @param clipboard A Clipboard added to buffer by add_selection_clipboard().

	void cut_clipboard(Clipboard& clipboard, bool default_editable);
	///< Copies the currently selected text to a clipboard, then deletes said text if it's editable.
	///< @param clipboard The Clipboard object to cut to.
	///< @param default_editable The default editability of the buffer.

	void copy_clipboard(Clipboard& clipboard);
	///< Copies the currently selected text to a clipboard.
	///< @param clipboard The Clipboard object to copy to.

	void paste_clipboard(Clipboard& clipboard, TextIter *override_location, bool default_editable);
	///< Pastes the contents of a clipboard at the insertion point, or at <EM>override_location</EM>.
	///< @param clipboard The Clipboard to paste from.
	///< @param override_location The location to insert pasted text, or null for at the cursor.
	///< @param default_editable Whether the buffer is editable by default.
	///<
	///< Note the pasting is asynchronous, that is, we'll ask for the paste data and return,
	///< and at some point later after the main loop runs, the paste data will be inserted.

	bool delete_selection(bool interactive, bool default_editable);
	///< Deletes the range between the "insert" and "selection_bound" marks, that is,
	///< the currently selected text. 
	///< @param interactive Whether the deletion is caused by user interaction.
	///< @param default_editable Whether the buffer is editable by default.
	///< @return Whether there was a non-empty selection to delete.
	///<
	///< If interactive is true, the editability of the selection will be considered
	///< (users can't delete uneditable text).

/// @}
/// @name Signal Proxies
/// @{

	const InsertTextSignalProxy signal_insert_text();
	///< Connect to the insert_text_signal; emitted whenever text is inserted into the text buffer.

	const InsertPixbufSignalProxy signal_insert_pixbuf();
	///< Connect to the insert_pixbuf_signal; emitted when a pixbuf image is inserted into the buffer.

	const InsertChildAnchorSignalProxy signal_insert_child_anchor();
	///< Connect to the insert_child_anchor_signal; emitted when a child anchor is inserted into the buffer.

	const DeleteRangeSignalProxy signal_delete_range();
	///< Connect to the delete_range_signal; emitted when contents of the buffer
	///< bewteen two iterators are removed.

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted when the contents of the buffer
	///< are changed by an insertion or deletion action.

	const ModifiedChangedSignalProxy signal_modified_changed();
	///< Connect to the modified_changed_signal; emitted when the buffer is modified
	///< since the last time it was saved.

	const MarkSetSignalProxy signal_mark_set();
	///< Connect to the mark_set_signal; emitted when a mark is placed in the buffer.

	const MarkDeletedSignalProxy signal_mark_deleted();
	///< Connect to the mark_deleted_signal; emitted when a mark is removed from the buffer.

	const ApplyTagSignalProxy signal_apply_tag();
	///< Connect to the apply_tag_signal; emitted when a tag is applied to a range characters
	///< bewteen two iterators.

	const RemoveTagSignalProxy signal_remove_tag();
	///< Connect to the remove_tag_signal; emitted when all occurrences of a tag are removed from
	///< a range characters bewteen two iterators.

	const BeginUserActionSignalProxy signal_begin_user_action();
	///< Connect to the begin_user_action_signal; emitted to indicate the user is starting
	///< buffer operations that are part of a single user-visible operation.

	const EndUserActionSignalProxy signal_end_user_action();
	///< Connect to the end_user_action_signal; emitted to indicate the user has ended
	///< the current buffer operations.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/textbuffer.inl>

#endif // XFC_GTK_TEXT_BUFFER_HH

