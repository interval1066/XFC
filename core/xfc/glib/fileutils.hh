/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/fileutils.hh
/// @brief C++ interface for GDir and the various GLib file-related functions.

#ifndef XFC_G_FILEUTILS_HH
#define XFC_G_FILEUTILS_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_DIR_H__
#include <glib/gdir.h>
#endif

#ifndef __G_FILEUTILS_H__
#include <glib/gfileutils.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Error;

/// @enum FileError
/// Values corresponding to errno codes returned from file operations on UNIX. 
/// Unlike errno codes, FileError values are available on all systems. The exact
/// meaning of each code depends on what sort of file operation you were performing;
/// the UNIX documentation gives more details. The following error code descriptions
/// come from the GNU C Library manual, and are under the copyright of that manual. 
///
/// It's not very portable to make detailed assumptions about exactly which errors will
/// be returned from a given operation. Some errors don't occur on some systems, etc.,
/// sometimes there are subtle differences in when a system will report a given error, etc.

enum FileError
{
	FILE_ERROR_EXIST = G_FILE_ERROR_EXIST,
	///< Operation not permitted; only the owner of the file (or other resource) or
	///< processes with special privileges can perform the operation. 

	FILE_ERROR_ISDIR = G_FILE_ERROR_ISDIR,
	///< File is a directory; you cannot open a directory for writing, or create or remove hard links to it. 

	FILE_ERROR_ACCES = G_FILE_ERROR_ACCES,
	///< Permission denied; the file permissions do not allow the attempted operation. 

	FILE_ERROR_NAMETOOLONG = G_FILE_ERROR_NAMETOOLONG,
	///< Filename is too long. 

	FILE_ERROR_NOENT = G_FILE_ERROR_NOENT,
	///< No such file or directory; This is a "file doesn't exist" error for ordinary files
	///< that are referenced in contexts where they are expected to already exist. 

	FILE_ERROR_NOTDIR = G_FILE_ERROR_NOTDIR,
	///< A file that isn't a directory was specified when a directory is required. 

	FILE_ERROR_NXIO = G_FILE_ERROR_NXIO,
	///< No such device or address; The system tried to use the device represented by a file you specified,
	///< and it couldn't find the device; This can mean that the device file was installed incorrectly, 
	///< or that the physical device is missing or not correctly attached to the computer. 

	FILE_ERROR_NODEV = G_FILE_ERROR_NODEV,
	///< This file is of a type that doesn't support mapping. 

	FILE_ERROR_ROFS = G_FILE_ERROR_ROFS,
	///< The directory containing the new link can't be modified because it's on a read-only file system. 

	FILE_ERROR_TXTBSY = G_FILE_ERROR_TXTBSY,
	///< Text file busy. 

	FILE_ERROR_FAULT = G_FILE_ERROR_FAULT,
	///< You passed in a pointer to bad memory (GLib won't reliably return this,
	///< don't pass in pointers to bad memory). 

	FILE_ERROR_LOOP = G_FILE_ERROR_LOOP,
	///< Too many levels of symbolic links were encountered in looking up a file name;
	///< This often indicates a cycle of symbolic links. 

	FILE_ERROR_NOSPC = G_FILE_ERROR_NOSPC,
	///< No space left on device; write operation on a file failed because the disk is full. 

	FILE_ERROR_NOMEM = G_FILE_ERROR_NOMEM,
	///< No memory available; The system cannot allocate more virtual memory because its capacity is full. 

	FILE_ERROR_MFILE = G_FILE_ERROR_MFILE,
	///< The current process has too many files open and can't open any more; 
	///< Duplicate descriptors do count toward this limit. 

	FILE_ERROR_NFILE = G_FILE_ERROR_NFILE,
	///< There are too many distinct file openings in the entire system. 

	FILE_ERROR_BADF = G_FILE_ERROR_BADF,
	///< Bad file descriptor; for example, I/O on a descriptor that has been closed
	///< or reading from a descriptor open only for writing (or vice versa). 

	FILE_ERROR_INVAL = G_FILE_ERROR_INVAL,
	///< Invalid argument; This is used to indicate various kinds of problems
	///< with passing the wrong argument to a library function. 

	FILE_ERROR_PIPE = G_FILE_ERROR_PIPE,
	///< Broken pipe; there is no process reading from the other end of a pipe (Every library function
	///< that returns this error code also generates a `SIGPIPE' signal; this signal terminates the 
	///< program if not handled or blocked; Thus, your program will never actually see this code 
	///< unless it has handled or blocked `SIGPIPE'). 

	FILE_ERROR_AGAIN = G_FILE_ERROR_AGAIN,
	///< Resource temporarily unavailable; the call might work if you try again later. 

	FILE_ERROR_INTR = G_FILE_ERROR_INTR,
	///< Interrupted function call; an asynchronous signal occurred and prevented completion
	///< of the call (When this happens, you should try the call again). 

	FILE_ERROR_IO = G_FILE_ERROR_IO,
	///< Input/output error; usually used for physical read or write errors, that is, the disk
	///< or other physical device hardware is returning errors. 

	FILE_ERROR_PERM = G_FILE_ERROR_PERM,
	///< Operation not permitted; only the owner of the file (or other resource) or processes
	///< with special privileges can perform the operation. 

	FILE_ERROR_NOSYS = G_FILE_ERROR_NOSYS,
	///< Function not implemented; this indicates that the system is missing some functionality. 

	FILE_ERROR_FAILED = G_FILE_ERROR_FAILED
	///< Does not correspond to a UNIX error code; this is the standard "failed for unspecified reason"
	///< error code present in all GError error code enumerations (Returned if no specific code applies).
};

/// @enum FileTest
/// Specifies a test to perform on a file using G::file_test().

enum FileTest
{
	FILE_TEST_IS_REGULAR = G_FILE_TEST_IS_REGULAR,
	///< Tests true if the file is a regular file (not a symlink or directory).

	FILE_TEST_IS_SYMLINK = G_FILE_TEST_IS_SYMLINK,
	///< Tests true if the file is a symlink.

	FILE_TEST_IS_DIR = G_FILE_TEST_IS_DIR,
	///< Tests true if the file is a directory.

	FILE_TEST_IS_EXECUTABLE = G_FILE_TEST_IS_EXECUTABLE,
	///< Tests true if the file is executable.

	FILE_TEST_EXISTS = G_FILE_TEST_EXISTS
	///< Tests true if the file exists. It may or may not be a regular file.
};

/// G::FileTestField holds one or more bit values from the G::FileTest enumeration.

typedef unsigned int FileTestField;

/// @name File Methods
/// @{

FileError file_error_from_errno(int err_no);
///< Gets a FileError constant based on the passed-in errno, for example,
///< if you pass in EEXIST this function returns G_FILE_ERROR_EXIST.
///< @param err_no An "errno" value
///< @return A FileError corresponding to the given errno.
///<
///< Unlike errno values, you can portably assume that all FileError values
///< will exist. Normally a FileError value goes into a G::Error returned from
///< a method that manipulates files. So you would use G::file_error_from_errno()
///< when constructing a G::Error.

bool file_test(const char *filename, FileTestField test);
bool file_test(const std::string& filename, FileTestField test);
///< Determines whether any of the tests in the bitfield test are true.
///< @param filename A filename to test.
///< @param test A bitfield of G::FileTest flags.
///< @return <EM>true</EM> if a test was true.
///<
///< For example, (G::FILE_TEST_EXISTS | G::FILE_TEST_IS_DIR) will return true
///< if the file exists; the check whether it's a directory doesn't matter since
///< the existence test is true. With the current set of available tests, there's
///< no point passing in more than one test at a time.
///<
///< Apart from G::FILE_TEST_IS_SYMLINK all tests follow symbolic links, so for a
///< symbolic link to a regular file file_test() will return true for both
///< G::FILE_TEST_IS_SYMLINK and G::FILE_TEST_IS_REGULAR. Note, that for a dangling
///< symbolic link file_test() will return true for G::FILE_TEST_IS_SYMLINK and
///< false for all other flags.
///<
///< You should never use file_test() to test whether it is safe to perform an
///< operaton, because there is always the possibility of the condition changing
///< before you actually perform the operation. For example, you might think you
///< could use G::FILE_TEST_IS_SYMLINK to know whether it is is safe to write to
///< a file without being tricked into writing into a different location. It
///< doesn't work!
///<
///< <B>Example:</B> DON'T DO THIS.
///< @code
///< if (!file_test(filename, FILE_TEST_IS_SYMLINK))
///< {
///<	TempFile file(filename);
///< 	if (file.is_open())
///< 	// write to file
///< }
///< @endcode
///<
///< Another thing to note is that G::FILE_TEST_EXISTS and G::FILE_TEST_IS_EXECUTABLE
///< are implemented using the access() system call. This usually doesn't matter, but
///< if your program is setuid or setgid it means that these tests will give you the
///< answer for the real user ID and group ID , rather than the effective user ID and
///< group ID.

bool file_get_contents(const char *filename, std::string& contents, G::Error *error);
bool file_get_contents(const std::string& filename, std::string& contents, G::Error *error);
///< Reads an entire file into allocated memory, with good error checking.
///< @param filename A file to read the contents from.
///< @param contents The location to store the file contents.
///< @param error The return location for a G::Error.
///< @return <EM>true</EM> on success, <EM>false</EM> if error is set.
///<
///< If error is set, false is returned, and contents is set to an empty string. If true
///< is returned, error will not be set, and contents will be set to the file contents. The
///< error domain is G_FILE_ERROR. Possible error codes are those in the FileError enumeration.

/// @}

/// @class TempFile fileutils.hh xfc/glib/fileutils.hh
/// A C++ wrapper interface for the g_file_open_tmp() and g_mkstemp() functions.
///
/// TempFile is a convenient wrapper class for the g_file_open_tmp() and
/// g_mkstemp() functions. It is a StackObject and must created on the stack.
/// You can't allocate a TempFile dynamically.
///
/// <B>Example 1:</B>
/// You can construct an empty temporary file using the default constructor
/// and then call either one of the open() methods or mkstemp().
/// @code
/// G::TempFile file;
/// std::string filename("/home/testfile");
/// if (file.mkstemp(filename))
/// {
/// 	// write to filename
/// }
/// file.close();
/// @endcode
///
/// <B>Example 2:</B>
/// Alternatively you can construct and open a temporary file in one step by
/// calling one of the parameterized constructors.
/// @code
/// std::string filename;
/// G::Error error;
/// G::TempFile file("testfile", filename, &error);
/// if (file.is_open())
/// {
/// 	// write to filename
/// }
/// file.close();
/// @endcode
///
/// You don't have to explicitly call TempFile::close() as above, unless you want to.
/// When a TempFile object goes out of scope its destructor will check for an open
/// file and close it.

class TempFile : public StackObject
{
	TempFile(const TempFile&);
	TempFile& operator=(const TempFile&);

	int file_descriptor_;

public:
/// @name Constructors
/// @{

	TempFile();
	///< Construct an empty temporary file.

	TempFile(std::string& template_filename);
	///< Construct and open a temporary file with the template filename <EM>template_filename</EM>
	///< @param template_filename The template for the filename.
	///<
	///< See mkstemp() for details.

	TempFile(const char *template_filename, std::string& actual_filename, G::Error *error);
	TempFile(const std::string& template_filename, std::string& actual_filename, G::Error *error);
	///< Construct and open a temporary file with the template filename <EM>template_filename</EM>
	///< @param template_filename The prefix template for the file name, but basename only.
	///< @param actual_filename The location to store actual filename used, includes full path.
	///< @param error The return location for a G::Error, or null.
	///<
	///< See open() for details.

	~TempFile();
	///< Destructor; Closes the temporary file if it's open.

/// @}
/// @name Accessors
/// @{

	bool is_open() const;
	///< Determines whether the temporary file is open.
	///< @return <EM>true</EM> if the file is open.

/// @}
/// @name Methods
/// @{

	bool open(std::string& actual_filename, G::Error *error);
	///< Opens a file for writing in the preferred directory for temporary files (as returned by g_get_tmp_dir()).
	///< @param actual_filename The location to store actual filename used, includes full path.
	///< @param error The return location for a G::Error, or null.
	///< @return <EM>true</EM> if the file was opened for reading and writing.
	///<
	///< This version of open() uses a default template (see open(const std::string&, std::string&, G::Error*)).

	bool open(const char *template_filename, std::string& actual_filename, G::Error *error);
	bool open(const std::string& template_filename, std::string& actual_filename, G::Error *error);
	///< Opens a file for writing in the preferred directory for temporary files (as returned by g_get_tmp_dir()).
	///< @param template_filename The prefix template for the file name, but basename only.
	///< @param actual_filename The location to store actual filename used, includes full path.
	///< @param error The return location for a G::Error, or null.
	///< @return <EM>true</EM> if the file was opened for reading and writing.
	///<
	///< The file is opened in binary mode on platforms where there is a difference.
	///< If the file is not explicitly closed with close() it will automatically be
	///< closed when the file goes out of scope. If an error occurs false is returned
	///< and <EM>error</EM> will be set. Otherwise true is returned.
	///<
	///< Do not suffix <EM>template_filename</EM> with any 'X' characters, this method
	///< will do that for you. Unlike mkstemp() <EM>template_filename</EM> should only
	///< be a basename, no directory components are allowed. Note that in contrast to
	///< mkstemp() <EM>template_filename</EM> is not modified, and might thus be a
	///< read-only literal string. On return the <EM>actual_filename</EM> holds the
	///< full path and filename of the temporary file.

	bool mkstemp(std::string& template_filename);
	///< Opens a temporary file.
	///< @param template_filename The template file name including any directory paths.
	///< @return <EM>true</EM> if the file was opened for reading and writing.
	///<
	///< The file is opened in binary mode on platforms where there is a difference.
	///< If the file is not explicitly closed with close() it will automatically be
	///< closed when the file goes out of scope. If an error occurs false is returned
	///< and <EM>error</EM> will be set. Otherwise true is returned.
	///<
	///< Do not suffix <EM>template_filename</EM> with any 'X' characters, this method
	///< will do that for you. On returning <EM>template_filename</EM> will have been
	///< modified to form the name of a file that didn't exist.

	bool close();
	///< Closes an open temporary file.

/// @}
};

/// @class Dir fileutils.hh xfc/glib/fileutils.hh
/// @brief A GDir C++ wrapper interface.
///
/// Dir is an object that represents a file directory. Dir is a
/// StackObject, that is it must created on the stack. You can't
/// allocate Dir dynamically.
///
/// <B>Example 1:</B>
/// You can construct an empty directory object using the default constructor
/// and then call open().
/// @code
/// G::Dir dir;
/// std::string dirname("/home");
/// if (dir.open(dirname))
/// {
/// 	// read directory
/// }
/// dir.close();
/// @endcode
///
/// <B>Example 2:</B>
/// Alternatively you can construct and open a directory object in one step
/// by calling one of the parameterized constructors.
/// @code
/// std::string dirname;
/// G::Error error;
/// G::Dir dir(dirname, &error);
/// if (dir.is_open())
/// {
/// 	// read directory
/// }
/// dir.close();
/// @endcode
///
/// You don't have to explicitly call Dir::close() as above, unless you want to.
/// When a directory object goes out of scope its destructor will check for an
/// open directory and close it.
///
/// For convenience the entries in a directory can be read individually by
/// calling read_name() or at once by calling read_names(). The latter method
/// fills a user-supplied 'std::vector of String' with the entry names.

class Dir : public StackObject
{
	Dir(const Dir&);
	Dir& operator=(const Dir&);

	GDir *dir_;

public:
/// @name Constructors
/// @{

	Dir();
	///< Constructs an empty directory object.

	Dir(const char *path, G::Error *error);
	Dir(const std::string& path, G::Error *error);
	///< Constructs a directory object and opens the directory <EM>path</EM>.
	///< @param path The path to the directory you are interested in.
	///< @param error The return location for a G::Error, or null.
	///<
	///< If the directory <EM>path</EM> is successfully opened is_open()
	///< returns true. If an error occurs is_open() returns false and <EM>error</EM>
	///< will contain information about the error.

	~Dir();
	///< Destructor;
	///< Closes the directory if it's open.

/// @}
/// @name Accessors
/// @{

	bool is_open() const;
	///< Determines whether the directory is open.
	///< @return <EM>true</EM> if the directory is open.

/// @}
/// @name Methods
/// @{

	bool open(const char *path, G::Error *error);
	bool open(const std::string& path, G::Error *error);
	///< Opens a directory for reading.
	///< @param path The path to the directory you are interested in.
	///< @param error The return location for a G::Error, or null.
	///< @return <EM>true</EM> if this method is successful, <EM>false</EM> otherwise.
	///<
	///< The names of the files in the directory can then be retrieved using read_name().
	///< If <EM>error</EM> is non-null, an error will be set if and only if this method fails.
	///< If successful you can either explicitly call close() or let the dir object call close()
	///< when it goes out of scope.

	const char* read_name();
	///< Retrieves the name of the next entry in the directory (the '.' and '..' entries
	///< are omitted).
	///< @return The entry's name or null if there are no more entries.
	///<
	///< The return value is owned by GLib and must not be modified or freed.

	int read_names(std::vector<std::string>& names);
	///< Gets a list of the names of all the entries in the directory (the '.' and
	///< '..' entries are omitted).
	///< @param names A reference to a vector of String to hold the names.
	///< @return -1 on failure, otherwise an integer value indicating the degree of success.
	///<
	///< This method retrieves the name of each entry and calls String::from_filename()
	///< to convert the string from the encoding used for filenames into a UTF-8 String.
	///< If this method successfully converts all entry names the return value is 0. If
	///< any entry names couldn't be converted the return value is the number of failed
	///< conversions. If you want to know the entry names of all failed conversions you
	///< should call read_name() instead.

	void rewind();
	///< Resets the given directory so that the next call to read_name()
	///< will return the first entry again.

	void close();
	///< Closes the directory and deallocates all related resources.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/fileutils.inl>

#endif // XFC_G_FILEUTILS_HH














