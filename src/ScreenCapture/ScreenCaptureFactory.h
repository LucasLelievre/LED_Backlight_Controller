#ifdef _WIN32
    #include "ScreenCaptureWindows.h"
#else
    #include "ScreenCaptureLinux.h"
#endif

class ScreenCaptureFactory {
public:
    static ScreenCapture* Create();
};

ScreenCapture* ScreenCaptureFactory::Create() {
    #ifdef _WIN32
        return new ScreenCaptureWindows();
    #else
        return new ScreenCaptureLinux();
    #endif
}