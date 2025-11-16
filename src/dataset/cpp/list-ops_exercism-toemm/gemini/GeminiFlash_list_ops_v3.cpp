#include "list_ops.h"
#include <algorithm>
#include <numeric>
#include <vector>

namespace list_ops {

    std::vector<int> append(const std::vector<int>& list1, const std::vector<int>& list2) {
        std::vector<int> result = list1;
        result.insert(result.end(), list2.begin(), list2.end());
        return result;
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

    std::vector<int> filter(const std::function<bool(int)>& predicate, const std::vector<int>& list) {
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

    std::vector<int> map(const std::function<int(int)>& transform, const std::vector<int>& list) {
        std::vector<int> result(list.size());
        std::transform(list.begin(), list.end(), result.begin(), transform);
        return result;
    }

    std::vector<int> reverse(const std::vector<int>& list) {
        std::vector<int> result = list;
        std::reverse(result.begin(), result.end());
        return result;
    }

    int foldl(const std::function<int(int, int)>& func, int initial, const std::vector<int>& list) {
        return std::accumulate(list.begin(), list.end(), initial, func);
    }

    int foldr(const std::function<int(int, int)>& func, int initial, const std::vector<int>& list) {
        int result = initial;
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            result = func(*it, result);
        }
        return result;
    }
    
}  // namespace list_ops