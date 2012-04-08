#ifndef TICTACTOE_HH
#define TICTACTOE_HH

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

namespace Xfc {

namespace Gtk {
class ToggleButton;
}

} // namespace Xfc

/*  Tictactoe
 */

class Tictactoe : public Xfc::Gtk::VBox
{
	Tictactoe(const Tictactoe&);
	Tictactoe& operator=(const Tictactoe&);

	Xfc::Gtk::ToggleButton *buttons[3][3];

	void on_toggle(Xfc::Gtk::ToggleButton *button);

public:
// Constructors
	Tictactoe();
	virtual ~Tictactoe();
	
// Methods
	void clear();

// Signals
	sigc::signal<void> tictactoe_signal;
};

#endif // TICTACTOE_HH

