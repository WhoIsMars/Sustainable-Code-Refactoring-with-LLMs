#pragma once

#include <array>
#include <vector>

namespace arcade {

class HighScores {
   private:
    std::vector<int> scores;

   public:
    HighScores(std::vector<int> scores) : scores(scores) {};

    std::vector<int> list_scores();

    int latest_score();

    int personal_best();

    std::vector<int> top_three();
};

}  // namespace arcade

namespace {

template <class T> 
struct greater {bool operator()(const T& x, const T& y) const {return x > y;}};

template<typename T> static void swap(T &x, T &y) {
    T temp {x}; x = y; y = temp;
}

template<class RandomAccessIterator, class Compare>
static void sort(RandomAccessIterator first, 
                 RandomAccessIterator last, Compare comp)
{
	for (auto i = first; i != last; i++)
		for (auto j = i + 1; j != last; j++) 
            if (comp(*j, *i)) swap(*i, *j); 
}

template<class ForwardIt>
constexpr auto max_elem(ForwardIt first, ForwardIt last) noexcept -> ForwardIt 
{
    if (first == last) return last;
    ForwardIt largest = first;
    for (first++; first != last; ++first) 
        if (*largest < *first) largest = first;
    return largest;
}

template<typename T> 
constexpr auto min(T x, T y) noexcept -> T { return x < y ? x : y; }

} // namespace

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif