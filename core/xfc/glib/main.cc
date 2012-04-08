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

#include "main.hh"
#include "thread.hh"
#include <glib/gmessages.h>

using namespace Xfc;

/*  G::get_current_time
 */

void
G::get_current_time(TimeVal& timeval)
{
	g_get_current_time(timeval);
}

/*  G::PollFD
 */

G::PollFD::PollFD()
{
	poll_fd_.fd = 0;
	poll_fd_.events = 0;
	poll_fd_.revents = 0;
}
	
G::PollFD::PollFD(int fd)
{
	poll_fd_.fd = fd;
	poll_fd_.events = 0;
	poll_fd_.revents = 0;
}
	
G::PollFD::PollFD(int fd, IOConditionField events)
{
	poll_fd_.fd = fd;
	poll_fd_.events = events;
	poll_fd_.revents = 0;
}

void 
G::PollFD::set(int fd, IOConditionField events)
{
	set_fd(fd);
	set_events(events);
}

/*  G::MainContext
 */

G::MainContext::MainContext()
: context_(g_main_context_new()), ref_count(1)
{
	set_owns_reference(true);
}

G::MainContext::MainContext(GMainContext *context, bool owns_reference)
: context_(context)
{
	set_owns_reference(owns_reference);
}

G::MainContext::~MainContext()
{
	if (context_)
	{
		g_main_context_unref(context_);
		context_ = 0;
	}
}

Pointer<G::MainContext>
G::MainContext::get_default()
{
	GMainContext *context = g_main_context_default();
	return context ? new G::MainContext(context) : 0;
}

void
G::MainContext::ref()
{
	g_main_context_ref(context_);
	++ref_count;
}

void
G::MainContext::unref()
{
	g_main_context_unref(context_);
	if (--ref_count == 0)
	{
		context_ = 0;
		if (is_dynamic())
			delete this;
	}
}

Pointer<G::Source> 
G::MainContext::find_source(unsigned int source_id)
{
	return new Source(g_main_context_find_source_by_id(g_main_context(), source_id), false);
}	

bool 
G::MainContext::wait(Condition& condition, Mutex& mutex)
{
	return g_main_context_wait(context_, condition.g_cond(), mutex.g_mutex());
}	

bool 
G::MainContext::query(int max_priority, int *timeout, std::vector<PollFD>& fds)
{
	g_return_val_if_fail(fds.empty(), false);
	
	int n_fds = 0; 
	GPollFD *tmp_fds = reinterpret_cast<GPollFD*>(&fds[0]);
	
	while ((n_fds = g_main_context_query(context_, max_priority, timeout, tmp_fds, fds.size())) > int(fds.size()))
	{
		fds.resize(n_fds);
	}
	return !fds.empty();
}

int 
G::MainContext::check(int max_priority, std::vector<PollFD>& fds)
{
	return g_main_context_check(context_, max_priority, reinterpret_cast<GPollFD*>(&fds[0]), fds.size());
}

void 
G::MainContext::add_poll(PollFD& fd, int priority)
{
	g_main_context_add_poll(context_, fd.g_poll_fd(), priority);
}
	
void 
G::MainContext::remove_poll(PollFD& fd)
{
	g_main_context_remove_poll(context_, fd.g_poll_fd());
}

/*  G::MainLoop
 */

G::MainLoop::MainLoop()
: loop_(g_main_loop_new(0, false)), ref_count(1)
{
	set_owns_reference(true);
}

G::MainLoop::MainLoop(MainContext& context)
: loop_(g_main_loop_new(context.g_main_context(), false)), ref_count(1)
{
	set_owns_reference(true);
}

G::MainLoop::~MainLoop()
{
	if (loop_)
	{
		g_main_loop_unref(loop_);
		loop_ = 0;
	}
}

void
G::MainLoop::ref()
{
	g_main_loop_ref(loop_);
	++ref_count;
}

void
G::MainLoop::unref()
{
	g_main_loop_unref(loop_);
	if (--ref_count == 0)
	{
		loop_ = 0;
		if (is_dynamic())
			delete this;
	}
}

Pointer<G::MainContext>
G::MainLoop::get_context() const
{
	GMainContext *context = g_main_loop_get_context(loop_);
	return context ? new MainContext(context, false) : 0;
}

/*  G::Source
 */

G::Source::Source(GSource *source, bool owns_reference)
: source_(source)
{
	set_owns_reference(owns_reference);
}

G::Source::~Source()
{
	if (source_)
	{
		g_source_unref(source_);
		source_ = 0;
	}
}

Pointer<G::MainContext>
G::Source::get_context() const
{
	GMainContext *context = g_source_get_context(source_);
	return context ? new G::MainContext(context, false) : 0;
}

void
G::Source::get_current_time(TimeVal& timeval)
{
	g_source_get_current_time(source_, timeval.g_time_val());
}

bool
G::Source::is_attached(G::MainContext& context) const
{
	return g_source_get_context(source_) == context.g_main_context();
}

unsigned int
G::Source::attach(MainContext *context)
{
	return g_source_attach(source_, *context);
}

void
G::Source::ref()
{
	g_source_ref(source_);
}

void
G::Source::unref()
{
	bool last_unref = source_->ref_count == 1;
	g_source_unref(source_);
	if (last_unref)
	{
		source_ = 0;
		if (is_dynamic())
			delete this;
	}
}

namespace { // XfcSource, SourceCallback and GSourceFuncs

struct XfcSource
{
	GSource source;
	gpointer data;
};

struct SourceCallback
{
	typedef sigc::slot<bool> SourceSlot;
	SourceSlot slot_;

	SourceCallback(const SourceSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(void *data)
	{
		SourceCallback *cb = static_cast<SourceCallback*>(data);
		return cb->slot_();
	}

	static void destroy(void *data)
	{
		SourceCallback *cb = static_cast<SourceCallback*>(data);
		delete cb;
	}
};

gboolean prepare_callback(GSource *source, int *timeout)
{
	gboolean result = FALSE;
	G::CustomSource *object = reinterpret_cast<G::CustomSource*>((reinterpret_cast<XfcSource*>(source))->data);
	if (object)
		result = object->prepare(*timeout);
	return result;
}

gboolean check_callback(GSource *source)
{
	gboolean result = FALSE;
	G::CustomSource *object = reinterpret_cast<G::CustomSource*>((reinterpret_cast<XfcSource*>(source))->data);
	if (object)
		result = object->check();
	return result;
}

gboolean dispatch_callback(GSource *source, GSourceFunc, void *user_data)
{
	gboolean result = FALSE;
	G::CustomSource *object = reinterpret_cast<G::CustomSource*>((reinterpret_cast<XfcSource*>(source))->data);
	if (object)
	{
		SourceCallback *cb = static_cast<SourceCallback*>(user_data);
		result = object->dispatch(cb ? &cb->slot_ : 0);
	}
	return result;
}

void finalize_callback(GSource *source)
{
	delete reinterpret_cast<G::CustomSource*>((reinterpret_cast<XfcSource*>(source))->data);
}

const GSourceFuncs xfc_source_funcs =
{
	&prepare_callback,
	&check_callback,
	&dispatch_callback,
	&finalize_callback,
	0
};

} // namespace

/*  CustomSource
*/

G::CustomSource::CustomSource()
: Source(g_source_new(const_cast<GSourceFuncs*>(&xfc_source_funcs), sizeof(XfcSource)))
{
	reinterpret_cast<XfcSource*>(g_source())->data = this;
}

G::CustomSource::~CustomSource()
{
}

void 
G::CustomSource::add_poll(PollFD& fd)
{
	g_source_add_poll(g_source(), fd.g_poll_fd());
}
	
void 
G::CustomSource::remove_poll(PollFD& fd)
{
	g_source_remove_poll(g_source(), fd.g_poll_fd());
}
	
sigc::connection 
G::CustomSource::connect(const SourceSlot& slot)
{
	SourceCallback *cb = new SourceCallback(slot);
	g_source_set_callback(g_source(), &SourceCallback::notify, cb, &SourceCallback::destroy);
	return sigc::connection(const_cast<SourceSlot&>(slot));
}

namespace { // ChildWatchCallback

struct ChildWatchCallback
{
	typedef G::ChildWatchSource::WatchSlot WatchSlot;
	WatchSlot slot_;

	ChildWatchCallback(const WatchSlot& slot)
	: slot_(slot)
	{
	}

	static void notify(GPid pid, int status, void *data)
	{
		ChildWatchCallback *cb = static_cast<ChildWatchCallback*>(data);
		cb->slot_(pid, status);
	}

	static void destroy(void *data)
	{
		ChildWatchCallback *cb = static_cast<ChildWatchCallback*>(data);
		delete cb;
	}
};

} // namespace

/*  G::ChildWatchSource
 */

G::ChildWatchSource::ChildWatchSource(GPid pid)
: G::Source(g_child_watch_source_new(pid))
{
	set_priority(PRIORITY_DEFAULT);
}

G::ChildWatchSource::ChildWatchSource(GPid pid, const WatchSlot& slot)
: G::Source(g_child_watch_source_new(pid))
{
	ChildWatchCallback *cb = new ChildWatchCallback(slot);
	g_source_set_callback(g_source(), (GSourceFunc)&ChildWatchCallback::notify, cb, &ChildWatchCallback::destroy);
	set_priority(PRIORITY_DEFAULT);
}

sigc::connection 
G::ChildWatchSource::connect(const WatchSlot& slot)
{
	ChildWatchCallback *cb = new ChildWatchCallback(slot);
	g_source_set_callback(g_source(), (GSourceFunc)&ChildWatchCallback::notify, cb, &ChildWatchCallback::destroy);
	return sigc::connection(const_cast<WatchSlot&>(slot));
}

/*  G::TimeoutSource
 */

G::TimeoutSource::TimeoutSource(unsigned int interval)
: G::Source(g_timeout_source_new(interval))
{
	set_priority(PRIORITY_HIGH);
}

G::TimeoutSource::TimeoutSource(const SourceSlot& slot, unsigned int interval)
: G::Source(g_timeout_source_new(interval))
{
	SourceCallback *cb = new SourceCallback(slot);
	g_source_set_callback(g_source(), &SourceCallback::notify, cb, &SourceCallback::destroy);
	set_priority(PRIORITY_HIGH);
}

sigc::connection 
G::TimeoutSource::connect(const SourceSlot& slot)	
{
	SourceCallback *cb = new SourceCallback(slot);
	g_source_set_callback(g_source(), &SourceCallback::notify, cb, &SourceCallback::destroy);
	return sigc::connection(const_cast<SourceSlot&>(slot));
}

/*  G::IdleSource
 */

G::IdleSource::IdleSource()
: G::Source(g_idle_source_new())
{
	set_priority(PRIORITY_DEFAULT_IDLE);
}

G::IdleSource::IdleSource(const SourceSlot& slot)
: G::Source(g_idle_source_new())
{
	SourceCallback *cb = new SourceCallback(slot);
	g_source_set_callback(g_source(), &SourceCallback::notify, cb, &SourceCallback::destroy);
	set_priority(PRIORITY_DEFAULT_IDLE);
}

sigc::connection 
G::IdleSource::connect(const SourceSlot& slot)	
{
	SourceCallback *cb = new SourceCallback(slot);
	g_source_set_callback(g_source(), &SourceCallback::notify, cb, &SourceCallback::destroy);
	return sigc::connection(const_cast<SourceSlot&>(slot));
}

namespace { // IOWatchCallback

struct IOWatchCallback
{
	typedef G::IOSource::IOSlot IOSlot;
	IOSlot slot_;

	IOWatchCallback(const IOSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GIOChannel*, GIOCondition condition, void *data)
	{
		IOWatchCallback *cb = static_cast<IOWatchCallback*>(data);
		return cb->slot_((G::IOConditionField)condition);
	}

	static void destroy(void *data)
	{
		IOWatchCallback *cb = static_cast<IOWatchCallback*>(data);
		delete cb;
	}
};

} // namespace

/*  G::IOSource
 */

G::IOSource::IOSource(G::IOChannel& channel, G::IOConditionField condition)
: G::Source(g_io_create_watch(channel.g_io_channel(), (GIOCondition)condition))
{
	set_priority(PRIORITY_DEFAULT);
}

G::IOSource::IOSource(G::IOChannel& channel, G::IOConditionField condition, const IOSlot& slot)
: G::Source(g_io_create_watch(channel.g_io_channel(), (GIOCondition)condition))
{
	IOWatchCallback *cb = new IOWatchCallback(slot);
	g_source_set_callback(g_source(), (GSourceFunc)&IOWatchCallback::notify, cb, &IOWatchCallback::destroy);
	set_priority(PRIORITY_DEFAULT);
}

sigc::connection 
G::IOSource::connect(const IOSlot& slot)
{
	IOWatchCallback *cb = new IOWatchCallback(slot);
	g_source_set_callback(g_source(), (GSourceFunc)&IOWatchCallback::notify, cb, &IOWatchCallback::destroy);
	return sigc::connection(const_cast<IOSlot&>(slot));
}

/*  G::ChildWatchSignal
 */

G::ChildWatchSignal G::child_watch_signal;

sigc::connection
G::ChildWatchSignal::connect(const SlotType& slot, GPid pid, int priority)
{
	ChildWatchCallback *cb = new ChildWatchCallback(slot);
	g_child_watch_add_full(priority, pid, &ChildWatchCallback::notify, cb, &ChildWatchCallback::destroy);
	return sigc::connection(const_cast<SlotType&>(slot));
}

/*  G::TimeoutSignal
 */

G::TimeoutSignal G::timeout_signal;

sigc::connection
G::TimeoutSignal::connect(const SlotType& slot, unsigned int interval, int priority)
{
	SourceCallback *cb = new SourceCallback(slot);
	g_timeout_add_full(priority, interval, &SourceCallback::notify, cb, &SourceCallback::destroy);
	return sigc::connection(const_cast<SlotType&>(slot));
}

/*  G::IdleSignal
 */

G::IdleSignal G::idle_signal;

sigc::connection
G::IdleSignal::connect(const SlotType& slot, int priority)
{
	SourceCallback *cb = new SourceCallback(slot);
	g_idle_add_full(priority, &SourceCallback::notify, cb, &SourceCallback::destroy);
	return sigc::connection(const_cast<SlotType&>(slot));
}

/*  G::IOSignal
 */

G::IOSignal G::io_signal;

sigc::connection
G::IOSignal::connect(G::IOChannel& channel, G::IOConditionField condition, const SlotType& slot, int priority)
{
	IOWatchCallback *cb = new IOWatchCallback(slot);
	g_io_add_watch_full(channel.g_io_channel(), priority, (GIOCondition)condition, &IOWatchCallback::notify, cb, &IOWatchCallback::destroy);
	return sigc::connection(const_cast<SlotType&>(slot));
}

