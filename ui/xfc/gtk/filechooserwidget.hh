/*  XFC: Xfce Foundation Classes (User Interface Library)
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

/// @file xfc/gtk/filechooserwidget.hh
/// @brief A GtkFileChooserWidget C++ wrapper interface.
///
/// Provides FileChooserWidget, a file chooser widget that can be embedded in other widgets. 

#ifndef XFC_GTK_FILE_CHOOSER_WIDGET_HH
#define XFC_GTK_FILE_CHOOSER_WIDGET_HH

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef XFC_GTK_FILE_CHOOSER_HH
#include <xfc/gtk/filechooser.hh>
#endif

#ifndef __GTK_FILE_CHOOSER_WIDGET_H__
#include <gtk/gtkfilechooserwidget.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class FileChooserWidget filechooserwidget.hh xfc/gtk/filechooserwidget.hh
/// @brief A GtkFileChooserWidget C++ wrapper class.
///
/// FileChooserWidget is a widget suitable for selecting files. It is the main
/// building block of a Gtk::FileChooserDialog. Most applications will only need
/// to use the latter; but you can use GtkFileChooserWidget as part of a larger 
/// window if you have special needs. 
/// 
/// Note that FileChooserWidget does not have any methods of its own. Instead, 
/// you should use the functions that work on a Gtk::FileChooser. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/filechooser.html">File Chooser</A> HOWTO
/// and the file chooser example in the <tests/filechooser> suddirectory.

class FileChooserWidget : public VBox, public FileChooser
{
	friend class G::Object;

	FileChooserWidget(const FileChooserWidget&);
	FileChooserWidget& operator=(const FileChooserWidget&);

protected:
/// @name Constructors
/// @{

	explicit FileChooserWidget(GtkFileChooserWidget *widget, bool owns_reference = false);
	///< Construct a new FileChooserWidget from an existing GtkFileChooserWidget.
	///< @param widget A pointer to a GtkFileChooserWidget.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>widget</EM> can be a newly created GtkFileChooserWidget or an existing
	///< GtkFileChooserWidget (see G::Object::Object).

/// @}

public:
	typedef GtkFileChooserWidget CObjectType;

/// @name Constructors
/// @{

	FileChooserWidget(FileChooserAction action, const char *backend = 0);
	///< Constructs a new file chooser widget.
	///< @param action Open or save mode for the widget. 
	///< @param backend The name of the specific filesystem backend to use, or null for the default. 
	
	virtual ~FileChooserWidget();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkFileChooserWidget* gtk_file_chooser_widget() const;
	///< Get a pointer to the GtkFileChooserWidget structure.

	operator GtkFileChooserWidget* () const;
	///< Conversion operator; safely converts an FileChooserWidget to a GtkFileChooserWidget pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/filechooserwidget.inl>

#endif // XFC_GTK_FILE_CHOOSER_WIDGET_HH

