/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  mutex.inl - G::Mutex, G::StaticMutex and G::StaticRWLock inline functions
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

/*  G::Mutex
 */

inline GMutex*
Xfc::G::Mutex::g_mutex() const
{
	return mutex_;
}

inline Xfc::G::Mutex::operator GMutex* () const
{
	return this ? mutex_ : 0;
}

inline bool
Xfc::G::Mutex::is_locked() const
{
	return locked_;
}

/*  G::StaticMutex
 */

inline GStaticMutex*
Xfc::G::StaticMutex::g_static_mutex() const
{
	return const_cast<GStaticMutex*>(&mutex_);
}

/*  G::StaticRecMutex
 */

inline GStaticRecMutex*
Xfc::G::StaticRecMutex::g_static_rec_mutex() const
{
	return const_cast<GStaticRecMutex*>(&mutex_);
}

inline bool
Xfc::G::StaticRecMutex::is_locked() const
{
	return mutex_.depth >= 1;
}

/*  G::StaticRWLock
 */

inline GStaticRWLock*
Xfc::G::StaticRWLock::g_static_rw_lock() const
{
	return const_cast<GStaticRWLock*>(&lock_);
}

