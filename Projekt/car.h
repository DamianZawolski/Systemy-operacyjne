#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

using namespace std;
#include <pthread.h>
#include <string>
#include "iostream"
#include <vector>
#include <thread>
#include "intersections.h"

class all_cars;

class car
{
public:
    car(int track, string name);
    void draw();
    void move(intersections all_intersections, all_cars all_cars);
    void set_delay(float desired_delay);
    void rotate_right();
    void simulate_car(intersections all_intersections, all_cars cars_on_track_1);
    void write_info(string text);
    float x, y, width, height, r, g, b;
    int track, laps, delay, intersection;
    string direction, name, color;
    bool finished;
    std::vector<car> cars_on_track_1;

    void set_list_of_cars_on_track_1(std::vector<car> cars);
};

// intersections
// 0    |    1
//------------
// 2    |    3

#include "all_cars.h"
#endif // SYSTEMY_OPERACYJNE_CAR_H