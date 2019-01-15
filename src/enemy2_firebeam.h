#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color);
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
    void tick();
    double speed;
private:
    VAO *ring1;
    VAO *ring2;
    VAO *line;
    VAO *square1;
    VAO *square2;
};

#endif // COIN_H
