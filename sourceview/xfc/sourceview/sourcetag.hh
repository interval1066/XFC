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

//! @file xfc/sourceview/sourcetag.h
//! @brief A GtkSourceTag and GtkSourceTagTable C++ wrapper interface.

#ifndef XFC_GTK_SOURCE_TAG_HH
#define XFC_GTK_SOURCE_TAG_HH

#ifndef XFC_GTK_TEXT_TAG_HH
#include <xfc/gtk/texttag.hh>
#endif

#ifndef __GTK_SOURCE_TAG_H__
#include <gtksourceview/gtksourcetag.h>
#endif

#ifndef __GTK_SOURCE_TAG_TABLE_H__
#include <gtksourceview/gtksourcetagtable.h>
#endif

namespace Xfc {

namespace Gtk {

class SourceTagStyle;

//! @class SourceTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkSourceTag C++ wrapper class.

class SourceTag : public TextTag
{
	friend class G::Object;

	SourceTag(const SourceTag&);
	SourceTag& operator=(const SourceTag&);

protected:
//! @name Constructors
//! @{

	explicit SourceTag(GtkSourceTag *tag, bool reference = false);
	//!< Construct a new SourceTag from an existing GtkSourceTag.
	//!< @param tag A pointer to a GtkSourceTag.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>tag</EM> can be a newly created GtkSourceTag or an existing
	//!< GtkSourceTag (see G::Object::Object).

//! @}
//  Properties

	typedef G::Property<String> IdPropertyType;
	typedef G::PropertyProxy<G::Object, IdPropertyType> IdPropertyProxy;
	static const IdPropertyType id_property;

	typedef G::Property<Pointer<SourceTagStyle> > TagStylePropertyType;
	typedef G::PropertyProxy<G::Object, TagStylePropertyType> TagStylePropertyProxy;
	static const TagStylePropertyType tag_style_property;

public:
//! @name Constructors
//! @{

	virtual ~SourceTag();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceTag* gtk_source_tag() const { return reinterpret_cast<GtkSourceTag*>(instance_); }
	//!< Get a pointer to the GtkSourceTag structure.

	operator GtkSourceTag* () const;
	//!< Conversion operator; safely converts a SourceTag to a GtkSourceTag pointer.

	bool is_gtk_source_tag() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_TAG.

	String get_id() const;
	//!< Returns the source tag ID.

	SourceTagStyle* get_style() const;
	//!< Returns the SourceTagStyle for the source tag.

//! @}
//! @name Methods
//! @{

	void set_style(const SourceTagStyle& style);
	//!< Set the SourceTagStyle for the source tag.
	//!< @param style The new tag style.

//! @}
//! @name Property Proxies
//! @{

	const IdPropertyProxy property_id()
	{
		return IdPropertyProxy(this, &id_property);
	}
	//!< The ID used to refer to the source tag (String : Read / Write / Construct).

	const TagStylePropertyProxy property_tag_style()
	{
		return TagStylePropertyProxy(this, &tag_style_property);
	}
	//!< The style associated to the source tag (Pointer<SourceTagStyle> : Read / Write).

//! @}
};

//! @class SyntaxTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkSyntaxTag C++ wrapper class.

class SyntaxTag : public SourceTag
{
	friend class G::Object;

	SyntaxTag(const SyntaxTag&);
	SyntaxTag& operator=(const SyntaxTag&);

protected:
//! @name Constructors
//! @{

	explicit SyntaxTag(GtkSyntaxTag *tag, bool reference = false);
	//!< Construct a new SyntaxTag from an existing GtkSyntaxTag.
	//!< @param tag A pointer to a GtkSyntaxTag.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>tag</EM> can be a newly created GtkSyntaxTag or an existing
	//!< GtkSyntaxTag (see G::Object::Object).

//! @}

public:
//! @name Constructors
//! @{

	SyntaxTag(const String& id, const String& name, const char *pattern_start, const char *pattern_end);
	//!< Construct a new syntax tag.
	//!< @param id The ID used to refer to the tag.
	//!< @param name The name of the tag.
	//!< @param pattern_start
	//!< @param pattern_end

	virtual ~SyntaxTag();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSyntaxTag* gtk_syntax_tag() const { return reinterpret_cast<GtkSyntaxTag*>(instance_); }
	//!< Get a pointer to the GtkSyntaxTag structure.

	operator GtkSyntaxTag* () const;
	//!< Conversion operator; safely converts a SyntaxTag to a GtkSyntaxTag pointer.

	bool is_gtk_syntax_tag() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SYNTAX_TAG.

//! @}
};

//! @class LineCommentTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkSyntaxTag C++ wrapper class.

class LineCommentTag : public SyntaxTag
{
public:
//! @name Constructors
//! @{

	LineCommentTag(const String& id, const String& name, const char *pattern_start);
	//!< Construct a new line comment tag.
	//!< @param id The ID used to refer to the tag.
	//!< @param name The name of the tag.
	//!< @param pattern_start

//! @}
};

//! @class StringTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkSyntaxTag C++ wrapper class.

class StringTag : public SyntaxTag
{
public:
//! @name Constructors
//! @{

	StringTag(const String& id, const String& name, const char *pattern_start, const char *pattern_end, bool end_at_line_end);
	//!< Construct a new line comment tag.
	//!< @param id The ID used to refer to the tag.
	//!< @param name The name of the tag.
	//!< @param pattern_start
	//!< @param pattern_end
	//!< @param end_at_line_end

//! @}
};

//! @class PatternTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkPatternTag C++ wrapper class.

class PatternTag : public SourceTag
{
	friend class G::Object;

	PatternTag(const PatternTag&);
	PatternTag& operator=(const PatternTag&);

protected:
//! @name Constructors
//! @{

	explicit PatternTag(GtkPatternTag *tag, bool reference = false);
	//!< Construct a new PatternTag from an existing GtkPatternTag.
	//!< @param tag A pointer to a GtkPatternTag.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>tag</EM> can be a newly created GtkPatternTag or an existing
	//!< GtkPatternTag (see G::Object::Object).

//! @}

public:
//! @name Constructors
//! @{

	PatternTag(const String& id, const String& name, const char *pattern);
	//!< Construct a new pattern tag.
	//!< @param id The ID used to refer to the tag.
	//!< @param name The name of the tag.
	//!< @param pattern

	virtual ~PatternTag();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkPatternTag* gtk_pattern_tag() const { return reinterpret_cast<GtkPatternTag*>(instance_); }
	//!< Get a pointer to the GtkPatternTag structure.

	operator GtkPatternTag* () const;
	//!< Conversion operator; safely converts a PatternTag to a GtkPatternTag pointer.

	bool is_gtk_pattern_tag() const;
	//!< Returns true if the object instance is of type GTK_TYPE_PATTERN_TAG.

//! @}
};

//! @class KeywordListTag sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkPatternTag C++ wrapper class.

class KeywordListTag : public PatternTag
{
public:
//! @name Constructors
//! @{

	KeywordListTag(const String& id, const String& name, std::vector<String>& keywords, bool case_sensitive,
	               bool match_empty_string_at_beginning, bool match_empty_string_at_end,
		       const char *beginning_regex, const char *end_regex);
	//!< Construct a new keyword list tag.
	//!< @param id The ID used to refer to the tag.
	//!< @param name The name of the tag.
	//!< @param keywords A vector of String that holds the keywords.
	//!< @param case_sensitive Set <EM>true</EM> if the keywords are case sensitive.
	//!< @param match_empty_string_at_beginning
	//!< @param match_empty_string_at_end
	//!< @param beginning_regex
	//!< @param end_regex

//! @}
};

//! @class SourceTagTable sourcetag.h inti/gtk-sourceview/sourcetag.h
//! @brief A GtkSourceTagTable C++ wrapper class.

class SourceTagTable : public TextTagTable
{
	friend class G::Object;

	SourceTagTable(const SourceTagTable&);
	SourceTagTable& operator=(const SourceTagTable&);

protected:
//! @name Constructors
//! @{

	explicit SourceTagTable(GtkSourceTagTable *table, bool reference = false);
	//!< Construct a new SourceTagTable from an existing GtkSourceTagTable.
	//!< @param table A pointer to a GtkSourceTagTable.
	//!< @param reference Set false if the initial reference count is floating, set true if it's not.
	//!<
	//!< <BR>The <EM>table</EM> can be a newly created GtkSourceTagTable or an existing
	//!< GtkSourceTagTable (see G::Object::Object).

//! @}
//  Signals

	typedef G::Signal0<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;

public:
//! @name Constructors
//! @{

	SourceTagTable();
	//!< Construct a new (empty) source tag table.

	virtual ~SourceTagTable();
	//!< Destructor.

//! @}
//! @name Accessors
//! @{

	GtkSourceTagTable* gtk_source_tag_table() const { return  reinterpret_cast<GtkSourceTagTable*>( instance_); }
	//!< Get a pointer to the GtkSourceTagTable structure.

	operator GtkSourceTagTable* () const;
	//!< Conversion operator; safely converts a SourceTagTable to a GtkSourceTagTable pointer.

	bool is_gtk_source_tag_table() const;
	//!< Returns true if the object instance is of type GTK_TYPE_SOURCE_TAG_TABLE.

//! @}
//! @name Methods
//! @{

	void add_tags(const std::vector<TextTag*>& tags);
	//!< Add a list of tags to the table. 
	//!< @param tags A vector of SourceTag pointers holding the source tags to add.
	//!<
	//!< <BR>The added tags are assigned the highest priority in the table. If a tag
	//!< is already present in table or has the same name as an already-added tag,
	//!< then it is not added to the table.

	void remove_source_tags();
	//!< Removes all the source tags from the table. This will remove the table's
	//!< reference to the tags, so be careful - tags will end up destroyed if you
	//!< don't have a reference to them.

//! @}
//! @name Signal Proxies
//! @{

	const ChangedSignalProxy sig_changed()
	{
		return ChangedSignalProxy(this, &changed_signal);
	}
	//!< Connect to the changed_signal; emitted whenever source tags are added to or removed from the table.

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_TAG_H

