#pragma once

#ifdef _WIN32
    #include "SerialArduinoWindows.h"
#else
    #include "SerialArduinoLinux.h"
#endif

class SerialArduinoFactory {
public:
    static SerialArduino* Create(const char* port);
};

/**
 * @brief Creates a SerialArduino object based on the operating system
 * 
 * @param port port on which the arduino is connected to
 * @return SerialArduino* windows or linux derived class
 */
SerialArduino* SerialArduinoFactory::Create(const char* port) {
    #ifdef _WIN32
        return new SerialArduinoWindows(port);
    #else
        return new SerialArduinoLinux(port);
    #endif
}