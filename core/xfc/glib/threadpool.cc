/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treadpool.cc - A GThreadPool C++ wrapper interface.
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

#include "threadpool.hh"
#include "mutex.hh"
#include "error.hh"
#include <algorithm>

namespace Xfc {

namespace G {

G::StaticMutex mutex = XFC_STATIC_MUTEX_INIT;

struct ThreadTask
{
	typedef ThreadPool::TaskSlot TaskSlot;
	TaskSlot slot_;

	ThreadTask(const TaskSlot& slot)
	: slot_(slot)
	{
	}

	static void callback(void *data, void *user_data)
	{
		typedef std::vector<ThreadTask*> TaskList;

		TaskList *list = static_cast<TaskList*>(user_data);
		ThreadTask *task = static_cast<ThreadTask*>(data);

		mutex.lock();
		TaskList::iterator i = std::find(list->begin(), list->end(), task);
		if (i != list->end())
		{
			list->erase(i);
		}
		mutex.unlock();

		task->slot_();
		delete task;
	}
};

} // namespace G

/*  G::ThreadPool
 */

G::ThreadPool::ThreadPool(int max_threads, bool exclusive, G::Error *error)
: pool_(g_thread_pool_new(&ThreadTask::callback, &task_list_, max_threads, exclusive, *error))
{
}

G::ThreadPool::~ThreadPool()
{
	if (pool_)
	{
		g_thread_pool_free(pool_, TRUE, TRUE);
		pool_ = 0;
	}
}

void
G::ThreadPool::push(const TaskSlot& slot, G::Error *error)
{
	ThreadTask *task = new ThreadTask(slot);
	mutex.lock();
	task_list_.push_back(task);
	mutex.unlock();
	g_thread_pool_push(pool_, task, *error);
}

void
G::ThreadPool::set_max_threads(int max_threads, G::Error *error)
{
	g_thread_pool_set_max_threads(pool_, max_threads, *error);
}

void
G::ThreadPool::free(bool immediate, bool wait)
{
	if (pool_)
	{
		g_thread_pool_free(pool_, immediate, wait);
		pool_ = 0;
	}
}

} // namespace Xfc

