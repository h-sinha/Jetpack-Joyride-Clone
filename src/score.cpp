#include "score.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Score::Score(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    // this->color = color;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->position = glm::vec3(x, y , 0);

    static const GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       0.01f, 0.0f, 0.0f,
       0.0f, 0.01f, 0.0f,
       0.01f, 0.01f, 0.0f,
       0.0f, 0.01f, 0.0f,
       0.01f, 0.0f, 0.0f,
     };
    this->line = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Score::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->line);
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

