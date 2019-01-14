#include "main.h"

#ifndef BRICKS_H
#define BRICKS_H


class Brick {
public:
    Brick() {}
    Brick(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double rotation;
    double speed;
private:
    VAO *object;
};

#endif // BRICKS_H
