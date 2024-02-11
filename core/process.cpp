#include "process.h"

inline const auto WND_CLASS = L"explorer_next";
inline const auto WND_TITLE = L"test";

static void CenterWindow(HWND hWnd, SIZE szWnd) {
  const SIZE szScreen{GetSystemMetrics(SM_CXSCREEN),
                      GetSystemMetrics(SM_CYSCREEN)};

  SetWindowPos(hWnd, NULL, (szScreen.cx - szWnd.cx) * 0.5,
               (szScreen.cy - szWnd.cy) * 0.5, szWnd.cx, szWnd.cy,
               SWP_NOOWNERZORDER | SWP_NOZORDER);
}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND InitMainWindow(HINSTANCE hInst, PWSTR lpCmdLine, int nCmdShow) {
  HWND hWnd{};
  WNDCLASSEXW wcex{};

  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.cbClsExtra = CS_OWNDC;
  wcex.hInstance = hInst;
  wcex.lpfnWndProc = WndProc;
  wcex.lpszClassName = WND_CLASS;

  if (RegisterClassEx(&wcex) == NULL)
    return NULL;

  CoreRender::Initialize();

  hWnd =
      CreateWindowEx(WS_EX_LAYERED, WND_CLASS, WND_TITLE, WS_VISIBLE | WS_POPUP,
                     0, 0, 800, 600, NULL, NULL, hInst, NULL);

  CenterWindow(hWnd, {800, 600});
  ShowWindow(hWnd, nCmdShow);

  return hWnd;
}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (uMsg == WM_CLOSE) {
    CoreRender::UnInitialize();
    DestroyWindow(hWnd);
    return NULL;
  }

  if (uMsg == WM_DESTROY) {
    PostQuitMessage(0);
    return NULL;
  }

  auto result = CoreRender::WindowProc(hWnd, uMsg, wParam, lParam);
  if (CoreRender::IsProcessed()) {
    return result;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}