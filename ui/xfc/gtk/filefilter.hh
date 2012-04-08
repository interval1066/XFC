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

/// @file xfc/gtk/filefilter.hh
/// @brief A GtkFileFilter C++ wrapper interface.
///
/// Provides FileFilter, a filter for selecting a file subset. 

#ifndef XFC_GTK_FILE_FILTER_HH
#define XFC_GTK_FILE_FILTER_HH

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

#ifndef __GTK_FILE_FILTER_H__
#include <gtk/gtkfilefilter.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum FileFilterFlags
/// Used by Gtk::FileFilter::add_custom() to let GTK+ know what file information
/// needs to be retrieved. This avoids retrieving expensive information when it
/// isn't needed by your filter function.

enum FileFilterFlags
{
	FILE_FILTER_FILENAME = GTK_FILE_FILTER_FILENAME, ///< Get filename.
	FILE_FILTER_URI = GTK_FILE_FILTER_URI, ///< Get URI.
	FILE_FILTER_DISPLAY_NAME = GTK_FILE_FILTER_DISPLAY_NAME, ///< Get display name.
	FILE_FILTER_MIME_TYPE = GTK_FILE_FILTER_MIME_TYPE ///< Get mime type.
};

/// FileFilterFlagsField holds one or more values from the Gtk::FileFilterFlags enumeration OR'd together.

typedef unsigned int FileFilterFlagsField;

/// @struct FileFilterInfo filefilter.hh xfc/gtk/filefilter.hh
/// @brief A GtkFileFilterInfo C++ wrapper class.
///
/// FileFilterInfo stores the requested file information
/// that needs to be passed to a custom callback slot.
  
struct FileFilterInfo
{
	FileFilterFlagsField contains;
	String filename;
	String uri;
	String display_name;
	String mime_type;
};

/// @class FileFilter filefilter.hh xfc/gtk/filefilter.hh
/// @brief A GtkFileFilter C++ wrapper class.
///
/// FileFilter is a filter for selecting a file subset.

class FileFilter : public Object
{
	friend class G::Object;

	FileFilter(const FileFilter&);
	FileFilter& operator=(const FileFilter&);

protected:
/// @name Constructors
/// @{

	explicit FileFilter(GtkFileFilter *filter, bool owns_reference = false);
	///< Construct a new FileFilter from an existing GtkFileFilter.
	///< @param filter A pointer to a GtkFileFilter.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>filter</EM> can be a newly created GtkFileFilter or an existing
	///< GtkFileFilter (see G::Object::Object).

/// @}

public:
	typedef GtkFileFilter CObjectType;
	
	typedef sigc::slot<bool, const FileFilterInfo&> CustomSlot;
	///< Signature of the custom filter callback slot to be called to filter files.
	///<
	///< <B>Example:</B> Method signature for CustomSlot.
	///< @code
	///< bool method(const FileFilterInfo& filter_info);
	///< // filter_info: The file information as requested when the slot was added.
	///< @endcode

/// @name Constructors
/// @{

	FileFilter();
	///< Constructs a new file filter with no rules added to it. Such a filter
	///< doesn't accept any files, so is not particularly useful until you add
	///< rules with add_mime_type(), add_pattern(), or add_custom(). 
	///<
	///< <B>Example:</B> To create a filter that accepts any file, use:
	///< @code 
	///< Gtk::FileFilter *filter = new Gtk::FileFilter;
	///< filter->add_pattern("*");
	///< @endcode
 	
	virtual ~FileFilter();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkFileFilter* gtk_file_filter() const;
	///< Get a pointer to the GtkFileFilter structure.

	operator GtkFileFilter* () const;
	///< Conversion operator; safely converts an FileFilter to a GtkFileFilter pointer.

	String get_name() const;
	///< Gets the human-readable name for the filter (see set_name()).
	///< @return The human-readable name of the filter, or a null String. 

/// @}
/// @name Methods
/// @{

	void set_name(const char *name);
	void set_name(const String& name);
	///< Sets the human-readable name of the filter.
	///< @param name The human-readable-name for the filter, or null to remove any existing name. 
	///<	 
	///< This is the string that will be displayed in the file selector
	///< user interface if there is a selectable list of filters.
	///< @param name The human-readable-name for the filter, or null to remove any existing name. 

	void add_mime_type(const char *mime_type);
	void add_mime_type(const String& mime_type);
	///< Adds a rule allowing a given mime type to filter.
	///< @param mime_type The name of a MIME type (such as "image/png").

	void add_pattern(const char *pattern);
	void add_pattern(const String& pattern);
	///< Adds a rule allowing a shell style glob to filter.
	///< @param pattern A shell style glob (such as "*" for all files).

	void add_pixbuf_formats();
	///< Adds a rule allowing image files in the formats supported by Gdk::Pixbuf.
	
	void add_custom(FileFilterFlagsField needed, const CustomSlot& slot);
	///< Adds rule to the filter that allows files based on a custom callback slot.
	///< @param needed The bitfield of Gtk::FileFilterFlags indicating the 
	///<               information that the custom filter slot needs. 
	///< @param slot The callback slot; if the slot returns <EM>true</EM>, 
	///<             then the file will be displayed. 
	///<	 
	///< The bitfield <EM>needed</EM> which is passed in provides information about what
	///< sorts of information the filter function needs; this allows GTK+ to avoid retrieving
	///< expensive information when it isn't needed by the filter.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/filefilter.inl>

#endif // XFC_GTK_FILE_FILTER_HH

