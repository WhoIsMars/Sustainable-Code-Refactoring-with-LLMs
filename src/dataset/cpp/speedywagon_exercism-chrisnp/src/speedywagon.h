#pragma once

#include <string>
#include <vector>

namespace speedywagon {

struct pillar_men_sensor {
    int activity{};
    std::string location{};
    std::vector<int> data{};
};

auto uv_light_heuristic(const std::vector<int>* data_array) -> int;

auto connection_check(const pillar_men_sensor* sensor) -> bool;
auto activity_counter(const pillar_men_sensor* sensors, int sensor_count) -> int;
auto alarm_control(const pillar_men_sensor* sensor) -> bool;
auto uv_alarm(const pillar_men_sensor* sensor) -> bool;

}  // namespace speedywagon

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif