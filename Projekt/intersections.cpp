using namespace std;
#include "intersections.h"
#include "all_cars.h"

std::mutex mtx_intersections;
std::mutex mtx_all_cars;

intersections::intersections()
{
    this->intersection_state;
}

void intersections::set_up_number_of_intersections(int number_of_intersections)
{
    for (int i = 0; i < number_of_intersections; i++)
    {
        this->intersection_state.push_back(0);
    }
}
void intersections::set_all_unused()
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    for (auto &&i : this->intersection_state)
    {
        i = 0;
    }
}

void intersections::add_car_to_intersection(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_state[intersection]++;
}

void intersections::del_car_from_intersection(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_state[intersection]--;
}

int intersections::return_intersection_state(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return this->intersection_state[intersection];
}

void intersections::print_intersections_status()
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    cout << "intersection 1: " << this->intersection_state[0];
    cout << " intersection 2: " << this->intersection_state[1];
    cout << " intersection 3: " << this->intersection_state[2];
    cout << " intersection 4: " << this->intersection_state[3] << endl;
}
