#pragma once
#include <string>
#include <memory>

#include <Windows.h>
#include <winreg.h>

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

namespace Registry {

class CValue {
 public:
  CValue(void*, int);
  ~CValue();

  std::string ToString();
  bool ToBool();
  int ToInt();
  void* GetRaw() { return _data; }
  int GetRawSize() { return _szData; }

 private:
  void* _data;
  int _szData;
};

bool SetValue(HKEY root,
              const char* path,
              const char* name,
              CValue data,
              DWORD dwType);
CValue GetValue(HKEY root,
                const char* path,
                const char* name,
                void* defaultValue);
}  // namespace Registry

#endif  // !_REGISTRY_H_
