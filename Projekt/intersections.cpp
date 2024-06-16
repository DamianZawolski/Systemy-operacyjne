#include "intersections.h"
#include "all_cars.h"

std::mutex mtx_intersections;
std::mutex mtx_all_cars;

intersections::intersections()
{
}

void intersections::set_up_number_of_intersections(int number_of_intersections)
{
    for (int i = 0; i < number_of_intersections; i++)
    {
        this->intersection_count.push_back(0);
        this->cv_intersections.push_back(std::make_shared<std::condition_variable>());
        this->intersections_ready.push_back(true);
    }
}

void intersections::set_all_unused()
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    for (auto &&i : this->intersection_count)
    {
        i = 0;
    }
    for (auto &&i : this->intersections_ready)
    {
        i = true;
    }
    for (auto &&i : this->cv_intersections)
    {
        i->notify_all();
    }
}

void intersections::add_car_to_intersection(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_count[intersection]++;
    if (this->intersection_count[intersection] > 1)
    {
        this->intersections_ready[intersection] = false;
    }
}

void intersections::del_car_from_intersection(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    this->intersection_count[intersection]--;
    if (this->intersection_count[intersection] <= 0)
    {
        this->intersections_ready[intersection] = true;
        this->cv_intersections[intersection]->notify_all();
    }
}

int intersections::return_intersection_state(int intersection)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return this->intersection_count[intersection];
}

void intersections::print_intersections_status()
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    cout << "intersection 1: " << this->intersection_count[0];
    cout << " intersection 2: " << this->intersection_count[1];
    cout << " intersection 3: " << this->intersection_count[2];
    cout << " intersection 4: " << this->intersection_count[3] << endl;
}

std::shared_ptr<std::condition_variable> intersections::get_cv_intersection(int index)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return cv_intersections[index];
}

bool intersections::get_intersection_ready(int index)
{
    std::lock_guard<std::mutex> lock(mtx_intersections);
    return intersections_ready[index];
}
