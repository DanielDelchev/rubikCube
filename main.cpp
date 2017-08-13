#include "Cube.h"
#include <iostream>
#include "UnitTest++.h"



int main()
{

    Cube T = Cube();
    T.setChoice(0);
    T.draw(2,0,0,0);

    return 0;//UnitTest::RunAllTests();

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
