using namespace std;
#include "intersections.h"
#include <mutex>

std::mutex mtx_intersections;

intersections::intersections()
{
    this->intersection_state;
}

void intersections::add_number_of_intersections(int number_of_intersections)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    for (int i = 0; i < number_of_intersections; i++)
    {
        this->intersection_state.push_back(false);
    }
}
void intersections::set_all_unused()
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    for (auto &&i : this->intersection_state)
    {
        i = false;
    }
}

void intersections::set_used(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_state[intersection] = true;
}

void intersections::set_unused(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_state[intersection] = false;
}
