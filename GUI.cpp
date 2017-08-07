#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>



//callback function for mouse scroll motion is of type : void (*) (int)
//so these following arguments are global, they are also static, so thy would not be
//used when linking

static float x = 0;
static float y = 0;
static float z = 0;
static int lastScrollPosition = 0;


void scrollFunction (int scrollPosition){
        if (lastScrollPosition>scrollPosition && x <=5){
            x += 0.2f;
        }
        if (lastScrollPosition<scrollPosition && x>=-5){
            x -= 0.2f;
        }
        lastScrollPosition = scrollPosition;
}



void pageFunction (int button, int pressed){
        glfwEnable( GLFW_KEY_REPEAT );
        if ( (button == GLFW_KEY_PAGEUP) && pressed && x<=5){
            x+=0.2;
        }
        if ( (button == GLFW_KEY_PAGEDOWN) && pressed && x>=-5){
            x-=0.2;
        }
        if (!pressed){
            glfwDisable( GLFW_KEY_REPEAT );
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
    glfwSetKeyCallback( pageFunction );

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

        // Draw some rotating garbage
        glMatrixMode( GL_MODELVIEW );//
        glLoadIdentity();
        gluLookAt(8.0f+x, 0.0f+y, 0.0f+z,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f );

        //glTranslatef( 1.0f, 1.0f, 0.0f );
        glRotatef(frame/100, 0.0f, 0.5f, 0.5f);//
        glBegin( GL_TRIANGLES );



          //yellow right
          glColor3f(1.0f, 1.0f, 0.0f );

          glVertex3f(1.0f, 1.0f, 1.0f);
          glVertex3f(1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);

          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, 1.0f);
          glVertex3f(1.0f, 1.0f, 1.0f);


          //green left
          glColor3f(0.0f, 1.0f, 0.0f );

          glVertex3f(1.0f, -1.0f, 1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);

          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f(1.0f, -1.0f, 1.0f);


          //white front
          glColor3f(1.0f, 1.0f, 1.0f );

          glVertex3f(1.0f, -1.0f, 1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);
          glVertex3f(1.0f, 1.0f, -1.0f);

          glVertex3f(1.0f, 1.0f, -1.0f);
          glVertex3f(1.0f, 1.0f, 1.0f);
          glVertex3f(1.0f, -1.0f, 1.0f);


          //back orange
          glColor3f(0.9f, 0.4f, 0.0f );

          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);

          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, 1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);


          //red bottom
          glColor3f(1.0f, 0.0f, 0.0f );

          glVertex3f(1.0f, -1.0f,-1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);

          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(1.0f, 1.0f, -1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);


          //blue top
          glColor3f(0.0f, 0.0f, 1.0f );

          glVertex3f(1.0f, -1.0f,1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f(-1.0f, 1.0f, 1.0f);

          glVertex3f(-1.0f, 1.0f, 1.0f);
          glVertex3f(1.0f, 1.0f, 1.0f);
          glVertex3f(1.0f, -1.0f, 1.0f);

        glEnd();


        glfwSwapBuffers();


        // exit if ESC was pressed or window was closed
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);
    }

    glfwTerminate();

}
