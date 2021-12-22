#include <iostream>
#include <chrono>
#include <thread>

#include "ScreenCapture/ScreenCaptureFactory.h"
#include "SerialArduino/SerialArduinoFactory.h"
#include "LEDstrip/LEDstrip.h"

/**
 * @brief Transcribe a command line argument into an Int
 * 
 * @param argv const char* input
 * @return int number output
 */
int argToInt(const char* argv) {
    std::string arg = argv;
    try {
        std::size_t pos;
        int x = std::stoi(arg, &pos);
        if (pos < arg.size()) {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
        return x;
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n' << ex.what() << '\n';
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n' << ex.what() << '\n';
    }
    return -1;
}
/**
 * @brief Transcribe a command line argument into a float
 * 
 * @param argv const char* input
 * @return float number output
 */
float argToFloat(const char* argv) {
    std::string arg = argv;
    try {
        std::size_t pos;
        float x = std::stof(arg, &pos);
        if (pos < arg.size()) {
            std::cerr << "Trailing characters after number: " << arg << '\n';
        }
        return x;
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n' << ex.what() << '\n';
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n' << ex.what() << '\n';
    }
    return -1.0;
}

int main(int argc, const char* argv[]) {
    std::cout << "[Begin]\tStarting " << argv[0] << std::endl;
    if (argc != 10) {
        std::cout << "/!\\---------------------------------------------------------------------------------------------\n";
        std::cerr << "Incorrect number of arguments given.\nUsage :\n";
        std::cout << "1- Screen number (starts at 0)\n2- Screen width resolution\n3- Screen height resolution\n4- Number of LEDs in total\n5- Number of LEDs on top of the screen\n6- Number of LEDs on each side of the screen\n7- Arduino COM port\n8- Capture frame rate\n9- Capture zone aspect ratio\n";
        std::cout << "Using default parameters : 0, 1920, 1080, 60, 30, 15, COM3, 30, 1.78\n";
        std::cout << "/!\\---------------------------------------------------------------------------------------------\n\n";
        const char* arg[] = {argv[0], "0", "1920", "1080", "60", "30", "16", "COM3", "30", "1.78"};
        argv = arg;
    }

    std::cout << "[1]\tReading parameters ...\n";
    // Screen number
	int numScreen = argToInt(argv[1]);
    // Screen X res
    int screenX = argToInt(argv[2]);
    // Screen Y res
    int screenY = argToInt(argv[3]);
    // LED nb total
    int ledNbTot = argToInt(argv[4]);
    // LED nb top
    int ledNbX = argToInt(argv[5]);
    // LED nb side
    int ledNbY = argToInt(argv[6]);
    // Arduino COM port
    std::string port("\\\\.\\");
    port.append(argv[7]);
    // Framerate
    std::chrono::milliseconds sleepTime((int)(1000/(argToFloat(argv[8]))));
    // Aspect ratio
	float ratio = argToFloat(argv[9]);

    std::cout << "[2]\tConnection to the Arduino on port " << port << "...\n";
    SerialArduino* arduino = SerialArduinoFactory::Create(port.c_str());
	if (arduino->isConnected()) {
		std::cout << "Arduino connected.\n\n";
	} else {
		std::cout << "/!\\ Connexion to Arduino failed.\nQuitting.\n";
		//exit(1);
	}

    std::cout << "[3]\tInitializing the LED strip ...\n";
    LEDstrip ledStrip(screenX, screenY, ledNbTot, ledNbX, ledNbY, ratio);

    std::cout << "[4]\tInitializing the Screen capture ...\n";
    ScreenCapture* sc = ScreenCaptureFactory::Create(numScreen);
    std::string initError = sc->initialize();
    if (initError.length() > 0) {
        std::cout << "ERROR: " << initError << '\n';
        exit(1);
    }

    std::cout << "[5]\tApp initialized.\nStarting to capture the screen and sending the data.\n";

    // while(true) {
        std::cout << "capture frame : " << sc->captureNext() << '\n';
        if (sc->getScreenData()->size() != (1920*1080*4)) {
            std::cout << "ERROR:\tcapture not size of screen\n";
            std::cout << (1920*1080*4) << ' ' << sc->getScreenData()->size() << '\n';
        } else {
            std::cout << "compute colours\n";
            char * serialData = ledStrip.computeColours(sc->getScreenData());
        
    //     std::cout << "send to arudino\n";
    //     arduino->writeData(serialData, args[2]*3+2);
    //     std::this_thread::sleep_for(sleepTime);
        }
    // }

    std::cout << "[End]\tQuitting" << std::endl;
    return 0;
}