#include "main.h"
#include <algorithm>

#ifndef SEMICIRCLE_H
#define SEMICIRCLE_H


class Semicircle {
public:
    Semicircle() {}
    Semicircle(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *ring1;
    VAO *ring2;
};

#endif // COIN_H
