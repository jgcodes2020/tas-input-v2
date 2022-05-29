#include "main_window.hpp"
#include "gtkmm/button.h"
#include "gtkmm/headerbar.h"
#include "joystick.hpp"

#include <cairomm/cairomm.h>
#include <glibmm.h>
#include <gtkmm.h>
#include <sigc++/sigc++.h>

#include <cstdlib>
#include <iostream>
#include <numbers>
#include "mupen_api.hpp"

#include <resources/ui/main.ui.rsrc.hpp>

namespace tasdi2 {
  // MAIN WINDOW CLASS
  // ======================
  MainWindow::MainWindow() :
    builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)) {
    // Setup UI
    set_title("TASInput");
    set_child(*builder->get_widget<Gtk::Box>("main-root"));
    set_resizable(false);

    // link joystick with spinners
    auto& jsfr_stick = *Gtk::Builder::get_widget_derived<tasdi2::Joystick>(
      builder, "jsfr-stick");
    auto& jsfr_spin_x = *builder->get_widget<Gtk::SpinButton>("jsfr-spin-x");
    auto& jsfr_spin_y = *builder->get_widget<Gtk::SpinButton>("jsfr-spin-y");

    Glib::Binding::bind_property(
      jsfr_stick.property_xpos(), jsfr_spin_x.property_value(),
      Glib::Binding::Flags::BIDIRECTIONAL);
    Glib::Binding::bind_property(
      jsfr_stick.property_ypos(), jsfr_spin_y.property_value(),
      Glib::Binding::Flags::BIDIRECTIONAL);

    signal_close_request().connect([]() { return true; }, false);
  };

  BUTTONS MainWindow::get_input() {
    BUTTONS res;
    res.L_TRIG =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-l")->get_active();
    res.Z_TRIG =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-z")->get_active();
    res.R_TRIG =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-r")->get_active();

    res.U_DPAD =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-du")->get_active();
    res.D_DPAD =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-dd")->get_active();
    res.L_DPAD =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-dl")->get_active();
    res.R_DPAD =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-dr")->get_active();

    res.U_CBUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-cu")->get_active();
    res.D_CBUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-cd")->get_active();
    res.L_CBUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-cl")->get_active();
    res.R_CBUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-cr")->get_active();

    res.A_BUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-a")->get_active();
    res.B_BUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-b")->get_active();
    res.START_BUTTON =
      builder->get_widget<Gtk::ToggleButton>("btfr-btn-start")->get_active();

    auto& jsfr_stick = *Gtk::Builder::get_widget_derived<tasdi2::Joystick>(
      builder, "jsfr-stick");

    res.X_AXIS = jsfr_stick.get_xpos();
    res.Y_AXIS = jsfr_stick.get_ypos();

    return res;
  }

  void MainWindow::set_input(BUTTONS btns) {
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-l")
      ->set_active(btns.L_TRIG);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-z")
      ->set_active(btns.Z_TRIG);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-r")
      ->set_active(btns.R_TRIG);

    builder->get_widget<Gtk::ToggleButton>("btfr-btn-du")
      ->set_active(btns.U_DPAD);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-dd")
      ->set_active(btns.D_DPAD);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-dl")
      ->set_active(btns.L_DPAD);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-dr")
      ->set_active(btns.R_DPAD);

    builder->get_widget<Gtk::ToggleButton>("btfr-btn-cu")
      ->set_active(btns.U_CBUTTON);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-cd")
      ->set_active(btns.D_CBUTTON);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-cl")
      ->set_active(btns.L_CBUTTON);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-cr")
      ->set_active(btns.R_CBUTTON);

    builder->get_widget<Gtk::ToggleButton>("btfr-btn-a")
      ->set_active(btns.A_BUTTON);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-b")
      ->set_active(btns.B_BUTTON);
    builder->get_widget<Gtk::ToggleButton>("btfr-btn-start")
      ->set_active(btns.START_BUTTON);
      
    auto& jsfr_stick = *Gtk::Builder::get_widget_derived<tasdi2::Joystick>(
      builder, "jsfr-stick");

    jsfr_stick.set_xpos(btns.X_AXIS);
    jsfr_stick.set_ypos(btns.Y_AXIS);
  }
}  // namespace tasdi2

// OLD MAIN FUNCTION
/*
int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("io.github.jgcodes2020.tasinput2");

  // Register tasdi2::Joystick to the GObject type system
  { tasdi2::Joystick(); }

  app->signal_startup().connect([]() {
    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);

    auto display = Gdk::Display::get_default();

    Gtk::StyleContext::add_provider_for_display(
      display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  });
  return app->make_window_and_run<tasdi2::MainWindow>(argc, argv);
}
*/