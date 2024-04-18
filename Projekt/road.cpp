//
// Created by damian-zawolski on 18.04.24.
//

#include "road.h"
#include <GL/glew.h>

void draw_road(float corner1_x, float corner1_y, float corner2_x, float corner2_y){
    glVertex2f(corner1_x, corner1_y);
    glVertex2f(corner2_x, corner1_y);
    glVertex2f(corner2_x, corner2_y);
    glVertex2f(corner1_x, corner2_y);
}
void draw_all_roads(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.1);
    float corner1_x = -0.7f;
    float corner1_y = 0.2f;
    float corner2_x = 0.7f;
    float corner2_y = 0.3f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_y = -0.2f;
    corner2_y = -0.3f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_x = -0.7f;
    corner1_y = -0.3f;
    corner2_x = -0.6f;
    corner2_y = 0.3f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_x = 0.7f;
    corner2_x = 0.6f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_x = -0.2f;
    corner1_y = -0.7f;
    corner2_x = 0.2f;
    corner2_y = -0.6f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_y = 0.7f;
    corner2_y = 0.6f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_x = -0.3f;
    corner1_y = 0.7f;
    corner2_x = -0.2f;
    corner2_y = -0.7f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);

    corner1_x = 0.3f;
    corner2_x = 0.2f;
    draw_road(corner1_x, corner1_y, corner2_x, corner2_y);
    glEnd();
}