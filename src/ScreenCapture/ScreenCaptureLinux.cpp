#include "ScreenCaptureLinux.h"

ScreenCaptureLinux::ScreenCaptureLinux(/* args */) {
    std::cout << "create linux screen capture" << std::endl;
}

ScreenCaptureLinux::~ScreenCaptureLinux() {
    std::cout << "deconstruct linux screen capture" << std::endl;
}

std::string ScreenCaptureLinux::initialize() { return "init"; }
void ScreenCaptureLinux::close() {}
bool ScreenCaptureLinux::captureNext() { return true; }

std::vector<uint8_t>* ScreenCaptureLinux::getScreenData() { return NULL; }