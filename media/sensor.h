#pragma once

typedef unsigned int Media_SensorType;

/* Sensors */
#define MEDIA_SENSOR_ACCELEROMETER   0x01

#ifdef __cplusplus
extern "C" {
#endif

int Media_enableSensor (Media_SensorType type, unsigned long rate);
int Media_disableSensor(Media_SensorType type);

#ifdef __cplusplus
}
#endif
