#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

#endif //SYSTEMY_OPERACYJNE_CAR_H
using namespace std;
#include <pthread.h>
#include <string>
#include "iostream"

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
    int track, laps, delay;
    string direction, name, color;
    bool finished;
};

