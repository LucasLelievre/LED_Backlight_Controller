#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>

#include "ScreenCapture.h"

// BGRA U8 Bitmap
struct Bitmap {
	int                  Width = 0;
	int                  Height = 0;
	std::vector<uint8_t> Buf;
};

class ScreenCaptureWindows : public ScreenCapture {
private:
	ID3D11Device*			D3DDevice = nullptr;
	ID3D11DeviceContext*	D3DDeviceContext = nullptr;
	IDXGIOutputDuplication* DeskDupl = nullptr;
	DXGI_OUTPUT_DESC        OutputDesc;
    Bitmap Latest;
	int    screenNumber;
	bool                    HaveFrameLock = false;
public:
    ScreenCaptureWindows(int screenNumber);
    ~ScreenCaptureWindows();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};