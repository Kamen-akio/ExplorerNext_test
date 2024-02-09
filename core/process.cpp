#include "process.h"

const auto WND_CLASS = L"explorer_next";
const auto WND_TITLE = L"test";

LRESULT __stdcall MainWndProc(HWND hWnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam);

HWND InitMainWindow(HINSTANCE hInst, PWSTR lpCmdLine, int nCmdShow) {
  HWND hWnd{};
  WNDCLASSEXW wcex{};

  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.cbClsExtra = CS_OWNDC;
  wcex.hInstance = hInst;
  wcex.lpfnWndProc = MainWndProc;
  wcex.lpszClassName = WND_CLASS;

  if (RegisterClassEx(&wcex) == NULL)
    return NULL;

  CoreRender::Initialize();

  hWnd = CreateWindowEx(WS_EX_LAYERED, WND_CLASS, WND_TITLE,
                        WS_VISIBLE | WS_POPUP, (1920 - 800) / 2,
                        (1080 - 600) / 2, 800, 600, NULL, NULL, hInst, NULL);

  ShowWindow(hWnd, nCmdShow);

  return hWnd;
}

LRESULT __stdcall MainWndProc(HWND hWnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam) {

  if (uMsg == WM_CLOSE) {
    CoreRender::UnInitialize();
    DestroyWindow(hWnd);
    return NULL;
  }

  if (uMsg == WM_DESTROY) {
    PostQuitMessage(0);
    return NULL;
  }

  auto result = CoreRender::CoreRender_WindowProc(hWnd, uMsg, wParam, lParam);
  if (CoreRender::CoreRender_IsProcessed()) {
    return result;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}