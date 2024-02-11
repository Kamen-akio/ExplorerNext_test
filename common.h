#pragma once

#ifdef GDIPVER
#undef GDIPVER
#endif  // GDIPVER

#define GDIPVER 0x0110

#include <Windows.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <windowsx.h>

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")

#include "core/env.h"