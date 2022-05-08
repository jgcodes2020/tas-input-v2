#include "joystick.hpp"
#include <gdkmm.h>
#include <gtkmm.h>
#include <iostream>
#include <numbers>

namespace {
  inline void circle(
    const Glib::RefPtr<Cairo::Context>& cairo, double cx, double cy, double r) {
    cairo->arc(cx, cy, r, 0, 2 * std::numbers::pi);
  }

  inline void line(
    const Glib::RefPtr<Cairo::Context>& cairo, double x1, double y1, double x2,
    double y2) {
    cairo->move_to(x1, y1);
    cairo->line_to(x2, y2);
  }
}  // namespace

namespace tasdi2 {
  Joystick::Joystick() :
    Glib::ObjectBase("Tasdi2Joystick"),
    Gtk::Widget(),
    prop_xpos(*this, "xpos", 0),
    prop_ypos(*this, "ypos", 0) {
    set_hexpand();
    set_hexpand_set();
    set_vexpand();
    set_vexpand_set();
  }

  void Joystick::measure_vfunc(
    Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
    int& minimum_baseline, int& natural_baseline) const {
    minimum          = 128;
    natural          = 160;
    minimum_baseline = -1;
    natural_baseline = -1;
    return;
  }

  void Joystick::on_map() { Gtk::Widget::on_map(); }
  void Joystick::on_unmap() { Gtk::Widget::on_unmap(); }

  void Joystick::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot>& snapshot) {
    const auto space = get_allocation();
    const Gdk::Rectangle rect(0, 0, space.get_width(), space.get_height());
    std::cout << "Allocation area: " << space.get_x() << ", " << space.get_y() << ", " << space.get_width() << ", " << space.get_height() << "\n";

    auto cairo = snapshot->append_cairo(rect);

    const double w  = space.get_width();
    const double h  = space.get_height();
    const double cx = w / 2;
    const double cy = h / 2;
    // colors
    const Gdk::RGBA color_bg0("#7F7F7F");
    const Gdk::RGBA color_bg1("#FFFFFF");
    const Gdk::RGBA color_oln("#000000");
    const Gdk::RGBA color_cln("#0000FF");
    const Gdk::RGBA color_dot("#FF0000");

    cairo->rectangle(0, 0, w, h);
    Gdk::Cairo::set_source_rgba(cairo, color_bg0);
    cairo->fill();

    circle(cairo, cx, cy, cx);
    Gdk::Cairo::set_source_rgba(cairo, color_bg1);
    cairo->fill_preserve();

    line(cairo, cx, 0, cx, h);
    line(cairo, 0, cy, w, cy);
    Gdk::Cairo::set_source_rgba(cairo, color_oln);
    cairo->stroke();
  }
}  // namespace tasdi2