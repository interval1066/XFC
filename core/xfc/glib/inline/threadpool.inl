/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  threadpool.inl - G::ThreadPool inline functions
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

inline GThreadPool*
Xfc::G::ThreadPool::g_thread_pool() const
{
	return pool_;
}

inline Xfc::G::ThreadPool::operator GThreadPool* () const
{
	return this ? pool_ : 0;
}

inline int
Xfc::G::ThreadPool::get_max_threads() const
{
	return g_thread_pool_get_max_threads(pool_);
}

inline unsigned int
Xfc::G::ThreadPool::get_num_threads() const
{
	return g_thread_pool_get_num_threads(pool_);
}

inline unsigned int
Xfc::G::ThreadPool::unprocessed() const
{
	return g_thread_pool_unprocessed(pool_);
}

inline unsigned int
Xfc::G::ThreadPool::get_num_unused_threads()
{
	return g_thread_pool_get_num_unused_threads();
}

inline int
Xfc::G::ThreadPool::get_max_unused_threads()
{
	return g_thread_pool_get_max_unused_threads();
}

inline void
Xfc::G::ThreadPool::set_max_unused_threads(int max_threads)
{
         g_thread_pool_set_max_unused_threads(max_threads);
}

inline void
Xfc::G::ThreadPool::stop_unused_threads()
{
	g_thread_pool_stop_unused_threads();
}

