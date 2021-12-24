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
    message("UNIX detected.")
    list(APPEND SRC_FILES ${SRC_FOLDER}/SerialArduino/SerialArduinoLinux.cpp)

    # Detect whether X11 or Wayland is used
        # get session name
    execute_process(COMMAND whoami OUTPUT_VARIABLE session_name)
    string(REPLACE "\n" "" session_name ${session_name})
        # get session id
    execute_process(COMMAND loginctl
                    COMMAND grep ${session_name}
                    COMMAND awk "{print $1}"
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    OUTPUT_VARIABLE session_id)
    string(REPLACE "\n" "" session_id ${session_id})
        # get session type
    execute_process(COMMAND loginctl show-session ${session_id} -p Type
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE display_server)
    string(REPLACE "\n" "" display_server ${display_server})

    #link the correct libraries
    if (display_server STREQUAL "Type=x11")
        message("x11 detected.")
        set(display_server_x11 TRUE)
        list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureLinuxX11.cpp)
    elseif(display_server STREQUAL "Type=wayland")
        message("wayland detected.")
        set(display_server_wayland TRUE)
        list(APPEND SRC_FILES ${SRC_FOLDER}/ScreenCapture/ScreenCaptureLinuxWayland.cpp)
    else()
        message("Windowing system unsuported.")
    endif()
else()
    message("unsupported OS.")
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link the libraries
if(WIN32)
    FIND_PATH(DX_INCLUDE_PATH d3d11.h     PATHS     "$ENV{DXSDK_DIR}/Include" "C:/Program Files (x86)/Microsoft DirectX SDK/Include"     DOC "The directory where D3D11.h resides")  
    find_library(D3D11_LIBRARY d3d11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3d11.lib resides")  
    set (D3D11_FOUND "YES") 
    set (D3D11_LIBRARIES ${D3D11_LIB}) 
    mark_as_advanced (D3D11_INCLUDE_PATH D3D11_LIB)  
    add_library(d3dx11.lib STATIC IMPORTED)
    target_link_libraries(${PROJECT_NAME} ${D3D11_LIBRARY})
    message("d3d11 added.")
elseif(UNIX)
    if (display_server_x11)
        find_package(X11 REQUIRED)
        if(X11_FOUND)
            message("x11 added.")
            ADD_DEFINITIONS("-D_X11LIBS")
            target_link_libraries(${PROJECT_NAME} "${X11_LIBRARIES}")
        else()
            message("ERROR: x11 not found.")
        endif(X11_FOUND)
    elseif(display_server_wayland)        
        if(WAYLAND_CLIENT_FOUND)
            message("wayland added.")
            ADD_DEFINITIONS("-D_WAYLANDLIBS")
            target_link_libraries(${PROJECT_NAME} "${WAYLAND_CLIENT_LIBRARY}")
        else()
            message("ERROR: wayland not found.")
        endif()
    endif()
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
