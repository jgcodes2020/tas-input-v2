#include "joystick.hpp"
#include <gdkmm.h>
#include <gtkmm.h>
#include <iostream>
#include <numbers>
#include <algorithm>
#include "gdkmm/general.h"
#include "gtkmm/gesturedrag.h"

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
  
  template <class T>
  inline T clamp(T x, T min, T max) {
    return std::max(min, std::min(max, x));
  }
}  // namespace

namespace tasdi2 {
  Joystick::Joystick() :
    Glib::ObjectBase("Tasdi2Joystick"),
    Gtk::Widget(),
    prop_xpos(*this, "xpos", 0),
    prop_ypos(*this, "ypos", 0),
    drag_gest(Gtk::GestureDrag::create()) {
    common_init();
  }
  
  Joystick::Joystick(BaseObjectType* c_obj, const Glib::RefPtr<Gtk::Builder> builder) :
    Glib::ObjectBase("Tasdi2Joystick"),
    Gtk::Widget(c_obj),
    prop_xpos(*this, "xpos", 0),
    prop_ypos(*this, "ypos", 0),
    drag_gest(Gtk::GestureDrag::create()) {
    common_init();
  }
  
  void Joystick::common_init() {
    // redraw when xpos or ypos changes
    slot_xpos = property_xpos().signal_changed().connect([&]() {
      queue_draw();
    });
    slot_ypos = property_ypos().signal_changed().connect([&]() {
      queue_draw();
    });
    
    set_cursor("pointer");
    
    // mouse drag handler
    this->add_controller(drag_gest);
    drag_gest->signal_drag_begin().connect([&](double x, double y) {
      drag_x = x;
      drag_y = y;
      
      prop_xpos.set_value(clamp(int(drag_x * 256 / get_width()) - 128, -128, 127));
      prop_ypos.set_value(-clamp(int(drag_y * 256 / get_width()) - 128, -128, 127));
      
      set_cursor("closedhand");
    }, false);
    drag_gest->signal_drag_update().connect([&](double dx, double dy) {
      const double real_x = drag_x + dx;
      const double real_y = drag_y + dy;
      
      prop_xpos.set_value(clamp(int(real_x * 256 / get_width()) - 128, -128, 127));
      prop_ypos.set_value(-clamp(int(real_y * 256 / get_width()) - 128, -128, 127));
    }, false);
    drag_gest->signal_drag_end().connect([&](double dx, double dy) {
      const double real_x = drag_x + dx;
      const double real_y = drag_y + dy;
      
      prop_xpos.set_value(clamp(int(real_x * 256 / get_width()) - 128, -128, 127));
      prop_ypos.set_value(-clamp(int(real_y * 256 / get_width()) - 128, -128, 127));
      set_cursor("pointer");
    }, false);
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

    auto cairo = snapshot->append_cairo(rect);
    // special points
    const double w  = space.get_width();
    const double h  = space.get_height();
    const double cx = w / 2;
    const double cy = h / 2;
    const double jx = (prop_xpos.get_value() + 128) * w / 256;
    const double jy = (128 - prop_ypos.get_value()) * w / 256;
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
    cairo->set_line_width(1);
    Gdk::Cairo::set_source_rgba(cairo, color_oln);
    cairo->stroke();

    line(cairo, cx, cy, jx, jy);
    cairo->set_line_width(3);
    Gdk::Cairo::set_source_rgba(cairo, color_cln);
    cairo->stroke();

    circle(cairo, jx, jy, 5);
    Gdk::Cairo::set_source_rgba(cairo, color_dot);
    cairo->fill();
  }
}  // namespace tasdi2