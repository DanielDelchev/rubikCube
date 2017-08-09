#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>
#include <cmath>


//callback function for mouse scroll motion is of type : void (*) (int)
//so these following arguments are global, they are also static, so thy would not be
//used when linking


#define PI 3.14

static int rot = 0;
static float R = 5;
static int alpha = 45;
static int beta = 45;
static int lastScrollPosition = 0;


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


/*
void moveFunction (int xPos, int yPos){

    //step MUST be a number, so that (int) beta % 180 == 0 will be true an odd number of times!
    const float STEP = 0.2;

    if (xPos > lastXpos){
        beta += STEP;
    }
    if (xPos <lastXpos){
        beta -= STEP;
    }
    if (yPos > lastYpos){
        alpha -= STEP;
    }
    if (yPos < lastYpos){
        alpha += STEP;
    }

    if ( (int) beta % 180 == 0){
            (rot == 0) ? (rot=180) : (rot=0);
        }

    lastXpos = xPos;
    lastYpos = yPos;

}


void mouseClick(int buttonID,int state){
    if (buttonID == GLFW_MOUSE_BUTTON_LEFT){
        if (state == GLFW_PRESS){
            glfwGetMousePos(&lastXpos,&lastYpos);
            glfwSetMousePosCallback( moveFunction );
        }
        else {
            glfwSetMousePosCallback( NULL );
        }
    }
}
*/


//this function is good enough by itselfF
//perhaps see if we can use callback on buttons with multhitheading?
void mover(int buttonID,int state){

    const int STEP = 1;

    switch (buttonID){

        case GLFW_KEY_UP:
            if (state == GLFW_PRESS){
                glfwEnable( GLFW_KEY_REPEAT);
                beta -= STEP;
                beta %= 360;
                if ( (beta % 180) == 0 ){
                    (rot == 0) ? (rot=180) : (rot=0);
                }
            }
            else if (state == GLFW_RELEASE){
                glfwDisable( GLFW_KEY_REPEAT);
            }
            break;

        case GLFW_KEY_DOWN:
            if (state == GLFW_PRESS){
                glfwEnable( GLFW_KEY_REPEAT);
                beta += STEP;
                beta %= 360;
                if ( (beta % 180) == 0 ){
                    (rot == 0) ? (rot=180) : (rot=0);
                }
            else if (state == GLFW_RELEASE){
                glfwDisable( GLFW_KEY_REPEAT);
                }
            }
            break;


        case GLFW_KEY_LEFT:
            if (state == GLFW_PRESS){
                glfwEnable( GLFW_KEY_REPEAT);
                alpha -= STEP;
                alpha %= 360;
            }
            else if (state == GLFW_RELEASE){
                glfwDisable( GLFW_KEY_REPEAT);
            }
            break;

        case GLFW_KEY_RIGHT:
            if (state == GLFW_PRESS){
                glfwEnable( GLFW_KEY_REPEAT);
                alpha += STEP;
                alpha %= 360;
            }
            else if (state == GLFW_RELEASE){
                glfwDisable( GLFW_KEY_REPEAT);
            }
            break;

    }


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
//    glfwSetMouseButtonCallback( mouseClick );
    glfwSetKeyCallback( mover );

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

        float alphaRads = ( static_cast<float> (alpha) /180) * PI;
        float betaRads = ( static_cast<float> (beta) /180) * PI;

        //used so that the vector representing the position of the eye does never match the vector representing the upside of the scene
        // see gluLookAt specification for more details;
        float error = 0.0001;

        float X = R*cos(alphaRads)*sin(betaRads)+Cx+error;
        float Y = R*sin(alphaRads)*sin(betaRads)+Cy+error;
        float Z = R*cos(betaRads)+Cz;

        glRotatef(rot, 0.0f, 0.0f, 1.0f);

        gluLookAt(X, Y, Z,
                Cx, Cy, Cz,
                0.0f, 0.0f, 1 );





        glBegin( GL_TRIANGLES );

          //yellow right
          glColor3f(1.0f, 1.0f, 0.0f );

          glVertex3f(Cx+1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);

          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz+1.0f);


          //green left
          glColor3f(0.0f, 1.0f, 0.0f );

          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz-1.0f);

          glVertex3f(Cx-1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);


          //white front
          glColor3f(1.0f, 1.0f, 1.0f );

          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz-1.0f);

          glVertex3f(Cx+1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);


          //back orange
          glColor3f(0.9f, 0.4f, 0.0f );

          glVertex3f(Cx-1.0f, Cy+-1.0f, Cz+1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);

          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz+1.0f);


          //red bottom
          glColor3f(1.0f, 0.0f, 0.0f );

          glVertex3f(Cx+1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz-1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);

          glVertex3f(Cx-1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz-1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz-1.0f);


          //blue top
          glColor3f(0.0f, 0.0f, 1.0f );

          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);
          glVertex3f(Cx-1.0f, Cy-1.0f, Cz+1.0f);
          glVertex3f(Cx-1.0f, Cy+1.0f, Cz+1.0f);

          glVertex3f(Cx-1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy+1.0f, Cz+1.0f);
          glVertex3f(Cx+1.0f, Cy-1.0f, Cz+1.0f);

        glEnd();


        glfwSwapBuffers();


        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);
    }

    glfwTerminate();

}
