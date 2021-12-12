#pragma once

#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "ScreenCapture.h"

class ScreenCaptureLinuxX11 : public ScreenCapture {
private:
    int screenNumber;
    Display *dis;
    Screen *scr;
    Drawable drawable;
    XImage *image;

    std::vector<uint8_t>* screenData;
public:
    ScreenCaptureLinuxX11(int screenNumber);
    ~ScreenCaptureLinuxX11();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};