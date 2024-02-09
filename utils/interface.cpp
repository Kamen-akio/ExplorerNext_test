#include "interface.h"
using namespace winrt::Windows::UI;

static inline bool IsColorLight(Color& clr) {
  return (((5 * clr.G) + (2 * clr.R) + clr.B) > (8 * 128));
}

static inline bool IsWindows11() {
  return Registry::GetValue(HKEY_LOCAL_MACHINE,
                            "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                            "CurrentBuild", nullptr)
             .ToInt() >= 22000;
}

void EnableArcylic(HWND hWnd, DWORD color) {
  auto themeColor = ViewManagement::UISettings().GetColorValue(
      ViewManagement::UIColorType::Background);

  COLORREF appearColor = color == NULL ? IsColorLight(themeColor)
                                             ? 0xefece9 | (0xA1 << 24)
                                             : 0x292521 | (0xA1 << 24)
                                       : color;

  ACCENT_POLICY accent{};
  WINDOWCOMPOSITIONATTRIBDATA data{};

  accent.AccentFlags = ACCENT_BORDER_ALL | ACCENT_WINDOWS11_LUMINOSITY;
  accent.AccentState = IsWindows11() ? ACCENT_ENABLE_ACRYLICBLURBEHIND
                                     : ACCENT_ENABLE_BLURBEHIND;
  accent.GradientColor = appearColor;

  data.cbData = sizeof(WINDOWCOMPOSITIONATTRIBDATA);
  data.Attrib = WCA_ACCENT_POLICY;
  data.pvData = &accent;

  try {
    VirtualSetWindowCompositionAttribute()(hWnd, &data);
  } catch (const std::nullptr_t) {
    return;
  }

  return;
}