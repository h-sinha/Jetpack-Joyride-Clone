#include "enemy2_firebeam.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Firebeam::Firebeam(float x, float y, color_t color) {
   
    speed = 0.03;
    up = 1;
    float xx, yy;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 0.2; 
    this->width = 1.5;
     int n=15, cur = 0;
    GLfloat vertex_buffer_data[9*n];
    GLfloat vertex_buffer_data1[9*n];
    GLfloat vertex_buffer_data2[9*n];
    xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    yy = 1.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
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
        vertex_buffer_data1[cur] =  1.5 + 0.1 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] =  0.1 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = 0.0;
        vertex_buffer_data1[cur+3] = 1.5 + 0.1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] =  0.1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = 0.0;
        vertex_buffer_data1[cur+6] = 1.5 + 0.0;
        vertex_buffer_data1[cur+7] =  0.0;
        vertex_buffer_data1[cur+8] = 0.0;
        cur += 9;
     } 
     cur = 0;
     float offset = 0.02;
     for (int i = 1; i <= 9; ++i)
     {
        vertex_buffer_data2[cur] =  0.0;
        vertex_buffer_data2[cur+1] =  - 0.1 + offset;
        vertex_buffer_data2[cur+2] =  -1.0;
        vertex_buffer_data2[cur+3] =  1.5;
        vertex_buffer_data2[cur+4] =  - 0.1 + offset;
        vertex_buffer_data2[cur+5] =  -1.0;
        cur += 6;
        offset += 0.02;
     } 
      static const GLfloat vertex_buffer_data3[] = {
        0.0f, -0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,
        0.2f, -0.1f, 0.0f,
        0.2f, -0.1f, 0.0f,
        0.2f, 0.1f, 0.0f,
        0.0f, 0.1f, 0.0f,

     };
      static const GLfloat vertex_buffer_data4[] = {
         1.3f, -0.1f, 0.0f,
        1.3f, 0.1f, 0.0f,
        1.5f, -0.1f, 0.0f,
        1.5f, -0.1f, 0.0f,
        1.5f, 0.1f, 0.0f,
        1.3f, 0.1f, 0.0f,
     };
     //  static const GLfloat vertex_buffer_data2[] = {
     //   0.0f, 0.0f, -1.0f,
     //   0.6f, 0.0f, -1.0f,
     // };
    this->ring1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_LIGHT_SLATE_GREY, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_LIGHT_SLATE_GREY, GL_FILL);
    this->line = create3DObject(GL_LINES, 2*9, vertex_buffer_data2, COLOR_DARK_RED, GL_FILL);
    this->square1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data3, COLOR_LIGHT_SLATE_GREY, GL_FILL);
    this->square2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data4, COLOR_LIGHT_SLATE_GREY, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     // this->position = glm::vec3(6.0, 0.58, 0);
     this->position = glm::vec3(3.0, 3.0, 0);
    this->rotation = 0;

    // this->line = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
    draw3DObject(this->square2);
    draw3DObject(this->square1);
    draw3DObject(this->line);
    // glLineWidth(2.5); 
    // glColor3f(1.0, 0.0, 0.0);
    // glBegin(GL_LINES);
    //     glVertex3f(0.0, 6.0, -1.0);
    //     glVertex3f(6.0, 6.0, -1.0);
    // glEnd();
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    this->position.x -= GameSpeed;
    if(up)
        this->position.y += speed;
    else 
        this->position.y -= speed;
    if(this->position.y > 4.0)
    {
        up = 0;
        this->position.y -= speed;
    } 
    else if(this->position.y < 0.5)
    {
        up = 1;
        this->position.y += speed;
    }
    
    if(this->position.x < -3.0)
    {
        float xx, yy;
        xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
         yy = 1.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.x = xx + 8.0, this->position.y = yy;
    }
}

