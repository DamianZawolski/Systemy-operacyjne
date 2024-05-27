using namespace std;
#include "intersections.h"
#include "all_cars.h"

std::mutex mtx_intersections;
std::mutex mtx_all_cars;

intersections::intersections()
{
    this->intersection_state;
}

void intersections::add_number_of_intersections(int number_of_intersections)
{
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

void intersections::update_intersection_status(all_cars &cars_on_track_1, all_cars &cars_on_track_2)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    std::lock_guard<std::mutex> lock2(mtx_all_cars);

    std::vector<bool> intersection_state_temp(this->intersection_state.size(), false);
    for (auto &&car : cars_on_track_1.list_of_cars)
    {
        if (car.x >= 0.3 and car.x <= 0.4 and car.y >= 0.2 and car.y <= 0.3)
        {
            intersection_state_temp[0] = true;
        }
        else if (car.x >= -0.3 and car.x <= -0.2 and car.y >= 0.3 and car.y <= 0.4)
        {
            intersection_state_temp[1] = true;
        }
        else if (car.x >= -0.3 and car.x <= -0.2 and car.y >= -0.3 and car.y <= -0.2)
        {
            intersection_state_temp[2] = true;
        }
        else if (car.x >= 0.3 and car.x <= 0.4 and car.y >= -0.3 and car.y <= -0.2)
        {
            intersection_state_temp[3] = true;
        }
    }
    this->intersection_state = intersection_state_temp;

    for (auto &&car : cars_on_track_1.list_of_cars)
    {
        if (car.x >= -0.3 and car.x <= -0.2 and car.y >= 0 and car.y <= 0.3)
        {
            // 1
            car.stopped = 1;
        }
        else if (car.x >= 0.2 and car.x <= 0.3 and car.y >= 0.5 and car.y <= 0.3)
        {
            // 2
            car.stopped = 2;
        }
        else if (car.x >= 0.2 and car.x <= 0.3 and car.y >= -0.3 and car.y <= 0)
        {
            // 4
            car.stopped = 3;
        }
        else if (car.x >= -0.3 and car.x <= -0.2 and car.y >= -0.5 and car.y <= -0.2)
        {
            // 3
            car.stopped = 4;
        }
        else if (intersection_state[car.stopped] == 0)
        {
            car.stopped = 0;
        }
    }
}

bool intersections::is_used(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return this->intersection_state[intersection - 1];
}