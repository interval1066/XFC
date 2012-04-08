/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fileutils.cc - C++ interface for GDir and various GLib file-related functions.
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

#include "fileutils.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gstrfuncs.h>
#include <glib/gmessages.h>
#include <xfc-config.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef G_OS_WIN32
#include <io.h>
#endif

using namespace Xfc;

/* G::file_test
 */

bool
G::file_test(const std::string& filename, FileTestField test)
{
	return file_test(filename.c_str(), test);
}

/*  G::file_get_contents
 */

bool
G::file_get_contents(const char *filename, std::string& contents, G::Error *error)
{
	gsize length;
	char *tmp_contents = 0;
	bool result = g_file_get_contents(filename, &tmp_contents, &length, *error);
	contents.assign(tmp_contents, length);
	g_free(tmp_contents);
	return result;
}

bool
G::file_get_contents(const std::string& filename, std::string& contents, G::Error *error)
{
	return file_get_contents(filename.c_str(), contents, error);
}

/*  G::TempFile
 */

G::TempFile::TempFile()
: file_descriptor_(-1)
{
}

G::TempFile::TempFile(std::string& template_filename)
{
	mkstemp(template_filename);
}

G::TempFile::TempFile(const char *template_filename, std::string& actual_filename, G::Error *error)
{
	open(template_filename, actual_filename, error);
}

G::TempFile::TempFile(const std::string& template_filename, std::string& actual_filename, G::Error *error)
{
	open(template_filename, actual_filename, error);
}

G::TempFile::~TempFile()
{
	if (file_descriptor_ >= 0)
		::close(file_descriptor_);
}

bool
G::TempFile::open(std::string& actual_filename, G::Error *error)
{
	char *name_used = 0;
	file_descriptor_ = g_file_open_tmp(0, &name_used, *error);
	actual_filename = name_used;
	g_free(name_used);
	return file_descriptor_ != -1;
}

bool
G::TempFile::open(const char *template_filename, std::string& actual_filename, G::Error *error)
{
	char *name_used = 0;
	std::string filename(template_filename);
	filename.append("XXXXXX");
	file_descriptor_ = g_file_open_tmp(filename.c_str(), &name_used, *error);
	actual_filename = name_used;
	g_free(name_used);
	return file_descriptor_ != -1;
}

bool
G::TempFile::open(const std::string& template_filename, std::string& actual_filename, G::Error *error)
{
	return open(template_filename.c_str(), actual_filename, error);
}

bool
G::TempFile::mkstemp(std::string& template_filename)
{
	char *actual_filename = g_strconcat(template_filename.c_str(), "XXXXXX", 0);
	file_descriptor_ = g_mkstemp(actual_filename);
	template_filename = actual_filename;
	g_free(actual_filename);
	return file_descriptor_ != -1;
}

bool
G::TempFile::close()
{
	int result = -1;
	if (file_descriptor_ != -1)
	{
		result = ::close(file_descriptor_);
		file_descriptor_ = -1;
	}
	return result != -1;
}

/*  G::Dir
 */

G::Dir::Dir()
: dir_(0)
{
}

G::Dir::Dir(const char *path, G::Error *error)
: dir_(g_dir_open(path, 0, *error))
{
}

G::Dir::Dir(const std::string& path, G::Error *error)
: dir_(g_dir_open(path.c_str(), 0, *error))
{
}

G::Dir::~Dir()
{
	if (dir_)
		g_dir_close(dir_);
}

bool
G::Dir::open(const char *path, G::Error *error)
{
	dir_ = g_dir_open(path, 0, *error);
	return dir_ != 0;
}

bool
G::Dir::open(const std::string& path, G::Error *error)
{
	return open(path.c_str(), error);
}

int
G::Dir::read_names(std::vector<std::string>& names)
{
	g_return_val_if_fail(dir_ != 0, -1);
	g_return_val_if_fail(names.empty(), -1);

	int result = 0;
	const char *dir_entry;
	while ((dir_entry = g_dir_read_name(dir_)) != 0)
	{
		names.push_back(dir_entry);
		result++;
		continue;
	}
	return result;
}

void
G::Dir::close()
{
	if (dir_)
	{
		g_dir_close(dir_);
		dir_ = 0;
	}
}

