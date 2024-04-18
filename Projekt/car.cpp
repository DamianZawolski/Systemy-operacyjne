
#include "car.h"
#include <GL/glew.h>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <time.h>



//create object car with 4 corners and color


car::car(int track) {
    this->track = track;
    if (track ==1){
        this->x = -1.6;
        this->y = 0.2;
        this->direction = "right";
    }
    else{
        int rand_wall = (rand() % 4);
        if (rand_wall == 0){
            this->x = 0.2;
            this->y = (rand() % 13 -6)/10;
            this->direction = "right";
        }
        else if (rand_wall == 1){
            this->x = -0.2;
            this->y = (rand() % 13 -6)/10;
            this->direction = "left";
        }
        else if (rand_wall == 2){
            this->x = (rand() % 5 -2)/10;
            this->y = 0.6;
            this->direction = "right";
        }
        else{
            this->x = (rand() % 5 -2)/10;
            this->y = -0.6;
            this->direction = "left";
        }
    }
    //width is random between 0.09 and 0.15
    float width_value = (rand() % 7 +9) / 100.0;
    //height is random between 0.04 and 0.07
    float height_value = (rand() % 4 + 4) / 100.0;
    this->width = width_value;
    this->height = height_value;
    //speed is random between 0.005 and 0.02
    float speed_value = (rand() % 16 + 5) / 1000.0;
    this->speed = speed_value;

    //r,g,b - color of car-random between 0,3 and 1
    float r_value = (rand() % 100) / 100.0;
    float g_value = (rand() % 100) / 100.0;
    float b_value = (rand() % 100) / 100.0;
    if (r_value < 0.3) r_value = 0.3;
    if (g_value < 0.3) g_value = 0.3;
    if (b_value < 0.3) b_value = 0.3;

    this->r = r_value;
    this->g = g_value;
    this->b = b_value;

    //10% chance for car to be a red ferrari, which overtakes other cars
    int rand_red = (rand() % 100);
    if (rand_red <= 10){
        this->r = 1;
        this->g = 0;
        this->b = 0;
        this->speed = 0.03;
    }

    this-> laps = 0;
}

//draw car
void car::draw() {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void car::rotate_right() {
    float temp = width;
    width = height;
    height = temp;

    if (direction == "right") {
        direction = "down";
    }
    else if (direction == "down") {
        direction = "left";
    }
    else if (direction == "left") {
        direction = "up";
    }
    else if (direction == "up") {
        direction = "right";
    }
}

//move car
void car::move() {
    if (track ==2){
        if (x>= 0.25 and direction == "right") {
            rotate_right();
        }
        else if (x <= -0.25 and direction == "left") {
            rotate_right();
        }
        else if (y >= 0.65 and direction == "up") {
            rotate_right();
        }
        else if (y <= -0.65 and direction == "down") {
            rotate_right();
        }

        if (direction == "right") {
            x += speed;
        }
        else if (direction == "down") {
            y -= speed;
        }
        else if (direction == "left") {
            x -= speed;
        }
        else if (direction == "up") {
            y += speed;
        }
    }
    else if (track == 1){
        if (x>= 0.65 and direction == "right") {
            rotate_right();
        }
        else if (x <= -0.65 and direction == "left" and laps<2) {
            rotate_right();
        }
        else if (y >= 0.25 and direction == "up") {
            rotate_right();
            laps++;
        }
        else if (y <= -0.25 and direction == "down") {
            rotate_right();
        }

        if (direction == "right") {
            x += speed;
        }
        else if (direction == "down") {
            y -= speed;
        }
        else if (direction == "left") {
            x -= speed;
        }
        else if (direction == "up") {
            y += speed;
        }
    }
}

void car::set_speed(float desired_speed){
    this->speed = desired_speed;
}
//move car in thread
void* car::move_thread() {
    while (true) {
        move();
        draw();
        usleep(20000);
    }
}


