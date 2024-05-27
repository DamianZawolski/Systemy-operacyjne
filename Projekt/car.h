#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

using namespace std;
#include <pthread.h>
#include <string>
#include "iostream"
#include <vector>
#include <thread>

class all_cars;
class intersections;
class car
{
public:
    car(int track, string name, int id);
    void draw();
    void move(intersections all_intersections, all_cars &cars_on_track_1, all_cars &cars_on_track_2);
    void set_delay(float desired_delay);
    void rotate_right();
    void simulate_car(intersections &all_intersections, all_cars &cars_on_track_1, all_cars &cars_on_track_2);
    void write_info(string text);
    float x, y, width, height, r, g, b;
    int track, laps, delay, intersection, id, stopped;
    string direction, name, color;
    bool finished;
};

// intersections
// 1    |    2
//------------
// 3    |    4

#include "intersections.h"
#include "all_cars.h"
#endif // SYSTEMY_OPERACYJNE_CAR_H