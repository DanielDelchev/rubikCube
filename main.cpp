#include "Cube.h"
#include <iostream>
#include "UnitTest++.h"



int main()
{

    Cube& cb =  Cube::instance();
    cb.draw(30,0.100,-100,10000);
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
