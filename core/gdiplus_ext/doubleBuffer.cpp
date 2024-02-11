#include "doubleBuffer.h"

static HBITMAP CreateMemoryBitmap(HDC hDC, RECT rcWnd) {
  static HBITMAP hLastBitmap = nullptr;

  if (hLastBitmap != nullptr) {
    DeleteObject(SelectObject(hDC, hLastBitmap));
  }

  BITMAPINFO bitmapInfo{};
  bitmapInfo.bmiHeader.biBitCount = 32;
  bitmapInfo.bmiHeader.biCompression = 0;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biSize = 40;
  bitmapInfo.bmiHeader.biWidth = rcWnd.right - rcWnd.left;
  bitmapInfo.bmiHeader.biHeight = rcWnd.bottom - rcWnd.top;

  const auto hNewBitmap =
      CreateDIBSection(hDC, &bitmapInfo, DIB_RGB_COLORS, nullptr, 0, 0);

  return hLastBitmap = (HBITMAP)SelectObject(hDC, hNewBitmap);
}

// init

Gdiplus::DoubleBuffer::DoubleBuffer(HWND hWnd) {
  RECT rcWnd{};
  GetWindowRect(hWnd, &rcWnd);

  _hWnd = hWnd;
  _szWnd = {rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top};
  _posWnd = {rcWnd.left, rcWnd.top};
  _hVirtualDC = CreateCompatibleDC(NULL);

  _hLastVirtualBitmap = CreateMemoryBitmap(_hVirtualDC, rcWnd);
  GetObject(_hVirtualDC, sizeof(BITMAP), &_hVirtualBitmap);
};

Gdiplus::DoubleBuffer::~DoubleBuffer() {
  SelectObject(_hVirtualDC, _hLastVirtualBitmap);
  DeleteObject(_hVirtualBitmap);
  DeleteDC(_hVirtualDC);

  _hVirtualDC = NULL;
  _hLastVirtualBitmap = _hVirtualBitmap = NULL;
}

// flush

void Gdiplus::DoubleBuffer::Flush() {
  HDC hWndDC = GetDC(_hWnd);
  POINT zeroPoint({0, 0});
  BLENDFUNCTION blendFunction{};

  blendFunction.AlphaFormat = AC_SRC_ALPHA;
  blendFunction.BlendFlags = 0;
  blendFunction.BlendOp = AC_SRC_OVER;
  blendFunction.SourceConstantAlpha = 255;
  UpdateLayeredWindow(_hWnd, hWndDC, &_posWnd, &_szWnd, _hVirtualDC, &zeroPoint,
                      0, &blendFunction, ULW_ALPHA);

  ReleaseDC(_hWnd, hWndDC);
}

void Gdiplus::DoubleBuffer::FlushPos(POINT posWnd) {
  _posWnd = posWnd;
}

void Gdiplus::DoubleBuffer::FlushSize(SIZE szWnd) {
  _szWnd = szWnd;
  _hLastVirtualBitmap =
      CreateMemoryBitmap(_hVirtualDC, {0, 0, szWnd.cx, szWnd.cy});
  GetObject(_hVirtualDC, sizeof(BITMAP), &_hVirtualBitmap);
}

// Get

HDC Gdiplus::DoubleBuffer::GetVirtualDC() const {
  return _hVirtualDC;
}

HBITMAP Gdiplus::DoubleBuffer::GetVirtualBitmap() const {
  return _hVirtualBitmap;
}
