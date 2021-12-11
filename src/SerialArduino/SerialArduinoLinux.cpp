#pragma once

#include "SerialArduinoLinux.h"

/**
 * @brief Initialize Serial communication with the given COM port
 * 
 * @param port the port name/number that the arduino is connected to
 */
SerialArduinoLinux::SerialArduinoLinux(const char* port) {
}

/**
 * @brief Close the connection
 * 
 */
SerialArduinoLinux::~SerialArduinoLinux() {
}

/** 
 * @brief Read data in a buffer, if nbChar is greater than the
 * maximum number of bytes available, it will return only the
 * bytes available. The function return -1 when nothing could
 * be read, the number of bytes actually read.
 * 
 * @param buffer output buffer that will contain the read data
 * @param nbChar size of the data to be read
 * @return int //TODO what is returned here ?
 */
int SerialArduinoLinux::readData(char* buffer, unsigned int nbChar) {
    return 0;
}

/**
 * @brief Writes data from a buffer through the Serial connection
 * 
 * @param buffer data to send to the arduino
 * @param nbChar size of the data
 * @return true success
 * @return false failure
 */
bool SerialArduinoLinux::writeData(const char* buffer, unsigned int nbChar) {
    return false;
}

/**
 * @brief Check if we are actually connected
 * 
 * @return true The arduino is connected
 * @return false The arduino is NOT connected
 */
bool SerialArduinoLinux::isConnected() {
    return false;
}
