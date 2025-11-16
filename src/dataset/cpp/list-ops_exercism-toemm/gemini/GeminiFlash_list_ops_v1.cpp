#include "list_ops.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

namespace list_ops {

    std::vector<int> append(std::vector<int> list1, const std::vector<int>& list2) {
        list1.insert(list1.end(), list2.begin(), list2.end());
        return list1;
    }

    std::vector<int> concat(const std::vector<std::vector<int>>& list_of_lists) {
        std::vector<int> result;
        size_t total_size = 0;
        for (const auto& list : list_of_lists) {
            total_size += list.size();
        }
        result.reserve(total_size);
        for (const auto& list : list_of_lists) {
            result.insert(result.end(), list.begin(), list.end());
        }
        return result;
    }

    std::vector<int> filter(const std::vector<int>& list, std::function<bool(int)> predicate) {
        std::vector<int> result;
        for (int x : list) {
            if (predicate(x)) {
                result.push_back(x);
            }
        }
        return result;
    }

    int length(const std::vector<int>& list) {
        return static_cast<int>(list.size());
    }

    std::vector<int> map(const std::vector<int>& list, std::function<int(int)> transform) {
        std::vector<int> result(list.size());
        std::transform(list.begin(), list.end(), result.begin(), transform);
        return result;
    }

    std::vector<int> reverse(std::vector<int> list) {
        std::reverse(list.begin(), list.end());
        return list;
    }

    int foldl(const std::vector<int>& list, int initial, std::function<int(int, int)> func) {
        int accumulator = initial;
        for (int x : list) {
            accumulator = func(accumulator, x);
        }
        return accumulator;
    }

    int foldr(const std::vector<int>& list, int initial, std::function<int(int, int)> func) {
        int accumulator = initial;
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            accumulator = func(accumulator, *it);
        }
        return accumulator;
    }
}  // namespace list_ops