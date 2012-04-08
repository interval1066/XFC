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

/// @file xfc/xfcui.hh
/// @brief The main XFC user inteface header file.
///
/// This header file includes all the XFC user inteface header files. You can safely
/// include this header file only, with minimal extra overhead, because each header
/// file uses include guards to prevent multiple inclusions.

/// @defgroup main_group The Main Namespace
/// @namespace Xfc::Main
/// @ingroup xfc_group
/// @brief The initialization, main event loop and event namespace.
///
/// Provides a set of methods and signals for handling program
/// initialization and custom event loop processing.

/// @defgroup atk_group The Atk Namespace
/// @namespace Xfc::Atk
/// @ingroup xfc_group
/// @brief The C++ framework for the ATK Accessibility Toolkit.
///
/// Provides a set of generic interfaces allowing accessibility
/// technologies to interact with a graphical user interface.
/// For example, a screen reader uses ATK to discover the text
/// in an interface and read it to blind users. GTK+ widgets have
/// built-in support for accessibility using the ATK framework.

/// @defgroup gdk_group The Gdk Namespace
/// @namespace Xfc::Gdk
/// @ingroup xfc_group
/// @brief The C++ framework for the GTK+ Drawing Kit and the GdkPixbuf library.
///
/// Provides an API that can be used to add two-dimensional graphics
/// to your program. GDK itself is the abstraction layer that allows
/// GTK+ to support multiple windowing systems. GDK provides drawing
/// and window system facilities on X11, Windows, and the Linux 
/// framebuffer device.

/// @defgroup gtk_group The Gtk Namespace
/// @namespace Xfc::Gtk
/// @ingroup xfc_group
/// @brief The C++ framework for the GTK GUI library.
///
/// Provides a set of graphical objects called widgets which serve as
/// the GUI component, such as Gtk::Button and Gtk::Textview.

/// @defgroup pango_group The Pango Namespace
/// @namespace Xfc::Pango
/// @ingroup xfc_group
/// @brief The C++ framework for the Pango text handling library.
///
/// Pango is a library for internationalized text handling. It centers
/// around the Pango::Layout object, representing a paragraph of text.
/// Pango provides the engine for Gtk::TextView, Gtk::Label, Gtk::Entry
/// and other widgets that display text.

/// @defgroup cairo_group The Cairo Namespace
/// @namespace Xfc::Cairo
/// @ingroup xfc_group
/// brief The C++ framework for the Cairo vector drawing library
///
/// Cairo is a 2D graphics library with support for multiple output devices. 

#ifndef XFC_UI_H
#define XFC_UI_H

#include <xfc/atk/atk.hh>
#include <xfc/gdk/gdk.hh>
#include <xfc/gdk-pixbuf/gdk-pixbuf.hh>
#include <xfc/gtk/gtk.hh>
#include <xfc/pango/pango.hh>
#include <xfc/cairo/cairo.hh>

#endif // XFC_UI_H

