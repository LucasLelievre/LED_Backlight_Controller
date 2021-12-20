#include <iostream>
#include <chrono>
#include <thread>

#include "ScreenCapture/ScreenCaptureFactory.h"
#include "SerialArduino/SerialArduinoFactory.h"
#include "LEDstrip/LEDstrip.h"

template <typename T>
/**
 * @brief Translates a const char* argument to a specified type
 * 
 * @param buffer the const char* argument input
 * @param format format specifier
 * @param output typed output
 */
void scanArg(const char* buffer, const char* format, T* output) {
    #ifdef _WIN32
        sscanf_s(buffer, format, output);
    #else
        sscanf(buffer, format, output);
    #endif
}

int main(int argc, const char* argv[]) {
    std::cout << "[Begin]\tStarting " << argv[0] << std::endl;
    if (argc != 10) {
        std::cout << "/!\\---------------------------------------------------------------------------------------------\n";
        std::cerr << "Incorrect number of arguments given.\nUsage :\n";
        std::cout << "1- Screen number (starts at 0)\n2- Screen width resolution\n3- Screen height resolution\n4- Number of LEDs in total\n5- Number of LEDs on top of the screen\n6- Number of LEDs on each side of the screen\n7- Arduino COM port\n8- Capture frame rate\n9- Capture zone aspect ratio\n";
        std::cout << "Using default parameters : 0, 1920, 1080, 60, 30, 15, COM3, 30, 1.78\n";
        std::cout << "/!\\---------------------------------------------------------------------------------------------\n\n";
        const char* arg[] = {argv[0], "0", "1920", "1080", "60", "30", "15", "COM3", "30", "1.78"};
        argv = arg;
    }

    std::cout << "[1]\tReading paramters ...\n";
    // Screen number
	int numScreen;
    scanArg(argv[1], "%d", &numScreen);

    // Framerate
	float frameRate;
    scanArg(argv[8], "%f", &frameRate);
	// translate the number of images per second to the number of milliseconds needed to wait to acheive the framerate
	frameRate = (1000 / frameRate);
    std::chrono::milliseconds sleepTime((int)frameRate);

    // Screen size and LEDs number
	int args[5];
	for (int i = 0; i < 5; i++)
        scanArg(argv[i+2], "%d", &args[1]);

    // Aspect ratio
	float ratio;
    scanArg(argv[9], "%f", &ratio);

    // Arduino COM port
    std::string port = "\\\\.\\";
    port.append(argv[7]);

    std::cout << "[2]\tConnection to the Arduino on port " << port << "...\n";
    SerialArduino* arduino = SerialArduinoFactory::Create(port.c_str());
	if (arduino->isConnected()) {
		std::cout << "Arduino connected.\n\n";
	} else {
		std::cout << "/!\\ Connexion to Arduino failed.\nQuitting.\n";
		//exit(1);
	}

    std::cout << "[3]\tInitializing the LED strip ...\n";
    LEDstrip ledStrip(args, ratio);

    std::cout << "[4]\tInitializing the Screen capture ...\n";
    ScreenCapture* sc = ScreenCaptureFactory::Create(numScreen);
    std::cout << sc->initialize();

    std::cout << "[5]\tApp initialized.\nStarting to capture the screen and sending the data.\n";

    // while(true) {
    //     std::cout << "capture\n";
    //     sc->captureNext();
    //     std::cout << "compute colours\n";
    //     char * serialData = ledStrip.computeColours(sc->getScreenData());
    //     std::cout << "send to arudino\n";
    //     arduino->writeData(serialData, args[2]*3+2);
    //     std::this_thread::sleep_for(sleepTime);
    // }

    std::cout << "[End]\tQuitting" << std::endl;
    return 0;
}