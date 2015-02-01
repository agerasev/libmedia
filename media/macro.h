#pragma once

#ifdef __ANDROID__
#include <android/log.h>
#define printInfo(...) ((void)__android_log_print(ANDROID_LOG_INFO, "libmedia_log", __VA_ARGS__))
#define printWarn(...) ((void)__android_log_print(ANDROID_LOG_WARN, "libmedia_log", __VA_ARGS__))
#else // DESKTOP
#include <stdio.h>
#define printInfo(...) (fprintf(stdout,__VA_ARGS__))
#define printWarn(...) (fprintf(stderr,__VA_ARGS__))
#endif
