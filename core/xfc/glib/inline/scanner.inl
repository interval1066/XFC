/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  scanner.inl - G::Scanner inline functions
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

inline GScanner*
Xfc::G::Scanner::g_scanner() const
{
	return scanner_;
}

inline Xfc::G::Scanner::operator GScanner* () const
{
	return this ? scanner_ : 0;
}

inline GTokenType
Xfc::G::Scanner::token() const
{
	return g_scanner_cur_token(scanner_);
}

inline GTokenValue
Xfc::G::Scanner::value() const
{
	return g_scanner_cur_value(scanner_);
}

inline unsigned int
Xfc::G::Scanner::line() const
{
	return g_scanner_cur_line(scanner_);
}

inline unsigned int
Xfc::G::Scanner::position() const
{
	return g_scanner_cur_position(scanner_);
}

inline bool
Xfc::G::Scanner::eof() const
{
	return g_scanner_eof(scanner_) != 0;
}

inline GTokenType
Xfc::G::Scanner::next_token() const
{
	return scanner_->next_token;
}

inline GTokenValue
Xfc::G::Scanner::next_value() const
{
	return scanner_->next_value;
}

inline unsigned int
Xfc::G::Scanner::next_line() const
{
	return scanner_->next_line;
}

inline unsigned int
Xfc::G::Scanner::next_position() const
{
	return scanner_->next_position;
}

inline GTokenType
Xfc::G::Scanner::get_next_token() const
{
	return g_scanner_get_next_token(scanner_);
}

inline GTokenType
Xfc::G::Scanner::peek_next_token() const
{
	return g_scanner_peek_next_token(scanner_);
}

inline void
Xfc::G::Scanner::input_file(int input_fd)
{
	g_scanner_input_file(scanner_, input_fd);
}

inline void
Xfc::G::Scanner::sync_file_offset()
{
	g_scanner_sync_file_offset(scanner_);
}

inline void
Xfc::G::Scanner::input_text(const char *text, unsigned int length)
{
	g_scanner_input_text(scanner_, text, length);
}

inline unsigned int
Xfc::G::Scanner::set_scope(unsigned int scope_id)
{
	return g_scanner_set_scope(scanner_, scope_id);
}

inline void
Xfc::G::Scanner::scope_add_symbol(unsigned int scope_id, const char *symbol, void *value)
{
	g_scanner_scope_add_symbol(scanner_, scope_id, symbol, value);
}

inline void
Xfc::G::Scanner::scope_remove_symbol(unsigned int scope_id, const char *symbol)
{
	g_scanner_scope_remove_symbol(scanner_, scope_id, symbol);
}

inline void*
Xfc::G::Scanner::scope_lookup_symbol(unsigned int scope_id, const char *symbol)
{
	return g_scanner_scope_lookup_symbol(scanner_, scope_id, symbol);
}

inline void*
Xfc::G::Scanner::lookup_symbol(const char *symbol)
{
	return g_scanner_lookup_symbol(scanner_, symbol);
}

