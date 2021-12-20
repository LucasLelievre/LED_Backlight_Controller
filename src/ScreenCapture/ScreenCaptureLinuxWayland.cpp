#include "ScreenCaptureLinuxWayland.h"

ScreenCaptureLinuxWayland::ScreenCaptureLinuxWayland(int screenNumber) {
    this->screenNumber = screenNumber;
}

ScreenCaptureLinuxWayland::~ScreenCaptureLinuxWayland() {
    this->close();
}

std::string ScreenCaptureLinuxWayland::initialize(){
    this->display = wl_display_connect("wayland-0");
    if (!this->display) {
        return "Could not connect to the wayland display\n";
    }
    return "init success\n";
}

void ScreenCaptureLinuxWayland::close(){
    wl_display_disconnect(this->display);
}

bool ScreenCaptureLinuxWayland::captureNext(){
    return false;
}

std::vector<uint8_t>* ScreenCaptureLinuxWayland::getScreenData(){
    return NULL;
}