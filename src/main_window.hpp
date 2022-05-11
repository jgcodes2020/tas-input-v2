#ifndef _TASDI2_MAIN_WINDOW_HPP_
#define _TASDI2_MAIN_WINDOW_HPP_

#include <gtkmm.h>
#include <glibmm.h>

#include "gtkmm/headerbar.h"
#include "mupen_api.hpp"

namespace tasdi2 {
  class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    
    BUTTONS retrieve_input(int idx);
  protected:
    Glib::RefPtr<Gtk::Builder> builder;
  };
}
#endif