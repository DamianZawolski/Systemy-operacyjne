using namespace std;
#include "car.h"
#include <GL/glew.h>
#include <string>
#include "iostream"
#include <chrono>
#include "thread"
#include <vector>
#include <cstdlib> // Include this header for the rand() function
#include <ctime>   // Include this header for the time() function

std::mutex m;
car::car(int track, string name, int id)
{
    this->intersection = 0;
    this->id = id;
    this->track = track;
    this->name = name;
    this->finished = false;
    this->on_intersection = false;
    this->stopped = 0;
    if (track == 1)
    {
        this->x = (rand() % 100 - 110) / 10;
        this->y = 0.25;
        this->direction = "right";
    }
    else
    {
        // Seed the random number generator at the beginning of the program

        int rand_wall = rand() % 4;
        if (rand_wall == 0)
        {
            // between -0.6 and 0.6 for y
            this->x = 0.25;
            this->y = -0.6f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.2f));
            this->direction = "right";
        }
        else if (rand_wall == 1)
        {
            // between -0.6 and 0.6 for y
            this->x = -0.25;
            this->y = -0.6f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.2f));
            this->direction = "left";
        }
        else if (rand_wall == 2)
        {
            // between -0.2 and 0.2 for x
            this->x = -0.2f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
            this->y = 0.65;
            this->direction = "right";
        }
        else
        {
            // between -0.2 and 0.2 for x
            this->x = -0.2f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
            this->y = -0.65;
            this->direction = "left";
        }
    }
    // width is random between 0.09 and 0.15
    float width_value = (rand() % 7 + 9) / 100.0;
    // height is random between 0.04 and 0.07
    float height_value = (rand() % 4 + 4) / 100.0;
    this->width = width_value;
    this->height = height_value;
    // delay is random between 10 and 30 (slower is faster)
    float delay_value = (rand() % 21 + 20);
    if (track == 2)
    {
        delay_value = 20;
    }
    this->delay = delay_value;
    int color_random = (rand() % 9);
    if (color_random == 0)
    {
        this->r = 1;
        this->g = 0;
        this->b = 0;
        this->color = "red";
    }
    else if (color_random == 1)
    {
        this->r = 0;
        this->g = 1;
        this->b = 0;
        this->color = "green";
    }
    else if (color_random == 2)
    {
        this->r = 0;
        this->g = 0;
        this->b = 1;
        this->color = "blue";
    }
    else if (color_random == 3)
    {
        this->r = 1;
        this->g = 1;
        this->b = 0;
        this->color = "yellow";
    }
    else if (color_random == 4)
    {
        this->r = 0;
        this->g = 1;
        this->b = 1;
        this->color = "cyan";
    }
    else if (color_random == 5)
    {
        this->r = 1;
        this->g = 0;
        this->b = 1;
        this->color = "magenta";
    }
    else if (color_random == 6)
    {
        this->r = 1;
        this->g = 1;
        this->b = 1;
        this->color = "white";
    }
    else if (color_random == 7)
    {
        this->r = 0.5;
        this->g = 0.5;
        this->b = 0.5;
        this->color = "grey";
    }
    else
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->color = "black";
    }

    this->laps = 0;
}

void car::draw()
{
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();
}

void car::rotate_right()
{
    float temp = width;
    width = height;
    height = temp;

    if (direction == "right")
    {
        direction = "down";
    }
    else if (direction == "down")
    {
        direction = "left";
    }
    else if (direction == "left")
    {
        direction = "up";
    }
    else if (direction == "up")
    {
        direction = "right";
    }
}

void car::write_info(string text)
{
    string text_to_write = name + text;
    if (color == "red")
        cout << "\033[31m" << text_to_write << "\033[0m" << endl;
    else if (color == "green")
        cout << "\033[32m" << name << text << "\033[0m" << endl;
    else if (color == "blue")
        cout << "\033[34m" << name << text << "\033[0m" << endl;
    else if (color == "yellow")
        cout << "\033[33m" << name << text << "\033[0m" << endl;
    else if (color == "cyan")
        cout << "\033[36m" << name << text << "\033[0m" << endl;
    else if (color == "magenta")
        cout << "\033[35m" << name << text << "\033[0m" << endl;
    else if (color == "grey")
        cout << "\033[37m" << name << text << "\033[0m" << endl;
    else if (color == "white")
        cout << "\033[0m" << name << text << "\033[0m" << endl;

    else if (color == "black")
        cout << "\033[30m" << name << text << "\033[0m" << endl;
    else
        cout << color << name << text << "\033[0m" << endl;
}

void car::move(intersections &all_intersections, all_cars &cars_on_track_1, all_cars &cars_on_track_2)
{
    if (track == 2)
    {

        if (x >= 0.25 and direction == "right")
        {
            rotate_right();
        }
        else if (x <= -0.25 and direction == "left")
        {
            rotate_right();
        }
        else if (y >= 0.65 and direction == "up")
        {
            rotate_right();
            laps++;
            string text = " finished lap " + to_string(laps);
            write_info(text);
        }
        else if (y <= -0.65 and direction == "down")
        {
            rotate_right();
        }
        std::unique_lock<std::mutex> lock(m);
        if (x >= -0.3 and x <= -0.2 and y >= 0.05 and y <= 0.15 and all_intersections.return_intersection_state(0) > 0)
        {
            all_intersections.get_cv_intersection(0)->wait(lock, [&all_intersections]
                                                           { return all_intersections.get_intersection_ready(0); });
        }
        else if (x >= 0.2 and x <= 0.3 and y >= 0.35 and y <= 0.45 and all_intersections.return_intersection_state(1) > 0)
        {
            all_intersections.get_cv_intersection(1)->wait(lock, [&all_intersections]
                                                           { return all_intersections.get_intersection_ready(1); });
        }
        else if (x >= -0.3 and x <= -0.2 and y >= -0.45 and y <= -0.35 and all_intersections.return_intersection_state(2) > 0)
        {
            all_intersections.get_cv_intersection(2)->wait(lock, [&all_intersections]
                                                           { return all_intersections.get_intersection_ready(2); });
        }
        else if (x >= 0.2 and x <= 0.3 and y >= -0.15 and y <= -0.05 and all_intersections.return_intersection_state(3) > 0)
        {
            all_intersections.get_cv_intersection(3)->wait(lock, [&all_intersections]
                                                           { return all_intersections.get_intersection_ready(3); });
        }

        if (direction == "right")
        {
            x += 0.01;
        }
        else if (direction == "down")
        {
            y -= 0.01;
        }
        else if (direction == "left")
        {
            x -= 0.01;
        }
        else if (direction == "up")
        {
            y += 0.01;
        }
    }
    else if (track == 1 and stopped == 0)
    {
        if (x >= 0.65 and direction == "right")
        {
            rotate_right();
        }
        else if (x <= -0.65 and direction == "left" and laps < 2)
        {
            rotate_right();
        }
        else if (y >= 0.25 and direction == "up")
        {
            rotate_right();
            laps++;
            string text = " finished lap " + to_string(laps);
            write_info(text);
        }
        else if (y <= -0.25 and direction == "down")
        {
            rotate_right();
        }

        if (direction == "right" and stopped == 0)
        {
            x += 0.01;
        }
        else if (direction == "down" and stopped == 0)
        {
            y -= 0.01;
        }
        else if (direction == "left" and stopped == 0)
        {
            x -= 0.01;
            if (x <= -2)
            {
                write_info(" finished race");
                finished = true;
            }
        }
        else if (direction == "up" and stopped == 0)
        {
            y += 0.01;
        }

        // entering intersection
        if (x >= -0.6 and x <= -0.2 and y >= 0.2 and y <= 0.3 and not on_intersection)
        {
            all_intersections.add_car_to_intersection(0);
            this->on_intersection = true;
        }
        else if (x >= -0.1 and x <= 0.3 and y >= 0.2 and y <= 0.3 and not on_intersection)
        {
            all_intersections.add_car_to_intersection(1);
            this->on_intersection = true;
        }
        else if (x >= -0.3 and x <= 0.1 and y >= -0.3 and y <= -0.2 and not on_intersection)
        {
            all_intersections.add_car_to_intersection(2);
            this->on_intersection = true;
        }
        else if (x >= 0.2 and x <= 0.6 and y >= -0.3 and y <= -0.2 and not on_intersection)
        {
            all_intersections.add_car_to_intersection(3);
            this->on_intersection = true;
        }
        // leaving intersection
        if (x >= -0.2 and x <= -0.1 and y >= 0.2 and y <= 0.3 and on_intersection)
        {
            all_intersections.del_car_from_intersection(0);
            this->on_intersection = false;
        }
        else if (x >= 0.3 and x <= 0.4 and y >= 0.2 and y <= 0.3 and on_intersection)
        {
            all_intersections.del_car_from_intersection(1);
            this->on_intersection = false;
        }
        else if (x >= -0.4 and x <= -0.3 and y >= -0.3 and y <= -0.2 and on_intersection)
        {
            all_intersections.del_car_from_intersection(2);
            this->on_intersection = false;
        }
        else if (x >= 0.1 and x <= 0.2 and y >= -0.3 and y <= -0.2 and on_intersection)
        {
            all_intersections.del_car_from_intersection(3);
            this->on_intersection = false;
        }
    }
}

void car::set_delay(float desired_delay)
{
    this->delay = desired_delay;
}

void car::simulate_car(intersections &all_intersections, all_cars &cars_on_track_1, all_cars &cars_on_track_2)
{

    bool run = false;
    while (not run and track == 1)
    {
        int random_number = (rand() % 1000);
        if (not finished and random_number > 1)
        {
            int random_time = (rand() % 1000 + 100);
            std::this_thread::sleep_for(std::chrono::milliseconds(random_time));
        }
        else
        {
            run = true;
        }
    }

    while (not finished)
    {
        move(all_intersections, cars_on_track_1, cars_on_track_2);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}