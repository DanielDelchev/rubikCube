#include "Cube.h"
#include "UnitTest++.h"

//BottomToTop mode, clockwise & anticlockwise, choices  1,2,3 (tested with 3 rows cube)

TEST(BottomToTopClockwise0){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,0);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][0];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][i];
        lhs4 = temp;

        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::RED;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::RED;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][0] = Color::BLACK;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][2] = Color::GREY;
    }


    //myCube.print();
    //controlCube.print();



    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);

}

TEST(BottomToTopCounterClockwise0){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,0);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::COUNTER_CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][0];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][i];
        lhs4 = temp;

        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::RED;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::RED;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][0] = Color::GREY;
        controlCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][2] = Color::BLACK;
    }


//    myCube.print();
//    controlCube.print();

    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);
}

TEST(BottomToTopClockwise1){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,1);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[1][1];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[1][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[1][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[1][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[1][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[1][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[1][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[1][i];
        lhs4 = temp;

    }


    //myCube.print();
    //controlCube.print();

    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);
}

TEST(BottomToTopCounterClockwise1){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,1);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::COUNTER_CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[1][1];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[1][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[1][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[1][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[1][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[1][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[1][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[1][i];
        lhs4 = temp;

    }


//    myCube.print();
//    controlCube.print();

    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);
}

TEST(BottomToTopClockwise2){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,2);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][2];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][i];
        lhs4 = temp;

        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::BLUE;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLUE;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][0] = Color::BLACK;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][2] = Color::GREY;
    }


//    myCube.print();
//    controlCube.print();

    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);
}

TEST(BottomToTopCounterClockwise2){
    int rows = 3;
    Cube myCube(rows,Mode::BOTTOM_TO_TOP,2);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    Cube controlCube = myCube;
    myCube.turn(Direction::COUNTER_CLOCK_WISE);

    //alter myCube accordingly manually
    Color temp = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][2];
    for (int i=0;i<rows;i++){

        Color  &lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][i];
        lhs1 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][i];

        Color &lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][i];
        lhs2 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][i];

        Color &lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][i];
        lhs3 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][i];

        Color &lhs4 = controlCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][i];
        lhs4 = temp;

        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::BLUE;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLUE;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][0] = Color::GREY;
        controlCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][2] = Color::BLACK;
    }


//    myCube.print();
//    controlCube.print();

    bool same = (myCube == controlCube);
    CHECK_EQUAL(true,same);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FrontToBack mode, clockwise & anticlockwise, choices  1,2,3 (tested with 3 rows cube)

TEST(FrontToBackClockwise1){

}

TEST(FrontToBackCounterClockwise1){

}

TEST(FrontToBackClockwise2){

}

TEST(FrontToBackCounterClockwise2){

}

TEST(FrontToBackClockwise3){

}

TEST(FrontToBackCounterClockwise3){

}

//LeftToRight mode, clockwise & anticlockwise, choices  1,2,3 (tested with 3 rows cube)

TEST(LeftToRightClockwise1){

}

TEST(LeftToRightCounterClockwise1){

}

TEST(LeftToRightClockwise2){

}

TEST(LeftToRightCounterClockwise2){

}

TEST(LeftToRightCounterClockwise3){

}

TEST(LeftToRightClockwise3){

}
