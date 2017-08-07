#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>
#include <memory>

//currently hollow, since no allocation on the heal is performed
void Cube::destroy(){}
Cube::~Cube(){destroy();}

Cube::Cube(int _scaling, Mode _mode, int _choice):scaling(_scaling),mode(_mode),choice(_choice){
    for (int i=0;i<SIDES_COUNT;i++){
        getCubeSide()[i].paint(static_cast<Color> (i));

    }
}

void Cube::copy(const Cube &given){
    scaling = given.getScaling();
    mode = given.getMode();
    choice = given.getChoice();
    for (int i=0;i<SIDES_COUNT;i++){
        cubeSide[i] = given.getCubeSide()[i];
    }
    history = given.getHistory();
}

Cube::Cube(const Cube &given){
    copy(given);
}


Cube& Cube::operator=(const Cube &given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}


void Cube::print(){
    std::cout<<"BOTTOM:\n";
    getCubeSide()[static_cast<int>(Side::BOTTOM)].print();
    std::cout<<"\n";

    std::cout<<"TOP:\n";
    getCubeSide()[static_cast<int>(Side::TOP)].print();
    std::cout<<"\n";

    std::cout<<"LEFT:\n";
    getCubeSide()[static_cast<int>(Side::LEFT)].print();
    std::cout<<"\n";

    std::cout<<"RIGHT:\n";
    getCubeSide()[static_cast<int>(Side::RIGHT)].print();
    std::cout<<"\n";

    std::cout<<"FRONT:\n";
    getCubeSide()[static_cast<int>(Side::FRONT)].print();
    std::cout<<"\n";

    std::cout<<"BACK:\n";
    getCubeSide()[static_cast<int>(Side::BACK)].print();
    std::cout<<"\n";
}



// this is what it was all about so far
// unit test for initial state of colors
// TODO implement this function, write 3*3*2 = 18 unit tests
// write operator == for cube and for sides for easier unit testing

void Cube::turn(Direction dir){

    //aquire lock?

    (dir == Direction::CLOCK_WISE) ? turnClockwise() : turnCounterClockwise();
    history.push(Turn(getMode(),getChoice(),Direction::CLOCK_WISE));


    // release lock or await end of animation?
}

void Cube::turnClockwise(){

    const int rows = getCubeSide()[0].getDimention();
    std::unique_ptr<Color[]> buffer (new Color[rows]);

    const int SIDES_TO_TURN = 4;

      Side sideIndexBottomToTop [SIDES_TO_TURN] = {Side::LEFT, Side::FRONT, Side::RIGHT, Side::BACK};
      Side sideIndexLeftToRight [SIDES_TO_TURN] = {Side::FRONT, Side::TOP, Side::BACK, Side::BOTTOM};
      Side sideIndexFrontToBack [SIDES_TO_TURN] = {Side::TOP, Side::RIGHT, Side::BOTTOM, Side::LEFT};
      (void) sideIndexBottomToTop;
      (void) sideIndexFrontToBack;
      (void) sideIndexLeftToRight;

    switch(getMode()){

        case Mode::BOTTOM_TO_TOP:

            for (int j=0;j<rows;j++){

                int currentChoice = getChoice();

                buffer[j] = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];

                Color &lhs2 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];

                Color &lhs4 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];
                lhs4 = buffer[j];

            }


            if ( choice == 0 ){
                getCubeSide()[static_cast <int> (Side::TOP)].transponate();
                getCubeSide()[static_cast <int> (Side::TOP)].reverseRows();
            }
            else if (choice == (rows-1)){
                getCubeSide()[static_cast <int> (Side::BOTTOM)].transponate();
                getCubeSide()[static_cast <int> (Side::BOTTOM)].reverseRows();
            }



            break;

        case Mode::LEFT_TO_RIGHT:
            //swap rows of affected walls accordingly
            if ( choice == 0 || choice == (rows-1) ){
                //trnasponate wall
            }
            break;

        case Mode::FRONT_TO_BACK:
            //swap rows of affected walls accordingly
            if ( choice == 0 || choice == (rows-1) ){
                //trnasponate wall
            }
            break;
        }


}


void Cube::turnCounterClockwise(){

    const int rows = getCubeSide()[0].getDimention();
    std::unique_ptr<Color[]> buffer (new Color[rows]);

    const int SIDES_TO_TURN = 4;

      Side sideIndexBottomToTop [SIDES_TO_TURN] = {Side::LEFT, Side::FRONT, Side::RIGHT, Side::BACK};
      Side sideIndexLeftToRight [SIDES_TO_TURN] = {Side::FRONT, Side::TOP, Side::BACK, Side::BOTTOM};
      Side sideIndexFrontToBack [SIDES_TO_TURN] = {Side::TOP, Side::RIGHT, Side::BOTTOM, Side::LEFT};
      (void) sideIndexBottomToTop;
      (void) sideIndexFrontToBack;
      (void) sideIndexLeftToRight;

    switch(getMode()){

        case Mode::BOTTOM_TO_TOP:

            for (int j=0;j<rows;j++){

                int currentChoice = getChoice();

                buffer[j] = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];

                Color &lhs2 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];

                Color &lhs4 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];
                lhs4 = buffer[j];

            }


            if ( choice == 0 ){
                getCubeSide()[static_cast <int> (Side::TOP)].transponate();
                getCubeSide()[static_cast <int> (Side::TOP)].reverseColumns();
            }

            else if ( choice == rows-1 ){
                getCubeSide()[static_cast <int> (Side::BOTTOM)].transponate();
                getCubeSide()[static_cast <int> (Side::BOTTOM)].reverseColumns();
            }
            break;

        case Mode::LEFT_TO_RIGHT:
            //swap rows of affected walls accordingly
            if ( choice == 0 || choice == (rows-1) ){
                //trnasponate wall
            }
            break;

        case Mode::FRONT_TO_BACK:
            //swap rows of affected walls accordingly
            if ( choice == 0 || choice == (rows-1) ){
                //trnasponate wall
            }
            break;
        }


}


bool Cube::operator==(const Cube &given)const{
    bool result = true;
    for (int i=0;i<SIDES_COUNT;i++){
        result = result && (getCubeSide()[i] == given.getCubeSide()[i]);
    }
    return result;
}













