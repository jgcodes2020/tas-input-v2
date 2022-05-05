#include "ButtonFrame.hpp"
#include <gtkmm.h>
#include <array>
#include "gtkmm/label.h"
#include "gtkmm/togglebutton.h"

namespace {
  template <class A, class B>
  struct raw_pair {
    A a;
    B b;
  };

  const std::array<Glib::ustring, 14> BUTTON_LABELS = {
    "⮞", "⮜", "⮟", "⮝", "R", "L", "⮞",
    "⮜", "⮟", "⮝", "S",   "Z", "B", "A"};
}  // namespace

namespace tasdi2 {
  ButtonFrame::ButtonFrame() : Gtk::Frame("Buttons"), grid() {
    
    // Setup grid
    {
      // Triggers
      buttons[BTN_L] = Gtk::ToggleButton("L");
      buttons[BTN_L].set_margin_bottom(20);
      grid.attach(buttons[BTN_L], 0, 0, 3, 1);
      buttons[BTN_Z] = Gtk::ToggleButton("Z");
      buttons[BTN_Z].set_margin_bottom(20);
      grid.attach(buttons[BTN_Z], 3, 0, 3, 1);
      buttons[BTN_R] = Gtk::ToggleButton("R");
      buttons[BTN_R].set_margin_bottom(20);
      grid.attach(buttons[BTN_R], 6, 0, 3, 1);
      
      // D-Pad
      buttons[BTN_DU] = Gtk::ToggleButton("⮝");
      grid.attach(buttons[BTN_DU], 1, 1);
      buttons[BTN_DD] = Gtk::ToggleButton("⮟");
      grid.attach(buttons[BTN_DD], 1, 3);
      buttons[BTN_DL] = Gtk::ToggleButton("⮜");
      grid.attach(buttons[BTN_DL], 0, 2);
      buttons[BTN_DR] = Gtk::ToggleButton("⮞");
      grid.attach(buttons[BTN_DR], 2, 2);
      lbl_d = Gtk::Label("D");
      grid.attach(lbl_d, 1, 2);
      
      // Start Button
      buttons[BTN_START] = Gtk::ToggleButton("S");
      grid.attach(buttons[BTN_START], 4, 2);
      
      // C Buttons
      buttons[BTN_DU] = Gtk::ToggleButton("⮝");
      grid.attach(buttons[BTN_DU], 7, 1);
      buttons[BTN_DD] = Gtk::ToggleButton("⮟");
      grid.attach(buttons[BTN_DD], 7, 3);
      buttons[BTN_DL] = Gtk::ToggleButton("⮜");
      grid.attach(buttons[BTN_DL], 6, 2);
      buttons[BTN_DR] = Gtk::ToggleButton("⮞");
      grid.attach(buttons[BTN_DR], 8, 2);
      lbl_c = Gtk::Label("C");
      grid.attach(lbl_c, 7, 2);
      
      // A and B
      buttons[BTN_B] = Gtk::ToggleButton("B");
      grid.attach(buttons[BTN_B], 5, 4);
      buttons[BTN_A] = Gtk::ToggleButton("A");
      grid.attach(buttons[BTN_A], 6, 5);
    }
    set_child(grid);
  }
}  // namespace tasdi2