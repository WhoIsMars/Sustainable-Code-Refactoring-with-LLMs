#include "speedywagon.h"

namespace speedywagon {

    bool alarm_control(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr && sensor_ptr->activity;
    }

    bool connection_check(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr != nullptr;
    }

    int activity_counter(pillar_men_sensor* sensor_array, int capacity) {
        int total_activity = 0;
        const pillar_men_sensor* const end_ptr = sensor_array + capacity;

        for (const pillar_men_sensor* ptr = sensor_array; ptr < end_ptr; ++ptr) {
            total_activity += ptr->activity;
        }
        return total_activity;
    }

    int uv_light_heuristic(std::vector<int>* data_array) {
        if (data_array->empty()) return 0;
        
        const size_t size = data_array->size();
        long long sum = 0;
        
        for (int element : *data_array) {
            sum += element;
        }
        
        const double avg = static_cast<double>(sum) / size;
        int uv_index = 0;
        
        for (int element : *data_array) {
            if (element > avg) ++uv_index;
        }
        
        return uv_index;
    }

    bool uv_alarm(pillar_men_sensor* sensor_ptr) {
        return sensor_ptr && (uv_light_heuristic(&sensor_ptr->data) > sensor_ptr->activity);
    }

}