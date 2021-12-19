#include "ScreenCaptureLinuxX11.h"

/**
 * @brief Construct a new Screen Capture Linux:: Screen Capture Linux object
 * 
 * @param screenNumber number of the screen to capture (starts at 0)
 */
ScreenCaptureLinuxX11::ScreenCaptureLinuxX11(int screenNumber) {
    std::cout << "create linux screen capture" << std::endl;
    this->screenNumber = screenNumber;
}

/**
 * @brief Destroy the Screen Capture Linux:: Screen Capture Linux object
 * 
 */
ScreenCaptureLinuxX11::~ScreenCaptureLinuxX11() {
    std::cout << "deconstruct linux screen capture" << std::endl;
    this->close();
}

/**
 * @brief initialize the screen capture
 * 
 * @return std::string //TODO what is returned here ?
 */
std::string ScreenCaptureLinuxX11::initialize() {
    // TODO select the requested screen
    this->dis=XOpenDisplay((char *)0);
    this->scr = XDefaultScreenOfDisplay(dis);
    this->drawable = XDefaultRootWindow(dis);
    return "init success\n";
}

/**
 * @brief End the screen capture
 * 
 */
void ScreenCaptureLinuxX11::close() {
    XDestroyImage(this->image);
    XCloseDisplay(this->dis);
}

/**
 * @brief Capture a frame of the screen
 * 
 * @return true success
 * @return false failure
 */
bool ScreenCaptureLinuxX11::captureNext() {
    this->image = XGetImage(this->dis, this->drawable, 0, 0, this->scr->width, this->scr->height, AllPlanes, ZPixmap);
    this->screenData = new std::vector<uint8_t>(this->image->data, this->image->data + (scr->width*4*scr->height));
    return true;
}

/**
 * @brief Get the captured screen data in a buffer
 * 
 * @return std::vector<uint8_t>* buffer containing the captured data
 */
std::vector<uint8_t>* ScreenCaptureLinuxX11::getScreenData() {
    return this->screenData;
}