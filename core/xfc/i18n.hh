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

/// @file xfc/i18n.hh
/// @brief A C++ gettext wrapper for internationalization and localiztion.
///
/// Provides convenient C++ wrapper methods for the various gettext functions.

#ifndef XFC_INTL_HH
#define XFC_INTL_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

/// Macro for No-op i18n marker.
/// Unfortunately there's no way to make this a function, since the whole point is
/// to have a way to mark text for translation in contexts where a function call is
/// not permitted. You can define XFC_NO_INTL_NOOP_MARKER to get rid of this macro.

#ifndef XFC_NO_INTL_NOOP_MARKER
#ifndef N_
#define N_(str) (str)
#endif
#endif

namespace Xfc {

#ifdef _
#error "You can't include headers that define the _ macro before xfc/i18n.h"
#endif

/// @name GetText Methods
/// @{

const char* _(const String& str);
///< Convenient wrapper for GNU gettext.
///< @param str A String to be passed to gettext().
///< @return The translation of <EM>str</EM> if it's available in the current domain.
///<
///< GNU gettext does two things. First, it marks a string as translable so xgettext()
///< will find it when it scans your sources. The second thing it does is actually return
///< the translated string. If no translation of <EM>str</EM> is available the <EM>str</EM>
///< itself is returned. Applications should use this method instead of defining a _ macro
///< that calls gettext(). When you run xgettext() don't forget to specify the '--keyword=_'
///< option. This option tells xgettext that translatable strings are marked with an 
///< underscore instead of the word gettext.

const char* _(const String& str, const char *domain);
///< Convenient wrapper for GNU dgettext.
///< @param str A String to be passed to dgettext().
///< @param domain The name of translation domain; will always be a string literal.
///< @return The translation of <EM>str</EM> if it's available in <EM>domain</EM>.
///<
///< GNU gettext does two things. First, it marks a string as translable so xgettext()
///< will find it when it scans your sources. The second thing it does is actually return
///< the translated string. If no translation of <EM>str</EM> is available the <EM>str</EM>
///< itself is returned. Libraries must specify the domain because the global domain is 
///< reserved for use by applications. Libraries use this method instead of defining a _ 
///< macro that calls dgettext(). When you run xgettext() don't forget to specify the 
///< '--keyword=_' option. This option tells xgettext that translatable strings are marked
///< with an underscore instead of the word gettext.

/// @}

namespace i18n {

const char* set_text_domain(const char *domain);
///< Change or query the current status of the current global domain of the LC_MESSAGE category.
///< @param domain The name of translation domain (must be legal filename characters).
///< @return A domain name (see explanation below).
///<
///< If the <EM>domain</EM> is null, the function returns the current value. If no
///< value has been set before, the name of the default domain is returned: messages. 
///< It is important to note that no checks of the availability are made. If the name
///< is not available no translations will be provided. The return string must not be freed.

const char* set_text_domain_dir(const char *domain, const char *dir);
///< Binds the given <EM>domain</EM> to a file in the specified directory <EM>dir</EM>
///< (see gettext documentation to find out this file is determined).
///< @param domain The translation domain.
///< @param dir The directory name.
///< @return A directory name (see expalantion below).
///<
///< If <EM>domain</EM> is null nothing happens and a null pointer is returned. If
///< <EM>dir</EM> is null the directory associated with <EM>domain</EM> is returned. It
///< is important to remember that relative path names for <EM>dir</EM> can be trouble.
///< Since the path is always computed relative to the current directory different
///< results will occur when the program executes a chdir command. Relative paths
///< should always be avoided to avoid dependencies and unreliabilities. The return 
///< string must not be freed.

} // namepsace i18n

} // namespace Xfc

#endif // XFC_INTL_HH

