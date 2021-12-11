#pragma once

#include "ScreenCaptureLinux.h"

/**
 * @brief Construct a new Screen Capture Linux:: Screen Capture Linux object
 * 
 * @param screenNumber number of the screen to capture (starts at 0)
 */
ScreenCaptureLinux::ScreenCaptureLinux(int screenNumber) {
    std::cout << "create linux screen capture" << std::endl;
}

/**
 * @brief Destroy the Screen Capture Linux:: Screen Capture Linux object
 * 
 */
ScreenCaptureLinux::~ScreenCaptureLinux() {
    std::cout << "deconstruct linux screen capture" << std::endl;
}

/**
 * @brief initialize the screen capture
 * 
 * @return std::string //TODO what is returned here ?
 */
std::string ScreenCaptureLinux::initialize() { return "init"; }

/**
 * @brief End the screen capture
 * 
 */
void ScreenCaptureLinux::close() {}

/**
 * @brief Capture a frame of the screen
 * 
 * @return true success
 * @return false failure
 */
bool ScreenCaptureLinux::captureNext() { return true; }

/**
 * @brief Get the captured screen data in a buffer
 * 
 * @return std::vector<uint8_t>* buffer containing the captured data
 */
std::vector<uint8_t>* ScreenCaptureLinux::getScreenData() { return NULL; }