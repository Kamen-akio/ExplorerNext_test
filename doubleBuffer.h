#pragma once

#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Msimg32.lib")

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
  void FlushResize(Size);

 private:
  HWND _hWnd{};
  SIZE _szWnd{};
  HDC _hVirtualDC{};
  HBITMAP _hVirtualBitmap{};
  HBITMAP _hLastVirtualBitmap{};
};

}  // namespace Gdiplus

#endif  // !_DOUBLE_BUFFER_H_
