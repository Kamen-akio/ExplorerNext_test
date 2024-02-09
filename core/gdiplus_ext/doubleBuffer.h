#pragma once
#include "../../common.h"

#ifndef _DOUBLE_BUFFER_H_
#define _DOUBLE_BUFFER_H_

namespace Gdiplus {

class DoubleBuffer {
 public:
  DoubleBuffer(HWND hWnd);
  ~DoubleBuffer();

  HDC GetVirtualDC() const;
  HBITMAP GetVirtualBitmap() const;

  void Flush();
  void FlushPos(POINT);
  void FlushSize(SIZE);

 private:
  HWND _hWnd{};
  SIZE _szWnd{};
  POINT _posWnd{};
  HDC _hVirtualDC{};
  HBITMAP _hVirtualBitmap{};
  HBITMAP _hLastVirtualBitmap{};
};

}  // namespace Gdiplus

#endif  // !_DOUBLE_BUFFER_H_
