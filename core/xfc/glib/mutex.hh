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

/// @file xfc/glib/mutex.hh
/// @brief A GMutex, GStaticMutex, GStaticRecMutex and GStaticRWLock C++ wrapper interface.
///
/// Provides Mutex, a mutual exclusion object that can be used to protect access to portions of memory.

#ifndef XFC_G_MUTEX_HH
#define XFC_G_MUTEX_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_THREAD_H__
#include <glib/gthread.h>
#endif

#define XFC_STATIC_RW_LOCK_INIT { G_STATIC_RW_LOCK_INIT }

namespace Xfc {

namespace G {

/// @class Mutex mutex.hh xfc/glib/mutex.hh
/// A GMutex C++ wrapper interface.
///
/// <B>Mutex</B> is an object that represents a mutex (mutual exclusion).
/// It can be used to protect data against shared access. Take for example
/// the following function:
///
/// <B>Example 1:</B>. A method which will not work in a threaded environment.
/// @code
/// int give_me_next_number()
/// {
/// 	static int current_number = 0;
///
/// 	// now do a very complicated calculation to calculate the new number,
/// 	// this might for example be a random number generator.
/// 	current_number = calc_next_number(current_number);
/// 	return current_number;
/// }
/// @endcode
///
/// It is easy to see, that this won't work in a multi-threaded application. There
/// <EM>current_number</EM> must be protected against shared access. A first naive
/// implementation would be:
///
/// <B>Example 2:</B> The wrong way to write a thread-safe method.
/// @code
/// int give_me_next_number ()
/// {
/// 	static int current_number = 0;
///
/// 	G::Mutex *mutex = 0;
/// 	if (!mutex)
/// 		mutex = new G::Mutex;
///
/// 	mutex->lock();
/// 	int result = current_number = calc_next_number(current_number);
/// 	mutex->unlock();
/// 	return result;
/// }
/// @endcode
///
/// This looks like it would work, but there is a race condition while constructing the mutex
/// and this code cannot work reliably. So please do not use such constructs in your own programs.
/// One working solution is:
///
/// <B>Example 3:</B> A correct thread-safe method.
/// @code
/// G::Mutex *give_me_next_number_mutex = 0;
///
/// // This method must be called exactly once before any call to give_me_next_number().
/// void init_give_me_next_number()
/// {
/// 	if (!give_me_next_number_mutex)
/// 		give_me_next_number_mutex = new G::Mutex;
/// }
///
/// int give_me_next_number()
/// {
/// 	static int current_number = 0;
/// 	give_me_next_number_mutex->lock();
/// 	int result = current_number = calc_next_number(current_number);
/// 	give_me_next_number_mutex->unlock();
/// 	return result;
/// }
/// @endcode

class Mutex : public Xfc::Object
{
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);

	GMutex *mutex_;
	bool locked_;

public:
/// @name Constructors
/// @{

	Mutex(bool lock_mutex = false);
	///< Construct a new mutex.
	///< @param lock_mutex Whether to lock the mutex at construction time.
	///<
	///< If the mutex is locked at construction time it will automatically
	///< be unlocked when it goes out of scope.
	///< <B>Note</B> this constructor will abort, if G::Thread::init() has not been called yet.

	~Mutex();
	///< Destructor; Unlocks the mutex if it is locked, and frees it.

/// @}
/// @name Accessors
/// @{

	GMutex* g_mutex() const;
	///< Get a pointer to the GMutex object.

	operator GMutex* () const;
	///< Conversion operator; Safely converts a G::Mutex object into a GMutex pointer.

	bool is_locked() const;
	///< Determines whether the mutex is locked.
	///< @return <EM>true</EM> if the mutex is locked.

/// @}
/// @name Methods
/// @{

	void lock();
	///< Locks the mutex. If mutex is already locked by another thread, the current thread
	///< will block until the mutex is unlocked by the other thread. This method can also be
	///< used if G::Thread::init() has not yet been called, in which case it will do nothing.
	///<
	///< <B>Note</B> Mutex is neither guaranteed to be recursive nor to be non-recursive,
	///< that is, a thread could deadlock while calling lock(), if it already has locked the
	///< mutex. Use G::StaticRecMutex, if you need a recursive mutex.

	bool trylock();
	///< Tries to lock the mutex.
	///< @return <EM>true</EM> if mutex could be locked.
	///<
	///< If the mutex is already locked by another thread, it immediately
	///< returns false. Otherwise it locks mutex and returns true. This method
	///< can also be used if G::Thread::init() has not yet been called, in
	///< which case it will immediately return true.
	///<
	///< <B>Note</B> Mutex is neither guaranteed to be recursive nor to be non-recursive,
	///< that is, the return value of trylock() could be both false or true, if the current
	///< thread already has locked the mutex. Use G::StaticRecMutex, if you need a recursive
	///< mutex.

	void unlock();
	///< Unlocks the mutex. If another thread is blocked in a lock() call for the mutex,
	///< it will be woken and can lock the mutex itself. This method can also be used if
	///< G::Thread::init() has not yet been called, in which case it will do nothing.
};

/// Macro that initializes a StaticMutex.
/// A StaticMutex must be initialized with this macro, before it can be used. This macro
/// can used be to initialize a variable, but it cannot be assigned to a variable. If you
/// want to allocate a run-time mutex use G::Mutex instead.

#define XFC_STATIC_MUTEX_INIT { G_STATIC_MUTEX_INIT }

/// @class StaticMutex mutex.hh xfc/glib/mutex.hh
/// A GStaticMutex C++ wrapper interface.
///
/// A StaticMutex works like a Mutex, but it has one significant advantage. It doesn't
/// need to be created at run-time like a Mutex, but can be defined at compile-time.
///
/// Here is a shorter, easier and safer version of the G::Mutex give_me_next_number()
/// example:
///
/// <B>Example:</B> Using StaticMutex to simplify thread-safe programming.
/// @code
/// int give_me_next_number()
/// {
/// 	static int current_number = 0;
/// 	G::StaticMutex mutex = XFC_STATIC_MUTEX_INIT;
/// 	mutex.lock();
/// 	int result = current_number = calc_next_number(current_number);
/// 	mutex.unlock();
/// 	return result;
/// }
/// @endcode
///
/// Sometimes you would like to dynamically create a mutex. If you don't want to
/// require prior calling to G::Thread::init(), because your code should also be
/// usable in non-threaded programs, you are not able to use a G::Mutex, as that
/// requires a prior call to G::Thread::init(). In theses cases you can also use
/// a StaticMutex.
///
/// A StaticMutex can be statically initialized with the value XFC_STATIC_MUTEX_INIT,
/// and then it can directly be used, which is much easier, than having to explicitly
/// allocate the mutex before use.

struct StaticMutex
{
	GStaticMutex mutex_;

/// @name Constructors
/// @{

	void init();
	///< Initializes a static mutex. Alternatively you can initialize it with G::XFC_STATIC_MUTEX_INIT.

/// @}
/// @name Accessors
/// @{

	GStaticMutex* g_static_mutex() const;
	///< Get a pointer to the GStaticMutex object.

	operator GStaticMutex* () const;
	///< Conversion operator; Safely converts a G::StaticMutex object into a GStaticMutex pointer.

/// @}
/// @name Methods
/// @{

	void lock();
	///< Locks the mutex. If mutex is already locked by another thread, the current thread
	///< will block until the mutex is unlocked by the other thread. This method can also be
	///< used if G::Thread::init() has not yet been called, in which case it will do nothing.
	///<
	///< <B>Note</B> Mutex is neither guaranteed to be recursive nor to be non-recursive,
	///< that is, a thread could deadlock while calling lock(), if it already has locked the
	///< mutex. Use G::StaticRecMutex, if you need a recursive mutex.

	bool trylock();
	///< Tries to lock the mutex.
	///< @return <EM>true</EM> if mutex could be locked.
	///<
	///< If the mutex is already locked by another thread, it immediately
	///< returns false. Otherwise it locks mutex and returns true. This method
	///< can also be used if G::Thread::init() has not yet been called, in
	///< which case it will immediately return true.
	///<
	///< <B>Note</B> Mutex is neither guaranteed to be recursive nor to be non-recursive,
	///< that is, the return value of trylock() could be both false or true, if the current
	///< thread already has locked the mutex. Use G::StaticRecMutex, if you need a recursive
	///< mutex.

	void unlock();
	///< Unlocks the mutex. If another thread is blocked in a lock() call for the mutex,
	///< it will be woken and can lock the mutex itself. This method can also be used if
	///< G::Thread::init() has not yet been called, in which case it will do nothing.
/// @}
};

/// Macro that initializes a StaticRecMutex.
/// A StaticRecMutex must be initialized with this macro, before it can be used. This macro
/// can used be to initialize a variable, but it cannot be assigned to a variable. If you
/// want to allocate a run-time mutex use G::RecMutex instead.

#define XFC_STATIC_REC_MUTEX_INIT { G_STATIC_REC_MUTEX_INIT }

/// @class StaticRecMutex mutex.hh xfc/glib/mutex.hh
/// A compile-time GStaticRecMutex C++ wrapper interface.
///
/// A StaticRecMutex works like a StaticMutex, but it can be locked multiple times
/// by one thread If you enter it n times, however, you have to unlock it n times
/// again to let other threads lock it. An exception is the function unlock_full(),
/// that allows you to unlock a StaticRecMutex completely returning the depth, i.e.
/// the number of times this mutex was locked. The depth can later be used to restore
/// the state by calling lock().
///
/// A StaticRecMutex can be statically initialized with the value XFC_STATIC_REC_MUTEX_INIT.
/// All of the StaticRecMutex methods can be used if G::Thread::init() has not been called.

struct StaticRecMutex
{
	GStaticRecMutex mutex_;

/// @name Constructors
/// @{

	void init();
	///< Initializes a StaticRecMutex. Alternatively you can initialize it with G::XFC_STATIC_REC_MUTEX_INIT.

/// @}
/// @name Accessors
/// @{

	GStaticRecMutex* g_static_rec_mutex() const;
	///< Get a pointer to the GStaticRecMutex object.

	operator GStaticRecMutex* () const;
	///< Conversion operator; Safely converts a G::StaticRecMutex object into a GStaticRecMutex pointer.

	bool is_locked() const;
	///< Returns true it the mutex is locked, that is, if its locked depth one or more.

/// @}
/// @name Methods
/// @{

	void lock(unsigned int depth = 1);
	///< Locks the mutex.
	///< @param depth The number of times the mutex has to be unlocked to be completely unlocked.
	///<
	///< If the mutex is already locked by another thread, the current thread
	///< will block until mutex is unlocked by the other thread. If mutex is already
	///< locked by the calling thread, this functions increases the depth of mutex
	///< <EM>depth</EM> times and returns. The default depth is one.

	bool trylock();
	///< Tries to lock the mutex.
	///< @return <EM>true</EM> if the mutex could be locked.
	///<
	///< If mutex is already locked by another thread, it immediately returns
	///< false. Otherwise it locks mutex and returns true. If mutex is already
	///< locked by the calling thread, this functions increases the depth of mutex
	///< by one and immediately returns true.

	void unlock();
	///< Unlocks the mutex one level. Other threads can only lock the mutex when it
	///< has been unlocked as many times, as it had been locked before. If mutex is
	///< completely unlocked and another thread is blocked in a lock() call for mutex,
	///< it will be woken and can lock mutex itself.

	unsigned int unlock_full();
	///< Unlocks the mutex completely. Other threads can only lock mutex when it has
	///< been unlocked as many times, as it had been locked before. If mutex is
	///< completely unlocked and another thread is blocked in a lock() call for mutex,
	///< it will be woken and can lock mutex itself.
/// @}
};

/// @class RecMutex mutex.hh xfc/glib/mutex.hh
/// A run-time GStaticRecMutex C++ wrapper interface.
///
/// A RecMutex works like a StaticRecMutex, but it can be constructed and initialized at run-time.
/// The RecMutex constructor calls StaticRecMutex::init() to initialize itself.

class RecMutex : public StaticRecMutex
{
	RecMutex(const RecMutex&);
	RecMutex& operator=(const RecMutex&);

public:
/// @name Constructors
/// @{

	RecMutex(bool lock_mutex = false, unsigned int depth = 1);
	///< Constructs and initializes a new StaticRecMutex.
	///< @param lock_mutex Whether to lock the mutex at construction time.
	///< @param depth The number of times the mutex has to be unlocked to be completely unlocked.

	~RecMutex();
	///< Destructor; Completely unlocks the mutex if it's locked, and frees it.

/// @}
};

/// Macro that initializes a StaticRWLock.
/// A StaticRWLock must be initialized with this macro, before it can be used. This macro
/// can used be to initialize a variable, but it cannot be assigned to a variable. If you
/// want to allocate a run-time mutex use G::RWLock instead.

#define XFC_STATIC_RW_LOCK_INIT { G_STATIC_RW_LOCK_INIT }

/// @class StaticRWLock mutex.hh xfc/glib/mutex.hh
/// A compile-time GStaticRWlock C++ wrapper interface.
///
/// StaticRWLock represents a read-write lock. A read-write lock can be used for
/// protecting data, that some portions of code only read from, while others also
/// write. In such situations it is desirable, that several readers can read at
/// once, whereas of course only one writer may write at a time. Take a look at
/// the following example:
///
/// <B>Example:</B> An array with access functions.
/// @code
/// G::StaticRWLock rwlock = XFC_STATIC_RW_LOCK_INIT;
/// GPtrArray *array;
///
/// void* my_array_get(unsigned int index)
/// {
/// 	void *retval = 0;
///
///     if (!array)
/// 		return 0;
///
///     rw_lock.reader_lock();
///
///     if (index < array->len)
/// 		retval = g_ptr_array_index(array, index);
///
/// 	rwlock.reader_unlock();
///
///     return retval;
/// }
///
/// void my_array_set(unsigned int index, void *data)
/// {
/// 	rwlock.writer_lock();
///
/// 	if (!array)
/// 		array = g_ptr_array_new();
///
/// 	if (index >= array->len)
/// 		g_ptr_array_set_size(array, index+1);
///
/// 	g_ptr_array_index(array, index) = data;
///
/// 	rwlock.writer_unlock();
/// }
/// @endcode
///
/// This example shows an array, which can be accessed by many readers (the my_array_get()
/// function) simultaneously, whereas the writers (the my_array_set() function) will only
/// be allowed once a time and only if no readers currently access the array. This is
/// because of the potentially dangerous resizing of the array. Using these functions is
/// fully multi-thread safe now.
///
/// Most of the time the writers should have precedence over readers. That means for this
/// implementation, that as soon as a writer wants to lock the data, no other reader is
/// allowed to lock the data, whereas of course the readers, that already have locked
/// the data are allowed to finish their operation. As soon as the last reader unlocks
/// the data, the writer will lock it.
///
/// A read-write lock has a higher overhead than a mutex. For example both reader_lock() and
/// reader_unlock() have to lock and unlock a StaticMutex, so it takes at least twice the
/// time to lock and unlock a StaticRWLock than to lock and unlock a StaticMutex. So only
/// data structures, that are accessed by multiple readers, which keep the lock for a
/// considerable time justify a StaticRWLock. The above example most probably would fare
/// better with a StaticMutex.

struct StaticRWLock
{
	GStaticRWLock lock_;

/// @name Constructors
/// @{

	void init();
	///< Initializes a StaticRWLock. Alternatively you can initialize it with G::XFC_STATIC_RW_LOCK_INIT.

/// @}
/// @name Accessors
/// @{

	GStaticRWLock* g_static_rw_lock() const;
	///< Get a pointer to the GStaticRWLock object.

	operator GStaticRWLock* () const;
	///< Conversion operator; Safely converts a G::StaticRWLock object into a GStaticRWLock pointer.

/// @}
/// @name Methods
/// @{

	void reader_lock();
	///< Locks a lock for reading. There may be unlimited concurrent locks for reading
	///< of a StaticRWLock at the same time. If lock is already locked for writing by
	///< another thread or if another thread is already waiting to lock lock for writing,
	///< this function will block until lock is unlocked by the other writing thread and
	///< no other writing threads want to lock lock. This lock has to be unlocked by
	///< reader_unlock().
	///<
	///< StaticRWLock is not recursive. It might seem to be possible to recursively lock
	///< for reading, but that can result in a deadlock as well, due to writer preference.

	bool reader_trylock();
	///< Tries to lock the lock for reading.
	///< @return <EM>true</EM> if lock could be locked for reading.
	///<
	///< If lock is already locked for writing by another thread or if another
	///< thread is already waiting to lock lock for writing, it immediately returns
	///< false. Otherwise it locks lock for reading and returns true. This lock has
	///< to be unlocked by reader_unlock().

	void reader_unlock();
	///< Unlocks the lock. If a thread waits to lock the lock for writing and all
	///< locks for reading have been unlocked, the waiting thread is woken up and
	///< can lock lock for writing.

	void writer_lock();
	///< Locks the lock for writing. If lock is already locked for writing or reading
	///< by other threads, this method will block until lock is completely unlocked
	///< and then lock the lock for writing. While this method waits to lock the lock,
	///< no other thread can lock the lock for reading. When lock is locked for writing,
	///< no other thread can lock the lock (neither for reading nor writing). This lock
	///< has to be unlocked by writer_unlock().

	bool writer_trylock();
	///< Tries to lock the lock for writing.
	///< @return <EM>true</EM> if lock could be locked for writing.
	///<
	///< If lock is already locked (for either reading or writing) by another thread,
	///< it immediately returns false. Otherwise it locks the lock for writing and returns
	///< true. This lock has to be unlocked by writer_unlock().

	void writer_unlock();
	///< Unlocks the lock. If a thread waits to lock the lock for writing and all locks
	///< for reading have been unlocked, the waiting thread is woken up and can lock the
	///< lock for writing. If no thread waits to lock the lock for writing and threads
	///< wait to lock the lock for reading, the waiting threads are woken up and can
	///< lock the lock for reading.
/// @}
};

/// @class RWLock mutex.hh xfc/glib/mutex.hh
/// A run-time GStaticRWlock C++ wrapper interface.
///
/// RWLock works like a StaticRWLock, but it can be constructed and initialized at run-time.
/// The RWLock constructor calls StaticRWLock::init() to initialize itself.

class RWLock : public StaticRWLock
{
	RWLock(const RWLock&);
	RWLock& operator=(const RWLock&);

public:
/// @name Constructors
/// @{

	RWLock();
	///< Constructs and initializes a new RWLock.

	~RWLock();
	///< Destructor; Frees the lock.
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/mutex.inl>

#endif // XFC_G_MUTEX_HH

