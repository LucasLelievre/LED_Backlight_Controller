#include <iostream>
#include <chrono>
#include <thread>

#include "ScreenCapture/ScreenCaptureFactory.h"
#include "SerialArduino/SerialArduinoFactory.h"
#include "LEDstrip/LEDstrip.h"

template <typename T>
void scanArg(const char* buffer, const char* format, T* output) {
    #ifdef _WIN32
        sscanf_s(buffer, format, output);
    #else
        sscanf(buffer, format, output);
    #endif
}

int main(int argc, const char* argv[]) {
    if (argc != 10) {
        std::cerr << "Incorrect number of arguments given.\nUsage :\n";
        std::cout << "1- Screen number (starts at 0)\n2- Screen width resolution\n3- Screen height resolution\n4- Number of LEDs in total\n5- Number of LEDs on top of the screen\n6- Number of LEDs on each side of the screen\n7- Arduino COM port\n8- Capture frame rate\n9- Capture zone aspect ratio\n";
        // std::cout << "Using default parameters : 0, 1920, 1080, 60, 30, 15, 5, 30, 1.78\n";
        //TODO default parameters
        exit(1);
    }

    std::cout << argv[0] << "Reading paramters ...\n";
    // Screen number
	int numScreen;
	//sscanf(argv[1], "%d", &numScreen);
    scanArg(argv[1], "%d", &numScreen);
    // Framerate
	float frameRate;
	// sscanf(argv[8], "%f", &frameRate);
    scanArg(argv[8], "%f", &frameRate);
	// translate the number of images per second to the number of milliseconds needed to wait to acheive the framerate
	frameRate = (1000 / frameRate);
    std::chrono::milliseconds sleepTime((int)frameRate);

    // Screen size and LEDs number
	int args[5];
	for (int i = 0; i < 5; i++)
        scanArg(argv[i+2], "%d", &args[1]);
		// sscanf(argv[i+2], "%d", &args[i]);
    // Aspect ratio
	float ratio;
    scanArg(argv[9], "%f", &ratio);
	// sscanf(argv[9], "%f", &ratio);
    // Arduino COM port
    std::string port = "\\\\.\\";
    port.append(argv[7]);


    std::cout << "Initializing the LED strip ...\n";
    LEDstrip ledStrip(args, ratio);

    std::cout << "Initializing the Screen capture ...\n";
    ScreenCapture* sc = ScreenCaptureFactory::Create();
    sc->initialize();


    std::cout << "Connection to the Arduino on port " << port << "...\n";
    //TODO arduino class
    SerialArduino* arduino = SerialArduinoFactory::Create(port.c_str());
	if (arduino->isConnected()) {
		std::cout << "Arduino connected.\n\n";
	} else {
		std::cout << "Connexion to Arduino failed.\nQuitting.";
		exit(1);
	}

    std::cout << "App initialized.\nStarting to capture the screen and sending the data.\n";

    while(true) {
        sc->captureNext();
        char * serialData = ledStrip.computeColours(sc->getScreenData());
        arduino->writeData(serialData, args[2]*3+2);
        std::this_thread::sleep_for(sleepTime);
    }

    std::cout << "Quiting" << std::endl;
    return 0;
}