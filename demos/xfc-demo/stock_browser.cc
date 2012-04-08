/* Stock Item and Icon Browser
 *
 * This source code for this demo doesn't demonstrate anything
 * particularly useful in applications. The purpose of the "demo" is
 * just to provide a handy place to browse the available stock icons
 * and stock items.
 */

#include "demowindow.hh"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/alignment.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/cellrendererpixbuf.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/iconfactory.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/scrolledwindow.hh>
#include <xfc/gtk/stock.hh>
#include <xfc/gtk/treeview.hh>
#include <xfc/glib/private/objectclass.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <algorithm>

using namespace Xfc;

struct StockItemInfo : public Xfc::Object
{
	Gtk::StockId id;
	Gtk::StockItem item;
	Pointer<Gdk::Pixbuf> small_icon;
	String macro;
	String accel_str;

	StockItemInfo();
	StockItemInfo(const Gtk::StockId& stock_id);
	~StockItemInfo();

	static GType get_type();
	static StockItemInfo* copy(StockItemInfo *src);
	static void free(StockItemInfo *src);

	String id_to_macro();
};

class StockItemList : public Gtk::ListStore
{
public:
	StockItemList(Gtk::Window& window);
	~StockItemList();
};

class StockBrowser : public Gtk::Window
{
	Gtk::Label *type_label;
	Gtk::Label *macro_label;
	Gtk::Label *id_label;
	Gtk::Label *label_accel_label;
	Gtk::Image *icon_image;

	Gtk::TreeView *treeview;

	Gtk::TreeViewColumn::CellDataSlot cell_pixbuf_slot;
	Gtk::TreeViewColumn::CellDataSlot cell_text_slot;
	Gtk::TreeViewColumn::CellDataSlot cell_label_slot;
	Gtk::TreeViewColumn::CellDataSlot cell_accel_slot;
	Gtk::TreeViewColumn::CellDataSlot cell_id_slot;

	void macro_set_text(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void label_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void accel_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);
	void id_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter);

	void on_selection_changed();

public:
	StockBrowser();
	~StockBrowser();
};
//!

// StockItemInfo

StockItemInfo::StockItemInfo()
{
}

StockItemInfo::StockItemInfo(const Gtk::StockId& stock_id)
{
	id = stock_id;
	macro = id_to_macro();
}

StockItemInfo::~StockItemInfo()
{
}

GType
StockItemInfo::get_type()
{
	static GType type = 0;

	if (!type)
		type = g_boxed_type_register_static("XFC_StockItemInfo", (GBoxedCopyFunc)&StockItemInfo::copy,
	                                                                 (GBoxedFreeFunc)&StockItemInfo::free);
	return type;
}

StockItemInfo*
StockItemInfo::copy(StockItemInfo *src)
{
	src->ref();
	return src;
}

void
StockItemInfo::free(StockItemInfo *info)
{
	info->unref();
}

String
StockItemInfo::id_to_macro()
{
	// gtk-foo-bar -> GTK_STOCK_FOO_BAR

	int start_pos = 0;
	if (id.str().compare(0, 4, "gtk-") == 0)
	{
		macro.assign("GTK_STOCK_");
		start_pos = 4;
	}
	macro.append(id.str().upper(start_pos));

	size_t pos = macro.find('-', 0);
	while (pos != String::npos)
	{
		macro.replace(pos, 1, 1, '_');
		pos = macro.find('-', pos);
	}
	return macro;
}

// StockItemList

StockItemList::StockItemList(Gtk::Window& window)
: Gtk::ListStore(2, StockItemInfo::get_type(), G_TYPE_STRING)
{
	std::vector<Gtk::StockId> stock_items = Gtk::Stock::list_ids();
	int n_stock_items = stock_items.size();

	for (int i = 0; i < n_stock_items; i++)
	{
		StockItemInfo *info = new StockItemInfo(stock_items[i]);
				
		Gtk::StockItem item;
		if (Gtk::Stock::lookup(info->id, item))
			info->item = item;
		
		// Only show icons for stock IDs that have default icons
		Pointer<Gtk::IconSet> icon_set = Gtk::IconFactory::lookup_default(info->id);
		if (icon_set)
		{
			std::vector<Gtk::IconSize> sizes;
			icon_set->get_sizes(sizes);
			Gtk::IconSize size = sizes[0];
			int n_sizes = sizes.size();

			int j = 0;
			while (j < n_sizes)
			{
				if (sizes[j] == Gtk::ICON_SIZE_MENU)
				{
					size = Gtk::ICON_SIZE_MENU;
					break;
				}
				j++;
			}

			info->small_icon = window.render_icon(info->id, size);

			if (size != Gtk::ICON_SIZE_MENU)
			{
			// Make the result the proper size for our thumbnail
				int w, h;
				Gtk::icon_size_lookup(Gtk::ICON_SIZE_MENU, &w, &h);
				Pointer<Gdk::Pixbuf> scaled = info->small_icon->scale_simple(w, h, Gdk::INTERP_BILINEAR);
				info->small_icon = scaled;
			}
		
		}


		if (info->item.keyval())
			info->accel_str = Gtk::accelerator_name(info->item.accel_key());

		Gtk::TreeIter iter = append();
		set_pointer(iter, 0, info);
		set_value(iter, 1, info->id.str());
		info->unref();
	}
}

StockItemList::~StockItemList()
{
}

// StockBrowser

StockBrowser::StockBrowser()
{
	set_title("Stock Icons and Items");
	set_default_size(-1, 500);
	set_border_width(8);

	Gtk::HBox *hbox = new Gtk::HBox(false, 8);
	add(*hbox);

	Gtk::ScrolledWindow *sw = new Gtk::ScrolledWindow;
	sw->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	hbox->pack_start(*sw, false, false);

	Pointer<StockItemList> model = new StockItemList(*this);

	treeview = new Gtk::TreeView(*model);
	sw->add(*treeview);
      
	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn;
	column->set_title("Macro");

	Gtk::CellRenderer *cell_renderer = new Gtk::CellRendererPixbuf;
	column->pack_start(*cell_renderer, false);
	column->add_attribute(*cell_renderer, "stock_id", 1);

	cell_renderer = new Gtk::CellRendererText;
	column->pack_start(*cell_renderer);
	cell_text_slot = sigc::mem_fun(this, &StockBrowser::macro_set_text);
	column->set_cell_data_func(*cell_renderer, cell_text_slot);
	treeview->append_column(*column);

	cell_renderer = new Gtk::CellRendererText;
	cell_label_slot = sigc::mem_fun(this, &StockBrowser::label_set);
	treeview->append_column("Label", *cell_renderer, cell_label_slot);

	cell_renderer = new Gtk::CellRendererText;
	cell_accel_slot = sigc::mem_fun(this, &StockBrowser::accel_set);
	treeview->append_column("Accel", *cell_renderer, cell_accel_slot);

	cell_renderer = new Gtk::CellRendererText;
 	cell_id_slot = sigc::mem_fun(this, &StockBrowser::id_set);
	treeview->append_column("ID", *cell_renderer, cell_id_slot);
     
	Gtk::Alignment *align = new Gtk::Alignment(0.5, 0.0, 0.0, 0.0);
	hbox->pack_end(*align, false, false);

	Gtk::Frame *frame = new Gtk::Frame("Selected Item");
	align->add(*frame);

	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(4);
	frame->add(*vbox);

	type_label = new Gtk::Label;
	vbox->pack_start(*type_label, false, false);

	icon_image = new Gtk::Image; // empty image
	vbox->pack_start(*icon_image, false, false);

	label_accel_label = new Gtk::Label;
	vbox->pack_start(*label_accel_label, false, false);

	macro_label = new Gtk::Label;
	vbox->pack_start(*macro_label, false, false);

	id_label = new Gtk::Label;
	vbox->pack_start(*id_label, false, false);

	Gtk::TreeSelection *selection = treeview->get_selection();
	selection->set_mode(Gtk::SELECTION_SINGLE);
	selection->signal_changed().connect(sigc::mem_fun(this, &StockBrowser::on_selection_changed));
	show_all();
}

StockBrowser::~StockBrowser()
{
}

void
StockBrowser::macro_set_text(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	StockItemInfo *info = 0;
	model.get_pointer(iter, 0, info);
	dynamic_cast<Gtk::CellRendererText&>(cell).property_text().set(info->macro);
	info->unref();
}

void
StockBrowser::label_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	StockItemInfo *info = 0;
	model.get_pointer(iter, 0, info);
	dynamic_cast<Gtk::CellRendererText&>(cell).property_text().set(info->item.label());
	info->unref();
}

void
StockBrowser::accel_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	StockItemInfo *info = 0;
	model.get_pointer(iter, 0, info);
	dynamic_cast<Gtk::CellRendererText&>(cell).property_text().set(info->accel_str);
	info->unref();
}

void
StockBrowser::id_set(Gtk::CellRenderer& cell, const Gtk::TreeModel& model, const Gtk::TreeIter& iter)
{
	StockItemInfo *info = 0;
	model.get_pointer(iter, 0, info);
	dynamic_cast<Gtk::CellRendererText&>(cell).property_text().set(info->id.str());
	info->unref();
}

namespace {

Gtk::IconSize
get_largest_size (const Gtk::StockId& stock_id)
{
	// Finds the largest size at which the given image stock id is available.
	// This would not be useful for a normal application.

	Pointer<Gtk::IconSet> set = Gtk::IconFactory::lookup_default(stock_id);
	std::vector<Gtk::IconSize> sizes;
	set->get_sizes(sizes);

	int n_sizes = sizes.size();
	Gtk::IconSize best_size = Gtk::ICON_SIZE_INVALID;
	int best_pixels = 0;

	for (int i = 0; i < n_sizes; i++)
	{
		int width, height;
      
		Gtk::icon_size_lookup(sizes[i], &width, &height);

		if (width * height > best_pixels)
		{
			best_size = sizes[i];
			best_pixels = width * height;
		}
	}
	return best_size;
}

} // namespace

void
StockBrowser::on_selection_changed()
{
	Gtk::TreeIter iter;
	Gtk::TreeModel *model = 0;
	Gtk::TreeSelection *selection = treeview->get_selection();

	if (selection->get_selected(&iter, &model))
	{
		StockItemInfo *info = 0;
		static_cast<StockItemList*>(model)->get_pointer(iter, 0, info);

		if (info->small_icon && !info->item.label())
			type_label->set_text("Icon and Item");
		else if (info->small_icon)
			type_label->set_text("Icon Only");
 		else if (!info->item.label())
			type_label->set_text("Item Only");
		else
			type_label->set_text("???????");

		macro_label->set_text(info->macro);
		id_label->set_text(info->id);

		if (info->item.label())
		{
			String str = String::format("%s %s", info->item.label(), info->accel_str.c_str());
			label_accel_label->set_text_with_mnemonic(str);
		}
		else
			label_accel_label->set_text("");

		if (info->small_icon)
			icon_image->set(info->id.c_str(), get_largest_size(info->id));
		else
			icon_image->set((Gdk::Pixbuf*)0);
	}
	else
	{
		type_label->set_text("No selected item");
		macro_label->set_text("");
		id_label->set_text ("");
		label_accel_label->set_text("");
		icon_image->set((Gdk::Pixbuf*)0);
	}
}

Gtk::Window*
do_stock_browser(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new StockBrowser;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}
