#ifndef CUBESIDE_H_INCLUDED
#define CUBESIDE_H_INCLUDED


enum class Color:int{
    RED = 0,
    BLUE = 1,
    GREEN = 2,
    YELLOW = 3,
    WHITE = 4,
    ORANGE = 5,
    BLACK = 6, //unit test purposes
    GREY = 7, //unit test purposes
};

class CubeSide{

public:
    CubeSide(int dim = 3, Color clr = Color::ORANGE); //constructor
    CubeSide(const CubeSide &given); //copy constructor
    CubeSide(CubeSide &&given); //move constructor
    CubeSide& operator=(const CubeSide &given); //assignment
    CubeSide& operator=(CubeSide &&given); //move assignment
    virtual ~CubeSide();

    bool operator == (const CubeSide &given)const;

    inline int getDimention()const{return dimention;}
    inline bool getState()const{return solved;}
    inline Color **getWall()const{return wall;}
    inline Color **getWall(){return wall;}

    inline void setDimention(int dmn){dimention = dmn;} //questionable whether to leave this public , decide later
    inline void setSolved(bool slv){solved = slv;}

    void print(); //for debugging purposes
    void paint(Color clr);

private:
    void copy(const CubeSide &given);
    void destroy();

    int dimention;
    bool solved;
    Color **wall = nullptr;
};


#endif // CUBESIDE_H_INCLUDED
