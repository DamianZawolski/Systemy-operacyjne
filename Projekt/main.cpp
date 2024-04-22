#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "road.h"
#include "car.h"
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

    srand((unsigned) time(nullptr));
    int number_of_cars_on_track2 = 3;
    std::vector<car> cars_on_track_2;
    std::vector<std::thread> thread_of_cars_on_track_2;

    for (int i=0; i<number_of_cars_on_track2; i++)
    {
        string name = "car " + to_string(i+1) + " on track 2";
        cars_on_track_2.push_back(car(2, name));
    }
    for (auto &car: cars_on_track_2) {
        thread_of_cars_on_track_2.emplace_back(std::thread(&car::simulate_car, &car));
    }

    car car1_track1 = car(1, "car 1 on track 1");
    car car2_track1 = car(1, "car 2 on track 1");
    car car3_track1 = car(1, "car 3 on track 1");
    car car4_track1 = car(1, "car 4 on track 1");
    car car5_track1 = car(1, "car 5 on track 1");
    car car6_track1 = car(1, "car 6 on track 1");
    car car7_track1 = car(1, "car 7 on track 1");
    car car8_track1 = car(1, "car 8 on track 1");
    car car9_track1 = car(1, "car 9 on track 1");

    thread thread_c1_t1(&car::simulate_car, &car1_track1);
    thread thread_c2_t1(&car::simulate_car, &car2_track1);
    thread thread_c3_t1(&car::simulate_car, &car3_track1);
    thread thread_c4_t1(&car::simulate_car, &car4_track1);
    thread thread_c5_t1(&car::simulate_car, &car5_track1);
    thread thread_c6_t1(&car::simulate_car, &car6_track1);
    thread thread_c7_t1(&car::simulate_car, &car7_track1);
    thread thread_c8_t1(&car::simulate_car, &car8_track1);
    thread thread_c9_t1(&car::simulate_car, &car9_track1);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        //clear content of window
        glClear(GL_COLOR_BUFFER_BIT);
        // Render of roads and cars
        draw_all_roads();
        for(auto& car : cars_on_track_2)
            car.draw();

        car1_track1.draw();
        car2_track1.draw();
        car3_track1.draw();
        car4_track1.draw();
        car5_track1.draw();
        car6_track1.draw();
        car7_track1.draw();
        car8_track1.draw();
        car9_track1.draw();

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
            for(auto& th : thread_of_cars_on_track_2)
                th.join();

            thread_c1_t1.join();
            thread_c2_t1.join();
            thread_c3_t1.join();
            thread_c4_t1.join();
            thread_c5_t1.join();
            thread_c6_t1.join();
            thread_c7_t1.join();
            thread_c8_t1.join();
            thread_c9_t1.join();
            break;
        }
    }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}
