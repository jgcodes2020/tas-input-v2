#include "main_window.hpp"
#include "gtkmm/button.h"
#include "joystick.hpp"

#include <cairomm/cairomm.h>
#include <glibmm.h>
#include <gtkmm.h>
#include <sigc++/sigc++.h>

#include <cstdlib>
#include <iostream>
#include <numbers>
#include "mupen64plus/m64p_plugin.h"
#include <resources/css/main.css.rsrc.hpp>
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
  };

  BUTTONS MainWindow::retrieve_input(int idx) {
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
    
    res.X_AXIS = jsfr_stick.property_xpos().get_value();
    res.Y_AXIS = jsfr_stick.property_ypos().get_value();
    
    return res;
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