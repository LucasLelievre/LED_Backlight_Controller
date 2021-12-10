#pragma once

#include <string>
#include <vector>

class ScreenCapture {
public:
    virtual std::string initialize() = 0;
    virtual void close() = 0;
    virtual bool captureNext() = 0;

    virtual std::vector<uint8_t>* getScreenData() = 0;
};