/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  fileutils.inl - File utilities inline functions
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

/*  G::file_error_from_errno
 */

inline Xfc::G::FileError
Xfc::G::file_error_from_errno(int err_no)
{
	return (FileError)g_file_error_from_errno(err_no);
}

/* G::file_test
 */

bool
Xfc::G::file_test(const char *filename, FileTestField test)
{
	return g_file_test(filename, (GFileTest)test);
}

/*  G::TempFile
 */

inline bool
Xfc::G::TempFile::is_open() const
{
	return file_descriptor_ != -1;
}

/*  G::Dir
 */

inline bool
Xfc::G::Dir::is_open() const
{
	return dir_ != 0;
}

inline const char*
Xfc::G::Dir::read_name()
{
	return g_dir_read_name(dir_);
}

inline void
Xfc::G::Dir::rewind()
{
	g_dir_rewind(dir_);
}

