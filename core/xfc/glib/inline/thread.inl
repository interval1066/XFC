/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  thread.inl - G::Thread and G::Condition inline functions
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

/*  G::Thread
 */

inline GThread*
Xfc::G::Thread::g_thread() const
{
	return (GThread*)this;
}

inline bool
Xfc::G::Thread::is_joinable() const
{
	return ((GThread*)this)->joinable;
}

inline Xfc::G::ThreadPriority
Xfc::G::Thread::get_priority() const
{
	return (ThreadPriority)((GThread*)this)->priority;
}

inline void
Xfc::G::Thread::init(GThreadFunctions *vtable)
{
	g_thread_init(vtable);
}

inline bool
Xfc::G::Thread::supported()
{
	return g_thread_supported();
}

inline Xfc::G::Thread*
Xfc::G::Thread::self()
{
	return reinterpret_cast<Thread*>(g_thread_self());
}

inline void
Xfc::G::Thread::join()
{
	g_thread_join((GThread*)this);
}

inline void
Xfc::G::Thread::set_priority(ThreadPriority priority)
{
	g_thread_set_priority((GThread*)this, (GThreadPriority)priority);
}

/*  G::Condition
 */

inline GCond*
Xfc::G::Condition::g_cond() const
{
	return cond_;
}

inline void
Xfc::G::Condition::signal()
{
	g_cond_signal(cond_);
}

inline void
Xfc::G::Condition::broadcast()
{
	g_cond_broadcast(cond_);
}

