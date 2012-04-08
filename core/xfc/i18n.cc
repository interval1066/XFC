/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  i18n.cc - A C++ gettext wrapper for internationalization and localiztion
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

#include "i18n.hh"
#include <libintl.h>

const char*
Xfc::_(const String& str)
{
	return gettext(str.c_str());
}

const char*
Xfc::_(const String& str, const char *domain)
{
	return dgettext(domain, str.c_str());
}

const char *
Xfc::i18n::set_text_domain(const char *domain)
{
	return textdomain(domain);
}

const char *
Xfc::i18n::set_text_domain_dir(const char *domain, const char *dir)
{
	return bindtextdomain(domain, dir);
}


