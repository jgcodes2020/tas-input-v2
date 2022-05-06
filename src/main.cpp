#include <gtkmm.h>
#include <sigc++/sigc++.h>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include "gdkmm/display.h"
#include "gdkmm/enums.h"
#include "gdkmm/rgba.h"
#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

#include "gtkmm/cssprovider.h"
#include "gtkmm/drawingarea.h"
#include "gtkmm/enums.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/stylecontext.h"
#include <resources/css/main.css.rsrc.hpp>
#include <resources/ui/main.ui.rsrc.hpp>

namespace tasdi2 {
  class JoystickDrawHandler {
  public:
    JoystickDrawHandler() :
      color_fg(0.0f, 0.0f, 0.0f),
      color_bg(1.0f, 1.0f, 1.0f),
      color_ln(0.0f, 0.0f, 1.0f),
      color_hd(1.0f, 0.0f, 0.0f) {}

    void operator()(
      const Cairo::RefPtr<Cairo::Context>& cairo, int width, int height) {
      const double width2  = width / 2.0;
      const double height2 = height / 2.0;

      // background circle
      circle(cairo, width2, height2, width2);
      set_color(cairo, color_bg);
      cairo->fill();

      // outline with axes
      circle(cairo, width2, height2, width2);
      line(cairo, width2, 0, width2, height);
      line(cairo, 0, height2, width, height2);
      set_color(cairo, color_fg);
      cairo->stroke();
    }

  private:
    static void set_color(
      const Cairo::RefPtr<Cairo::Context>& cairo, const Gdk::RGBA& color) {
      cairo->set_source_rgba(
        color.get_red(), color.get_green(), color.get_blue(),
        color.get_alpha());
    }
    static void circle(
      const Cairo::RefPtr<Cairo::Context>& cairo, double cx, double cy,
      double r) {
      cairo->arc(cx, cy, r, 0, std::numbers::pi * 2);
    }
    static void line(
      const Cairo::RefPtr<Cairo::Context>& cairo, double x1, double y1,
      double x2, double y2) {
      cairo->move_to(x1, y1);
      cairo->line_to(x2, y2);
    }

    Gdk::RGBA color_fg;
    Gdk::RGBA color_bg;
    Gdk::RGBA color_ln;
    Gdk::RGBA color_hd;
  };

  class MainWindow : public Gtk::Window {
  public:
    MainWindow() :
      builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)) {
      // Setup UI
      set_default_size(385, 475);
      set_resizable(false);
      set_title("TASInput");
      set_child(*builder->get_widget<Gtk::Box>("main-root"));

      // Setup drawing thing
      Gtk::DrawingArea& jsfr_area =
        *builder->get_widget<Gtk::DrawingArea>("jsfr-stick");
      JoystickDrawHandler draw;
      jsfr_area.set_draw_func(draw);
    };

  protected:
    Glib::RefPtr<Gtk::Builder> builder;
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