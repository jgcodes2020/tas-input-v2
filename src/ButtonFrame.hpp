#ifndef _BUTTON_FRAME_HPP_
#define _BUTTON_FRAME_HPP_
#include <gtkmm.h>
namespace tasdi2 {
  class ButtonFrame : public Gtk::Frame {
  public:
    ButtonFrame();
  protected:
    Gtk::ToggleButton tbtn;
  };
}
#endif