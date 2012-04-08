/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/error.hh
/// @brief A C++ GLib error reporting class.
///
/// GLib provides a standard method of reporting errors from a called function to the calling code.
/// It's important to understand that this method is both a data type (the G::Error object) and a
/// set of rules. If you use G::Error incorrectly, then your code will not properly interoperate
/// with other code that uses G::Error, and users of your API will probably get confused.

#ifndef XFC_G_ERROR_HH
#define XFC_G_ERROR_HH

#include <exception>

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_ERROR_H__
#include <glib/gerror.h>
#endif

namespace Xfc {

namespace G {

class Quark;

/// @class Error error.hh xfc/glib/error.hh
/// @brief A C++ GLib error reporting class.
///
/// Error provides a C++ wrapper for GLib's standard method of reporting errors from a called
/// function to the calling code. It's important to understand that this method is both a data type
/// (the Error object) and a set of rules. If you use Error incorrectly, then your code will
/// not properly interoperate with other code that uses Error, and users of your API will probably
/// get confused.
///
/// First and foremost: Error should only be used to report recoverable runtime errors, never to
/// report programming errors. If the programmer has screwed up, then you should use g_warning(),
/// g_return_if_fail(), g_assert(), g_error(), or some similar facility. (Incidentally, remember that
/// the g_error() function should only be used for programming errors, it should not be used to print
/// any error reportable via G::Error.)
///
/// This class can be thrown, as an std exception too.
/// 
/// Examples of recoverable runtime errors are "file not found" or "failed to parse input". Runtime 
/// errors should be handled or reported to the user, programming errors should be eliminated by
/// fixing the bug in the program. This is why most functions in XFC do not use the Error facility.
/// You will find examples of Error usage in the gfc-demo program. The following example is from
/// "demowindow.cc".
/// @code
/// Pointer<Gdk::Pixbuf> pixbuf;
/// G::Error error;
///
/// String filename = find_file("gtk-logo-rgb.gif", &error);
/// if (!filename.null())
/// 	pixbuf = new Gdk::Pixbuf(filename, &error);
///
/// if (error.get())
/// {
/// 	Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
/// 	dialog.set_message("Failed to read icon file: %s", error.message());
/// 	dialog.set_position(Gtk::WIN_POS_CENTER);
/// 	dialog.run();
/// 	dialog.dispose();
/// }
/// @endcode
/// <BR>Note that passing NULL for the error location ignores errors.

class Error : public StackObject, public std::exception 
{
	GError *error_;

public:
/// @name Constructors
/// @{

	Error() throw();
	///< Create a properly initialized error object.

	Error(GQuark domain, int code, const char *format, ...) throw();
	///< Create a new error object with the given domain and code, and a message formatted with format.
	///< @param domain The error domain.
	///< @param code The error code.
	///< @param format Parameters for message format.
	///< @param ... Arguments to format.

	Error(GQuark domain, int code, const String& message) throw();
	///< Create a new error object with the given domain, code, and message.
	///< @param domain The error domain.
	///< @param code The error code.
	///< @param message The error message.
	///<
	///< Unlike the other constructor, message is not a printf()-style format string. Use
	///< this constructor if message contains text you don't have control over, that could include
	///< printf() escape sequences.

	Error(GError *error) throw();
	///< Create an Error from an existing GError*. Used by XFC for error reporting.

	Error(const Error& src) throw();
	///< Copy constructor.

	virtual ~Error() throw();
	///< Destructor.

	Error& operator=(const Error& src);
	///< Assignment operator.

/// @}
/// @name Accessors
/// @{

	operator GError* () const;
	///< Returns the internal GError pointer.

	operator GError** ();
	///< The return location for an allocated error

	bool get() const;
	///< Returns true if the error-reporting function failed and reported an error.

	bool matches(GQuark domain, int code) const;
	///< Returns <EM>true</EM> if error matches domain and code, <EM>false</EM> otherwise.
	///< @param domain An error domain.
	///< @param code An error code.
	///< @return Whether error has domain and code.

	Quark domain() const;
	///< Returns the error domain.

	int code() const;
	///< Returns the error code.

	const char* message() const;
	///< Returns the human-readable informative error message.

/// @}
/// @name Methods
/// @{

	void set(GQuark domain, int code, const char *format, ...);
	///< A new error object is created and assigned to the internal error pointer.
	///< @param domain The error domain.
	///< @param code The error code.
	///< @param format printf()-style message format.
	///< @param ... Arguments to format.
	
	void set(GQuark domain, int code, const String& message);
	///< A new error object is created and assigned to the internal error pointer.
	///< @param domain The error domain.
	///< @param code The error code.
	///< @param message The error message.
	///<
	///< Unlike the other set method, message is not a printf()-style format string. Use
	///< this method if message contains text you don't have control over, that could include
	///< printf() escape sequences.

	void propagate(const Error& src);
	///< Moves src into the calling error object.

	void clear();
	///< Frees the associated GError object and sets the internal error pointer to null.

    /// std C++ exception, that just return the human readable message part
    virtual const char *what( void ) const throw();
    
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/error.inl>

#endif // XFC_G_ERROR_HH
