#include "enemy3_boomerang.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Boomerang::Boomerang(float x, float y, color_t color) {
   
    this->speed = 0.05;
    up = 1;
    this->left = 0;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 0.8; 
    this->width = 0.2;
    this->flag = 0;
    this->center = 2.0;
     this->gravity = -0.05/60.0;
     int n=15, cur = 0;
     this->theta = PI/4.0;
      static const GLfloat vertex_buffer_data[] = {
        0.0f , 0.1f, 0.0f,    
        0.1f , 0.0f, 0.0f,    
        0.0f , 0.0f, 0.0f,    
     };
     GLfloat vertex_buffer_data1[9*n];
     GLfloat vertex_buffer_data2[9*n];
     GLfloat vertex_buffer_data3[9*n];
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data1[cur] =  0.02 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 0.02 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = 0.0;
        vertex_buffer_data1[cur+3] = 0.02 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = 0.02 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = 0.0;
        vertex_buffer_data1[cur+6] = 0.0;
        vertex_buffer_data1[cur+7] = 0.0;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
     cur = 0;
      for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data2[cur] =  0.02 * cos((2.0*PI*i)/n);
        vertex_buffer_data2[cur+1] = 0.1 + 0.02 * sin((2.0*PI*i)/n);
        vertex_buffer_data2[cur+2] = 0.0;
        vertex_buffer_data2[cur+3] = 0.02 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+4] = 0.1 + 0.02 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+5] = 0.0;
        vertex_buffer_data2[cur+6] = 0.0;
        vertex_buffer_data2[cur+7] = 0.1;
        vertex_buffer_data2[cur+8] = 0.0;
        cur += 9;
     } 
     cur = 0;
      for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data3[cur] =  0.1 + 0.02 * cos((2.0*PI*i)/n);
        vertex_buffer_data3[cur+1] = 0.02 * sin((2.0*PI*i)/n);
        vertex_buffer_data3[cur+2] = 0.0;
        vertex_buffer_data3[cur+3] = 0.1 + 0.02 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data3[cur+4] = 0.02 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data3[cur+5] = 0.0;
        vertex_buffer_data3[cur+6] = 0.1;
        vertex_buffer_data3[cur+7] = 0.0;
        vertex_buffer_data3[cur+8] = 0.0;
        cur += 9;
     } 
    this->ring1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_MIDNIGHT_BLUE, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->ring3 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->tri = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data3, COLOR_RED, GL_FILL);
    // this->line = create3DObject(GL_LINE_LOOP, 2*n, vertex_buffer_data2, COLOR_DARK_RED, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     this->position = glm::vec3(3.0, 0.0, 0);
    this->rotation = 0.1;

    // this->line = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    glm::mat4 scale1    = glm::scale(glm::vec3(3.0, 3.0, 3.0));
    glm::mat4 rotate    = glm::rotate(this->rotation,glm::vec3(0, 0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate  * scale * scale1 * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
    draw3DObject(this->ring3);
    draw3DObject(this->tri);
    // draw3DObject(this->line);
    // glLineWidth(2.5); 
    // glColor3f(1.0, 0.0, 0.0);
    // glBegin(GL_LINES);
    //     glVertex3f(0.0, 6.0, -1.0);
    //     glVertex3f(6.0, 6.0, -1.0);
    // glEnd();
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick(float x) {
    this->theta += 0.02;
    this->rotation += 0.02;
    this->center -= GameSpeed;
    this->position.x = this->center + 1.814*cos(this->theta);
    this->position.y = 2.0 + 1.214*sin(this->theta);
    if(this->center < -4.0 || this->center >6.0)
    {
        this->center = 4.0;
        this->theta = 0.0;
    }
}

