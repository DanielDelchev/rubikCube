#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <GL/glfw.h>

void drawSubcube(float sideLength,float Cx, float Cy, float Cz);
void drawBox(float length, float width, float height, float Cx, float Cy, float Cz);
void drawTileFrontBack(float sideLength, float Cx, float Cy, float Cz);
void drawTileLeftRight(float sideLength, float Cx, float Cy, float Cz);
void drawTileTopBottom(float sideLength, float Cx, float Cy, float Cz);


#endif // UTILITIES_H_INCLUDED
