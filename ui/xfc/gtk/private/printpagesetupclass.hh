#ifndef XFC_GTK_PAGE_SETUP_CLASS_HH
#define XFC_GTK_PAGE_SETUP_CLASS_HH

#include <xfc/gtk/private/objectclass.hh>

class PageSetupClass {
public:
        static void init(GtkWidgetClass *g_class);

        static GtkWidgetClass* get_parent_class(void *instance);

        static GType get_type();

        static void* create();
};

#endif
