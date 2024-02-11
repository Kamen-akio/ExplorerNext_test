#include "initialize.h"

ComUtils::ComBase::ComBase() {
  bInited = CoInitialize(NULL) == S_OK;
  FailAndCrash();
};

ComUtils::ComBase::~ComBase() {
  CoUninitialize();
}

inline void ComUtils::ComBase::FailAndCrash() const {
  if (bInited != S_OK) {
    throw new std::exception(
        ("The process has something wrong in " + moduleName + "com unit").c_str());
  }
}