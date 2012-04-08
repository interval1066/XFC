/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/glib/timer.hh
/// @brief GTimer C++ interface.
///
/// Provides Timer, an object that keeps track of elapsed time.

#ifndef XFC_G_TIMER_HH
#define XFC_G_TIMER_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_TIMER_H__
#include <glib/gtimer.h>
#endif

namespace Xfc {

namespace G {

/// @class Timer timer.hh xfc/glib/timer.hh
/// @brief A GTimer C++ wrapper interface.
///
/// Timer records a start time, and counts microseconds elapsed since that time.
/// This is done somewhat differently on different platforms, and can be tricky
/// to get exactly right, so Timer provides a portable and convenient interface.
///
/// There is not much you can do with a timer. You can construct it, start() it
/// running, stop() it running, and reset() it to zero.

class Timer : public Xfc::Object
{
	Timer(const Timer&);
	Timer& operator=(const Timer&);

	GTimer *timer_;

public:
/// @name Constructors
/// @{

	Timer();
	///< Constructs a new timer, and starts timing (that is, start() is
	///< implicitly called for you).

	~Timer();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GTimer* g_timer() const;
	///< Get a pointer to the GTimer object.

	operator GTimer* () const;
	///< Conversion operator; Safely converts a G::Timer object into a GTimer pointer.

/// @}
/// @name Methods
/// @{

	void start();
	///< Marks a start time, so that future calls to elapsed() will report the time since start()
	///< was called. When you construct a new timer this method automatically marks the start
	///< time, so there is no need to call start() immediately after constructing the timer.

	void stop();
	///< Marks an end time, so calls to elapsed() will return the difference between this
	///< end time and the start time.

	void reset();
	///< Reset an already started timer to zero. It's fine to call start() on an
	///< already-started timer to reset the start time, so reset() serves no real
	///< purpose, other than to make the intentions of your code a bit clearer.

	void resume();
	///< Resumes a timer that has previously been stopped with stop(). Note stop() 
	///< must be called before using this function. 
	
	double elapsed(unsigned long *microseconds = 0);
	///< Obtains the elapsed time.
	///< @param microseconds The fractional part of seconds elapsed, in microseconds, or null.
	///< @return The seconds elapsed as a floating point value, including any fractional part.
	///<
	///< If a timer has been started but not stopped this method obtains the time since
	///< the timer was started. If timer has been stopped it obtains the elapsed time
	///< between the time it was started and the time it was stopped. The return value is
	///< the number of seconds elapsed, including any fractional part. If <EM>microseconds</EM>
	///< is non-null, it will be set to the microseconds fraction of the elapsed time. It does
	///< not contain the seconds. The microseconds out parameter is not very useful.

/// @}

};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/timer.inl>

#endif // XFC_G_TIMER_HH



