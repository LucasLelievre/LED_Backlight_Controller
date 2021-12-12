#pragma once

#include <iostream>

#include "SerialArduino.h"

class SerialArduinoLinux : public SerialArduino {
private:
    const char* port;
public:
    SerialArduinoLinux(const char* port);
    ~SerialArduinoLinux();

    //TODO linux arduino serial connection
    int readData(char* buffer, unsigned int nbChar);
    bool writeData(const char* buffer, unsigned int nbChar);
    bool isConnected();
};
