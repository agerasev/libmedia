#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void Media_setRenderer(void (*renderer)(void*), void *data);

void Media_renderFrame();

#ifdef __cplusplus
}
#endif
