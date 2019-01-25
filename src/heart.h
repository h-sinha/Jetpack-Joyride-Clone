#include "main.h"

#ifndef HEART_H
#define HEART_H


class Heart {
public:
    Heart() {}
    Heart(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
private:
    VAO *tri;
    VAO *c1;
    VAO *c2;
};

#endif // PLAYER_H
