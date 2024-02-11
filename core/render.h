#pragma once
#include "../common.h"

#include <initguid.h>
#include <ShObjIdl.h>

#include "../utils/interface.h"
#include "gdiplus_ext/doubleBuffer.h"

#include "logic.h"

using namespace Gdiplus;

#ifndef _CORE_RENDER_H_
#define _CORE_RENDER_H_

namespace CoreRender {
void Initialize();
void UnInitialize();
LRESULT __stdcall WindowProc(HWND hWnd,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam);
bool __stdcall IsProcessed();
}


#endif  // !_CORE_RENDER_H_
