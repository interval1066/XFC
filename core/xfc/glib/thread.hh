/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
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

/// @file xfc/glib/thread.hh
/// @brief A GThread C++ wrapper interface.
///
/// Provides a thread abstraction; including threads, different mutexes, conditions and thread private data.

#ifndef XFC_G_THREAD_HH
#define XFC_G_THREAD_HH

#ifndef XFC_G_MUTEX_HH
#include <xfc/glib/mutex.hh>
#endif

#ifndef XFC_G_TIMEVAL_HH
#include <xfc/glib/timeval.hh>
#endif

#ifndef SIGCXX_SIGCXX_H
#include <sigc++/sigc++.h>
#endif

namespace Xfc {

namespace G {

class Error;

/// @enum ThreadError
/// Specifies the possible errors for thread related methods.

enum ThreadError
{
	THREAD_ERROR_AGAIN = G_THREAD_ERROR_AGAIN ///< The resource temporarily unavailable.
};

/// @enum ThreadPriority
/// Specifies the priority of a thread. It is not guaranteed, that threads with different
/// priorities really behave accordingly. On some systems (e.g. Linux) only root can
/// increase priorities. On other systems (e.g. Solaris) there doesn't seem to be different
/// scheduling for different priorities. All in all try to avoid being dependent on priorities.

enum ThreadPriority
{
	THREAD_PRIORITY_LOW = G_THREAD_PRIORITY_LOW, ///< A priority lower than normal.
	THREAD_PRIORITY_NORMAL = G_THREAD_PRIORITY_NORMAL, ///< The default priority.
	THREAD_PRIORITY_HIGH = G_THREAD_PRIORITY_HIGH, ///< A priority higher than normal.
	THREAD_PRIORITY_URGENT = G_THREAD_PRIORITY_URGENT ///< The highest priority.
};

/// @class Thread thread.hh xfc/glib/thread.hh
/// A GThread C++ wrapper interface.
///
/// Threads act almost like processes, but unlike processes all threads of one process
/// share the same memory. This is good, as it provides easy communication between the
/// involved threads via this shared memory, and it is bad, because strange things
/// (so called Heisenbugs) might happen, when the program is not carefully designed.
/// Especially bad is, that due to the concurrent nature of threads no assumptions on
/// the order of execution of different threads can be done unless explicitly forced
/// by the programmer through synchronization primitives.
///
/// The aim of the thread related classes is to provide a portable means for writing
/// multi-threaded software. There are primitives for mutexes to protect the access to
/// portions of memory (Mutex, StaticMutex, RecMutex, StaticRecMutex, RWLock and
/// StaticRWLock), there are primitives for condition variables to allow synchronization
/// of threads (Condition) and finally there are primitives for thread-private data,
/// that every thread has a private instance of (Private, StaticPrivate). Last but
/// definitely not least there are primitives to portably create and manage threads
/// (Thread).
///
/// A thread of execution has an initial function. For the program's initial thread,
/// the initial function is main(). For a G::Thread, the initial function is the
/// call() or operator() function of the slot object passed to G::Thread::create().
/// A thread of execution is finished executing when its initial function returns
/// or is terminated by calling exit().
///
/// A Thread object has an associated state which is either joinable or non-joinable.
/// If a thread is joinable you can wait for the threads termination by calling join().
/// If a thread is non-joinable, the thread will just disappear when its finished
/// executing.
///
/// The lifetime of a thread of execution may be different from the thread object.
/// After a call to join(), the thread of execution will no longer exist even
/// though the thread object will continue to exist until the end of its normal
/// lifetime. The converse is also true; if a thread object is destroyed without
/// a call to join(), the thread of execution continues until its initial function
/// returns.

class Thread : private GThread, protected sigc::trackable
{
	friend class none;

	Thread();
	Thread(const Thread&);
	Thread& operator=(const Thread&);

public:
	typedef sigc::slot<void> ThreadSlot;
	///< Signature of the callback slot to execute in the new thread.
	///<
	///< <B>Example:</B> Method signature for ThreadSlot.
	///< @code
	///< void method();
	///< @endcode

/// @name Constructors
/// @{

	static Thread* create(const ThreadSlot& slot, bool joinable, G::Error *error = 0);
	///< Create a new thread with the default priority.
	///< @param slot The callback slot to execute in the new thread.
	///< @param joinable Should this thread be joinable?
	///< @param error The return location for a G::Error, or null.
	///< @return A pointer to the new thread on success, or null if an error occurs.
	///<
	///< The new thread executes the callback slot <EM>slot</EM>. The <EM>slot</EM>
	///< is owned by this method and will be released when the thread terminates. This
	///< means that you can construct and pass a slot inline, as you would when pass a
	///< slot to a signal. If you want to keep the slot around you will have to store
	///< a referenced pointer to it somewhere. If <EM>joinable</EM> is true, you can
	///< wait for this threads termination by calling join(). Otherwise the thread will
	///< just disappear, when ready.
	///<
	///< The <EM>error</EM> argument can be null to ignore errors, or non-null to
	///< report errors. The error is set, if and only if the thread could not be
	///< created.

	static Thread* create(const ThreadSlot& slot, unsigned long stack_size, bool joinable, bool bound, G::Error *error = 0);
	///< Create a new thread with the default priority and the specified stack size.
	///< @param slot The callback slot to execute in the new thread.
	///< @param stack_size A stack size for the new thread.
	///< @param joinable Should this thread be joinable?
	///< @param bound Should this thread be bound to a system thread?
	///< @param error The return location for a G::Error.
	///< @return A pointer to the new thread on success, or null if an error occurs.
	///<
	///< The new thread executes the callback slot <EM>slot</EM>. The <EM>slot</EM>
	///< is owned by this method and will be released when the thread terminates. This
	///< means that you can construct and pass a slot inline, as you would when pass a
	///< slot to a signal. If you want to keep the slot around you will have to store
	///< a referenced pointer to it somewhere.
	///<
	///< The stack gets the size <EM>stack_size</EM> or the default value for the
	///< current platform, if <EM>stack_size</EM> is 0. If <EM>joinable</EM> is true,
	///< you can wait for this threads termination by calling join(). Otherwise the
	///< thread will just disappear, when ready. If <EM>bound</EM> is true, the thread
	///< will be scheduled in the system scope, otherwise the implementation is free
	///< to do scheduling in the process scope. The first variant is more expensive
	///< resource-wise, but generally faster. On some systems (e.g. Linux) all threads
	///< are bound. The new thread calls the callback slot <EM>slot</EM>. If the thread
	///< could not be created successfully, <EM>error</EM> is set.
	///<
	///< <B>Note:</B> Only use this method when you really have to. The <EM>stack_size</EM>,
	///< and <EM>bound</EM> arguments should only be used for cases where it's inevitable.

/// @}
/// @name Accessors
/// @{

	GThread* g_thread() const;
	///< Get a pointer to the GThread structure.

	bool is_joinable() const;
	///< Determines whether the thread is joinable.
	///< @return <EM>true</EM> if the thread is joinable.

	ThreadPriority get_priority() const;
	///< Returns the thread priority.

/// @}
/// @name Accessors
/// @{

	static bool supported();
	///< This method returns, whether the thread system is initialized or not.
	///< @return <EM>true</EM> if the thread system is initialized.

	static Thread* self();
	///< This method returns the Thread corresponding to the calling thread.
	///< @return A pointer to the current thread.
	
/// @}
/// @name Methods
/// @{

	void join();
	///< Waits until the thread finishes, that is, the callback slot as given to the
	///< constructor returns, or exit() is called by the thread. All resources of
	///< thread including the GThread struct are released. The thread must have been
	///< created with joinable=true in the constructor.

	void set_priority(ThreadPriority priority);
	///< Sets the priority of thread to <EM>priority</EM>.
	///< @param priority A priority for the thread.
	///<
	///< Note, it is not guaranteed that threads with different priorities really
	///< behave accordingly. On some systems (e.g. Linux) only root can increase
	///< priorities. On other systems (e.g. Solaris) there doesn't seem to be different
	///< scheduling for different priorities. All in all try to avoid being dependent
	///< on priorities.

/// @}
/// @name Methods
/// @{

	static void init(GThreadFunctions *vtable = 0);
	///< Before you use a thread related method, call init() to initialize the thread system.
	///< @param vtable A function table of type GThreadFunctions, that provides the
	///< entry points to the thread system to be used.
	///<
	///< Most of the time you will only have to call init(null). Note you should only
	///< call init() with a non-null parameter if you really know what you are doing.
	///< init() must not be called directly or indirectly as a callback from GLib. Also
	///< no mutexes may be currently locked, while calling init().
	///<
	///< Note, do not call gdk_threads_init(). This method calls gdk_threads_init() for you.
	///< init() can only be called once. On the second call it will abort with an error. If
	///< you want to make sure, that the thread system is initialized, you can do that too:
	///<
	///< <B>Example:</B> Checking if the thread system has been initialized.
	///< @code
	///< if (!G::Thread::supported())
	///< 	G::Thread::init();
	///< @endcode
	///<
	///< After that line either the thread system is initialized or the program will abort,
	///< if no thread system is available in GLib, i.e. either G_THREADS_ENABLED is not
	///< defined or G_THREADS_IMPL_NONE is defined.
	///<
	///< If no thread system is available and vtable is null or if not all elements of
	///< vtable are non-null, then G::Thread::init() will abort. To Initialize the thread
	///< system with errorcheck mutexes vtable must be null and G_ERRORCHECK_MUTEXES must
	///< be defined.

	static void yield();
	///< Gives way to other threads waiting to be scheduled. This method is often used
	///< as a way to make a busy wait less evil. But in most cases, you will encounter,
	///< there are better ways to do that. So in general you shouldn't use this function.

	static void exit();
	///< Exits the current thread. If another thread is waiting for that thread using join()
	///< and the current thread is joinable, the waiting thread will be woken up.
	///<
	///< <B>Note:</B> Never call exit() from within a thread of a ThreadPool, as that
	///< will mess up the bookkeeping and lead to funny and unwanted results.

/// @}
};

/// @class Condition thread.hh xfc/glib/thread.hh
/// A GCond C++ wrapper interface.
///
/// The Condition object represents a condition that threads can block on, if they find
/// a certain condition to be false. If other threads change the state of this
/// condition they can signal the Condition, such that the waiting thread is woken up.
///
/// <B>Example:</B> Using G::Condition to block a thread until a condition is satisfied.
/// @code
/// G::Condition *data_cond = 0; // Must be initialized somewhere.
/// G::Mutex *data_mutex = 0; // Must be initialized somewhere.
/// void *current_data = 0;
///
/// void push_data(void *data)
/// {
/// 	data_mutex->lock();
/// 	current_data = data;
/// 	data_cond->signal();
/// 	data_mutex->unlock();
/// }
///
/// void* pop_data()
/// {
/// 	data_mutex->lock();
/// 	while (!current_data)
/// 		data_cond->wait(*data_mutex);
/// 	void *data = current_data;
/// 	current_data = 0;
/// 	data_mutex->unlock();
///     return data;
/// }
/// @endcode
///
/// Whenever a thread calls pop_data() now, it will wait until current_data is non-null, i.e.
/// until some other thread has called push_data().
///
/// Note, it is important to use the wait() method only inside a loop, which checks for the
/// condition to be <EM>true</EM> as it is not guaranteed that the waiting thread will find
/// it fulfilled, even if the signaling thread left the condition in that state. This is
/// because another thread can have altered the condition, before the waiting thread got the
/// chance to be woken up, even if the condition itself is protected by a Mutex, like above.

class Condition : public Xfc::Object

{
	Condition(const Condition&);
	Condition& operator=(const Condition&);

	GCond *cond_;

public:
/// @name Constructors
/// @{

	Condition();
	///< Creates a new condition. This constructor will abort, if G::Thread::init() has not been called yet.

	~Condition();
	///< Destructor. Frees the condition.

/// @}
/// @name Accessors
/// @{

	GCond* g_cond() const;
	///< Get a pointer to the GCond structure.

/// @}
/// @name Methods
/// @{

	void signal();
	///< If threads are waiting for the condition, exactly one of them is woken up.
	///< It is good practice to hold the same lock as the waiting thread, while
	///< calling this method, though not required. This method can also be used, if
	///< g_thread_init() has not yet been called, and will do nothing then.

	void broadcast();
	///< If threads are waiting for the condition, all of them are woken up. It is
	///< good practice to lock the same mutex as the waiting threads, while
	///< calling this method, though not required. This method can also be used
	///< if g_thread_init() has not yet been called, and will do nothing then.

	bool wait(Mutex& mutex, const TimeVal *abs_time = 0);
	///< Waits until a thread is woken up on condition.
	///< @param mutex A Mutex that is currently locked.
	///< @param abs_time A TimeVal determining the final time, or null for unlimited time.
	///< @return <EM>true</EM> if the thread is woken up in time, or if <EM>abs_time</EM> is null.
	///<
	///< The mutex is unlocked before falling asleep and locked again before resuming.
	///< If abs_time is null, timed_wait() acts like g_cond_wait(). If <EM>abs_time</EM>
	///< is specified, this method waits no longer than the time <EM>abs_time</EM> specifies.
	///< To easily calculate <EM>abs_time</EM> a combination of G::get_current_time() and
	///< G::TimeVal::add() can be used. This method can be used if g_thread_init() has not
	///< yet been called, and will immediately return true then.

/// @}
};

/// Macro that initializes a StaticPrivate.
/// A StaticPrivate must be initialized with this macro, before it can be used. This macro
/// can used be to initialize a variable, but it cannot be assigned to a variable. If you
/// want to allocate a run-time private key use G::Private instead.

#define XFC_STATIC_PRIVATE_INIT { G_STATIC_PRIVATE_INIT }

/// @class StaticPrivate thread.hh xfc/glib/thread.hh
/// A compile-time GStaticPrivate C++ wrapper interface.
///
/// A StaticPrivate works almost like a Private, but it has one significant advantage.
/// It doesn't need to be created at run-time like a Private, but can be defined at
/// compile-time. This is similar to the difference between G::Mutex and G::StaticMutex.
/// Now look at our give_me_next_number() example with StaticPrivate:
///
/// <B>Example:</B> Using StaticPrivate for per-thread data.
/// @code
/// int give_me_next_number ()
/// {
/// 	G::StaticPrivate current_number_key = XFC_STATIC_PRIVATE_INIT;
/// 	int *current_number = current_number_key.get();
///
/// 	if (!current_number)
/// 	{
/// 		current_number = new int;
/// 		*current_number = 0;
/// 		current_number_key->set(current_number);
/// 	}
/// 	*current_number = calc_next_number(*current_number);
/// 	return *current_number;
/// }
/// @endcode

template<typename T>
struct StaticPrivate
{
	GStaticPrivate private_key_;

	static void delete_data(void *data)
	{
		delete static_cast<T*>(data);
	}
	///< Default callback function called to delete the data pointer passed to set().
	///< @param data The data pointer passed to set().
	///<
	///< The data pointer must be allocated by operator new.


/// @name Accessors
/// @{

	GStaticPrivate* g_static_private() const
	{
		return const_cast<GStaticPrivate*>(&private_key_);
	}
	///< Get a pointer to the GStaticPrivate object.

	operator GStaticPrivate* () const
	{
		return this ? g_static_private() : 0;
	}
	///< Conversion operator; Safely converts a G::StaticPrivate object into a GStaticPrivate pointer.

/// @}
/// @name Methods
/// @{

	T* get() const
	{
		return static_cast<T*>(g_static_private_get(g_static_private()));
	}
	///< Gets the pointer keyed to the private key for the current thread.
	///< @return The corresponding data pointer.
	///<
	///< This pointer is null when set() hasn't been called for the current private key and
	///< thread yet. This method can also be used if G::Thread::init() has not yet been called,
	///< and will return the value of the private key cast to a 'T' pointer then.

	void set(T *data, GDestroyNotify notify = &delete_data)
	{
		g_static_private_set(private_key_, data, notify);
	}
	///< Sets the pointer keyed to the private key for the current thread, and the destroy
	///< notify function to be called with that pointer (null or non-null), whenever the
	///< pointer is set again or whenever the current thread ends.
	///< @param data The new data pointer.
	///< @param notify A function to be called with <EM>data</EM> whenever the current thread
	///< ends or sets the pointer again.
	///<
	///< The default destroy notify function <EM>delete_data</EM> simply calls operator
	///< delete on <EM>data</EM>, so <EM>data</EM> must have been allocated by operator new.
	///< This method also works if G::Thread::init() has not yet been called. If G::Thread::init()
	///< is called later, the data keyed to the private key will be inherited only by the
	///< main thread, that is, the one that called G::Thread::init().

/// @}
};

/// @class Private thread.hh xfc/glib/thread.hh
/// A run-time GStaticPrivate C++ wrapper interface.
///
/// The Private object represents a thread private data key. Threads can thereby obtain
/// and set a pointer, which is private to the current thread. Take our give_me_next_number()
/// example from previously. Now we don't want current_number to be shared between the threads,
/// but to be private to each thread. This can be done as follows:
///
/// <B>Example:</B> Using G::Private for per-thread data.
/// @code
/// G::Private<int> *current_number_key = 0; // Must be initialized somewhere.
///
/// int give_me_next_number()
/// {
/// 	int *current_number = current_number_key->get();
///
/// 	if (!current_number)
/// 	{
/// 		current_number = new int;
/// 		*current_number = 0;
/// 		current_number_key->set(current_number);
/// 	}
/// 	*current_number = calc_next_number(*current_number);
/// 	return *current_number;
/// }
/// @endcode
///
/// Here the pointer belonging to the key current_number_key is read. If it is null, it has not
/// been set yet. Then get memory for an integer value, assign this memory to the pointer and
/// write the pointer back. Now we have an integer value, that is private to the current thread.

template<typename T>
class Private : public StaticPrivate<T>
{
	Private(const Private<T>&);
	Private<T>& operator=(const Private<T>&);

public:
/// @name Constructors
/// @{

	Private()
	{
		g_static_private_init(this->g_static_private());
	}
	///< Constructs and initializes a new private key.

	~Private()
	{
		g_static_private_free(this->g_static_private());
	}
	///< Destructor. Frees the private key.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/thread.inl>

#endif // XFC_G_THREAD_HH
