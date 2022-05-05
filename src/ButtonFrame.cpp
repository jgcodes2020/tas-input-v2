#include "ButtonFrame.hpp"
#include "gtkmm/frame.h"

namespace tasdi2 {
  ButtonFrame::ButtonFrame() :
    Gtk::Frame("Buttons"),
    tbtn("TESTING") {
    
    tbtn.set_margin(10);
    set_child(tbtn);
  }
}