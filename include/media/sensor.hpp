#pragma once

namespace media {
class Sensor {
public:
	class Handler {
		virtual void accelerometer(double, double, double) {}
	};
};
}
