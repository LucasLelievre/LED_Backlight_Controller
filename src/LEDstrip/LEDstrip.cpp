#include "LEDstrip.h"

/**
 * @brief Construct a new LEDstrip::LEDstrip object
 * 
 * @param intArgs array of width/height/LEDtotal/LEDhorizontal/LEDvertical
 * @param ratio ratio of the captured zone
 */
LEDstrip::LEDstrip(int* intArgs, float ratio) {
    this->width = intArgs[0];
    this->height = intArgs[1];
    this->leds_total = intArgs[2];
    this->leds_x = intArgs[3];
    this->leds_y = intArgs[4];

    // Initialising the offset array
    int x[16];
    int y[16];
    // LED colours are the average of 256 samples of a portion of the screen
    float rangeX, rangeY, stepX, stepY, startX, startY;
    // Range is the size of the portion of the screen that will be represented by one LED
    rangeX = (float)this->width / this->leds_x;
    rangeY = (float)this->height / this->leds_y;
    // Step is the space between two samples for one LED (16*16=256 samples)
    stepX = rangeX / 16.0f;
    stepY = rangeY / 16.0f;

    // Size of the "blackbars" when the captured zone ratio is different than the screen ratio.
    float blackBarHeight = (this->height - (this->width / ratio)) / 2;

    for (int i = 0; i < this->leds_total; i++) { // For each LED...
        // start base on the position of the LED
        startX = rangeX * (float)LEDposX(i) + stepX * 0.5f;
        startY = rangeY * (float)LEDposY(i) + stepY * 0.5f;
        if (i >= 15 && i <= 45)
            startY += blackBarHeight;

        for (int j = 0; j < 16; j++) {
            // Computing all sample positions
            x[j] = (int)(startX + stepX * (float)j);
            y[j] = (int)(startY + stepY * (float)j);
        }

        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                // computing the index of the pixel in the bitmap data from the XY position
                pixelOffset[i][row * 16 + col] = (x[row] + (y[col] * this->width)) * 4;
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

    this->data_index = 2; // 0, 1 are predefined header

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
        // 
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