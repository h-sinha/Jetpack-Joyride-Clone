#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color, float init_speed) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.3;
    this->width = 0.3;
    speed = init_speed;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
          x -0.3f,y-0.3f,0.0f, // triangle 1 : begin
       x -0.3f,y-0.3f, 0.0f,
      x  -0.3f, y+0.3f, 0.0f, // triangle 1 : end
      x + 0.3f,y+ 0.3f,0.0f, // triangle 2 : begin
      x  -0.3f,y-0.3f,0.0f,
      x  -0.3f,y+ 0.3f,0.0f, // triangle 2 : end
      x + 0.3f,y-0.3f, 0.0f,
      x  -0.3f,y-0.3f,0.0f,
      x  +0.3f,y-0.3f,0.0f,
      x + 0.3f,y+ 0.3f,0.0f,
       x +0.3f,y-0.3f,0.0f,
       x -0.3f,y-0.3f,0.0f,
      x  -0.3f,y-0.3f,0.0f,
      x  -0.3f,y+ 0.3f, 0.0f,
      x  -0.3f, y+0.3f,0.0f,
      x + 0.3f,y-0.3f, 0.0f,
      x  -0.3f,y-0.3f, 0.0f,
      x  -0.3f,y-0.3f,0.0f,
      x  -0.3f,y+ 0.3f, 0.0f,
      x  -0.3f,y-0.3f, 0.0f,
      x + 0.3f,y-0.3f, 0.0f,
      x + 0.3f,y+ 0.3f, 0.0f,
      x + 0.3f,y-0.3f,0.0f,
      x  +0.3f, y+0.3f,0.0f,
      x+  0.3f,y+0.3f,0.0f,
      x + 0.3f, y+0.3f, 0.0f,
      x + 0.3f,y-0.3f, 0.0f,
      x + 0.3f,y+0.3f, 0.0f,
      x + 0.3f, y+0.3f,0.0f,
      x  -0.3f, y+0.3f,0.0f,
      x + 0.3f, y+0.3f, 0.0f,
      x  -0.3f, y+0.3f,0.0f,
      x  -0.3f,y+0.3f, 0.0f,
      x + 0.3f, y+0.3f, 0.0f,
      x  -0.3f, y+0.3f, 0.0f,
      x + 0.3f,y-0.3f, 0.0f
    
     };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
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
    // this->rotation += speed;
    this->position.x -= speed;
    // this->position.y -= speed;
    // this->set_position(this->position.x, this->position.y);
    // printf("%f %f\n",speed, this->position.x );
}
