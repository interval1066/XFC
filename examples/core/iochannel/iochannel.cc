// Simple example that shows you how to read one file (iochannel-test-infile)
// and write its contents to a new file (iochannel-test-outfile).

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <xfc/pointer.hh>
#include <xfc/utfstring.hh>
#include <xfc/glib/error.hh>
#include <xfc/glib/iochannel.hh>
#include <glib/gutils.h>
#include <iostream>

using namespace Xfc;

const int BUFFER_SIZE = 1024;

int main(int argc, char *argv[])
{
	String srcdir();
	String filename = g_get_current_dir();
	filename += '/';
	filename += "iochannel-test-infile";

	G::Error error;
	Pointer<G::IOChannel> gio_read = G::IOChannel::create(filename, "r", &error);
	if (error.get())
	{
		std::cout << "Unable to open file " << filename << ": " << error.message() << std::endl;
		return 1;
	}

	Pointer<G::IOChannel> gio_write = G::IOChannel::create("iochannel-test-outfile", "w", &error);
	if (error.get())
	{
		std::cout << "Unable to open file iochannel-test-outfile: " << error.message() << std::endl;
		return 1;
	}

	gio_read->set_encoding("EUC-JP", &error);
	if (error.get())
	{
		std::cout << error.message() << std::endl;
		return 1;
	}

	gio_read->set_buffer_size(BUFFER_SIZE);

	G::IOStatus status = gio_read->set_flags(G::IO_FLAG_NONBLOCK, &error);
	if (status == G::IO_STATUS_ERROR)
	{
		std::cout << error.message() << std::endl;
		return 1;
	}

	G::IOFlagsField flags = gio_read->get_flags();
	bool block = !(flags & G::IO_FLAG_NONBLOCK);
	if (block)
        	std::cout << " BLOCKING TRUE \n\n";
	else
		std::cout << " BLOCKING FALSE \n\n";

	String buffer;
	int read_length = 0;
	size_t length_out = 0;
	long write_length = 0;

	while (true)
	{
		do
		status = gio_read->read_line(buffer, 0, &error);
		while (status == G::IO_STATUS_AGAIN);
		if (status != G::IO_STATUS_NORMAL)
		break;

		read_length += buffer.size();

		do
		status = gio_write->write(buffer.c_str(), &length_out, &error);
		while (status == G::IO_STATUS_AGAIN);
		if (status != G::IO_STATUS_NORMAL)
		break;

		write_length += length_out;

		if (length_out < buffer.size())
			std::cout << "Only wrote part of the line." << std::endl;

		std::cout << buffer << std::endl;
	}

	switch (status)
	{
	case G::IO_STATUS_EOF:
		break;

	case G::IO_STATUS_ERROR:
		std::cout << error.message() << std::endl;
		break;

	default:
		std::cout << "Abnormal exit from write loop." << std::endl;
		break;
	}

	do
	status = gio_write->flush(&error);
	while (status == G::IO_STATUS_AGAIN);

	if (status == G::IO_STATUS_ERROR)
		std::cout << error.message() << std::endl;

	std::cout << "read " << read_length << " bytes, wrote " << write_length << " bytes" << std::endl;
	return 0;
}

