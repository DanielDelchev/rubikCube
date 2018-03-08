#include "Cube.h"
#include <GL/glfw.h>
#include <iostream>


void Cube::destroy(){}
Cube::~Cube(){destroy();}

Cube::Cube(int _rows, Mode _mode, int _choice, int _length):mode(_mode),choice(_choice),rows(_rows){
    dir = Direction::NEUTRAL;
    for (int i=0;i<SIDES_COUNT;i++){
        getCubeSide()[i] = CubeSide(rows ,static_cast<Color> (i));
    }

    if ( (rows < 2) || (rows > 9)){
        rows = 3;
    }

    setLength(_length);
}

void Cube::choiceDecrease(){
    int rowsCount = getRows();
    int current = getChoice();
    if (current == 0){
        setChoice(-1);
    }
    else if (current == -1){
        setChoice(rowsCount-1);
    }
    else{
        setChoice( (current-1) % rowsCount) ;
    }

    //
    std::cout<<getChoice()<<std::endl;
}

void Cube::choiceIncrease(){
    int rowsCount = getRows();
    int current = getChoice();
    if (current == rowsCount-1){
        setChoice(-1);
    }
    else if (current == -1){
        setChoice(0);
    }
    else{
        setChoice( (current+1) % rowsCount) ;
    }

    //
    std::cout<<getChoice()<<std::endl;
}

void Cube::modeIncrease(){
    Mode current = getMode();
    const int modesCount = 3;
    setMode( static_cast<Mode>((static_cast<int>(current)+1)%modesCount) );

    //
    std::cout<<static_cast<int> (getMode())<<std::endl;
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


void Cube::turn(){
    (dir == Direction::CLOCK_WISE) ? turnClockwise() : turnCounterClockwise();
    history.push(Turn(getMode(),getChoice(),dir));
}

void Cube::turnClockwise(){

    const int rowsCount = getCubeSide()[0].getDimention();
    //int subsquares =  rowsCount*rowsCount;
    Color buffer;

    switch(getMode()){

        case Mode::TOP_TO_BOTTOM:

            for (int j=0;j<rowsCount;j++){

                int currentChoice = getChoice();

                buffer = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];

                Color &lhs2 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];

                Color &lhs4 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];
                lhs4 = buffer;

            }

            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::TOP)].transponate();
                getCubeSide()[static_cast <int> (Side::TOP)].reverseRows();
            }
            else if ( getChoice() == (rowsCount-1)){
                getCubeSide()[static_cast <int> (Side::BOTTOM)].transponate();
                getCubeSide()[static_cast <int> (Side::BOTTOM)].reverseRows();
            }

            break;

        case Mode::LEFT_TO_RIGHT:

            for (int j=0;j<rowsCount;j++){

                //int shift = (subsquares-j-1)%rows;
                int shift = (rows-j-1)%rows;
                int currentChoice = getChoice();
                int shiftCurrentChoice = (rows - 1 -currentChoice)%rows;

                buffer = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[j][currentChoice];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[j][currentChoice];
                lhs1 = getCubeSide()[static_cast<int> (Side::TOP)].getWall()[j][currentChoice];

                Color &lhs2 = cubeSide[static_cast<int> (Side::TOP)].getWall()[j][currentChoice];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[shift][shiftCurrentChoice];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[shift][shiftCurrentChoice];
                lhs3 = getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[shift][shiftCurrentChoice];

                Color &lhs4 = cubeSide[static_cast<int> (Side::BOTTOM)].getWall()[shift][shiftCurrentChoice];
                lhs4 = buffer;

            }

            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::LEFT)].transponate();
                getCubeSide()[static_cast <int> (Side::LEFT)].reverseRows();
            }
            else if ( getChoice() == (rowsCount-1)){
                getCubeSide()[static_cast <int> (Side::RIGHT)].transponate();
                getCubeSide()[static_cast <int> (Side::RIGHT)].reverseRows();
            }

            break;


        case Mode::FRONT_TO_BACK:

            for (int j=0;j<rowsCount;j++){

                int currentChoice = getChoice();
                int shiftCurrentChoice = (rows - 1 -currentChoice)%rows;
                int shift = (rows-j-1)%rows;

                buffer = getCubeSide()[static_cast<int> (Side::TOP)].getWall()[shiftCurrentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::TOP)].getWall()[shiftCurrentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[shift][shiftCurrentChoice];

                Color &lhs2 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[shift][shiftCurrentChoice];
                lhs2 = getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[shiftCurrentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BOTTOM)].getWall()[shiftCurrentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[j][currentChoice];

                Color &lhs4 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[j][currentChoice];
                lhs4 = buffer;

            }

            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::FRONT)].transponate();
                getCubeSide()[static_cast <int> (Side::FRONT)].reverseRows();
            }
            else if ( getChoice() == (rowsCount-1)){
                getCubeSide()[static_cast <int> (Side::BACK)].transponate();
                getCubeSide()[static_cast <int> (Side::BACK)].reverseRows();
            }

            break;
        }

}


void Cube::turnCounterClockwise(){

    const int rowsCount = getCubeSide()[0].getDimention();
    //int subsquares =  rowsCount*rowsCount;
    Color buffer;

    switch(getMode()){

        case Mode::TOP_TO_BOTTOM:

            for (int j=0;j<rowsCount;j++){

                int currentChoice = getChoice();

                buffer = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[currentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];

                Color &lhs2 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[currentChoice][j];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[currentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];

                Color &lhs4 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[currentChoice][j];
                lhs4 = buffer;

            }


            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::TOP)].transponate();
                getCubeSide()[static_cast <int> (Side::TOP)].reverseColumns();
            }

            else if ( getChoice() == rowsCount-1 ){
                getCubeSide()[static_cast <int> (Side::BOTTOM)].transponate();
                getCubeSide()[static_cast <int> (Side::BOTTOM)].reverseColumns();
            }
            break;

        case Mode::LEFT_TO_RIGHT:

            for (int j=0;j<rowsCount;j++){

                //int shift = (subsquares-j-1)%rows;
                int shift = (rows-j-1)%rows;
                int currentChoice = getChoice();
                int shiftCurrentChoice = (rows - 1 -currentChoice)%rows;

                buffer = getCubeSide()[static_cast<int> (Side::FRONT)].getWall()[j][currentChoice];

                Color &lhs1 = cubeSide[static_cast<int> (Side::FRONT)].getWall()[j][currentChoice];
                lhs1 = getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[shift][shiftCurrentChoice];

                Color &lhs2 = cubeSide[static_cast<int> (Side::BOTTOM)].getWall()[shift][shiftCurrentChoice];
                lhs2 = getCubeSide()[static_cast<int> (Side::BACK)].getWall()[shift][shiftCurrentChoice];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BACK)].getWall()[shift][shiftCurrentChoice];
                lhs3 = getCubeSide()[static_cast<int> (Side::TOP)].getWall()[j][currentChoice];

                Color &lhs4 = cubeSide[static_cast<int> (Side::TOP)].getWall()[j][currentChoice];
                lhs4 = buffer;

            }

            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::LEFT)].transponate();
                getCubeSide()[static_cast <int> (Side::LEFT)].reverseColumns();
            }
            else if ( getChoice() == (rowsCount-1)){
                getCubeSide()[static_cast <int> (Side::RIGHT)].transponate();
                getCubeSide()[static_cast <int> (Side::RIGHT)].reverseColumns();
            }

            break;

        case Mode::FRONT_TO_BACK:

            for (int j=0;j<rowsCount;j++){

                int currentChoice = getChoice();
                int shiftCurrentChoice = (rows - 1 -currentChoice)%rows;
                int shift = (rows-j-1)%rows;

                buffer = getCubeSide()[static_cast<int> (Side::TOP)].getWall()[shiftCurrentChoice][j];

                Color &lhs1 = cubeSide[static_cast<int> (Side::TOP)].getWall()[shiftCurrentChoice][j];
                lhs1 = getCubeSide()[static_cast<int> (Side::RIGHT)].getWall()[j][currentChoice];

                Color &lhs2 = cubeSide[static_cast<int> (Side::RIGHT)].getWall()[j][currentChoice];
                lhs2 = getCubeSide()[static_cast<int> (Side::BOTTOM)].getWall()[shiftCurrentChoice][j];

                Color &lhs3 = cubeSide[static_cast<int> (Side::BOTTOM)].getWall()[shiftCurrentChoice][j];
                lhs3 = getCubeSide()[static_cast<int> (Side::LEFT)].getWall()[shift][shiftCurrentChoice];

                Color &lhs4 = cubeSide[static_cast<int> (Side::LEFT)].getWall()[shift][shiftCurrentChoice];
                lhs4 = buffer;

            }

            if ( getChoice() == 0 ){
                getCubeSide()[static_cast <int> (Side::FRONT)].transponate();
                getCubeSide()[static_cast <int> (Side::FRONT)].reverseColumns();
            }
            else if ( getChoice() == (rowsCount-1)){
                getCubeSide()[static_cast <int> (Side::BACK)].transponate();
                getCubeSide()[static_cast <int> (Side::BACK)].reverseColumns();
            }

            break;
        }

}
