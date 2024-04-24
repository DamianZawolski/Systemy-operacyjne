#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

#endif //SYSTEMY_OPERACYJNE_CAR_H
using namespace std;
#include <pthread.h>
#include <string>
#include "iostream"
#include <vector>
#include <thread>
#include "intersection.h"

class car {
public:
    car(int track, string name);
    void draw();
    void move();
    void set_delay(float desired_delay);
    void rotate_right();
    void simulate_car();
    void write_info(string text);
    float x, y, width, height, r, g, b, new_x, new_y;
    int track, laps, delay, intersection;
    string direction, name, color;
    bool finished;
    std::vector<car> cars_on_track_1;
    void set_list_of_cars_on_track_1(std::vector<car> cars);
    bool check_if_car_on_intersection(int intersection);
};

// intersections
// 1    |    2
//------------
// 3    |    4