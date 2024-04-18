
#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

#endif //SYSTEMY_OPERACYJNE_CAR_H

#include <pthread.h>
#include <string>



class car {
public:
    car(int track);
    void draw();
    void move();
    void set_speed(float desired_speed);
    void rotate_right();
    void* move_thread();
    float x, y, width, height, r, g, b, speed;
    int track, laps;
    //direction of car
    std::string direction;
    pthread_t thread;
};

