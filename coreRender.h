#pragma once

#define GDIPVER 0x0110

#include <Windows.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <ShObjIdl.h>

#include "doubleBuffer.h"

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

#ifndef _CORE_RENDER_H_
#define _CORE_RENDER_H_


namespace CoreRender {
void Initialize();
void UnInitialize();
LRESULT __stdcall CoreRender_WindowProc(HWND hWnd,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam);
bool __stdcall CoreRender_WndProcShouldReturn();
}


#endif  // !_CORE_RENDER_H_
