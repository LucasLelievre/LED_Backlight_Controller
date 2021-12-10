#include <vector>
#include <algorithm>

class LEDstrip {
private:
    int width, height, leds_total, leds_x, leds_y;

    short fade = 70;
    int minBrightness = 120;

    int pixelOffset[60][256];

    // RGB values for eahc LED
    short ledColour[180];
    short prevColour[180];

    char gamma[256][3];
    // Data that will be sent to the arduino : 60 LEDs * 3 colours + 2 header characters
    char serialData[60 * 3 + 2];
    int data_index = 0;

    int LEDposX(int posX);
    int LEDposY(int posY);
public:
    char * computeColours(std::vector<unsigned char>* screenData);

    LEDstrip(int* intArgs, float ratio);
    ~LEDstrip();
};