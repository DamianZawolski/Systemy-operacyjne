
#include "car.h"
#include <GL/glew.h>
#include <pthread.h>

//car is a rectangle that moves in a square path. It has a speed and a direction. It can be drawn using openGL. It is a thread.


void draw_car(float corner1_x, float corner1_y, float corner2_x, float corner2_y){
    glVertex2f(corner1_x, corner1_y);
    glVertex2f(corner2_x, corner1_y);
    glVertex2f(corner2_x, corner2_y);
    glVertex2f(corner1_x, corner2_y);
}

void draw_all_cars(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.1);
    float corner1_x = -0.1f;
    float corner1_y = 0.1f;
    float corner2_x = 0.1f;
    float corner2_y = -0.1f;
    draw_car(corner1_x, corner1_y, corner2_x, corner2_y);
    glEnd();
}

void* car_thread(void* arg){
    while(1){
        draw_all_cars();
    }
    return NULL;
}

void start_car_thread(){
    pthread_t car_thread_id;
    pthread_create(&car_thread_id, NULL, car_thread, NULL);
}

void stop_car_thread(){
    pthread_cancel(car_thread_id);
}

