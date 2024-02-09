#pragma once
#include "common.h"
#include "./core/gdiplus_ext/doubleBuffer.h"

#ifndef _INTERFACE_GENERAL_H_
#define _INTERFACE_GENERAL_H_

namespace TypeDefine {

typedef struct __tagProcessInstance {
  HWND hWnd;
  SIZE szWnd;
  POINT posWnd;
  Gdiplus::DoubleBuffer* renderContext;
} ProcessInstance, ProcInst;

}  // namespace TypeDefine

#endif  // !_INTERFACE_GENERAL_H_
