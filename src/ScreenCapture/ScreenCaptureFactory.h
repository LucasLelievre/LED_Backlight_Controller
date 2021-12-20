#pragma once

#if _WIN32
    #include "ScreenCaptureWindows.h"
#elif _X11LIBS
    #include "ScreenCaptureLinuxX11.h"
#elif _WAYLANDLIBS
    #include "ScreenCaptureLinuxWayland.h"
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
    #elif _X11LIBS
        return new ScreenCaptureLinuxX11(screenNumber);
    #elif _WAYLANDLIBS
        return new ScreenCaptureLinuxWayland(screenNumber);
    #else
        return NULL;
    #endif
}