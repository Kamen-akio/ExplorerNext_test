#include "registry.h"

bool Registry::SetValue(HKEY root,
                        const char* path,
                        const char* name,
                        CValue data,
                        DWORD dwType) {
  HKEY hPathKey{};
  if (RegOpenKeyExA(root, path, NULL, KEY_SET_VALUE, &hPathKey) !=
      ERROR_SUCCESS) {
    return false;
  }

  if (RegSetKeyValueA(root, path, name, dwType, data.GetRaw(),
                      data.GetRawSize()) != ERROR_SUCCESS) {
    return false;
  }

  RegCloseKey(root);
  return true;
}

Registry::CValue Registry::GetValue(HKEY root,
                                    const char* path,
                                    const char* name,
                                    void* defaultData) {
  HKEY hPathKey{};
  DWORD dwType{};
  char ptrData[MAX_PATH]{};
  DWORD pcbData = MAX_PATH;

  if (RegOpenKeyExA(root, path, NULL, KEY_READ, &hPathKey) != ERROR_SUCCESS) {
    return CValue(nullptr, NULL);
  }

  if (RegGetValueA(root, path, name, RRF_RT_ANY | RRF_ZEROONFAILURE, &dwType,
                   ptrData, &pcbData) != ERROR_SUCCESS) {
    return CValue(nullptr, NULL);
  }

  if (RegGetValueA(root, path, name, RRF_RT_ANY | RRF_ZEROONFAILURE, &dwType,
                   ptrData, &pcbData) != ERROR_SUCCESS) {
    return CValue(nullptr, NULL);
  }

  RegCloseKey(root);
  return CValue(ptrData, pcbData);
}

// Value

Registry::CValue::CValue(void* data, int szData) {
  _data = GlobalAlloc(GMEM_FIXED, GMEM_ZEROINIT);
  _szData = szData;

  memcpy_s(_data, szData, data, szData);
};

Registry::CValue::~CValue() {
  memset(_data, NULL, _szData);
  GlobalFree(_data);

  _data = nullptr;
  _szData = NULL;
}

std::string Registry::CValue::ToString() {
  if (_data == nullptr)
    return std::string();

  return std::string((char*)_data);
}

int Registry::CValue::ToInt() {
  return atoi((char*)_data);
}

bool Registry::CValue::ToBool() {
  if (_data == nullptr) {
    return false;
  }

  return ToInt() > 0; // Right?
}
