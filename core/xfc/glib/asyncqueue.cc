/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  asyncqueue.cc - A GAsyncQueue C++ wrapper interface.
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

#include "asyncqueue.hh"
#include "timeval.hh"

using namespace Xfc;

/*  G::AsyncQueue
 */

G::AsyncQueue::AsyncQueue()
: queue_(g_async_queue_new()), locked_(false)
{
}

G::AsyncQueue::~AsyncQueue()
{
	if (queue_)
	{
		unref();
	}
}

int
G::AsyncQueue::length() const
{
	return locked_ ? g_async_queue_length_unlocked(queue_) : g_async_queue_length(queue_);
}

void
G::AsyncQueue::ref()
{
	g_async_queue_ref(queue_);
	Xfc::Object::ref();
}

void
G::AsyncQueue::unref()
{
	g_async_queue_unref(queue_);
	queue_ = 0;
	Xfc::Object::unref();
}

void
G::AsyncQueue::lock()
{
	g_async_queue_lock(queue_);
	locked_ = true;
}

void
G::AsyncQueue::unlock()
{
	g_async_queue_unlock(queue_);
	locked_ = false;
}

void
G::AsyncQueue::push(void *data)
{
	if (locked_)
		g_async_queue_push_unlocked(queue_, data);
	else
		g_async_queue_push(queue_, data);
}

void*
G::AsyncQueue::pop()
{
	return  locked_ ? g_async_queue_pop_unlocked(queue_) : g_async_queue_pop(queue_);
}

void*
G::AsyncQueue::try_pop()
{
	return locked_ ? g_async_queue_try_pop_unlocked(queue_) : g_async_queue_try_pop(queue_);
}

void*
G::AsyncQueue::timed_pop(TimeVal *end_time)
{
	return locked_ ? g_async_queue_timed_pop_unlocked(queue_, *end_time) : g_async_queue_timed_pop(queue_, *end_time);
}

