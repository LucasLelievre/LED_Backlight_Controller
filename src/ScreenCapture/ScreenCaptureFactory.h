#pragma once

#ifdef _WIN32
    #include "ScreenCaptureWindows.h"
#else
    #include "ScreenCaptureLinuxX11.h"
#endif

class ScreenCaptureFactory {
public:
    static ScreenCapture* Create(int screenNumber);
};

/**
 * @brief Creates a new ScreenCapture object based on operating system
 * 
 * @return ScreenCapture* windows or linux derived class
 */
ScreenCapture* ScreenCaptureFactory::Create(int screenNumber) {
    #ifdef _WIN32
        return new ScreenCaptureWindows(screenNumber);
    #else
        return new ScreenCaptureLinuxX11(screenNumber);
    #endif
}