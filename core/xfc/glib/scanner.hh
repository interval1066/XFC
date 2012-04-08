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
 
/// @file xfc/glib/scanner.hh
/// @brief GScanner C++ interface.
///
/// Provides a general purpose lexical scanner.

#ifndef XFC_G_SCANNER_HH
#define XFC_G_SCANNER_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_DATASET_H__
#include <glib/gdataset.h>
#endif

#ifndef __G_SCANNER_H__
#include <glib/gscanner.h>
#endif

namespace Xfc {

namespace G {

/// @class Scanner scanner.hh xfc/glib/scanner.hh
/// @brief A general purpose lexical scanner.

class Scanner : public Xfc::Object
{
	Scanner(const Scanner&);
	Scanner& operator=(const Scanner&);

	GScanner *scanner_;

public:
	typedef sigc::slot<void, void*, void*> ScopeForeachSymbolSlot;
	///< Signature of the callback slot for a key/value pair.

/// @name Constructors
/// @{

	Scanner(const GScannerConfig *initial_settings);
	///< Construct a new scanner.
	///< @param initial_settings A GScannerConfig structure specifiying the initial settings for the scanner.
	///<
	///< If you pass null for the initial_settings, the default settings are used.
	
	explicit Scanner(GScanner *scanner);
	///< Construct a scanner from an existing GScanner.
	///< @param scanner A pointer to a GScanner.
	///<
	///< The Scanner object takes over the ownership of the GScanner and destroys it
	///< when the destructor is called.

	~Scanner();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	GScanner* g_scanner() const;
	///< Get a pointer to the GScanner object.

	operator GScanner* () const;
	///< Conversion operator; Safely converts a G::Scanner object into a GScanner pointer.
	
	GTokenType token() const;
	///< Gets the current token type. 

	GTokenValue value() const;
	///< Gets the current token value.

	unsigned int line() const;
	///< Gets the current line in the input stream (counting from 1).

	unsigned int position() const;
	///< Gets the current position in the current line (counting from 0).

	bool eof() const;
	///< Returns true if the scanner has reached the end of the file or text buffer.

	GTokenType next_token() const;
	///< Gets the next token type.

	GTokenValue next_value() const;
	///< Gets the next token value.

	unsigned int next_line() const;
	///< Gets the next line in the input stream (counting from 1).

	unsigned int next_position() const;
	///< Gets the next position in the current line (counting from 0).

	GTokenType get_next_token() const;
	///< Gets the next token, removing it from the input stream. 
	///< The token data is placed in the token(), value(), line(), and position() fields.

	GTokenType peek_next_token() const;
	///< Gets the next token, without removing it from the input stream.
	///< The token data is placed in the next_token(), next_value(), next_line(), and next_position() fields.
	
/// @}
/// @name Methods
/// @{

	void input_file(int input_fd);
	///< Prepares to scan a file.
	///< @param input_fd A file descriptor.

	void sync_file_offset();
	///< Rewinds the file descriptor to the current buffer position and blows the file read ahead buffer.
	///< This is useful for third party uses of the scanners filedescriptor, which hooks onto the
	///< current scanning position.

	void input_text(const char *text, unsigned int length);
	///< Prepares to scan a text buffer.
	///< @param text The text buffer to scan.
	///< @param length The length of the text buffer.

	void input_text(const String& text);
	///< Prepares to scan a text buffer.
	///< @param text The text buffer to scan.

	unsigned int set_scope(unsigned int scope_id);
	///< Sets the current scope.
	///< @param scope_id The new scope id.
	///< @return The old scope id.

	void scope_add_symbol(unsigned int scope_id, const char *symbol, void *value);
	///< Adds a symbol to the given scope.
	///< @param scope_id The scope id.
	///< @param symbol The symbol to add.
	///< @param value The value of the symbol.

	void scope_remove_symbol(unsigned int scope_id, const char *symbol);
	///< Removes a symbol from a scope.
	///< @param scope_id The scope id.
	///< @param symbol The symbol to remove.

	void* scope_lookup_symbol(unsigned int scope_id, const char *symbol);
	///< Looks up a symbol in a scope and returns its value.
	///< @param scope_id The scope id.
	///< @param symbol The symbol to look up.
	///<
	///< If the symbol is not bound in the scope, null is returned.

	void scope_foreach_symbol(unsigned int scope_id, const ScopeForeachSymbolSlot& slot);
	///< Calls the given slot for each of the symbol/value pairs in the given scope of the scanner. 
	///< @param scope_id The scope id.
	///< @param slot The ScopeForeachSymbolSlot method to call.
	///<
	///< The slot method is passed the symbol and value of each pair as a parameter.

	void* lookup_symbol(const char *symbol);
	///< Looks up a symbol in the current scope and returns its value.
	///< @param symbol The symbol to look up.
	///< @return The value of symbol in the current scope, or null if symbol is not bound in the current scope.
	
	void error(const char *format, ...);
	///< Outputs an error message, via the GScanner message handler.
	///< @param format The message format. See the printf() documentation.
	///< @param ... The parameters to insert into the format string.

	void warn(const char *format, ...);
	///< Outputs a warning message, via the GScanner message handler.
	///< @param format The message format. See the printf() documentation.
	///< @param ... The parameters to insert into the format string.
	
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/scanner.inl>

#endif // XFC_G_SCANNER_HH

