
#ifndef SO2_ALL_CARS_H
#define SO2_ALL_CARS_H

using namespace std;
#include <pthread.h>
#include <string>
#include "iostream"
#include <vector>
#include <thread>
#include <mutex>

class car;
class intersections;

class all_cars
{
public:
    all_cars();
    std::vector<car> list_of_cars;
    void append_car(car car);
};

#include "car.h"
#include "intersections.h"
#endif // SO2_ALL_CARS_H
