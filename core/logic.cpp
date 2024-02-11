#include "logic.h"

static bool bProcReturn = false;
inline static void LogicReturn() {
  bProcReturn = true;
};

static SIZE szWnd{};
static POINT posWnd{};

int ProcessHitTestLogic(POINT ptMouse, POINT posWnd, SIZE szWnd);

LRESULT __stdcall CoreLogic::WindowProc(HWND hWnd,
                                        UINT uMsg,
                                        WPARAM wParam,
                                        LPARAM lParam) {
  if (uMsg == WM_MOVE) {
    posWnd.x = GET_X_LPARAM(lParam);
    posWnd.y = GET_Y_LPARAM(lParam);
  }

  if (uMsg == WM_SIZE) {
    szWnd.cx = LOWORD(lParam);
    szWnd.cy = HIWORD(lParam);
  }

  if (uMsg == WM_NCHITTEST) {
    LogicReturn();
    return ProcessHitTestLogic({GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)},
                               posWnd, szWnd);
  }

  return NULL;
};

static int ProcessHitTestLogic(POINT ptMouse, POINT posWnd, SIZE szWnd) {
  ptMouse = {ptMouse.x - posWnd.x, ptMouse.y - posWnd.y};
  // LEFT-(TOP/BOTTOM)

  if (ptMouse.x <= 8) {
    if (ptMouse.y <= 8)  // LT
      return HTTOPLEFT;

    if (ptMouse.y >= szWnd.cy - 8)  // LB
      return HTBOTTOMLEFT;

    // L

    return HTLEFT;
  }

  // RIGHT-(TOP/BOTTOM)

  if (ptMouse.x >= szWnd.cx - 8) {
    if (ptMouse.y <= 8)  // RT
      return HTTOPRIGHT;

    if (ptMouse.y >= szWnd.cy - 8)  // RB
      return HTBOTTOMRIGHT;

    // R

    return HTRIGHT;
  }

  // TOP-(CAPTIAN/CLIENT/BOTTOM)

  if (ptMouse.y <= 8)  // T
    return HTTOP;

  if (ptMouse.y <= 30)  // TC
    return HTCAPTION;

  if (ptMouse.y >= szWnd.cy - 8)  // TB
    return HTBOTTOM;

  // TC

  return HTCLIENT;
}

bool CoreLogic::IsProcessed() {
  if (bProcReturn) {
    bProcReturn = false;
    return true;
  }

  return false;
}
