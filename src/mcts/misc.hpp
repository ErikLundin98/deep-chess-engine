#ifndef MISC_H
#define MISC_H

#include <random>
#include <iterator>
#include <chrono>
#include <unordered_map>
#include <algorithm>

// Retrieve an iterator at a random position
template<typename Iterator, typename RandomGenerator>
inline Iterator random_element(Iterator start, Iterator end, RandomGenerator& generator)
{
    std::uniform_int_distribution<> dist(0, std::distance(start, end)-1);
    std::advance(start, dist(generator));
    return start;
};

// Retrieve a random element between two iterators
template<typename Iterator>
inline Iterator random_element(Iterator start, Iterator end)
{
    static std::random_device random_device;
    static std::mt19937 generator(random_device());
    return random_element(start, end, generator);
};

// Get the index of the maximum element between two iterators
template<typename Iterator>
inline size_t get_max_idx(Iterator start, Iterator end)
{
    return std::distance(start, std::max_element(start, end));
};

// Get the max element between two iterators
template<typename T, typename Iterator1, typename Iterator2>
inline T get_max_element(Iterator1 wanted_start, Iterator2 comparator_start, Iterator2 comparator_end)
{
    size_t max_idx = get_max_idx(comparator_start, comparator_end);
    std::advance(wanted_start, max_idx);
    return *wanted_start;
};
// Simple timer class for measuring execution time
struct Timer
{
    Timer();
    void set_start();
    
    double get_time(bool setstart=false);

    std::chrono::time_point<std::chrono::high_resolution_clock> start_t = std::chrono::high_resolution_clock::now();
};

// Simple function to get key(string) val(int) pairs from file to Map
std::unordered_map<std::string, int> parse_config(std::string filename);

#endif /* MISC_H */