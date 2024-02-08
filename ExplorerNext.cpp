#include "ExplorerNext.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {

  const auto hWindow = InitMainWindow(hInstance, lpCmdLine, nCmdShow);
  if (hWindow == NULL)
    return -1;

  MSG msg{};
  while (GetMessage(&msg, NULL, 0, 0) > NULL) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return NULL;
}
