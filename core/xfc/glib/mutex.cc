/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  mutex.cc - A GMutex, GStaticMutex, GStaticRecMutex and GStaticRWLock C++ wrapper interface.
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

#include "mutex.hh"

using namespace Xfc;

/*  G::Mutex
 */

G::Mutex::Mutex(bool lock_mutex)
: mutex_(g_mutex_new()), locked_(lock_mutex)
{
	if (lock_mutex)
		lock();
}

G::Mutex::~Mutex()
{
	if (locked_)
		unlock();

	if (mutex_)
	{
		g_mutex_free(mutex_);
		mutex_ = 0;
	}
}

void
G::Mutex::lock()
{
	g_mutex_lock(mutex_);
	locked_ = true;
}

bool
G::Mutex::trylock()
{
	locked_ = g_mutex_trylock(mutex_);
	return locked_;
}

void
G::Mutex::unlock()
{
	g_mutex_unlock(mutex_);
	locked_ = false;
}

/*  G::StaticMutex
 */

void
G::StaticMutex::init()
{
	g_static_mutex_init(g_static_mutex());
}

G::StaticMutex::operator GStaticMutex* () const
{
	return this ? g_static_mutex() : 0;
}

void
G::StaticMutex::lock()
{
	g_static_mutex_lock(g_static_mutex());
}

bool
G::StaticMutex::trylock()
{
	return g_static_mutex_trylock(g_static_mutex());
}

void
G::StaticMutex::unlock()
{
	g_static_mutex_unlock(g_static_mutex());
}

/*  G::StaticRecMutex
 */

void
G::StaticRecMutex::init()
{
	g_static_rec_mutex_init(g_static_rec_mutex());
}

G::StaticRecMutex::operator GStaticRecMutex* () const
{
	return this ? g_static_rec_mutex() : 0;
}

void
G::StaticRecMutex::lock(unsigned int depth)
{
	g_static_rec_mutex_lock_full(g_static_rec_mutex(), depth);
}

bool
G::StaticRecMutex::trylock()
{
	return g_static_rec_mutex_trylock(g_static_rec_mutex());
}

void
G::StaticRecMutex::unlock()
{
	g_static_rec_mutex_unlock(g_static_rec_mutex());
}

unsigned int
G::StaticRecMutex::unlock_full()
{
	return g_static_rec_mutex_unlock_full(g_static_rec_mutex());
}

/*  G::RecMutex
 */

G::RecMutex::RecMutex(bool lock_mutex, unsigned int depth)
{
	init();
	if (lock_mutex)
		lock(depth);
}

G::RecMutex::~RecMutex()
{
	if (mutex_.depth >= 1)
		unlock_full();

	g_static_rec_mutex_free(g_static_rec_mutex());
}

/*  G::StaticRWLock
 */

void
G::StaticRWLock::init()
{
	g_static_rw_lock_init(g_static_rw_lock());
}

G::StaticRWLock::operator GStaticRWLock* () const
{
	return this ? g_static_rw_lock() : 0;
}

void
G::StaticRWLock::reader_lock()
{
	g_static_rw_lock_reader_lock(g_static_rw_lock());
}

bool
G::StaticRWLock::reader_trylock()
{
	return g_static_rw_lock_reader_trylock(g_static_rw_lock());
}

void
G::StaticRWLock::reader_unlock()
{
	g_static_rw_lock_reader_unlock(g_static_rw_lock());
}

void
G::StaticRWLock::writer_lock()
{
	g_static_rw_lock_writer_lock(g_static_rw_lock());
}

bool
G::StaticRWLock::writer_trylock()
{
	return g_static_rw_lock_writer_trylock(g_static_rw_lock());
}

void
G::StaticRWLock::writer_unlock()
{
	g_static_rw_lock_writer_unlock(g_static_rw_lock());
}

/*  G::RWLock
 */

G::RWLock::RWLock()
{
	init();
}

G::RWLock::~RWLock()
{
	g_static_rw_lock_free(g_static_rw_lock());
}

