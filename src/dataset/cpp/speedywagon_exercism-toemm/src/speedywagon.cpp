#include "speedywagon.h"

namespace speedywagon {

    // Enter your code below:

    bool alarm_control(pillar_men_sensor* sensor_ptr) {

        return connection_check(sensor_ptr) and (*sensor_ptr).activity;

    }

    bool connection_check(pillar_men_sensor* sensor_ptr) {
        return (sensor_ptr != nullptr);
    }

    int activity_counter(pillar_men_sensor* sensor_array, int capacity) {
        int total_activity {};
        pillar_men_sensor* end_ptr = sensor_array+capacity;

        while (sensor_array < end_ptr) {
            total_activity += sensor_array->activity;
            sensor_array++;
        }
        return total_activity;
    }




    // Please don't change the interface of the uv_light_heuristic function
    int uv_light_heuristic(std::vector<int>* data_array) {
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

    bool uv_alarm(pillar_men_sensor* sensor_ptr) {
        //if (!sensor_ptr) return false;

        //std::vector<int>* data_ptr = &(sensor_ptr->data);

        // SHORT CIRCUIT EVALUATION: if left side fails (nullptr), right side isn't evaluated
        return connection_check(sensor_ptr) and (uv_light_heuristic(&sensor_ptr->data) > sensor_ptr->activity);
    }


}  // namespace speedywagon
