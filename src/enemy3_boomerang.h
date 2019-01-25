#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    float rotation;
    float gravity;
    float theta;
    float center;
    bool up, left, flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x);
    double speed;
private:
    VAO *ring1;
    VAO *ring2;
    VAO *ring3;
    VAO *tri;
};

#endif // COIN_H
