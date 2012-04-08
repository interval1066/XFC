/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  trackable.cc - Primary base class for Xfc::Object, Xfc::G::Boxed, and Xfc::G::TypeInstance.
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

#include "trackable.hh"
#include <algorithm>

using namespace Xfc;

/*  Static members
 */

Trackable::AllocationList Trackable::allocation_list_;
std::new_handler Trackable::current_handler_;

/*  Trackable::AllocationList
 */

Trackable::AllocationList::AllocationList()
{
}

Trackable::AllocationList::~AllocationList()
{
	iterator i = begin();
	while (i != end())
	{
		::operator delete (*i);
		++i;
	}
	clear();
}

/* Trackable
 */
 
Trackable::Trackable()
: owns_reference_(false)
{
}

Trackable::~Trackable()
{
}

void 
Trackable::ref()
{
}

void 
Trackable::unref()
{
}

std::new_handler
Trackable::set_new_handler(std::new_handler handler)
{
	std::new_handler old_handler = current_handler_;
	current_handler_ = handler;
	return old_handler;
}

void*
Trackable::operator new(size_t size)
{
	// Set the new_handler for this call
	std::new_handler global_handler  = std::set_new_handler(current_handler_);

	// If allocation fails current_handler_ is called, if specified, otherwise the global new_handler is called.
	void *ptr;

	try
	{
		ptr = ::operator new(size);
		allocation_list_.push_front(ptr);
	}
	catch(std::bad_alloc&)
	{
		std::set_new_handler(global_handler);
		throw;
	}

	//  Reset gloabal new_handler
	std::set_new_handler(global_handler);
	return ptr;
}

#if (__GNUC__ < 4 && __GNUC_MINOR__ < 4)

void* 
Trackable::operator new(size_t size, void *ptr)
{
	return ::operator new(size, ptr);
}

#endif

void
Trackable::operator delete(void *ptr)
{
	AllocationList::iterator i = std::find(allocation_list_.begin(), allocation_list_.end(), ptr);
	if (i != allocation_list_.end())
	{
		allocation_list_.erase(i);
		::operator delete(ptr);
	}
}

bool
Trackable::is_dynamic() const
{
	// Get pointer to beginning of the memory occupied by this.
	const void* ptr = dynamic_cast<const void*>(this);
	
	// Search for ptr in allocation_list
	AllocationList::iterator i = std::find(allocation_list_.begin(), allocation_list_.end(), ptr);
	return i != allocation_list_.end();
}

