#include "test.h"

void TESTRENDER::Render(Gdiplus::Graphics& a) {
  Gdiplus::Font font(L"Microsoft YaHei", 16);
  Gdiplus::SolidBrush brush(Gdiplus::Color::White);

  Gdiplus::Rect rcRender(100, 100, 100, 100);
  auto const renderContainer = a.BeginContainer(rcRender, rcRender, Gdiplus::UnitPixel);
  a.DrawString(L"I was rendered", 15, &font, Gdiplus::PointF(100, 100), &brush);
  a.EndContainer(renderContainer);
};