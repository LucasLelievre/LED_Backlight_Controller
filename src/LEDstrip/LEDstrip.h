#include <iostream>
#include <vector>
#include <algorithm>

class LEDstrip {
private:
    int width, height, leds_total, leds_x, leds_y;
    
    // colour transition
    short fade = 70;
    // RGB values for each LED
    short ledColour[180] = {0};
    // Previous rgb values for smooth transitions
    short prevColour[180] = {0};

    // TODO works only for 60 LEDs
    // Data that will be sent to the arduino : 60 LEDs * 3 colours + 2 header characters
    char serialData[60 * 3 + 2];
    
    // TODO works only for 60 LEDs
    // index of a [x][y] in the screenData buffer
    size_t pixelOffset[60][256];

    int LEDposX(int posX);
    int LEDposY(int posY);
public:
    char * computeColours(std::vector<unsigned char>* screenData);

    LEDstrip(int screenX, int screenY, int ledNbTot, int ledNbX, int ledNbY, float ratio);
    ~LEDstrip();
};