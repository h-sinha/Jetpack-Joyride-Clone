#include "main.h"
#ifndef FUNC_H
#define FUNC_H

std::string sevenSegment(char s);
bool on_line(float x1, float y1, float x2, float y2, float px, float py);
int direction(float ax, float ay, float bx, float by, float cx, float cy);
bool check_intersection(glm::vec4 l1, glm::vec4 l2);
void makePolygon(float xoffset, float yoffset,float zoffset, float r1, float r2, int n, GLfloat vertex_buffer_data[]);
#endif