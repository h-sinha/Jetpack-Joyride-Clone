#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class  {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
     float length;
    float width;
     float scalex;
    float scaley;
    float scalez;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double rotation;
    double speed;
private:
    VAO *ring1;
    VAO *ring2;
    VAO *line;
};

#endif // WALL_H
