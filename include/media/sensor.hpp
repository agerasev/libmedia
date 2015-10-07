#pragma once

namespace media {
class Sensor {
public:
	class Listener {
		virtual void accelerometer(double, double, double) {}
	};
};
}
