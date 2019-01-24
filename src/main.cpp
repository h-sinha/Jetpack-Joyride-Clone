#include "main.h"
#include "timer.h"
#include "ball.h"
#include "bricks.h"
#include "wall.h"
#include "coin.h"
#include "player.h"
#include "enemy1_firelines.h"
#include "enemy2_firebeam.h"
#include "enemy3_boomerang.h"
#include "magnet.h"
#include "speedup.h"
#include "bonuscoin.h"
#include "dragon.h"
#include "ice.h"
#include "score.h"
#include "functions.h"
#include <vector>
#include <set>

using namespace std;
int co = 0;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

std::vector<Brick> BrickPos;
// std::vector<Wall> WallPos;
std::vector<Ball> BallPos;
std::vector<Ice> IcePos;
std::vector<Coin> CoinPos;
std::vector<Score> ScorePos;
string ScoreBoard = "SCORE-";
Fireline fireline;
Firebeam firebeam;
Magnet magnet;
Speed speedup;
BonusCoin bonuscoin;
Dragon dragon;
Boomerang boomerang;
Player player;
bounding_box_t PlayerBound;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int ScreenWidth = 800, ScreenHeight = 800, score = 0, speeding = 0;
// std::vector<bool> done(30);
time_t tmr, btr,ict, speedtime;
Timer t60(1.0 / 60.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void gameOver()
{
    cout<<"-----------------GAMEOVER-------------------------\n";
    cout<<"YOUR SCORE : "<<score<<endl;
    cout<<"-----------------********-------------------------\n";
    // quit(window);
    score -= 1;
    if(score < 0)score = 0;

}
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
    // for(auto &x:WallPos)
    // {
    //     x.draw(VP);
    // }
    int cur = CoinPos.size();
    Coin x;
    for(int i = cur-1;i>=0;--i)
    {
        x = CoinPos[i];
        bounding_box_t c;
        c.x = x.position[0];
        c.y = x.position[1];
        c.height = x.length;
        c.width = x.width;
        int flag = detect_collision(PlayerBound, c);
        if(!flag)
            x.draw(VP);
        else 
        {
            score += 5;
            CoinPos.erase(CoinPos.begin() + i);
        }
    }   
    bounding_box_t Fbeam, Fline, Boom, Mag, Drag, xx, SpeedUp;
    Fbeam = {firebeam.position[0], firebeam.position[1], firebeam.width, firebeam.length};
    Fline = {fireline.position[0], fireline.position[1], fireline.width, fireline.length};
    Boom = {boomerang.position[0], boomerang.position[1], boomerang.width, boomerang.length};
    Mag = {magnet.position[0] + 0.05f, magnet.position[1], magnet.width, magnet.length};
    Drag = {dragon.position.x , dragon.position.y, dragon.width, dragon.length};
    SpeedUp = {speedup.position.x , speedup.position.y, speedup.width, speedup.length};
    for (int i = int(BallPos.size()) - 1; i >= 0 ; --i)
    {
        if(BallPos[i].position.y <= 0.3)
        {
            BallPos.erase(BallPos.begin() + i);
            continue;
        }
        xx = {BallPos[i].position.x, BallPos[i].position.y, BallPos[i].width, BallPos[i].length};
        if(detect_collision(xx, Fbeam))
            firebeam.set_position(-100.0, -100.0);
        if(detect_collision(xx, Fline))
            fireline.set_position(-100.0, -100.0);
    }
     for (int i = int(IcePos.size()) - 1; i >= 0 ; --i)
    {
        if(IcePos[i].position.y <= 0.3)
        {
            IcePos.erase(IcePos.begin() + i);
            continue;
        }
        xx = {IcePos[i].position.x, IcePos[i].position.y, IcePos[i].width, IcePos[i].length};
        if(detect_collision(xx, PlayerBound))
            gameOver();
    }
    player.draw(VP);
    if(detect_collision(Fbeam, PlayerBound))
        gameOver();
    if(detect_collision(SpeedUp, PlayerBound))
    {
        speedtime = time(NULL);
        GameSpeed += 0.01;
        speeding = 1;
    }
    if(time(NULL) - speedtime > 5.0 && speeding)
    {
        speeding = 0;
        GameSpeed -= 0.01;
    }
    // if(detect_collision(Fbeam, Mag))
        // magnet.position = glm::vec3 (-100.0,-100.0,0.0);

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("fire %lf %lf %lf %lf\n",fireline.line[i][0], fireline.line[i][1], fireline.line[i][2], fireline.line[i][3]);
            printf("player %lf %lf %lf %lf\n",player.line[j][0], player.line[j][1], player.line[j][2], player.line[j][3]);
            if(check_intersection(fireline.line[i], player.line[j]))
                gameOver();
        }

    }
     // if(detect_collision(Fline, Mag))
        // magnet.position = glm::vec3 (-100.0,-100.0,0.0);
    if(detect_collision(Boom, PlayerBound))
        gameOver();
     if(detect_collision(Drag, PlayerBound))
        gameOver();
    firebeam.draw(VP);
    boomerang.draw(VP);
    fireline.draw(VP);
    magnet.draw(VP);
    speedup.draw(VP);
    bonuscoin.draw(VP);
    dragon.draw(VP);
    for (auto &x:BallPos)
    {
        x.draw(VP);
    }
    for (auto &x:CoinPos)
    {
        x.draw(VP);
    }
     for (auto &x:IcePos)
    {
        x.draw(VP);
    }
    string digit;
    int aux_score = score;
    for (int i = 0; i < int(ScorePos.size()); ++i)
    {
        if(i < 42)
        {
            if(i%7 == 0)digit = sevenSegment(ScoreBoard[i/7]);
            if(digit[i%7] == '1')
            {
                ScorePos[i].draw(VP);
            }
        }
        else
        {
            if(i == 42)
            {
                digit = sevenSegment(aux_score/100 + 48);
                aux_score%=100;
            }
            else if(i == 49)
            {
                digit = sevenSegment(aux_score/10 + 48);
                aux_score%=10;
            }
            else if(i == 56)
            {
                digit = sevenSegment(aux_score + 48);
                aux_score = 0;
            }
            if(digit[(i-42)%7] == '1')
            {
                ScorePos[i].draw(VP);
            }
        }
    }

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
    for (auto &x:BallPos)
    {
        x.scalex = ScaleFactor;
        x.scaley = ScaleFactor;
        x.scalez = ScaleFactor;
    }
    for (auto &x:IcePos)
    {
        x.scalex = ScaleFactor;
        x.scaley = ScaleFactor;
        x.scalez = ScaleFactor;
    }
    fireline.scalex = ScaleFactor;
    fireline.scalez = ScaleFactor;
    fireline.scaley = ScaleFactor;
    magnet.scalex = ScaleFactor;
    magnet.scalez = ScaleFactor;
    magnet.scaley = ScaleFactor;
    speedup.scalex = ScaleFactor;
    speedup.scalez = ScaleFactor;
    speedup.scaley = ScaleFactor;
     firebeam.scalex = ScaleFactor;
    firebeam.scalez = ScaleFactor;
    firebeam.scaley = ScaleFactor;
    boomerang.scalex = ScaleFactor;
    boomerang.scalez = ScaleFactor;
    boomerang.scaley = ScaleFactor;
    bonuscoin.scalex = ScaleFactor;
    bonuscoin.scalez = ScaleFactor;
    bonuscoin.scaley = ScaleFactor;
    dragon.scalex = ScaleFactor;
    dragon.scalez = ScaleFactor;
    dragon.scaley = ScaleFactor;
}
void tick_elements() {
    for (auto &x:BrickPos)
    {
        x.tick();
    }
    for (auto &x:BallPos)
    {
        x.tick();
    }
    for (auto &x:IcePos)
    {
        x.tick();
    }
    // for (auto &x:WallPos)
    // {
    //     x.tick();
    // }
    for (auto &x:CoinPos)
        x.tick();
    player.tick();
    PlayerBound.x = player.position[0];
    PlayerBound.y = player.position[1];
    PlayerBound.height = player.length;
    PlayerBound.width = player.width;
    fireline.tick();
    magnet.tick();
    speedup.tick();
    bonuscoin.tick();
    dragon.tick();
    firebeam.tick();
    boomerang.tick(player.position[0]);
    if(dragon.position.x > 0.0 && dragon.position.x < 3.6 && abs(time(NULL) - ict) > 1)
    {
        ict = time(NULL);
        Ice ice = Ice(dragon.position.x , dragon.position.y, COLOR_MIDNIGHT_BLUE);
        IcePos.push_back(ice);
    }
}

void tick_input(GLFWwindow *window) {
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int scroll = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    int shoot = glfwGetKey(window, GLFW_KEY_SPACE);
    zoom();
    if (up) {
        player.move(1);
    }
    if(right){
        if(GameSpeed < 0.2)
        GameSpeed+=0.001;
        dragon.position.x -= GameSpeed;
        dragon.position.x += 0.001;
    }
    if(left){
        if(GameSpeed > -0.2){
            GameSpeed -= 0.001;
        }
    }
    
    if(shoot && abs(time(NULL) - tmr) > 1e-6){
        tmr = time(NULL);
        Ball ball = Ball(PlayerBound.x + PlayerBound.width, PlayerBound.y + PlayerBound.height, COLOR_BLACK);
        BallPos.push_back(ball);
    }
    if(abs(time(NULL) - btr) > 1 && bonuscoin.position.x <= 3.6 && bonuscoin.position.x >=0.0)
    {
        btr = time(NULL);
        Coin coin = Coin(bonuscoin.position.x, bonuscoin.position.y, COLOR_HOT_PINK,1);
        CoinPos.push_back(coin);
    }
    if(GameSpeed > 0.01 && !right && !left)GameSpeed -= 0.001;
    if(GameSpeed < 0.01 && !right && !left)GameSpeed += 0.001;
   

    // if(magnet.position.y > player.position.y + 0.2  && magnet.position.x >= 0.0 && magnet.position.x <= 3.6)
    // {
    //     player.move(1);
    //     player.move(1);
    // }
    // if(magnet.position.y < player.position.y + 0.2 && magnet.position.x >= 0.0 && magnet.position.x <= 3.6)player.move(-1);
    // if(magnet.position.x + 0.1 < player.position.x && magnet.position.x >= 0.0 && magnet.position.x <= 3.6)
    // {
    //     if(!right)
    //     GameSpeed = -0.02;
    //     tick_elements();
    //     GameSpeed = 0.01;
    // }
    // if(magnet.position.x - 0.1 >= player.position.x + 0.4 && magnet.position.x >= 0.0 && magnet.position.x <= 3.6)
    // {
    //     if(!right)
    //     GameSpeed = 0.02;
    //     tick_elements();
    //     GameSpeed = 0.01;
    // }
     if(!up)
    player.move(-1);
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int cur = -10;
    for (float i = 0; i < 60; ++i)
    {
        Brick brick;
        if(int(i)%2 == 0)
            brick = Brick(cur*(0.4), 0.0f, COLOR_BROWN);
        else
            brick = Brick(cur*(0.4), 0.0f, COLOR_LIGHT_BROWN);
        BrickPos.push_back(brick);
        cur++;
    }
    cur = -10;
    for (float i = 0; i < 60; ++i)
    {
        Brick brick;
        if(int(i)%2 == 1)
            brick = Brick(cur*(0.4), 0.18f, COLOR_BROWN);
        else
            brick = Brick(cur*(0.4), 0.18f, COLOR_LIGHT_BROWN);
        BrickPos.push_back(brick);
        cur++;
    }
    // for (float i = 0; i < 15; ++i)
    // {
    //     Wall wall;
    //     wall = Wall(0.0, 0.0, COLOR_LIGHT_BROWN);
    //     WallPos.push_back(wall);
    // }
    for (float i = 0; i < 10; ++i)
    {
        // Coin coin;
        Coin coin = Coin(0.0f, 0.0f, COLOR_YELLOW);
        CoinPos.push_back(coin);
    }
     player = Player(1.8,0.4,COLOR_BROWN);
     fireline = Fireline(0.0, 0.0, COLOR_BACKGROUND);
     magnet = Magnet(0.0, 0.0, COLOR_BACKGROUND);
     speedup = Speed(0.0, 0.0);
     bonuscoin = BonusCoin(0.0, 0.0, COLOR_BACKGROUND);
     dragon = Dragon(0.0, 0.0, COLOR_BACKGROUND);
     firebeam = Firebeam(0.0, 0.0, COLOR_BACKGROUND);
     boomerang = Boomerang(0.0, 0.0, COLOR_BACKGROUND);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    float current = 2.75, diff = 0.02, xx = 0.02, yy = 0.08;
    Score score;
    for(int i =0 ;i<9;++i)
    {   
        score = Score(current, 3.94f - xx - yy - diff, xx, yy);
        ScorePos.push_back(score);
        score = Score(current + diff, 3.94f - xx, yy, xx);
        ScorePos.push_back(score);
        score = Score(current + xx + yy , 3.94f - xx - yy - diff, xx, yy);
        ScorePos.push_back(score);
        score = Score(current + xx + yy, 3.94f - xx - 2*yy - 2*diff, xx, yy);
        ScorePos.push_back(score);
        score = Score(current+ diff, 3.94f - 2*yy - xx -3*diff, yy, xx);
        ScorePos.push_back(score);
        score = Score(current, 3.94f - xx - 2*yy - 2*diff, xx, yy);
        ScorePos.push_back(score);
        score = Score(current + diff, 3.94f - xx - yy - 2*diff, yy, xx);
        ScorePos.push_back(score);
        current += (2*xx + yy + diff);
    }
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

bool detect_collision(bounding_box_t rect1, bounding_box_t rect2) {
    // return (abs(a.x - b.x) * 2.0 < (a.width + b.width)) &&
           // (abs(a.y - b.y) * 2.0 < (a.height + b.height));
if (rect1.x < rect2.x + rect2.width && rect1.x + rect1.width > rect2.x &&
   rect1.y < rect2.y + rect2.height && rect1.height + rect1.y > rect2.y) {
    // collision detected!
            return 1;
}
if (rect2.x < rect1.x + rect1.width && rect2.x + rect2.width > rect1.x &&
   rect2.y < rect1.y + rect1.height && rect2.height + rect2.y > rect1.y) {
    // collision detected!
            return 1;
}
return 0;
}

void reset_screen() {

    float top    =  4/screen_zoom;
    float bottom = 0 ;
    float left   = 0;
    float right  = 4 / screen_zoom;
    // changed origin
     Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    // Matrices.projection = glm::ortho(0.0f, right, 0.0f, top, 0.1f, 500.0f);
    // Matrices.projection = glm::ortho(0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 500.0f);
}
