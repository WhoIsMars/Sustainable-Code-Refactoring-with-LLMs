#pragma once

#include <string>
#include <vector>

namespace speedywagon {


    struct pillar_men_sensor {
        int activity{};
        std::string location{};
        std::vector<int> data{};
    };

    bool uv_alarm(pillar_men_sensor* sensor_ptr);
    bool alarm_control(pillar_men_sensor* sensor_ptr);
    bool connection_check(pillar_men_sensor* sensor_ptr);
    int activity_counter(pillar_men_sensor* sensor_array, int capacity);


    int uv_light_heuristic(std::vector<int>* data_array);

}  // namespace speedywagon
