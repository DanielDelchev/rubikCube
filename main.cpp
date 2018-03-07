#include "Cube.h"
#include <iostream>
#include "UnitTest++.h"

#ifdef __WIN32__
#include "windows.h"
#endif // __WIN32__

int main()
{
    #ifdef __WIN32__
    FreeConsole();
    #endif // __WIN32__

    // unittests are designed for 3x3x3 cube, and will crash with segmentation fault for other dimentions of the cube
    #ifndef UNITTESTPP_H
        Cube& cb =  Cube::instance(8,Mode::TOP_TO_BOTTOM,-1,27);
    #else
        Cube& cb =  Cube::instance();
    #endif

    cb.draw(0.100,-100,10000);

    #ifdef UNITTESTPP_H
        return UnitTest::RunAllTests();
    #endif
    return 0;


/*
 Cube T;
 T.getCubeSide()[static_cast<int>(Side::TOP)].getWall()[0][0] = Color::RED;
 T.getCubeSide()[static_cast<int>(Side::TOP)].getWall()[1][1] = Color::RED;
 T.getCubeSide()[static_cast<int>(Side::TOP)].getWall()[1][1] = Color::RED;
 T.getCubeSide()[static_cast<int>(Side::TOP)].getWall()[0][2] = Color::GREY;
 T.getCubeSide()[static_cast<int>(Side::TOP)].getWall()[2][0] = Color::BLACK;

    T.getCubeSide()[static_cast<int>(Side::TOP)].print();

    T.getCubeSide()[static_cast<int>(Side::TOP)].transponate();
    std::cout<<std::endl;
    T.getCubeSide()[static_cast<int>(Side::TOP)].print();


   // T.getCubeSide()[static_cast<int>(Side::TOP)].reverseRows();
   // std::cout<<std::endl;
   // T.getCubeSide()[static_cast<int>(Side::TOP)].print();

    T.getCubeSide()[static_cast<int>(Side::TOP)].reverseColumns();
    std::cout<<std::endl;
    T.getCubeSide()[static_cast<int>(Side::TOP)].print();

 return 0;

 */
}
