#include "windowCompositionAttribute.h"

pfnGetWindowCompositionAttribute VirtualGetWindowCompositionAttribute() {
  auto hUser = GetModuleHandleA("user32.dll");

  if (hUser == nullptr) {
    hUser = LoadLibraryA("user32.dll");
  }

  if (hUser == NULL)
    return nullptr;

  return (pfnGetWindowCompositionAttribute)GetProcAddress(
      hUser, "GetWindowCompositionAttribute");
}

pfnSetWindowCompositionAttribute VirtualSetWindowCompositionAttribute() {
  
  auto hUser = GetModuleHandleA("user32.dll");

  if (hUser == NULL) {
    hUser = LoadLibraryA("user32.dll");
  }

  if (hUser == NULL)
    return nullptr;

  return (pfnSetWindowCompositionAttribute)GetProcAddress(
      hUser, "SetWindowCompositionAttribute");
}