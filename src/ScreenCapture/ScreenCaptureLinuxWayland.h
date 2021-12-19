#include <wayland-client.h>

#include "ScreenCapture.h"

class ScreenCaptureLinuxWayland : public ScreenCapture {
private:
    int screenNumber;
    
    wl_display* display;
public:
    ScreenCaptureLinuxWayland(int screenNumber);
    ~ScreenCaptureLinuxWayland();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};