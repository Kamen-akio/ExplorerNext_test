#pragma once
#include <objbase.h>
#include <string>
#include <exception>

#ifndef _UTILS_COM_INITIALIZE_H
#define _UTILS_COM_INITIALIZE_H

namespace ComUtils {
class ComBase {
 public:
  bool bInited = false;
  std::string moduleName = "base";

  ComBase();
  ~ComBase();

  inline void FailAndCrash() const;
};
}  // namespace ComUtils

#endif  // !_UTILS_COM_INITIALIZE_H
