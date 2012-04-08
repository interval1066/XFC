/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  thread.cc - A GThread C++ wrapper interface.
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

#include "thread.hh"
#include "error.hh"
#include "timeval.hh"

using namespace Xfc;

/*  G::Thread
 */

namespace { // ThreadCallback

struct ThreadCallback
{
	typedef G::Thread::ThreadSlot ThreadSlot;
	ThreadSlot slot_;

	ThreadCallback(const ThreadSlot& slot)
	: slot_(slot)
	{
	}

	static void* notify(void *data)
	{
		ThreadCallback *cb = static_cast<ThreadCallback*>(data);
		cb->slot_();
		delete cb;
		return 0;
	}
};

} // namespace

G::Thread*
G::Thread::create(const ThreadSlot& slot, bool joinable, G::Error *error)
{
	ThreadCallback *cb = new ThreadCallback(slot);
	return reinterpret_cast<Thread*>(g_thread_create(&ThreadCallback::notify, cb, joinable, *error));
}

G::Thread*
G::Thread::create(const ThreadSlot& slot, unsigned long stack_size, bool joinable, bool bound, G::Error *error)
{
	ThreadCallback *cb = new ThreadCallback(slot);
	return reinterpret_cast<Thread*>(g_thread_create_full(&ThreadCallback::notify, cb, stack_size,
	                                 joinable, bound, G_THREAD_PRIORITY_NORMAL, *error));
}

void
G::Thread::yield()
{
	if (supported())
		g_thread_yield();
}

void
G::Thread::exit()
{
	if (supported())
		g_thread_exit(0);
}

/*  G::Condition
 */

G::Condition::Condition()
: cond_(g_cond_new())
{
}

G::Condition::~Condition()
{
	if (cond_)
	{
		g_cond_free(cond_);
		cond_ = 0;
	}
}

bool
G::Condition::wait(Mutex& mutex, const TimeVal *abs_time)
{
	return g_cond_timed_wait(cond_, mutex.g_mutex(), *abs_time);
}

