#pragma once

#if 0
#define USE_BLUR
#endif

#if true
#define USE_BLUR_AUTO
#endif

#if defined(USE_BLUR) and defined(USE_BLUR_AUTO)
#error Do not define USE_BLUR and USE_BLUR_AUTO in project.
#endif  // defined(USE_BLUR) and defined(USE_BLUR_AUTO)
