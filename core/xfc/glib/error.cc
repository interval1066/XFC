/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  error.cc - GError C++ wrapper implementation
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

#include "error.hh"
#include "quark.hh"
#include <glib-object.h>

using namespace Xfc;

namespace {

GError* error_new_valist(GQuark domain, int code, const char *format, va_list args)
{
	GError *error = g_new(GError, 1);
	error->domain = domain;
	error->code = code;
	error->message = g_strdup_vprintf (format, args);
	return error;
}

} // namespace

G::Error::Error() throw() : error_(0)
{
}

G::Error::Error(GQuark domain, int code, const char *format, ...) throw()
: error_(0)
{
	g_return_if_fail(format != 0);
	g_return_if_fail(domain != 0);
	va_list args;
	va_start(args, format);
	error_ = error_new_valist(domain, code, format, args);
	va_end(args);
}

G::Error::Error(GQuark domain, int code, const String& message) throw()
: error_(g_error_new_literal(domain, code, message.c_str()))
{
}

G::Error::Error(GError *error) throw()
: error_(g_error_copy(error))
{
}

G::Error::Error(const Error& src) throw()
: error_(g_error_copy(src.error_))
{
}

G::Error::~Error() throw()
{
	if (error_)
	{
		g_error_free(error_);
		error_ = 0;
	}
}

G::Error&
G::Error::operator=(const Error& src)
{
	if (src.error_ == error_)
		return *this;

	if (error_)
		g_error_free(error_);

	error_ = g_error_copy(src.error_);
	return *this;
}

void
G::Error::set(GQuark domain, int code, const char *format, ...)
{
	g_return_if_fail(format != 0);
	if (error_)
		clear();
	va_list args;
	va_start(args, format);
	error_ = error_new_valist(domain, code, format, args);
	va_end(args);
}

G::Quark
G::Error::domain() const
{
	return error_->domain;
}

void
G::Error::set(GQuark domain, int code, const String& message)
{
	if (error_)
		clear();
	g_set_error(&error_, domain, code, message.c_str());
}

void
G::Error::propagate(const Error& src)
{
	if (error_)
		clear();
	g_propagate_error(&error_, src.error_);
}

const char * G::Error::what( void ) const throw()
{
    return (error_) ? error_->message : "Undefined error";
}
