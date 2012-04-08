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
 
/// @file xfc/gtk/clipboard.hh
/// @brief A GtkClipboard C++ wrapper interface.
///
/// Provides Clipboard, an object for storing data on clipboards.

#ifndef XFC_GTK_CLIPBOARD_HH
#define XFC_GTK_CLIPBOARD_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef __GTK_CLIPBOARD_H__
#include <gtk/gtkclipboard.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Object;
}

namespace Gdk {
class Display;
class Pixbuf;
}

namespace Gtk {

class SelectionData;
class TargetEntry;

/// @class Clipboard clipboard.hh xfc/gtk/clipboard.hh
/// @brief A GtkClipboard C++ wrapper class.
///
/// The Clipboard object represents a clipboard of data shared between different processes or
/// between different widgets in the same process. Each clipboard is identified by a name encoded
/// as a Gdk::Atom. (Conversion to and from strings can be done with gdk_atom_intern() and
/// gdk_atom_name().) The default clipboard corresponds to the "CLIPBOARD" atom; another commonly
/// used clipboard is the "PRIMARY" clipboard, which, in X, traditionally contains the currently
/// selected text.
///
/// To support having a number of different formats on the clipboard at the same time, the clipboard
/// mechanism allows providing callbacks instead of the actual data. When you set the contents of the
/// clipboard, you can either supply the data directly (via functions like Gtk::Clipboard::set_text()),
/// or you can supply a <EM>slot</EM> to be called at a later time when the data is needed
/// (via Gtk::Clipboard::set()). Providing a slot also avoids having to make copies of the data when
/// it is not needed. When the clear_slot you provided is called, you simply free any data.
///
/// Requesting the data from the clipboard is essentially asynchronous. If the contents of the clipboard
/// are provided within the same process, then a direct function call will be made to retrieve the data,
/// but if they are provided by another process, then the data needs to be retrieved from the other 
/// process, which may take some time. To avoid blocking the user interface, the call to request the
/// selection, Gtk::Clipboard::request_contents() takes a slot that will be called when the contents are
/// received (or when the request fails.) If you don't want to deal with providing a separate slot, you
/// can also use Gtk::Clipboard::wait_for_contents(). What this does is run the main loop recursively
/// waiting for the contents. This can simplify the code flow, but you still have to be aware that other
/// slots in your program can be called while this recursive mainloop is running.
///
/// Along with the functions to get the clipboard contents as an arbitrary data chunk, there are also 
/// methods to retrieve it as text, Gtk::Clipboard::request_text() and Gtk::Clipboard::wait_for_text().
/// These methods take care of determining which formats are advertised by the clipboard provider,
/// asking for the clipboard in the best available format and converting the results into the UTF-8
/// encoding. (The standard form for representing strings in GTK+.)

class Clipboard : public G::Object
{
	friend class G::Object;
	
	Clipboard(const Clipboard&);
	Clipboard& operator=(const Clipboard&);

protected:
/// @name Constructors
/// @{

	explicit Clipboard(GtkClipboard *clipboard, bool owns_reference = false);
	///< Construct a new Clipboard from an existing GtkClipboard.
	///< @param clipboard A pointer to a GtkClipboard.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>clipboard</EM> can be a newly created GtkClipboard or an existing
	///< GtkClipboard. (see G::Object::Object).

/// @}

public:
	typedef GtkClipboard CObjectType;
	
	typedef sigc::slot<void, const SelectionData&> ReceivedSlot;
	///< Signature of the callback slot to be called when the results of request_contents()
	///< are received, or when the request fails.
	///<
	///< <B>Example:</B> Method signature for ReceivedSlot.
	///< @code
	///< void method(const SelectionData& selection_data);
	///< // selection_data: contains the data that was received. If retrieving the data failed,
	///< //                 then Gtk::SelectionData::is_valid() will be false.
	///< @endcode

	typedef sigc::slot<void, const String&> TextReceivedSlot;
	///< Signature of the callback slot to be called when the results of request_text()
	///< are received, or when the request fails.
	///<
	///< <B>Example:</B> Method signature for TextReceivedSlot.
	///< @code
	///< void method(const String& text);
	///< // text: the text received, as a UTF-8 encoded string, or null if retrieving the data failed.
	///< @endcode

 	typedef sigc::slot<void, const Pointer<Gdk::Pixbuf>& > ImageReceivedSlot;	
	///< Signature of the callback slot to be called when the results of request_image()
	///< are received, or when the request fails.
	///< <B>Example:</B> Method signature for ImageReceivedSlot.
	///< @code
	///< void method(const Pointer<Gdk::Pixbuf>& pixbuf);
	///< // pixbuf: the image received, as a Gdk::Pixbuf, or null if retrieving the image failed.
	///< @endcode
	///<
	///< Image retrieval could fail for various reasons, in particular if the clipboard was empty
	///< or if the contents of the clipboard could not be converted into an image.
	
	typedef sigc::slot<void, const std::vector<Gdk::Atom>&> TargetsReceivedSlot;
	///< Signature of the callback slot to be called when the results of request_targets()
	///< are received, or when the request fails.
	///<
	///< <B>Example:</B> Method signature for TargetsReceivedSlot.
	///< @code
	///< void method(const std::vector<Gdk::Atom>& targets);
	///< // targets: The supported targets, as vector of Gdk::Atom, or an empty vector if retrieving the data failed.
	///< @endcode
	
	typedef sigc::slot<void, SelectionData&, unsigned int> GetSlot;
	///< Signature of the callback slot that will be called to provide the contents of the selection.
	///< If multiple types of data were advertised, the requested type can be determined from the info
	///< (unsigned int) parameter or by checking the target field of the SelectionData. If the data could
	///< successfully be converted into then it should be stored into the selection_data object by
	///< calling Gtk::SelectionData::set() (or related functions such as Gtk::SelectionData::set_text()).
	///< If no data is set, the requestor will be informed that the attempt to get the data failed.
	///<
	///< <B>Example:</B> Method signature for GetSlot.
	///< @code
	///< void method(SelectionData& selection_data, unsigned int info);
	///< // selection_data: contains the data that was received. If retrieving the data failed,
	///< //                 then Gtk::SelectionData::is_valid() will be false.
	///<
	///< // info:           the info field corresponding to the requested target from the
	///< //                 TargetEntry vector passed to set().
	///< @endcode

	typedef sigc::slot<void> ClearSlot;
	///< Signature of the callback slot that will be called when the contents of the clipboard are changed
	///< or cleared.
	///< <B>Example:</B> Method signature for ClearSlot.
	///< @code
	///< void method();
	///< @endcode

/// @name Constructors
/// @{

	virtual ~Clipboard();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkClipboard* gtk_clipboard() const;
	///< Get a pointer to the GtkClipboard structure.

	operator GtkClipboard* () const;
	///< Conversion operator; safely converts a Clipboard to a GtkClipboard pointer.

	Gdk::Display* get_display() const;
	///< Gets the Gdk::Display associated with the clipboard.
	///< @return The Gdk::Display associated with clipboard.

	bool wait_is_text_available() const;
	///< Test to see if there is text available to be pasted.
	///< @return <EM>true</EM> is there is text available, <EM>false</EM> otherwise. 
	///<
	///< This method requests the TARGETS atom and checks to see if it contains any
	///< of the names: STRING, TEXT, COMPOUND_TEXT, UTF8_STRING. It waits for the data
	///< to be received using the main loop, so events, timeouts, etc, may be dispatched
	///< during the wait. It's a little faster than calling wait_for_text() since it 
	///< doesn't need to retrieve the actual text.

	bool is_image_available() const;
	///< Test to see if there is an image available to be pasted.
	///< @return <EM>true</EM> is there is an image available, <EM>false</EM> otherwise.
	///<		 
	///< This is done by requesting the TARGETS atom and checking if it contains 
	///< any of the supported image targets. This method waits for the data to be
	///< received using the main loop, so events, timeouts, etc, may be dispatched
	///< during the wait.
	///<
	///< This method is a little faster than calling wait_for_image() since it doesn't
	///< need to retrieve the actual image data.
	
	bool is_target_available(Gdk::Atom target) const;
	///< Checks if a clipboard supports pasting data of a given type. 
	///< @param target A Gdk::Atom indicating which target to look for. 
	///< @return <EM>true</EM> if the target is available, <EM>false</EM> otherwise. 
	///<	
	///< This method can be used to determine if a "Paste" menu item should be insensitive
	///< or not. If you want to see if there's text available on the clipboard, use 
	///< wait_is_text_available() instead.

/// @}
/// @name Accessors
/// @{

	static Clipboard* get(Gdk::Atom selection, const Gdk::Display *display = 0);
	///< Returns the clipboard object for the given selection.
	///< @param selection A Gdk::Atom which identifies the clipboard to use.
	///< @param display The display for which the clipboard is to be retrieved
	///<                or created, or null for the default Display.
	///< @return The appropriate clipboard object.
 	///<
	///< If no clipboard already exists, a new one will be created. Once a clipboard object
	///< has been created, it is persistent for all time. GTK+ holds onto a reference to the
	///< clipboard and will unreference it when GTK+ is removed from memory.
	///<
	///< Cut/copy/paste menu items and keyboard shortcuts should use the default clipboard,
	///< returned by passing GDK_SELECTION_CLIPBOARD for selection. (GDK_NONE is supported
	///< as a synonym for GDK_SELECTION_CLIPBOARD for backwards compatibility reasons.) The
	///< currently-selected object or text should be provided on the clipboard identified by
	///< GDK_SELECTION_PRIMARY. Cut/copy/paste menu items conceptually copy the contents of
	///< the GDK_SELECTION_PRIMARY clipboard to the default clipboard, i.e. they copy the
	///< selection to what the user sees as the clipboard.
	///<
	///< Passing GDK_NONE is the same as using gdk_atom_intern("CLIPBOARD", FALSE). See
	///< http://www.freedesktop.org/standards/clipboards.txt for a detailed discussion of
	///< the "CLIPBOARD" vs. "PRIMARY" selections under the X window system. On Win32 the
	///< GDK_SELECTION_PRIMARY clipboard is essentially ignored.
	///<
	///< It's possible to have arbitrary named clipboards; if you do invent new clipboards,
	///< you should prefix the selection name with an underscore (because the ICCCM requires
	///< that nonstandard atoms are underscore-prefixed), and namespace it as well. For
	///< example, if your application called "Foo" has a special-purpose clipboard, you might
	///< call it "_FOO_SPECIAL_CLIPBOARD".
	///<
	///< <B>Note:</B> The default GDK display is the only display in the absence of MultiHead support.

	static Clipboard* get_default(const Gdk::Display *display = 0);
	///< Returns the default clipboard object for <EM>display</EM> (see get() for details).
	///< @param display The display for which the clipboard is to be retrieved
	///<                or created, or null for the default Display.
	///< @return The default clipboard object.
	///<
	///< The default clipboard is the one identified by the atom GDK_SELECTION_CLIPBOARD.
	///< Cut/copy/paste menu items and keyboard shortcuts should use the default clipboard.
	///<
	///< If no clipboard already exists, a new one will be created. Once a clipboard object
	///< has been created, it is persistent for all time. GTK+ holds onto a reference to the
	///< clipboard and will unreference it when GTK+ is removed from memory.
	///<
	///< <B>Note:</B> The default GDK display is the only display in the absence of MultiHead support.

	static Clipboard* get_primary(const Gdk::Display *display = 0);
	///< Returns the primary clipboard object (see get() for details).
	///< @param display The display for which the clipboard is to be retrieved
	///<                or created, or null for the default Display.
	///< @return The primary clipboard object.
	///<
	///< The primary clipboard is the one identified by the atom GDK_SELECTION_PRIMARY.
	///< The currently-selected object or text should be provided on the primary clipboard.
	///<
	///< If no clipboard already exists, a new one will be created. Once a clipboard object
	///< has been created, it is persistent for all time. GTK+ holds onto a reference to the
	///< clipboard and will unreference it when GTK+ is removed from memory.
	///<
	///< <B>Note:</B> The default GDK display is the only display in the absence of MultiHead support.

/// @}
/// @name Methods
/// @{

	bool set(const std::vector<TargetEntry>& targets, const GetSlot& get, const ClearSlot& clear);
	///< Sets the contents of the specified clipboard.
	///< @param targets A vector containing information about the available forms for the clipboard data.
	///< @param get Slot to call to get the actual clipboard data.
	///< @param clear When the clipboard contents are set again, this slot will be called,
	///<                   and <EM>get</EM> will not be subsequently called.
	///< @return <EM>true</EM> if setting the clipboard data succeeded.
	///<
	///< Virtually sets the contents of the specified clipboard by providing a list of
	///< supported formats for the clipboard data and a slot to call to get the actual data
	///< when it is requested.  If setting the clipboard data failed the provided slots
	///< will be ignored.

	void clear();
	///< Clears the contents of the clipboard.
	///< Generally this should only be called between the time you call set(), and when the 
	///< <EM>clear</EM> slot you supplied is called. Otherwise, the clipboard may be owned
	///< by someone else.

	void set_text(const String& text);
	///< Sets the contents of the clipboard to the given UTF-8 string. 
	///< @param text A UTF-8 string.
	///<
	///< GTK+ will make a copy of the text and take responsibility for responding for
	///< requests for the text, and for converting the text into the requested format.

	void set_image(Gdk::Pixbuf& pixbuf);
	///< Sets the contents of the clipboard to the given Gdk::Pixbuf. 
	///< @param pixbuf A Gdk::Pixbuf
	///<	
	///< GTK+ will take responsibility for responding for requests for the image, 
	///< and for converting the image into the requested format.
		
	void request_contents(Gdk::Atom target, const ReceivedSlot& received) const;
	///< Requests the contents of clipboard as the given target.
	///< @param target Atom representing the form into which to convert the selection.
	///< @param received The slot to call when the results of request_contents() are received.
	///<
	///< If the retrieval fails Gtk::SelectionData::is_valid() will be false.
	///< Alternatively, the length field of selection_data will be negative.

	void request_text(const TextReceivedSlot& received) const;
	///< Requests the contents of the clipboard as text.
	///< @param received The slot to call when the results of request_text() are received.
	///<
	///< When the text is later received, it will be converted to UTF-8 if necessary, and
	///< <EM>received</EM> will be called. The text parameter to slot method will contain
	///< the resulting text if the request succeeded, or null if it failed. This could 
	///< happen for various reasons, in particular if the clipboard was empty or if the
	///< contents of the clipboard could not be converted into text form.

	void request_image(const ImageReceivedSlot& received);
	///< Requests the contents of the clipboard as image. 
	///< @param received A callback slot to call when the image is received, or the retrieval fails.
	///<	
	///< When the image is later received, it will be converted to a GdkPixbuf,
	///< and <EM>received</EM> will be called. The pixbuf parameter to callback
	///< will contain the resulting Gdk::Pixbuf if the request succeeded, or null
	///< if it failed. This could happen for various reasons, in particular if 
	///< the clipboard was empty or if the contents of the clipboard could not be
	///< converted into an image. Note, whether the retrieval succeeds or fails the 
	///< callback slot will always be called, one way or the other. 

	void request_targets(const TargetsReceivedSlot& received);
	///< Requests the contents of the clipboard as list of supported targets. 
	///< @param received A slot to call when the targets are received, or the retrieval fails
	///<	
	///< When the list is later received, <EM>received</EM> will be called. The callback slot
	///< will contain the resulting targets, as a vector of Gdk::Atom, if the request succeeded,
	///< or an empty vector if it failed. This method will always be called one way or the other. 
	
	Pointer<SelectionData> wait_for_contents(Gdk::Atom target) const;
	///< Requests the contents of the clipboard using the given target. 
	///< @param target Atom representing the form into which to convert the selection.
	///< @return A newly-allocated SelectionData object or null if retrieving the target failed.
	///<
	///< This method waits for the data to be received using the main loop, so events,
	///< timeouts, etc, may be dispatched during the wait.

	String wait_for_text() const;
	///< Requests the contents of the clipboard as text and converts the result to UTF-8 if necessary.
	///< @return A UTF-8 String, or null if retrieving the selection data failed.
	///<
	///< This function waits for the data to be received using the main loop, so events,
	///< timeouts, etc, may be dispatched during the wait. It could fail for various reasons,
	///< in particular if the clipboard was empty or if the contents of the clipboard could
	///< not be converted into text form.
	
	Pointer<Gdk::Pixbuf> wait_for_image();
	///< Requests the contents of the clipboard as image and converts the result to a Gdk::Pixbuf.
	///< @return A smart pointer to a Gdk::Pixbuf object, or null if retrieving the image failed.
	///<	 
	///< This method waits for the data to be received using the main loop, so events,
	///< timeouts, etc, may be dispatched during the wait. Image retrieval could fail
	///< for various reasons, in particular if the clipboard was empty or if the contents
	///< of the clipboard could not be converted into an image. 

	bool wait_for_targets(std::vector<Gdk::Atom>& targets) const;
	///< Returns a vector of targets that are present on the clipboard, or an empty vector
	///< if there aren't any targets available. 
	///< @param targets A reference to a vector Gdk::Atom to hold the list of targets. 
	///< @return <EM>true</EM> if any targets are present on the clipboard, otherwise <EM>false</EM>. 
	///<	 
	///< This method waits for the data to be received using the main loop, so events,
	///< timeouts, etc, may be dispatched during the wait.

	void set_can_store(const std::vector<TargetEntry>& targets);
	///< Hints that the clipboard data should be stored somewhere when the application
	///< exits or when store() is called. 
	///< @param targets A vector of TargetEntry containing information about which forms should
	///<                be stored or null to indicate that all forms should be stored. 
	///<
	///< This value is reset when the clipboard owner changes. Where the clipboard data is stored
	///< is platform dependent, see Gdk::Display::store_clipboard() for more information.

	void store();
	///< Stores the current clipboard data somewhere so that it will stay around
	///< after the application has quit.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/clipboard.inl>

#endif // XFC_GTK_CLIPBOARD_HH

