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

/// @file xfc/glib/asyncqueue.hh
/// @brief A GAsyncQueue C++ wrapper interface.
///
/// Provides AsyncQueue, a object that provides asynchronous communication between threads.

#ifndef XFC_G_ASYNCQUEUE_HH
#define XFC_G_ASYNCQUEUE_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_ASYNCQUEUE_H__
#include <glib/gasyncqueue.h>
#endif

namespace Xfc {

namespace G {

class TimeVal;

/// @class AsyncQueue asyncqueue.hh xfc/glib/asyncqueue.hh
/// A GAsyncQueue C++ wrapper interface.
///
/// Often you need to communicate between different threads. In general it's safer
/// not to do this by shared memory, but by explicit message passing. These messages
/// only make sense asynchronously for multi-threaded applications though, as a
/// synchronous operation could as well be done in the same thread.
///
/// Asynchronous queues are an exception from most other GLib data structures, as they
/// can be used simultaneously from multiple threads without explicit locking and they
/// bring their own builtin reference counting. This is because the nature of an
/// asynchronous queue is that it will always be used by at least 2 concurrent threads.
///
/// For using an asynchronous queue you first have to construct one, either dynamically
/// or on the stack. A newly-created queue will get the reference count 1. Whenever
/// another thread is creating a new reference to a queue, it has to increase the
/// reference count (using ref()). Also, before removing this reference, the reference
/// count has to be decreased (using unref()). After that the queue might no longer
/// exist so you must not access it after that point.
///
/// A thread which wants to send a message to a queue simply calls push() to push the
/// message to the queue. A thread which is expecting messages from an asynchronous
/// queue simply calls pop() for that queue. If no message is available in the queue
/// at that point, the thread is now put to sleep until a message arrives. The message
/// will be removed from the queue and returned. The methods try_pop() and timed_pop()
/// can be used to only check for the presence of messages or to only wait a certain
/// time for messages respectively.
///
/// In GLib, for almost every g_async_queue_* function there exist two variants, one that
/// locks the queue and one that doesn't. That way you can hold the queue lock (acquire
/// it with g_async_queue_lock() and release it with g_async_queue_unlock()) over
/// multiple queue accessing instructions. This can be necessary to ensure the integrity
/// of the queue, but should only be used when really necessary, as it can make your
/// life harder if used unwisely. Normally you should only use the locking function
/// variants (those without the suffix _unlocked).
///
/// AsyncQueue hides the these two function variants behind a single API. When you call
/// lock() the bool flag 'locked_' is set, and the API calls the *_unlocked functions.
/// When you call unlock() the 'locked_' flag is cleared, and the functions without the
/// suffix _unlocked are called. For saftey reasons, and ensure the AsyncQueue locked_
/// flag can't be broken, there is no g_async_queue() method or conversion operator.
///
/// Note, you must call unref() whether you create the queue dynamically or on the stack.
/// If you create an AsyncQueue dynamically with operatror new the easiest way to handle
/// unref() is to use a smart pointer. If you create an AsyncQueue on the stack you will
/// have to unref() it yourself, as you would with any object derived from ReferencedBase,
/// including G::Objects.

class AsyncQueue : public Xfc::Object
{
	AsyncQueue(const AsyncQueue&);
	AsyncQueue& operator=(const AsyncQueue&);

	GAsyncQueue *queue_;
	bool locked_;

public:
/// @name Constructors
/// @{

	AsyncQueue();
	///< Constructs a new asynchronous queue.

	~AsyncQueue();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GAsyncQueue* g_async_queue() const;
	///< Get a pointer to the GAsyncQueue structure.

	int length() const;
	///< Gets the length of the queue.
	///< @return The queue length.
	///<
	///< Negative values mean that threads are waiting, positive values mean
	///< that there are entries in the queue. Actually this method returns the
	///< length of the queue minus the number of waiting threads, length == 0
	///< could also mean 'n' entries in the queue and 'n' thread waiting. Such
	///< can happen due to locking of the queue or due to scheduling.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increases the reference count of the asynchronous queue by one.

	virtual void unref();
	///< Decreases the reference count of the asynchronous queue by one.
	///< After this call if the reference is zero and the queue will be destroyed.

	void lock();
	///< Acquires the queue's lock. All methods lock/unlock the queue for themselves,
	///< but in certain cirumstances you want to hold the lock longer, thus you lock
	///< the queue, and unlock when your finished.

	void unlock();
	///< Releases the queue's lock. All methods lock/unlock the queue for themselves,
	///< but in certain cirumstances you want to hold the lock longer, thus you lock
	///< the queue, and unlock when your finished.

	void push(void *data);
	///< Pushes the <EM>data</EM> into the queue (<EM>data</EM> must not be null).
	///< @param data The data to push into the queue.

	void* pop();
	///< Pop data from the async queue.
	///< @return The data from the queue.
	///<
	///< When no data is there, the thread is blocked until data arrives.

	void* try_pop();
	///< Try to pop data.
	///< @return The data from the queue, or null if the queue is empty.

	void* timed_pop(TimeVal *end_time);
	///< Pops data from the queue.
	///< @param end_time A G::TimeVal, determining the final time.
	///< @return The data from the queue, or null when no data is received before end_time.
	///<
	///< To easily calculate end_time a combination of G::get_current_time() and
	///< G::TimeVal::add() can be used.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/asyncqueue.inl>

#endif // XFC_G_ASYNCQUEUE_HH

