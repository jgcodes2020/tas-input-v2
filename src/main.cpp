#include <cstdlib>
#include <iostream>
#include "ButtonFrame.hpp"
#include "glibmm/ustring.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "sigc++/functors/ptr_fun.h"
#include <sigc++/sigc++.h>
#include <gtkmm.h>

namespace tasdi2 {
  class MainWindow : public Gtk::Window {
  public:
    MainWindow() :
      frame(),
      main_box(Gtk::Orientation::VERTICAL) {
      
      // Setup box
      main_box.set_homogeneous(true);
      main_box.set_margin(10);
      main_box.append(frame);
      
      set_child(main_box);
    };
  protected:
    // Container
    Gtk::Box main_box;
    // Widgets
    ButtonFrame frame;
  };
}

int main(int argc, char* argv[]) {
  Gio::Application::Flags flags = Gio::Application::Flags::NONE;
  auto app = Gtk::Application::create("io.github.jgcodes2020.testapp");
  return app->make_window_and_run<tasdi2::MainWindow>(argc, argv);
}