#include "shield.h"
#include "main.h"
const double PI = 3.141592653589793238460;
Shield::Shield(float x, float y) {
    this->rotation = 0;
    this->length = 0.4;
    this->width = 0.4;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
   x = y = 2.0;
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       0.4, 0.0f, 0.0f,
       0.0f, 0.4f, 0.0f,
       0.4f, 0.4f, 0.0f,
       0.0f, 0.4f, 0.0f,
       0.4f, 0.0f, 0.0f,
     };
     static const GLfloat vertex_buffer_data1[] = {
       0.1f, 0.15f, 0.0f,
       0.2f, 0.07f, 0.0f,
       0.2f, 0.25f, 0.0f,
       0.1f, 0.15f, 0.0f,
       0.1f, 0.3f, 0.0f,
       0.2f, 0.25f, 0.0f,
       
       0.2f, 0.07f, 0.0f,
       0.3f, 0.15f, 0.0f,
       0.3f, 0.3f, 0.0f,
       0.2f, 0.07f, 0.0f,
       0.2f, 0.25f, 0.0f,
       0.3f, 0.3f, 0.0f,
     };
     static const GLfloat vertex_buffer_data2[] = {
       0.35f, 0.2f, 0.0f,
       0.15, 0.2f, 0.0f,
       0.05f, 0.04f, 0.0f,
     };
    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data1, COLOR_NEON_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_NEON_GREEN, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Shield::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Shield::tick() {
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
