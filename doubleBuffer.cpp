#include "doubleBuffer.h"

Gdiplus::DoubleBuffer::DoubleBuffer(HWND hWnd) {
  RECT rcWnd{};
  GetWindowRect(hWnd, &rcWnd);
  _szWnd = {rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top};
  _hWnd = hWnd;
  _hVirtualDC = CreateCompatibleDC(NULL);

  // _hVirtualBitmap = CreateCompatibleBitmap(_hVirtualDC, _szWnd.cx, _szWnd.cy);
  BITMAPINFO bitmapInfo{};
  bitmapInfo.bmiHeader.biBitCount = 32;
  bitmapInfo.bmiHeader.biCompression = 0;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biSize = 40;
  bitmapInfo.bmiHeader.biWidth = _szWnd.cx;
  bitmapInfo.bmiHeader.biHeight = _szWnd.cy;

  _hVirtualBitmap =
      CreateDIBSection(_hVirtualDC, &bitmapInfo, DIB_RGB_COLORS, nullptr, 0, 0);

  _hLastVirtualBitmap = (HBITMAP)SelectObject(_hVirtualDC, _hVirtualBitmap);
};

void Gdiplus::DoubleBuffer::Flush() {
  auto hWndDC = GetDC(_hWnd);
  POINT zeroPoint({0, 0});

  // auto b = BitBlt(hWndDC, 0, 0, _szWnd.cx, _szWnd.cy, _hVirtualDC, 0, 0,
  // SRCCOPY);

  BLENDFUNCTION blendFunction;
  blendFunction.AlphaFormat = AC_SRC_ALPHA;
  blendFunction.BlendFlags = 0;
  blendFunction.BlendOp = AC_SRC_OVER;
  blendFunction.SourceConstantAlpha = 255;

  // AlphaBlend(hWndDC, 0, 0, _szWnd.cx, _szWnd.cy, _hVirtualDC, 0, 0,
  // _szWnd.cx, _szWnd.cy, blendFunction);
  RECT rcWnd{};
  GetWindowRect(_hWnd, &rcWnd);
  POINT psWnd{rcWnd.left, rcWnd.top};
  SIZE szWnd{rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top};
  auto b = UpdateLayeredWindow(_hWnd, hWndDC, &psWnd, &szWnd, _hVirtualDC,
                               &zeroPoint, 0, &blendFunction, ULW_ALPHA);
  
  ReleaseDC(_hWnd, hWndDC);
}

void Gdiplus::DoubleBuffer::FlushResize(Size szWnd) {
  SelectObject(_hVirtualDC, _hLastVirtualBitmap);
  DeleteObject(_hVirtualBitmap);

  BITMAPINFO bitmapInfo{};
  bitmapInfo.bmiHeader.biBitCount = 32;
  bitmapInfo.bmiHeader.biCompression = 0;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biSize = 40;
  bitmapInfo.bmiHeader.biWidth = _szWnd.cx;
  bitmapInfo.bmiHeader.biHeight = _szWnd.cy;

  _hVirtualBitmap =
      CreateDIBSection(_hVirtualDC, &bitmapInfo, DIB_RGB_COLORS, nullptr, 0, 0);

  _hLastVirtualBitmap = (HBITMAP)SelectObject(_hVirtualDC, _hLastVirtualBitmap);
}

HDC Gdiplus::DoubleBuffer::GetVirtualDC() const {
  return _hVirtualDC;
}

HBITMAP Gdiplus::DoubleBuffer::GetVirtualBitmap() const {
  return _hVirtualBitmap;
}

Gdiplus::DoubleBuffer::~DoubleBuffer() {
  SelectObject(_hVirtualDC, _hLastVirtualBitmap);
  DeleteObject(_hVirtualBitmap);
  DeleteDC(_hVirtualDC);

  _hVirtualDC = NULL;
  _hLastVirtualBitmap = _hVirtualBitmap = NULL;
}