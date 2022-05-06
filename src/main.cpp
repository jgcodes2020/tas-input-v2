#include <cstdlib>
#include <iostream>
#include "gdkmm/display.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include <sigc++/sigc++.h>
#include <gtkmm.h>

#include "gtkmm/cssprovider.h"
#include "gtkmm/stylecontext.h"
#include <resources/ui/main.ui.rsrc.hpp>
#include <resources/css/main.css.rsrc.hpp>

namespace tasdi2 {
  class MainWindow : public Gtk::Window {
  public:
    MainWindow() : builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)) {
      set_child(*builder->get_widget<Gtk::Box>("main-root"));
    };
  protected:
    Glib::RefPtr<Gtk::Builder> builder;
  };
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("io.github.jgcodes2020.testapp");
  app->signal_startup().connect([]() {
    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);
    
    auto display = Gdk::Display::get_default();
    
    Gtk::StyleContext::add_provider_for_display(display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  });
  return app->make_window_and_run<tasdi2::MainWindow>(argc, argv);
}