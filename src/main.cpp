#include "main.h"
#include "timer.h"
#include "ball.h"
#include "bricks.h"
#include "wall.h"
#include "coin.h"
#include "player.h"
#include <vector>
#include <set>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

std::vector<Brick> BrickPos;
std::vector<Wall> WallPos;
std::vector<Coin> CoinPos;

Player player;
bounding_box_t PlayerBound;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int score = 0;
int ScreenWidth = 600, ScreenHeight = 600;
std::vector<bool> done(30);

Timer t60(1.0 / 60.0);

void scoreDisplay(){
  //    glFontBegin(&font);
  // glScalef(8.0, 8.0, 8.0);
  // glTranslatef(30, 30, 0);
  // glFontTextOut("Test", 5, 5, 0);
  // glFontEnd();
  // glFlush();
    // GLvoid* font_style = GLUT_BITMAP_TIMES_ROMAN_24;
    // int temp = score, idx = 0;
    // while(temp > 0)
    // {
    //     glRasterPos3f ((0.0-(idx*space_char)), 6.0, 100.0);    
    //     // takes font style and ascii value as parameter
    //     glutBitmapCharacter(font_style, 48+(temp%10));
    //     idx++;
    //     temp /= 10;
    // }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0,0,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(auto &x:BrickPos)
    {
        x.draw(VP);
    }
    for(auto &x:WallPos)
    {
        x.draw(VP);
    }
    int cur = 0;
    for(auto x:CoinPos)
    {
        if(done[cur])
        {
            cur++;
            continue;
        }
        bounding_box_t c;
        PlayerBound.x = player.position[0];
        PlayerBound.y = player.position[1];
        PlayerBound.height = player.length;
        PlayerBound.width = player.width;
        c.x = x.position[0];
        c.y = x.position[1];
        c.height = x.length;
        c.width = x.width;
        int flag = detect_collision(PlayerBound, c);
        if(flag)
        {
            cout<<done[cur]<<" "<<cur<<endl;
            printf("%d %lf %lf %lf %lf\n", flag, x.position[0], x.position[1],PlayerBound.x, PlayerBound.y);
        }
        if(!flag)
            x.draw(VP);
        else 
            done[cur] = 1;
        cur++;
    }
    player.draw(VP);
    scoreDisplay();
}
// zoom function 
void zoom(){
    player.scalex = ScaleFactor;
    player.scaley = ScaleFactor;
    player.scalez = ScaleFactor;
    for (auto &x:BrickPos)
    {
        x.scalex = ScaleFactor;
        x.scaley = ScaleFactor;
        x.scalez = ScaleFactor;
    }
    for (auto &x:CoinPos)
    {
        x.scalex = ScaleFactor;
        x.scaley = ScaleFactor;
        x.scalez = ScaleFactor;
    }
    for (auto &x:WallPos)
    {
        x.scalex = ScaleFactor;
        x.scaley = ScaleFactor;
        x.scalez = ScaleFactor;
    }
}
void tick_input(GLFWwindow *window) {
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int scroll = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    zoom();
    if (up) {
        player.move(1);
    }
    else if(right){
        if(GameSpeed < 0.2)
        GameSpeed+=0.001;
    }
    else if(left){
        if(GameSpeed > -0.2){
            GameSpeed -= 0.001;
        }
    }
    else {
        if(GameSpeed > 0.01)GameSpeed -= 0.001;
        if(GameSpeed < 0.01)GameSpeed += 0.001;
    }
    if(!up)
    player.move(-1);
}

void tick_elements() {
    for (auto &x:BrickPos)
    {
        x.tick();
    }
    for (auto &x:WallPos)
    {
        x.tick();
    }
    int cur = 0;
    for (auto &x:CoinPos)
    {
        float prev = x.position[0];
        x.tick();
        if(x.position[0] > prev)done[cur] = 0;
        cur++;
    }
    player.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int cur = -10;
    scoreDisplay();
    for (float i = 0; i < 60; ++i)
    {
        Brick brick;
        if(int(i)%2 == 0)
            brick = Brick(cur*(0.2), 0.0f, COLOR_BROWN);
        else
            brick = Brick(cur*(0.2), 0.0f, COLOR_LIGHT_BROWN);
        BrickPos.push_back(brick);
        cur++;
    }
    cur = -10;
    for (float i = 0; i < 60; ++i)
    {
        Brick brick;
        if(int(i)%2 == 1)
            brick = Brick(cur*(0.2), 0.18f, COLOR_BROWN);
        else
            brick = Brick(cur*(0.2), 0.18f, COLOR_LIGHT_BROWN);
        BrickPos.push_back(brick);
        cur++;
    }
    for (float i = 0; i < 15; ++i)
    {
        Wall wall;
        wall = Wall(0.0, 0.0, COLOR_LIGHT_BROWN);
        WallPos.push_back(wall);
    }
    for (float i = 0; i < 10; ++i)
    {
        Coin coin;
        coin = Coin(0.0f, 0.0f, COLOR_YELLOW);
        CoinPos.push_back(coin);
    }
    player = Player(0.9,0.18,COLOR_BROWN);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));

    window = initGLFW(ScreenWidth, ScreenHeight);

    initGL (window, ScreenWidth, ScreenHeight);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    // Collision x-axis?
    bool collisionX = a.x + a.width >= b.x && b.x + b.width >= a.x;
    bool collisionY = a.y + a.height >= b.y && b.y + b.height >= a.y;
    // Collision only if on both axes
    if(collisionX && collisionY)
    {
        printf("%lf %lf %lf %lf\n",a.x+ a.width, b.x, b.x + b.width, a.x );
        printf("%lf %lf %lf %lf\n",a.y+ a.height, b.y, b.y + b.height, a.y );
    }
    return collisionX && collisionY;


    // printf("%f %f %f %f %f %f %f %f\n",a.x, b.x, a.width, b.width, a.y, b.y, a.height, b.height );
    // return (abs(a.x - b.x) * 2.0 < (a.width + b.width)) &&
    //        (abs(a.y - b.y) * 2.0 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // changed origin
     // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::ortho(0.0f, right, 0.0f, top, 0.1f, 500.0f);
    // Matrices.projection = glm::ortho(0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 500.0f);
}
