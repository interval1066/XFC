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

/// @file xfc/gtk/filechooser.hh
/// @brief A GtkFileChooser C++ wrapper interface.
///
/// Provides FileChooser, an object 

#ifndef XFC_GTK_FILE_CHOOSER_HH
#define XFC_GTK_FILE_CHOOSER_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_GTK_FILE_FILTER_HH
#include <xfc/gtk/filefilter.hh>
#endif

#ifndef __GTK_FILE_CHOOSER_H__
#include <gtk/gtkfilechooser.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gtk {

class Widget;

/// @enum FileChooserAction
/// Describes whether a FileChooser is being used to open 
/// existing files or to save to a possibly new file.

enum FileChooserAction
{
	FILE_CHOOSER_ACTION_OPEN = GTK_FILE_CHOOSER_ACTION_OPEN,
	///< Indicates open mode; The file chooser will only let the user pick an existing file.
	
	FILE_CHOOSER_ACTION_SAVE = GTK_FILE_CHOOSER_ACTION_SAVE,
	///< Indicates save mode; The file chooser will let the user pick an existing file, 
	///< or type in a new filename.
	
	FILE_CHOOSER_ACTION_SELECT_FOLDER = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
	///< Indicates an Open mode for selecting folders; The file chooser will let
	/// the user pick an existing folder. 
	
	FILE_CHOOSER_ACTION_CREATE_FOLDER = GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER
	///< Indicates a mode for creating a new folder; The file chooser will let 
	///< the user name an existing or new folder.
};

/// @enum FileChooserError
/// These identify the various errors that can occur while calling FileChooser functions. 

enum FileChooserError
{
	FILE_CHOOSER_ERROR_NONEXISTENT = GTK_FILE_CHOOSER_ERROR_NONEXISTENT,
	///< Indicates that a file does not exist.
	
	FILE_CHOOSER_ERROR_BAD_FILENAME = GTK_FILE_CHOOSER_ERROR_BAD_FILENAME
	///< Indicates a malformed filename.
};

/// @class FileChooser filechooser.hh xfc/gtk/filechooser.hh
/// @brief A GtkFileChooser C++ wrapper class.
///
/// FileChooser is an interface that can be implemented by file selection widgets.
/// In XFC, the main objects that implement this interface are Gtk::FileChooserWidget
/// and Gtk::FileChooserDialog. You do not need to write an object that implements the
/// FileChooser interface unless you are trying to adapt an existing file selector to
/// expose a standard programming interface. 
///
/// <B>File Names and Encodings</B>
///
/// When the user is finished selecting files in a FileChooser, your program can get 
/// the selected names either as filenames or as URIs. For URIs, the normal escaping
/// rules are applied if the URI contains non-ASCII characters. However, filenames
/// are always returned in the character set specified by the G_FILENAME_ENCODING 
/// environment variable. Please see the Glib documentation for more details about
/// this variable. 
///
/// <B>Important:</B> This means that while you can pass the result of get_filename()
/// to open(2) or fopen(3), you may not be able to directly set it as the text of 
/// a Gtk::Label widget unless you convert it first to UTF-8, which all GTK+ widgets
/// expect. For this reason, methods that take a filename as an argument or return a
/// filename use a std::string, not an Xfc::String. To convert this filename into a
/// UTF-8 string that all GTK+ widgets expect call Xfc::String::from_filename(). To
/// convert a UTF-8 string into a filename string call Xfc::String::to_filename();
///
/// <HR><B>Adding a Preview Widget</B>
///
/// You can add a custom preview widget to a file chooser and then get notification
/// about when the preview needs to be updated. To install a preview widget, use 
/// set_preview_widget(). Then, connect to the file chooser's 'update_preview_signal'
/// with signal_update_preview() to get notified when you need to update the contents
/// of the preview. 
///
/// Your callback slot should use get_preview_filename() to see what needs previewing.
/// Once you have generated the preview for the corresponding file, you must call 
/// set_preview_widget_active() with a boolean flag that indicates whether your slot
/// could successfully generate a preview.
///
/// @code
/// MyFileChooser::MyFileChooser
/// {
/// 	Gtk::Image *preview = new Gtk::Image;
/// 	my_file_chooser->set_preview_widget(*preview);
/// 	my_file_chooser->signal_update_preview().connect(sigc::mem_fun(my_file_chooser, 
/// 	                                              &MyFileChooser::on_update_preview));
/// }
/// 
/// void
/// MyFileChooser::on_update_preview()
/// {
/// 	String filename = get_preview_filename();
/// 	Pointer<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create(filename, 128, 128);
/// 	if (pixbuf)
/// 	{
/// 		preview->set_from_pixbuf(pixbuf);
/// 		set_preview_widget_active(true);
/// 	}
/// }
/// @endcode
///
/// <HR><B>Adding Extra Widgets</B>    
///
/// You can add extra widgets to a file chooser to provide options that are not present
/// in the default design. For example, you can add a toggle button to give the user the
/// option to open a file in read-only mode. You can use set_extra_widget() to insert 
/// additional widgets in a file chooser.
///
/// 
/// @code
/// MyFileChooser::MyFileChooser
/// {
/// 	Gtk::CheckButton *toggle = new Gtk::CheckButton("Open file read-only");
/// 	toggle->show();
/// 	set_extra_widget(*toggle);
/// }
/// @endcode
///
/// Note: <EM>If you want to set more than one extra widget in the file chooser, you can
/// add a container such as a Gtk::VBox or a Gtk::Table and include your widgets in it. Then,
/// set the container as the whole extra widget.</EM>
///
/// <B>See also:</B> the <A HREF="../../howto/html/filechooser.html">File Chooser</A> HOWTO
/// and the file chooser example in the <tests/filechooser> suddirectory.

class FileChooser : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	FileChooser();
	///< Constructs a new FileChooser object.	
	
	virtual ~FileChooser() = 0;

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> CurrentFolderChangedSignalType;
	typedef G::SignalProxy<TypeInstance, CurrentFolderChangedSignalType> CurrentFolderChangedSignalProxy;
	static const CurrentFolderChangedSignalType current_folder_changed_signal;
	///< Current folder changed signal (see signal_current_folder_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
	typedef G::Signal<void> FilerActivatedSignalType;
	typedef G::SignalProxy<TypeInstance, FilerActivatedSignalType> FilerActivatedSignalProxy;
	static const FilerActivatedSignalType file_activated_signal;
	///< File activated signal (see signal_file_activated()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> SelectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionChangedSignalType> SelectionChangedSignalProxy;
	static const SelectionChangedSignalType selection_changed_signal;
	///< Selection changed signal (see signal_selection_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
	typedef G::Signal<void> UpdatePreviewSignalType;
	typedef G::SignalProxy<TypeInstance, UpdatePreviewSignalType> UpdatePreviewSignalProxy;
	static const UpdatePreviewSignalType update_preview_signal;
	///< Update preview signal (see signal_update_preview()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	GtkFileChooser* gtk_file_chooser() const;
	///< Get a pointer to the GtkFileChooser structure.

	operator GtkFileChooser* () const;
	///< Conversion operator; safely converts an FileChooser to a GtkFileChooser pointer.

	FileChooserAction get_action() const;
	///< Gets the type of operation that the file chooser is performing (see set_action()).
	///< @return The action that the file selector is performing.

	bool get_local_only() const;
	///< Gets whether only local files can be selected in the file selector (see set_local_only()).
	///< @return <EM>true</EM> if only local files can be selected.

	bool get_select_multiple() const;
	///< Gets whether multiple files can be selected in the file selector (see set_select_multiple()).
	///< @return <EM>true</EM> if multiple files can be selected.

	bool get_show_hidden() const;
	///< Determines whether hidden files and folders are displayed in the file selector (see set_show_hidden()).
	///< @return <EM>true</EM> if hidden files and folders are displayed. 
	
	std::string get_filename() const;
	///< Gets the filename for the currently selected file in the file selector. 
	///< @return The currently selected filename.
	///<	
	///< If multiple files are selected, one of the filenames will be returned at random. 
	///< If the file chooser is in folder mode, this function returns the selected folder.
	///< 
	///< Note an empty string is returned if no file is selected, or the selected file 
	///< can't be represented with a local filename.

	bool get_filenames(std::vector<std::string>& filenames) const;
	///< Lists all the selected files and subfolders in the current folder of the file chooser.
	///< @param filenames A vector of std::string to hold the filenames. 
	///< @return <EM>true</EM> if any filenames are returned, <EM>false</EM> otherwise.
	///<	 
	///< The returned names are full absolute paths. If files in the current folder 
	///< cannot be represented as local filenames they will be ignored (see get_uris()).

	std::string get_current_folder() const;
	///< Gets the current folder of chooser as a local filename (see set_current_folder()).
	///< @return The full path of the current folder.
	///<	 
	///< Note an empty string is returned if the current path cannot be represented as a local filename.

	String get_uri() const;
	///< Gets the URI for the currently selected file in the file selector. 
	///< @return The currently selected URI, or a null String if no file is selected.
	///<	
	///< If multiple files are selected, one of the filenames will be returned at random. 
	///< If the file chooser is in folder mode, this function returns the selected folder.

	bool get_uris(std::vector<String>& uris) const;
	///< Lists all the selected files and subfolders in the current folder of chooser.
	///< @param uris A vector of String to hold the uris. 
	///< @return <EM>true</EM> if any uris are returned, <EM>false</EM> otherwise.
	///<	 
	///< The returned names are full absolute URIs.

	String get_current_folder_uri() const;
	///< Gets the current folder of the file chooser as an URI (see set_current_folder_uri()).
	///< @return The URI for the current folder.

	Widget* get_preview_widget() const;
	///< Gets the current preview widget (see set_preview_widget()).
	///< @return The current preview widget, or null.

	bool get_preview_widget_active() const;
	///< Gets whether the preview widget set by set_preview_widget() should be shown
	///< for the current filename (see set_preview_widget_active()).
	///< @return <EM>true</EM> if the preview widget is active for the current filename.

	bool get_use_preview_label() const;
	///< Gets whether a stock label should be drawn with the name of the previewed file
	///< (see set_use_preview_label()).
	///, @return <EM>true</EM> if the file chooser will display a label with the previewed file name.

	std::string get_preview_filename() const;
	///< Gets the filename that should be previewed in a custom preview widget (see set_preview_widget()).
	///< @return The filename to preview.
	///<	 
	///< Note an empty string is returned if no file is selected, or if the
	///< selected file cannot be represented as a local filename. 
 
	String get_preview_uri() const;
	///< Gets the URI that should be previewed in a custom preview widget (see set_preview_widget()).
	///< @return The URI for the file to preview, or a null String if no file is selected.

	Widget* get_extra_widget() const;
	///< Gets the current preview widget (see set_extra_widget()).
	///< @return The current extra widget, or null.

	FileFilter* get_filter() const;
	///< Gets the current filter (see set_filter()).
	///< @returns The current filter, or null.
	
	bool list_filters(std::vector<String>& filters) const;
	///< Lists the current set of user-selectable filters (see add_filter(), remove_filter()).
	///< @param filters A vector of String to hold the filter strings. 
	///< @return <EM>true</EM> if any filters are returned, <EM>false</EM> otherwise.

	bool list_shortcut_folders(std::vector<std::string>& folders) const;
	///< Queries the list of shortcut folders in the file chooser, as set by add_shortcut_folder().
	///< @param folders A vector of std::string to hold the folder filenames. 
	///< @return <EM>true</EM> if successful, <EM>false</EM> if there are no shortcut folders.

	bool list_shortcut_folder_uris(std::vector<String>& uris) const;
	///< Queries the list of shortcut folders in the file chooser, as set by add_shortcut_folder_uri().
	///< @param uris A vector of String to hold the folder uris. 
	///< @return <EM>true</EM> if successful, <EM>false</EM> if there are no shortcut folders.
	
/// @}
/// @name Methods
/// @{

	void set_action(FileChooserAction action);
	///< Sets the type of operation that that the chooser is performing. 
	///< @param action The action that the file selector is performing.
	///<	
	///< The user interface is adapted to suit the selected action. For example, an option
	///< to create a new folder might be shown if the action is Gtk::FILE_CHOOSER_ACTION_SAVE
	///< but not if the action is Gtk::FILE_CHOOSER_ACTION_OPEN.
	 
	void set_local_only(bool local_only);
	///< Sets whether only local files can be selected in the file selector. 
	///< @param local_only Set <EM>true</EM> if only local files can be selected.
	///<	
	///< If <EM>local_only</EM> is true (the default), then the selected are files
	///< guaranteed to be accessible through the operating systems native file system
	///< and therefore the application only needs to worry about the filename functions
	///< in FileChooser, like get_filename(), rather than the URI functions like get_uri().

	void set_select_multiple(bool select_multiple);
	///< Sets whether multiple files can be selected in the file selector.
	///< @param select_multiple Set <EM>true</EM> if multiple files can be selected.
	///<	 
	///< This is only relevant if the action is set to be Gtk::FILE_CHOOSER_ACTION_OPEN
	///< or Gtk::FILE_CHOOSER_ACTION_SAVE. It cannot be set with either of the folder actions.
		
	void set_show_hidden(bool show_hidden);
	///< Sets whether hidden files and folders are displayed in the file selector.
	///< @param show_hidden Set to <EM>true</EM> if hidden files and folders should be displayed.
	 
	void set_current_name(const char *name);
	void set_current_name(const String& name);
	///< Sets the current name in the file selector, as if entered by the user. 
	///< @param name The filename to use, as a UTF-8 string.
	///< 	
	///< Note that the name passed in here is a UTF-8 string rather than a filename.
	///< This function is meant for such uses as a suggested name in a "Save As..." dialog. 
	///< If you want to preselect a particular existing file, you should use set_filename()
	///< instead.
	
	bool set_filename(const char *filename);
	bool set_filename(const std::string& filename);
	///< Sets <EM>filename</EM> as the current filename for the file chooser.
	///< @param filename The filename to set as current. 
	///< @return <EM>true</EM> if both the folder could be changed and the file was selected successfully.
	///<
	///< If the file name isn't in the current folder of the file chooser, then the
	///< current folder of chooser will be changed to the folder containing filename. 
	///< This is equivalent to a sequence of unselect_all() followed by select_filename(). 
	///<
	///< Note that the file must exist, or nothing will be done except for the directory change.
	///< To pre-enter a filename for the user, as in a save-as dialog, use set_current_name().

	bool select_filename(const char *filename);
	bool select_filename(const std::string& filename);
	///< Selects a filename. 
	///< @param filename The filename to select. 
	///< @return <EM>true</EM> if both the folder could be changed and the file was selected successfully.
	///<	
	///< If the file name isn't in the current folder of the file chooser, then the current
	///< folder of the file chooser will be changed to the folder containing <EM>filename</EM>.
	
	void unselect_filename(const char *filename);
	void unselect_filename(const std::string& filename);
	///< Unselects a currently selected filename. 
	///< @param filename The filename to unselect. 
	///<	
	///< If the filename is not in the current directory, does not exist, 
	///< or is otherwise not currently selected, this method does nothing.

	void select_all();
	///< Selects all the files in the current folder of a file chooser.

	void unselect_all();
	///< Unselects all the files in the current folder of a file chooser.

	bool set_current_folder(const char *filename);
	bool set_current_folder(const std::string& filename);
	///< Sets the current folder for chooser from a local filename. 
	///< @param filename The full path of the new current folder. 
	///< @return <EM>true</EM> if the folder could be changed successfully, <EM>false</EM> otherwise. 
	///<	
	///< The user will be shown the full contents of the current folder, 
	///< plus user interface elements for navigating to other folders.

	bool set_uri(const char *uri);
	bool set_uri(const String& uri);
	///< Sets the file referred to by <EM>uri</EM> as the current file for the the file chooser.
	///< @param uri The URI to set as current. 
	///< @return <EM>true</EM> if both the folder could be changed and the URI was selected successfully.
	///<	 
	///< If the file name isn't in the current folder of chooser, then the current folder
	///< of the file chooser will be changed to the folder containing <EM>uri</EM>. This is 
	///< equivalent to a sequence of unselect_all() followed by select_uri(). 
	///<
	///< Note that the file must exist, or nothing will be done except for the directory change.
	///< To pre-enter a filename for the user, as in a save-as dialog, use set_current_name()

	bool select_uri(const char *uri);
	bool select_uri(const String& uri);
	///< Selects the file referred to by uri. 
	///< @param uri The URI to select. 
	///, @return <EM>true</EM> if both the folder could be changed and the URI was selected successfully.
	///<	
	///< If the URI doesn't refer to a file in the current folder of the file chooser, 
	///< then the current folder of chooser will be changed to the folder containing filename.

	void unselect_uri(const char *uri);
	void unselect_uri(const String& uri);
	///< Unselects the file referred to by <EM>uri</EM>. 
	///< @param uri The URI to unselect.
	///<	
	///< If the file is not in the current directory, does not exist,
	///< or is otherwise not currently selected, this method does nothing.

	bool set_current_folder_uri(const char *uri);
	bool set_current_folder_uri(const String& uri);
	///< Sets the current folder for the file chooser from a URI. 
	///< @param uri The URI for the new current folder. 
	///< @return <EM>true</EM> if the folder could be changed successfully, <EM>false</EM> otherwise.
	///< 	
	///< The user will be shown the full contents of the current folder, 
	///< plus user interface elements for navigating to other folders.

	void set_preview_widget(Widget& preview_widget);
	///< Sets an application-supplied widget to use to display a custom preview
	///< of the currently selected file. 
	///< @param preview_widget The widget for displaying a preview.
	///<	
	///< To implement a preview, after setting the preview widget, you connect to the
	///< "selection-changed" signal, and call get_preview_filename() or get_preview_uri()
	///< on each change. If you can display a preview of the new file, update your widget
	///< and set the preview active using set_preview_widget_active(). Otherwise, set the
	///< preview inactive. 
	///<
	///< When there is no application-supplied preview widget, or the application-supplied
	///< preview widget is not active, the file chooser may display an internally generated
	///< preview of the current file or it may display no preview at all.

	void set_preview_widget_active(bool active);
	///< Sets whether the preview widget set by set_preview_widget() should be shown
	///< for the current filename. 
	///< @param active Whether to display the user-specified preview widget.
	///<	
	///< When active is set to <EM>false</EM>, the file chooser may display an internally
	///< generated preview of the current file or it may display no preview at all.
	
	void set_use_preview_label(bool use_label);
	///< Sets whether the file chooser should display a stock label with the name
	///< of the file that is being previewed; the default is <EM>true</EM>. 
	///< @param use_label Whether to display a stock label with the name of the previewed file. 
	///<	
	///< Applications that want to draw the whole preview area themselves should set
	///< this to <EM>false</EM> and display the name themselves in their preview widget. 
	///<
	///< See also: set_preview_widget().

	void set_extra_widget(Widget& extra_widget);
	///< Sets an application-supplied widget to provide extra options to the user.
	///< @param extra_widget The widget for extra options.
				
	void add_filter(const FileFilter& filter);
	///< Adds filter to the list of filters that the user can select between. 
	///< @param filter A Gtk::FileFilter.
	///<	
	///< When a filter is selected, only files that are passed by that filter are displayed.

	void remove_filter(const FileFilter& filter);
	///< Removes filter from the list of filters that the user can select between.
	///< @param filter A Gtk::FileFilter.

	void set_filter(const FileFilter& filter);
	///< Sets the current filter; only the files that pass the filter will be displayed.
	///< @param filter A Gtk::FileFilter.
	///<
	///< If the user-selectable list of filters is non-empty, then the filter should
	///< be one of the filters in that list. Setting the current filter when the list of
	///< filters is empty is useful if you want to restrict the displayed set of files
	///< without letting the user change it.
	
	bool add_shortcut_folder(const char *folder, G::Error *error = 0);
	bool add_shortcut_folder(const std::string& folder, G::Error *error = 0);
	///< Adds a folder to be displayed with the shortcut folders in a file chooser. 
	///< @param folder The filename of the folder to add. 
	///< @param error The location to store any error, or null.
	///< @return <EM>true</EM> if the folder could be added successfully, <EM>false</EM> otherwise. 
	///<	
	///< Note that shortcut folders do not get saved, as they are provided by the application.
	///< For example, you can use this to add a "/usr/share/mydrawprogram/Clipart" folder to the
	///< volume list. 
	///<
	///< If the operation fails <EM>error</EM> will be set as appropriate.
	
	bool remove_shortcut_folder(const char *folder, G::Error *error = 0);
	bool remove_shortcut_folder(const std::string& folder, G::Error *error = 0);
	///< Removes a folder from a file chooser's list of shortcut folders.
	///< @param folder The filename of the folder to remove. 
	///< @param error The location to store any error, or null. 
	///< @return <EM>true</EM> if the operation succeeds, <EM>false</EM> otherwise.
	///<
	///< If the operation fails <EM>error</EM> will be set as appropriate (see add_shortcut_folder()).

	bool add_shortcut_folder_uri(const char *uri, G::Error *error = 0);
	bool add_shortcut_folder_uri(const String& uri, G::Error *error = 0);
	///< Adds a folder URI to be displayed with the shortcut folders in a file chooser.
	///< @param uri The URI of the folder to add. 
	///< @param error The location to store error, or null. 
	///< @return <EM>true</EM> if the folder could be added successfully, <EM>false</EM> otherwise. 
	///<	 
	///< Note that shortcut folders do not get saved, as they are provided by the application.
	///< For example, you can use this to add a "/usr/share/mydrawprogram/Clipart" folder
	///< to the volume list.
	///<
	///< If the operation fails <EM>error</EM> will be set as appropriate.

	bool remove_shortcut_folder_uri(const char *uri, G::Error *error = 0);
	bool remove_shortcut_folder_uri(const String& uri, G::Error *error = 0);
	///< Removes a folder URI from a file chooser's list of shortcut folders.
	///< @param uri The URI of the folder to remove. 
	///< @param error The location to store error, or null. 
	///< @return <EM>true</EM> if the operation succeeds, <EM>false</EM> otherwise.
	///<	
	///< If the operation fails <EM>error</EM> will be set as appropriate (see add_shortcut_folder_uri()).

/// @}
/// @name Signal Proxies
/// @{

	const CurrentFolderChangedSignalProxy signal_current_folder_changed();
	///< Connect to the activate_signal; emitted when the current folder in a
	///< FileChooser changes. This can happen due to the user performing some
	///< action that changes folders, such as selecting a bookmark or visiting
	///< a folder on the file list. It can also happen as a result of calling
	///< a function to explicitly change the current folder in a file chooser. 
	///<
	///< Normally you do not need to connect to this signal, unless you need
	///< to keep track of which folder a file chooser is showing. 
	///< 
	///< See also: set_current_folder(), get_current_folder(), set_current_folder_uri()
	///< and get_current_folder_uri().
	
	const FilerActivatedSignalProxy signal_file_activated();
	///< Connect to the activate_signal; emitted when the user "activates" a 
	///< file in the file chooser. This can happen by double-clicking on a file
	///< in the file list, or by pressing <EM>Enter</EM>. 
	///<
	///< Normally you do not need to connect to this signal. It is used internally by
	///< FileChooserDialog to know when to activate the default button in the dialog. 
	///<
	///< See also: get_filename(), get_filenames(), get_uri() and get_uris().
		
	const SelectionChangedSignalProxy signal_selection_changed();
	///< Connect to the activate_signal; emitted when there is a change in the set
	///< of selected files in a FileChooser. This can happen when the user modifies
	///< the selection with the mouse or the keyboard, or when explicitly calling
	///< functions to change the selection. 
	///<
	///< Normally you do not need to connect to this signal, as it is easier to wait
	///< for the file chooser to finish running, and then to get the list of selected
	///< files using the functions mentioned below. 
	///<
	///< See also: select_filename(), unselect_filename(), get_filename(), get_filenames(),
	///< select_uri(), unselect_uri(), get_uri() and get_uris().

	const UpdatePreviewSignalProxy signal_update_preview();
	///< Connect to the activate_signal; emitted when the preview in a file chooser
	///< should be regenerated. For example, this can happen when the currently selected
	///< file changes. You should use this signal if you want your file chooser to have
	///< a preview widget. 
	///<
	///< Once you have installed a preview widget with set_preview_widget(), you should
	///< update it when this signal is emitted. You can use the functions get_preview_uri()
	///< or get_preview_filename() to get the name of the file to preview. Your widget may
	///< not be able to preview all kinds of files; your callback must call 
	///< set_preview_wiget_active() to inform the file chooser about whether the preview
	///< was generated successfully or not. 
	///<
	///< See also: set_preview_widget(), set_preview_widget_active(), set_use_preview_label(),
	///< get_preview_filename() and get_preview_uri().

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/filechooser.inl>

#endif // XFC_GTK_FILE_CHOOSER_HH

