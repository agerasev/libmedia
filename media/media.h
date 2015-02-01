#pragma once

#include "macro.h"
#include "event.h"
#include "motion.h"
#include "sensor.h"
#include "render.h"

#ifdef __cplusplus
extern "C" {
#endif

int  Media_init();
void Media_quit();

#ifdef __ANDROID__
int main();
#endif

#ifdef __cplusplus
}
#endif


