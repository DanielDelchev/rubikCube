#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "CubeSide.h"
#include <stack>
#include <atomic>

enum class Mode:int{
    BOTTOM_TO_TOP = 0,
    LEFT_TO_RIGHT = 1,
    FRONT_TO_BACK = 2,

};

enum class Side:int{
    BOTTOM = 0,
    TOP = 1,
    LEFT = 2,
    RIGHT = 3,
    FRONT = 4,
    BACK = 5,
};

enum class Direction:int{
    CLOCK_WISE = 0,
    COUNTER_CLOCK_WISE = 1,
};

struct Turn{
    Mode mode;
    int choice;
    Direction dir;
    Turn(Mode _mode, int _choice, Direction _dir):mode(_mode), choice (_choice), dir (_dir){}
};


class Cube{

public:


    Cube(int _rows = 3, Mode _mode = Mode::BOTTOM_TO_TOP, int _choice = -1);
    Cube(const Cube &given);
    Cube& operator=(const Cube &given);

    Cube(Cube &&given) = default;
    Cube& operator=(Cube &&given) = default ;

    virtual ~Cube();

    inline int getRows()const{return rows;}

    inline bool getState()const{ //true if all sides are solved
        bool solved = true;
        for (int i=0;i<SIDES_COUNT;i++){
            solved = solved && cubeSide[i].getState();
        }
        return solved;
    }


    inline const CubeSide * getCubeSide()const{return cubeSide;}
    inline CubeSide *getCubeSide(){return cubeSide;}
    inline const std::stack<Turn>& getHistory()const{return history;}
    inline std::stack<Turn>& getHistory(){return history;}


    bool operator== (const Cube &given)const;

    void draw(int length,float Cx = 0, float Cy = 0, float Cz = 0);
    void turn(Direction dir);
    void print(); //for debugging purposes
    void solve(); //apply all turns in history in reverse direction

    int getChoice()const{return choice.load();}
    Mode getMode()const{return mode.load();}
    void setChoice(int _choice){return choice.store(_choice);}
    void setMode(Mode _mode){return mode.store(_mode);}


    void randomize(int count = 16);

private:

    void turnClockwise();
    void turnCounterClockwise();

    void copy(const Cube& given);
    void destroy();

    std::atomic<Mode> mode; //how the cube will be drawn (segmented for rotation)
    std::atomic<int> choice; //which row of subcubes is currently considered for rotation [0 ; wall_dimention]

    static const int SIDES_COUNT = 6;
    int rows; // regarding drawing sizes
    CubeSide cubeSide [SIDES_COUNT];
    std::stack<Turn> history;
};

#endif // CUBE_H_INCLUDED
