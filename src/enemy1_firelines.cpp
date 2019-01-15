#include "enemy1_firelines.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Fireline::Fireline(float x, float y, color_t color) {
   
    speed = GameSpeed;
    int n = rand()%15;
    GLfloat vertex_buffer_data[9*n];
    x1 = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    y1 = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    x2 = x1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0 - x1)));
    y2 = y1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0 - y1)));
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    int cur = 0;
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data[cur] =  0.2 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] = 0.2 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = 0.2 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = 0.2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = 0.0;
        cur += 9;
     } 
    this->ring1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_RED, GL_FILL);
    cur = 0;
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data[cur] =  x2 + 0.2 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] =  y2 + 0.2 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = x2 + 0.2 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = y2 + 0.2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = 0.0;
        cur += 9;
     } 
    this->ring2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_RED, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->line = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
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
    draw3DObject(this->line);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    this->position.x -= GameSpeed;
    if(this->position.x <= -0.2)
      this->position.x += 5.8;
  else if(this->position.x > 6.0)
      this->position.x -= 6.0;
    this->set_position(this->position.x, this->position.y);
}

