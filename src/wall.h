#include "main.h"

#ifndef WALL_H
#define WALL_H


class Wall {
public:
    Wall() {}
    Wall(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double rotation;
    double speed;
private:
    VAO *object;
};

#endif // WALL_H
