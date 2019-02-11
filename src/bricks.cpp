#include "bricks.h"
#include "main.h"

Brick::Brick(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.1;
    this->width = 0.2;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
    static const GLfloat vertex_buffer_data[] = {
        0.0f , 0.2f, 0.0f,    
        0.0f , 0.0f, 0.0f,    
        0.4f , 0.0f, 0.0f,    
        0.4f , 0.2f, 0.0f,    
        0.4f , 0.0f, 0.0f,    
        0.0f, 0.2f, 0.0f,    
     };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Brick::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Brick::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Brick::tick() {
    this->position.x -= GameSpeed;
    if(this->position.x <= -0.8)
      this->position.x += 5.8;
    else if(this->position.x > 5.6)
        this->position.x -= 5.8;
    this->set_position(this->position.x, this->position.y);

}

