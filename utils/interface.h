#pragma once
#include "../common.h"

#include <winrt/windows.ui.viewmanagement.h>
#include "mutliTree.h"
#include "registry.h"
#include "windowCompositionAttribute.h"

static inline bool IsWindows11();
void EnableArcylic(HWND, DWORD = NULL);