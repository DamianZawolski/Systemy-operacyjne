#ifndef SYSTEMY_OPERACYJNE_INTERSECTIONS_H
#define SYSTEMY_OPERACYJNE_INTERSECTIONS_H

#include <vector>

class intersections
{
public:
    intersections();
    void add_number_of_intersections(int number_of_intersections);
    std::vector<bool> intersection_state;
    void set_all_unused();
    void set_used(int intersection);
    void set_unused(int intersection);
};

#endif // SYSTEMY_OPERACYJNE_INTERSECTIONS_H
