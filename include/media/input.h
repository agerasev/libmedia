#pragma once

typedef struct Media_App Media_App;

#ifdef __cplusplus
extern "C" {
#endif

/* Gets positions of pointers (cursor) */
void Media_getPointer(Media_App *app, int *x, int *y);
void Media_getPointerByIndex(Media_App *app, int index, int *x, int *y);
int Media_getPointerCount(Media_App *app);

/* Enables sensor to produce events with given period
 * @return non-zero if there was an error */
int Media_enableSensor (Media_App *app, Media_SensorType type, unsigned long rate);
/* Disables sensor */
int Media_disableSensor(Media_App *app, Media_SensorType type);

#ifdef __cplusplus
}
#endif
