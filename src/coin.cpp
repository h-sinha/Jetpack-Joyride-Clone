#include "coin.h"
#include "main.h"
const double PI = 3.141592653589793238460;
float cur=0;
Coin::Coin(float x, float y, color_t color, int flag) {
    this->rotation = 0;
    this->length = 0.2;
    this->width = 0.2;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 15;
    GLfloat vertex_buffer_data[9*n];
    GLfloat vertex_buffer_data1[9*n];
    GLfloat vertex_buffer_data2[9*n];
    // x = 0.9;
    // y = 0.3 + cur;
    // cur+=0.3;
    if(flag == 0)
    {
        x = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
        y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    }
    this->position = glm::vec3(x, y  , -10.0);
    
    int cur = 0;
    for (int i = 1; i <= n; ++i)
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
     cur = 0;
   for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  0.09 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 0.09 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = 0.0;
        vertex_buffer_data1[cur+3] = 0.09 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = 0.09 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = 0.0;
        vertex_buffer_data1[cur+6] = 0.0;
        vertex_buffer_data1[cur+7] = 0.0;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
     cur = 0;
   for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data2[cur] =  0.08 * cos((2.0*PI*i)/n);
        vertex_buffer_data2[cur+1] = 0.08 * sin((2.0*PI*i)/n);
        vertex_buffer_data2[cur+2] = 0.0;
        vertex_buffer_data2[cur+3] = 0.08 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+4] = 0.08 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+5] = 0.0;
        vertex_buffer_data2[cur+6] = 0.0;
        vertex_buffer_data2[cur+7] = 0.0;
        vertex_buffer_data2[cur+8] = 0.0;
        cur += 9;
     } 
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
    this->ring = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->ring1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    glm::mat4 rotate    = glm::rotate(this->rotation, glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->ring);
    // draw3DObject(this->ring1);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    this->rotation += 0.01;
    this->position.x -= GameSpeed;
    if(this->position.x <-6.0)
      this->position.x += 12.0;
    else if(this->position.x > 6.0)
      this->position.x -= 12.0;
}
