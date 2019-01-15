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
    bool up;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x);
    double speed;
private:
    VAO *ring1;
};

#endif // COIN_H
