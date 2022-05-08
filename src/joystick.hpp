#ifndef _TASDI2_JOYSTICK_HPP_
#define _TASDI2_JOYSTICK_HPP_
#include <gtkmm.h>

namespace tasdi2 {
  class Joystick : public Gtk::Widget {
  public:
    Joystick();
    virtual ~Joystick() {}

    virtual Gtk::SizeRequestMode get_request_mode_vfunc() const override {
      return Gtk::Widget::get_request_mode_vfunc();
    }

    virtual void measure_vfunc(
      Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
      int& minimum_baseline, int& natural_baseline) const override;
    
    void on_map() override;
    void on_unmap() override;
    
    void snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot> &snapshot) override;
    
    
    
    Glib::PropertyProxy<int> property_xpos() {
      return prop_xpos.get_proxy();
    }
    Glib::PropertyProxy_ReadOnly<int> property_xpos() const {
      return prop_xpos.get_proxy();
    }
    Glib::PropertyProxy<int> property_ypos() {
      return prop_ypos.get_proxy();
    }
    Glib::PropertyProxy_ReadOnly<int> property_ypos() const {
      return prop_ypos.get_proxy();
    }
  private:
    Glib::Property<int> prop_xpos;
    Glib::Property<int> prop_ypos;
  };
}  // namespace tasdi2
#endif