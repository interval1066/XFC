/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gtk/filechooserbutton.hh
/// @brief A GtkFileChooserButton C++ wrapper interface.
///
/// Provides FileChooserButton, a button to launch a file selection dialog.

#ifndef XFCE_GTK_FILE_CHOOSER_BUTTON_HH
#define XFC_GTK_FILE_CHOOSER_BUTTON_HH

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef XFC_GTK_FILE_CHOOSER_HH
#include <xfc/gtk/filechooser.hh>
#endif

#ifndef __GTK_FILE_CHOOSER_BUTTON_H__
#include <gtk/gtkfilechooserbutton.h>
#endif

namespace Xfc {

namespace Gtk {

class FileChooserDialog;

/// @class FileChooserButton filechooserbutton.hh xfc/gtk/filechooserbutton.hh
/// @brief A GtkFileChooserButton C++ wrapper class.
///
/// FileChooserButton is a widget that lets the user select a file or folder.
/// It implements the FileChooser interface. Visually, it's a file name with a
/// button to bring up a FileChooserDialog. The user can then use that dialog
/// to change the file associated with that button. This widget does not support
/// setting the "select-multiple" property to true.
///
/// <B>Example:</B> Create a button to let the user select a file in /etc
///
/// In the simplest of cases, you can use FileChooserDialog as in the following code: 
/// @code
/// Gtk::FileChooserButton *button = new Gtk::FileChooserButton(_("Select a file"));
/// button->set_current_folder("/etc");
/// @endcode
///
/// FileChooserButton only supports the FileChooserActions: Gtk::FILE_CHOOSER_ACTION_OPEN
/// and Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER. FileChooserButton will ellipsize the
/// label, and thus will thus request little horizontal space. To give the button more
/// space, you should call set_width_chars(), Gtk::Widget::size_request(), or pack the
/// button in such a way that other interface elements give space to the widget. 

class FileChooserButton : public HBox, public FileChooser
{
	friend class G::Object;
	
	FileChooserButton(const FileChooserButton&);
	FileChooserButton& operator=(const FileChooserButton&);
	
protected:
/// @name Constructors
/// @{

	explicit FileChooserButton(GtkFileChooserButton *button, bool owns_reference = false);
	///< Construct a new FileChooserButton from an existing GtkFileChooserButton.
	///< @param button A pointer to a GtkFileChooserButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button</EM> can be a newly created GtkFileChooserButton or an existing
	///< GtkFileChooserButton. (see G::Object::Object).
	
/// @}
public:
	typedef GtkFileChooserButton CObjectType;

/// @name Constructors
/// @{
	
	FileChooserButton(FileChooserAction action, const char *backend = 0);
	///< Constructs a new FileChooserButton.
	///< @param action The open for the widget. 
	///< @param backend The name of the specific filesystem backend to use, or null for the default. 
		
	FileChooserButton(const char *title, FileChooserAction action, const char *backend = 0);
	FileChooserButton(const String& title, FileChooserAction action, const char *backend = 0);
	///< Constructs a new FileChooserButton with the given <EM>title</EM>.
	///< @param title The title of the browse dialog.
	///< @param action The open for the widget. 
	///< @param backend The name of the specific filesystem backend to use, or null for the default. 
	
	FileChooserButton(FileChooserDialog& dialog);
	///< Constructs a FileChooserButton widget which uses <EM>dialog</EM> as it's file-picking window.
	///< @param dialog A FileChooserDialog.
	
	virtual ~FileChooserButton();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkFileChooserButton* gtk_file_chooser_button() const;
	///< Get a pointer to the GtkFileChooserButton structure.

	operator GtkFileChooserButton* () const;
	///< Conversion operator; safely converts an FileChooserButton to a GtkFileChooserButton pointer.

	String get_title() const;
	///< Retrieves the title of the browse dialog used by button. 
	///< @return The browse dialog's title.
	
	int get_width_chars() const;
	///< Retrieves the width in characters of the button widget's entry and/or label.
	///< @return An integer width (in characters) that the button will use to size itself. 
 
/// @}
/// @name Methods
/// @{

	void set_title(const char *title);
	void set_title(const String& title);
	///< Modifies the title of the browse dialog used by the button.
	///< @param title The new title for the browse dialog.

	void set_width_chars(int n_chars);
	///< Sets the width (in characters) that button will use to <EM>n_chars</EM>.
	///< @param n_chars The new width, in chracters.

/// @}
};

/// @class FileChooserOpenButton filechooserbutton.hh xfc/gtk/filechooserbutton.hh
/// @brief A GtkFileChooserButton "File/Open" C++ wrapper class.
///
/// FileChooserOpenButton is a widget that lets the user select a file to open.
/// (see FileChooserButton). To select folders only, use FileChooserButton and
/// set the action: Gtk:FILE_CHOOSER_ACTION_SELECT_FOLDER. 

class FileChooserOpenButton : public FileChooserButton
{
	FileChooserOpenButton(const FileChooserOpenButton&);
	FileChooserOpenButton& operator=(const FileChooserOpenButton&);
	
public:
/// @name Constructors
/// @{
	
	FileChooserOpenButton();
	///< Constructs a new FileChooserOpenButton with the title "Open...".
	
	FileChooserOpenButton(const char *title);
	FileChooserOpenButton(const String& title);
	///< Constructs a new FileChooserOpenButton with the given <EM>title</EM>.
	///< @param title The title of the browse dialog.
	
	virtual ~FileChooserOpenButton();
	///< Destructor.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/filechooserbutton.inl>

#endif // XFC_GTK_FILE_CHOOSER_BUTTON_HH

