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
#include "joystick.hpp"
#include <resources/css/main.css.rsrc.hpp>
#include <resources/ui/main.ui.rsrc.hpp>

namespace tasdi2 {

  // MAIN WINDOW CLASS
  // ======================
  class MainWindow : public Gtk::Window {
  public:
    MainWindow() :
      builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)),
      drag_hnd(Gtk::GestureDrag::create()) {
      // Setup UI
      set_title("TASInput");
      set_child(*builder->get_widget<Gtk::Box>("main-root"));
      // Link joystick
      auto& jsfr_stick_ctn =
        *builder->get_widget<Gtk::AspectFrame>("jsfr-stick-ctn");
      // Temporary fix until my SO question is answered:
      // https://stackoverflow.com/questions/72157547/gtkmm-how-do-i-use-a-custom-widget-in-a-gtkbuilder-xml-file
      jsfr_stick_ctn.set_child(stick);
    };

  protected:
    tasdi2::Joystick stick;
  
    Glib::RefPtr<Gtk::Builder> builder;
    Glib::RefPtr<Gtk::GestureDrag> drag_hnd;
  };
}  // namespace tasdi2

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("io.github.jgcodes2020.testapp");
  app->signal_startup().connect([]() {
    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);

    auto display = Gdk::Display::get_default();

    Gtk::StyleContext::add_provider_for_display(
      display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  });
  return app->make_window_and_run<tasdi2::MainWindow>(argc, argv);
}