#include "Cube.h"
#include "UnitTest++.h"
#include <iostream>


/*
* This file contains unit tests for the turn function of the Cube class
* there are 18 tests (1 for each possible configuration of the turn)
* for a Cube 3x3x3. Later on more unittest may be added
* for the solve function of Cube and some other utility functions
* but currently it is vital to know that the turn function is working properly
* so as to look for any future bugs in the GUI part.
*/


#define CHECK_SIDES_EQUAL     bool topMatch = (top == myCube.getCubeSide()[static_cast<int> (Side::TOP)]); \
                              bool bottomMatch = (bottom == myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)]); \
                              bool leftMatch = (left == myCube.getCubeSide()[static_cast<int> (Side::LEFT)]); \
                              bool rightMatch = (right == myCube.getCubeSide()[static_cast<int> (Side::RIGHT)]); \
                              bool frontMatch = (front == myCube.getCubeSide()[static_cast<int> (Side::FRONT)]); \
                              bool backMatch = (back == myCube.getCubeSide()[static_cast<int> (Side::BACK)]); \
                              CHECK_EQUAL(true, topMatch); \
                              CHECK_EQUAL(true, bottomMatch); \
                              CHECK_EQUAL(true, leftMatch); \
                              CHECK_EQUAL(true, rightMatch); \
                              CHECK_EQUAL(true, frontMatch); \
                              CHECK_EQUAL(true, backMatch); \

/*
* Fixture class containing common variables for the unittests and
* some utility functions for them. Also build up and tear down functions
* ( the constructor and destructo of the class)
*/
struct Fixture
{
    Fixture() {
        myCube.setChoice (-1);
        for (int i=0;i<Cube::SIDES_COUNT;i++){
            myCube.getCubeSide()[i] = CubeSide(rows ,static_cast<Color> (i));
        }
    }

    ~Fixture() {
        for (int i=0;i<Cube::SIDES_COUNT;i++){
            myCube.getCubeSide()[i] = CubeSide(rows ,static_cast<Color> (i));
        }
    }

    CubeSide top, bottom, left, right, front, back ;

    void debugPrint(){
        myCube.print();
        std::cout<<std::endl;

        std::cout<<"bottom:\n";
        bottom.print();
        std::cout<<"\n";

        std::cout<<"top:\n";
        top.print();
        std::cout<<"\n";

        std::cout<<"left:\n";
        left.print();
        std::cout<<"\n";

        std::cout<<"right:\n";
        right.print();
        std::cout<<"\n";

        std::cout<<"front:\n";
        front.print();
        std::cout<<"\n";

        std::cout<<"back:\n";
        back.print();
        std::cout<<"\n";

    }

    const int rows = 3;
    Cube& myCube = Cube::instance(rows,Mode::TOP_TO_BOTTOM,-1,5);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BottomToTop mode, clockwise & anticlockwise, choices  0,1,2 (tested with 3 rows cube)

TEST_FIXTURE(Fixture, BottomToTopClockwise0){
    int choice = 0;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = right.getWall()[choice][i];

        Color &lhs2 = right.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = left.getWall()[choice][i];

        Color &lhs4 = left.getWall()[choice][i];
        lhs4 = temp;
    }

    top.getWall()[0][2] = Color::RED;
    top.getWall()[2][0] = Color::RED;
    top.getWall()[0][0] = Color::BLACK;
    top.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;
}



TEST_FIXTURE(Fixture, BottomToTopCounterClockwise0){
    int choice = 0;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = left.getWall()[choice][i];

        Color &lhs2 = left.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = right.getWall()[choice][i];

        Color &lhs4 = right.getWall()[choice][i];
        lhs4 = temp;
    }

    top.getWall()[0][2] = Color::RED;
    top.getWall()[2][0] = Color::RED;
    top.getWall()[0][0] = Color::GREY;
    top.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;
}


TEST_FIXTURE(Fixture, BottomToTopClockwise1){
    int choice = 1;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = right.getWall()[choice][i];

        Color &lhs2 = right.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = left.getWall()[choice][i];

        Color &lhs4 = left.getWall()[choice][i];
        lhs4 = temp;

    }

    CHECK_SIDES_EQUAL;

}

TEST_FIXTURE(Fixture, BottomToTopCounterClockwise1){
    int choice = 1;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = left.getWall()[choice][i];

        Color &lhs2 = left.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = right.getWall()[choice][i];

        Color &lhs4 = right.getWall()[choice][i];
        lhs4 = temp;

    }


    CHECK_SIDES_EQUAL;
}


TEST_FIXTURE(Fixture, BottomToTopClockwise2){
    int choice = 2;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;


    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = right.getWall()[choice][i];

        Color &lhs2 = right.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = left.getWall()[choice][i];

        Color &lhs4 = left.getWall()[choice][i];
        lhs4 = temp;
    }
    bottom.getWall()[0][2] = Color::BLUE;
    bottom.getWall()[2][0] = Color::BLUE;
    bottom.getWall()[0][0] = Color::BLACK;
    bottom.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;

}

TEST_FIXTURE(Fixture, BottomToTopCounterClockwise2){
    int choice = 2;
    myCube.setChoice(choice);
    myCube.setMode(Mode::TOP_TO_BOTTOM);
    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[i][i] = Color::RED;
        myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[i][i] = Color::BLUE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::TOP)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        Color temp = front.getWall()[choice][i];

        Color  &lhs1 = front.getWall()[choice][i];
        lhs1 = left.getWall()[choice][i];

        Color &lhs2 = left.getWall()[choice][i];
        lhs2 = back.getWall()[choice][i];

        Color &lhs3 = back.getWall()[choice][i];
        lhs3 = right.getWall()[choice][i];

        Color &lhs4 = right.getWall()[choice][i];
        lhs4 = temp;
    }

    bottom.getWall()[0][2] = Color::BLUE;
    bottom.getWall()[2][0] = Color::BLUE;
    bottom.getWall()[0][0] = Color::GREY;
    bottom.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FrontToBack mode, clockwise & anticlockwise, choices  0,1,2 (tested with 3 rows cube)


TEST_FIXTURE(Fixture, FrontToBackClockwise0){
    int choice = 0;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = left.getWall()[shift][shiftChoice];

        Color &lhs2 = left.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = right.getWall()[i][choice];

        Color &lhs4 = right.getWall()[i][choice];
        lhs4 = temp;
    }

    front.getWall()[0][2] = Color::ORANGE;
    front.getWall()[2][0] = Color::ORANGE;
    front.getWall()[0][0] = Color::BLACK;
    front.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;
}


TEST_FIXTURE(Fixture, FrontToBackClockwise1){
    int choice = 1;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = left.getWall()[shift][shiftChoice];

        Color &lhs2 = left.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = right.getWall()[i][choice];

        Color &lhs4 = right.getWall()[i][choice];
        lhs4 = temp;
    }

    CHECK_SIDES_EQUAL;
}

TEST_FIXTURE(Fixture, FrontToBackClockwise2){
    int choice = 2;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = left.getWall()[shift][shiftChoice];

        Color &lhs2 = left.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = right.getWall()[i][choice];

        Color &lhs4 = right.getWall()[i][choice];
        lhs4 = temp;

    }


    back.getWall()[0][2] = Color::WHITE;
    back.getWall()[2][0] = Color::WHITE;
    back.getWall()[0][0] = Color::BLACK;
    back.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;

}


TEST_FIXTURE(Fixture, FrontToBackCounterClockwise0){
    int choice = 0;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){
        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = right.getWall()[i][choice];

        Color &lhs2 = right.getWall()[i][choice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = left.getWall()[shift][shiftChoice];

        Color &lhs4 = left.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }

    front.getWall()[0][2] = Color::ORANGE;
    front.getWall()[2][0] = Color::ORANGE;
    front.getWall()[0][0] = Color::GREY;
    front.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;
}

TEST_FIXTURE(Fixture, FrontToBackCounterClockwise1){
    int choice = 1;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = right.getWall()[i][choice];

        Color &lhs2 = right.getWall()[i][choice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = left.getWall()[shift][shiftChoice];

        Color &lhs4 = left.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }

    CHECK_SIDES_EQUAL;
}

TEST_FIXTURE(Fixture, FrontToBackCounterClockwise2){
    int choice = 2;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::FRONT_TO_BACK);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[i][i] = Color::ORANGE;
        myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[i][i] = Color::WHITE;
    }
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::BACK)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[shiftChoice][i];

        Color  &lhs1 = top.getWall()[shiftChoice][i];
        lhs1 = right.getWall()[i][choice];

        Color &lhs2 = right.getWall()[i][choice];
        lhs2 = bottom.getWall()[shiftChoice][i];

        Color &lhs3 = bottom.getWall()[shiftChoice][i];
        lhs3 = left.getWall()[shift][shiftChoice];

        Color &lhs4 = left.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }


    back.getWall()[0][2] = Color::WHITE;
    back.getWall()[2][0] = Color::WHITE;
    back.getWall()[0][0] = Color::GREY;
    back.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LeftToRight mode, clockwise & anticlockwise, choices  0,1,2 (tested with 3 rows cube)

TEST_FIXTURE(Fixture, LeftToRightClockwise0){
    int choice = 0;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = back.getWall()[shift][shiftChoice];

        Color &lhs2 = back.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = front.getWall()[i][choice];

        Color &lhs4 = front.getWall()[i][choice];
        lhs4 = temp;
    }

    left.getWall()[0][2] = Color::YELLOW;
    left.getWall()[2][0] = Color::YELLOW;
    left.getWall()[0][0] = Color::BLACK;
    left.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;
}

TEST_FIXTURE(Fixture, LeftToRightClockwise1){
    int choice = 1;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = back.getWall()[shift][shiftChoice];

        Color &lhs2 = back.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = front.getWall()[i][choice];

        Color &lhs4 = front.getWall()[i][choice];
        lhs4 = temp;
    }

    CHECK_SIDES_EQUAL;
}

TEST_FIXTURE(Fixture, LeftToRightClockwise2){

    int choice = 2;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::CLOCK_WISE);
    myCube.setDir(Direction::CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = back.getWall()[shift][shiftChoice];

        Color &lhs2 = back.getWall()[shift][shiftChoice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = front.getWall()[i][choice];

        Color &lhs4 = front.getWall()[i][choice];
        lhs4 = temp;
    }

    right.getWall()[0][2] = Color::GREEN;
    right.getWall()[2][0] = Color::GREEN;
    right.getWall()[0][0] = Color::BLACK;
    right.getWall()[2][2] = Color::GREY;

    CHECK_SIDES_EQUAL;

}

TEST_FIXTURE(Fixture, LeftToRightCounterClockwise0){
    int choice = 0;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();


    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = front.getWall()[i][choice];

        Color &lhs2 = front.getWall()[i][choice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = back.getWall()[shift][shiftChoice];

        Color &lhs4 = back.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }

    left.getWall()[0][2] = Color::YELLOW;
    left.getWall()[2][0] = Color::YELLOW;
    left.getWall()[0][0] = Color::GREY;
    left.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;

}

TEST_FIXTURE(Fixture, LeftToRightCounterClockwise1){
    int choice = 1;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //myCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = front.getWall()[i][choice];

        Color &lhs2 = front.getWall()[i][choice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = back.getWall()[shift][shiftChoice];

        Color &lhs4 = back.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }

    CHECK_SIDES_EQUAL;

}

TEST_FIXTURE(Fixture, LeftToRightCounterClockwise2){
    int choice = 2;
    int shiftChoice = (rows - 1 - choice)%rows;
    myCube.setChoice(choice);
    myCube.setMode(Mode::LEFT_TO_RIGHT);

    for (int i=0;i<rows;i++){
        myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[i][i] = Color::YELLOW;
        myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[i][i] = Color::GREEN;
    }
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[2][0] = Color::BLACK;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[0][2] = Color::GREY;
    myCube.getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[2][0] = Color::BLACK;

    top = myCube.getCubeSide()[static_cast<int> (Side::TOP)];
    bottom = myCube.getCubeSide()[static_cast<int> (Side::BOTTOM)];
    left = myCube.getCubeSide()[static_cast<int> (Side::LEFT)];
    right = myCube.getCubeSide()[static_cast<int> (Side::RIGHT)];
    front = myCube.getCubeSide()[static_cast<int> (Side::FRONT)];
    back = myCube.getCubeSide()[static_cast<int> (Side::BACK)];

    //fmyCube.turn(Direction::COUNTER_CLOCK_WISE);
    myCube.setDir(Direction::COUNTER_CLOCK_WISE);
    myCube.turn();

    for (int i=0;i<rows;i++){

        int shift = (rows-i-1)%rows;

        Color temp = top.getWall()[i][choice];

        Color  &lhs1 = top.getWall()[i][choice];
        lhs1 = front.getWall()[i][choice];

        Color &lhs2 = front.getWall()[i][choice];
        lhs2 = bottom.getWall()[shift][shiftChoice];

        Color &lhs3 = bottom.getWall()[shift][shiftChoice];
        lhs3 = back.getWall()[shift][shiftChoice];

        Color &lhs4 = back.getWall()[shift][shiftChoice];
        lhs4 = temp;
    }

    right.getWall()[0][2] = Color::GREEN;
    right.getWall()[2][0] = Color::GREEN;
    right.getWall()[0][0] = Color::GREY;
    right.getWall()[2][2] = Color::BLACK;

    CHECK_SIDES_EQUAL;
}

