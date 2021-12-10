#ifdef _WIN32
    #include "SerialArduinoWindows.h"
#else
    #include "SerialArduinoLinux.h"
#endif

class SerialArduinoFactory {
public:
    static SerialArduino* Create(const char* port);
};

SerialArduino* SerialArduinoFactory::Create(const char* port) {
    #ifdef _WIN32
        return new SerialArduinoWindows(port);
    #else
        return new SerialArduinoLinux(port);
    #endif
}