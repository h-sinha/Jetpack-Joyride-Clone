#include "main.h"

#ifndef SPEED_H
#define SPEED_H


class Speed {
public:
    Speed() {}
    Speed(float x, float y);
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
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // COIN_H
