#include <iostream>

#include "ScreenCapture.h"

class ScreenCaptureLinux : public ScreenCapture {
private:
    /* data */
public:
    ScreenCaptureLinux(/* args */);
    ~ScreenCaptureLinux();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};