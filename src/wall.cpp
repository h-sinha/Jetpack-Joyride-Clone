#include "wall.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Wall::Wall(float x, float y, color_t color) {
   
    speed = GameSpeed;
    int n = rand()%15;
    GLfloat vertex_buffer_data[9*n];
    x = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    
    int cur = 0;
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data[cur] =  0.2 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] =  0.2 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = -100.0;
        vertex_buffer_data[cur+3] = 0.2 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = 0.2 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = -100.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = -100.0;
        cur += 9;
     } 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_RED, GL_FILL);
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
    if(this->position.x <= -0.2)
      this->position.x += 5.8;
}

