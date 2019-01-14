#include "coin.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Coin::Coin(float x, float y, color_t color) {
    this->rotation = 0;
    this->length = 0.1;
    this->width = 0.1;
    speed = GameSpeed;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n = 15;
    GLfloat vertex_buffer_data[9*n];
    x = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
    y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    this->position = glm::vec3(x, y, 0);
    
    int cur = 0;
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data[cur] =  x + 0.1 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] = y + 0.1 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = x + 0.1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = y + 0.1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = x;
        vertex_buffer_data[cur+7] = y;
        vertex_buffer_data[cur+8] = 0.0;
        cur += 9;
     } 
   
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
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

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    // this->rotation += speed;
    this->position.x -= GameSpeed;
    if(this->position.x <-6.0)
      position.x += 12.0;
    else if(this->position.x > 6.0)
      position.x -= 12.0;
    this->set_position(this->position.x, this->position.y);
}
