#include "ScreenCaptureWindows.h"

ScreenCaptureWindows::ScreenCaptureWindows(/* args */) {
    std::cout << "create windows screen capture" << std::endl;
}

ScreenCaptureWindows::~ScreenCaptureWindows() {
    std::cout << "deconstruct windows screen capture" << std::endl;
}

std::string ScreenCaptureWindows::initialize() { return "init"; }
void ScreenCaptureWindows::close() {}
bool ScreenCaptureWindows::captureNext() { return true; }

std::vector<uint8_t>* ScreenCaptureWindows::getScreenData() { return NULL; }