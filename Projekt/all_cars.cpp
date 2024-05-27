using namespace std;
#include "all_cars.h"
#include <GL/glew.h>
#include <string>
#include "iostream"
#include <chrono>
#include "thread"
#include <vector>

all_cars::all_cars()
{
    this->list_of_cars;
}

void all_cars::append_car(car car)
{
    this->list_of_cars.push_back(car);
}
