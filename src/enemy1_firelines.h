#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec4 line[6];
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
    // VAO *lin;
};

#endif // COIN_H
