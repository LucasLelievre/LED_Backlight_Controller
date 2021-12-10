cmake_minimum_required(VERSION 3.0.0)
project(LED_Backlight_Controller VERSION 0.3.0)

include(CTest)
enable_testing()

# src folder
set (SRC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
# Add the cpp files
set (SRC_FILES
    ${SRC_FOLDER}/main.cpp
    ${SRC_FOLDER}/LEDstrip/LEDstrip.cpp)
# Add the correct file based on system
if(WIN32)
    list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureWindows.cpp)
    list(APPEND SRC_FILES ${SRC_FOLDER}/SerialArduino/SerialArduinoWindows.cpp)
else()
    list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureLinux.cpp)
    list(APPEND SRC_FILES ${SRC_FOLDER}/SerialArduino/SerialArduinoLinux.cpp)
endif()

add_executable(LED_Backlight_Controller ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
