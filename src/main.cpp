#include <cstdlib>
#include <iostream>
#include "ButtonFrame.hpp"
#include "gdkmm/display.h"
#include "glibmm/ustring.h"
#include "gtkmm/button.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include "gtkmm/stylecontext.h"
#include "gtkmm/togglebutton.h"
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
      
      tbt = Gtk::Button("Hello!");
      main_box.append(tbt);
      
      set_child(main_box);
    };
  protected:
    // Container
    Gtk::Box main_box;
    // Widgets
    ButtonFrame frame;
    Gtk::Button tbt;
  };
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("io.github.jgcodes2020.testapp");
  return app->make_window_and_run<tasdi2::MainWindow>(argc, argv);
}