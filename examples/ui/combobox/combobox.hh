#include <xfc/main.hh>
#include <xfc/gtk/comboboxentry.hh>
#include <xfc/gtk/liststore.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

/*  ComboBox
 */

class ComboBox : public Gtk::ComboBox
{
public:
	ComboBox();
};

/*  ComboBoxGrid
 */

class ComboBoxGrid : public Gtk::ComboBox
{
public:
	ComboBoxGrid();
};

/*  ComboBoxEntry
 */

class ComboBoxEntry : public Gtk::ComboBoxEntryText
{
public:
	ComboBoxEntry();
};

/*  Window
 */

class Window : public Gtk::Window
{
public:
	Window();
	virtual ~Window();
};

