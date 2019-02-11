#include "magnet.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Magnet::Magnet(float x, float y, color_t color) {
   
    speed = GameSpeed;
    float x1,y1,x2,y2,xx,yy;
    xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    yy = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    // xx = 1.0, yy = 1.0;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 0.2;
    this->width = 0.2;
     int n=15, cur = 0;
     this->rotation = 0.1;
      GLfloat vertex_buffer_data[9*7];
    for (int i = 4; i <= 10; ++i)
     {
        vertex_buffer_data[cur] =  0.05 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] = 0.05 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = 0.05 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = 0.05 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = 0.0;
        cur += 9;
     } 
       GLfloat vertex_buffer_data1[9*7];
    cur = 0;
    for (int i = 4; i <= 10; ++i)
     {
        vertex_buffer_data1[cur] =  0.025 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 0.025 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = 0.0;
        vertex_buffer_data1[cur+3] = 0.025 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = 0.025 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = 0.0;
        vertex_buffer_data1[cur+6] = 0.0;
        vertex_buffer_data1[cur+7] = 0.0;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
       static const GLfloat vertex_buffer_data2[] = {
        -0.005f, -0.05f, 0.0f, 
        -0.005f, -0.025f, 0.0f, 
        0.05f, -0.05f, 0.0f, 
        -0.005f, -0.025f, 0.0f, 
        0.05f, -0.025f, 0.0f, 
        0.05f, -0.05f, 0.0f, 
     };
      static const GLfloat vertex_buffer_data3[] = {
        -0.005f, 0.025f, 0.0f, 
        -0.005f, 0.05f, 0.0f, 
        0.05f, 0.025f, 0.0f, 
        -0.005f, 0.05f, 0.0f, 
        0.05f, 0.05f, 0.0f, 
        0.05f, 0.025f, 0.0f, 
     };
    this->ring1 = create3DObject(GL_TRIANGLES, 3*7, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3*7, vertex_buffer_data1, COLOR_BACKGROUND, GL_FILL);
    this->rect1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->rect2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->position = glm::vec3(xx, yy, 0);
}

void Magnet::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    glm::mat4 scale1    = glm::scale(glm::vec3(2.0, 2.0, 2.0));
    Matrices.model *= (translate *  scale * scale1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
    draw3DObject(this->rect1);
    draw3DObject(this->rect2);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    this->position.x -= GameSpeed;
    if(this->position.x < -10.0)
    {
        this->position.x = 8.0 + 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.y = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    }
    if(this->position.x > 15.0)
    {
        this->position.x = -3.0 + 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.y = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    }
}

