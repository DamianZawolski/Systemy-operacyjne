#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "road.h"
#include "car.h"
#include "intersection.h"
#include <ctime>
#include <thread>
#include <string>
#include <vector>



int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!" << endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(960, 640, "Damian Zawolski 260353", nullptr, nullptr);
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

    srand(time(0));

    int number_of_cars_on_track1 = 100;
    int number_of_cars_on_track2 = 3;
    int number_of_intersections = 4;

    std::vector<car> cars_on_track_1;
    std::vector<car> cars_on_track_2;
    std::vector<intersection> intersections;

    std::vector<std::thread> thread_of_cars_on_track_1;
    std::vector<std::thread> thread_of_cars_on_track_2;

    for (int i=0; i<number_of_cars_on_track2; i++)
    {
        string name = "car " + to_string(i+1) + " on track 2";
        cars_on_track_2.push_back(car(2, name));
    }

    for (int i=0; i<number_of_cars_on_track1; i++)
    {
        string name = "car " + to_string(i+1) + " on track 1";
        cars_on_track_1.push_back(car(1, name));
    }

    for (int i=0; i<number_of_intersections; i++)
    {
        intersections.push_back(intersection());
    }

    for (auto &car: cars_on_track_2) {
        thread_of_cars_on_track_2.emplace_back(std::thread(&car::simulate_car, &car));
    }

    for (auto &car: cars_on_track_1) {
        thread_of_cars_on_track_1.emplace_back(std::thread(&car::simulate_car, &car));
    }


    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        //clear content of window
        glClear(GL_COLOR_BUFFER_BIT);
        // Render of roads and cars
        draw_all_roads();
        for(auto& car : cars_on_track_2)
        {
            car.draw();
        }

        for(auto& car : cars_on_track_1)
        {
            car.draw();
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // wait for 0.01 second
        glfwWaitEventsTimeout(0.01);

        //exit if space is pressed
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            //track 2 cars threads are finished immediately, for rest we have to wait
            for(auto& car : cars_on_track_2)
                car.finished= true;
            for(auto& car : cars_on_track_1)
                car.finished= true;
            for(auto& th : thread_of_cars_on_track_2)
                th.join();
            for(auto& th : thread_of_cars_on_track_1)
                th.join();
            break;
        }
    }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
