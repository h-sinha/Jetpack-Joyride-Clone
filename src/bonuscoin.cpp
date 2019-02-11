#include "bonuscoin.h"
#include "main.h"
#include "functions.h"
const double PI = 3.141592653589793238460;

BonusCoin::BonusCoin(float x, float y, color_t color) {
   
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
      GLfloat vertex_buffer_data[9*15];
      makePolygon(0,0,0,0.2,0.2,15, vertex_buffer_data);
       GLfloat vertex_buffer_data1[9*15];
    cur = 0;
    for (int i = 1; i <= 15; ++i)
     {
        vertex_buffer_data1[cur] =  0.3 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = -0.08 +  0.12 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = 0.0;
        vertex_buffer_data1[cur+3] = 0.3 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = -0.08 + 0.12 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = 0.0;
        vertex_buffer_data1[cur+6] = 0.0;
        vertex_buffer_data1[cur+7] = 0.0;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
       static const GLfloat vertex_buffer_data2[] = {
        -0.2f, -0.15f, -2.0f, 
        -0.1f, -0.15f, -2.0f, 
        -0.15f, -0.25f, -2.0f, 
     };
      static const GLfloat vertex_buffer_data3[] = {
        0.2f, -0.15f, -2.0f, 
        0.1f, -0.15f, -2.0f, 
        0.15f, -0.25f, -2.0f, 
     };
    this->ring1 = create3DObject(GL_TRIANGLES, 3*15, vertex_buffer_data, COLOR_GAINS_BORO, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3*15, vertex_buffer_data1, COLOR_MIDNIGHT_BLUE, GL_FILL);
    this->rect1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->rect2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->position = glm::vec3(0.0, 0.6, 0);
}

void BonusCoin::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate *  scale );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
    draw3DObject(this->rect1);
    draw3DObject(this->rect2);
}

void BonusCoin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void BonusCoin::tick() {
  this->position.y += this->speed;

  this->speed += this->gravity;
  this->position.x += 0.01;
    if(this->position.y >= Top)
    {
      this->speed = 0;
    }
    if(this->position.y <= Bottom + 0.2)
      this->speed = 0.05;
    if(this->position.x < -5.0 || this->position.x > 9.0)
    {
        this->position.x = 0.0;
        this->position.y = 0.6;
        this->flag = 0;
        this->speed = 0.05;
    }
}

