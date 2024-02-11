#pragma once
#include "interface/render.h"
#define ________

#ifndef ________
#define ________

class TESTRENDER final : RenderBase {
 public:

  TESTRENDER(HWND a, Gdiplus::DoubleBuffer* b) : RenderBase(a, b) { }
  void Layout(Gdiplus::Graphics&);
};

#endif  // !________
