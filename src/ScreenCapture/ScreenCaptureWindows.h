#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>

#include "ScreenCapture.h"

class ScreenCaptureWindows : public ScreenCapture {
private:
    /* data */
public:
    ScreenCaptureWindows(int screenNumber);
    ~ScreenCaptureWindows();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};