#include "render.h"
#include "../test.h"

HWND hRenderWindow;
ULONG_PTR gdipToken{};
DoubleBuffer* RenderScreen;

ITaskbarList3* pTaskbarList{};

IMMDeviceEnumerator* pAudioDeviceEnumerator{};
IMMDevice* pAudioEndpoint{};
IAudioMeterInformation* pAudioMeterInfo{};

TESTRENDER* testtest{};

bool bProcReturn = false;
static void WndProcReturn() {
  bProcReturn = true;
}

void CoreRender::Initialize() {
  GdiplusStartupInput gdiplusStartupInput{};
  GdiplusStartup(&gdipToken, &gdiplusStartupInput, nullptr);

  if (CoInitialize(0) != S_OK)
    return;

  // Taskbar

  if (CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER,
                       IID_ITaskbarList3, (void**)&pTaskbarList))
    return;

  // Audio

  if (CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
                       __uuidof(IMMDeviceEnumerator),
                       (void**)&pAudioDeviceEnumerator))
    return;

  if (pAudioDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole,
                                                      &pAudioEndpoint))
    return;

  if (pAudioEndpoint->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL,
                               NULL, (void**)&pAudioMeterInfo))
    return;
}

void CoreRender::UnInitialize() {
  GdiplusShutdown(gdipToken);

  pTaskbarList->UnregisterTab(hRenderWindow);
  if (pTaskbarList != nullptr) {
    pTaskbarList->Release();
    pTaskbarList = nullptr;
  }

  if (pAudioDeviceEnumerator != nullptr) {
    pAudioDeviceEnumerator->Release();
    pAudioDeviceEnumerator = nullptr;
  }

  if (pAudioEndpoint != nullptr) {
    pAudioEndpoint->Release();
    pAudioEndpoint = nullptr;
  }

  if (pAudioMeterInfo != nullptr) {
    pAudioMeterInfo->Release();
    pAudioMeterInfo = nullptr;
  }
  CoUninitialize();
}

bool _stdcall CoreRender::CoreRender_IsProcessed() {
  if (bProcReturn) {
    bProcReturn = false;
    return true;
  }

  return false;
}

static void OnWindowCreate(HWND hWnd) {
  EnableArcylic(hWnd);
  hRenderWindow = hWnd;

  pTaskbarList->HrInit();
  pTaskbarList->RegisterTab(hWnd, hWnd);

  RenderScreen = new DoubleBuffer(hWnd);

  SetTimer(hWnd, TIMER_GENERAL, 1000, nullptr);
  SetTimer(hWnd, TIMER_RENDERLOOP, USER_TIMER_MINIMUM, nullptr);

  // test //
  testtest = new TESTRENDER(hWnd, RenderScreen);
}

static void PaintFps(Gdiplus::Graphics* grap, short fps) {
  Font font(L"Segoe UI", 16);
  SolidBrush brush(Color::White);

  auto output = std::to_wstring(fps);
  output = (L"Fps: " + output + L"\0");
  grap->DrawString(output.c_str(), output.length(), &font, PointF(0, 0),
                   &brush);
}
static void PaintFun(Gdiplus::Graphics* grap) {
  float volume{};
  pAudioMeterInfo->GetPeakValue(&volume);

  static float lastWidth = 0;
  lastWidth = lastWidth + (volume * volume - lastWidth) * 0.1;

  SolidBrush brush(Color(255, 255, 255 * volume));
  grap->FillRectangle(&brush, 0, 250, (int)(800 * lastWidth), 16);

  Font font(L"Segoe UI", 16);
  brush.SetColor(Color::AliceBlue);
  auto output = L"Volume: " + std::to_wstring(std::floor(volume * 100)) + L"%";
  grap->DrawString(output.c_str(), output.length(), &font, PointF(0, 210),
                   &brush);
};

LRESULT __stdcall CoreRender::CoreRender_WindowProc(HWND hWnd,
                                                    UINT uMsg,
                                                    WPARAM wParam,
                                                    LPARAM lParam) {
  static bool bInit = false;
  static short nFps = 0;
  static short nLastFps = 0;

  static POINT ptMouse{};

  if (uMsg == WM_CREATE) {
    OnWindowCreate(hWnd);
    bInit = true;
  }

  if (uMsg == WM_MOVE) {
    RenderScreen->FlushPos({LOWORD(lParam), HIWORD(lParam)});
  }

  if (uMsg == WM_SIZE) {
    RenderScreen->FlushSize({LOWORD(lParam), HIWORD(lParam)});
  }

  if (uMsg == WM_ERASEBKGND) {
    WndProcReturn();
  }

  if (uMsg == WM_DWMCOLORIZATIONCOLORCHANGED) {
    EnableArcylic(hWnd);
    WndProcReturn();
  }

  if (uMsg == WM_TIMER) {
    auto grap = Gdiplus::Graphics(RenderScreen->GetVirtualDC());
    grap.SetSmoothingMode(SmoothingModeHighQuality);

    grap.Clear(Color(11, 55, 11, 173));

    if (wParam == TIMER_GENERAL) {
      nLastFps = nFps;
      nFps = 0;
    }
    if (wParam == TIMER_RENDERLOOP) {
      nFps++;

      PaintFps(&grap, nLastFps);
      PaintFun(&grap);
      testtest->Render(grap);

      RenderScreen->Flush();
    }
  }

  if (uMsg == WM_MOUSEMOVE) {
    ptMouse = {LOWORD(lParam), HIWORD(lParam)};
  }

  return NULL;
}