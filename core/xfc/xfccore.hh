/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/xfccore.hh
/// @brief The main XFC core header file.
///
/// This header file includes all the XFC core header files and the compile-time
/// XFC version numbers. You can safely include this header file only, with
/// minimal extra overhead, because each header file uses include guards to prevent
/// multiple inclusions.

/// @defgroup xfc_group The Xfc Namespace
/// @namespace Xfc
/// @brief The primary namespace for the Xfce Foundation Classes.

/// @defgroup i18n_group The Internationalization Namespace
/// @namespace Xfc::i18n
/// @ingroup xfc_group
/// @brief The internationalization and localization namespace.
///
/// Provides a C++ interface to GNU gettext for
/// Internationalization and Localization support.

/// @defgroup g_group The G Namespace
/// @namespace Xfc::G
/// @ingroup xfc_group
/// @brief The C++ framework for the GObject and GLib libraries.
///
/// Implements the object API that provides the base classes for the
/// entire XFC library. Also wraps several of GLIB utility classes.

#ifndef XFC_CORE_HH
#define XFC_CORE_HH

#include <xfc/i18n.hh>
#include <xfc/version.hh>
#include <xfc/glib/g.hh>

#endif // XFC_CORE_HH

