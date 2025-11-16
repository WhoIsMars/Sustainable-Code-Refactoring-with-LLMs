#pragma once

#include <algorithm>
#include <vector>

namespace list_ops {

template<typename T>
using List = std::vector<T>;

template<typename T>
void append(List<T>& left, const List<T>& right) {  

    for (const auto& e : right) {
        left.push_back(e);
    }

}


template<typename T>
List<T> concat(const std::vector<List<T>>& in) {

    List<T> out;

    for (const auto& e : in) {
        append(out, e);
    }

    return out;

}


template<typename T, typename F>
List<T> filter(List<T>& input, F&& func) {

    List<T> out;
    std::copy_if(input.begin(), input.end(), std::back_inserter(out), func);

    return out;
}


template<typename T>
std::size_t length(const List<T>& input) {

    std::size_t ctr{};

    for (std::size_t i{}; i < input.size(); i++) {
        ctr++;
    }

    return ctr;

}

template<typename T, typename F>
List<T> map(List<T>& input, F&& func) {

    for (auto& e : input) {
        e = func(e);
    }

    return input;
}

template<typename T, typename F>
T foldl(List<T>& input, T acc, F&& func) {


    for (std::size_t i{}; i < input.size(); i++) {
        acc = func(acc, input[i]);
    }

    return acc;

}

template<typename T, typename F>
T foldr(List<T>& input, T acc, F&& func) {


    for (std::size_t i{}; i < input.size(); i++) {
        acc = func(acc, input[input.size() - 1 - i]);
    }

    return acc;

}

template<typename T>
List<T> reverse(List<T> input) {

    List<T> out;

    for (std::size_t i{}; i < input.size(); i++) {
        out.push_back(input[input.size() - 1 - i]);
    }

    return out;
}

}  // namespace list_ops
