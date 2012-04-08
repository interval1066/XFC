#ifndef XFC_DE_ABOUT_HH
#define XFC_DE_ABOUT_HH

namespace Xfc {

namespace De {

class AboutInfo {
public:
    AboutInfo( const String &program,
               const String &version,
               const String &description,
               const String &copyright,
               const String &license);
}

class AboutDialog : public Gtk::Dialog {
public:

/// @name Constructors
/// @{

    AboutDialog( AboutInfo &info, Gdk::Pixbuf * );

/// @}
/// @name Methods
/// @{
    
    void set_homepage(const String *homepage);
    void add_credit(const String &name,
                    const String &mail,
                    const String &task);

/// @}            
/// @name Property Prototypes
/// @{

    // "copyright"                gchar*                : Read / Write
    typedef G::Property<String> CopyrightPropertyType;
    typedef G::PropertyProxy<G::Object, CopyrightPropertyType> CopyrightPropertyProxy;
    static const CopyrightPropertyType copyright_property;
  
    // "description"              gchar*                : Read / Write
    typedef G::Property<String> DescriptionPropertyType;
    typedef G::PropertyProxy<G::Object, DescriptionPropertyType> DescriptionPropertyProxy;
    static const DescriptionPropertyType description_property;

    // "homepage"                 gchar*                : Read / Write
    typedef G::Property<String> HomepagePropertyType;
    typedef G::PropertyProxy<G::Object, HomepagePropertyType> HomepagePropertyProxy;
    static const HomepagePropertyType homepage_property;

    // "icon"                     GdkPixbuf*            : Read / Write
    typedef G::Property<Gtk::Pixbuf> IconPropertyType;
    typedef G::PropertyProxy<G::Object, IconPropertyType> IconPropertyProxy;
    static const IconPropertyType icon_property;

    // "license"                  gchar*                : Read / Write
    typedef G::Property<String> LicensPropertyType;
    typedef G::PropertyProxy<G::Object, LicensPropertyType> LicensPropertyProxy;
    static const LicensPropertyType licens_property;

    // "program"                  gchar*                : Read / Write
    typedef G::Property<String> ProgramPropertyType;
    typedef G::PropertyProxy<G::Object, ProgramPropertyType> ProgramPropertyProxy;
    static const ProgramPropertyType program_property;

    // "version"                  gchar*                : Read / Write
    typedef G::Property<String> VersionPropertyType;
    typedef G::PropertyProxy<G::Object, VersionPropertyType> VersionPropertyProxy;
    static const VersionPropertyType version_property;


/// @}
/// @name Property Proxies
/// @{

    const CopyrightPropertyProxy property_copyright();

    const DescriptionPropertyProxy property_description();

    const HomepagePropertyProxy property_homepage();

    const IconPropertyProxy property_icon();

    const LicensPropertyProxy property_licens();

    const ProgramPropertyProxy property_program();

    const VersionPropertyProxy property_version();

/// @}
};

}
}

#endif
