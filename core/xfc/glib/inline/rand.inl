/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  rand.inl - G::Rand inline functions
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

/*  G::random_set_seed
 */

inline void
Xfc::G::random_set_seed(unsigned int seed)
{
	g_random_set_seed(seed);
}

/*  G::random_boolean
 */

inline bool
Xfc::G::random_boolean()
{
	return g_random_boolean();
}

/*  G::random_int
 */

inline unsigned int
Xfc::G::random_int()
{
	return g_random_int();
}

/*  G::random_int_range
 */

inline int
Xfc::G::random_int_range(int begin, int end)
{
	return g_random_int_range(begin, end);
}

/*  G::random_double
 */

inline double
Xfc::G::random_double()
{
	return g_random_double();
}

/*  G::random_double_range
 */

inline double
Xfc::G::random_double_range(double begin, double end)
{
	return g_random_double_range(begin, end);
}

/*  G::Rand
 */

inline GRand*
Xfc::G::Rand::g_rand() const
{
	return rand_;
}

inline Xfc::G::Rand::operator GRand* () const
{
	return this ? rand_ : 0;
}

inline bool
Xfc::G::Rand::get_bool() const
{
	return g_rand_boolean(rand_);
}

inline unsigned int
Xfc::G::Rand::get_int() const
{
	return g_rand_int(rand_);
}

inline int
Xfc::G::Rand::get_int_range(int begin, int end) const
{
	return g_rand_int_range(rand_, begin, end);
}

inline double
Xfc::G::Rand::get_double() const
{
	return g_rand_double(rand_);
}

inline double
Xfc::G::Rand::get_double_range(double begin, double end) const
{
	return g_rand_double_range(rand_, begin, end);
}

inline void
Xfc::G::Rand::set_seed(unsigned int seed)
{
	g_rand_set_seed(rand_, seed);
}

