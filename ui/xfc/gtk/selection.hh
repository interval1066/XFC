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
 
/// @file xfc/gtk/selection.hh
/// @brief A GtkSelectionData, GtkTargetEntry and GtkTargetList C++ wrapper interface.
///
/// The selection mechanism provides the basis for different types of communication
/// between processes. In particular, drag-and-drop and Clipboard work via selections.
/// You will very seldom or never need to use most of the functions in this section
/// directly; Clipboard provides a nicer interface to the same functionality. Some of
/// the datatypes defined this section are used in the Clipboard and drag-and-drop
/// API's as well. 

#ifndef XFC_GTK_SELECTION_HH
#define XFC_GTK_SELECTION_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_GTK_DND_HH
#include <xfc/gtk/dnd.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Display;
class Pixbuf;
}

namespace Gtk {
	
class TreeModel;
class TreePath;
	
/// @class SelectionData selection.hh xfc/gtk/selection.hh
/// @brief A GtkSelectionData C++ wrapper class.
///
/// The selection mechanism provides the basis for different types of communication
/// between processes. In particular, drag-and-drop and Clipboard work via selections.
/// You will very seldom or never need to use most of the functions in this section
/// directly; Clipboard provides a nicer interface to the same functionality. Some of
/// the datatypes defined in this section are used in the Clipboard and drag-and-drop
/// API's as well. 
///
/// The SelectionData object is used to store a chunk of data along with the data type
/// and other associated information. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/selections.html">Selection</A> HOWTO and example.

class SelectionData : public G::Boxed
{
	SelectionData(const SelectionData&);
	SelectionData& operator=(const SelectionData&);

public:
/// @name Constructors
/// @{

	explicit SelectionData(GtkSelectionData *data);
	///< Construct a new SelectionData from an existing GtkSelectionData.
	///< @param data A pointer to a GtkSelectionData.
	///<
	///< The <EM>data</EM> can be a newly created GtkSelectionData or an existing
	///< GtkSelectionData. The SelectionData object created is a temporary object. It
	///< doesn't take over the ownership of GtkSelectionData and GtkSelectionData is 
	///< not freed by the destructor.

	SelectionData(GtkSelectionData *data, bool copy);
	///< Construct a new SelectionData from an existing GtkSelectionData.
	///< @param data A pointer to a GtkSelectionData.
	///< @param copy Whether the SelectionData object should make a copy of GtkSelectionData or not. 
	///<
	///< The <EM>data</EM> can be a newly created GtkSelectionData or an existing GtkSelectionData.
	///< If <EM>copy</EM> is true SelectionData will make a copy of GtkSelectionData. If <EM>copy</EM>
	///< is false SelectionData wont make a copy but instead takes over the ownership of GtkSelectionData.
	///< Either way, the destructor will free GtkSelectionData when the SelectionData object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GtkSelectionData objects in a C++ wrapper.
	
	~SelectionData();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkSelectionData* gtk_selection_data() const;
	///< Get a pointer to the GtkSelectionData structure.

	bool is_valid() const;
	///< Returns true if the length of the data is >= zero; false indicates the data should be ignored.

	Gdk::Atom selection() const;
	///< Returns an atom that defines which selection this data belongs to.

	String get_selection() const;
	///< Returns a string corresponding to the atom that defines which selection this data belongs to.

	Gdk::Atom target() const;
	///< Returns an atom that defines which target has been requested.

	String get_target() const;
	///< Returns a string corresponding to the atom that defines which target has been requested.

	Gdk::Atom type() const;
	///< Returns an atom that defines what type the received data has been converted to.

	String get_type() const;
	///< Returns a string corresponding to the atom that defines what type the received data has been converted to.

	int format() const;
	///< Returns the number of bits that are required to store one element of the target type.

	unsigned char* data() const;
	///< Returns a pointer to the data that has been provided.

	int length() const;
	///< Returns the length in bytes of the data that has been provided.

	Gdk::Display* display() const;
	///< Returns the Gdk::Display where the selection is set.
	
	String get_text() const;
	///< Gets the contents of the selection data as a UTF-8 string.
	///< @return If the selection data contained a recognized text type and it could be
	///< converted to UTF-8, a String containing the converted text, otherwise a null String.

	Pointer<Gdk::Pixbuf> get_pixbuf() const;
	///< Gets the contents of the selection data as a Gdk::Pixbuf.
	///< @return A smart pointer to a Gdk::Pixbuf.
	///<	
	///< If the selection data contained a recognized image type and it could be converted
	///< to a Gdk::Pixbuf, a pixbuf is returned, otherwise a null pointer is returned. 
	
	std::vector<String> get_uris() const;
	///< Gets the contents of the selection data as a vector of URI Strings.
	///< @return A vector of String that holds the URIs.
	///<
	///< If the selection data contained no URIs the returned vector of String will be empty.
	
	bool get_targets(std::vector<Gdk::Atom>& targets) const;
	///< Gets the contents of the selection data as a vector of Gdk::Atom that defines the targets available.
	///< @param targets A reference to a vector of Gdk::Atom to store the list of targets.
	///< @return <EM>true</EM> if selection data contains a valid targets, otherwise <EM>false</EM>.
	///<
	///< This can be used to interpret the results of getting the standard <EM>TARGETS</EM>
	///< target that is always supplied for any selection.

	bool get_targets(std::vector<String>& targets) const;
	///< Gets the contents of the selection data as a vector of String corresponding to the atoms
	///< that define the targets available.
	///< @param targets A reference to a vector of String to store the names of targets.
	///< @return <EM>true</EM> if selection data contains a valid targets, otherwise <EM>false</EM>.
	///<
	///< This can be used to interpret the results of getting the standard <EM>TARGETS</EM>
	///< target that is always supplied for any selection.

	bool targets_include_text() const;
	///< Returns true if any of the targets can be used to provide text.

	bool targets_include_image(bool writable) const;
	///< Given a Gtk::SelectionData object holding a list of targets, determines
	///< if any of the targets in targets can be used to provide a Gdk::Pixbuf.
	///< @param writable Whether to accept only targets for which GTK+ knows
	///<                 how to convert a pixbuf into the format 
	///< @return <EM>true</EM> if the selection data holds a list of targets, and a 
	///<         suitable target for images is included, otherwise <EM>false</EM>. 
	
/// @}
/// @name Methods
/// @{

	void set(Gdk::Atom type, int format, const void *data, int length);
	///< Stores new data in this SelectionData object. 
	///< @param type The type of selection data.
	///< @param format The format (number of bits in a unit).
	///< @param data The pointer to the data (will be copied).
	///< @param length The length of the data.
	///<
	///< Should only be called from a selection handler callback. Zero-terminates the stored data.

	bool set_text(const char *str);
	bool set_text(const String& str);
	///< Sets the contents of the selection from a UTF-8 encoded string. The string is converted to
	///< the form determined by target().
	///< @param str A UTF-8 string.
	///< @return <EM>true</EM> if the selection was successfully set, otherwise <EM>false</EM>.

	bool set_pixbuf(Gdk::Pixbuf& pixbuf);
	///< Sets the contents of the selection from a Gdk::Pixbuf.
	///< @param pixbuf A Gdk::Pixbuf 
	///< @return <EM>true</EM> if the selection was successfully set, otherwise <EM>false</EM>.
	///<	 
	///< The pixbuf is converted to the form determined by selection_data->target.
	
	bool set_uris(const std::vector<String>& uris);
	///< Sets the contents of the selection from a list of URIs. 
	///< @param uris A vector of String holding the URIs. 
	///< @return <EM>true</EM> if the selection was successfully set, otherwise <EM>false</EM>. 
	///<	
	///< The strings are converted to the form determined by selection_data->target.

/// @}
/// @name Drag-and-Drop Methods
/// @{

	bool get_row_drag_data(TreeModel **model, Pointer<TreePath> *path) const;
	///< Obtains a <EM>model</EM> and <EM>path</EM> from selection data of target type GTK_TREE_MODEL_ROW.
	///< @param model A pointer to a TreeModel pointer.
	///< @param path A pointer to a smart TreePath pointer to hold the path to a row in <EM>tree_model</EM>.
	///< @return <EM>true</EM> if SelectionData had target type GTK_TREE_MODEL_ROW and is otherwise valid.
	///<
	///< Normally called from a <EM>drag_data_received</EM> handler. This method can only
	///< be used if SelectionData originates from the same process that's calling this method,
	///< because a pointer to the tree model is being passed around. If you aren't in the same
	///< process, then you'll get memory corruption. In the TreeDragDest <EM>drag_data_received</EM>
	///< handler, you can assume that SelectionData of type GTK_TREE_MODEL_ROW is from the current
	///< process. If the target type is wrong this method returns false.

	bool set_row_drag_data(TreeModel& tree_model, const TreePath& path);
	///< Sets selection data of target type GTK_TREE_MODEL_ROW.
	///< @param tree_model A reference to a TreeModel.
	///< @param path A row in <EM>tree_model</EM>.
	///< @return <EM>true</EM> if the SelectionData had the proper target type to allow us to set a tree row.
 	///<
	///< Normally used in a <EM>drag_data_get</EM> handler. If the target type is wrong
	///< this method returns false.

/// @}
};

/// @class TargetEntry selection.hh xfc/gtk/selection.hh
/// @brief A GtkTargetEntry C++ wrapper class.
///
/// The selection mechanism provides the basis for different types of communication
/// between processes. In particular, drag-and-drop and Clipboard work via selections.
/// You will very seldom or never need to use most of the functions in this section
/// directly; Clipboard provides a nicer interface to the same functionality. Some of
/// the datatypes defined this section are used in the Clipboard and drag-and-drop
/// API's as well. 
///
/// The TargetEntry structure represents an entry in a TargetList of data types that
/// are supported when sending or receiving data.  
///
/// <B>See also:</B> the <A HREF="../../howto/html/selections.html">Selection</A> HOWTO and example.

class TargetEntry
{
	GtkTargetEntry entry_;

public:
/// @name Constructors
/// @{

	TargetEntry();
	///< Contruct an empty TargetEntry.

	TargetEntry(const char *target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags = 0);
	TargetEntry(const String& target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags = 0);
	///< Contruct a TargetEntry with the specified values.
	///< @param target_name The name of the target.
	///< @param unique_id A unique application-specific integer.
	///< @param drag_flags Either TARGET_SAME_APP or TARGET_SAME_WIDGET.
	///<
	///< The <EM>drag_flags</EM> field is used to restrict the validity of the
	///< corresponding target to the same applcaiton of the same widget.
	
/// @}
/// @name Accessors
/// @{

	GtkTargetEntry* gtk_target_entry() const;
	///< Get a pointer to the GtkTargetEntry structure.

	const char* target() const;
	///< Returns the string containing the name of the target. The string is owned by the TargetEntry.

	unsigned int flags() const;
	///< Only used in drag-and-drop to indicate a drag-and-drop within the 
	///< same application or the same widget.
	///< @return The flags value, either TARGET_SAME_APP or TARGET_SAME_WIDGET.

	unsigned int info() const;
	///< An application specific integer that will be passed back through signals later on.
	///< This allows additional information to be attached to the target.
	
/// @}
/// @name Methods
/// @{

	void set(const char *target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags = 0);
	void set(const String& target_name, unsigned int unique_id, Gtk::TargetFlagsField drag_flags = 0);
	///< Sets the TargetEntry values.
	///< @param target_name The name of the target.
	///< @param unique_id A unique application-specific integer.
	///< @param drag_flags Either TARGET_SAME_APP or TARGET_SAME_WIDGET.
	///<
	///< The <EM>drag_flags</EM> field is used to restrict the validity of the
	///< corresponding target to the same application or the same widget.
	
/// @}
};

/// @class TargetList selection.hh xfc/gtk/selection.hh
/// @brief A GtkTargetList C++ wrapper class.
///
/// The selection mechanism provides the basis for different types of communication
/// between processes. In particular, drag-and-drop and Clipboard work via selections.
/// You will very seldom or never need to use most of the functions in this section
/// directly; Clipboard provides a nicer interface to the same functionality. Some of
/// the datatypes defined this section are used in the Clipboard and drag-and-drop
/// API's as well. 
///
/// The TargetList structure represents a list of data types that are supported when
/// sending or receiving data. TargetList is only useful when you want to manually
/// initiate drag and drop to have dynamic control.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/selections.html">Selection</A> HOWTO and example.

class TargetList : public Xfc::Object
{
	TargetList(const TargetList& src);
	TargetList& operator=(const TargetList& src);
	
	GtkTargetList *target_list_;
	
public:
/// @name Constructors
/// @{

	TargetList(); 
	///< Construct an empty target list with a reference count of 1 that the caller owns.

	TargetList(const std::vector<TargetEntry>& targets);
	///< Construct a target list that contains the target entries in targets.
	///< @param targets The vector of TargetEntry to add into the target list.
	///<
	///< The TargetList is created with a reference count of 1 that the caller owns.

	TargetList(GtkTargetList *target_list);
	///< Constructs a new TargetList from an existing GtkTargetList.
	///< @param target_list A newly created GtkTargetList with a reference count of 1.
	///<
	///< TargetList takes over the ownership of the GtkTargetList reference count,
	///< unreferencing the GtkTargetList when it is destroyed. 
	
	virtual ~TargetList();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkTargetList* gtk_target_list() const;
	///< Get a pointer to the GtkTargetList structure.

	operator GtkTargetList* () const;
	///< Conversion operator; safely converts a TargetList to a GtkTargetList pointer.
	
/// @}
/// @name Methods
/// @{

	void add(Gdk::Atom target, unsigned int flags, unsigned int info);
	///< Adds a target to the TargetList.
	///< @param target The interned atom representing the target.
	///< @param flags The flags for this target.
	///< @param info An ID that will be passed back to the application.

	void add(const TargetEntry& entry);
	///< Adds a TargetEntry to the target list.
	///< @param entry The TargetEntry to add.

	void add(const std::vector<TargetEntry>& targets);
	///< Adds a vector of TargetEntry to the target list.
	///< @param targets The vector of TargetEntry to add.

	void add_text_targets(unsigned int info);
	///< Adds the text targets supported by GTK+ selection to the target list. 
	///< @param info An ID that will be passed back to the application.
	///<		
	///< All targets are added with the same info.

	void add_image_targets(unsigned int info, bool writable);
	///< Adds the image targets supported by GTK+ selection to the target list. 
	///< @param info An ID that will be passed back to the application.
	///< @param writable Whether to add only targets for which GTK+ knows 
	///<                 how to convert a pixbuf into the format.
	///<		
	///< All targets are added with the same info.

	void add_uri_targets(unsigned int info);
	///< Adds the URI targets supported by GTK+ selection to the target list. 
	///< @param info An ID that will be passed back to the application.
	///<		
	///< All targets are added with the same info.
	
	void remove(Gdk::Atom target);
	///< Removes a target from a target list.
	///< @param target The interned atom representing the target.

	bool find(Gdk::Atom target, unsigned int *info);
	///< Looks up a given target in the target list.
	///< @param target An interned atom representing the target to search for.
	///< @param info A pointer to the location to store application info for target.
	///< @return <EM>true</EM> if the target was found, otherwise <EM>false</EM>.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/selection.inl>

#endif // XFC_GTK_SELECTION_HH

