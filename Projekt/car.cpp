using namespace std;
#include "car.h"
#include <GL/glew.h>
#include <unistd.h>
#include <string>
#include "iostream"


car::car(int track, string name, string color) {
    this->track = track;
    this->name = name;
    this-> finished = false;
    if (track ==1){
        this->x = (rand() % 100 -110)/10;
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

    if (color=="red"){this->r = 1; this->g = 0; this->b = 0; this->speed = 0.03; this->color = color;}
    else if (color=="green"){this->r = 0; this->g = 1; this->b = 0; this->color = color;}
    else if (color=="blue"){this->r = 0; this->g = 0; this->b = 1; this->color = color;}
    else if (color=="yellow"){this->r = 1; this->g = 1; this->b = 0; this->color = color;}
    else if (color=="cyan"){this->r = 0; this->g = 1; this->b = 1; this->color = color;}
    else if (color=="magenta"){this->r = 1; this->g = 0; this->b = 1; this->color = color;}
    else if (color=="white"){this->r = 1; this->g = 1; this->b = 1; this->color = color;}
    else if (color=="grey"){this->r = 0.5; this->g = 0.5; this->b = 0.5; this->color = color;}

    else{this->r = 0; this->g = 0; this->b = 0; this->color = color;}

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
            laps++;
            string text = " finished lap " + to_string(laps);
            write_info(text);
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
        if (not finished){
            if (x>= 0.65 and direction == "right") {
                rotate_right();
            }
            else if (x <= -0.65 and direction == "left" and laps<2) {
                rotate_right();
            }
            else if (y >= 0.25 and direction == "up") {
                rotate_right();
                laps++;
                string text = " finished lap " + to_string(laps);
                write_info(text);
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
                if (x <=-2){
                    write_info(" finished race");
                    finished = true;
                }
            }
            else if (direction == "up") {
                y += speed;
            }
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


