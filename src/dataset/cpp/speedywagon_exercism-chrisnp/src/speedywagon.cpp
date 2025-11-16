#include "speedywagon.h"

namespace speedywagon {

// Enter your code below:
bool connection_check(const pillar_men_sensor* sensor) {
    return sensor != nullptr;
}

int activity_counter(const pillar_men_sensor* sensors, int sensor_count) {
    auto count = int{};
    for(auto i = int{ 0 }; i < sensor_count; ++i) {
      count += sensors[i].activity;
    }
    return count;
}

bool alarm_control(const pillar_men_sensor* sensor) {
    return sensor && sensor->activity > 0;
}

bool uv_alarm(const pillar_men_sensor* sensor) {
    return sensor && (uv_light_heuristic(&sensor->data) > sensor->activity);
}

// Please don't change the interface of the uv_light_heuristic function
int uv_light_heuristic(const std::vector<int>* data_array) {
    double avg{};
    for (auto element : *data_array) {
        avg += element;
    }
    avg /= data_array->size();
    int uv_index{};
    for (auto element : *data_array) {
        if (element > avg) ++uv_index;
    }
    return uv_index;
}

}  // namespace speedywagon

