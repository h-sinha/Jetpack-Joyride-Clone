#include "ice.h"
#include "main.h"
#include "functions.h"
const double PI = 3.141592653589793238460;

Ice::Ice(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.3;
    this->length = 0.3;
    this->width = 0.3;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
    int cur = 0, n = 5;
    GLfloat vertex_buffer_data[9*n];
    makePolygon(0, 0, 0, 0.1, 0.1, n, vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data,COLOR_DARK_RED, GL_FILL);
}

void Ice::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ice::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ice::tick() {
    this->position.x -= GameSpeed;
    this->position.x -= 0.03;
    this->position.y += speed;
    speed -= 0.0005;
}
