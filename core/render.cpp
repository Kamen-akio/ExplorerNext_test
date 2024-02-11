#include "render.h"

// Gdiplus Render

static ULONG_PTR gdiplusToken{};

static HWND hRenderWindow;
static MutliTree* RenderTree;
static DoubleBuffer* RenderContext;

// Com

static ITaskbarList3* pTaskbarList{};

static bool bProcReturn = false;
inline static void WndProcReturn() {
  bProcReturn = true;
};

static void WindowInitialize(HWND hWnd) {
#if defined(USE_BLUR) or defined(USE_BLUR_AUTO)

  EnableArcylic(hWnd);

#endif  // defined(USE_BLUR) or defined(USE_BLUR_AUTO)

  hRenderWindow = hWnd;

  pTaskbarList->HrInit();
  pTaskbarList->RegisterTab(hWnd, hWnd);

  RenderTree = new MutliTree();
  RenderContext = new DoubleBuffer(hWnd);
}

LRESULT __stdcall CoreRender::WindowProc(HWND hWnd,
                                         UINT uMsg,
                                         WPARAM wParam,
                                         LPARAM lParam) {
  static POINT ptMouse{};

  if (uMsg == WM_CREATE) {
    WindowInitialize(hWnd);
  }

  // Handle window rect is changed.

  if (uMsg == WM_MOVE) {
    RenderContext->FlushPos({LOWORD(lParam), HIWORD(lParam)});
  }

  if (uMsg == WM_SIZE) {
    RenderContext->FlushSize({LOWORD(lParam), HIWORD(lParam)});
  }

  // Skip the WM ERASEBKGND message.

  if (uMsg == WM_ERASEBKGND) {
    WndProcReturn();
  }

  // Respond to system theme changes

#ifdef USE_BLUR_AUTO

  if (uMsg == WM_DWMCOLORIZATIONCOLORCHANGED) {
    EnableArcylic(hWnd);
    WndProcReturn();
  }

#endif  // USE_BLUR_AUTO

  if (uMsg == WM_MOUSEMOVE) {
    ptMouse = {LOWORD(lParam), HIWORD(lParam)};
  }

  auto result = CoreLogic::WindowProc(hWnd, uMsg, wParam, lParam);
  if (CoreLogic::IsProcessed()) {
    WndProcReturn();
    return result;
  }

  return NULL;
}

void CoreRender::Initialize() {
  GdiplusStartupInput gdiplusStartupInput{};
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

  if (CoInitialize(0) != S_OK)
    return;

  // Taskbar

  if (CoCreateInstance((const IID)CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER,
                       IID_ITaskbarList3, (void**)&pTaskbarList))
    return;
}

void CoreRender::UnInitialize() {
  GdiplusShutdown(gdiplusToken);

  pTaskbarList->UnregisterTab(hRenderWindow);
  if (pTaskbarList != nullptr) {
    pTaskbarList->Release();
    pTaskbarList = nullptr;
  }

  CoUninitialize();
}

bool _stdcall CoreRender::IsProcessed() {
  if (bProcReturn) {
    bProcReturn = false;
    return true;
  }

  return false;
}