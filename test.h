#pragma once
#include "interface/render.h"

#ifndef ________
#define ________

class TESTRENDER final : RenderBase {
 public:

  TESTRENDER(HWND a, Gdiplus::DoubleBuffer* b) : RenderBase(a, b) { }
  void Render(Gdiplus::Graphics&);
};

#endif  // !________
