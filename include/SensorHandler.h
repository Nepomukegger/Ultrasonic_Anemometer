#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <vector.h>

class SensorHandler {
public:
    void processDistances(const std::vector<double>& distances);
};

#endif
