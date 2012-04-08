/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//! @file xfc/sourceview/sourcelanguage.h
//! @brief A GtkSourceLanguage and GtkSourceLanguagesManager C++ wrapper interface.
//!
//! Provides SourceLanguage and SourceLanguageManager, two objects that implement
//! and manage the Gtk::SourceBuffer's language.

#ifndef XFC_GTK_SOURCE_LANGUAGE_H
#define XFC_GTK_SOURCE_LANGUAGE_H

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_GTK_SOURCE_TAG_HH
#include <xfc/sourceview/sourcetagstyle.hh>
#endif

#ifndef __GTK_SOURCE_LANGUAGE_H__
#include <gtksourceview/gtksourcelanguage.h>
#endif

#ifndef __GTK_SOURCE_LANGUAGES_MANAGER_H__
#include <gtksourceview/gtksourcelanguagesmanager.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {

class SourceStyleScheme;
class TextTag;

//! @class SourceLanguage sourcelanguage.h inti/gtk-sourceview/sourcelanguage.h
//! @brief A GtkSourceLanguage C++ wrapper class.
//!
//! SourceLanguage is an object that represents a SourceBuffer's language.

class SourceLanguage : public G::Object
{
	friend class G::Object;
	friend class SourceLanguageClass;

	SourceLanguage(const SourceLanguage&);
	SourceLanguage& operator=(const SourceLanguage&);

protected:
//! @name Constructors
//! @{

	explicit SourceLanguage(GtkSourceLanguage *language, bool reference = false);
	//!< Construct a new SourceLanguage from an existing GtkSourceLanguage.
	//!< @param language A pointer to a GtkSourceLanguage.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>language</EM> can be a newly created GtkSourceLanguage or an existing
	//!< GtkSourceLanguage (see G::Object::Object).

//! @}
//  Signals

	typedef G::Signal1<void, const char*> TagStyleChangedSignalType;
	typedef G::SignalProxy<TypeInstance, TagStyleChangedSignalType> TagStyleChangedSignalProxy;
	static const TagStyleChangedSignalType tag_style_changed_signal;

public:
//! @name Constructors
//! @{

	virtual ~SourceLanguage();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceLanguage* gtk_source_language() const { return reinterpret_cast<GtkSourceLanguage*>(instance_); }
	//!< Get a pointer to the GtkSourceLanguage structure.

	GtkSourceLanguageClass* gtk_source_language_class() const;
	//!< Get a pointer to the GtkSourceLanguageClass structure.

	operator GtkSourceLanguage* () const;
	//!< Conversion operator; safely converts a SourceLanguage to a GtkSourceLanguage pointer.

	bool is_gtk_source_language() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_LANGUAGE.

//! @}
//! @name Accessors
//! @{

	String get_id() const;
	//!< Returns the ID of the language (ID is not locale-dependent).

	String get_name() const;
	//!< Returns the name of the language from the language specification file (.lang)
	//!< or a null String if no language name can be retrieved.

	String get_section() const;
	//!< Returns the name of the section from the language specification file (.lang)
	//!< or a null String if no section name can be retrieved.

	bool get_tags(std::vector<Pointer<TextTag> >& tags) const;
	//!< Gets a list of the available source tags.
	//!< @param tags A vector of TextTag smart pointers to hold the source tags.
	//!< @return <EM>true</EM> if <EM>tags</EM> is not empty.

	G::Unichar get_escape_char() const;
	//!< Returns the escape character used for syntax delimiters.

	bool get_mime_types(std::vector<String>& mime_types) const;
	//!< Gets a list of the mime types set by set_mime_types().
	//!< @param mime_types A vector of String to hold the mime types.
	//!< @return <EM>true</EM> if <EM>mime_types</EM> is not empty.

	SourceStyleScheme* get_style_scheme() const;
	//!< Returns the style scheme currently used by the language.

	SourceTagStyle* get_tag_style(const String& tag_id) const;
	//!< Gets the SourceTagStyle used by <EM>tag_id</EM>.
	//!< @param tag_id The tag ID.
	//!< @return A pointer to the SourceTagStyle.

	SourceTagStyle* get_tag_default_style(const String& tag_id) const;
	//!< Get the default style for <EM>tag_id</EM>.
	//!< @param tag_id The tag ID.
	//!< @return A pointer to the default SourceTagStyle.

//! @}
//! @name Methods
//! @{

	void set_mime_types(const std::vector<String>& mime_types);
	//!< Set the mime types.
	//!< @param mime_types A vector of String holding the mime types

	void set_style_scheme(SourceStyleScheme& scheme);
	//!< Set the style scheme used by the language.
	//!< @param scheme The new SourceStyleScheme.

	void set_tag_style(const String& tag_id, const SourceTagStyle& style);
	//!< Set the style of the tag whose ID is <EM>tag_id</EM>.
	//!< @param tag_id The ID identifying the source tag.
	//!< @param style The new SourceTagStyle.

//! @}
//! @name Signal Proxies
//! @{

	const TagStyleChangedSignalProxy sig_tag_style_changed()
	{
		return TagStyleChangedSignalProxy(this, &tag_style_changed_signal);
	}
	//!< Connect to the tag_style_changed_signal; emitted when a tag style is changed.

//! @}
};

//! @class SourceLanguagesManager sourcelanguage.h inti/gtk-sourceview/sourcelanguage.h
//! @brief A GtkSourceLanguagesManager C++ wrapper class.
//!
//! SourceLanguagesManager is an object that manages a SourceBuffer's languages.

class SourceLanguagesManager : public G::Object
{
	friend class G::Object;

	SourceLanguagesManager(const SourceLanguagesManager&);
	SourceLanguagesManager& operator=(const SourceLanguagesManager&);

protected:
//! @name Constructors
//! @{

	explicit SourceLanguagesManager(GtkSourceLanguagesManager *lm, bool reference = false);
	//!< Construct a new SourceLanguagesManager from an existing GtkSourceLanguagesManager.
	//!< @param lm A pointer to a GtkSourceLanguagesManager.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>lm</EM> can be a newly created GtkSourceLanguagesManager or an existing
	//!< GtkSourceLanguagesManager (see G::Object::Object).

//! @}
//  Properties

	typedef G::Property<GSList*> LangSpecsDirsPropertyType;
	typedef G::PropertyProxy<G::Object, LangSpecsDirsPropertyType> LangSpecsDirsPropertyProxy;
	static const LangSpecsDirsPropertyType lang_specs_dirs_property;

public:
//! @name Constructors
//! @{

	SourceLanguagesManager();
	//!< Construct a new source languages manager object.

	virtual ~SourceLanguagesManager();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceLanguagesManager* gtk_source_languages_manager() const { return reinterpret_cast<GtkSourceLanguagesManager*>(instance_); }
	//!< Get a pointer to the GtkSourceLanguagesManager structure.

	operator GtkSourceLanguagesManager* () const;
	//!< Conversion operator; safely converts a SourceLanguagesManager to a GtkSourceLanguagesManager pointer.

	bool is_gtk_source_languages_manager() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_LANGUAGES_MANAGER.

//! @}
//! @name Accessors
//! @{

	bool get_available_languages(std::vector<SourceLanguage*>& languages) const;
	//!< Get a list of the available source languages.
	//!< @param languages A vector of SourceLanguage pointers to hold the available languages.
	//!< @return <EM>true</EM> if <EM>languages</EM> is not empty.

	SourceLanguage* get_language_from_mime_type(const String& mime_type) const;
	//!< Get the SourceLanguage object for <EM>mime_type</EM>.
	//!< @param mime_type The mime type.
	//!< @return The SourceLanguage.

	Gtk::SourceLanguage* get_language_from_name(const String& language) const;
	//!< Get the SourceLanguage object for <EM>language</EM>.
	//!< @param language The name of the language.
	//!< @return The SourceLanguage.
	//!<
	//!< <BR>The names for the currently supported languages are: Ada, C, C++, Diff, .desktop,
	//!< HTML, IDL, Java, Latex, Perl, gettext translation, Python, XML.

	bool get_lang_files_dirs(std::vector<String>& dirs) const;
	//!< Get a list of the directories where language specifications are kept.
	//!< @param dirs A vector of String to hold the directories.
	//!< @return <EM>true</EM> if <EM>dirs</EM> is not empty.

//! @}
//! @name Property Proxies
//! @{

	const LangSpecsDirsPropertyProxy property_lang_specs_dirs()
	{
		return LangSpecsDirsPropertyProxy(this, &lang_specs_dirs_property);
	}
	//!< A list of directories where the language specification files (.lang)
	//!< are located (GSList* : Read / Write / Construct Only).

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_LANGUAGE_H

