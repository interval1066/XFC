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

/// @file xfc/gtk/filechooserdialog.hh
/// @brief A GtkFileChooserDialog C++ wrapper interface.
///
/// Provides FileChooserDialog, a dialog box suitable for "File/Open" or "File/Save" commands.

#ifndef XFC_GTK_FILE_CHOOSER_DIALOG_HH
#define XFC_GTK_FILE_CHOOSER_DIALOG_HH

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef XFC_GTK_FILE_CHOOSER_HH
#include <xfc/gtk/filechooser.hh>
#endif

#ifndef __GTK_FILE_CHOOSER_DIALOG_H__
#include <gtk/gtkfilechooserdialog.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class FileChooserDialog filechooserdialog.hh xfc/gtk/filechooserdialog.hh
/// @brief A GtkFileChooserDialog C++ wrapper class.
///
/// FileChooserDialog is a dialog box suitable for use with "File/Open" or "File/Save as"
/// commands. This widget works by putting a Gtk::FileChooserWidget inside a Gtk::Dialog.
/// It exposes the Gtk::FileChooser interface, so you can use all of the Gtk::FileChooser
/// functions on the file chooser dialog as well as those for Gtk::Dialog. To add buttons
/// to the dialog call Gtk::Dialog::add_button().
///
/// Note that FileChooserDialog does not have any methods of its own. Instead, you should
/// use the functions that work on a Gtk::FileChooser. 
///
/// <B>Example:</B> Typical usage
///
/// In the simplest of cases, you can use FileChooserDialog as in the following code: 
/// @code
/// Gtk::FileChooserDialog dialog("Open File", parent_window, Gtk::FILE_CHOOSER_ACTION_OPEN);
/// dialog->add_button(Gtk::StockId::CANCEL, Gtk::RESPONSE_CANCEL);                                                      
/// dialog->add_button(Gtk::StockId::OPEN, Gtk::RESPONSE_ACCEPT);                                                      
/// 
/// if (dialog->run() == Gtk::RESPONSE_ACCEPT)
/// {
/// 	String filename = dialog->get_filename();
/// 	open_file(filename.c_str());
/// }
/// @endcode
///
/// <B>Response Codes</B>
///
/// FileChooserDialog inherits from Gtk::Dialog, so buttons that go in its action area have
/// response codes such as Gtk::RESPONSE_ACCEPT and Gtk::RESPONSE_CANCEL. In the above example
/// the calls to add_button() adds stock "Cancel" and  "Open" buttons that use the response
/// indentifiers from Gtk::ResponseType. For most dialog boxes you can use your own custom 
/// response codes rather than the ones in Gtk::ResponseType, but Gtk::FileChooserDialog 
/// assumes that its "accept"-type action, e.g. an "Open" or "Save" button, will have one of
/// the following response codes:
/// - Gtk::RESPONSE_ACCEPT
/// - Gtk::RESPONSE_OK
/// - Gtk::RESPONSE_YES
/// - Gtk::RESPONSE_APPLY
///
/// This is because Gtk::FileChooserDialog must intercept responses and switch to folders
/// if appropriate, rather than letting the dialog terminate the implementation uses these
/// known response codes to know which responses can be blocked if appropriate. 
///
/// <B>Note:</B> Make sure you use a stock response code when you use Gtk::FileChooserDialog
/// to ensure proper operation. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/filechooser.html">File Chooser</A> HOWTO
/// and the file chooser example in the <tests/filechooser> suddirectory.

class FileChooserDialog : public Dialog, public FileChooser
{
	friend class G::Object;

	FileChooserDialog(const FileChooserDialog&);
	FileChooserDialog& operator=(const FileChooserDialog&);

protected:
/// @name Constructors
/// @{

	explicit FileChooserDialog(GtkFileChooserDialog *dialog, bool owns_reference = false);
	///< Construct a new FileChooserDialog from an existing GtkFileChooserDialog.
	///< @param dialog A pointer to a GtkFileChooserDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>dialog</EM> can be a newly created GtkFileChooserDialog or an existing
	///< GtkFileChooserDialog (see G::Object::Object).

/// @}

public:
	typedef GtkFileChooserDialog CObjectType;

/// @name Constructors
/// @{

	FileChooserDialog(const char *title, FileChooserAction action, const char *backend = 0);
	FileChooserDialog(const String& title, FileChooserAction action, const char *backend = 0);
	///< Constructs a new FileChooserDialog with no parent.
	///< @param title The title of the dialog, or null.
	///< @param action Open or save mode for the dialog. 
	///< @param backend The name of the specific filesystem backend to use, or null for the default. 
	
	FileChooserDialog(const char *title, Window *parent, FileChooserAction action, const char *backend = 0);
	FileChooserDialog(const String& title, Window *parent, FileChooserAction action, const char *backend = 0);
	///< Constructs a new FileChooserDialog.
	///< @param title The title of the dialog, or null.
	///< @param parent The transient parent of the dialog. 
	///< @param action Open or save mode for the dialog. 
	///< @param backend The name of the specific filesystem backend to use, or null for the default. 
	
	virtual ~FileChooserDialog();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkFileChooserDialog* gtk_file_chooser_dialog() const;
	///< Get a pointer to the GtkFileChooserDialog structure.

	operator GtkFileChooserDialog* () const;
	///< Conversion operator; safely converts an FileChooserDialog to a GtkFileChooserDialog pointer.

/// @}
};

/// @class FileChooserOpenDialog filechooserdialog.hh xfc/gtk/filechooserdialog.hh
/// @brief A GtkFileChooserDialog "File/Open" C++ wrapper class.
///
/// FileChooserOpenDialog is a dialog box suitable for use with "File/Open"
/// commands. To add buttons to the dialog call Gtk::Dialog::add_button().
///
/// <B>See also:</B> the <A HREF="../../howto/html/filechooser.html">File Chooser</A> HOWTO
/// and the file chooser example in the <tests/filechooser> suddirectory.

class FileChooserOpenDialog : public FileChooserDialog
{
	FileChooserOpenDialog(const FileChooserOpenDialog&);
	FileChooserOpenDialog& operator=(const FileChooserOpenDialog&);

public:
/// @name Constructors
/// @{

	FileChooserOpenDialog(Window *parent = 0);
	///< Constructs a new "File/Open" FileChooserDialog with the title "Open...".
	///< @param parent The transient parent of the dialog, or null. 
	
	FileChooserOpenDialog(const char *title, Window *parent = 0);
	FileChooserOpenDialog(const String& title, Window *parent = 0);
	///< Constructs a new "File/Open" FileChooserDialog.
	///< @param title The title of the dialog, or null.
	///< @param parent The transient parent of the dialog. 
	
	virtual ~FileChooserOpenDialog();
	///< Destructor.

/// @}
};

/// @class FileChooserSaveAsDialog filechooserdialog.hh xfc/gtk/filechooserdialog.hh
/// @brief A GtkFileChooserDialog "File/Save as" C++ wrapper class.
///
/// FileChooserSaveAsDialog is a dialog box suitable for use with "File/Save as"
/// commands. To add buttons to the dialog call Gtk::Dialog::add_button().
///
/// <B>See also:</B> the <A HREF="../../howto/html/filechooser.html">File Chooser</A> HOWTO
/// and the file chooser example in the <tests/filechooser> suddirectory.

class FileChooserSaveAsDialog : public FileChooserDialog
{
	FileChooserSaveAsDialog(const FileChooserSaveAsDialog&);
	FileChooserSaveAsDialog& operator=(const FileChooserSaveAsDialog&);

public:
/// @name Constructors
/// @{

	FileChooserSaveAsDialog(Window *parent = 0);
	///< Constructs a new "File/Save as" FileChooserDialog with the title "Save as...".
	///< @param parent The transient parent of the dialog, or null. 
	
	FileChooserSaveAsDialog(const char *title, Window *parent = 0);
	FileChooserSaveAsDialog(const String& title, Window *parent = 0);
	///< Constructs a new "File/Save as" FileChooserDialog.
	///< @param title The title of the dialog, or null.
	///< @param parent The transient parent of the dialog. 
	
	virtual ~FileChooserSaveAsDialog();
	///< Destructor.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/filechooserdialog.inl>

#endif // XFC_GTK_FILE_CHOOSER_DIALOG_HH

