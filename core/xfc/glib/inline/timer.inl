/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  timer.inl - G::Timer inline functions
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

inline GTimer*
Xfc::G::Timer::g_timer() const
{
	return timer_;
}

inline Xfc::G::Timer::operator GTimer* () const
{
	return this ? timer_ : 0;
}

inline void
Xfc::G::Timer::start()
{
	g_timer_start(timer_);
}

inline void
Xfc::G::Timer::stop()
{
	g_timer_stop(timer_);
}

inline void
Xfc::G::Timer::reset()
{
	g_timer_reset(timer_);
}

inline void 
Xfc::G::Timer::resume()
{
	g_timer_continue(timer_);
}

inline double
Xfc::G::Timer::elapsed(unsigned long *microseconds)
{
	return g_timer_elapsed(timer_, microseconds);
}

