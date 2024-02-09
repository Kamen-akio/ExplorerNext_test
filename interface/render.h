#pragma once
#include "../common.h"
#include "../core/gdiplus_ext/doubleBuffer.h"

#ifndef _TEMPLATE_RENDER_H_
#define _TEMPLATE_RENDER_H_

class RenderBase {
 public:
  RenderBase(HWND hWnd, Gdiplus::DoubleBuffer* db) {
    _hWnd = hWnd;
    renderContext = db;
  }

 virtual void Render(Gdiplus::Graphics&){};

 private:
  HWND _hWnd{};
  SIZE _szWnd{};
  POINT _posWnd{};

  Gdiplus::DoubleBuffer* renderContext;
};

#endif  // !_TEMPLATE_RENDER_H_
