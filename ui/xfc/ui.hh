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

/// @file xfc/ui.hh
/// @brief A convenient header file that includes the main user interface elements.
///
/// This convenient header file includes the header files generally needed by 
/// most applications. Note, \<xfc/gtk/dialog.hh\> includes all the header files
/// in it's inheritance path. These are: \<xfc/gtk/window.hh\>, \<xfc/gtk/bin.hh\>, 
/// \<xfc/gtk/container.hh\>, \<xfc/gtk/widget.hh\>, \<xfc/gtk/object.hh\> and
/// \<xfc/glib/object.hh\>.

#ifndef XFC_UI_HH
#define XFC_UI_HH

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

#endif // XFC_UI_HH
