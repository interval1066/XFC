/* Images
 *
 * Gtk::Image is used to display an image; the image can be in a number of formats.
 * Typically, you load an image into a Gdk::Pixbuf, then display the pixbuf.
 *
 * This demo code shows some of the more obscure cases, in the simple
 * case a call to 'new Image(const String& filename)' is all you need.
 *
 * If you want to put image data in your program as a C variable,
 * use the make-inline-pixbuf program that comes with GTK+.
 * This way you won't need to depend on loading external files, your
 * application binary can be self-contained.
 */

#include "demowindow.hh"
#include <xfc/gtk/alignment.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/togglebutton.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <xfc/gdk-pixbuf/pixbuf-loader.hh>
#include <xfc/glib/main.hh>
#include <glib/gstdio.h>
#include <cstdio>
#include <cerrno>

using namespace Xfc;

class ImageWindow : public Gtk::Window
{
	Gtk::VBox *vbox;
	Gtk::Image *image;
	Gtk::ToggleButton *toggle_button;
	Gdk::PixbufLoader *pixbuf_loader;
	static FILE *image_stream;

	void on_progressive_prepared();
	bool on_progressive_timeout();
	void on_progressive_updated(int x, int y, int width, int height);
	void on_toggle_sensitivity();

	sigc::connection timeout_connection;

public:
	ImageWindow();
	~ImageWindow();
};
//!

FILE *ImageWindow::image_stream = 0;

ImageWindow::ImageWindow()
: image(0), pixbuf_loader(0)
{
	set_title("Images");
	set_border_width(8);

	vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(8);
	add(*vbox);

	Gtk::Label *label = new Gtk::Label;
	label->set_markup("<u>Image loaded from a file</u>");
	vbox->pack_start(*label, false, false);

	Gtk::Frame *frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);

	// The alignment keeps the frame from growing when users resize the window
	Gtk::Alignment *align = new Gtk::Alignment(0.5, 0.5, 0, 0);
	align->add(*frame);
	vbox->pack_start(*align, false, false);

	// DemoWindow::find_file() looks in the the current directory first, then looks in the location where the file is installed.
	Pointer<Gdk::Pixbuf> pixbuf;
	G::Error error;
	String filename = DemoWindow::find_file("gtk-logo-rgb.gif", &error);
	if (!filename.null())
		pixbuf = Gdk::Pixbuf::create(filename, &error);

	if (error.get())
	{
		// This code shows off error handling. You can just use 'Gdk::Pixbuf::create(filename)'
		// instead if you don't want to report errors to the user. If the file doesn't load when 
		// using 'Gdk::Pixbuf::create(filename)', a "missing image" icon will be displayed instead.
		Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
		dialog.format_message("Unable to open image file 'gtk-logo-rgb.gif': %s", error.message());
		dialog.set_position(Gtk::WIN_POS_CENTER);
		if (dialog.run())
			dialog.dispose();
	}

	image = new Gtk::Image(*pixbuf);
	frame->add(*image);

	// Animation
 	label = new Gtk::Label;
	label->set_markup("<u>Animation loaded from a file</u>");
	vbox->pack_start(*label, false, false);

	frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);

	// The alignment keeps the frame from growing when users resize the window
	align = new Gtk::Alignment(0.5, 0.5, 0, 0);
	align->add(*frame);
	vbox->pack_start(*align, false, false);

	filename = DemoWindow::find_file("floppybuddy.gif");
	image = new Gtk::Image(filename);
	frame->add(*image);


	// Progressive
	label = new Gtk::Label;
	label->set_markup("<u>Progressive image loading</u>");
	vbox->pack_start(*label, false, false);

	frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);

	// The alignment keeps the frame from growing when users resize the window
	align = new Gtk::Alignment(0.5, 0.5, 0, 0);
	align->add(*frame);
	vbox->pack_start(*align, false, false);

	// Create an empty image for now; the progressive loader will create the pixbuf and fill it in.
	image = new Gtk::Image();
	frame->add(*image);

	timeout_connection = G::timeout_signal.connect(sigc::mem_fun(this, &ImageWindow::on_progressive_timeout), 150);

	// Sensitivity control
	toggle_button = new Gtk::ToggleButton("_Insensitive", true);
	vbox->pack_start(*toggle_button, false, false);
	toggle_button->signal_toggled().connect(sigc::mem_fun(this, &ImageWindow::on_toggle_sensitivity));
	show_all();
}

ImageWindow::~ImageWindow()
{
	if (pixbuf_loader)
	{
		pixbuf_loader->close();
		pixbuf_loader->unref();
		pixbuf_loader = 0;
	}

	if (image_stream)
 	{
 		timeout_connection.disconnect();
   		fclose(image_stream);
		image_stream = 0;
	}
}

bool
ImageWindow::on_progressive_timeout()
{
	// This shows off fully-paranoid error handling, so looks scary. You could factor out
	// the error handling code into a nice separate function to make things nicer.
	if (image_stream)
	{
		size_t bytes_read;
		unsigned char buf[256];

		bytes_read = fread(buf, 1, 256, image_stream);
		if (ferror(image_stream))
		{
			Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
			dialog.format_message("Failure reading image file 'alphatest.png': %s", g_strerror (errno));
			dialog.set_position(Gtk::WIN_POS_CENTER);
			fclose(image_stream);
			image_stream = 0;
			if (dialog.run())
				dialog.dispose();
			return false; // uninstall the timeout
		}

		G::Error error;
		if (!pixbuf_loader->write(buf, bytes_read, &error))
		{
			Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
			dialog.format_message("Failed to load image: %s", error.message());
			dialog.set_position(Gtk::WIN_POS_CENTER);
			fclose(image_stream);
			image_stream = 0;
			if (dialog.run())
				dialog.dispose();
			return false; // uninstall the timeout
		}

		if (feof(image_stream))
		{
			fclose(image_stream);
			image_stream = 0;

			// Errors can happen on close, e.g. if the image file was truncated we'll know on close that it was incomplete.
			error.clear();
			if (!pixbuf_loader->close(&error))
			{
				Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
				dialog.format_message("Failed to load image: %s", error.message());
				dialog.set_position(Gtk::WIN_POS_CENTER);
				if (dialog.run())
					dialog.dispose();
				pixbuf_loader->unref();
				pixbuf_loader = 0;
				return false; // uninstall the timeout
			}
			pixbuf_loader->unref();
			pixbuf_loader = 0;
	    }
	}
	else
	{
		// DemoWindow::find_file() looks in the the current directory first, then looks in the location where the file is installed.
		G::Error error;
		String error_message;
		String filename = DemoWindow::find_file("alphatest.png", &error);
		if (error.get())
			error_message.assign(error.message());
		else
		{
			image_stream = g_fopen(filename.c_str(), "r");
			if (!image_stream)
				error_message.format("Unable to open image file 'alphatest.png': %s", g_strerror(errno));
		}

		if (!image_stream)
		{
			Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, error_message, this);
			dialog.set_position(Gtk::WIN_POS_CENTER);
			dialog.run();
			dialog.dispose();
			return false; // uninstall the timeout
		}

		if (pixbuf_loader)
		{
			pixbuf_loader->close();
			pixbuf_loader->unref();
			pixbuf_loader = 0;
		}

		pixbuf_loader = new Gdk::PixbufLoader;
		pixbuf_loader->signal_area_prepared().connect(sigc::mem_fun(this, &ImageWindow::on_progressive_prepared));
		pixbuf_loader->signal_area_updated().connect(sigc::mem_fun(this, &ImageWindow::on_progressive_updated));
	}

	// leave timeout installed
	return true;
}

void
ImageWindow::on_progressive_prepared()
{
	Gdk::Pixbuf *pixbuf = pixbuf_loader->get_pixbuf();

	// Avoid displaying random memory contents, since the pixbuf isn't filled in yet.
	pixbuf->fill(0xaaaaaaff);

	image->set(pixbuf);
}

void
ImageWindow::on_progressive_updated(int x, int y, int width, int height)
{
	// We know the pixbuf inside the Gtk::Image has changed, but the image itself doesn't know this;
	// so queue a redraw. If we wanted to be really efficient, we could use a drawing area or something
	// instead of a Gtk::Image, so we could control the exact position of the pixbuf on the display,
	// then we could queue a draw for only the updated area of the image.
	image->queue_draw();
}

void
ImageWindow::on_toggle_sensitivity()
{
	std::vector<Gtk::Widget*> list;
	if (vbox->get_children(list))
	{
		int count = list.size();
		for (int i = 0; i < count; i++)
		{
			if (list[i]->gtk_widget() != toggle_button->gtk_widget())
				list[i]->set_sensitive(!toggle_button->get_active());
		}
	}
}

Gtk::Window*
do_images(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ImageWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

