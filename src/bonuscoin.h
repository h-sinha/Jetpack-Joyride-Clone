#include "main.h"

#ifndef BONUSCOIN_H
#define BONUSCOIN_H


class BonusCoin {
public:
    BonusCoin() {}
    BonusCoin(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    float rotation;
    int flag;
    float gravity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *ring1;
    VAO *ring2;
    VAO *rect1;
    VAO *rect2;
};

#endif // COIN_H
