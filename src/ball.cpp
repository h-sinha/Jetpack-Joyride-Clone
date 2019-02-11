#include "ball.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.3;
    this->length = 0.3;
    this->width = 0.3;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->speed = GameSpeed;
    int cur = 0, n = 3;
    GLfloat vertex_buffer_data[9*n];
    float xmin, xmax, ymin, ymax;
    for (int i = 1; i <= n; ++i)
     {
        vertex_buffer_data[cur] =  0.1 * cos((2.0*PI*i)/n);
        vertex_buffer_data[cur+1] = 0.1 * sin((2.0*PI*i)/n);
        vertex_buffer_data[cur+2] = 0.0;
        vertex_buffer_data[cur+3] = 0.1 * cos((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+4] = 0.1 * sin((2.0*PI*(i+1))/n);
        vertex_buffer_data[cur+5] = 0.0;
        vertex_buffer_data[cur+6] = 0.0;
        vertex_buffer_data[cur+7] = 0.0;
        vertex_buffer_data[cur+8] = 0.0;
        xmin = std::min(xmin, vertex_buffer_data[cur]);
        xmin = std::min(xmin, vertex_buffer_data[cur+3]);
        xmin = std::min(xmin, vertex_buffer_data[cur+6]);
         xmax = std::max(xmin, vertex_buffer_data[cur]);
        xmax = std::max(xmin, vertex_buffer_data[cur+3]);
        xmax = std::max(xmin, vertex_buffer_data[cur+6]);
        ymin = std::min(ymin, vertex_buffer_data[cur+1]);
        ymin = std::min(ymin, vertex_buffer_data[cur+4]);
        ymin = std::min(ymin, vertex_buffer_data[cur+7]);
        ymax = std::max(ymin, vertex_buffer_data[cur+1]);
        ymax = std::max(ymin, vertex_buffer_data[cur+4]);
        ymax = std::max(ymin, vertex_buffer_data[cur+7]);
        cur += 9;
     } 
     this->line[0] = glm::vec4(x + xmin, y + ymin, x + xmin, y + ymax);
     this->line[1] = glm::vec4(x + xmin, y + ymin, x + xmax, y + (ymax-ymin)/2.0f);
     this->line[2] = glm::vec4(x + xmin, y + ymax, x + xmin, y + (ymax-ymin)/2.0f);
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BALL, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x -= GameSpeed;
    for (int i = 0; i < 3; ++i)
    {
        this->line[i][0] -= GameSpeed;
        this->line[i][2] -= GameSpeed;
    }

    this->position.x += 0.03;
    this->position.y += this->speed;
     for (int i = 0; i < 3; ++i)
    {
        this->line[i][0] += 0.03;
        this->line[i][2] += 0.03;
         this->line[i][1] += this->speed;
        this->line[i][3] += this->speed;
    }
   this->speed -= 0.0005;
}
