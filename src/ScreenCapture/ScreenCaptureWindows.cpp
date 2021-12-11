#pragma once

#include "ScreenCaptureWindows.h"

/**
 * @brief Construct a new Screen Capture Windows:: Screen Capture Windows object
 * 
 * @param screenNumber number of the screen to capture (starts at 0)
 */
ScreenCaptureWindows::ScreenCaptureWindows(int screenNumber) {
    std::cout << "create windows screen capture" << std::endl;
}

/**
 * @brief Destroy the Screen Capture Windows:: Screen Capture Windows object
 * 
 */
ScreenCaptureWindows::~ScreenCaptureWindows() {
    std::cout << "deconstruct windows screen capture" << std::endl;
}

/**
 * @brief initialize the screen capture
 * 
 * @return std::string //TODO what is returned here ?
 */
std::string ScreenCaptureWindows::initialize() { return "init"; }

/**
 * @brief End the screen capture
 * 
 */
void ScreenCaptureWindows::close() {}

/**
 * @brief Capture a frame of the screen
 * 
 * @return true success
 * @return false failure
 */
bool ScreenCaptureWindows::captureNext() { return true; }

/**
 * @brief Get the captured screen data in a buffer
 * 
 * @return std::vector<uint8_t>* buffer containing the captured data
 */
std::vector<uint8_t>* ScreenCaptureWindows::getScreenData() { return NULL; }