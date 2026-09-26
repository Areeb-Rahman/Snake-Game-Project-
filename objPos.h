#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct
{
    int x;
    int y;
} Pos;

class objPos
{
public:
    Pos *pos;
    char symbol;

    objPos();                             // default contstructor
    objPos(int xPos, int yPos, char sym); // additional constructor

    // additional member functions

    ~objPos();                                 // deconstructor
    objPos(const objPos &original);            // copy
    objPos &operator=(const objPos &original); // copy assignment

    // Respect the rule of six / minimum four
    // [TODO] Implement the missing special member functions to meet the minimum four rule

    void setObjPos(const objPos &o);
    void setObjPos(int xPos, int yPos, char sym);

    objPos getObjPos() const;
    char getSymbol() const;
    char getSymbolIfPosEqual(const objPos *refPos) const;

    bool isPosEqual(const objPos *refPos) const;
};

#endif