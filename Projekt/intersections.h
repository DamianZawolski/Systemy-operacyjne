#ifndef SYSTEMY_OPERACYJNE_INTERSECTIONS_H
#define SYSTEMY_OPERACYJNE_INTERSECTIONS_H

#include <vector>
#include <mutex>

class all_cars;

class intersections
{
public:
    intersections();
    void add_number_of_intersections(int number_of_intersections);
    std::vector<bool> intersection_state;
    void set_all_unused();
    void set_used(int intersection);
    void set_unused(int intersection);
    bool is_used(int intersection);
    void update_intersection_status(all_cars &cars_on_track_1, all_cars &cars_on_track_2);
};

#include "car.h"
#include "all_cars.h"

#endif // SYSTEMY_OPERACYJNE_INTERSECTIONS_H
