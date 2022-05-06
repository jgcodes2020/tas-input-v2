#include "ButtonFrame.hpp"
#include <gtkmm.h>
#include <array>
#include <stdexcept>

#include <resources/css/button-frame.css.rsrc.hpp>
#include <resources/ui/button-frame.ui.rsrc.hpp>


namespace tasdi2 {
  ButtonFrame::ButtonFrame() :
    Gtk::Frame("Buttons"),
    builder(Gtk::Builder::create_from_string(tasdi2::rsrc::ui_data)) {
    // Add style provider
    auto css_loader = Gtk::CssProvider::create();
    css_loader->load_from_data(tasdi2::rsrc::css_data);

    auto style_ctx = this->get_style_context();
    auto display   = this->get_display();
    style_ctx->add_provider_for_display(
      display, css_loader, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    set_child(*builder->get_widget<Gtk::Grid>("btfr-root"));
  }
}  // namespace tasdi2