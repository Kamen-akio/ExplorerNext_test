#include "coreRender.h"

HWND hRenderWindow;
ULONG_PTR gdipToken{};
ITaskbarList3* pTaskbar{};

DoubleBuffer* RenderScreen;

bool bShouldReturn = false;

void WndRenderInit(HWND hWnd);

LRESULT __stdcall CoreRender::CoreRender_WindowProc(HWND hWnd,
                                                    UINT uMsg,
                                                    WPARAM wParam,
                                                    LPARAM lParam) {
  static bool bInit = false;

  if (uMsg == WM_CREATE) {
    WndRenderInit(hWnd);
    bInit = true;

    auto grap = Gdiplus::Graphics(RenderScreen->GetVirtualDC());
    grap.Clear(Color(11, 11, 11, 173));
    grap.~Graphics();
    RenderScreen->Flush();
  }

  if (uMsg == WM_SIZE) {
    RenderScreen->FlushResize({LOWORD(lParam), HIWORD(lParam)});
  }

  if (uMsg == WM_ERASEBKGND) {
    bShouldReturn = true;
    return NULL;
  }

  if (uMsg == WM_MOUSEMOVE) {
    auto grap = Gdiplus::Graphics(RenderScreen->GetVirtualDC());
    grap.Clear(Color(11, 11, 11, 173));

    SolidBrush brush(Color(255, 0, 255));
    Pen pen(&brush);
    POINT posMouse{LOWORD(lParam), HIWORD(lParam)};
    Rect rect{posMouse.x - 4, posMouse.y - 8, 8, 16};

    grap.FillRectangle(&brush, rect);
    grap.DrawLine(&pen, 0, 0, posMouse.x, posMouse.y);

    grap.Save();
    grap.Flush();
    grap.~Graphics();
    RenderScreen->Flush();
    // bShouldReturn = true;

    return NULL;
  }

  return NULL;
}

void WndRenderInit(HWND hWnd) {
  hRenderWindow = hWnd;

  // int _true = 1;
  // DwmSetWindowAttribute(hWnd, DWMWA_HAS_ICONIC_BITMAP, &_true, sizeof(_true));
  // DwmSetWindowAttribute(hWnd, DWMWA_FORCE_ICONIC_REPRESENTATION, &_true, sizeof(_true));

  pTaskbar->HrInit();
  pTaskbar->RegisterTab(hWnd, hWnd);

  RenderScreen = new DoubleBuffer(hWnd);
}

void CoreRender::Initialize() {
  GdiplusStartupInput gdiplusStartupInput{};
  GdiplusStartup(&gdipToken, &gdiplusStartupInput, nullptr);

  if (CoInitialize(0) != S_OK)
    return;

  if (CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER,
                       IID_ITaskbarList3, (void**)&pTaskbar))
    return;
}

void CoreRender::UnInitialize() {
  GdiplusShutdown(gdipToken);

  pTaskbar->UnregisterTab(hRenderWindow);
  CoUninitialize();
}

bool _stdcall CoreRender::CoreRender_WndProcShouldReturn() {
  if (bShouldReturn) {
    bShouldReturn = false;
    return true;
  }

  return false;
}