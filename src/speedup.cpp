#include "speedup.h"
#include "main.h"
const double PI = 3.141592653589793238460;
Speed::Speed(float x, float y) {
    this->rotation = 0;
    this->length = 0.4;
    this->width = 0.4;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
     x = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    this->position = glm::vec3(x, y, 0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       0.4, 0.0f, 0.0f,
       0.0f, 0.4f, 0.0f,
       0.4f, 0.4f, 0.0f,
       0.0f, 0.4f, 0.0f,
       0.4f, 0.0f, 0.0f,
     };
     static const GLfloat vertex_buffer_data1[] = {
       0.15f, 0.2f, 0.0f,
       0.05, 0.36f, 0.0f,
       0.35f, 0.2f, 0.0f,
     };
     static const GLfloat vertex_buffer_data2[] = {
       0.35f, 0.2f, 0.0f,
       0.15, 0.2f, 0.0f,
       0.05f, 0.04f, 0.0f,
     };
    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_NEON_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_NEON_GREEN, GL_FILL);
}

void Speed::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Speed::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Speed::tick() {
    this->position.x -= GameSpeed;
    float x, y;
    if(this->position.x <-10.0)
    {
       x =  10.0 - 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
        y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
         this->position.x = x;
         this->position.y = y;
    }
    else if(this->position.x > 10.0)
    {
         x = -10.0 + 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
          y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
         this->position.x = x;
         this->position.y = y;
    }
}
