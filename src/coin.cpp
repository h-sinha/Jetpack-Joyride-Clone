#include "coin.h"
#include "main.h"
#include "functions.h"
const double PI = 3.141592653589793238460;
float cur=0;
Coin::Coin(float x, float y, color_t color, int flag) {
    this->rotation = 0;
    this->length = 0.2;
    this->width = 0.2;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    speed = GameSpeed;
    int n = 15;
    GLfloat vertex_buffer_data[9*n];
    GLfloat vertex_buffer_data1[9*n];
    GLfloat vertex_buffer_data2[9*n];
    if(flag == 0)
    {
        x = 0.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(6.0)));
        y = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(5)));
    }
    this->position = glm::vec3(x, y  , -10.0);
    
    makePolygon(0, 0, 0, 0.1, 0.1, n, vertex_buffer_data);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    glm::mat4 rotate    = glm::rotate(this->rotation, glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    this->rotation += 0.01;
    this->position.x -= GameSpeed;
    if(this->position.x <-6.0)
      this->position.x += 12.0;
    else if(this->position.x > 6.0)
      this->position.x -= 12.0;
}
