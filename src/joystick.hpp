#ifndef _TASDI2_JOYSTICK_HPP_
#define _TASDI2_JOYSTICK_HPP_
#include <gtkmm.h>

namespace tasdi2 {
  class Joystick : public Gtk::Widget {
  public:
    // Default constructor.
    Joystick();
    // Constructor used by GtkBuilder.
    Joystick(BaseObjectType* c_obj, const Glib::RefPtr<Gtk::Builder> builder);
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
    // Performs initialization common to all constructors.
    void common_init();
  
    Glib::Property<int> prop_xpos;
    Glib::Property<int> prop_ypos;
    
    sigc::connection slot_xpos;
    sigc::connection slot_ypos;
    
    Glib::RefPtr<Gtk::GestureDrag> drag_gest;
    int drag_x;
    int drag_y;
  };
}  // namespace tasdi2
#endif