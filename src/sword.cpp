#include "sword.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Sword::Sword(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.4;
    this->width = 0.4;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 0.0;
    speed = 0.02;
    int cur = 0, n = 20;
    this->position = glm::vec3(x, y , 0);
    static const GLfloat vertex_buffer_blade1[] = {
       0.0f, 0.2f, 0.0f,
       0.32f, 0.2f, 0.0f,
       0.32f, 0.24f, 0.0f,
    };
     static const GLfloat vertex_buffer_blade2[] = {
        0.0f, 0.2f, 0.0f,
       0.32f, 0.2f, 0.0f,
       0.32f, 0.16f, 0.0f,
    };
     static const GLfloat vertex_buffer_blade3[] = {
       0.32f, 0.24f, 0.0f,
       0.32f, 0.16f, 0.0f,
       0.4f, 0.2f, 0.0f,
    };
     static const GLfloat vertex_buffer_handle[] = {
       0.0f, 0.22f, 0.0f,
       0.06f, 0.18f, 0.0f,
       0.0f, 0.18f, 0.0f,

       0.06f, 0.18f, 0.0f,
       0.06f, 0.22f, 0.0f,
       0.0f, 0.22f, 0.0f,

    };
    this->blade1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_blade1, COLOR_GAINS_BORO, GL_FILL);
    this->blade2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_blade2, COLOR_GAINS_BORO, GL_FILL);
    this->blade3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_blade3, COLOR_GAINS_BORO, GL_FILL);
    this->handle = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_handle, COLOR_BROWN, GL_FILL);
}

void Sword::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->blade1);
    draw3DObject(this->blade2);
    draw3DObject(this->blade3);
    draw3DObject(this->handle);
}

void Sword::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

