#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <condition_variable>

#define PI 3.14

static Cube *callbackPtrCube = nullptr;


// file local variables and constants
static const float EPS = 0.01;
static const float STEP = 0.04;
static float R = 5;
static double alpha = 45;
static double beta = 45;
static int lastScrollPosition = 0;
static const int HALF_CIRCLE = 180;
static const int CIRCLE = 360;
static int upside = 1;
std::mutex cubeAccess;
std::thread backendTurn;

std::mutex boolean;
bool turning = false;
std::condition_variable cv;

static void scrollFunction (int scrollPosition){
        const int LIMIT = 10;
        float step = 0.2f;
        if (lastScrollPosition>scrollPosition && R <=LIMIT){
            R += step;
        }
        if (lastScrollPosition<scrollPosition && R>=LIMIT/2){
            R -= step;
        }
        lastScrollPosition = scrollPosition;
}


static void choiceReduce(){
    int rowsCount = callbackPtrCube->getRows();
    int current = callbackPtrCube->getChoice();
    if (current == 0){
        callbackPtrCube->setChoice(-1);
    }
    else if (current == -1){
        callbackPtrCube->setChoice(rowsCount-1);
    }
    else{
        callbackPtrCube->setChoice( (current-1) % rowsCount) ;
    }
    std::cout<<callbackPtrCube->getChoice()<<std::endl;
}

static void choiceIncrease(){
    int rowsCount = callbackPtrCube->getRows();
    int current = callbackPtrCube->getChoice();
    if (current == rowsCount-1){
        callbackPtrCube->setChoice(-1);
    }
    else if (current == -1){
        callbackPtrCube->setChoice(0);
    }
    else{
        callbackPtrCube->setChoice( (current+1) % rowsCount) ;
    }
    std::cout<<callbackPtrCube->getChoice()<<std::endl;
}

static void modeAndChoiceCb(int buttonID, int state){

    glfwDisable(GLFW_KEY_REPEAT);

    boolean.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_SPACE){
        Mode current = callbackPtrCube->getMode();
        const int modesCount = 3;
        callbackPtrCube->setMode( static_cast<Mode>((static_cast<int>(current)+1)%modesCount) );
        std::cout<<static_cast<int> (callbackPtrCube->getMode())<<std::endl;
    }
    boolean.unlock();


    boolean.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_RALT){
        if (upside == 1){
            choiceIncrease();
        }
        else {
            choiceReduce();
        }
    }
    boolean.unlock();

    boolean.lock();
    if (!turning && state == GLFW_PRESS && buttonID == GLFW_KEY_LALT){
        if (upside == 1){
            choiceReduce();
        }
        else {
            choiceIncrease();
        }
    }
    boolean.unlock();
}

static void modifyPOV(){
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
        beta -= STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if  ( (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            beta -= STEP;
            upside *= (-1);
        }
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
        beta += STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if ( (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            beta += STEP;
            upside *= (-1);
        }

    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
        alpha -= STEP*upside;
        if ( (fabs(alpha - CIRCLE) < EPS) || (fabs(alpha + CIRCLE) < EPS) ){
            alpha = 0;
        }
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
        alpha += STEP*upside;
        if ( (fabs(alpha - CIRCLE) < EPS) || (fabs(alpha + CIRCLE) < EPS) ){
            alpha = 0;
       }
    }
}



void draw_example_cube (float length = 1,float Cx = 0 , float Cy = 0, float Cz = 0){


          float halfLength = length/2 ;
          glBegin( GL_TRIANGLES );
          //yellow right
          glColor3f(1.0f, 1.0f, 0.0f );

          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glEnd();

          //green left
          glBegin( GL_TRIANGLES );
          glColor3f(0.0f, 1.0f, 0.0f );

          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);

          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();

          //white front

          glBegin( GL_TRIANGLES );
          glColor3f(1.0f, 1.0f, 1.0f );

          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);

          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();

          //back orange
          glBegin( GL_TRIANGLES );
          glColor3f(0.9f, 0.4f, 0.0f );

          glVertex3f(Cx-halfLength, Cy+-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();

          //red bottom
          glBegin( GL_TRIANGLES );
          glColor3f(1.0f, 0.0f, 0.0f );

          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz-halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);

          glVertex3f(Cx-halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz-halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz-halfLength);
          glEnd();

          //blue top
          glBegin( GL_TRIANGLES );
          glColor3f(0.0f, 0.0f, 1.0f );

          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy-halfLength, Cz+halfLength);
          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);

          glVertex3f(Cx-halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy+halfLength, Cz+halfLength);
          glVertex3f(Cx+halfLength, Cy-halfLength, Cz+halfLength);
          glEnd();
}




static void turnOOP(Cube * const cube,Direction dir){
    std::unique_lock<std::mutex> lck(boolean);
    while (turning) {
        cv.wait(lck);
        if (!turning){
            cubeAccess.lock();
            cube->turn(dir);
            cube->print(); //debugging
            cubeAccess.unlock();
        }
    }
}

static void checkTurn(Cube * const cube){
    Direction dir;
    boolean.lock();
    if (glfwGetKey(GLFW_KEY_RCTRL)==GLFW_PRESS && !backendTurn.joinable() && !turning && cube->getChoice()>=0){
        turning = true;
        (upside==1) ? (dir = Direction::CLOCK_WISE) : (dir = Direction::COUNTER_CLOCK_WISE);
        backendTurn = std::thread(turnOOP,cube,dir);
        backendTurn.detach();
    }

    else if (glfwGetKey(GLFW_KEY_LCTRL)==GLFW_PRESS && !backendTurn.joinable() && !turning && cube->getChoice()>=0){
        turning = true;
        (upside==1) ? (dir = Direction::COUNTER_CLOCK_WISE) : (dir = Direction::CLOCK_WISE);
        backendTurn = std::thread(turnOOP,cube,dir);
        backendTurn.detach();
    }

    boolean.unlock();
}

void Cube::draw(int length, float Cx , float Cy , float Cz){

    callbackPtrCube = this;

    int     width, height;
    int     frame = 0;
    bool    running = true;

    glfwInit();

    if( !glfwOpenWindow( 300, 300, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetWindowTitle("In the beginning");
    glfwSetWindowPos(500,200);
    glfwSetWindowSize(512,512);

    glfwSetMouseWheelCallback( scrollFunction );
    glfwSetKeyCallback( modeAndChoiceCb );

    while(running)
    {
        frame++;

        glfwGetWindowSize( &width, &height );
        height = height > 0 ? height : 1;

        glViewport( 0, 0, width, height ); //?

        glClearColor( 0.45f, 0.45f, 0.45f, 0.82f );
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
        draw_example_cube(length,Cx,Cy,Cz);
        cubeAccess.unlock();

        modifyPOV();



        if (glfwGetKey(GLFW_KEY_F10)==GLFW_PRESS){ //if not turning anymore
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
