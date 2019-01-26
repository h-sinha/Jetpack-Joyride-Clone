#include "player.h"
#include "main.h"
const double PI = 3.141592653589793238460;

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = 0.4;
    this->width = 0.4;
    this->scalex = 1.0;
    this->scaley = 1.0;
    this->scalez = 0.0;
    this->color = color;
    speed = 0.02;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int cur = 0, n = 20;
    this->position = glm::vec3(x, y , 0);

    static const GLfloat vertex_buffer_blackring[] = {
       0.0f, 0.0f, 0.0f,
       0.0f, 0.4f, 0.0f,
       0.4f, 0.0f, 0.0f,
       0.4f, 0.4f, 0.0f,
       0.4f, 0.0f, 0.0f,
       0.0f, 0.4f, 0.0f,
     };
      static const GLfloat vertex_buffer_whitering[] = {
       0.05f, 0.0f, 0.0f,
       0.05f, 0.1f, 0.0f,
       0.35f, 0.0f, 0.0f,
       0.35f, 0.1f, 0.0f,
       0.35f, 0.0f, 0.0f,
       0.05f, 0.1f, 0.0f,
     };
      static const GLfloat vertex_buffer_whiteeye1[] = {
       0.05f, 0.2f, 0.0f,
       0.05f, 0.3f, 0.0f,
       0.15f, 0.2f, 0.0f,
       0.15f, 0.3f, 0.0f,
       0.15f, 0.2f, 0.0f,
       0.05f, 0.3f, 0.0f,
     };
      static const GLfloat vertex_buffer_whiteeye2[] = {
       0.25f, 0.2f, 0.0f,
       0.25f, 0.3f, 0.0f,
       0.35f, 0.2f, 0.0f,
       0.35f, 0.3f, 0.0f,
       0.35f, 0.2f, 0.0f,
       0.25f, 0.3f, 0.0f,
     };
     static const GLfloat vertex_buffer_nose[] = {
        0.24f, 0.2f, 0.0f,
        0.2f, 0.08f, 0.0f,
        0.16f, 0.2f, 0.0f,
     };
     static const GLfloat vertex_buffer_blackeye1[] = {
       0.063f, 0.23f, 0.0f,
       0.063f, 0.27f, 0.0f,
       0.13f, 0.23f, 0.0f,
       0.13f, 0.27f, 0.0f,
       0.13f, 0.23f, 0.0f,
       0.063f, 0.27f, 0.0f,
     };
      static const GLfloat vertex_buffer_blackeye2[] = {
       0.263f, 0.23f, 0.0f,
       0.263f, 0.27f, 0.0f,
       0.33f, 0.23f, 0.0f,
       0.33f, 0.27f, 0.0f,
       0.33f, 0.23f, 0.0f,
       0.263f, 0.27f, 0.0f,
     };
      static const GLfloat vertex_buffer_jet1[] = {
       0.03f, 0.0f, 0.0f,
       0.15f, 0.0f, 0.0f,
       0.09f, -0.1f, 0.0f,
     };
      static const GLfloat vertex_buffer_jet2[] = {
       0.37f, 0.0f, 0.0f,
       0.25f, 0.0f, 0.0f,
       0.31f, -0.1f, 0.0f,
     };
    this->blackring = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_blackring, COLOR_BLACK, GL_FILL);
    this->whitering = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whitering, COLOR_WHITE, GL_FILL);
    this->whiteeye1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whiteeye1, COLOR_WHITE, GL_FILL);
    this->whiteeye2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whiteeye2, COLOR_WHITE, GL_FILL);
    this->nose = create3DObject(GL_TRIANGLES, 3, vertex_buffer_nose, COLOR_RED, GL_FILL);
    this->blackeye1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_blackeye1, COLOR_BLACK, GL_FILL);
    this->blackeye2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_blackeye2, COLOR_BLACK, GL_FILL);
    this->jet1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_jet1, COLOR_RED, GL_FILL);
    this->jet2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_jet2, COLOR_RED, GL_FILL);
    this->line[0] = glm::vec4(x, y, x + 0.4f, y);
    this->line[1] = glm::vec4(x + 0.4f, y, x + 0.4f, y + 0.4f);
    this->line[2] = glm::vec4(x , y + 0.4f, x + 0.4f, y + 0.4f);
    this->line[3] = glm::vec4(x, y, x , y + 0.4f);
}

void Player::draw(glm::mat4 VP) {
    if(this->position.x < -2.0 || this->position.x > 6)return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->blackring);
    draw3DObject(this->whitering);
    draw3DObject(this->whiteeye1);
    draw3DObject(this->whiteeye2);
    draw3DObject(this->blackeye1);
    draw3DObject(this->blackeye2);
    draw3DObject(this->nose);
    if(this->position.y>0.4)
    {
      draw3DObject(this->jet1);
      draw3DObject(this->jet2);
    }
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    this->rotation += 0.01;
    // this->position.x -= speed;
    // this->position.y -= speed;
    // this->set_position(this->position.x, this->position.y);
    // printf("%f %f\n",speed, this->position.x );
}
void Player::move(int up) {
    // this->rotation += speed;
    // this->position.x -= speed;
    if(up == 1)
    {
      if(this->position.y + speed + 0.4f < Top)
      {
        this->position.y += speed;
        this->line[0][1] += speed;
        this->line[0][3] += speed;
         this->line[1][1] += speed;
        this->line[1][3] += speed;
         this->line[2][1] += speed;
        this->line[2][3] += speed;
         this->line[3][1] += speed;
        this->line[3][3] += speed;
      }
    }
    else
    {
      // std::cout<<this->position.y<<std::endl;
      // std::cout<<0.38-ScreenDiff<<" "<<this->position.y - speed<<std::endl;
      if(this->position.y - speed > Bottom)
      {
        this->position.y -= speed;
        this->line[0][1] -= speed;
        this->line[0][3] -= speed;
         this->line[1][1] -= speed;
        this->line[1][3] -= speed;
         this->line[2][1] -= speed;
        this->line[2][3] -= speed;
         this->line[3][1] -= speed;
        this->line[3][3] -= speed;
      }
      // else
      // {
      //   float diff = this->position.y - 0.38+2*ScreenDiff;
      //   // printf("%lf\n",diff );
      //    this->position.y -= diff;
      //   this->line[0][1] -= diff;
      //   this->line[0][3] -= diff;
      //    this->line[1][1] -= diff;
      //   this->line[1][3] -= diff;
      //    this->line[2][1] -= diff;
      //   this->line[2][3] -= diff;
      //    this->line[3][1] -= diff;
      //   this->line[3][3] -= diff;
      // }
    }
    // this->set_position(this->position.x, this->position.y);
}
