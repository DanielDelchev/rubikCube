#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>

/**@TODO
    *revise how lighting vector works so as to figure out how to make the chosen row paler
    *see multhithreading specifics in glfw and key callbacks
    *if nothing relevant, see what will happen if we use std::thread and in each of them
    *define a callback for a single key
    *finish unit tests
    *start gui implementation of Cube
    *DO NOT FORGET THAT THERE IS ROTATING IN THE VIEW POINT KEY CALLBACK WHICH MIGHT CAUSE PROBLEMS LATER
    *ALTHOUGH IF IT THE CALLBACK GETS LOCKED/DISABLED WHILE SPINNINNG ANIMATION OCCURS, THERE OUGHT NOT BE A PROBLEM
    *POSSIBLY AWAIT WILL BE USED BY THE OOP TURN FUNCTION WAITING FOR THE GUI TURN TO END ?

    also spinning could use more testing to check if some combinations of alpha+beta changes cause abnormalities in the GUI
    this could be testet later on by beta testers ?

*/

//callback function for mouse scroll motion is of type : void (*) (int)
//so these following arguments are global, they are also static, so thy would not be
//used when linking


#define PI 3.14


// file local variables and constants
static const float EPS = 0.01;
static const float STEP = 0.04;
static int rotationView = 0;
static float R = 5;
static double alpha = 45;
static double beta = 45;
static int lastScrollPosition = 0;
static const int HALF_CIRCLE = 180;
static const int CIRCLE = 360;


void scrollFunction (int scrollPosition){
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

void modifyPOV(){
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
        beta -= STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if  ( (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            (rotationView == 0) ? (rotationView=HALF_CIRCLE) : (rotationView=0);
            //{ std::cout<<"rotation:"<<std::endl;}
            beta -= STEP;
        }
    }
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
        beta += STEP;
        if ( (fabs(beta - CIRCLE) < EPS) || (fabs(beta + CIRCLE) < EPS) ){
            beta = 0;
        }
        if ( (fabs(beta - HALF_CIRCLE) < EPS) || (fabs(beta + HALF_CIRCLE) < EPS) || (fabs(beta) < EPS) ){
            (rotationView == 0) ? (rotationView=HALF_CIRCLE) : (rotationView=0);
            //{ std::cout<<"rotation:"<<std::endl;}
            beta += STEP;
        }

    }
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
        alpha -= STEP;
        if ( (fabs(alpha - CIRCLE) < EPS) || (fabs(alpha + CIRCLE) < EPS) ){
            alpha = 0;
        }
    }
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
        alpha += STEP;
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

void Cube::draw(int length, float Cx , float Cy , float Cz){

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


        glRotatef(rotationView, 0.0f, 0.0f, 1.0f);

        //std::cout<<alpha<<" "<<beta<<std::endl;

        gluLookAt(X, Y, Z,
                Cx, Cy, Cz,
                0.0f, 0.0f, 1 );
        draw_example_cube(length,Cx,Cy,Cz);

        modifyPOV();

        glfwSwapBuffers();


        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);
    }

    glfwTerminate();

}
