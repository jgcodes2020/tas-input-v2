#include <cairomm/cairomm.h>
#include <glibmm.h>
#include <gtkmm.h>
#include <sigc++/sigc++.h>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include "gdkmm/enums.h"
#include "glibmm/binding.h"
#include "glibmm/property.h"
#include "gtkmm/aspectframe.h"
#include "gtkmm/drawingarea.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/eventcontrollermotion.h"
#include "gtkmm/gesture.h"
#include "gtkmm/gesturedrag.h"
#include "gtkmm/spinbutton.h"
#include "joystick.hpp"
#include <resources/css/main.css.rsrc.hpp>
#include <resources/ui/main.ui.rsrc.hpp>

namespace tasdi2 {

  // MAIN WINDOW CLASS
  // ======================
  class MainWindow : public Gtk::Window {
  public:
    MainWindow() :
      builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)){
      // Setup UI
      set_title("TASInput");
      set_child(*builder->get_widget<Gtk::Box>("main-root"));
      set_resizable(false);
      
      // link joystick with spinners
      auto& jsfr_stick = *Gtk::Builder::get_widget_derived<tasdi2::Joystick>(builder, "jsfr-stick");
      auto& jsfr_spin_x = *builder->get_widget<Gtk::SpinButton>("jsfr-spin-x");
      auto& jsfr_spin_y = *builder->get_widget<Gtk::SpinButton>("jsfr-spin-y");

      Glib::Binding::bind_property(
        jsfr_stick.property_xpos(), jsfr_spin_x.property_value(),
        Glib::Binding::Flags::BIDIRECTIONAL);
      Glib::Binding::bind_property(
        jsfr_stick.property_ypos(), jsfr_spin_y.property_value(),
        Glib::Binding::Flags::BIDIRECTIONAL);
    };

  protected:
    Glib::RefPtr<Gtk::Builder> builder;
  };
}  // namespace tasdi2

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