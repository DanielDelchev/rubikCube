#include "CubeSide.h"
#include <string.h>
#include <iostream>

void CubeSide::paint(Color clr){
    int dim  = getDimention();
    for (int i=0; i<dim;i++){
        for (int j=0;j<dim;j++){
            getWall()[i][j] = clr;
        }
    }
}

void CubeSide::destroy(){
    int dim = getDimention();
    for (int i=0;i<dim;i++){
        delete [] getWall()[i];
    }
    delete [] getWall();
}

void CubeSide::copy(const CubeSide &given){
    this->solved = given.getState();
    this->dimention = given.getDimention();
    int dim  = getDimention();
    this->wall = new Color *[dim];
    for (int i=0; i<dim;i++){
        getWall()[i] = new Color[dim];
        memcpy(getWall()[i],given.getWall()[i],dim*sizeof(Color));
    }
}

CubeSide::CubeSide(int dim,Color clr):dimention(dim),solved(true),wall(nullptr){
    wall = new Color *[dimention];
    for (int i=0; i<dimention;i++){
        wall[i] = new Color[dimention];
    }
    paint(clr);
}

CubeSide::~CubeSide(){
    destroy();
}

CubeSide::CubeSide(const CubeSide &given){
    copy(given);
}

CubeSide& CubeSide::operator=(const CubeSide &given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

CubeSide::CubeSide(CubeSide &&given):dimention(given.getDimention()),solved(given.getState()),wall(nullptr){
    this->wall = given.getWall();
    given.wall = nullptr;
    given.dimention = 0;
}

CubeSide& CubeSide::operator= (CubeSide &&given){
    if (this!=&given){
        destroy();
        this->wall = given.getWall();
        this->solved = given.getState();
        this->dimention = given.getDimention();
        given.wall = nullptr;
        given.dimention = 0;
    }
    return *this;
}

/////////////////////////////////////////////////////////////////
void CubeSide::print(){
    int dim = getDimention();
    for (int i=0; i<dim;i++){
        for (int j=0;j<dim;j++){
            Color clr = getWall()[i][j];
            std::string cur = "";
            switch(clr){
                case Color::WHITE: cur+="WHITE"; break;
                case Color::RED: cur+="RED"; break;
                case Color::BLUE: cur+="BLUE"; break;
                case Color::ORANGE: cur+="ORANGE"; break;
                case Color::GREEN: cur+="GREEN"; break;
                case Color::YELLOW: cur+="YELLOW"; break;
                case Color::BLACK: cur+="BLACK"; break;
                case Color::GREY: cur+="GREY"; break;
            }
            std::cout<<cur<<" ";
        }
        std::cout<<std::endl;
    }
}

bool CubeSide::operator==(const CubeSide &given)const{
    bool result = true;
    int dim = getDimention();
    for (int i=0;i<dim;i++){
        for (int j=0;j<dim;j++){
            result = result && getWall()[i][j] == given.getWall()[i][j];
        }
    }

    return result;
}

// designed for square matrices only!
void CubeSide::transponate(){
    int dim = getDimention();
    for (int row=0;row<dim;row++){
        for (int column=0;column<dim;column++){
            if (column < row){
                continue;
            }
            std::swap(getWall()[row][column],getWall()[column][row]);
        }
    }

}

void CubeSide::reverseColumns(){
    int dim = getDimention();
    for (int column=0;column<dim;column++){
        int half = dim/2;
        for (int row=0;row<half;row++){
            std::swap(getWall()[row][column],getWall()[dim-1-row][column]);
        }
    }
}

void CubeSide::reverseRows(){
    int dim = getDimention();
    for (int row=0;row<dim;row++){
        int half = dim/2;
        for (int column=0;column<half;column++){
            std::swap(getWall()[row][column],getWall()[row][dim-1-column]);
        }
    }
}
