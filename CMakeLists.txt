cmake_minimum_required(VERSION 3.0.0)
project(LED_Backlight_Controller VERSION 0.3.0)

include(CTest)
enable_testing()

add_compile_options(-Wall -pedantic)

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
    FIND_PATH(DX_INCLUDE_PATH d3d11.h     PATHS     "$ENV{DXSDK_DIR}/Include" "C:/Program Files (x86)/Microsoft DirectX SDK/Include"     DOC "The directory where D3D11.h resides")  
    find_library(D3D11_LIBRARY d3d11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3d11.lib resides")  
    find_library(D3DX11_LIBRARY d3dx11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3dx11.lib resides") 
    set (D3D11_FOUND "YES") 
    set (D3D11_LIBRARIES ${D3D11_LIB}) 
    mark_as_advanced (D3D11_INCLUDE_PATH D3D11_LIB)  
    add_library(d3dx11.lib STATIC IMPORTED)
    target_link_libraries(${PROJECT_NAME} ${D3D11_LIBRARY} ${D3DX11_LIBRARY})
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
