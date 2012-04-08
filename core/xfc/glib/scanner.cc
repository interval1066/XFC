/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  scanner.cc - GScanner C++ wrapper implementation
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
 
#include "scanner.hh"
#include <glib/gmessages.h>
#include <glib/gstrfuncs.h>
#include <glib/gmem.h>

using namespace Xfc;

G::Scanner::Scanner(const GScannerConfig *initial_settings)
: scanner_(g_scanner_new(initial_settings))
{
}	

G::Scanner::Scanner(GScanner *scanner)
: scanner_(scanner)
{
}

G::Scanner::~Scanner()
{
	if (scanner_)
	{
		g_scanner_destroy(scanner_);
		scanner_ = 0;
	}
}

void
G::Scanner::input_text(const String& text)
{
	g_scanner_input_text(scanner_, text.c_str(), text.size());
}

namespace {

void scope_foreach_symbol_slot(gpointer key, gpointer value, gpointer user_data)
{
	G::Scanner::ScopeForeachSymbolSlot& slot = *static_cast<G::Scanner::ScopeForeachSymbolSlot*>(user_data);
	slot(key, value);
}

} // namespace

void
G::Scanner::scope_foreach_symbol(unsigned int scope_id, const ScopeForeachSymbolSlot& slot)
{
	ScopeForeachSymbolSlot tmp_slot(slot);
	g_scanner_scope_foreach_symbol(scanner_, scope_id, &scope_foreach_symbol_slot, &tmp_slot);
}

void
G::Scanner::error(const char *format, ...)
{
	g_return_if_fail(format != 0);

	scanner_->parse_errors++;

	if (scanner_->msg_handler)
	{
		va_list args;
		va_start(args, format);
		char * msg = g_strdup_vprintf(format, args);
		va_end(args);
		scanner_->msg_handler(scanner_, msg, TRUE);
		g_free(msg);
	}
}

void
G::Scanner::warn(const char *format, ...)
{
	g_return_if_fail(format != 0);

	scanner_->parse_errors++;

	if (scanner_->msg_handler)
	{
		va_list args;
		va_start(args, format);
		char * msg = g_strdup_vprintf(format, args);
		va_end(args);
		scanner_->msg_handler(scanner_, msg, FALSE);
		g_free(msg);
	}
}

