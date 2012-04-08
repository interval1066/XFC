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

/// @file xfc/glib/threadpool.hh
/// @brief A GThreadPool C++ wrapper interface.
///
/// Provides ThreadPool, a object that manages pools of threads to execute work concurrently.

#ifndef XFC_G_THREADPOOL_HH
#define XFC_G_THREADPOOL_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_THREADPOOL_H__
#include <glib/gthreadpool.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Error;
class ThreadTask;

/// @class ThreadPool threadpool.hh xfc/glib/threadpool.hh
/// A GThreadPool C++ wrapper interface.
///
/// Sometimes you wish to asynchronously fork out the execution of work and continue working
/// in your own thread. If that will happen often, the overhead of starting and destroying
/// a thread each time might be to high. In such cases reusing already started threads seems
/// like a good idea. And it indeed is, but implementing this can be tedious and error-prone.
///
/// ThreadPools are provided for your convenience. An added advantage is, that the threads
/// can be shared between the different subsystems of your program, when they are using GLib.
///
/// There is only one constructor to create a thread pool and the pool is freed automatically
/// when it goes out of scope. A free() method is provided for use either when you want to free
/// the thread pool before it goes out of scope, or change the default values for <EM>immediate</EM>
/// and <EM>wait</EM> that get passed to g_thread_pool_free().
///
/// If you want to execute a certain task within a thread pool, you call push(). To get the
/// current number of running threads you call get_num_threads(). To get the number of still
/// unprocessed tasks you call unprocessed(). To control the maximal number of threads for a
/// thread pool, you use get_max_threads() and set_max_threads().
///
/// Finally you can control the number of unused threads, that are kept alive by GLib for
/// future use. The current number can be fetched with get_num_unused_threads(). The maximal
/// number can be controlled by get_max_unused_threads() and set_max_unused_threads(). All
/// currently unused threads can be stopped by calling stop_unused_threads().

class ThreadPool : public Xfc::Object
{
	ThreadPool(const ThreadPool&);
	ThreadPool& operator=(const ThreadPool&);

	typedef std::vector<ThreadTask*> TaskList;
	TaskList task_list_;

	GThreadPool *pool_;

public:
	typedef sigc::slot<void> TaskSlot;
	///< Signature of the callback slot to be executed in the threads of the thread pool.
	///<
	///< <B>Example:</B> Method signature for a TaskSlot.
	///< @code
	///< void method();
	///< @endcode

/// @name Constructors
/// @{

	ThreadPool(int max_threads = -1, bool exclusive = false, G::Error *error = 0);
	///< Construct a new thread pool.
	///< @param max_threads The maximal number of threads to execute concurrently
	///<                    in the new thread pool, -1 means no limit.
	///< @param exclusive Should this thread pool be exclusive.
	///< @param error The return location for a G::Error.
	///<
	///< Whenever you call push(), either a new thread is created or an unused one
	///< is reused. At most <EM>max_threads</EM> threads are running concurrently for
	///< this thread pool. <EM>max_threads</EM> = -1 allows unlimited threads to be
	///< created for this thread pool.
	///<
	///< The parameter <EM>exclusive</EM> determines, whether the thread pool owns all
	///< threads exclusively or whether the threads are shared globally. If <EM>exclusive</EM>
	///< is true, <EM>max_threads</EM> threads are started immediately and they will run
	///< exclusively for this thread pool until it is destroyed. If <EM>exclusive</EM> is
	///< false, threads are created, when needed and shared between all non-exclusive
	///< thread pools. This implies that max_threads may not be -1 for exclusive thread pools.
	///<
	///< The error can be null to ignore errors, or non-null to report errors. An error can
	///< only occur when <EM>exclusive</EM> is set to true and not all <EM>max_threads</EM>
	///< threads could be created.

	~ThreadPool();
	///< Destructor. Frees the thread pool but not before the last task
	///< currently being processed is finished running. No new tasks are
	///< processed.

/// @}
/// @name Accessors
/// @{

	GThreadPool* g_thread_pool() const;
	///< Get a pointer to the GThreadPool object.

	operator GThreadPool* () const;
	///< Conversion operator; Safely converts a G::ThreadPool object into a GThreadPool pointer.

	int get_max_threads() const;
	///< Gets the maximal number of threads for the pool.
	///< @return the maximal number of threads.

	unsigned int get_num_threads() const;
	///< Gets the number of threads currently running in the pool.
	///< @return The number of threads currently running.

	unsigned int unprocessed() const;
	///< Gets the number of tasks still unprocessed in the pool.
	///< @return The number of unprocessed tasks.

/// @}
/// @name Accessors
/// @{

	static unsigned int get_num_unused_threads();
	///< Gets the number of currently unused threads.
	///< @return The number of currently unused threads.

	static int get_max_unused_threads();
	///< Gets the maximal allowed number of unused threads.
	///< @returns The maximal number of unused threads.

/// @}
/// @name Methods
/// @{

	void push(const TaskSlot& slot, G::Error *error = 0);
	///< Inserts <EM>data</EM> into the list of tasks to be executed by the pool.
	///< @param slot A new task to execute in the thread pool.
	///< @param error The return location for a G::Error.
	///<
	///< When the number of currently running threads is lower than the maximal
	///< allowed number of threads, a new thread is started (or reused) with the
	///< properties given to the constructor. Otherwise <EM>task</EM> stays in the
	///< queue until a thread in this pool finishes its previous task and executes
	///< <EM>task</EM>. Do not unref() the task slot when your finished. The pool
	///< will do this automatically when it gets destroyed.
	///<
	///< The <EM>error</EM> can be null to ignore errors, or non-null to report errors.
	///< An error can only occur when a new thread couldn't be created. In that case
	///< <EM>task</EM> is simply appended to the queue of work to do.

	void set_max_threads(int max_threads, G::Error *error = 0);
	///< Sets the maximal allowed number of threads for pool.
	///< @param max_threads The new maximal number of threads for the pool.
	///< @param error The return location for a G::Error.
	///<
	///< A value of -1 means, that the maximal number of threads is unlimited.
	///< Setting max_threads to 0 means stopping all work for pool. It is effectively
	///< frozen until max_threads is set to a non-zero value again. A thread is never
	///< terminated while calling a TaskSlot. Instead the maximal number of threads
	///< only has effect for the allocation of new threads in push(). A new thread
	///< is allocated, whenever the number of currently running threads in pool is
	///< smaller than the maximal number.
	///<
	///< The <EM>error</EM> can be null to ignore errors, or non-null to report errors.
	///< An error can only occur when a new thread couldn't be created. In that case
	///< <EM>data</EM> is simply appended to the queue of work to do.

	void free(bool immediate = false, bool wait = true);
	///< Frees all resources allocated for the pool.
	///< @param immediate Should pool shut down immediately (default is false)?
	///< @param wait Should the pool wait for all tasks to finish (default is true)?
	///<
	///< If <EM>immediate</EM> is true, no new task is processed for the pool. Otherwise
	///<  the pool is not freed before the last task is processed. Note however, that no
	///< thread of the pool is interrupted, while processing a task. Instead at least all
	///< still running threads can finish their tasks before the pool is freed.
	///<
	///< If <EM>wait</EM> is true, the thread pool does not return before all tasks to be
	///< processed (dependent on immediate, whether all or only the currently running)
	///< are ready. Otherwise the thread pool returns immediately.
	///<
	///< Usually you wont need to call this method because the pool is automatically freed
	///< by the destructor when the pool object goes out of scope. The default values the
	///< destructor uses to free the pool are 'immediate == false' and 'wait == true'. The
	///< only reasons to call free() is either when you want to use different values for
	///< immediate and wait, or when you want to free a pool before the pool object goes
	///< out of scope. free() is a wrapper around the C function call g_thread_pool_free()
	///< and doesn't unref() the pool object. If you created the pool dynamically you still
	///< must call unref(). However, as with all ReferencedObjects, if you created the
	///< pool on the stack you don't need to call unref(). Note after calling this method
	///< the pool must not be used anymore.

/// @}
/// @name Methods
/// @{

	static void set_max_unused_threads(int max_threads);
	///< Sets the maximal number of unused threads to max_threads.
	///< @param max_threads The maximal number of unused threads.
	///<
	///< If max_threads is -1, no limit is imposed on the number of unused threads.

	static void stop_unused_threads();
	///< Stops all currently unused threads. This does not change the maximal number
	///< of unused threads. This method can be used to regularly stop all unused
	///< threads.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/threadpool.inl>

#endif // XFC_G_THREADPOOL_HH

