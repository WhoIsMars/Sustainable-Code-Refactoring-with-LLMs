#include "speedywagon.h"
#include <numeric>

namespace speedywagon {

    bool alarm_control(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr && sensor_ptr->activity;
    }

    bool connection_check(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr != nullptr;
    }

    int activity_counter(pillar_men_sensor* sensor_array, int capacity) {
        int total_activity = 0;
        for (int i = 0; i < capacity; ++i) {
            total_activity += sensor_array[i].activity;
        }
        return total_activity;
    }

    int uv_light_heuristic(std::vector<int>* data_array) {
        if (data_array->empty()) return 0;

        double sum = std::accumulate(data_array->begin(), data_array->end(), 0.0);
        double avg = sum / data_array->size();

        int uv_index = 0;
        for (int element : *data_array) {
            if (element > avg) ++uv_index;
        }
        return uv_index;
    }

    bool uv_alarm(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr && (uv_light_heuristic(&sensor_ptr->data) > sensor_ptr->activity);
    }

}  // namespace speedywagon