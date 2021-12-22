#include "LEDstrip.h"

/**
 * @brief Construct a new LEDstrip::LEDstrip object
 * 
 * @param intArgs array of width/height/LEDtotal/LEDhorizontal/LEDvertical
 * @param ratio ratio of the captured zone
 */
LEDstrip::LEDstrip(int screenX, int screenY, int ledNbTot, int ledNbX, int ledNbY, float ratio) {
    this->width = screenX;
    this->height = screenY;
    this->leds_total = ledNbTot;
    this->leds_x = ledNbX;
    this->leds_y = ledNbY;

    // LED colours are the average of 256 samples of a portion of the screen
    
    // Samples positions arrays
    int x[16], y[16];

    // Range is the size of the portion of the screen that will be represented by one LED
    int rangeX, rangeY;
    rangeX = this->width / this->leds_x;
    rangeY = this->height / this->leds_y;

    // Step is the space between two samples for one LED (16*16=256 samples)
    int stepX, stepY;
    stepX = rangeX / 16;
    stepY = rangeY / 16;

    // Size of the "black bars" when the captured zone ratio is different than the screen ratio.
    float imageHeight = (float)this->width / ratio;
    int blackBarHeight = (this->height - (int)imageHeight) / 2;

    // Start position is the first 
    int startX, startY;
    for (int i = 0; i < this->leds_total; i++) { // For each LED...
        // start base on the position of the LED
        startX = rangeX * LEDposX(i) + stepX/2;
        startY = rangeY * LEDposY(i) + stepY/2;

        // Offset the y position under the top black bar
        if (i >= ledNbY && i <= ledNbY+ledNbX) {
            startY += blackBarHeight;
        }

        for (int j = 0; j < 16; j++) {
            // Computing all sample positions
            x[j] = startX + stepX * j;
            y[j] = startY + stepY * j;
        }

        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                // computing the index of the pixel in the bitmap data from the XY position
                pixelOffset[i][row * 16 + col] = (size_t)((x[row] + (y[col] * this->width)) * 4);
            }
        }
    }

    // A special header expected by the Arduino, to identify the beginning of a new bunch data.
    serialData[0] = 'o';
    serialData[1] = 'z';
}

LEDstrip::~LEDstrip() {
}

/**
 * @brief Get the pixel's x position from it's index in the screen buffer
 * 
 * @param led index in the screen buffer
 * @return int X position
 */
int LEDstrip::LEDposX(int led) {
    return std::min(std::max(led - 15, 0), 29);
}

/**
 * @brief Get the pixel's y position from it's index in the screen buffer
 * 
 * @param led index in the screen buffer
 * @return int Y position
 */
int LEDstrip::LEDposY(int led) {
    double pos = std::abs((double)led - 29.5) - 14.5;
    return std::max<int>(int(pos), 0);
}

/**
 * @brief Compute the Data to send to the arduino
 * 
 * @param screenData captured screen data
 * @return char* data to send to the arduino
 */
char * LEDstrip::computeColours(std::vector<unsigned char> * screenData) {
    // screenData is the BGRA bitmap data captured from the screen

    int data_index = 2; // 0, 1 are predefined header

    for (int i = 0; i < this->leds_total; i++) {  // For each LED...
        int r = 0;
        int g = 0;
        int b = 0;

        for (int o = 0; o < 256; o++) {
            // adding all samples to each other
            r += (int)screenData->at(pixelOffset[i][o] + 2);
            g += (int)screenData->at(pixelOffset[i][o] + 1);
            b += (int)screenData->at(pixelOffset[i][o] + 0);
        }

        // Blend new pixel value with the value from the prior frame
        ledColour[i * 3 + 0] = ((r >> 8) * (255 - this->fade) + prevColour[i * 3 + 0] * fade) >> 8;
        ledColour[i * 3 + 1] = ((g >> 8) * (255 - this->fade) + prevColour[i * 3 + 1] * fade) >> 8;
        ledColour[i * 3 + 2] = ((b >> 8) * (255 - this->fade) + prevColour[i * 3 + 2] * fade) >> 8;

        serialData[data_index++] = (char)prevColour[i * 3 + 0];
        serialData[data_index++] = (char)prevColour[i * 3 + 1];
        serialData[data_index++] = (char)prevColour[i * 3 + 2];
    }

    std::copy(ledColour, ledColour+180, prevColour);
    //delete[] screenData;
    return this->serialData;
}