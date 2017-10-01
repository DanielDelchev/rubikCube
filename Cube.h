#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "CubeSide.h"
#include <stack>
#include <atomic>

enum class Mode:int{
    TOP_TO_BOTTOM = 0,
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
    NEUTRAL = 0,
    CLOCK_WISE = 1,
    COUNTER_CLOCK_WISE = -1,
};

struct Turn{
    Mode mode;
    int choice;
    Direction dir;
    Turn(Mode _mode, int _choice, Direction _dir):mode(_mode), choice (_choice), dir (_dir){}
};


class Cube{

public:

    static Cube& instance(int _rows = 3, Mode _mode = Mode::TOP_TO_BOTTOM, int _choice = -1, int _length = 5)
    {
        static Cube singleton(_rows, Mode::TOP_TO_BOTTOM, _choice, _length);
        return singleton;
    }

    Cube(const Cube &given) = delete;
    Cube& operator=(const Cube &given) = delete;
    Cube(Cube &&given) = delete;
    Cube& operator=(Cube &&given) = delete;
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



    void draw(float Cx = 0, float Cy = 0, float Cz = 0);
    void turn();
    void print(); //for debugging purposes
    void solve(); //apply all turns in history in reverse direction

    inline int getChoice()const{return choice.load();}
    inline Mode getMode()const{return mode.load();}
    inline void setChoice(int _choice){return choice.store(_choice);}
    inline void setMode(Mode _mode){return mode.store(_mode);}
    inline Direction getDir()const{return dir.load();}
    inline void setDir(Direction _dir){return dir.store(_dir);}
    inline int getLength()const{return length;}

    void choiceIncrease();
    void choiceDecrease();
    void modeIncrease();


    void randomize(int count = 16);

    static const int SIDES_COUNT = 6;

private:

    Cube(int _rows = 3, Mode _mode = Mode::TOP_TO_BOTTOM, int _choice = -1, int _length = 5);

    inline void setLength(int _length){
        length = _length;
        float eps = 0.001;
        if ( (_length-3) < eps || (_length-30) > eps ){
            length = 5;
        }
    }

    void turnClockwise();
    void turnCounterClockwise();
    void drawCube(int turningDegrees, float Cx, float Cy, float Cz)const;

    void destroy();

    std::atomic<Mode> mode; //how the cube will be drawn (segmented for rotation)
    std::atomic<int> choice; //which row of subcubes is currently considered for rotation [0 ; wall_dimention]
    std::atomic<Direction> dir; //which row of subcubes is currently considered for rotation [0 ; wall_dimention]

    int length;
    int rows; // regarding drawing sizes
    CubeSide cubeSide [SIDES_COUNT];
    std::stack<Turn> history;


    //TODO
    //calculate all these in the constructor
    // replace Cx,Cy,Cz everywhere with a Point object
    //figure out how to rotate around all 3 axes
    //vector<Point> top_to_bottom_box_centres
    //vector<Point> top_to_bottom_subCubes_centres

    //vector<Point> left_to_right_box_centres
    //vector<Point> left_to_right_subCubes_centres

    //vector<Point> front_to_back_box_centres
    //vector<Point> front_to_back_subCubes_centres

    //vector<vector<points>> cubeSideTilesCentres;

};

#endif // CUBE_H_INCLUDED
