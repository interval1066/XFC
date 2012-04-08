/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  clipboard.cc - GtkClipboard C++ wrapper implementation
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
 
#include "clipboard.hh"
#include "selection.hh"
#include "../gdk/display.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

Gtk::Clipboard::Clipboard(GtkClipboard *clipboard, bool owns_reference)
: G::Object((GObject*)clipboard, owns_reference)
{
}

Gtk::Clipboard::~Clipboard()
{
}
	
Gtk::Clipboard*
Gtk::Clipboard::get(Gdk::Atom selection, const Gdk::Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Clipboard>(gtk_clipboard_get_for_display(tmp_display, selection));
}

Gtk::Clipboard*
Gtk::Clipboard::get_default(const Gdk::Display *display)
{
	return get(GDK_SELECTION_CLIPBOARD, display);
}

Gtk::Clipboard*
Gtk::Clipboard::get_primary(const Gdk::Display *display)
{
	return get(GDK_SELECTION_PRIMARY, display);
}

Gdk::Display*
Gtk::Clipboard::get_display() const
{
	return G::Object::wrap<Gdk::Display>(gtk_clipboard_get_display(gtk_clipboard()));
}

namespace { // GetClearCallback

struct GetClearCallback
{
	typedef Gtk::Clipboard::GetSlot GetSlot;
	typedef Gtk::Clipboard::ClearSlot ClearSlot;

	GetSlot get_slot_;
	ClearSlot clear_slot_;

	GetClearCallback(const GetSlot& get_slot, const ClearSlot& clear_slot)
	: get_slot_(get_slot), clear_slot_(clear_slot)
	{
	}

	static void get(GtkClipboard*, GtkSelectionData *selection_data, guint info, void *data)
	{
		GetClearCallback *cb = static_cast<GetClearCallback*>(data);
		Gtk::SelectionData tmp_selection_data(selection_data);
		cb->get_slot_(tmp_selection_data, info);
	}

	static void clear(GtkClipboard*, gpointer data)
	{
		GetClearCallback *cb = static_cast<GetClearCallback*>(data);
		cb->clear_slot_();
		delete cb;
	}
};

} // namespace

bool
Gtk::Clipboard::set(const std::vector<TargetEntry>& targets, const GetSlot& get, const ClearSlot& clear)
{
	g_return_val_if_fail(!targets.empty(), false);
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	GetClearCallback *cb = new GetClearCallback(get, clear);
	bool result = gtk_clipboard_set_with_data(gtk_clipboard(), tmp_targets, count, &GetClearCallback::get, &GetClearCallback::clear, cb);
	delete [] tmp_targets;
	return result;
}

void
Gtk::Clipboard::set_text(const String& text)
{
	gtk_clipboard_set_text(gtk_clipboard(), text.c_str(), text.size());
}

void 
Gtk::Clipboard::set_image(Gdk::Pixbuf& pixbuf)
{
	gtk_clipboard_set_image(gtk_clipboard(), pixbuf.gdk_pixbuf());
}

namespace { // ReceivedCallback

struct ReceivedCallback
{
	typedef Gtk::Clipboard::ReceivedSlot ReceivedSlot;
	ReceivedSlot slot_;

	ReceivedCallback(const ReceivedSlot& slot)
	: slot_(slot)
	{
	}

	static void get(GtkClipboard*, GtkSelectionData *selection_data, void *data)
	{
		ReceivedCallback *cb = static_cast<ReceivedCallback*>(data);
		Gtk::SelectionData tmp_selection_data(selection_data);
		cb->slot_(tmp_selection_data);
		delete cb;
	}
};

} // namespace

void
Gtk::Clipboard::request_contents(Gdk::Atom target, const ReceivedSlot& received) const
{
	ReceivedCallback *cb = new ReceivedCallback(received);
	gtk_clipboard_request_contents(gtk_clipboard(), target, &ReceivedCallback::get, cb);
}

namespace { // TextReceivedCallback

struct TextReceivedCallback
{
	typedef Gtk::Clipboard::TextReceivedSlot TextReceivedSlot;
	TextReceivedSlot slot_;

	TextReceivedCallback(const TextReceivedSlot& slot)
	: slot_(slot)
	{
	}

	static void get(GtkClipboard*, const gchar *text, void *data)
	{
		TextReceivedCallback *cb = static_cast<TextReceivedCallback*>(data);
		String tmp_text(text);
		cb->slot_(tmp_text);
		delete cb;
	}
};

} // namespace

void
Gtk::Clipboard::request_text(const TextReceivedSlot& received) const
{
	TextReceivedCallback *cb = new TextReceivedCallback(received);
	gtk_clipboard_request_text(gtk_clipboard(), &TextReceivedCallback::get, cb);
}

namespace { // ImageReceivedCallback

struct ImageReceivedCallback
{
	typedef Gtk::Clipboard::ImageReceivedSlot ImageReceivedSlot;
	ImageReceivedSlot slot_;

	ImageReceivedCallback(const ImageReceivedSlot& slot)
	: slot_(slot)
	{
	}

	static void get(GtkClipboard*, GdkPixbuf *pixbuf, void* data)
	{
		ImageReceivedCallback *cb = static_cast<ImageReceivedCallback*>(data);
		Pointer<Gdk::Pixbuf> tmp_pixbuf(G::Object::wrap<Gdk::Pixbuf>(pixbuf));				
		cb->slot_(tmp_pixbuf);
		delete cb;
	}
};

} // namespace

void 
Gtk::Clipboard::request_image(const ImageReceivedSlot& received)
{
	ImageReceivedCallback *cb = new ImageReceivedCallback(received);
	gtk_clipboard_request_image(gtk_clipboard(), &ImageReceivedCallback::get, cb);
}

namespace { // TargetsReceivedCallback

struct TargetsReceivedCallback
{
	typedef Gtk::Clipboard::TargetsReceivedSlot TargetsReceivedSlot;
	TargetsReceivedSlot slot_;

	TargetsReceivedCallback(const TargetsReceivedSlot& slot)
	: slot_(slot)
	{
	}
	
	static void get(GtkClipboard*, GdkAtom *atoms, gint n_atoms, void *data)
	{
		std::vector<GdkAtom> targets;		
		
		int i = 0;
		while (i < n_atoms)
		{
			targets.push_back(atoms[i]);
			++i;
		}

		TargetsReceivedCallback *cb = static_cast<TargetsReceivedCallback*>(data);
		cb->slot_(targets);
		delete cb;
	}
};

} // namespace

void 
Gtk::Clipboard::request_targets(const TargetsReceivedSlot& received)
{
	TargetsReceivedCallback *cb = new TargetsReceivedCallback(received);
	gtk_clipboard_request_targets(gtk_clipboard(), &TargetsReceivedCallback::get, cb);

}

Pointer<Gtk::SelectionData>
Gtk::Clipboard::wait_for_contents(Gdk::Atom target) const
{
	GtkSelectionData* data = gtk_clipboard_wait_for_contents(gtk_clipboard(), target);
	return data ? G::Boxed::wrap<SelectionData>(GTK_TYPE_SELECTION_DATA, data, false) : 0;
}

String
Gtk::Clipboard::wait_for_text() const
{
	return gtk_clipboard_wait_for_text(gtk_clipboard());
}

Pointer<Gdk::Pixbuf> 
Gtk::Clipboard::wait_for_image()
{
	GdkPixbuf *pixbuf = gtk_clipboard_wait_for_image(gtk_clipboard());
	return pixbuf ? G::Object::wrap<Gdk::Pixbuf>(pixbuf, true) : 0;
}

bool
Gtk::Clipboard::wait_for_targets(std::vector<Gdk::Atom>& targets) const
{
	g_return_val_if_fail(targets.empty(), false);
	GdkAtom *tmp_targets = 0;
	int n_atoms = 0;

	bool result = gtk_clipboard_wait_for_targets(gtk_clipboard(), &tmp_targets, &n_atoms);
	if (result)
	{
		int i = 0;
		while (i < n_atoms)
		{
			targets.push_back(tmp_targets[i]);
			++i;
		}
		g_free(tmp_targets);
	}
	return result;
}

void 
Gtk::Clipboard::set_can_store(const std::vector<TargetEntry>& targets)
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}
	
	gtk_clipboard_set_can_store(gtk_clipboard(), tmp_targets, count);
	delete [] tmp_targets;
}

