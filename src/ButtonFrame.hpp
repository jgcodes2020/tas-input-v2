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
    enum Indices : size_t {
      BTN_CR = 0,
      BTN_CL = 1,
      BTN_CD = 2,
      BTN_CU = 3,
      
      BTN_R = 4,
      BTN_L = 5,
      
      BTN_DR = 6,
      BTN_DL = 7,
      BTN_DD = 8,
      BTN_DU = 9,
      
      BTN_START = 10,
      BTN_Z = 11,
      BTN_B = 12,
      BTN_A = 13,
    };
  
    Gtk::Grid grid;
    std::array<Gtk::Label, 1> spacers;
    
    std::array<Gtk::ToggleButton, 14> buttons;
    Gtk::Label lbl_d;
    Gtk::Label lbl_c;
  };
}
#endif