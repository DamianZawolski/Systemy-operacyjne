#ifndef SYSTEMY_OPERACYJNE_INTERSECTIONS_H
#define SYSTEMY_OPERACYJNE_INTERSECTIONS_H

#include <vector>
#include <mutex>

class all_cars;

class intersections
{
public:
    intersections();
    void set_up_number_of_intersections(int number_of_intersections);
    std::vector<int> intersection_state;
    void set_all_unused();
    void add_car_to_intersection(int intersection);
    void del_car_from_intersection(int intersection);
    void print_intersections_status();
    int return_intersection_state(int intersection);
};

#include "car.h"
#include "all_cars.h"

#endif // SYSTEMY_OPERACYJNE_INTERSECTIONS_H
