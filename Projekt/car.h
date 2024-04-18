
#ifndef SYSTEMY_OPERACYJNE_CAR_H
#define SYSTEMY_OPERACYJNE_CAR_H

#endif //SYSTEMY_OPERACYJNE_CAR_H


void draw_car(float corner1_x, float corner1_y, float corner2_x, float corner2_y);

void draw_all_cars();

void* car_thread(void* arg);

void start_car_thread();

void stop_car_thread();


