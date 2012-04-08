/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  combobox.cc - GtkComboBox C++ wrapper implementation
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

#include "combobox.hh"
#include "comboboxsignals.hh"
#include "liststore.hh"
#include "cellrenderertext.hh"
#include "private/comboboxclass.hh"
#include "private/marshal.hh"
#include "../atk/object.hh"

using namespace Xfc;

/*  Gtk::ComboBox
 */

Gtk::ComboBox::ComboBox(GtkComboBox *combo_box, bool owns_reference)
: Bin((GtkBin*)combo_box, owns_reference)
{
}

Gtk::ComboBox::ComboBox()
: Bin((GtkBin*)ComboBoxClass::create())
{
}	
		
Gtk::ComboBox::ComboBox(TreeModel& model)
: Bin((GtkBin*)ComboBoxClass::create())
{
	set_model(model);
}	

Gtk::ComboBox::~ComboBox()
{
}

bool 
Gtk::ComboBox::get_active_iter(TreeIter& iter) const
{
	return gtk_combo_box_get_active_iter(gtk_combo_box(), iter.gtk_tree_iter());
}	

Gtk::TreeModel* 
Gtk::ComboBox::get_model() const
{
	Gtk::TreeModel *tmp_model = 0;
	GtkTreeModel *model = gtk_combo_box_get_model(gtk_combo_box());
	if (model)
	{
		G::Object *object = G::Object::pointer((GObject*)model);
		tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_model;
}

Atk::Object* 
Gtk::ComboBox::get_popup_accessible() const
{
	return G::Object::wrap<Atk::Object>(gtk_combo_box_get_popup_accessible(gtk_combo_box()));
}

void 
Gtk::ComboBox::set_active_iter(const TreeIter& iter)
{
	gtk_combo_box_set_active_iter(gtk_combo_box(), iter.gtk_tree_iter());
}

void 
Gtk::ComboBox::set_model(TreeModel& model)
{
	gtk_combo_box_set_model(gtk_combo_box(), model.gtk_tree_model());
}
	
namespace { // RowSeparatorCallback

struct RowSeparatorCallback
{
	typedef Gtk::ComboBox::RowSeparatorSlot RowSeparatorSlot;
	RowSeparatorSlot slot_;

	RowSeparatorCallback(const RowSeparatorSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeModel *model, GtkTreeIter *iter, void *data)
	{
		RowSeparatorCallback *cb = static_cast<RowSeparatorCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		return cb->slot_(*tmp_model, tmp_iter);
	}

	static void destroy(void *data)
	{
		RowSeparatorCallback *cb = static_cast<RowSeparatorCallback*>(data);
		delete cb;
	}
};

} // namespace

void  
Gtk::ComboBox::set_row_separator_func(const RowSeparatorSlot& slot)
{
	RowSeparatorCallback *cb = new RowSeparatorCallback(slot);
	gtk_combo_box_set_row_separator_func(gtk_combo_box(), &RowSeparatorCallback::notify, cb, &RowSeparatorCallback::destroy);
}

void  
Gtk::ComboBox::unset_row_separator_func()
{
	gtk_combo_box_set_row_separator_func(gtk_combo_box(), 0, 0, 0);
}

/*  Gtk::ComboBoxClass
 */

void
Gtk::ComboBoxClass::init(GtkComboBoxClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->changed = &changed_proxy;
}

GtkComboBoxClass*
Gtk::ComboBoxClass::get_parent_class(void *instance)
{
	return static_cast<GtkComboBoxClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ComboBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_COMBO_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ComboBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ComboBoxClass::changed_proxy(GtkComboBox *combo_box)
{
	ComboBoxSignals *signals = dynamic_cast<ComboBoxSignals*>(G::ObjectSignals::pointer((GObject*)combo_box));
	if (signals)
		signals->on_changed();
	else
	{
		GtkComboBoxClass *g_class = get_parent_class(combo_box);
		if (g_class && g_class->changed)
			g_class->changed(combo_box);
	}
}

/*  Gtk::ComboBox signals
 */

const Gtk::ComboBox::ChangedSignalType Gtk::ComboBox::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

/*  Gtk::ComboBoxText
 */
 
Gtk::ComboBoxText::ComboBoxText()
: ComboBox((GtkComboBox*)ComboBoxClass::create())
{
	Pointer<Gtk::ListStore> model = new Gtk::ListStore(1, G_TYPE_STRING);	
	set_model(*model);
	Gtk::CellRendererText *cell_renderer = new Gtk::CellRendererText;	
	pack_start(*cell_renderer);
	add_attribute(*cell_renderer, "text", 0);
}	

Gtk::ComboBoxText::ComboBoxText(GtkComboBoxText *combo_box, bool owns_reference)
: ComboBox((GtkComboBox*)combo_box, owns_reference)
{
}

Gtk::ComboBoxText::~ComboBoxText()
{
}

String 
Gtk::ComboBoxText::get_active_text() const
{
	char *text = gtk_combo_box_get_active_text(gtk_combo_box());
	String s(text);
	g_free(text);
	return s;
}

void 
Gtk::ComboBoxText::append(const String& text)
{
	append(text.c_str());
}

void 
Gtk::ComboBoxText::prepend(const String& text)
{
	prepend(text.c_str());
}

void 
Gtk::ComboBoxText::insert(int position, const String& text)
{
	insert(position, text.c_str());
}

void
Gtk::ComboBoxText::clear()
{
	Gtk::ListStore *store = dynamic_cast<Gtk::ListStore*>(get_model());
	if (store)
	{
		store->clear();
	}
}
