#include "audio.h"

ComUtils::Audio::Audio() {
  moduleName = "com.audio";
  bInited =
      CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
                       __uuidof(IMMDeviceEnumerator),
                       (void**)&pAudioDeviceEnumerator) == S_OK;
  FailAndCrash();

  bInited = pAudioDeviceEnumerator->GetDefaultAudioEndpoint(
      (EDataFlow)eRender, eConsole, &pAudioEndpoint);
  FailAndCrash();

  bInited =
      pAudioEndpoint->Activate((IID) __uuidof(IAudioMeterInformation),
                               CLSCTX_ALL, NULL, (void**)&pAudioMeterInfo);
  FailAndCrash();
}

ComUtils::Audio::~Audio() {
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
}