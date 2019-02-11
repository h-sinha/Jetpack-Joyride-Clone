#include "dragon.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Dragon::Dragon(float x, float y, color_t color) {
   
    speed = GameSpeed;
    float x1,y1,x2,y2,xx,yy;
    xx = 3.0, yy = 3.0;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 0.2;
    this->width = 0.2;
    this->flag = 0;
     int n=15, cur = 0;
     this->rotation = 0.1;
     this->speed = 0.05;
     this->gravity = -0.05/60.0;
     this->length = 0.4;
     this->width = 0.4;
       static const GLfloat vertex_buffer_data[] = {
            0.2f, 0.4f, 0.0f,
            0.25f, 0.3f, 0.0f,
            0.0f, 0.2f, 0.0f,
     };
      static const GLfloat vertex_buffer_data1[] = {
        0.0f, 0.0f, 0.0f, 
        0.2f, 0.4f, 0.0f, 
        0.4f, 0.0f, 0.0f, 
     };
      static const GLfloat vertex_buffer_data2[] = {
        0.15f, 0.32f, 0.0f, 
        0.2f, 0.32f, 0.0f, 
        0.175f, 0.36f, 0.0f, 
     };
    this->tri1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->mouth1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
    this->mouth2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->position = glm::vec3(8.0, 0.4, 0);
}

void Dragon::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model = (translate *  scale );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->tri1);
    draw3DObject(this->mouth1);
    draw3DObject(this->mouth2);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
  this->position.y += this->speed;

  this->speed += this->gravity;
  this->position.x -= 0.01;
    if(this->position.y >= Top - 0.4)
    {
      this->speed = 0;
    }
    if(this->position.y <= Bottom)
      this->speed = 0.05;
    if(this->position.x < -20.0 || this->position.x > 20.0)
    {
        this->position.x = 8.0;
        this->position.y = Bottom;
        this->flag = 0;
        this->speed = 0.05;
    }
}

