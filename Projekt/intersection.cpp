using namespace std;
#include "intersection.h"
#include "iostream"

intersection::intersection(){
    this->used=false;
}

void intersection::set_used(){
    this->used=true;
}

void intersection::set_unused(){
    this->used=false;
}

