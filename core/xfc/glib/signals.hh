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

/// @file xfc/glib/signals.hh
/// @brief C++ signal interface for GTK+ signals.
///
/// Provides a set of signal class templates that wrap the GTK+ signal system.
/// Each class derived from G::Object declares a C++ signal for each of the GTK+
/// signals it emits. These signals are protected, are declared static, and
/// require an object pointer; for example the clicked_signal in the Gtk::Button
/// class. A public accessor method is declared for each protected signal; for
/// example signal_clicked() for the <EM>clicked_signal</EM>. These accessor methods
/// pass the object <EM>this</EM> pointer to the protected signal for you. The
/// signal classes are named Signal0 to Signal7, where 0 to 7 specifies
/// the number of arguments passed to a connected slot. (see sigc++/slot.h).

#ifndef XFC_G_SIGNALS_HH
#define XFC_G_SIGNALS_HH

#ifndef SIGCXX_SIGCXX_H
#include <sigc++/sigc++.h>
#endif

#ifndef __G_OBJECT_H__
#include <glib-object.h>
#endif

namespace Xfc {
	
namespace G {

typedef sigc::nil nil;

class TypeInstance;

/// @class SignalBase signals.hh xfc/glib/signals.hh
/// @brief Base class for the GTK+ C++ signal interface.

class SignalBase  : public sigc::signal_base
{
	SignalBase(const SignalBase&);
	SignalBase& operator=(const SignalBase&);

	const char *const name_;
	const GCallback callback_;

protected:
	typedef sigc::slot_base SlotBase;
	///< The base class for all sigc::slot's.

	SignalBase(const char *name, GCallback callback);
	///< Constructor.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	~SignalBase();
	///< Destructor.

	void connect(TypeInstance *instance, const SlotBase& slot, const char *detail, bool after) const;
	///< Connects <EM>slot</EM> to this signal through the callback specified in the constructor.
	///< @param instance The object instance containing the signal.
	///< @param slot The sigc::slot to connect to the signal.
	///< @param detail The detail string to append to the signal name.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.

public:
	const char* name() const { return name_; }
	///< Returns the name of the signal

	void stop_emission(TypeInstance *instance);
	///< Stops the signal's current emission.
	///< @param instance The object whose signal handlers you wish to stop.
	///<
	///< This will prevent the default method from running, if the signal was
	///< G_SIGNAL_RUN_LAST and you connected normally (i.e. without the "after" flag).
	///< Prints a warning if used on a signal which isn't being emitted.
};

/// @class SignalProxy signals.hh xfc/glib/signals.hh
/// @brief A proxy object for manipulating a protected signal (connection, mostly).
///
/// SignalProxy is used to access the connection method of a protected signal.

template<typename ObjectType, typename SignalType>
class SignalProxy
{
	ObjectType *const object_;
	const SignalType *const signal_;
	const char *const detail_;

public:
	typedef typename SignalType::SlotType SlotType;
	///< The slot signature for slots connecting to the specified SignalType.

	SignalProxy(ObjectType *object, const SignalType *signal, const char *detail = 0)
	: object_(object), signal_(signal), detail_(detail)
	{
	}
	///< Constructs a new signal proxy object.
	///< @param object An object that contains <EM>SignalType</EM>.
	///< @param signal The signal object, usually a protected static member of a class.
	///< @param detail The detail string to append to the signal name.
	///<
	///< The <EM>detail</EM> is set as a filter on one of the following signals:
	///< G::Object::notify_signal, Gtk::AccelMap::changed_signal and 
	///< Gtk::Widget::child_notify_signal. As a result, the signal name at connection
	///< time becomes 'name::detail' instead of 'name'. Specifying a detail on a signal,
	///< such as a property name for the G::Object::notify_signal, is a way of filtering
	///< out unwanted signal emissions on these frequently emitted signals.

	sigc::connection connect(const SlotType& slot, bool after = false) const
	{
		return signal_->connect(object_, slot, detail_, after);
	}
	///< Connect a slot to the signal.
	///< @param slot The sigc::slot object to connect to SignalType.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.

	template<typename MethodObjectType, typename MethodType>
	sigc::connection connect(MethodObjectType *object, MethodType method, bool after = false) const
	{
		return signal_->connect(object_, SlotType(object, method), detail_, after);
	}
	///< Connect a class method to the signal.
	///< @param object A pointer to the object that has <EM>MethodType</EM> as a member.
	///< @param method The class method in <EM>object</EM> to connect to this signal.
	///< @param after Set <EM>true</EM> to call the user-defined metho after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< This is a convenience method that creates the sigc::slot for you. All you
	///< need to do is pass this function is a pointer to the object and the object method,
	///< just as you would when creating a slot. The returned connection object can be used
	///< to control the signal connection, either by calling block(), unblock() or
	///< disconnect(). You don't need to call discconnect() unless you have good reason
	///< to. GTK+ signals are automatically disconnected when an object gets destroyed.

	template<typename FunctionType>
	sigc::connection connect(FunctionType function, bool after = false) const
	{
		return signal_->connect(object_, SlotType(function), detail_, after);
	}
	///< Connect a free function to the signal.
	///< @param function The free function to connect to this signal.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< This is a convenience method that creates the sigc::slot for you. All you
	///< need to do is pass a pointer to the function, just as you would when creating
	///< a slot. The returned connection object can be used to control the signal
	///< connection, either by calling block(), unblock() or disconnect(). You don't
	///< need to call discconnect() unless you have good reason to. GTK+ signals are
	///< automatically disconnected when an object gets destroyed.
};

/// @class Signal0 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing no arguments and returning a value of type R.

template <class R>
class Signal0 : public SignalBase
{
	Signal0(const Signal0&);
	Signal0& operator=(const Signal0&);

public:
	typedef sigc::slot<R> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking no
	///< arguments and returning type R.

	Signal0(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal1 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing one argument of type P1 and returning a value of type R.

template <typename R, typename P1>
class Signal1 : public SignalBase
{
	Signal1(const Signal1&);
	Signal1& operator=(const Signal1&);

public:
	typedef sigc::slot<R, P1> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking one
	///< argument (P1) and returning type R.

	Signal1(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal2 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing two arguments of type P1 and P2,
/// and returning a value of type R.

template <typename R, typename P1, typename P2>
class Signal2 : public SignalBase
{
	Signal2(const Signal2&);
	Signal2& operator=(const Signal2&);

public:
	typedef sigc::slot<R, P1, P2> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking two
	///< arguments (P1 and P2) and returning type R.

	Signal2(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal3 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing three arguments of type P1, P2 and P3,
/// and returning a value of type R.

template <typename R, typename P1, typename P2, typename P3>
class Signal3 : public SignalBase
{
	Signal3(const Signal3&);
	Signal3& operator=(const Signal3&);

public:
	typedef sigc::slot<R, P1, P2, P3> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking three
	///< arguments (P1, P2 and P3) and returning type R.

	Signal3(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2, P3>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal4 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing four arguments of type P1, P2, P3 and P4,
/// and returning a value of type R.

template <typename R, typename P1, typename P2, typename P3, typename P4>
class Signal4 : public SignalBase
{
	Signal4(const Signal4&);
	Signal4& operator=(const Signal4&);

public:
	typedef sigc::slot<R, P1, P2, P3, P4> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking four
	///< arguments (P1, P2, P3 and P4) and returning type R.

	Signal4(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2, P3, P4>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal5 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing five arguments of type P1, P2, P3, P4 and P5,
/// and returning a value of type R.

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class Signal5 : public SignalBase
{
	Signal5(const Signal5&);
	Signal5& operator=(const Signal5&);

public:
	typedef sigc::slot<R, P1, P2, P3, P4, P5> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking five
	///< arguments (P1, P2, P3, P4 and P5) and returning type R.

	Signal5(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2, P3, P4, P5>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal6 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing six arguments of type P1, P2, P3, P4, P5 and P6,
/// and returning a value of type R.

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Signal6 : public SignalBase
{
	Signal6(const Signal6&);
	Signal6& operator=(const Signal6&);

public:
	typedef sigc::slot<R, P1, P2, P3, P4, P5, P6> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking six
	///< arguments (P1, P2, P3, P4, P5 and P6) and returning type R.

	Signal6(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2, P3, P4, P5, P6>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal7 signals.hh xfc/glib/signals.hh
/// @brief A template for a signal passing seven arguments of type P1, P2, P3, P4, P5, P6 and P7,
/// and returning a value of type R.

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class Signal7 : public SignalBase
{
	Signal7(const Signal7&);
	Signal7& operator=(const Signal7&);

public:
	typedef sigc::slot<R, P1, P2, P3, P4, P5, P6, P7> SlotType;
	///< The slot signature for slots connecting to this signal is a function taking seven
	///< arguments (P1, P2, P3, P4, P5, P6 and P7) and returning type R.

	Signal7(const char *name, GCallback callback) : SignalBase(name, callback)
	{
	}
	///< Constructs a new signal.
	///< @param name The GTK+ name for the signal.
	///< @param callback The callback function to translate GObject signal emissions into sigc::slot calls.

	sigc::connection connect(TypeInstance *instance, const SlotType& slot, 
	                         const char *detail = 0, bool after = false) const
	{
		SignalBase::connect(instance, static_cast<const SlotBase&>(slot), detail, after);
		return sigc::connection(const_cast<SlotType&>(slot));
	}
	///< Connect a slot to the signal.
	///< @param instance The object instance containing the signal.
	///< @param slot A slot of type sigc::slot<R, P1, P2, P3, P4, P5, P6, P7>.
	///< @param detail The detail string to append to the signal name, or null.
	///< @param after Set <EM>true</EM> to call the user-defined slot after the signal,
	///<              or <EM>false</EM> to let the signal's default behavior preside.
	///< @return A sigc::connection object.
	///<
	///< The connection object can be used to control the signal connection, either by
	///< calling block(), unblock() or disconnect(). You don't need to call discconnect()
	///< unless you have good reason to. GTK+ signals are automatically disconnected when
	///< an object gets destroyed.
};

/// @class Signal signals.hh xfc/glib/signals.hh
/// @brief A convenience template wrapper for the numbered Signal#<> templates.
///
/// Signal can be used to connect slots that are invoked when GObject/GTK+ signals are emitted.
/// Any functor (sigc::mem_fun, sigc::ptr_fun), or sigc::slot can be passed into connect. A
/// functor is converted into a slot implicitely.

template<typename R, typename P1 = nil, typename P2 = nil, typename P3 = nil, typename P4 = nil, typename P5 = nil, typename P6 = nil, typename P7 = nil>
class Signal : public Signal7<R, P1, P2, P3, P4, P5, P6, P7>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal7<R, P1, P2, P3, P4, P5, P6, P7>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 0 arguments.

template<typename R>
class Signal<R> : public Signal0<R>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal0<R>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 1 arguments.

template<typename R, typename P1>
class Signal<R, P1> : public Signal1<R, P1>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal1<R, P1>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 2 arguments.

template<typename R, typename P1, typename P2>
class Signal<R, P1, P2> : public Signal2<R, P1, P2>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal2<R, P1, P2>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 3 arguments.

template<typename R, typename P1, typename P2, typename P3>
class Signal<R, P1, P2, P3> : public Signal3<R, P1, P2, P3>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal3<R, P1, P2, P3>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 4 arguments.

template<typename R, typename P1, typename P2, typename P3, typename P4>
class Signal<R, P1, P2, P3, P4> : public Signal4<R, P1, P2, P3, P4>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal4<R, P1, P2, P3, P4>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 5 arguments.

template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class Signal<R, P1, P2, P3, P4, P5> : public Signal5<R, P1, P2, P3, P4, P5>
{
	Signal(const char *name, GCallback callback)
	: Signal5<R, P1, P2, P3, P4, P5>(name, callback)
	{
	}
};

// A convenience template wrapper for the numbered Signal#<> templates.
// This is the template specialization of the unnumbered Signal<> template for 6 arguments.

template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Signal<R, P1, P2, P3, P4, P5, P6> : public Signal6<R, P1, P2, P3, P4, P5, P6>
{
public:
	Signal(const char *name, GCallback callback)
	: Signal6<R, P1, P2, P3, P4, P5, P6>(name, callback)
	{
	}
};

} // namespace G

} // namespace Xfc

#endif // XFC_G_SIGNALS_HH

