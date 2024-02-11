#pragma once
#include "../common.h"

#ifndef _CORE_LOGIC_H_
#define _CORE_LOGIC_H_

namespace CoreLogic {
LRESULT __stdcall WindowProc(HWND hWnd,
                             UINT uMsg,
                             WPARAM wParam,
                             LPARAM lParam);
bool __stdcall IsProcessed();
}

#endif  // !_CORE_LOGIC_H_
