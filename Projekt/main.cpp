#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "road.h"
#include "car.h"
#include <ctime>


int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Damian Zawolski 260353", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create window!" << endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW!" << endl;
        return -1;
    }

    srand((unsigned) time(nullptr));
    draw_all_roads();
    car car1_track2 = car(2, "car 1 on track 2", "red");
    car car2_track2 = car(2, "car 2 on track 2", "green");
    car car3_track2 = car(2, "car 3 on track 2", "yellow");

    car1_track2.set_speed(0.01);
    car2_track2.set_speed(0.01);
    car3_track2.set_speed(0.01);

    car all_cars_track2[3] = {car1_track2, car2_track2, car3_track2};


    car car1_track1 = car(1, "car 1 on track 1", "blue");
    car car2_track1 = car(1, "car 2 on track 1", "magenta");
    car car3_track1 = car(1, "car 3 on track 1", "cyan");
    car car4_track1 = car(1, "car 4 on track 1", "white");
    car car5_track1 = car(1, "car 5 on track 1", "red");
    car car6_track1 = car(1, "car 6 on track 1", "green");
    car car7_track1 = car(1, "car 7 on track 1", "yellow");
    car car8_track1 = car(1, "car 8 on track 1", "black");
    car car9_track1 = car(1, "car 9 on track 1", "grey");

    car all_cars_track1[9] = {car1_track1, car2_track1, car3_track1, car4_track1, car5_track1, car6_track1, car7_track1, car8_track1, car9_track1};

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        //clear content of window
        glClear(GL_COLOR_BUFFER_BIT);
        // Render here
        draw_all_roads();

        for (auto & car : all_cars_track2){
            car.move();
            car.draw();
        }

        for (auto & car : all_cars_track1){
            car.move();
            car.draw();
            }


            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();

            // wait for 1 second
            glfwWaitEventsTimeout(0.01);

            //exit if space is pressed
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                break;
            }
        }

        // Terminate GLFW
        glfwTerminate();

        return 0;
    }
