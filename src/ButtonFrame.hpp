#ifndef _BUTTON_FRAME_HPP_
#define _BUTTON_FRAME_HPP_
#include <gtkmm.h>
#include <array>
#include <vector>

namespace tasdi2 {
  
  class ButtonFrame : public Gtk::Frame {
  public:
    ButtonFrame();
    
    uint16_t get_button_mask();
  protected:
    Glib::RefPtr<Gtk::Builder> builder;
  };
}
#endif