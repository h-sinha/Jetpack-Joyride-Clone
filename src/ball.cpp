#include "ball.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.3;
    this->length = 0.3;
    this->width = 0.3;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->speed = GameSpeed;
    int cur = 0, n = 15;
    GLfloat vertex_buffer_data[9*15];
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    for (int i = 1; i <= 15; ++i)
     {
        vertex_buffer_data[cur] =  0.1 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] = 0.1 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = 0.1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = 0.1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = 0.0;
        cur += 9;
     } 
    this->object = create3DObject(GL_TRIANGLES, 15*3, vertex_buffer_data, COLOR_BALL, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= GameSpeed;
    // this->rotation += speed;
    this->position.x += 0.03;
    this->position.y += this->speed;
   this->speed -= 0.0005;
    // this->set_position(this->position.x, this->position.y);
    // printf("%f %f\n",speed, this->position.x );
}
