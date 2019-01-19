#include "main.h"

#ifndef ICE_H
#define ICE_H


class Ice {
public:
    Ice() {}
    Ice(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    float width;
    float scalex;
    float scaley;
    float scalez;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
