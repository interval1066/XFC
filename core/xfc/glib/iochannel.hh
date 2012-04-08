/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/iochannel.hh
/// @brief A GIOChannel C++ interface.
///
/// Provides IO Channels for portable support for using files, pipes and sockets.

#ifndef XFC_G_IOCHANNEL_HH
#define XFC_G_IOCHANNEL_HH

#ifndef XFC_TRACKABLE_HH
#include <xfc/trackable.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_IOCHANNEL_H__
#include <glib/giochannel.h>
#endif

namespace Xfc {

namespace G {

class Error;
class Source;

/// enum IOChannelError
/// The error codes returned by IOChannel operations.

enum IOChannelError
{
	IO_CHANNEL_ERROR_FBIG = G_IO_CHANNEL_ERROR_FBIG, ///< File too large.
	IO_CHANNEL_ERROR_INVAL = G_IO_CHANNEL_ERROR_INVAL, ///< Invalid argument.
	IO_CHANNEL_ERROR_IO = G_IO_CHANNEL_ERROR_IO, ///< IO error.
	IO_CHANNEL_ERROR_ISDIR = G_IO_CHANNEL_ERROR_ISDIR, ///< File is a directory.
	IO_CHANNEL_ERROR_NOSPC = G_IO_CHANNEL_ERROR_NOSPC, ///< No space left on device.
	IO_CHANNEL_ERROR_NXIO = G_IO_CHANNEL_ERROR_NXIO, ///< No such device or address.
	IO_CHANNEL_ERROR_OVERFLOW = G_IO_CHANNEL_ERROR_OVERFLOW, ///< Value too large for defined datatype.
	IO_CHANNEL_ERROR_PIPE = G_IO_CHANNEL_ERROR_PIPE, ///< Broken pipe.
	IO_CHANNEL_ERROR_FAILED = G_IO_CHANNEL_ERROR_FAILED ///< Some other error.

};

/// enum IOStatus
/// Describes the status of an IO operation.

enum IOStatus
{
	IO_STATUS_ERROR = G_IO_STATUS_ERROR, ///< An error occurred.
	IO_STATUS_NORMAL = G_IO_STATUS_NORMAL, ///< Success.
	IO_STATUS_EOF = G_IO_STATUS_EOF, ///< End of file.
	IO_STATUS_AGAIN = G_IO_STATUS_AGAIN ///< Resource temporarily unavailable.
};

/// @enum SeekType
/// Specifies the base position for a IOChannel::seek() operation.

enum SeekType
{
	IO_SEEK_CUR = G_SEEK_CUR, ///< The current position in the file.
	IO_SEEK_SET = G_SEEK_SET, ///< The start of the file.
	IO_SEEK_END = G_SEEK_END ///< The end of the file.
};

/// enum IOCondition
/// A bitwise combination representing a condition to watch for on an event source.

enum IOCondition
{
	IO_IN = G_IO_IN, ///< There is data to read.
	IO_OUT = G_IO_OUT, ///< Data can be written (without blocking).
	IO_PRI = G_IO_PRI, ///< There is urgent data to read.
	IO_ERR = G_IO_ERR, ///< Error condition.
	IO_HUP = G_IO_HUP, ///< Hung up (the connection has been broken, usually for pipes and sockets).
	IO_NVAL = G_IO_NVAL ///< Invalid request. The file descriptor is not open.
} ;

/// IOConditionField holds one or more conditions from the G::IOCondition enumeration OR'd together.

typedef unsigned int IOConditionField;

/// enum IOFlags
/// Specifies the properties of an IOChannel. Some of the flags can only be read
/// with G::IOChannel::get_flags(), but not changed with G::IOChannel::set_flags().

enum IOFlags
{
	IO_FLAG_APPEND = G_IO_FLAG_APPEND,
	///< Turns on append mode, corresponds to O_APPEND (see the documentation of the UNIX open() syscall).

	IO_FLAG_NONBLOCK = G_IO_FLAG_NONBLOCK,
	///< Turns on nonblocking mode, corresponds to O_NONBLOCK/O_NDELAY (see the documentation of the UNIX open() syscall).

	IO_FLAG_IS_READABLE = G_IO_FLAG_IS_READABLE,	/* Read only flag */
	///< Read only flag; Indicates that the io channel is readable.

	IO_FLAG_IS_WRITEABLE = G_IO_FLAG_IS_WRITEABLE,	/* Read only flag */
	///< Read only flag; Indicates that the io channel is writable..

	IO_FLAG_IS_SEEKABLE = G_IO_FLAG_IS_SEEKABLE,	/* Read only flag */
	///< Read only flag; Indicates that the io channel is seekable, i.e. that G::IOChannel::seek_position() can be used on it.

	IO_FLAG_MASK = G_IO_FLAG_MASK,
	///< Mask flag (I dont know what this means).

	IO_FLAG_GET_MASK = G_IO_FLAG_GET_MASK,
	///< Same as mask flag.

	IO_FLAG_SET_MASK = G_IO_FLAG_SET_MASK
	///< Turns on append mode and nonblocking mode.
};

/// IOFlags holds one or more flags form the G::IOFlags enumeration OR'd together.

typedef unsigned int IOFlagsField;

/// @class IOChannel iochannel.hh xfc/glib/iochannel.hh
/// @brief A GIOChannel C++ wrapper class.
///
/// The IOChannel object provides a portable method for using file descriptors, pipes,
/// and sockets, and integrating them into the main event loop. Currently full support
/// is available on UNIX platforms, support for Windows is only partially complete.
///
/// To create a new IOChannel on UNIX systems use the create() 'file descriptor' method.
/// This works for plain file descriptors, pipes and sockets. Alternatively, a channel
/// can be opened for a file in a system independent manner using open_file(). Once an
/// IOChannel has been created, it can be used in a generic manner with the methods
/// read(), write(), seek(), and close().
///
/// To add an IOChannel to the main event loop use add_watch(). Here you specify which
/// events you are interested in watching on the IOChannel, and provide a slot to be called
/// whenever these events occur.
///
/// IOChannel instances are created with an initial reference count of 1. ref() and
/// unref() can be used to increment or decrement the reference count respectively.
/// When the reference count falls to 0, the IOChannel is freed. (Though it isn't
/// closed automatically, unless it was opened using open_file().) Using add_watch()
/// increments a channel's reference count.

class IOChannel : public Trackable
{
	IOChannel(const IOChannel&);
	IOChannel& operator=(const IOChannel&);

	GIOChannel *channel_;

public:
/// @name Constructors
/// @{

	explicit IOChannel(GIOChannel *channel, bool owns_reference = true);
	///< Construct a IO channel from an existing GIOChannel.
	///< @param channel A pointer to a GIOChannel.
	///< @param owns_reference Set <EM>true</EM> if the initial reference count is owned by this object.
	///<
	///< The IOChannel object takes over the ownership of the GIOChannel and
	///< unreferences it when the destructor is called.

	~IOChannel();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	static Pointer<IOChannel> create(const String& filename, const char *mode, G::Error *error);
	///< Create a new channel for the file <EM>filename</EM> using the mode <EM>mode</EM>.
	///< @param filename A string containing the name of a file.
	///< @param mode One of "r", "w", "a", "r+", "w+", "a+". These have the same meaning as in fopen().
	///< @param error A location to return an error of type G_FILE_ERROR.
	///< @return A smart pointer to a new IOChannel on success, or null on failure.
	///<
	///< This channel will be closed automatically when the last reference to it is dropped.

	static Pointer<IOChannel> create(int fd, bool close_on_unref = false);
	///< Create a new channel for the file descriptor <EM>fd</EM>.
	///< @param fd A file descriptor.
	///< @param close_on_unref Whether to close the channel on the final unref of the GIOChannel data structure.
	///< @return A smart pointer to a new IOChannel.
	///<
	///< On UNIX systems this works for plain files, pipes, and sockets. The default
	///< encoding for an IOChannel is UTF-8. If your application is reading output from a
	///< command using via pipe, you may need to set the encoding to the encoding of the
	///< current locale (see g_get_charset()) with the IOChannel::set_encoding() method.

	static IOChannelError error_from_errno(int errno_number);
	///< Converts an errno error number to a IOChannelError.
	///< @param errno_number An errno error number, e.g. EINVAL.
	/// @return An IOChannelError error number, e.g. IO_CHANNEL_ERROR_INVAL.

/// @}
/// @name Accessors
/// @{

	GIOChannel* g_io_channel() const;
	///< Get a pointer to the GIOChannel structure.

	operator GIOChannel* () const;
	///< Conversion operator; Safely converts a G::IOChannel object into a GIOChannel pointer.

	size_t get_buffer_size() const;
	///< Gets the buffer size.
	///< @return The size of the buffer.

	IOConditionField get_buffer_condition() const;
	///< Gets an IOCondition depending on whether there is data to be read/space to write data
	///< in the internal buffers in the IOChannel.
	///< @return A G::IOCondition.
	///<
	///< Note only the flags IO_IN and IO_OUT may be set.

	IOFlagsField get_flags() const;
	///< Gets the current flags for the channel, including read-only flags such as IO_FLAG_IS_READABLE.
	///< @return The G::IOFlags which are set on the channel.
	///<
	///< The values of the flags IO_FLAG_IS_READABLE and IO_FLAG_IS_WRITEABLE are cached
	///< for internal use by the channel when it is created. If they should change at some
	///< later point (e.g. partial shutdown of a socket with the UNIX shutdown() function),
	///< the user should immediately call get_flags() to update the internal values of these
	///< flags.

	String get_line_term() const;
	///< Gets the string that the channel uses to determine where in the file a line break
	///< occurs.
	///< @return The line termination string (a null String indicates auto detection).

	bool get_buffered() const;
	///< Returns whether the channel is buffered.
	///< @return <EM>true</EM> if the channel is buffered.

	String get_encoding() const;
	///< Gets the encoding for the input/output of the channel.
	///< @return A string containing the encoding.
	///<
	///< The internal encoding is always UTF-8. The encoding <EM>null</EM> makes the channel safe
	///< for binary data.

	bool get_close_on_unref() const;
	///< Returns whether the file/socket/whatever associated with the channel will be closed
	///< when the channel receives its final unref and is destroyed.
	///< @return Whether the channel will be closed on the final unref of the IOChannel data structure.
	///<
	///< The return value is <EM>true</EM> for channels created from a filename, and <EM>false</EM>
	///< for all other channels.

	int get_fd() const;
	///< Returns the file descriptor of the UNIX channel created by the create() file descriptor method.
	///< @return The file descriptor of the channel.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increase an IO channel's reference count by one.

	virtual void unref();
	///< Decrease an IO channel's reference count by one.
	///< When the reference count becomes zero for a heap object delete is called.
	///< Remember, as with all XFC Objects you must call unref() on a dynamically
	///< allocated IOChannel, not delete. If you use a smart you don't need to call
	///< unref(), the smart pointer will do that for you. You don't need to call unref()
	///< on an IOChannel allocated on the stack unless you first called ref().

	IOStatus close(bool flush, G::Error *error = 0);
	///< Close an IO channel.
	///< @param flush Set <EM>true</EM> to flush pending data.
	///< @param error The location to store an IOChannelError
	///< @return The status of the operation.
	///<
	///< Any pending data to be written will be flushed if <EM>flush</EM> is true.
	///< The channel will not be freed until the last reference is dropped using unref().
	///< Note that you don't need top call unref() with smart pointers, the smart pointer
	///< does that for you.

	void set_buffer_size(size_t size);
	///< Sets the buffer size.
	///< @param size The size of the buffer (0 == pick a good size).

	IOStatus set_flags(IOFlagsField flags, G::Error *error = 0);
	///< Sets the (writeable) flags in the channel to (flags & IO_CHANNEL_SET_MASK).
	///< @param flags The G::IOFlags to set on the IO channel.
	///< @param error The location to store an error of type IOChannelErro.
	///< @return The status of the operation.

	void set_line_term(const String& line_term);
	///< This sets the string that the channel uses to determine where in the file a line break occurs.
	///< @param line_term The line termination string (use null for auto detect).
	///<
	///< Auto detection breaks on "\n", "\r\n", "\r", "\0", and the Unicode paragraph separator.
	///< Auto detection should not be used for anything other than file-based channels.

	void set_buffered(bool buffered);
	///< Set the buffering state of the channel (the default state is buffered).
	///< @param buffered Whether to set the channel buffered or unbuffered.
	///<
	///< The buffering state can only be set if the channel's encoding is null. For any other
	///< encoding, the channel must be buffered. A buffered channel can only be set unbuffered if
	///< the channel's internal buffers have been flushed. Newly created channels or channels which
	///< have returned IO_STATUS_EOF do not require such a flush. For write-only channels, a call
	///< to flush() is sufficient. For all other channels, the buffers may be flushed by a call to
	///< seek(). This includes the possibility of seeking with seek type IO_SEEK_CUR and an offset of
	///< zero. Note that this means that socket-based channels cannot be set unbuffered once they
	///< have had data read from them.

	IOStatus set_encoding(const char *encoding, G::Error *error = 0);
	///< Sets the encoding for the input/output of the channel.
	///< @param encoding The encoding type.
	///< @param error The location to store an error of type GConvertError.
	///< @return IO_STATUS_NORMAL if the encoding was successfully set.
	///<
	///< The internal encoding is always UTF-8. The default encoding for the external file is UTF-8.
	///< The encoding 'null' is safe to use with binary data. The encoding can only be set if one of the
	///< following conditions is true:
	///< -# The channel was just created, and has not been written to or read from yet.
	///< -# The channel is write-only.
	///< -# The channel is a file, and the file pointer was just repositioned by a call
	///<    to seek() (this flushes all the internal buffers).
	///< -# The current encoding is NULL or UTF-8.
	///< -# One of the read functions has just returned IO_STATUS_EOF (or, in the case of read_to_end(),
	///<    IO_STATUS_NORMAL).
	///< -# One of the read() methods has returned IO_STATUS_AGAIN or IO_STATUS_ERROR. This may be useful
	///<    in the case of G_CONVERT_ERROR_ILLEGAL_SEQUENCE. Returning one of these statuses from
	///<    read_line() or read_to_end() does not guarantee that the encoding can be changed.
	///< Channels which do not meet one of the above conditions cannot call seek with an offset of IO_SEEK_CUR,
	///< and, if they are "seekable", cannot call write after calling one of the read() methods.

	void set_close_on_unref(bool do_close);
	///< Setting this flag to true for a channel you have already closed can cause problems.
	///< @param do_close Whether to close the channel on the final unref of the GIOChannel data structure.
	///<
	///< The default value is <EM>true</EM> for channels created by the create() filename method,
	///< and <EM>false</EM> for all other channels.

	IOStatus flush(G::Error *error = 0);
	///< Flushes the write buffer for the channel.
	///< @param error The location to store an error of type G::IOChannelError.
	///< @return The status of the operation: One of IO_CHANNEL_NORMAL, IO_CHANNEL_AGAIN, or IO_CHANNEL_ERROR.
	
	IOStatus read_line(String& str, size_t *bytes_read, G::Error *error = 0);
	///< Reads a line, including the terminating character(s), from a channel into String.
	///< @param str The line read from the IOChannel, including the line terminator.
	///< @param bytes_read The number of bytes read.
	///< @param error A location to return an error of type GConvertError or IOChannelError.
	///< @return The status of the operation.

	IOStatus read_to_end(String& str, size_t *bytes_read, G::Error *error = 0);
	///< Reads data from a channel.
	///< @param str A String to read the data into.
	///< @param bytes_read The number of bytes read.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError.
	///< @return The status of the operation.

	IOStatus read(char *buffer, size_t count, size_t *bytes_read, G::Error *error = 0);
	///< Reads data from a channel.
	///< @param buffer A buffer to read data into.
	///< @param count The size of the buffer.
	///< @param bytes_read The number of bytes read.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError.
	///< @return The status of the operation.
	///<
	///< Note that the buffer may not be complelely filled even if there is data in the
	///< buffer if the remaining data is not a complete character. The <EM>bytes_read</EM>
	///< may be zero even on success if <EM>count</EM> < 6 and the channel's encoding is
	///< non-null. This indicates that the next UTF-8 character is too wide for the buffer.

	IOStatus read(String& str, size_t *bytes_read, G::Error *error = 0);
	///< Reads at most <EM>count</EM> data from a channel into a String.
	///< @param str A String to read the data into.
	///< @param bytes_read The number of bytes read.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError.
	///< @return The status of the operation.
	///<
	///< Note that the buffer may not be complelely filled even if there is data in the
	///< buffer if the remaining data is not a complete character.

	IOStatus read(G::Unichar& unichar, G::Error *error = 0);
	///< This method cannot be called on a channel with a null encoding.
	///< @param unichar A location to return a unicode character.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError.
	///< @return The status of the operation.

	IOStatus write(const char *buffer, size_t count, size_t *bytes_written, G::Error *error = 0);
	///< Writes data to a channel.
	///< @param buffer A buffer to write data from.
	///< @param count The size of the buffer. If -1, the buffer is taken to be a null-terminated string.
	///< @param bytes_written The location to store the number of bytes written.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError
	///< @return The status of the operation.
	///<
	///< On seekable channels with encodings other than null or UTF-8, generic mixing
	///< of reading and writing is not allowed. A call to write() may only be made on a
	///< channel from which data has been read in the cases described in the documentation
	///< for set_encoding().
	///<
	///< The <EM>bytes_read</EM> can be nonzero even if the return value is not G_IO_STATUS_NORMAL.
	///< If the return value is G_IO_STATUS_NORMAL and the channel is blocking, <EM>bytes_read</EM>
	///< will always be equal to count if count >= 0.

	IOStatus write(const String& str, size_t *bytes_written, G::Error *error = 0);
	///< Writes a String to a channel.
	///< @param str A String to write from.
	///< @param bytes_written The location to store the number of bytes written.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError
	///< @return The status of the operation.
	///<
	///< On seekable channels with encodings other than null or UTF-8, generic mixing
	///< of reading and writing is not allowed. A call to write() may only be made on a
	///< channel from which the String has been read in the cases described in the documentation
	///< for set_encoding().

	IOStatus write(G::Unichar unichar, G::Error *error = 0);
	///< This method cannot be called on a channel with a null encoding.
	///< @param unichar A unicode character.
	///< @param error A location to return an error of type GConvertError or G::IOChannelError.
	///< @return The status of the operation.

	IOStatus seek(gint64 offset, SeekType type, G::Error *error = 0);
	///< Sets the current position in the channel, similar to the standard library function fseek().
	///< @param offset The offset in bytes from the position specified by type.
	///< @param type A SeekType.
	///< @param error A location to return an error of type G::IOChannelError.
	///< @return The status of the operation.
	///<
	///< The G::SeekType IO_SEEK_CUR is only allowed in those cases where a call to set_encoding()
	///< is allowed. See the documentation for set_encoding() for details.

/// @}

};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/iochannel.inl>

#endif // XFC_G_IOCHANNEL_HH
