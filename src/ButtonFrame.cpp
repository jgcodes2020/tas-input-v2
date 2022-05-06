#include "ButtonFrame.hpp"
#include <gtkmm.h>
#include <array>

#include <resources/css/button-frame.css.rsrc.hpp>

namespace tasdi2 {
  ButtonFrame::ButtonFrame() : Gtk::Frame("Buttons"), grid() {
    // Add style provider
    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);

    auto style_ctx = this->get_style_context();
    auto display = this->get_display();
    style_ctx->add_provider_for_display(display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    {
      // Triggers
      buttons[BTN_L] = Gtk::ToggleButton("L");
      buttons[BTN_L].set_name("btfr-btn-l");
      buttons[BTN_L].add_css_class("btfr-trigger");
      buttons[BTN_L].set_margin_bottom(20);
      grid.attach(buttons[BTN_L], 0, 0, 3, 1);
      
      buttons[BTN_Z] = Gtk::ToggleButton("Z");
      buttons[BTN_Z].set_name("btfr-btn-z");
      buttons[BTN_Z].add_css_class("btfr-trigger");
      buttons[BTN_Z].set_margin_bottom(20);
      grid.attach(buttons[BTN_Z], 3, 0, 3, 1);
      
      buttons[BTN_R] = Gtk::ToggleButton("R");
      buttons[BTN_R].set_name("btfr-btn-r");
      buttons[BTN_R].add_css_class("btfr-trigger");
      buttons[BTN_R].set_margin_bottom(20);
      grid.attach(buttons[BTN_R], 6, 0, 3, 1);

      // D-Pad
      buttons[BTN_DU] = Gtk::ToggleButton("⮝");
      buttons[BTN_DU].set_name("btfr-btn-du");
      grid.attach(buttons[BTN_DU], 1, 1);
      buttons[BTN_DD] = Gtk::ToggleButton("⮟");
      buttons[BTN_DD].set_name("btfr-btn-dd");
      grid.attach(buttons[BTN_DD], 1, 3);
      buttons[BTN_DL] = Gtk::ToggleButton("⮜");
      buttons[BTN_DL].set_name("btfr-btn-dl");
      grid.attach(buttons[BTN_DL], 0, 2);
      buttons[BTN_DR] = Gtk::ToggleButton("⮞");
      buttons[BTN_DR].set_name("btfr-btn-dr");
      grid.attach(buttons[BTN_DR], 2, 2);
      lbl_d = Gtk::Label("D");
      grid.attach(lbl_d, 1, 2);

      // Start Button, spacer to left
      spacers[0] = Gtk::Label("");
      grid.attach(spacers[0], 3, 2);
      buttons[BTN_START] = Gtk::ToggleButton("S");
      buttons[BTN_START].set_name("btfr-btn-start");
      grid.attach(buttons[BTN_START], 4, 2);

      // C Buttons
      buttons[BTN_CU] = Gtk::ToggleButton("⮝");
      buttons[BTN_CU].set_name("btfr-btn-cu");
      grid.attach(buttons[BTN_CU], 7, 1);
      buttons[BTN_CD] = Gtk::ToggleButton("⮟");
      buttons[BTN_CD].set_name("btfr-btn-cd");
      grid.attach(buttons[BTN_CD], 7, 3);
      buttons[BTN_CL] = Gtk::ToggleButton("⮜");
      buttons[BTN_CL].set_name("btfr-btn-cl");
      grid.attach(buttons[BTN_CL], 6, 2);
      buttons[BTN_CR] = Gtk::ToggleButton("⮞");
      buttons[BTN_CR].set_name("btfr-btn-cr");
      grid.attach(buttons[BTN_CR], 8, 2);
      lbl_c = Gtk::Label("C");
      grid.attach(lbl_c, 7, 2);

      // A and B
      buttons[BTN_B] = Gtk::ToggleButton("B");
      buttons[BTN_B].set_name("btfr-btn-b");
      grid.attach(buttons[BTN_B], 5, 4);
      buttons[BTN_A] = Gtk::ToggleButton("A");
      buttons[BTN_A].set_name("btfr-btn-a");
      grid.attach(buttons[BTN_A], 6, 5);
    }
    grid.set_margin(5);
    grid.set_column_homogeneous(true);
    set_child(grid);
  }
}  // namespace tasdi2