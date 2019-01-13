#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
     float length;
    float width;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move(int up);
    double speed;
private:
    VAO *object;
};

#endif // PLAYER_H
