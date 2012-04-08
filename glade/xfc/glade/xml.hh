/*  XFC: Xfce Foundation Classes (Glade Library)
 *  Copyright (C) 2005 The XFC Development Team.
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

/// @file xfc/glade/xml.hh 
/// @brief A GladeXML C++ wrapper interface.
///
/// Provides Xml, an object that allows dynamic loading of user interfaces from XML descriptions.

#ifndef XFC_GLADE_XML_HH
#define XFC_GLADE_XML_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef GLADE_XML_H
#include <glade/glade-xml.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {
class Widget;
}

namespace Glade {

/// @class Xml xml.hh xfc/glade/xml.hh
/// @brief A GladeXML C++ wrapper class.
///
/// Glade::Xml represents an instantiation of an XML interface description. When one of
/// these objects is created, the XML file is read, and the interface is created. The 
/// Xml object then provides an interface for accessing the widgets in the interface by
/// the names assigned to them inside the XML description. The Xml object can also be 
///< used to connect signals handlers to the named signals in the description.
///<
///< <B>Example:</B> Instantiating a main application window from an XML description. 
///<
///< @code
///< //Declare derived window class.
///< 
///< class MyWindow : public Gtk::Window
///< {
///< 	Gtk::Button *ok_button;
///< 	
///< protected:
///< 	void on_ok_clicked();
///< 	
///< public: 
///< 	MyWindow(CObjectType *object, const Glade::Xml& xml);
///< };
///< 
///< // Define constructor and load any widgets built by the Glade::Xml object.
///< 
///< MyWindow::MyWindow(CObjectType *object, const Glade::Xml& xml)
///< : Gtk::Window(object)
///< {
///< 	if (xml.get_widget("ok_button", ok_button))
///< 	{
///< 		ok_button->signal_clicked().connect(sigc::mem_fun((this, &MyWindow::on_ok_clicked));
///< 	}
///< }
///< 
///< // Define on_ok_clicked handler, just calls dispose the destroy the window.
///< 
///< void 
///< MyWindow::on_ok_clicked()
///< {
///< 	dispose();
///< }
///< 
///< // Create the Glade::Xml object in main() and instantiate the main application window.
///< 
///< int main(int argc, char *argv[])
///< {
///< 	using namespace Main;
///< 
///< 	init(&argc, &argv);
///< 	
///< 	Pointer<Glade::Xml> xml = Glade::Xml::create("mywindow.glade");
///< 	if (!xml)
///< 		return 1;
///< 	
///< 	MyWindow *window;
///< 	if (xml->get_widget_derived("MyWindow", window))
///< 	{
///< 		window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
///< 		window->show();
///< 		run();
///< 	}
///< 	return 0;
///< }
///< @endcode

class Xml : public G::Object
{
	friend class G::Object;

	Xml(const Xml&);
	Xml& operator=(const Xml&);

protected:
/// @name Constructors
/// @{

	Xml();
	///< Construct an empty Xml object. To create the interface from
	///< an XML interface description call construct(). 	
	
	explicit Xml(GladeXML *self, bool owns_reference = true);
	///< Construct a new Xml object from an existing GladeXML object.
	///< @param self A pointer to a GladeXML object.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>self</EM> argument can be a newly created GladeXML object or an
	///< existing GladeXML object (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	bool construct(const char *filename, const char *root, const char *domain);
	bool construct(const std::string& filename, const String& root, const String& domain);
	///< This method is used by derived classes to help construct the Xml object.
	///< @param filename The XML filename. 
	///< @param root The root widget node, or null for none. 
	///< @param domain The translation domain, or null for the default. 
	///< @return <EM>true</EM> if the construction succeeded, <EM>false</EM> on failure.					  
					  
/// @}

public:
/// @name Constructors
/// @{

	virtual ~Xml();
	///< Destructor.
	
/// @}
/// @name Constructors
/// @{

	static Pointer<Xml> create(const char *filename, const char *root = 0, const char *domain = 0);
	static Pointer<Xml> create(const std::string& filename, const String& root = 0, const String& domain = 0);
	///< Creates a new Glade::Xml object (and the corresponding widgets) from
	///< the XML file <EM>filename</EM>. 
	///< @param filename The XML filename. 
	///< @param root The widget node in <EM>filename</EM> to start building from, or null. 
	///< @param domain The translation domain for the XML file, or null for the default. 
	///< @return A smart pointer to the newly created Xml object, or null on failure.					  
	///<	
	///< Optionally it will only build the interface from the widget node <EM>root</EM>
	///< (if it is not null). This feature is useful if you only want to build say a 
	///< toolbar or menu from the XML file, but not the window it is embedded in. Note
	///< also that the XML parse tree is cached to speed up creating another Glade::Xml
	///< object for the same file.
	
	static Pointer<Xml> create(const char *buffer, int size, const char *root = 0, const char *domain = 0);
	static Pointer<Xml> create(const char *buffer, int size, const String& root = 0, const String& domain = 0);
	///< Creates a new Glade::XML object (and the corresponding widgets) from the buffer <EM>buffer</EM>.
	///< @param buffer The memory buffer containing the XML document. 
	///< @param size The size of the buffer. 
	///< @param root The widget node in <EM>filename</EM> to start building from, or null. 
	///< @param domain The translation domain for the XML buffer, or null for the default. 
	///< @return A smart pointer to the newly created Xml object, or null on failure.					  
	///<	 
	///< Optionally it will only build the interface from the widget node root (if it is not null). 
	///< This feature is useful if you only want to build say a toolbar or menu from the XML document,
	///< but not the window it is embedded in.

/// @}
/// @name Accessors
/// @{

	GladeXML* glade_xml() const;
	///< Get a pointer to the GladeXML structure.

	operator GladeXML* () const;
	///< Conversion operator; safely converts a Xml object to a GladeXML pointer.

	std::string get_filename() const;
	///< Gets the name of the XML file that was used to create the Glade::Xml object.
	///< @return The XML filename, or an empty string if an error occurs.	
	
	Gtk::Widget* get_widget(const char *name) const;
	Gtk::Widget* get_widget(const String& name) const;
	///< Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
	///< @param name The name of the widget in the XML description. 
	///< @return A pointer to the widget matching <EM>name</EM>, or null if none exists.
	
	template<typename WidgetType>
	bool get_widget(const String& name, WidgetType *&widget) const;
	///< Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
	///< @param name The name of the widget in the XML description. 
	///< @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.
	///< 
	///< To use this method <EM>WidgetType</EM> must be one of the standard XFC widgets. 
	///<
	///< <B>Example:</B> Connecting a "clicked" signal handler to a Gtk::Button.
	///< @code
	///< Gtk::Button *button;
	///< if (xml->get_widget("my_button", button))
	///< {
	///<     button->signal_clicked().connect(sigc::mem_fun(this, &MyWindow::on_my_button_clicked));
	///< }
	///< @endcode    

	template<typename DerivedType>
	bool get_widget_derived(const String& name, DerivedType *&widget) const;
	///< Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
	///< @param name The name of the widget in the XML description. 
	///< @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.
	///< 
	///< To use this method <EM>DerivedType</EM> must be a user-defined widget class
	///< that derives from one of the standard XFC widgets. The derived widget class
	///< must declare it's constructor with the following signature:
	///<
	///< @code
	///< DerivedType(CObjectType *object, Glade::Xml& xml_object)
	///< @endcode
	///<
	///< <B>Example:</B> Instantiating a main application window from an XML description.
	///< @code
	///< MyWindow *window;
	///< if (xml->get_widget_derived("MyWindow", window))
	///< {
	///<     window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	///<     window->show();
	///<     run();
	///< }
	///< @endcode    

	bool get_widget_prefix(const char *prefix, std::vector<Gtk::Widget*>& widgets) const;
	bool get_widget_prefix(const String& prefix, std::vector<Gtk::Widget*>& widgets) const;
	///< Fills a vector with a list of pointers to the Gtk::Widget(s) with names that start
	///< with the string <EM>prefix</EM> in the XML interface description. 
	///< @param prefix The starting prefix that is part of the name of a widget(s) in the XML description. 
	///< @param widgets A vector of Gtk::Widget pointers to hold the widgets with names matching <EM>prefix</EM>.
	///< @return <EM>true</EM> if any widgets are found, <EM>false</EM> if no widgets exist.
	///<
	///< You would use this method if you have to do something to all of these widgets after loading.

	std::string relative_file(const char *filename) const;
	std::string relative_file(const std::string& filename) const;
	///< This method resolves a relative pathname, using the directory of the XML file as a base.
	///< @param filename The filename to resolve.
	///< @return The filename.
	///<	  
	///< If the pathname is absolute, then the original filename is returned.

/// @}
/// @name Accessors
/// @{
	
	static String get_widget_name(Gtk::Widget& widget);
	///< Gets the name of a <EM>widget</EM> that was generated by a Glade::XML object.
	///< @param widget The widget to get the name for.
	///< @return The name of the <EM>widget</EM>.

	static Pointer<Xml> get_widget_tree(Gtk::Widget& widget);
	///< Gets the Glade::Xml object that built this widget.
	///< @param widget The widget to get the name for.
	///< @return A smart pointer to the Glade::Xml object that built this widget.

/// @}
};

} // namespace Glade

} // namespace Xfc

#include <xfc/glade/inline/xml.inl>

#endif // XFC_GLADE_XML_HH

