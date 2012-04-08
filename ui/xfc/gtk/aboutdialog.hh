/*  XFC: Xfce Foundation Classes (User Interface Library)
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
 
/// @file xfc/gtk/aboutdialog.hh
/// @brief A GtkAboutDialog C++ wrapper interface.
///
/// Provides AboutDialog which displays information about an application.

#ifndef XFC_GTK_ABOUT_DIALOG_HH
#define XFC_GTK_ABOUT_DIALOG_HH

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef __GTK_ABOUT_DIALOG_H__
#include <gtk/gtkaboutdialog.h>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

/// @class AboutDialog aboutdialog.hh xfc/gtk/aboutdialog.hh
/// @brief A GtkAboutDialog C++ wrapper class.
///
/// AboutDialog offers a simple way to display information about a program like its
/// logo, name, copyright, website and license. It is also possible to give credits
/// to the authors, documenters, translators and artists who have worked on the 
/// program. An about dialog is typically opened when the user selects the About 
/// option from the Help menu. All parts of the dialog are optional. 
///
/// About dialogs often contain links and email addresses. AboutDialog supports this
/// by letting you to set a callback slot, which is called when the user clicks on
/// a link or email address (see set_email_hook() and set_url_hook(). Email addresses
/// in the authors, documenters and artists properties are recognized by looking for
/// <user\@host>, URLs are recognized by looking for http://url, with url extending to
/// the next space, tab or line break. 

class AboutDialog : public Dialog
{
	friend class G::Object;
	
	AboutDialog(const AboutDialog&);
	AboutDialog& operator=(const AboutDialog&);
	
protected:
/// @name Constructors
/// @{

	explicit AboutDialog(GtkAboutDialog *about, bool owns_reference = false);
	///< Construct a new AboutDialog from an existing GtkAboutDialog.
	///< @param about A pointer to a GtkAboutDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>about</EM> can be a newly created GtkAboutDialog or an existing
	///< GtkAboutDialog. (see G::Object::Object).
	
/// @}
public:
	typedef GtkAboutDialog CObjectType;
	
	typedef sigc::slot<void, AboutDialog&, const String&> ActivateLinkSlot;
	///< Signature of the callback slot to be called when a URL or email link is activated.
	///< <B>Example:</B> Method signature for ActivateLinkSlot.
	///< @code
	///< void method(AboutDialog& about, const String& link);
	///< // about: the AboutDialog in which the link was activated.
	///< // link: the URL or email address to which the activated link points.
	///< @endcode

/// @name Constructors
/// @{

	AboutDialog();
	///< Construct an empty about dialog.	
	
	AboutDialog(const char *name, const char *version);
	AboutDialog(const String& name, const String& version);
	///< Construct a new about dialog with the specified <EM>name</EM> and <EM>version</EM>.	
	///< @param name The program name.
	///< @param version The version string.
	///<	
	///< If <EM>name</EM> is not set, it defaults to g_get_application_name().
	
	AboutDialog(const char *name, const char *version, const char *copyright, Gdk::Pixbuf *logo = 0);
	AboutDialog(const String& name, const String& version, const String& copyright, Gdk::Pixbuf *logo = 0);
	///< Construct a new about dialog with the specified <EM>name</EM>, <EM>version</EM> and <EM>logo</EM>.	
	///< @param name The program name.
	///< @param version The version string.
	///< @param copyright The copyright string.
	///< @param logo A Gdk::Pixbuf, or null.
	///<	
	///< If <EM>name</EM> is not set, it defaults to g_get_application_name().

	virtual ~AboutDialog();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkAboutDialog* gtk_about_dialog() const;
	///< Get a pointer to the GtkAboutDialog structure.

	operator GtkAboutDialog* () const;
	///< Conversion operator; safely converts an AboutDialog to a GtkAboutDialog pointer.

	String get_name() const;
	///< Gets the program name displayed in the about dialog.
	///< @return The program name.

	String get_version() const;
	///< Gets the version string.
	///< @return The version string.
	
	String get_copyright() const;
	///< Gets the copyright string.
	///< @return The copyright string.
	
	String get_comments() const;
	///< Gets the comments string.
	///< @return The comments string.

	String get_license() const;
	///< Gets the license information.
	///< @return The license information.

	String get_website() const;
	///< Gets the website URL.
	///< @return The website URL. 
	
	String get_website_label() const;
	///< Get the label used for the website link.
	///< @return The label used for the website link.
	
	std::vector<String> get_authors() const;
	///< Gets the strings which are displayed in the authors tab of the secondary credits dialog.
	///< @return A vector of String containing the authors.
	
	std::vector<String> get_documenters() const;
	///< Gets the strings which are displayed in the documenters tab of the secondary credits dialog.
	///< @return A vector of String containing the documenters.
	
	std::vector<String> get_artists() const;
	///< Gets the strings which are displayed in the artists tab of the secondary credits dialog.
	///< @return A vector of String containing the artists.
	
	String get_translator_credits() const;
	///< Gets the translator credits string which is displayed in the translators tab
	///< of the secondary credits dialog.
	///< @return The translator credits string.
	
	Gdk::Pixbuf* get_logo() const;
	///< Gets the pixbuf displayed as the logo in the about dialog.
	///< @return The pixbuf displayed as the logo.
	
	String get_logo_icon_name() const;
	///< Gets the icon name displayed as the logo in the about dialog.
	///< @return The icon name displayed as the logo.
	 
/// @}
/// @name Methods
/// @{

	void set_name(const char *name);
	void set_name(const String& name);
	///< Sets the name to display in the about dialog. 
	///< @param name The program name.
	///<	
	///< If this is not set, the name defaults to g_get_application_name().
	
	void set_version(const char *version);
	void set_version(const String& version);
	///< Sets the version string to display in the about dialog.
	///< @param version The version string.
	
	void set_copyright(const char *copyright);
	void set_copyright(const String& copyright);
	///< Sets the copyright string to display in the about dialog. 
	///< @param copyright The copyright text.
	///<	
	///< This should be a short string of one or two lines.
	
	void set_comments(const char *comments);
	void set_comments(const String& comments);
	///< Sets the comments string to display in the about dialog. 
	///< @param comments The comments text.
	///<	
	///< This should be a short string of one or two lines.

	void set_license(const char *license);
	void set_license(const String& license);
	///< Sets the license information to be displayed in the secondary license dialog.
	///< @param license The license information, or null.
	///< 
	///< If license is null, the license button is hidden.

	void set_website(const char *website);
	void set_website(const String& website);
	///< Sets the URL to use for the website link.
	///< @param website A URL string starting with "http://".
	
	void set_website_label(const char *website_label);
	void set_website_label(const String& website_label);
	///< Sets the label to be used for the website link.
	///< @param website_label The label used for the website link.
	///< 	 
	///< The default label is the website URL.

	void set_authors(const std::vector<String>& authors);
	///< Sets the strings which are displayed in the authors tab of the secondary credits dialog.
	///< @param authors A vector of String containing the authors.
	
	void set_documenters(const std::vector<String>& documenters);
	///< Sets the strings which are displayed in the documenters tab of the secondary credits dialog.
	///< @param documenters A vector of String containing the documenters.

	void set_artists(const std::vector<String>& artists);
	///< Sets the strings which are displayed in the artists tab of the secondary credits dialog.
	///< @param artists A vector of String containing the artists.

	void set_translator_credits(const char *translator_credits);
	void set_translator_credits(const String& translator_credits);
	///< Sets the translator credits string which is displayed in the translators tab
	///< of the secondary credits dialog.
	///< @param translator_credits The translator credits string.
	///<
	///< The intended use for this string is to display the translator of the language
	///< which is currently used in the user interface. Using gettext(), a simple way 
	///< to achieve that is to mark the string for translation:
	///<
	///< @code
	///< dialog->set_translator_credits(_("translator-credits"));
	///< @endcode
	///<
	///< It is a good idea to use the customary msgid "translator-credits" for this purpose,
	///< since translators will already know the purpose of that msgid, and since AboutDialog
	///< will detect if "translator-credits" is untranslated and hide the tab.
		
	void set_logo(Gdk::Pixbuf *logo);
	///< Sets the pixbuf to be displayed as the logo in the about dialog.
	///< @param logo A Gdk::Pixbuf, or null.
	///<	 
	///< If logo is null, the default window icon set with Gtk::Window::set_default_icon() will be used.

	void set_logo_icon_name(const char *icon_name);
	void set_logo_icon_name(const String& icon_name);
	///< Sets the icon name to be displayed as the logo in the about dialog.
	///< @param icon_name The icon name to display as the logo.
	 
/// @}
/// @name Methods
/// @{

	static void set_email_hook(const ActivateLinkSlot& slot);
	///< Installs a global callback slot to be called whenever the user 
	///< activates an email link in an about dialog.
	///< param slot The slot to call when an email link is activated. 

	static void set_url_hook(const ActivateLinkSlot& slot);
	///< Installs a global callback slot to be called whenever the user
	///< activates a URL link in an about dialog.
	///< @param slot The slot to call when a URL link is activated.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/aboutdialog.inl>

#endif // XFC_GTK_ABOUT_DIALOG_HH

