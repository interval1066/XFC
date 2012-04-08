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

/// @file xfc/gtk/rc.hh
/// @brief A GtkRcStyle  C++ wrapper interface.
///
/// GTK+ provides a resource file mechanism for configuring various aspects of the operation
/// of a GTK+ program at runtime. XFC wraps the API for managing resource files into a one
/// convenient class, called RC.

#ifndef XFC_GTK_RC_HH
#define XFC_GTK_RC_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_RC_H__
#include <gtk/gtkrc.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Quark;
class Scanner;
}

namespace Gdk {
class Color;
class Colormap;
class Pixmap;
}

namespace Pango {
class FontDescription;
}

namespace Gtk {

class Settings;
class Style;
class Widget;

/// @class RC rc.hh xfc/gtk/rc.hh
/// @brief A C++ wrapper class for the various resource file functions.
///
/// GTK+ provides a resource file mechanism for configuring various aspects of the operation
/// of a GTK+ program at runtime. XFC wraps the API for managing resource files into a one
/// convenient class, called RC.
///
/// <B>Default files</B>
/// 
/// An application can cause GTK+ to parse a specific RC file by calling Gtk::RC::parse(). In
/// addition to this, certain files will be read at the end of Main::init(). Unless modified,
/// the files looked for will be \<SYSCONFDIR\>/gtk-2.0/gtkrc and .gtkrc-2.0 in the users home
/// directory. (\<SYSCONFDIR\> defaults to /usr/local/etc. It can be changed with the --prefix
/// or --sysconfdir options when configuring GTK+.)
/// 
/// The set of these default files can be retrieved with Gtk::RC::get_default_files() and modified
/// with Gtk::RC::add_default_file() and Gtk::RC::set_default_files(). Additionally, the 
/// GTK2_RC_FILES environment variable can be set to a G_SEARCHPATH_SEPARATOR_S-separated list of
/// files in order to overwrite the set of default files at runtime.
///
/// For each RC file, in addition to the file itself, GTK+ will look for a locale-specific file
/// that will be parsed after the main file. For instance, if LANG is set to ja_JP.ujis, when
/// loading the default file ~/.gtkrc then GTK+ looks for ~/.gtkrc.ja_JP and ~/.gtkrc.ja, and 
/// parses the first of those that exists.
///
/// For information on writing RC files, see the GTK+ reference documentation: Resource Files.

class RC
{
public:
/// @name Accessors
/// @{

	static std::vector<String> get_default_files();
	///< Retrieves the current list of RC files that will be parsed at the end of Main::init().
	///< @return A vector of String that holds the list of filenames.

	static Style* get_style_by_paths(const Settings& settings, const char *widget_path, const char *class_path, GType type);
	static Style* get_style_by_paths(const Settings& settings, const String& widget_path, const String& class_path, GType type);
	///< Creates a Style from styles defined in a RC file by providing the raw components used in matching.
	///< @param settings A Settings object.
	///< @param widget_path The widget path to use when looking up the style, or null
	///<                    if no matching against the widget path should be done.
	///< @param class_path The class path to use when looking up the style, or null
	///<                   if no matching against the class path should be done.
	///< @param type A type that will be used along with parent types of this type
	///<             when matching against class styles, or G_TYPE_NONE
	///< @return A style created by matching with the supplied paths, or null if nothing matching
	///< was specified and the default style should be used.
	///<
	///< This function may be useful when creating pseudo-widgets that should be themed
	///< like widgets but don't actually have corresponding GTK+ widgets. An example of this
	///< would be items inside a GNOME canvas widget. The returned value is owned by GTK+ as
	///< part of an internal cache, so you must call ref() on the returned value if you want
	///< to keep a reference to it.

	static String get_theme_dir();
	///< Returns the standard directory in which themes should be installed (GTK+ does not actually
	///< use this directory itself).
	///< @return The directory.

	static String get_module_dir();
	///< Returns a directory in which GTK+ looks for theme engines. 
	///< @return The directory.
	///<
	///< For full information about the search for theme engines, see the docs for GTK_PATH
	///< in Running GTK+ Applications(3).
	
	static String get_im_module_file();
	///< Obtains the path to the IM modules file (see the documentation of the
	///< GTK_IM_MODULE_FILE environment variable for more details).
	///< @return A String containing the name of the file listing the IM modules available for loading.

	static Style* get_style(const Widget& widget);
	///< Finds all matching RC styles for a given widget, composites them together, and then creates
	///< a Style representing the composite appearance. 
	///< @param widget A GtkWidget.
	///< @return The resulting style.
	///<
	///< GTK+ actually keeps a cache of previously created styles, so a new style may not
	///< be created. No refcount is added to the returned style, so if you want to save this
	///< style, you should add a reference yourself.

	static Pointer<G::Scanner> get_scanner();
	///< Returns a properly initialized RC scanner.

/// @}
/// @name Methods
/// @{

	static void add_default_file(const char *filename);
	static void add_default_file(const String& filename);
	///< Adds a file to the list of files to be parsed at the end of Main::init().
	///< @param filename  The pathname to the file. 
	///<
	///< If filename is not absolute, it is searched in the current directory.

	static void set_default_files(const std::vector<String>& filenames);
	///< Sets the list of files that will be read at the end of Main::init().
	///< @param filenames A vector of String that holds the list of filenames.
	
	static void parse(const char *filename);
	static void parse(const String& filename);
	///< Parses a given resource file.
	///< @param filename  The name of a file to parse. 
	///< 
	///< If filename is not absolute, it is searched for in the current directory.

	static void parse_string(const char *rc_string);
	static void parse_string(const String& rc_string);
	///< Parses resource information directly from a string.
	///< @param rc_string A string to parse.

	static bool reparse_all();
	///< If the modification time on any previously read file for the default Settings has changed,
	///< discard all style information and then reread all previously read RC files.
	///< @return <EM>true</EM> if the files were reread.

	static bool reparse_all_for_settings(const Settings& settings, bool force_load);
	///< If the modification time on any previously read file for the default Settings has changed,
	///< discard all style information and then reread all previously read RC files.
	///< @param settings A Settings object.
	///< @param force_load If <EM>true</EM> load whether or not anything changed.
	///< @return <EM>true</EM> if the files were reread.

	static void reset_styles(const Settings& settings);
	///< Recomputes the styles for all widgets that use a particular Settings object.
	///< @param settings A Settings object.
	///<
	///< There is one Gtk::Settings object per Gdk::Screen (see Gtk::Settings::get_for_screen()).
	///< This method is useful when some global parameter has changed that affects the appearance 
	///< of all widgets, because when a widget gets a new style, it will both redraw and recompute
	///< any cached information about its appearance. As an example, it is used when the default 
	///< font size set by the operating system changes. Note that this function doesn't affect 
	///< widgets that have a style set explicitely on them with Gtk::Widget::set_style().

	static String find_pixmap_in_path(const Settings& settings, const char *pixmap_file, const G::Scanner *scanner = 0);
	static String find_pixmap_in_path(const Settings& settings, const String& pixmap_file, const G::Scanner *scanner = 0);
	///< Looks up a file in pixmap path for the specified Settings.
	///< @param settings A Settings object.
	///< @param pixmap_file The name of the pixmap file to locate.
	///< @param scanner A scanner used to get line number information for the warning message, or null.
	///< @return The filename.
	///<
	///< If the file is not found, it outputs a warning message using g_warning() and returns a null String.

	static unsigned int parse_color(const G::Scanner& scanner, Gdk::Color& color);
	///< Parses a color in the format expected in a RC file.
	///< @param scanner A Scanner.
	///< @param color A reference to a Gdk::Color that will to store the result.
	///< @return G_TOKEN_NONE if parsing succeeded, otherwise the token that was expected but not found.

	static unsigned int parse_state(const G::Scanner& scanner, StateType& state);
	///< Parses a StateType variable from the format expected in a RC file.
	///< @param scanner A Scanner (must be initialized for parsing an RC file)
	///< @param state A reference to a StateType variable in which to store the result.
	///< @return G_TOKEN_NONE if parsing succeeded, otherwise the token that was expected but not found.

/// @}
};

/// @class RcStyle rc.hh xfc/gtk/rc.hh
/// @brief A GtkRcStyle C++ wrapper class.
///
/// The RcStyle structure is used to represent a set of information about the appearance of a widget.
/// This can later be composited together with other RcStyle structures to form a Style.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class RcStyle : public G::Object
{
	friend class G::Object;

	RcStyle(const RcStyle& src);
	RcStyle& operator=(const RcStyle& src);

protected:
/// @name Constructors
/// @{

	explicit RcStyle(GtkRcStyle *rc_style, bool owns_reference = true);
	///< Construct a new RcStyle from an existing GtkRcStyle.
	///< @param rc_style A pointer to a GtkRcStyle.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>rc_style</EM> can be a newly created GtkRcStyle or an existing
	///< GtkRcStyle (see G::Object::Object).

/// @}

public:
	typedef GtkRcStyle CObjectType;

/// @name Constructors
/// @{

	RcStyle();
	///< Constructs a new RcStyle with no fields set and a reference count of 1
	///< that the caller owns.
	
	virtual ~RcStyle();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkRcStyle* gtk_rc_style() const;
	///< Get a pointer to the GtkRcStyle structure.

	operator GtkRcStyle* () const;
	///< Conversion operator; safely converts a RcStyle to a GtkRcStyle pointer.
	
	String name() const;
	///< Gets the name of the RC style.
	///< @return The name of the RC style, or a null string if a name has not been set.  

	String bg_pixmap_name(StateType state_type) const;
	///< Gets the name of the pixmap used as the background for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The name of the background pixmap, or a null string if a pixmap name has not been set.  

	Pointer<Pango::FontDescription> font_description() const;
	///< Gets the font description for the RC style.
	///< @return A Pango::FontDescription.

	Gdk::Color fg(StateType state_type) const;
	///< Gets the foreground color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	bool fg_set(StateType state) const;
	///< Determines whether the foreground color for <EM>state_type</EM> is set.
	///< @return <EM>true</EM> if the foreground color is set.
	
	Gdk::Color bg(StateType state_type) const;
	///< Gets the background color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	bool bg_set(StateType state) const;
	///< Determines whether the background color for <EM>state_type</EM> is set.
	///< @return <EM>true</EM> if the background color is set.
	
	Gdk::Color text(StateType state_type) const;
	///< Gets the text color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	bool text_set(StateType state) const;
	///< Determines whether the text color for <EM>state_type</EM> is set.
	///< @return <EM>true</EM> if the text color is set.
	
	Gdk::Color base(StateType state_type) const;
	///< Gets the base color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	bool base_set(StateType state) const;
	///< Determines whether the base color for <EM>state_type</EM> is set.
	///< @return <EM>true</EM> if the base color is set.

	int xthickness() const;
	///< Obtains the current value used for various horizontal padding values in GTK+,
	///< such as frame and bevel size.
	///< @return The current horizontal padding value.

	int ythickness() const;
	///< Obtains the current value used for various vertical padding values in GTK+,
	///< such as frame and bevel size.
	///< @return The current vertical padding value.
  
/// @}
/// @name Methods
/// @{

	Pointer<RcStyle> copy() const;
	///< Makes a copy of the specified RcStyle. This method will correctly copy
	///< an RC style that is a member of a class derived from RcStyle.
	
	void set_name(const char *name);
	void set_name(const String& name);
	///< Sets the name of the RC style.
	///< @param name The new name for the RC style, or null to unset the current name.

	void set_bg_pixmap_name(StateType state_type, const char *name);
	void set_bg_pixmap_name(StateType state_type, const String& name);
	///< Sets the name of the pixmap to use as the background for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param name The new pixmap name, or null to unset the current pixmap name.

	void set_font_description(const Pango::FontDescription *font_desc) const;
	///< Sets the font description for the RC style.
	///< @param font_desc The new font description, or null to unset the current font description.

	void set_fg(StateType state_type, const Gdk::Color& color);
	///< Sets the foreground color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
	
	void unset_fg(StateType state_type);
	///< Unsets the foreground color for <EM>state_type</EM>. 
	///< @param state_type One of the values in the Gtk::StateType enumeration.

	void set_bg(StateType state_type, const Gdk::Color& color);
	///< Sets the background color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
	
	void unset_bg(StateType state_type);
	///< Unsets the background color for <EM>state_type</EM>. 
	///< @param state_type One of the values in the Gtk::StateType enumeration.

	void set_text(StateType state_type, const Gdk::Color& color);
	///< Sets the text color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
	
	void unset_text(StateType state_type);
	///< Unsets the text color for <EM>state_type</EM>. 
	///< @param state_type One of the values in the Gtk::StateType enumeration.

	void set_base(StateType state_type, const Gdk::Color& color);
	///< Sets the base color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
	
	void unset_base(StateType state_type);
	///< Unsets the base color for <EM>state_type</EM>. 
	///< @param state_type One of the values in the Gtk::StateType enumeration.

	void set_xthickness(int size);
	///< Sets the current value used for various horizontal padding values in GTK+,
	///< such as frame and bevel size
	///< @param size The new horizontal padding value.

	void set_ythickness(int size);
	///< Sets the current value used for various vertical padding values in GTK+,
	///< such as frame and bevel size
	///< @param size The new vertical padding value.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/rc.inl>

#endif // XFC_GTK_RC_HH

