#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = GameSpeed;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float x1 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    float x2 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    float x3 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    float y1 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    float y2 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    float y3 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    static const GLfloat vertex_buffer_data[] = {
        x1, y1, 0.0f,
        x2, y2, 0.0f,
        x3, y3, 0.0f,
     };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Wall::tick() {
    this->position.x -= speed;
    if(this->position.x <= -0.3)
      this->position.x += 5.0;
}

