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
    this->blackring = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_blackring, COLOR_BLACK, GL_FILL);
    this->whitering = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whitering, COLOR_WHITE, GL_FILL);
    this->whiteeye1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whiteeye1, COLOR_WHITE, GL_FILL);
    this->whiteeye2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_whiteeye2, COLOR_WHITE, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::scale(glm::vec3(this->scalex, this->scaley, this->scalez));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
     // printf("hola\n");
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->blackring);
    draw3DObject(this->whitering);
    draw3DObject(this->whiteeye1);
    draw3DObject(this->whiteeye2);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    // this->rotation += speed;
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
      if(this->position.y + speed + 0.4f < 4.0f)
        this->position.y += speed;
    }
    else
    {
      if(this->position.y - speed > 0.38f)
        this->position.y -= speed;
    }
    this->set_position(this->position.x, this->position.y);
}
