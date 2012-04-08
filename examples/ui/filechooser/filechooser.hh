#include <xfc/main.hh>
#include <xfc/gtk/checkbutton.hh>
#include <xfc/gtk/combobox.hh>
#include <xfc/gtk/filechooserdialog.hh>

using namespace Xfc;

class FileDialog : public Gtk::FileChooserDialog
{
	Gtk::Button *button;
	
protected: 
	void on_ok();
	void on_toggled_show_hidden(Gtk::CheckButton *check_button);
	void on_toggled_select_multiple(Gtk::CheckButton *check_button);
	void on_action_changed(Gtk::ComboBox *combobox);
	
public:
	FileDialog();
	virtual ~FileDialog();
};

