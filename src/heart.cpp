#include "heart.h"
#include "main.h"
#include "functions.h"
const double PI = 3.141592653589793238460;

Heart::Heart(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       -0.13, 0.2f, 0.0f,
       0.13f, 0.2f, 0.0f,
     };
     int n = 15;
    GLfloat vertex_buffer_data1[9*n];
    GLfloat vertex_buffer_data2[9*n];
    makePolygon(-0.06, 0.2, -100, 0.06, 0.06, n, vertex_buffer_data1);
    makePolygon(0.06, 0.2, -100, 0.06, 0.06, n, vertex_buffer_data2);
    this->tri = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->c1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->c2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data2, COLOR_RED, GL_FILL);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
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

