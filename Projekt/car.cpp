using namespace std;
#include "car.h"
#include <GL/glew.h>
#include <string>
#include "iostream"
#include <chrono>
#include "thread"

car::car(int track, string name) {
    this->track = track;
    this->name = name;
    this-> finished = false;
    if (track ==1){
        this->x = (rand() % 100 -110)/10;
        this->y = 0.25;
        this->direction = "right";
    }
    else{
        int rand_wall = (rand() % 4);
        if (rand_wall == 0){
            this->x = 0.25;
            this->y = (rand() % 13 -6)/10;
            this->direction = "right";
        }
        else if (rand_wall == 1){
            this->x = -0.25;
            this->y = (rand() % 13 -6)/10;
            this->direction = "left";
        }
        else if (rand_wall == 2){
            this->x = (rand() % 5 -2)/10;
            this->y = 0.65;
            this->direction = "right";
        }
        else{
            this->x = (rand() % 5 -2)/10;
            this->y = -0.65;
            this->direction = "left";
        }
    }
    //width is random between 0.09 and 0.15
    float width_value = (rand() % 7 +9) / 100.0;
    //height is random between 0.04 and 0.07
    float height_value = (rand() % 4 + 4) / 100.0;
    this->width = width_value;
    this->height = height_value;
    //delay is random between 10 and 30 (slower is faster)
    float delay_value = (rand() % 21 + 10);
    if (track==2){delay_value = 20;}
    this->delay = delay_value;
    int color_random = (rand() % 9);
    if (color_random==0){this->r = 1; this->g = 0; this->b = 0; this->color = "red";}
    else if (color_random==1){this->r = 0; this->g = 1; this->b = 0; this->color = "green";}
    else if (color_random==2){this->r = 0; this->g = 0; this->b = 1; this->color = "blue";}
    else if (color_random==3){this->r = 1; this->g = 1; this->b = 0; this->color = "yellow";}
    else if (color_random==4){this->r = 0; this->g = 1; this->b = 1; this->color = "cyan";}
    else if (color_random==5){this->r = 1; this->g = 0; this->b = 1; this->color = "magenta";}
    else if (color_random==6){this->r = 1; this->g = 1; this->b = 1; this->color = "white";}
    else if (color_random==7){this->r = 0.5; this->g = 0.5; this->b = 0.5; this->color = "grey";}
    else{this->r = 0; this->g = 0; this->b = 0; this->color = "black";}

    this-> laps = 0;
}

void car::draw() {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
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
    }}

void car::write_info(string text){
    string text_to_write = name + text;
    if (color=="red") cout<<"\033[31m"<<text_to_write<<"\033[0m"<<endl;
    else if (color=="green") cout<<"\033[32m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="blue") cout<<"\033[34m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="yellow") cout<<"\033[33m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="cyan") cout<<"\033[36m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="magenta") cout<<"\033[35m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="grey") cout<<"\033[37m"<<name<<text<<"\033[0m"<<endl;
    else if (color=="white") cout<<"\033[0m"<<name<<text<<"\033[0m"<<endl;

    else if (color=="black") cout<<"\033[30m"<<name<<text<<"\033[0m"<<endl;
    else cout<<color<<name<<text<<"\033[0m"<<endl;

}

void car::move() {
        if (track == 2) {
            if (x >= 0.25 and direction == "right") {
                rotate_right();
            } else if (x <= -0.25 and direction == "left") {
                rotate_right();
            } else if (y >= 0.65 and direction == "up") {
                rotate_right();
                laps++;
                string text = " finished lap " + to_string(laps);
                write_info(text);
            } else if (y <= -0.65 and direction == "down") {
                rotate_right();
            }

            if (direction == "right") {
                x += 0.01;
            } else if (direction == "down") {
                y -= 0.01;
            } else if (direction == "left") {
                x -= 0.01;
            } else if (direction == "up") {
                y += 0.01;
            }
        } else if (track == 1) {
                if (x >= 0.65 and direction == "right") {
                    rotate_right();
                } else if (x <= -0.65 and direction == "left" and laps < 2) {
                    rotate_right();
                } else if (y >= 0.25 and direction == "up") {
                    rotate_right();
                    laps++;
                    string text = " finished lap " + to_string(laps);
                    write_info(text);
                } else if (y <= -0.25 and direction == "down") {
                    rotate_right();
                }

                if (direction == "right") {
                    x += 0.01;
                } else if (direction == "down") {
                    y -= 0.01;
                } else if (direction == "left") {
                    x -= 0.01;
                    if (x <= -2) {
                        write_info(" finished race");
                        finished = true;
                    }
                } else if (direction == "up") {
                    y += 0.01;
            }}}

void car::set_delay(float desired_delay){
    this->delay = desired_delay;
}

void car::simulate_car() {
    while (not finished) {
        move();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}