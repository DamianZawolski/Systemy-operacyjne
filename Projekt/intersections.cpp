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
        if (car.x >= -0.4 and car.x <= -0.2 and car.y >= 0.2 and car.y <= 0.3)
        {
            intersection_state_temp[0] = true;
        }
        else if (car.x >= 0.1 and car.x <= 0.3 and car.y >= 0.2 and car.y <= 0.3)
        {
            intersection_state_temp[1] = true;
        }
        else if (car.x >= -0.3 and car.x <= -0.1 and car.y >= -0.3 and car.y <= -0.2)
        {
            intersection_state_temp[2] = true;
        }
        else if (car.x >= 0.2 and car.x <= 0.4 and car.y >= -0.3 and car.y <= -0.2)
        {
            intersection_state_temp[3] = true;
        }
    }
    this->intersection_state = intersection_state_temp;
    /*
    cout << "intersection 1: " << this->intersection_state[0];
    cout << " intersection 2: " << this->intersection_state[1];
    cout << " intersection 3: " << this->intersection_state[2];
    cout << " intersection 4: " << this->intersection_state[3] << endl;*/
    for (auto &&car : cars_on_track_2.list_of_cars)
    {
        car.stopped = 0;
    }

    for (auto &&car : cars_on_track_2.list_of_cars)
    {
        if (car.x >= -0.3 and car.x <= -0.2 and car.y >= 0 and car.y <= 0.2 and this->intersection_state[0] == true)
        {
            car.stopped = 1;
        }
        else if (car.x >= 0.2 and car.x <= 0.3 and car.y >= 0.3 and car.y <= 0.5 and this->intersection_state[1] == true)
        {
            car.stopped = 1;
        }
        else if (car.x >= -0.3 and car.x <= -0.2 and car.y >= -0.5 and car.y <= -0.3 and this->intersection_state[2] == true)
        {
            car.stopped = 1;
        }
        else if (car.x >= 0.2 and car.x <= 0.3 and car.y >= -0.2 and car.y <= -0 and this->intersection_state[3] == true)
        {
            car.stopped = 1;
        }
    }
}

bool intersections::is_used(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return this->intersection_state[intersection - 1];
}