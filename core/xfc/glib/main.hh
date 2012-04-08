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

/// @file xfc/glib/main.hh
/// @brief A C++ interface for the GLib main event loop.
///
/// Provides G::MainContext, G::MainLoop and G::Source.

#ifndef XFC_G_MAIN_HH
#define XFC_G_MAIN_HH

#ifndef XFC_TRACKABLE_HH
#include <xfc/trackable.hh>
#endif

#ifndef XFC_G_IOCHANNEL_HH
#include <xfc/glib/iochannel.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Condition;
class Mutex;
class Source;
class TimeVal;

enum
{
	PRIORITY_HIGH = G_PRIORITY_HIGH,
	///< Use this for high priority event sources; It is not used within GLib or GTK+ (value -100).

	PRIORITY_DEFAULT = G_PRIORITY_DEFAULT,
	///< Use this for default priority event sources; In GLib this priority is used	
	///< when adding timeout functions with g_timeout_add(); In GDK this priority
	///< is used for events from the X server (value 0).

	PRIORITY_HIGH_IDLE = G_PRIORITY_HIGH_IDLE,
	///< Use this for high priority idle functions (value 100); GTK+ uses G_PRIORITY_HIGH_IDLE + 10
	///< for window resizes and G_PRIORITY_HIGH_IDLE + 20 for window redraws, to ensure that any
	///< pending resizes are processed before any pending redraws, so that widgets are not redrawn
	///< twice unnecessarily; <B>Note</B> that you will interfere with GTK+ if you use a priority above
	///< G_PRIORITY_HIGH_IDLE + 10 (that is, GTK_PRIORITY_RESIZE).

	PRIORITY_DEFAULT_IDLE = G_PRIORITY_DEFAULT_IDLE,
	///< Use this for default priority idle functions; In GLib this priority is used when
	///< adding idle functions with g_idle_add() (value 200).

	PRIORITY_LOW = G_PRIORITY_LOW
	///<  Use this for very low priority background tasks; It is not used within GLib or GTK+ (value 300).
};

/// @name Time Methods
/// @{

void get_current_time(TimeVal& timeval);
///< Equivalent to the UNIX gettimeofday() function, but portable.
///< @param timeval A TimeVal object in which to store the current time.

/// @}

/// @class PollFD main.hh xfc/glib/main.hh
/// A C++ wrapper for the GPollFD.
///
/// PollFD is used to hold information about a file descriptor being watched (polled)
/// for a particular context or event source.

class PollFD
{
	GPollFD poll_fd_;
	
public:
/// @name Constructors
/// @{
	
	PollFD();
	///< Constructs an empty PollFD object;
	
	PollFD(int fd);
	///< Constructs a new PollFD object for the file descriptor <EM>fd</EM>;
	///< @param fd The file descriptor to poll.
	
	PollFD(int fd, IOConditionField events);
	///< Constructs a new PollFD object that polls the specified <EM>events</EM>
	///< for the file descriptor <EM>fd</EM>;
	///< @param fd The file descriptor to poll.
	///< @param events A bitwise combination of flags from G::IOCondition, specifying which events to poll for.
	///<
	///< Typically for reading from a file descriptor you would use G::IO_IN | G::IO_HUP | G::IO_ERR,
	///< and for writing you would use G::IO_OUT | G::IO_ERR. 

/// @}
/// @name Accessors
/// @{
	
	GPollFD* g_poll_fd() const ;
	///< Get a pointer to the GPollFD structure.

	operator GPollFD* () const;
	///< Conversion operator; safely converts a PollFD to a GPollFD pointer.

	int fd() const;
	///< Gets the file descriptor being polled.
	///< @return The file descriptor. 
	
	IOConditionField events() const;
	///< Gets the events that should be polled for.
	///< @return A bitwise combination of flags from G::IOCondition.
	
	IOConditionField revents() const;
	///< Gets the bitwise combination of flags returned from poll() that indicate which events occurred. 
	///< @return A bitwise combination of flags from G::IOCondition. 
	
/// @}
/// @name Methods
/// @{
	
	void set_fd(int fd);
	///< Sets the file descriptor to poll.
	///< @param fd The file descriptor. 

	void set_events(IOConditionField events);
	///< Sets the events that should be polled for.
	///< @param events A bitwise combination of flags from G::IOCondition.
	///<
	///< Typically for reading from a file descriptor you would use G::IO_IN | G::IO_HUP | G::IO_ERR,
	///< and for writing you would use G::IO_OUT | G::IO_ERR. 
	
	void set(int fd, IOConditionField events);
	///< Sets the file descriptor to poll and the events to poll for;
	///< @param fd The file descriptor to poll.
	///< @param events A bitwise combination of flags from G::IOCondition, specifying which events to poll for.
	///<
	///< Typically for reading from a file descriptor you would use G::IO_IN | G::IO_HUP | G::IO_ERR,
	///< and for writing you would use G::IO_OUT | G::IO_ERR. 

/// @}
};	

/// @class MainContext main.hh xfc/glib/main.hh
/// A C++ interface for the GMainContext.
///
/// MainContext is an object representing a set of sources to be handled in a main loop.
/// Different main contexts should be used for different threads. Single iterations
/// of a main context can be run with iteration(). 
///
/// In some cases, more detailed control of exactly how the details of the main loop work
/// is desired, for instance, when integrating the G::MainLoop with an external main loop.
/// In such cases, you can call the component methods of iteration() directly. These methods
/// are prepare(), query(), check() and dispatch(), and must be called in that sequence. The
/// sequence can be stopped at any time, and you can return to prepare(), but you must never
/// skip a step or call one of the methods twice (except for query()).
///
/// Whenever prepare() is invoked, any pending sources are cleared, and checking starts
/// again from scratch.

class MainContext : public Trackable
{
	MainContext(const MainContext&);
	MainContext& operator=(const MainContext&);

	GMainContext *context_;
	int ref_count;

public:
/// @name Constructors
/// @{

	MainContext();
	///< Construct a new main context object.

	explicit MainContext(GMainContext *context, bool owns_reference = true);
	///< Construct a main context from an existing GMainContext.
	///< @param context A pointer to a GMainContext.
	///< @param owns_reference Set <EM>true</EM> if the initial reference count is owned by this object.
	///<
	///< The MainContext object takes over the ownership of the GMainContext and
	///< unreferences it when the destructor is called.

	virtual ~MainContext();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GMainContext* g_main_context() const;
	///< Get a pointer to the GMainContext object.

	operator GMainContext* () const;
	///< Conversion operator; Safely converts a G::MainContext object into a GMainContext pointer.

	bool pending() const;
	///< Checks if any sources have pending events for the given context.
	///< @return <EM>true</EM> if events are pending.

	GPollFunc get_poll_func() const;
	///< Gets the poll function set by set_poll_func().
	///< @return The poll function.

/// @}
/// @name Accessors
/// @{

	static Pointer<MainContext> get_default();
	///< Gets the default main context.
	///< @return The default main context.
	///<
	///< This is the main context used for main loop functions when a main context is not explicitly specified.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increases the reference count of the main context by one.

	virtual void unref();
	///< Decreases the reference count of the main context by one.
	///< When the reference count becomes zero delete is called. Remember, as with all XFC Objects
	///< you must call unref() on a dynamically allocated IOChannel, not delete. If you use a smart
	///< you don't need to call unref(), the smart pointer will do that for you. You must also call
	///< unref() on an IOChannel allocated on the stack because IOChannels don't get passed on to
	///< owner objects that manage their reference count (like widgets in a container).

	bool iteration(bool may_block);
	///< Runs a single iteration of the main loop.
	///< @param may_block Whether the call may block.
	///< @return <EM>true</EM> if events were dispatched.
	///<
	///< This involves checking to see if any event sources are ready to be processed, then if
	///< no events sources are ready and <EM>may_block</EM> is true, waiting for a source to become
	///< ready, then dispatching the highest priority events sources that are ready. Note that even
	///< when <EM>may_block</EM> is true, it is still possible for iteration() to return false,
	///< since the the wait may be interrupted for other reasons than an event source becoming ready.

	Pointer<Source> find_source(unsigned int source_id);
	///< Finds a Source given the source ID.
	///< @param source_id The source ID, as returned by attach() or get_id(). 
	///< @return The G::Source if found, otherwise null.
		
	void wakeup();
	///< If the context is currently waiting in a poll(), interrupt the poll(), and continue the iteration process.
	
	bool acquire();
	///< Tries to become the owner of the context. 
	///< @return <EM>true</EM> if the operation succeeded, and this thread is now the owner of the context.
	///<	
	///< If some other context is the owner of the context, returns <EM>false</EM> immediately. 
	///< Ownership is properly recursive: the owner can require ownership again and will release
	///< ownership when release() is called as many times as acquire(). 
	///< 
	///< You must be the owner of a context before you can call prepare(), query(), check() and dispatch().

	void release();
	///< Releases ownership of the context previously acquired by this thread with acquire(). 
	///< If the context was acquired multiple times, then only release ownership when release()
	///< is called as many times as it was acquired.
	
	bool wait(Condition& condition, Mutex& mutex);
	///< Tries to become the owner of the specified context, as with acquire(), but if another thread
	///< is the owner, atomically drop mutex and wait on <EM>condition</EM> until that owner releases
	///< ownership or until <EM>conditon</EM> is signaled, then try again (once) to become the owner.
	///< @param condition A condition variable. 
	///< @param mutex A mutex, currently held. 
	///< @return <EM>true</EM> if the operation succeeded, and this thread is now the owner of context.	
	
	bool prepare(int *priority);
	///< Prepares to poll sources within a main loop. 
	///< @param priority The location to store the priority of the highest priority source already ready.
	///< @return <EM>true</EM> if some source is ready to be dispatched prior to polling. 
	///< 
	///< The resulting information for polling is determined by calling query().

	bool query(int max_priority, int *timeout, std::vector<PollFD>& fds);
	///< Determines the information necessary to poll the main loop.
	///< @param max_priority The maximum priority source to check. 
	///< @param timeout The location to store the timeout to be used in polling. 
	///< @param fds A vector of PollFD to store poll records that need to be polled. 
	///< @return <EM>true</EM> if any records have been stored in the vector.
	
	int check(int max_priority, std::vector<PollFD>& fds);
	///< Passes the results of polling back to the main loop.
	///< @param max_priority The maximum numerical priority of sources to check.
	///< @param fds A vector of PollFD that was passed to the last call to query().  
	///< @returns <EM>true</EM> if some sources are ready to be dispatched.

	void dispatch();
	///< Dispatches all pending sources.
	
	void add_poll(PollFD& fd, int priority);
	///< Adds a file descriptor to the set of file descriptors polled for this context. 
	///< @param fd A PollFD object holding information about a file descriptor to watch. 
	///< @param priority The priority for this file descriptor.
	///< 
	///< This will very seldomly be used directly. Instead a typical event source
	///< will use G::Source::add_poll() instead. The <EM>priority</EM> should be the same
	///< as the priority used for G::Source::attach() to ensure that the file descriptor
	///< is polled whenever the results may be needed.	
	
	void remove_poll(PollFD& fd);
	///< Removes the file descriptor from the set of file descriptors to be polled for the context.
	///< @param fd A PollFD descriptor previously added with add_poll().
	
	void set_poll_func(GPollFunc func);
	///< Sets the function to use to handle the polling of file descriptors. 
	///< @param func The function to call to poll all file descriptors.
	///<	
	///< It will be used instead of the poll() system call (or GLib's replacement function,
	///< which is used where poll() isn't available). This function could possibly be used to
	///< integrate the GLib event loop with an external event loop.

/// @}
};

/// @class MainLoop main.hh xfc/glib/main.hh
/// A C++ interface for the GMainLoop.
///
/// The main event loop manages all the available sources of events for GLib and GTK+ 
/// applications. These events can come from any number of different types of sources
/// such as file descriptors (plain files, pipes or sockets) and timeouts. New types
/// of event sources can also be added using G::Source::attach().
///
/// To allow multiple independent sets of sources to be handled in different threads, each
/// source is associated with a MainContext. A MainContext can only be running in a single
/// thread, but sources can be added to it and removed from it from other threads.
///
/// Each event source is assigned a priority. The default priority, G::PRIORITY_DEFAULT,
/// is 0. Values less than 0 denote higher priorities. Values greater than 0 denote lower
/// priorities. Events from high priority sources are always processed before events from
/// lower priority sources.
///
/// Idle functions can also be added, and assigned a priority. These will be run whenever
/// no events with a higher priority are ready to be processed.
///
/// MainLoop represents a single invocation of the main event loop. After constructing a
/// MainLoop and adding the initial event sources, run() is called. This continuously checks
/// for new events from each of the event sources and dispatches them. This continues until
/// finally, the processing of an event from one of the sources leads to a call to quit() to
/// exit the main loop, and run() returns.
///
/// It is possible to create new instances of MainLoop recursively. This is often used in
/// GTK+ applications when showing modal dialog boxes. Note that event sources are associated
/// with a particular MainContext, and will be checked and dispatched for all main loops
/// associated with that MainContext.

class MainLoop : public Trackable
{
	MainLoop(const MainLoop&);
	MainLoop& operator=(const MainLoop&);

	GMainLoop *loop_;
	int ref_count;

public:
/// @name Constructors
/// @{

	MainLoop();
	///< Construct a new main loop object using the default MainContext.

	MainLoop(MainContext& context);
	///< Construct a new main loop object using the specified MainContext.
	///< @param context A MainContext.

	virtual ~MainLoop();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GMainLoop* g_main_loop() const;
	///< Get a pointer to the GMainLoop object.

	operator GMainLoop* () const;
	///< Conversion operator; Safely converts a G::MainLoop object into a GMainLoop pointer.

	bool is_running() const;
	///< Checks to see if the main loop is currently being run via run().
	///< @return <EM>true</EM> if the main loop is currently being run.

	Pointer<MainContext> get_context() const;
	///< Obtains the MainContext of loop.
	///< @return The MainContext of loop

/// @}
/// @name Accessors
/// @{
	
	static int depth();
	///< Get the main loop recursion level in the current thread.
	///< @return The main loop recursion level in the current thread.
	///<
	///< When called from the toplevel, this method returns 0. When called from
	///< within a callback from G::MainContext::iteration() (or G::MainLoop::run(), etc.)
	///< it returns 1. When called from within a callback to a recursive call to 
	///< G::MainContext::iteration(), it returns 2. And so forth.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increases the reference count on a main loop object by one.

	virtual void unref();
	///< Decreases the reference count on a main loop object by one.
	///< When the reference count becomes zero for a heap object delete is called.
	///< Remember, as with all XFC Objects you must call unref() on a dynamically
	///< allocated MainLoop, not delete. If you use a smart you don't need to call
	///< unref(), the smart pointer will do that for you. You don't need to call
	///< unref() on a loop allocated on the stack unless you first called ref().

	void run();
	///< Runs a main loop until quit() is called on the loop.
	///< If this is called for the thread of the loop's MainContext, it will process
	///< events from the loop, otherwise it will simply wait.

	void quit();
	///< Stops a main loop from running, and any calls to run() for the loop will return.

/// @}
};

/// @class Source main.hh xfc/glib/main.hh
/// A GSource C++ interface.
///
/// A Source corresponds to a single source of input. When sources are created they
/// aren't associated with any main context. Once attached, a source is permanently
/// associated with a particular context and can't be moved to another context.
///
/// Source is the base class for the built-in ChildWatchSource, TimeoutSource, IdleSource
/// and IOSource types. In most cases the built-in source types should be enough. When 
/// they aren't, or when you need something more powerful, you can create your own custom
/// event source by subclassing G::CustomSource and overriding its pure virtual methods. 

class Source : public Trackable
{
	Source(const Source&);
	Source& operator=(const Source&);

	GSource *source_;

public:
	typedef sigc::slot<bool> SourceSlot;
	///< Signature of the callback slot passed to timeout, idle and custom sources.
	///< <B>Example:</B> Method signature for SourceSlot.
	///< @code
	///< bool method();
	///< // return: The slot should return false if the source should be removed.
	///< @endcode

/// @name Constructors
/// @{

	Source(GSource *source, bool owns_reference = true);
	///< Construct a source from an existing GSource object.
	///< @param source A pointer to a GSource.
	///< @param owns_reference Set <EM>true</EM> if the initial reference count is owned by this object.
	///<
	///< The Source object takes over the ownership of the GSource and unreferences
	///< it when the destructor is called.
	
	virtual ~Source();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GSource* g_source() const;
	///< Get a pointer to the GSource object.

	operator GSource* () const;
	///< Conversion operator; Safely converts a G::Source object into a GSource pointer.

	int get_priority() const;
	///< Gets the priority of the source.
	///< @return The priority of the source.

	bool get_can_recurse() const;
	///< Checks whether a source is allowed to be called recursively (see set_can_recurse()).
	///< @return Whether recursion is allowed.

	unsigned int get_id() const;
	///< Gets the numeric ID for a particular source.
	///< @return The ID for the source.

	Pointer<MainContext> get_context() const;
	///< Gets the main context with which the source is associated.
	///< @return The associated MainContext, or null if a context has not yet been added to the source.
	///<
	///< Calling this function on a destroyed source is an error.

	void get_current_time(TimeVal& timeval);
	///< Gets the "current time" to be used when checking this source.
	///< @param timeval A TimeVal object in which to store the current time.
	///<
	///< The advantage of calling this function over calling G::get_current_time()
	///< directly is that when checking multiple sources, GLib can cache a single value
	///< instead of having to repeatedly get the system time.

	bool is_attached(G::MainContext& context) const;
	///< Determines whether <EM>context</EM> is attached to this source.
	///< @return <EM>true</EM> if context is attached to this source.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increase the source reference count by one.

	virtual void unref();
	///< Decrease the source reference count by one.
	///< When the reference count becomes zero for a heap object delete is called.
	///< Remember, as with all XFC Objects you must call unref() on a dynamically
	///< allocated IOChannel, not delete. If you use a smart you don't need to call
	///< unref(), the smart pointer will do that for you. You don't need to call unref()
	///< on a source allocated on the stack unless you first called ref().

	unsigned int attach(MainContext *context = 0);
	///< Adds the source to <EM>context</EM> so that it will be executed within that context.
	///< @param context A MainContext, or null to use the default context.
	///< @return The ID for the source within the MainContext.

	void destroy();
	///< Removes a source from its MainContext, if any, and marks it as destroyed.
	///< After calling this method the source cannot be subsequently added to another context.

	void set_priority(int priority);
	///< Sets the priority of the source.
	///< @param priority The new priority.
	///<
	///< While the main loop is being run, the source will be dispatched if it is ready
	///< to be dispatched and no sources at a higher (numerically smaller) priority are
	///< ready to be dispatched.

	void set_can_recurse(bool can_recurse);
	///< Sets whether a source can be called recursively.
	///< @param can_recurse Whether recursion is allowed for this source.
	///<
	///< If <EM>can_recurse</EM> is true, while the source is being dispatched
	///< the source will be processed normally. Otherwise, all processing of the
	///< source is blocked until the dispatch function returns.

/// @}
};

/// @class Source main.hh xfc/glib/main.hh
/// A Custom GSource C++ interface.
///
/// One of the unusual features of the GLib/GTK+ main loop functionality is that new types
/// of event source can be created and used in addition to the built-in type of event source.
/// For example, GTK+ creates a new event source type to handle GDK events. A new source type
/// is created by deriving it from CustomSource. The three source methods prepare(), check() 
/// and dispatch() determine the behavior of new source types. 
///
/// New source types basically interact with with the main context in two ways. Their prepare
/// method can set a timeout to determine the maximum amount of time that the main loop will
/// sleep before checking the source again. In addition, or as well, the source can add file
/// descriptors to the set that the main context checks using G::Source::add_poll(). 
///
/// CustomSource has three pure virtual methods: prepare(), check() and dispatch(), that must
/// be overridden in dervied classes. The prepare method asks a source two things: does it 
/// have any events, and when does it need to be asked again. For example, a TimeoutSource
/// requires that it wakes up after a certain time elapses. The check method ask a source if
/// it has any events now, taking into account the results of the poll() call. The dispatch
/// method dispatches the sources with events ready by calling the passed in slot.
///
/// For idle sources, the prepare and check methods should always return <EM>true</EM> to 
/// indicate that the source is always ready to be processed. The prepare function should also 
/// return a timeout value of 0 to ensure that the poll() call doesn't block (since that would
/// be time wasted which could have been spent running the idle function). 
///
/// For timeout sources, the prepare and check methods should both return <EM>true</EM> if the
/// timeout interval has expired. The prepare function also returns a timeout value to ensure 
/// that the poll() call doesn't block too long and miss the next timeout. 
///
/// For file descriptor sources, the prepare method typically returns <EM>false</EM>, since it
/// must wait until poll() has been called before it knows whether any events need to be processed.
/// It should set the returned timeout to -1 to indicate that it doesn't mind how long the poll()
/// call blocks. In the check method, it tests the results of the poll() call to see if the 
/// required condition has been met, and returns <EM>true</EM> if so.

class CustomSource : public Source
{
	CustomSource(const CustomSource&);
	CustomSource& operator=(const CustomSource&);

protected:
/// @name Constructors
/// @{
	
	CustomSource();
	///< Constructs a new Source object. The source will not initially be associated
	///< with any MainContext and must be added to one with G::Source::attach() before
	///< it will be executed. Custom sources must override the pure virutal methods
	///< prepare(), check() and dispatch().
	
/// @}

public:
/// @name Constructors
/// @{

	virtual ~CustomSource();
	///< Destructor.

/// @}
/// @name Pure virtual methods that must be overridden in derived classes
/// @{

	virtual bool prepare(int& timeout) = 0;
	///< Called before all the file descriptors are polled. 
	///< @param timeout The maximum time to wait for an event of the file descriptors.
	///<		
	///< If the source can determine that it is ready here (without waiting for the
	///< results of the system poll() call) it should return <EM>true</EM>. It can also
	///< return a <EM>timeout</EM> value which should be the maximum timeout (in milliseconds)
	///< which should be passed to the poll() call. The actual timeout used will be -1 if all
	///< sources returned -1, or it will be the minimum of all the timeout values returned
	///< which were >= 0. A negative timeout value indicates an infinite timeout.
		
	virtual bool check() = 0;
	///< Called after all the file descriptors are polled. The source should return <EM>true</EM>
	///< if it is ready to be dispatched. Note that some time may have passed since the previous
	///< prepare method was called, so the source should be checked again here.
	
	virtual bool dispatch(const SourceSlot *slot) = 0;
	///< Called to process the event source, after either the prepare or check method
	///< returned <EM>true</EM> to indicate that an event was pending. 
	///< @return <EM>true</EM> to continue watching the source, or <EM>false</EM> to remove the source.
	///<
	///< The dispatch method is passed a callback slot which it should call (e.g. (*slot)()).
	///< The callback slot may be null if the source was never connected to a callback slot using
	///< connect(). If false is returned, the Source object will be deleted when its reference
	///< count reaches zero.

/// @}
/// @name Methods
/// @{

	void add_poll(PollFD& fd);
	///< Adds a file descriptor to the set of file descriptors polled for this source.
	///< @param fd A PollFD object holding information about a file descriptor to watch.
	///<	 
	///< This is usually called from a constructor to add a new event source. 
	///< The event source's check function will typically test the G::PollFD::revents()
	///< field and return <EM>true</EM> if events need to be processed.
	
	void remove_poll(PollFD& fd);
	///< Removes a file descriptor from the set of file descriptors polled for this source.
	///< @param fd A PollFD object previously passed to add_poll().
	
	sigc::connection connect(const SourceSlot& slot);
	///< Connects the callback slot to the custom source.
	///< @param slot The callback slot, of type sigc::slot<bool>.

/// @}
};

/// @class ChildWatchSource main.hh xfc/glib/main.hh
/// A child watch GSource C++ interface.
///
/// A slot connected to a ChildWatchSource is called when the child indicated by pid exits,
/// at a default priority, G_PRIORITY_DEFAULT.
///
/// See also G::ChildWatchSignal.

class ChildWatchSource : public Source
{
	ChildWatchSource(const ChildWatchSource&);
	ChildWatchSource& operator=(const ChildWatchSource&);

public:
	typedef sigc::slot<void, GPid, int> WatchSlot;				       
	/// Signature for the callback slot to call when a child process being watched exits,
	/// at a default priority G::PRIORITY_DEFAULT.
	///<
	///< <B>Example:</B> Method signature for WatchSlot.
	///< @code
	///< void method(GPid pid, int status);
	///< @endcode

/// @name Constructors
/// @{

	ChildWatchSource(GPid pid);
	///< Constructs a new child watch source. 
	///< @param pid The process id of a child process to watch. 
	///<
	///< The source will not initially be associated with any main context and
	///< must be added to one with G::Source::attach() before it will be executed. 
	///< Note that on platforms where GPid must be explicitely closed pid must not
	///< be closed while the source is still active (see G::Spawn::close_pid()).
	///< Typically, you will want to call G::Spawn::close_pid() in the callback
	///< slot method for the source.
	///<
	///< To set the callback slot call set_callback(). To override the default
	///< priority <EM>PRIORITY_DEFAULT</EM> call set_priority().
	
	ChildWatchSource(GPid pid, const WatchSlot& slot);
	///< Constructs a new child watch source. 
	///< @param pid The process id of a child process to watch. 
	///< @param slot The child watch callback slot, of type sigc::slot<void, GPid, int>.
	///<
	///< The source will not initially be associated with any main context and
	///< must be added to one with G::Source::attach() before it will be executed. 
	///< Note that on platforms where GPid must be explicitely closed pid must not
	///< be closed while the source is still active (see G::Spawn::close_pid()).
	///< Typically, you will want to call G::Spawn::close_pid() in the callback
	///< slot method for the source.

/// @}
/// @name Methods
/// @{

	sigc::connection connect(const WatchSlot& slot);
	///< Connects the callback slot to the child watch source.
	///< @param slot The callback slot, of type sigc::slot<void, GPid, int>.

/// @}
};

/// @class TimeoutSource main.hh xfc/glib/main.hh
/// A timeout GSource C++ interface.
///
/// TimeoutSource is a source that's called at regular intervals, with the given priority.
/// The connected slot is called repeatedly until it returns false, at which point the timeout
/// is automatically destroyed and will not be called again. The first call to the slot
/// will be at the end of the first interval.
///
/// See also G::TimeoutSignal.

class TimeoutSource : public Source
{
	TimeoutSource(const TimeoutSource&);
	TimeoutSource& operator=(const TimeoutSource&);

public:
/// @name Constructors
/// @{

	TimeoutSource(unsigned int interval);
	///< Constructs a new timeout source that can be associated with any main context.
	///< @param interval The time between calls to the function, in milliseconds.
	///<
	///< G::Source::attach() must be called to attach the source to a context.
	///< To set the callback slot call set_callback(). To override the default
	///< priority <EM>PRIORITY_HIGH</EM> call set_priority().

	TimeoutSource(const SourceSlot& slot, unsigned int interval);
	///< Constructs a new timeout source that can be associated with any main context.
	///< @param slot The callback slot, of type sigc::slot<bool>.
	///< @param interval The time between calls to the function, in milliseconds.
	///<
	///< G::Source::attach() must be called to attach the source to a context.
	///< To override the default priority <EM>PRIORITY_HIGH</EM> call set_priority().

/// @}
/// @name Methods
/// @{

	sigc::connection connect(const SourceSlot& slot);	
	///< Connects the callback slot to the timeout source.
	///< @param slot The callback slot, of type sigc::slot<bool>.

/// @}
};

/// @class IdleSource main.hh xfc/glib/main.hh
/// A idle GSource C++ interface.
///
/// IdleSource is a source that's called whenever there are no higher priority events pending.
/// If the connected slot returns false it is automatically removed from the list of event sources
/// and will not be called again.
///
/// See also G::IdleSignal.

class IdleSource : public Source
{
	IdleSource(const IdleSource&);
	IdleSource& operator=(const IdleSource&);

public:
/// @name Constructors
/// @{

	IdleSource();
	///< Constructs a new idle source that can be associated with any main context.
	///< G::Source::attach() must be called to attach the source to a context.
	///< To set the callback slot call set_callback(). To override the default
	///< priority <EM>PRIORITY_DEFAULT_IDLE</EM> call set_priority().

	IdleSource(const SourceSlot& slot);
	///< Constructs a new idle source that can be associated with any main context.
	///< @param slot The callback slot, of type sigc::slot<bool>.
	///<
	///< G::Source::attach() must be called to attach the source to a context.
	///< To override the default priority <EM>PRIORITY_DEFAULT_IDLE</EM> call
	///< set_priority().

/// @}
/// @name Methods
/// @{

	sigc::connection connect(const SourceSlot& slot);	
	///< Connects the callback slot to the idle source.
	///< @param slot The callback slot, of type sigc::slot<bool>.

/// @}
};

/// @class IOSource main.hh xfc/glib/main.hh
/// A input/output GSource C++ interface.
///
/// IOSource is a source that's dispatched when <EM>condition</EM> is met for the io channel.
/// For example, if condition is G::IO_IN, the source will be dispatched when there's data
/// available for reading. If the IOSlot returns false it is automatically removed from the
/// list of event sources and will not be called again.
///
/// See also G::IOSignal.

class IOSource : public Source
{
	IOSource(const IOSource&);
	IOSource& operator=(const IOSource&);

public:
	typedef sigc::slot<bool, IOConditionField> IOSlot;
	///< Signature of the callback slot to be called when the requested condition on a IOChannel is satisfied.
	///< <B>Example:</B> Method signature for IOSlot.
	///< @code
	///< bool method(IOConditionField condition);
	///< // condition: The condition which has been satisfied.
	///< // return: The slot should return false if the event source should be removed.
	///< @endcode

/// @name Constructors
/// @{

	IOSource(G::IOChannel& channel, G::IOConditionField condition);
	///< Constructs a new io source that can be associated with any main context.
	///< @param channel A G::IOChannel.
	///< @param condition The condition to watch for.
	///<
	///< G::Source::attach() must be called to attach the source to a context.
	///< To set the callback slot call set_callback(). To override the default
	///< priority PRIORITY_DEFAULT you can call set_priority().

	IOSource(G::IOChannel& channel, G::IOConditionField condition, const IOSlot& slot);
	///< Constructs a new io source that can be associated with any main context.
	///< @param channel A G::IOChannel.
	///< @param condition The condition to watch for.
	///< @param slot The callback slot, of type sigc::slot<bool, IOChannel&, IOConditionField>.
	///<
	///< G::Source::attach() must be called to attach the source to a context. To
	///< override the default priority PRIORITY_DEFAULT you can call set_priority().

/// @}
/// @name Methods
/// @{

	sigc::connection connect(const IOSlot& slot);	
	///< Connects the callback slot to the io source.
	///< @param slot The callback slot, of type sigc::slot<bool, IOConditionField>.

/// @}
};

/// @class ChildWatchSignal main.hh xfc/main.hh
/// @brief A child watch signal class.
///
/// Slots connected to the ChildWatchSignal are called when the child indicated by pid exits,
/// at a default priority, G_PRIORITY_DEFAULT. ChildWatchSignal is a convenience class that
/// lets you connect a child watch source to the default main context. This is equivalent to
/// creating a ChildWatchSource for the default main context and connecting a slot to it. If
/// your using a different context, for example, inside a thread, use a ChildWatchSource.

class ChildWatchSignal : public sigc::trackable
{
public:
	typedef sigc::slot<void, GPid, int> SlotType;
	///< Function signature for handlers connected to this signal.

	sigc::connection connect(const SlotType& slot, GPid pid, int priority = PRIORITY_DEFAULT);
	///< Sets a callback slot to be called when the child indicated by <EM>pid</EM> exits,
	///< at a default priority, G::PRIORITY_DEFAULT.
	///< @param slot The sigc::slot to call periodically.
	///< @param pid The process id of a child process to watch. 
	///< @param priority The priority of the idle source. 
	///< @return A sigc::connection object that can be used to break or alter the connection.
	///<	
	///< Note that on platforms where GPid must be explicitely closed pid must not be
	///< closed while the source is still active (see G::Spawn::close_pid()). Typically,
	///< you will want to call (see G::Spawn::close_pid()) in the callback slot for the
	///< source.
	///<
	///< Typically the priority will be in the range between G::PRIORITY_DEFAULT_IDLE and 
	///< G::PRIORITY_HIGH_IDLE. 
};

/// A namespace instance of the ChildWatchSignal for connecting slots to be invoked periodically.

extern ChildWatchSignal child_watch_signal;

/// @class TimeoutSignal main.hh xfc/main.hh
/// @brief A Timeout signal class.
///
/// Timeout signal is a convenience class that lets you connect a callback slot to the default
/// main context. If your using a different context, for example, inside a thread, you should
/// use TimeoutSource instead. If the slot returns false the timeout source will be removed.

class TimeoutSignal : public sigc::trackable
{
public:
	typedef sigc::slot<bool> SlotType;
	///< Function signature for handlers connected to this signal.

	sigc::connection connect(const SlotType& slot, unsigned int interval, int priority = PRIORITY_DEFAULT);
	///< Sets a callback slot to be called at regular intervals, with the given priority.
	///< @param slot The sigc::slot to call periodically.
	///< @param interval The time between calls to the function, in milliseconds.
	///< @param priority The priority of the timeout source.
	///< @return A sigc::connection object that can be used to break or alter the connection.
	///<
	///< The slot is called repeatedly until it returns <EM>false</EM>, at which point
	///< the timeout is automatically destroyed and the function will not be called again.
	///< Note that timeout functions may be delayed, due to the processing of other event
	///< sources. Thus they should not be relied on for precise timing. After each call to
	///< the timeout function, the time of the next timeout is recalculated based on the
	///< current time and the given interval (it does not try to 'catch up' time lost in
	///< delays).
};

/// A namespace instance of the TimeoutSignal for connecting slots to be invoked periodically.

extern TimeoutSignal timeout_signal;

/// @class IdleSignal main.hh xfc/main.hh
/// @brief Idle signal class.
///
/// IdleSignal is a convenience class that adds a callback slot to the default main context,
/// to be called whenever there are no higher priority events pending. If your using a different
/// context, for example, inside a thread, you should use an IdleSource instead. If a connected
/// slot returns false it is automatically removed from the list of event sources and will not be
/// called again.

class IdleSignal : public sigc::trackable
{
public:
	typedef sigc::slot<bool> SlotType;
	///< Function signature for handlers connected to this signal.

	sigc::connection connect(const SlotType& slot, int priority = PRIORITY_DEFAULT_IDLE);
	///< Connect a slot to be called when the event loop is idle.
	///< @param slot The slot to call.
	///< @param priority The priority which should not be above G::PRIORITY_HIGH_IDLE.
	///< @return A connection object that can be used to break or alter the connection.
	///<
	///< You can give a priority different from G::PRIORITY_DEFAULT_IDLE to the idle function.
	///< Note that you will interfere with GTK+ if you use a priority above G::PRIORITY_RESIZE.
	///< The user function returns <EM>false</EM> to remove itself or <EM>true</EM> to have it
	///< called again.
};

/// A namespace instance of IdleSignal for connecting slots to be invoked when the event loop is idle.

extern IdleSignal idle_signal;

/// @class IOSignal main.hh xfc/main.hh
/// @brief IO signal class.
///
/// IOSource is a convenience class that adds a callback slot to the default main context, to be called
/// when a given condition is met. If your using a different context, for example, inside a thread, you
/// should use an IOSource instead. If a connected slot returns false it is automatically removed from
/// the list of event sources and will not be called again.

class IOSignal : public sigc::trackable
{
public:
	typedef sigc::slot<bool, IOConditionField> SlotType;
	///< Function signature for handlers connected to this signal.

	sigc::connection connect(G::IOChannel& channel, G::IOConditionField condition, const SlotType& slot, int priority = PRIORITY_DEFAULT);
	///< Connect a slot to be called when the event loop is idle.
	///< @param channel A G::IOChannel.
	///< @param condition The condition to watch for.
	///< @param slot The callback slot to call when the condition is satisfied.
	///< @param priority The priority of the io source.
	///< @return A connection object that can be used to break or alter the connection.
};

/// A namespace instance of IOSignal for connecting slots to be invoked when a condition is met.

extern IOSignal io_signal;

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/main.inl>

#endif // XFC_G_MAIN_HH

