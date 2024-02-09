#pragma once
#include "../common.h"

#include <initguid.h>
#include <ShObjIdl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include "../utils/interface.h"
#include "gdiplus_ext/doubleBuffer.h"

using namespace Gdiplus;

#ifndef _CORE_RENDER_H_
#define _CORE_RENDER_H_

#define TIMER_GENERAL 0x01
#define TIMER_RENDERLOOP 0x02

namespace CoreRender {
void Initialize();
void UnInitialize();
LRESULT __stdcall CoreRender_WindowProc(HWND hWnd,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam);
bool __stdcall CoreRender_IsProcessed();
}


#endif  // !_CORE_RENDER_H_
