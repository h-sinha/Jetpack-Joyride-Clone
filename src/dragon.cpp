#include "dragon.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Dragon::Dragon(float x, float y, color_t color) {
   
    speed = GameSpeed;
    float x1,y1,x2,y2,xx,yy;
    xx = 3.0, yy = 3.0;
    // xx = 0.2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    // yy = 2.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0)));
    // xx = 1.0, yy = 1.0;
     this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 1.0;
    this->length = 0.2;
    this->width = 0.2;
    this->flag = 0;
     int n=15, cur = 0;
     this->rotation = 0.1;
     this->speed = 0.05;
     // this->speed = 1.0f;
     this->gravity = -0.05/60.0;
    // GLfloat vertex_buffer_data[9*n];
    // GLfloat vertex_buffer_data1[9*n];
    // GLfloat vertex_buffer_data2[9*n];
      // GLfloat vertex_buffer_data[9*15];
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // for (int i = 1; i <= 15; ++i)
    //  {
    //     vertex_buffer_data[cur] =  0.2 * cos((2.0*PI*i)/n);
    //     vertex_buffer_data[cur+1] = 0.2 * sin((2.0*PI*i)/n);
    //     vertex_buffer_data[cur+2] = 0.0;
    //     vertex_buffer_data[cur+3] = 0.2 * cos((2.0*PI*(i+1))/n);
    //     vertex_buffer_data[cur+4] = 0.2 * sin((2.0*PI*(i+1))/n);
    //     vertex_buffer_data[cur+5] = 0.0;
    //     vertex_buffer_data[cur+6] = 0.0;
    //     vertex_buffer_data[cur+7] = 0.0;
    //     vertex_buffer_data[cur+8] = 0.0;
    //     cur += 9;
    //  } 
    //    GLfloat vertex_buffer_data1[9*15];
    // cur = 0;
    // for (int i = 1; i <= 15; ++i)
    //  {
    //     vertex_buffer_data1[cur] =  0.3 * cos((2.0*PI*i)/n);
    //     vertex_buffer_data1[cur+1] = -0.08 +  0.12 * sin((2.0*PI*i)/n);
    //     vertex_buffer_data1[cur+2] = 0.0;
    //     vertex_buffer_data1[cur+3] = 0.3 * cos((2.0*PI*(i+1))/n);
    //     vertex_buffer_data1[cur+4] = -0.08 + 0.12 * sin((2.0*PI*(i+1))/n);
    //     vertex_buffer_data1[cur+5] = 0.0;
    //     vertex_buffer_data1[cur+6] = 0.0;
    //     vertex_buffer_data1[cur+7] = 0.0;
    //     vertex_buffer_data1[cur+8] = 0.0;
    //     cur += 9;
    //  } 
     this->length = 0.4;
     this->width = 0.4;
       static const GLfloat vertex_buffer_data[] = {
            0.2f, 0.4f, 0.0f,
            0.25f, 0.3f, 0.0f,
            0.0f, 0.2f, 0.0f,
     };
      static const GLfloat vertex_buffer_data1[] = {
        0.0f, 0.0f, 0.0f, 
        0.2f, 0.4f, 0.0f, 
        0.4f, 0.0f, 0.0f, 
     };
      static const GLfloat vertex_buffer_data2[] = {
        0.15f, 0.32f, 0.0f, 
        0.2f, 0.32f, 0.0f, 
        0.175f, 0.36f, 0.0f, 
     };
    this->tri1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->mouth1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
    this->mouth2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->position = glm::vec3(4.0, 0.4, 0);

    // this->line = create3DObject(GL_LINES, 2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // glm::mat4 rotate    = glm::rotate(this->rotation,glm::vec3(0, 0, 1));
    // glm::mat4 scale1    = glm::scale(glm::vec3(2.0, 2.0, 2.0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = (translate *  scale );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->tri1);
    draw3DObject(this->mouth1);
    draw3DObject(this->mouth2);
    // draw3DObject(this->rect2);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
  this->position.y += this->speed;

  this->speed += this->gravity;
  this->position.x -= 0.01;
    if(this->position.y >= 3.6)
    {
      this->speed = 0;
    }
    if(this->position.y <= 0.4)
      this->speed = 0.05;
    if(this->position.x < -4.0 || this->position.x > 11.0)
    {
        this->position.x = 4.0;
        this->position.y = 0.4;
        this->flag = 0;
        this->speed = 0.05;
    }
}
