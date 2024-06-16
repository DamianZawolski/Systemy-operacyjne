#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "road.h"
#include "intersections.h"
#include <ctime>
#include <thread>
#include <string>
#include <vector>
#include "car.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    // Initialize GLFW
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW!" << endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(1280, 900, "Damian Zawolski 260353", nullptr, nullptr);

    if (!window)
    {
        cerr << "Failed to create window!" << endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        cerr << "Failed to initialize GLEW!" << endl;
        return -1;
    }

    srand(time(0));

    int number_of_cars_on_track1 = 100;
    int number_of_cars_on_track2 = 3;
    int number_of_intersections = 4;

    all_cars cars_on_track_1;
    all_cars cars_on_track_2;

    intersections all_intersections;

    std::vector<std::thread> thread_of_cars_on_track_1;
    std::vector<std::thread> thread_of_cars_on_track_2;

    for (int i = 0; i < number_of_cars_on_track2; i++)
    {
        string name = "car " + to_string(i) + " on track 2";
        cars_on_track_2.append_car(car(2, name, i));
    }

    for (int i = 0; i < number_of_cars_on_track1; i++)
    {
        string name = "car " + to_string(i) + " on track 1";
        cars_on_track_1.append_car(car(1, name, i));
    }

    all_intersections.set_up_number_of_intersections(number_of_intersections);

    for (auto &car : cars_on_track_2.list_of_cars)
    {
        thread_of_cars_on_track_2.emplace_back([&car, &all_intersections, &cars_on_track_1, &cars_on_track_2]()
                                               { car.simulate_car(all_intersections, cars_on_track_1, cars_on_track_2); });
    }

    std::mutex mtx_all_cars;
    for (auto &car : cars_on_track_1.list_of_cars)
    {
        thread_of_cars_on_track_2.emplace_back([&car, &all_intersections, &cars_on_track_1, &cars_on_track_2]()
                                               { car.simulate_car(all_intersections, cars_on_track_1, cars_on_track_2); });
    }
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // clear content of window
        glClear(GL_COLOR_BUFFER_BIT);
        // Render of roads and cars
        draw_all_roads();
        for (auto &car : cars_on_track_2.list_of_cars)
        {
            car.draw();
        }

        for (auto &car : cars_on_track_1.list_of_cars)
        {
            car.draw();
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // wait for 0.01 second
        glfwWaitEventsTimeout(0.01);

        // exit if space is pressed
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            // track 2 cars threads are finished immediately, for rest we have to wait
            all_intersections.set_all_unused();
            for (auto &car : cars_on_track_2.list_of_cars)
                car.finished = true;
            for (auto &car : cars_on_track_1.list_of_cars)
                car.finished = true;
            for (auto &th : thread_of_cars_on_track_2)
                th.join();
            for (auto &th : thread_of_cars_on_track_1)
                th.join();
            break;
        }
    }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
