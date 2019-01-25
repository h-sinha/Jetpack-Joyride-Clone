#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H


class Shield {
public:
    Shield() {}
    Shield(float x, float y);
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
