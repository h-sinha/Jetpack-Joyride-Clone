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
     float scalex;
    float scaley;
    float scalez;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move(int up);
    double speed;
private:
    VAO *blackring;
    VAO *whitering;
    VAO *whiteeye1;
    VAO *whiteeye2;
    VAO *blackeye1;
    VAO *blackeye2;
    VAO *nose;
    VAO *jet1;
    VAO *jet2;
};

#endif // PLAYER_H
