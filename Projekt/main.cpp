#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "road.h"
#include "car.h"
#include "time.h"

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

    srand((unsigned) time(NULL));
    draw_all_roads();
    car car1_track2 = car(2);
    car car2_track2 = car(2);
    car car3_track2 = car(2);

    car1_track2.set_speed(0.01);
    car2_track2.set_speed(0.01);
    car3_track2.set_speed(0.01);


    car car1_track1 = car(1);
    car1_track1.set_speed(0.02);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        //clear content of window
        glClear(GL_COLOR_BUFFER_BIT);
        // Render here
        draw_all_roads();

        car1_track2.move();
        car2_track2.move();
        car3_track2.move();
        car1_track2.draw();
        car2_track2.draw();
        car3_track2.draw();

        car1_track1.move();
        car1_track1.draw();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // wait for 1 second
        glfwWaitEventsTimeout(0.01);
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
