#include "Cube.h"
#include "Utilities.h"
#include <GL/glfw.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>

#define PI 3.14


static Cube *callbackPtrCube = nullptr;
static const float EPS = 0.01;
static const float STEP = 0.04;
static float R = 0;
static float limitR = 0;
static double alpha = 45;
static double beta = 45;
static int lastScrollPosition = 0;
static const int HALF_CIRCLE = 180;
static const int CIRCLE = 360;
static int upside = 1;
static float rotationSpeedEpsilon = 0.1;

std::mutex cubeAccess;
std::thread backendTurn;
std::mutex boolean;
bool turning = false;
std::condition_variable cv;


static void scrollFunction (int scrollPosition){
        float step = 0.2f;
        if (lastScrollPosition>scrollPosition && R <= limitR){
            R += step;
        }
        if (lastScrollPosition<scrollPosition && R >= limitR/2){
            R -= step;
        }
        lastScrollPosition = scrollPosition;
}

static void modeAndChoiceCb(int buttonID, int state){

    glfwDisable(GLFW_KEY_REPEAT);

    boolean.lock();
    cubeAccess.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_SPACE){
        callbackPtrCube->modeIncrease();
    }
    boolean.unlock();
    cubeAccess.unlock();

    boolean.lock();
    cubeAccess.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_RALT){
        if (upside == 1){
            callbackPtrCube->choiceIncrease();
        }
        else {
            callbackPtrCube->choiceDecrease();
        }
    }
    boolean.unlock();
    cubeAccess.unlock();

    boolean.lock();
    cubeAccess.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_LALT){
        if (upside == 1){
            callbackPtrCube->choiceDecrease();
        }
        else {
            callbackPtrCube->choiceIncrease();
        }
    }
    boolean.unlock();
    cubeAccess.unlock();
}

static void modifyPOV(){
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(static_cast<int> ('W')) == GLFW_PRESS){
        beta -= STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if  ( (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            beta -= STEP;
            upside *= (-1);
        }
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(static_cast<int> ('S')) == GLFW_PRESS){
        beta += STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if ( (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            beta += STEP;
            upside *= (-1);
        }

    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(static_cast<int> ('A')) == GLFW_PRESS){
        alpha -= STEP*upside;
        if ( (fabs(alpha - CIRCLE) < EPS) || (fabs(alpha + CIRCLE) < EPS) ){
            alpha = 0;
        }
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(static_cast<int> ('D')) == GLFW_PRESS){
        alpha += STEP*upside;
        if ( (fabs(alpha - CIRCLE) < EPS) || (fabs(alpha + CIRCLE) < EPS) ){
            alpha = 0;
       }
    }
}



static void turnOOP(Cube * const cube){
    std::unique_lock<std::mutex> lck(boolean);
    while (turning) {
        cv.wait(lck);
        if (!turning){
            cubeAccess.lock();
            cube->turn();
            cube->setDir(Direction::NEUTRAL);
            cube->print(); //debugging
            cubeAccess.unlock();
        }
    }
}

static void checkTurn(Cube * const cube){
    glfwDisable(GLFW_KEY_REPEAT);

    boolean.lock();
    if (glfwGetKey(GLFW_KEY_RCTRL)==GLFW_PRESS && !backendTurn.joinable() && !turning && cube->getChoice()>=0){
        std::cout<<"RCTRL\n";
        turning = true;
        if (cube->getMode() != Mode::FRONT_TO_BACK){
            (upside==1) ? (cube->setDir(Direction::CLOCK_WISE)) : (cube->setDir(Direction::COUNTER_CLOCK_WISE));
        }
        else{
            cube->setDir(Direction::CLOCK_WISE);
        }
        backendTurn = std::thread(turnOOP,cube);
        backendTurn.detach();
    }

    else if (glfwGetKey(GLFW_KEY_LCTRL)==GLFW_PRESS && !backendTurn.joinable() && !turning && cube->getChoice()>=0){
        std::cout<<"LCTRL\n";
        turning = true;
        if (cube->getMode() != Mode::FRONT_TO_BACK){
            (upside==1) ? (cube->setDir(Direction::COUNTER_CLOCK_WISE)) : (cube->setDir(Direction::CLOCK_WISE));
        }
        else{
            cube->setDir(Direction::COUNTER_CLOCK_WISE);
        }
        backendTurn = std::thread(turnOOP,cube);
        backendTurn.detach();
    }

    boolean.unlock();
}

void Cube::draw(int length, float Cx , float Cy , float Cz){

    float eps = 0.001;
    if ( (length-3) < eps || (length-30) > eps ){
        length = 5;
    }
    callbackPtrCube = this;
    R = (length/2)*5;
    limitR = 2*R;


    int     width, height;
    int     frame = 0;
    bool    running = true;

    glfwInit();

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if( !glfwOpenWindow( 300, 300, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);


    glfwSetWindowTitle("In the beginning");
    glfwSetWindowPos(540,100);
    glfwSetWindowSize(640,640);


    glfwSetMouseWheelCallback( scrollFunction );
    glfwSetKeyCallback( modeAndChoiceCb );

    float turningDegrees = 0;

    while(running)
    {
        frame++;

        glfwGetWindowSize( &width, &height );
        height = height > 0 ? height : 1;

        glViewport( 0, 0, width, height ); //?

        glClearColor( 0.70f, 0.90f, 0.90f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT + GL_DEPTH_BUFFER_BIT);

        glMatrixMode( GL_PROJECTION );//
        glLoadIdentity();//
        gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );//

        glMatrixMode( GL_MODELVIEW );//
        glLoadIdentity();//

        double alphaRads = ( static_cast<double> (alpha) /180) * PI;
        double betaRads = ( static_cast<double> (beta) /180) * PI;

        double X = R*cos(alphaRads)*sin(betaRads)+Cx;
        double Y = R*sin(alphaRads)*sin(betaRads)+Cy;
        double Z = R*cos(betaRads)+Cz;

        //std::cout<<alpha<<" "<<beta<<std::endl;

        gluLookAt(X, Y, Z,
                Cx, Cy, Cz,
                0.0f, 0.0f, upside );


        checkTurn(this);

        cubeAccess.lock();

        boolean.lock();
        if(turning){
            glRotatef(turningDegrees,Cx+1,Cy+0,Cz+0);
        }
        boolean.unlock();

        drawCube(turningDegrees,length, Cx, Cy, Cz);

        glPopMatrix();

        cubeAccess.unlock();

        modifyPOV();

        boolean.lock();
        std::cout<<turningDegrees<<std::endl;
        if ( turning && ((fabs(turningDegrees-90) < rotationSpeedEpsilon) || (fabs(turningDegrees+90) < rotationSpeedEpsilon))){
            turning = false;
            turningDegrees = 0.0f;
            cv.notify_one();
        }
        else if (turning){
            turningDegrees += rotationSpeedEpsilon * static_cast<float>(static_cast<int>(getDir()));
        }
        boolean.unlock();


        if (turning && glfwGetKey(GLFW_KEY_F10)==GLFW_PRESS){ //if not turning anymore
            std::cout<<"F10\n";
            boolean.lock();
            turning = false;
            boolean.unlock();
            cv.notify_one();
        }

        glfwSwapBuffers();

        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);
    }

    glfwTerminate();

}


//debugging draw object
void draw_example_cube (float length, float Cx, float Cy, float Cz){
          glDisable(GL_LIGHTING);
          glDisable(GL_NORMALIZE);
          float coef = 0.85;
          float halfLength = length/2 ;
          glBegin( GL_TRIANGLES );
          //yellow right

          glColor3f(1.0f, 1.0f, 0.0f );

          glNormal3f(0,1,0);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glNormal3f(0,1*coef,0);
          glColor3f(1.0f*coef, 1.0f*coef ,0.0f*coef);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glEnd();

          //green left
          glBegin( GL_TRIANGLES );
          glColor3f(0.0f, 1.0f, 0.0f );

          glNormal3f(0,-1,0);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);

          glNormal3f(0,-1*coef,0);
          glColor3f(0.0f * coef, 1.0f * coef, 0.0f *coef );
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();

          //white front

          glBegin( GL_TRIANGLES );
          glColor3f(1.0f, 1.0f, 1.0f );

          glNormal3f(1,0,0);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);

          glNormal3f(1*coef,0,0);
          glColor3f(1.0f * coef, 1.0f * coef, 1.0f *coef);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();

          //back orange
          glBegin( GL_TRIANGLES );
          glColor3f(1.0f, 0.5f, 0.0f );

          glNormal3f(-1,0,0);
          glVertex3f(Cx-halfLength, Cy+-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glNormal3f(-1*coef,0,0);
          glColor3f(1.0f * coef, 0.5f * coef, 0.0f *coef );
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();


          //red bottom
          glBegin( GL_TRIANGLES );
          glColor3f(1.0f, 0.0f, 0.0f );

          glNormal3f(0,0,-1);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glNormal3f(0,0,-1*coef);
          glColor3f(1.0f *coef , 0.0f * coef, 0.0f *coef );
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glEnd();

          //blue top
          glBegin( GL_TRIANGLES );
          glColor3f(0.0f, 0.0f, 1.0f );

          glNormal3f(0,0,1);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);

          glNormal3f(0,0,1*coef);
          glColor3f(0.0f * coef, 0.0f * coef, 1.0f * coef);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();
          glEnable(GL_NORMALIZE);
          //glEnable(GL_LIGHTING);
}

void Cube::drawCube(int turningDegrees, float length, float Cx, float Cy, float Cz)const{

    switch (getMode()){
        case Mode::TOP_TO_BOTTOM: break;
        case Mode::LEFT_TO_RIGHT: break;
        case Mode::FRONT_TO_BACK: break;
        default: break;
    }

    draw_example_cube(length,Cx,Cy,Cz);
}
