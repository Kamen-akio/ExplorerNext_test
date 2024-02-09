#pragma once
#include "../common.h"
#include "registry.h"
#include "windowCompositionAttribute.h"
#include <winrt/windows.ui.viewmanagement.h>

static inline bool IsWindows11();
void EnableArcylic(HWND, DWORD = NULL);