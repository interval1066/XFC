/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  rand.cc - A C++ interface for GRand.
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

#include "rand.hh"

using namespace Xfc;

/*  G::Rand
 */

G::Rand::Rand()
: rand_(g_rand_new())
{
}

G::Rand::Rand(unsigned int seed)
: rand_(g_rand_new_with_seed(seed))
{
}
	
G::Rand::Rand(const std::vector<unsigned int>& seed)
: rand_(!seed.empty() ? g_rand_new_with_seed_array(&seed[0], seed.size()) : 0)
{
}

G::Rand::Rand(const Rand& src)
: rand_(g_rand_copy(src.rand_))
{
}

G::Rand::~Rand()
{
	if (rand_)
	{
		g_rand_free(rand_);
		rand_ = 0;
	}
}

G::Rand& 
G::Rand::operator=(const Rand& src)
{
	if (src.rand_ == rand_)
		return *this;
		
	if (rand_)
		g_rand_free(rand_);
		
	rand_ = g_rand_copy(src.rand_);
	return *this;
}

void 
G::Rand::set_seed(const std::vector<unsigned int>& seed)
{
	if (!seed.empty())	
		g_rand_set_seed_array(rand_, &seed[0], seed.size());
}

