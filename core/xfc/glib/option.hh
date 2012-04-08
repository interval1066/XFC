/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/option.hh
/// @brief A C++ interface for the GLib commandline option parser.
///
/// Provides G::OptionContext, an object that defines which options are accepted
/// by the commandline option parser, and G::OptionGroup, an object that defines
/// the options in a single group.

#ifndef XFC_G_OPTION_HH
#define XFC_G_OPTION_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_OPTION_H__
#include <glib/goption.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Error;
class OptionGroup;
class OptionGroupData;

/// @enum OptionError
/// Specifies the error codes returned by option parsing.

enum OptionError
{
	OPTION_ERROR_UNKNOWN_OPTION = G_OPTION_ERROR_UNKNOWN_OPTION,
	///< An option was not known to the parser; this error will only be reported, if the parser
	///< hasn't been instructed to ignore unknown options (see set_ignore_unknown_options()).
	
	OPTION_ERROR_BAD_VALUE = G_OPTION_ERROR_BAD_VALUE,
	///< A value couldn't be parsed.
	
	OPTION_ERROR_FAILED = G_OPTION_ERROR_FAILED
}; 

/// @enum OptionFlags
/// Specifies the flags which modify individual options.

enum OptionFlags
{
	OPTION_FLAG_HIDDEN = G_OPTION_FLAG_HIDDEN, 
	///< The option doesn't appear in --help output.
	
	OPTION_FLAG_IN_MAIN = G_OPTION_FLAG_IN_MAIN, 
	///< The option appears in the main section of the --help output, even if it is defined in a group.
	
	OPTION_FLAG_REVERSE = G_OPTION_FLAG_REVERSE
	///< For options of the G_OPTION_ARG_NONE kind, this flag indicates that the sense of the option is reversed.
};

/// G::OptionFlagsField holds one or more bit values from the G::OptionFlags enumeration.

typedef unsigned int OptionFlagsField;

/// @class OptionContext option.hh xfc/glib/option.hh
/// A C++ wrapper interface for GOptionContext.
///
/// OptionContext defines which options are accepted by the commandline option parser.
///
/// The GLib commandline option parser supports the use of short and long commandline options.
/// Short options take one hyphen and a character, like "-a". Long options take two hyphens and
/// a string, like "--all". Both option types can take arguments. When using short options,
/// the argument must be given after the option, separated by a space. When using long options,
/// the argument can either be separated by a space or appended with an equal sign. Look at the
/// following commandline:
///
/// @code
/// testtreemodel -r 1 --max-size 20 --rand --display=:1.0 -vb -- file1 file2
/// @endcode
///
/// This example demonstrates a number of features of the GLib commandline option parser:
/// <ol>
///   <li>Options can be single letters, prefixed by a single hyphen.</li> 
///   <li>Multiple short options can be grouped behind a single hyphen.</li> 
///   <li>Long options are prefixed by two consecutive hyphens.</li> 
///   <li>Options can have an extra argument, which can be a number, a string or a filename.</li>
///   <li>For long options, the extra argument can be appended with an equals sign after the option name.</li> 
///   <li>Non-option arguments are returned to the application as rest arguments.</li>
///   <li>An argument consisting solely of two hyphens turns off further parsing.</li>
/// </ol> 
/// An important feature of the parser is that an argument consisting solely of two hyphens
/// turns off further parsing, and any remaining arguments (even those starting with a hyphen)
/// are returned to the application as rest arguments. Another important feature is that the 
/// parser can automatically generate nicely formatted help output. Unless it is explicitly
/// turned off with set_help_enabled(), the parser will recognize the --help, -?, --help-all
/// and --help-groupname options (where groupname is the name of a OptionGroup) and write a
/// text similar to the one shown in the following example to stdout:
///
/// @code
/// Usage:
///   testtreemodel [OPTION...] - test tree model performance
/// 
/// Help Options:
///   --help                   Show help options
///   --help-all               Show all help options
///   --help-gtk               Show GTK+ Options
/// 
/// Application Options:
///   -r, --repeats=N          Average over N repetitions
///   -m, --max-size=M         Test up to 2^M items
///   --display=DISPLAY        X display to use
///   -v, --verbose            Be verbose
///   -b, --beep               Beep when done   
///   --rand                   Randomize the data 
/// @endcode
///
/// Grouping options into groups makes it easy for applications to incorporate options from
/// multiple sources. This allows an application to collect option groups from the libraries
/// it uses, add them to their option context, and parse all options with a one call to 
/// G::OptionContext::parse(). If an option is declared to be of type string or filename, the
/// parser takes care of converting it to the right encoding; strings are returned in UTF-8,
/// filenames are returned in the GLib filename encoding.
///
/// <B>Example:</B> Sets up an option parser to parse the above commandline and produce the help output.
/// @code
/// int repeats = 2;
/// int max_size = 8;
/// bool verbose = false;
/// bool beep = false;
/// bool rand = false;
///
/// int main (int argc, char *argv[])
/// {
///     G::OptionGroup main_group;
///     main_group->add("repeats", 'r', &repeats, "Average over N repetitions", "N");
///     main_group->add("max-size", 'm', &max_size, "Test up to 2^M items", "M");
///     main_group->add("verbose", 'v', &verbose, "Be verbose");
///     main_group->add("beep", 'b', &beep, "Beep when done");
///     main_group->add("rand", 0, &rand, "Randomize the data");
///     G::OptionContext context("- test tree model performance", main_group);
///     context->add_group(Main::get_option_group());
///
///     G::Error error;
///     context->parse(&argc, &argv, &error);
///     ...
/// }
/// @endcode
///
/// Main::get_option_group() returns an option group for all the commandline arguments
/// recognized by GTK+ and GDK. Adding this group to your context and calling parse()
/// will initialize the XFC library so you wont need to call Main::init().

class OptionContext : public Xfc::Object
{
	OptionContext(const OptionContext&);
	OptionContext& operator=(const OptionContext&);

	GOptionContext *context_;
	bool can_free_;

public:
/// @name Constructors
/// @{

	OptionContext(const char *parameter_string);
	OptionContext(const String& parameter_string);
	///< Construct a new option context.
	///< @param parameter_string The string to display in the first line of --help output, after programname [OPTION...]. 

	OptionContext(const char *parameter_string, OptionGroup& main_group);
	OptionContext(const String& parameter_string, OptionGroup& main_group);
	///< Construct a new option context with the specified main group.
	///< @param parameter_string The string to display in the first line of --help output, after programname [OPTION...]. 
	///< @param main_group The group to set as the main group for the option context.
	///<
	///< The options in the main group are treated differently when generating --help output.
	
	OptionContext(GOptionContext *context, bool can_free);
	///< Construct a new option context from an existing GOptionContext.
	///< @param context A GOptionContext. 
	///< @param can_free Set <EM>true</EM> if the GOptionContext should be freed by this option context.
	///<
	///< This constructor is used to wrap a GOptionContext pointer in a temporary G::OptionContext
	///< class for passing to G::OptionGroup::on_pre_parse() and G::OptionGroup::on_post_parse().
	///< You should have no need to use this constructor.
		
	~OptionContext();
	///< Destructor; Frees the memory allocated to the option context.

/// @}
/// @name Accessors
/// @{

	GOptionContext* g_option_context() const;
	///< Get a pointer to the GOptionContext object.

	operator GOptionContext* () const;
	///< Conversion operator; Safely converts a G::OptionContext object into a GOptionContext pointer.

	bool get_help_enabled() const;
	///< Determines whether automatic --help generation is turned on for context (see set_help_enabled()).
	///< @return <EM>true</EM> if automatic help generation is turned on.

	bool get_ignore_unknown_options() const;
	///< Determines whether unknown options are ignored or not (see set_ignore_unknown_options()).
	///< @return <EM>true</EM> if unknown options are ignored.

	Pointer<OptionGroup> get_main_group() const;
	///< Gets a pointer to the main group of context.
	///< @return The main group of context, or null if context doesn't have a main group.
	///<
	///< Note that group belongs to context and should not be modified.
	
/// @}
/// @name Methods
/// @{

	void set_help_enabled(bool help_enabled);
	///< Enables or disables automatic generation of --help output. 
	///< @param help_enabled Set <EM>true</EM> to enable --help, <EM>false</EM> to disable it.
	///<	
	///< By default, parse() recognizes --help, -?, --help-all and --help-groupname
	///< and creates suitable output to stdout.

	void set_ignore_unknown_options(bool ignore_unknown);
	///< Sets whether to ignore unknown options or not. 
	///< @param ignore_unknown Set <EM>true</EM> to ignore unknown options. 
	///<
	///< If <EM>ignore_unknown</EM> is set to false, an error is produced when unknown options are
	///< met. If an argument is ignored, it is left in the argv array after parsing. By default,
	///< parse() treats unknown options as error. This setting does not affect non-option arguments
	///< (i.e. arguments which don't start with a dash). But note that the option parser cannot 
	///< reliably determine whether a non-option belongs to a preceding unknown option.
	
	bool parse(int *argc, char ***argv, Error *error);
	///< Parses the command line arguments, recognizing options which have been added to context. 
	///< @param argc A pointer to the number of command line arguments. 
	///< @param argv A pointer to the array of command line arguments. 
	///< @param error The return location for errors. 
	///< @return <EM>true</EM> if the parsing was successful, <EM>false</EM> if an error occurred.
	///<	
	///< A side-effect of calling this function is that g_set_prgname() will be called. If the parsing
	///< is successful, any parsed arguments are removed from the array and <EM>argc</EM> and <EM>argv</EM>
	///< are updated accordingly. In case of an error, <EM>argc</EM> and <EM>argv</EM> are left unmodified. 
	///< 
	///< If automatic --help support is enabled (see set_help_enabled()), and the <EM>argv</EM> array 
	///< contains one of the recognized help options, this method will produce help output to stdout
	///< and call exit(0).

	void add_group(GOptionGroup *group);
	///< Adds a GOptionGroup to the option context, so that parsing with
	///< the option context will recognize the options in the group. 
	///< @param group A GOptionGroup to add to the context.
	///<	
	///< For convenience, this method lets you add an unwrapped GOptionGroup to the context.
	///< The purpose of the method is to make it easy to add GOptionGroups returned by other
	///< libraries, such as the GTK+ option group returned from Main::get_option_group(). 
	///< Note that the group will be destroyed together with the context, when the context
	///< is destroyed, so you must not unreference the group yourself after adding it to a
	///< context.
	
	void add_group(OptionGroup& group);
	///< Adds an OptionGroup to the option context, so that parsing with
	///< the option context will recognize the options in the group. 
	///< @param group A group to add to the context.
	///<	
	///< Note that the group will be destroyed together with the context, when the context is destroyed,
	///< so you must not unreference the group yourself after adding it to a context.
	
	void set_main_group(OptionGroup& group);
	///< Sets <EM>group</EM> to be the main group for the context. 
	///< @param group The group to set as main group for the context.
	///<	
	///< This has the same effect as calling add_group(), the only difference is that the options
	///< in the main group are treated differently when generating --help output. Note, a context
	///< can have only one main group.

/// @}
};

/// @class OptionGroup option.hh xfc/glib/option.hh
/// A C++ wrapper interface for the GOptionGroup.
///
/// OptionGroup defines the options in a single group. All options in a group share the same
/// translation function. Libaries which need to parse commandline options are expected to 
/// provide a function for getting an OptionGroup holding their options, which the application
/// can then add to its G::OptionContext.

class OptionGroup : public Xfc::Object
{
	friend class OptionContext;	
	
	OptionGroup(const OptionGroup&);
	OptionGroup& operator=(const OptionGroup&);

	GOptionGroup *group_;
	bool can_free_;
	
	OptionGroupData *data_;	

public:
/// @name Constructors
/// @{

	OptionGroup();
	///< Constructs a MAIN option group only. The MAIN option group does not need to set a
	///< user defined "name", "description" or "help_description" so this constructor sets
	///< these properties to null. This group should only be used as the MAIN option group
	///< and must be passed to the Main::init_with_args() function, the G::OptionContext
	///< constructor or the G::OptionContext::set_main_group() method.
	
	OptionGroup(const char *name, const char *description, const char  *help_description);
	///< Constructs a new option group.
	///< @param name The name for the option group.
	///< @param description A description for this group to be shown in --help. 
	///< @param help_description A description for the --help-name option. 
	///<	 
	///< The <EM>name</EM> is used to provide help for the options in this group with --help-name. 
	///< The <EM>description</EM> and <EM>help_description</EM> strings are translated using the
	///< translation domain or translation function of the group. 

	OptionGroup(GOptionGroup *group, bool can_free);
	///< Construct a new option group from an existing GOptionGroup.
	///< @param group A GOptionGroup. 
	///< @param can_free Set <EM>true</EM> if the GOptionGroup should be freed by this option group.
	///<
	///< This constructor is used to wrap a GOptionGroup pointer in a temporary
	///< G::OptionGroup class. You should have no need to use this constructor.
		
	~OptionGroup();
	///< Destrcutor frees the group if the group has not been added to an option context.

/// @}
/// @name Accessors
/// @{

	GOptionGroup* g_option_group() const;
	///< Get a pointer to the GOptionGroup object.

	operator GOptionGroup* () const;
	///< Conversion operator; Safely converts a G::OptionGroup object into a GOptionGroup pointer.
	
	const GOptionEntry* get_entries() const;
	///< Obtains a pointer to the internal GOptionGroup array that holds the options added to the group.
	///< @return A pointer to the internal GOptionGroup array.
	///<
	///< This is an internal method called by Main::init_with_args().
	///< It is of no real use to the application programmer.

/// @}
/// @name Methods
/// @{

	virtual bool on_parse(const char *option_name, const char *value, Error& error);
	///< Called to parse options that were added to the group using one of the callback add methods.
	///< @param option_name The name of the option being parsed. 
	///< @param value The value to be parsed.
	///< @param error The return location for errors.
	///< @return <EM>true</EM> if the option was successfully parsed, <EM>false</EM> if an error occurred.
	///<
	///< This method is a group-wide callback that is called to parse any options added to
	///< the group using one of the callback add methods. The <EM>option_name</EM> will be
	///< either a single dash followed by a single letter (for a short name) or two dashes
	///< followed by a long option name. The error code G::OPTION_ERROR_FAILED should be
	///< used for any errors that occur during parsing.	
	
	virtual bool on_pre_parse(OptionContext& context, Error& error);
	///< Callback method, called before parsing the group. 
	///< @param context The active option context.
	///< @param error The return location for error details. 
	///< @return <EM>true</EM> if the method completed successfully, <EM>false</EM> if an error occurred.
	///<
	///< Override this method if your option group has any pre-parse processing to do. 

	virtual bool on_post_parse(OptionContext& context, Error& error);
	///< Callback method, called after parsing the group. 
	///< @param context The active option context.
	///< @param error The return location for error details. 
	///< @return <EM>true</EM> if the method completed successfully, <EM>false</EM> if an error occurred.
	///<
	///< Override this method if your option group has any post-parse processing to do. If you do,
	///< be sure to call or return this parent method because it does some essential processing.    

	virtual void on_error(OptionContext& context, const Error& error);
	///< Callback method, called when a parse error occurs. 
	///< @param context The active option context.
	///< @param error The G::Error containing details about the parse error.

	void set_translation_domain(const char *domain);
	void set_translation_domain(const String& domain);
	///< A convenience method to use gettext() for translating user-visible strings.
	///< @param domain The domain to use.

/// @}
/// @name Callback Add Methods
/// @{

	void add(const char *long_name, char short_name, const char *description, const char *arg_description);
	///< Adds an option to the group that gets passed to on_parse() to parse the extra argument.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, 
	         const char *description, const char *arg_description);
	///< Adds an option to the group that gets passed to on_parse() to parse the extra argument.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
/// @}
/// @name Boolean Add Methods
/// @{
	
	void add(const char *long_name, char short_name, bool& arg, const char *description);
	///< Adds an boolean option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg The return location to store the boolean value.
	///< @param description The description for the option in --help output
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> is translated using
	///< the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, bool& arg, const char *description);
	///< Adds an boolean option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg The return location to store the boolean value.
	///< @param description The description for the option in --help output
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> is translated using
	///< the translate_func of the group (see set_translation_domain()).

/// @}
/// @name Integer Add Methods
/// @{

	void add(const char *long_name, char short_name, int& arg, const char *description, const char *arg_description);
	///< Adds an integer option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg The return location to store the integer value.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, int& arg, 
	         const char *description, const char *arg_description);
	///< Adds an integer option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg The return location to store the integer value.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).

/// @}
/// @name String Add Methods
/// @{

	void add(const char *long_name, char short_name, String& arg, const char *description, const char *arg_description);
	///< Adds a string option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg The return location to store the string.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, String& arg, 
	         const char *description, const char *arg_description);
	///< Adds a string option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg The return location to store the string.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).

	void add(const char *long_name, char short_name, std::vector<String>& arg, 
	         const char *description, const char *arg_description);
	///< Adds a string vector option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg A vector of String to store the string values.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, std::vector<String>& arg,
	         const char *description, const char *arg_description);
	///< Adds a string vector option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg A vector of String to store the string values.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).

/// @}
/// @name Filename Add Methods
/// @{

	void add(const char *long_name, char short_name, std::string& arg, 
	         const char *description, const char *arg_description);
	///< Adds a filename option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg The return location to store the filename.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, std::string& arg,
	         const char *description, const char *arg_description);
	///< Adds a filename option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg The return location to store the filename.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).

	void add(const char *long_name, char short_name, std::vector<std::string>& arg, 
	         const char *description, const char *arg_description);
	///< Adds a filename vector option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param arg A vector of std::string to store the filename values.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
	
	void add(const char *long_name, char short_name, OptionFlagsField flags, std::vector<std::string>& arg,
	         const char *description, const char *arg_description);
	///< Adds a filename vector option to the group.
	///< @param long_name The long name of the option.
	///< @param short_name The short name of the option.
	///< @param flags One or more flags from G::OptionFlags enumeration.
	///< @param arg A vector of std::string to store the filename values.
	///< @param description The description for the option in --help output
	///< @param arg_description The placeholder to use for the extra argument parsed by the option in --help output.
	///<
	///< The long name of an option can be used to specify it in a commandline as --long_name. Every option
	///< must have a long name. To resolve conflicts if multiple option groups contain the same long name,
	///< it is also possible to specify the option as --groupname-long_name. If an option has a short name,
	///< it can be specified as -short_name in a commandline. The <EM>description</EM> and <EM>arg_description</EM> 
	///< are translated using the translate_func of the group (see set_translation_domain()).
		 
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/option.inl>

#endif // XFC_G_OPTION_HH

