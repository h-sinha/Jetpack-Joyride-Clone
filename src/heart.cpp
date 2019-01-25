#include "heart.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Heart::Heart(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    // this->color = color;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // printf("%lf %lf\n",xx, yy );
    GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       -0.13, 0.2f, 0.0f,
       0.13f, 0.2f, 0.0f,
     };
     int n = 15;
      GLfloat vertex_buffer_data1[9*n];
    int cur = 0;
    for (int i = 0; i < n; ++i)
     {
        vertex_buffer_data1[cur] = -0.06 +  0.06 * cos((2.0*PI*i)/n);
        vertex_buffer_data1[cur+1] = 0.2 + 0.06 * sin((2.0*PI*i)/n);
        vertex_buffer_data1[cur+2] = -100.0;
        vertex_buffer_data1[cur+3] = -0.06 +  0.06 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+4] = 0.2 + 0.06 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data1[cur+5] = -100.0;
        vertex_buffer_data1[cur+6] = -0.06   ;
        vertex_buffer_data1[cur+7] = 0.2;
        vertex_buffer_data1[cur+8] = -100.0;
        cur += 9;
     } 
      GLfloat vertex_buffer_data2[9*n];
    cur = 0;
    for (int i = 0; i < n; ++i)
     {
        vertex_buffer_data2[cur] = 0.06 +  0.06 * cos((2.0*PI*i)/n);
        vertex_buffer_data2[cur+1] = 0.2 + 0.06 * sin((2.0*PI*i)/n);
        vertex_buffer_data2[cur+2] = -100.0;
        vertex_buffer_data2[cur+3] = 0.06 +  0.06 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+4] = 0.2 + 0.06 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data2[cur+5] = -100.0;
        vertex_buffer_data2[cur+6] = 0.06   ;
        vertex_buffer_data2[cur+7] = 0.2;
        vertex_buffer_data2[cur+8] = -100.0;
        cur += 9;

     } 
    this->tri = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->c1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->c2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data2, COLOR_RED, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->tri);
    draw3DObject(this->c1);
    draw3DObject(this->c2);
}

void Heart::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

