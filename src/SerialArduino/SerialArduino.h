#pragma once

class SerialArduino {
public:
    virtual int readData(char* buffer, unsigned int nbChar) = 0;
    virtual bool writeData(const char* buffer, unsigned int nbChar) = 0;
    virtual bool isConnected() = 0;
};