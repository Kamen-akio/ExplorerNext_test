#pragma once
#include "initialize.h"

#include <endpointvolume.h>
#include <initguid.h>
#include <mmdeviceapi.h>

#ifndef _UTILS_COM_AUDIO_H_
#define _UTILS_COM_AUDIO_H_

namespace ComUtils {
class Audio : public ComBase {
 public:
  Audio();
  ~Audio();

 public:
  float GetPeekVolume();

  IMMDeviceEnumerator& GetDeviceEnumerator() const {
    return *pAudioDeviceEnumerator;
  };
  IMMDevice& GetAudioEndpoint() const { return *pAudioEndpoint; };
  IAudioMeterInformation& GetAudioMeterInfomation() const {
    return *pAudioMeterInfo;
  };

 private:
  IMMDeviceEnumerator* pAudioDeviceEnumerator{};
  IMMDevice* pAudioEndpoint{};
  IAudioMeterInformation* pAudioMeterInfo{};
};
}  // namespace ComUtils

#endif  // !_UTILS_COM_AUDIO_H_
