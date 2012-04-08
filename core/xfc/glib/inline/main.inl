/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  main.inl - G::MainContext, G::MainLoop and G::Source inline functions
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

/*  G::PollFD
 */
	
inline GPollFD* 
Xfc::G::PollFD::g_poll_fd() const 
{ 
	return const_cast<GPollFD*>(&poll_fd_); 
}

inline Xfc::G::PollFD::operator GPollFD* () const
{
	return this ? g_poll_fd() : 0;
}

inline int 
Xfc::G::PollFD::fd() const
{
	return poll_fd_.fd;
}	
	
inline Xfc::G::IOConditionField 
Xfc::G::PollFD::events() const
{
	return poll_fd_.events;
}	
	
inline Xfc::G::IOConditionField 
Xfc::G::PollFD::revents() const
{
	return poll_fd_.events;
}	
	
inline void 
Xfc::G::PollFD::set_fd(int fd)
{
	poll_fd_.fd = fd;
}	

inline void 
Xfc::G::PollFD::set_events(IOConditionField events)
{
	poll_fd_.events = events;
}
	
/*  G::MainContext
 */

inline GMainContext*
Xfc::G::MainContext::g_main_context() const
{
	return context_;
}

inline Xfc::G::MainContext::operator GMainContext* () const
{
	return this ? context_ : 0;
}

inline bool
Xfc::G::MainContext::pending() const
{
	return g_main_context_pending(context_);
}

inline GPollFunc 
Xfc::G::MainContext::get_poll_func() const
{
	return g_main_context_get_poll_func(context_);
}

inline bool
Xfc::G::MainContext::iteration(bool may_block)
{
	return g_main_context_iteration(context_, may_block);
}

inline void 
Xfc::G::MainContext::wakeup()
{
	g_main_context_wakeup(context_);
}
	
inline bool 
Xfc::G::MainContext::acquire()
{
	return g_main_context_acquire(context_);
}

inline void 
Xfc::G::MainContext::release()
{
	g_main_context_release(context_);
}

inline bool 
Xfc::G::MainContext::prepare(int *priority)
{
	return g_main_context_prepare(context_, priority);
}

inline void 
Xfc::G::MainContext::dispatch()
{
	g_main_context_dispatch(context_);
}
	
inline void 
Xfc::G::MainContext::set_poll_func(GPollFunc func)
{
	g_main_context_set_poll_func(context_, func);	
}

/*  G::MainLoop
 */

inline GMainLoop*
Xfc::G::MainLoop::g_main_loop() const
{
	return loop_;
}

inline Xfc::G::MainLoop::operator GMainLoop* () const
{
	return this ? loop_ : 0;
}

inline bool
Xfc::G::MainLoop::is_running() const
{
	return g_main_loop_is_running(loop_);
}

inline int 
Xfc::G::MainLoop::depth()
{
	return g_main_depth();
	
}

inline void
Xfc::G::MainLoop::run()
{
	g_main_loop_run(loop_);
}

inline void
Xfc::G::MainLoop::quit()
{
	g_main_loop_quit(loop_);
}

/*  G::Source
 */

inline GSource*
Xfc::G::Source::g_source() const
{
	return source_;
}

inline Xfc::G::Source::operator GSource* () const
{
	return this ? source_ : 0;
}

inline int
Xfc::G::Source::get_priority() const
{
	return g_source_get_priority(source_);
}

inline bool
Xfc::G::Source::get_can_recurse() const
{
	return g_source_get_can_recurse(source_);
}

inline unsigned int
Xfc::G::Source::get_id() const
{
	return g_source_get_id(source_);
}

inline void
Xfc::G::Source::destroy()
{
	g_source_destroy (source_);
}

inline void
Xfc::G::Source::set_priority(int priority)
{
	g_source_set_priority(source_, priority);
}

inline void
Xfc::G::Source::set_can_recurse(bool can_recurse)
{
	g_source_set_can_recurse(source_, can_recurse);
}

