#ifndef SYSTEMY_OPERACYJNE_INTERSECTIONS_H
#define SYSTEMY_OPERACYJNE_INTERSECTIONS_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>

class all_cars;

class intersections
{
public:
    intersections();
    void set_up_number_of_intersections(int number_of_intersections);
    void set_all_unused();
    void add_car_to_intersection(int intersection);
    void del_car_from_intersection(int intersection);
    int return_intersection_state(int intersection);
    void print_intersections_status();

    // Metody dostępu do prywatnych członków
    std::shared_ptr<std::condition_variable> get_cv_intersection(int index);
    bool get_intersection_ready(int index);

private:
    std::vector<int> intersection_count;
    std::vector<std::shared_ptr<std::condition_variable>> cv_intersections;
    std::vector<bool> intersections_ready;
};

#include "car.h"
#include "all_cars.h"

#endif // SYSTEMY_OPERACYJNE_INTERSECTIONS_H
