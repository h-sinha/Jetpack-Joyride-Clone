#include "main.h"

#ifndef SWORD_H
#define SWORD_H


class Sword {
public:
    Sword() {}
    Sword(float x, float y);
    glm::vec3 position;
    glm::vec4 line[4];
    float rotation;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double speed;
private:
    VAO* blade1;
    VAO* blade2;
    VAO* blade3;
    VAO* handle;
};

#endif // PLAYER_H
