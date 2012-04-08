#include "demowindow.hh"

typedef sigc::slot<Gtk::Window*, Gtk::Widget*> DoSlot;

struct Demo
{
	const char *title;
	const char *filename;
	DoSlot do_slot;
	Demo *children;
};

Gtk::Window* do_appwindow(Gtk::Widget *do_widget);
Gtk::Window* do_button_box(Gtk::Widget *do_widget);
Gtk::Window* do_changedisplay(Gtk::Widget *do_widget);
Gtk::Window* do_clipboard(Gtk::Widget *do_widget);
Gtk::Window* do_colorsel(Gtk::Widget *do_widget);
Gtk::Window* do_dialog(Gtk::Widget *do_widget);
Gtk::Window* do_drawingarea(Gtk::Widget *do_widget);
Gtk::Window* do_editable_cells(Gtk::Widget *do_widget);
Gtk::Window* do_entry_completion(Gtk::Widget *do_widget);
Gtk::Window* do_expander(Gtk::Widget *do_widget);
Gtk::Window* do_hypertext(Gtk::Widget *do_widget);
Gtk::Window* do_iconview(Gtk::Widget *do_widget);
Gtk::Window* do_images(Gtk::Widget *do_widget);
Gtk::Window* do_list_store(Gtk::Widget *do_widget);
Gtk::Window* do_menus(Gtk::Widget *do_widget);
Gtk::Window* do_panes(Gtk::Widget *do_widget);
Gtk::Window* do_pixbufs(Gtk::Widget *do_widget);
Gtk::Window* do_rotated_text(Gtk::Widget *do_widget);
Gtk::Window* do_sizegroup(Gtk::Widget *do_widget);
Gtk::Window* do_stock_browser(Gtk::Widget *do_widget);
Gtk::Window* do_textview(Gtk::Widget *do_widget);
Gtk::Window* do_tree_store(Gtk::Widget *do_widget);
Gtk::Window* do_ui_manager(Gtk::Widget *do_widget);

Demo child0[] = {
  { "Editable Cells", "editable_cells.cc", sigc::ptr_fun(&do_editable_cells), 0 },
  { "List Store", "list_store.cc", sigc::ptr_fun(&do_list_store), 0 },
  { "Tree Store", "tree_store.cc", sigc::ptr_fun(&do_tree_store), 0 },
  { 0, 0, DoSlot(), 0 }
};

Demo child1[] = {
  { "Hypertext", "hypertext.cc", sigc::ptr_fun(&do_hypertext), 0 },
  { "Multiple Views", "textview.cc", sigc::ptr_fun(&do_textview), 0 },
  { NULL } 
};

Demo testgtk_demos[] = {
  { "Application main window", "appwindow.cc", sigc::ptr_fun(&do_appwindow), 0 },
  { "Button Boxes", "button_box.cc", sigc::ptr_fun(&do_button_box), 0 },
  { "Change Display", "changedisplay.cc", sigc::ptr_fun(&do_changedisplay), 0 },
  { "Clipboard", "clipboard.cc", sigc::ptr_fun(&do_clipboard), 0 },
  { "Color Selector", "colorsel.cc", sigc::ptr_fun(&do_colorsel), 0 },
  { "Dialog and Message Boxes", "dialog.cc", sigc::ptr_fun(&do_dialog), 0 },
  { "Drawing Area", "drawingarea.cc", sigc::ptr_fun(&do_drawingarea), 0 },
  { "Entry Completion", "entry_completion.cc", sigc::ptr_fun(&do_entry_completion), 0 }, 
  { "Expander", "expander.cc", sigc::ptr_fun(&do_expander), 0 }, 
  { "Icon View", "iconview.cc", sigc::ptr_fun(&do_iconview), 0 }, 
  { "Images", "images.cc", sigc::ptr_fun(&do_images), 0 },
  { "Menus", "menus.cc", sigc::ptr_fun(&do_menus), 0 },
  { "Paned Widgets", "panes.cc", sigc::ptr_fun(&do_panes), 0 },
  { "Pixbufs", "pixbufs.cc", sigc::ptr_fun(&do_pixbufs), 0 },
  { "Rotated Text", "rotated_text.cc", sigc::ptr_fun(&do_rotated_text), 0 },
  { "Size Groups", "sizegroup.cc", sigc::ptr_fun(&do_sizegroup), 0 },
  { "Stock Item and Icon Browser", "stock_browser.cc", sigc::ptr_fun(&do_stock_browser), 0 },
  { "Text Widget", 0, DoSlot(), child1 },
  { "Tree View", 0, DoSlot(), child0 },
  { "UI Manager", "ui_manager.cc", sigc::ptr_fun(&do_ui_manager), 0 },
  { 0, 0, DoSlot(), 0 }
  };
