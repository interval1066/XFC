#include "combobox.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/iconfactory.hh>
#include <xfc/gtk/stockid.hh>
#include <xfc/gtk/cellrendererpixbuf.hh>
#include <xfc/gtk/cellrenderertext.hh>
#include <xfc/gdk/color.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <iostream>

namespace { // create_color_pixbuf

Pointer<Gdk::Pixbuf> 
create_color_pixbuf(const char *spec)
{
	Gdk::Color color(spec); 
	Pointer<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create(16, 16, false);        
		      
	unsigned char *p, *pixels;
	p = pixels = pixbuf->get_pixels();
	int num = pixbuf->get_width() * pixbuf->get_height();

        for (int i = 0; i < num; i++) 
	{
                p[0] = color.get_red() / 65535 * 255;
                p[1] = color.get_green() / 65535 * 255;
                p[2] = color.get_blue() / 65535 * 255;
                p += 3;
        }
	return pixbuf;
}

} // namespace

ComboBox::ComboBox()
{
	Pointer<Gtk::ListStore> store = new Gtk::ListStore(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);		
	set_model(*store);
		
        Gtk::CellRenderer *renderer = new Gtk::CellRendererPixbuf;
        pack_start(*renderer, false);
        add_attribute(*renderer, "pixbuf", 0);
	renderer = new Gtk::CellRendererText;
	pack_start(*renderer, true);
	add_attribute(*renderer, "text", 1);
	
	Pointer<Gdk::Pixbuf> pixbuf = render_icon(Gtk::StockId::DIALOG_WARNING, Gtk::ICON_SIZE_BUTTON);
	Gtk::TreeIter iter = store->append();  
	store->set_value(iter, 0, pixbuf);       
	store->set_value(iter, 1, "gtk-stock-dialog-warning");       
	
	pixbuf = render_icon(Gtk::StockId::STOP, Gtk::ICON_SIZE_BUTTON);
	iter = store->append();  
	store->set_value(iter, 0, pixbuf);       
	store->set_value(iter, 1, "gtk-stock-stop");       

	pixbuf = render_icon(Gtk::StockId::NEW, Gtk::ICON_SIZE_BUTTON);
	iter = store->append();  
	store->set_value(iter, 0, pixbuf);       
	store->set_value(iter, 1, "gtk-stock-new");       

	pixbuf = render_icon(Gtk::StockId::CLEAR, Gtk::ICON_SIZE_BUTTON);
	iter = store->append();  
	store->set_value(iter, 0, pixbuf);       
	store->set_value(iter, 1, "gtk-stock-clear");       

        set_active( 1);
}

ComboBoxGrid::ComboBoxGrid()
{
        Pointer<Gtk::ListStore> store = new Gtk::ListStore(1, GDK_TYPE_PIXBUF);
	set_model(*store);
	
	Pointer<Gtk::CellRenderer> renderer = new Gtk::CellRendererPixbuf;
        pack_start(*renderer, true);
        add_attribute(*renderer, "pixbuf", 0);
        set_wrap_width(3);

        // First row
        Gtk::TreeIter iter = store->append();
	Pointer<Gdk::Pixbuf> pixbuf = create_color_pixbuf("red");        
	store->set_value(iter, 0, pixbuf);

        iter = store->append();
 	pixbuf = create_color_pixbuf("green");        
	store->set_value(iter, 0, pixbuf);

        iter = store->append();
 	pixbuf = create_color_pixbuf("blue");        
	store->set_value(iter, 0, pixbuf);

        // Second row 
        iter = store->append();
 	pixbuf = create_color_pixbuf("yellow");        
	store->set_value(iter, 0, pixbuf);
        
        iter = store->append();
 	pixbuf = create_color_pixbuf("black");        
	store->set_value(iter, 0, pixbuf);

        iter = store->append();
 	pixbuf = create_color_pixbuf("white");        
	store->set_value(iter, 0, pixbuf);
		
        // Third row
        iter = store->append();
 	pixbuf = create_color_pixbuf("gray");        
	store->set_value(iter, 0, pixbuf);
        
        iter = store->append();
 	pixbuf = create_color_pixbuf("snow");        
	store->set_value(iter, 0, pixbuf);
        
        iter = store->append();
 	pixbuf = create_color_pixbuf("magenta");        
	store->set_value(iter, 0, pixbuf);
        
        set_active(0);
}

ComboBoxEntry::ComboBoxEntry()
{
 	set_text_column(0);
	for (int i = 0; i < 6; i++)
	{
		String s = String::format("Item Number %i", i);
		append(s);       
	}
	set_active(3);
}

Window::Window()
{
	set_title("ComboBox Types");	
	set_border_width(5);
	Gtk::VBox *mainbox = new Gtk::VBox(false, 2);
        add(*mainbox);

        //  Gtk::ComboBox
        Gtk::Frame *frame = new Gtk::Frame("Gtk::ComboBox");
        mainbox->pack_start(*frame, false, false);
 
        Gtk::VBox *childbox = new Gtk::VBox;
        childbox->set_border_width(5);
        frame->add(*childbox);

	ComboBox *combobox = new ComboBox;
        childbox->add(*combobox);

        // Gtk::ComboBox (grid mode)
        frame = new Gtk::Frame("Gtk::ComboBox (grid mode)");
        mainbox->pack_start(*frame, false, false);
        
        childbox = new Gtk::VBox;
        childbox->set_border_width(5);
        frame->add(*childbox);

        ComboBoxGrid *comboboxgrid = new ComboBoxGrid;
        childbox->pack_start(*comboboxgrid, false, false);

        // Gtk::ComboBoxEntry
        frame = new Gtk::Frame("Gtk::ComboBoxEntry");
        mainbox->pack_start(*frame, false, false);
 
        childbox = new Gtk::VBox;
        childbox->set_border_width(5);
        frame->add(*childbox);
	
        ComboBoxEntry *comboboxtext = new ComboBoxEntry;
	childbox->add(*comboboxtext);
	
	mainbox->show_all();
}

Window::~Window()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

