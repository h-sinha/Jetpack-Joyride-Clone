#include "enemy1_firelines.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Fireline::Fireline(float x, float y, color_t color) {
   
    speed = GameSpeed;
    float x1,y1,x2,y2,xx,yy;
    xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    yy = 1.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 1.775;
    this->width = 0.92;
     int n=15, cur = 0;
     this->rotation = 0.1;
     static const GLfloat vertex_buffer_data[] = {
       0.644f, 0.282f, 0.0f,
       0.76f, 0.28 , 0.0f,
       0.458f, 0.712f , 0.0f,
     };
       static const GLfloat vertex_buffer_data1[] = {
       0.826f, 0.0f, 0.0f,
       0.512f, 0.388f , 0.0f,
       0.63f , 0.388f, 0.0f,
     };
    this->ring1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_DARK_RED, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_DARK_RED, GL_FILL);
    this->position = glm::vec3(xx + 3.0, yy, 0);
    this->line[0] = glm::vec4(xx + 3.0f + 0.644f, yy + 0.282f, xx + 3.0f + 0.76f, yy + 0.28f);
    this->line[1] = glm::vec4(xx + 3.0f + 0.458f, yy + 0.712f, xx + 3.0f + 0.76f, yy + 0.28f);
    this->line[2] = glm::vec4(xx + 3.0f + 0.644f, yy + 0.282f, xx + 3.0f + 0.458f, yy + 0.712f);
    this->line[3] = glm::vec4(xx + 3.0f + 0.826f, yy , xx + 3.0f + 0.512f, yy + 0.388f);
    this->line[4] = glm::vec4(xx + 3.0f + 0.63f, yy + 0.388f, xx + 3.0f + 0.512f, yy + 0.388f);
    this->line[5] = glm::vec4(xx + 3.0f + 0.826f, yy , xx + 3.0f + 0.63f, yy + 0.388f);
}

void Fireline::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    Matrices.model *= (translate *  scale );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    this->position.x -= GameSpeed;
    this->line[0][0] -= GameSpeed; this->line[0][2] -= GameSpeed;
    this->line[1][0] -= GameSpeed; this->line[1][2] -= GameSpeed;
    this->line[2][0] -= GameSpeed; this->line[2][2] -= GameSpeed;
    this->line[3][0] -= GameSpeed; this->line[3][2] -= GameSpeed;
    this->line[4][0] -= GameSpeed; this->line[4][2] -= GameSpeed;
    this->line[5][0] -= GameSpeed; this->line[5][2] -= GameSpeed;
    if(this->position.x < -8.0)
    {
        this->position.x = 8.0 - 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.y = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->line[0] = glm::vec4(this->position.x  + 0.644f, this->position.y + 0.282f, this->position.x  + 0.76f, this->position.y + 0.28f);
        this->line[1] = glm::vec4(this->position.x  + 0.458f, this->position.y + 0.712f, this->position.x  + 0.76f, this->position.y + 0.28f);
        this->line[2] = glm::vec4(this->position.x   + 0.644f, this->position.y + 0.282f, this->position.x  + 0.458f, this->position.y + 0.712f);
        this->line[3] = glm::vec4(this->position.x  + 0.826f, this->position.y , this->position.x  + 0.512f, this->position.y + 0.388f);
        this->line[4] = glm::vec4(this->position.x + 0.63f, this->position.y + 0.388f, this->position.x  + 0.512f, this->position.y + 0.388f);
        this->line[5] = glm::vec4(this->position.x  + 0.826f, this->position.y , this->position.x  + 0.63f, this->position.y + 0.388f);
    }
    if(this->position.x > 8.0)
    {
        this->position.x = -8.0 + 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.y = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->line[0] = glm::vec4(this->position.x  + 0.644f, this->position.y + 0.282f, this->position.x + 0.76f, this->position.y + 0.28f);
        this->line[1] = glm::vec4(this->position.x  + 0.458f, this->position.y + 0.712f, this->position.x  + 0.76f, this->position.y + 0.28f);
        this->line[2] = glm::vec4(this->position.x   + 0.644f, this->position.y + 0.282f, this->position.x  + 0.458f, this->position.y + 0.712f);
        this->line[3] = glm::vec4(this->position.x   + 0.826f, this->position.y , this->position.x  + 0.512f, this->position.y + 0.388f);
        this->line[4] = glm::vec4(this->position.x + 0.63f, this->position.y + 0.388f, this->position.x  + 0.512f, this->position.y + 0.388f);
        this->line[5] = glm::vec4(this->position.x   + 0.826f, this->position.y , this->position.x  + 0.63f, this->position.y + 0.388f);
    }
}

