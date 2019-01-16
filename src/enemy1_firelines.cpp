#include "enemy1_firelines.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Fireline::Fireline(float x, float y, color_t color) {
   
    speed = GameSpeed;
    float x1,y1,x2,y2,xx,yy;
    xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    yy = 1.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    // xx = 1.0, yy = 1.0;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 1.775;
    this->width = 0.92;
     int n=15, cur = 0;
     this->rotation = 0.1;
    // GLfloat vertex_buffer_data[9*n];
    // GLfloat vertex_buffer_data1[9*n];
    // GLfloat vertex_buffer_data2[9*n];
     static const GLfloat vertex_buffer_data[] = {
       0.322f  - 0.256f, 0.166f  - 0.22f, 0.0f,
       0.380f  - 0.256f, 0.166  - 0.22f, 0.0f,
       0.229f - 0.256f, 0.381f  - 0.22f, 0.0f,
     };
       static const GLfloat vertex_buffer_data1[] = {
       0.413f  - 0.256f, 0.0260f - 0.22f, 0.0f,
       0.256f - 0.256f, 0.22f - 0.22f, 0.0f,
       0.315f  - 0.256f, 0.220f - 0.22f, 0.0f,
     };
    this->ring1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_DARK_RED, GL_FILL);
    this->ring2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_DARK_RED, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->position = glm::vec3(xx, yy, 0);

    // this->line = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // glm::mat4 rotate    = glm::rotate(this->rotation,glm::vec3(0, 0, 1));
    glm::mat4 scale1    = glm::scale(glm::vec3(5.0, 5.0, 5.0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *  scale * scale1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring1);
    draw3DObject(this->ring2);
    // draw3DObject(this->line);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    this->position.x -= GameSpeed;
    if(this->position.x < -2.0)
    {
        this->position.y = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
        this->position.y = 1.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    }
}

