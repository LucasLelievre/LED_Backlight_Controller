cmake_minimum_required(VERSION 3.0.0)
project(LED_Backlight_Controller VERSION 0.3.0)

include(CTest)
enable_testing()

add_compile_options(-Wall -Wextra -pedantic)

# src folder
set (SRC_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
# Add the cpp files
set (SRC_FILES
    ${SRC_FOLDER}/main.cpp
    ${SRC_FOLDER}/LEDstrip/LEDstrip.cpp)
# Add the correct file based on system
if(WIN32)
    message("Win32 detected.")
    list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureWindows.cpp)
    list(APPEND SRC_FILES ${SRC_FOLDER}/SerialArduino/SerialArduinoWindows.cpp)
elseif(UNIX)
    message("UNIX detected")
    list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureLinuxX11.cpp)
    list(APPEND SRC_FILES ${SRC_FOLDER}/SerialArduino/SerialArduinoLinux.cpp)
endif()

add_executable(LED_Backlight_Controller ${SRC_FILES})

# Link the libraries
if(WIN32)
elseif(UNIX)
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        message("x11 added")
        message("${X11_LIBRARIES}")
        target_link_libraries(LED_Backlight_Controller "${X11_LIBRARIES}")
    else()
        message("ERROR: x11 not found")
    endif(X11_FOUND)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
