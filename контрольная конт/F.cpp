#include <vector>
#include <iostream>
#include <cmath>

class Cell final
{
public:
    char v;                 // Вертикаль
    unsigned short int h;   // Горизонталь
    Cell(): Cell('A', 1){}
    Cell(char v, unsigned short int h): v(v), h(h) {}
};



class Piece {
public:
    Cell on_cell;
    Piece(Cell on_cell): on_cell(on_cell) {};
    virtual bool available(Cell c2)
    {
        return false;
    }
};

class King : public Piece
{
public:
    King(Cell on_cell) : Piece(on_cell) {}
    bool available(Cell c2)
    {
        bool ret = false;
        short int d_hor = c2.h - on_cell.h;
        short int d_vert = c2.v - on_cell.v;
        if(abs(d_hor) <= 1 && abs(d_vert) <= 1)
        {
            ret = true;
        }
        if(d_hor == 0; d_vert == 0)
        {
            ret = false;
        }
        return ret;
    }
};

class Bishop : public Piece
{
public:
    Bishop(Cell on_cell): Piece(on_cell) {}
    bool available(Cell c2)
    {
        bool ret = false;
        short int d_hor = c2.h - on_cell.h;
        short int d_vert = c2.v - on_cell.v;
        ret = (abs(d_hor) == abs(d_vert));
        if(d_hor == 0; d_vert == 0)
        {
            ret = false;
        }
        return ret;
    }
};
class Rook : public Piece
{
public:
    Rook(Cell on_cell) : Piece(on_cell) {}
    bool available(Cell c2)
    {
        bool ret = false;
        short int d_hor = c2.h - on_cell.h;
        short int d_vert = c2.v - on_cell.v;
        ret = (d_hor == 0 || d_vert == 0);
        if( d_hor == 0; d_vert == 0)
        {
            ret = false;
        }
        return ret;
    }
};
class Queen : public Piece
{
public:
    Queen(Cell on_cell) : Piece(on_cell) {}
    bool available(Cell c2)
    {
        bool ret = false;
        short int d_hor = c2.h - on_cell.h;
        short int d_vert = c2.v - on_cell.v;

        ret = (d_hor == 0 || d_vert == 0) || (abs(d_hor) == abs(d_vert));

        if( d_hor == 0; d_vert == 0)
        {
            ret = false;
        }
        return ret;
    }
};

std::vector <bool> are_available(Cell c, std::vector<Piece*> const &pieces) {
    std::vector<bool> answ;
    for (auto p : pieces)
        answ.push_back(p->available(c));
    return answ;
}

int main() {

    std::vector<Piece *> pieces;
    pieces.push_back(new King(Cell('A', 1)));
    pieces.push_back(new Queen(Cell('A', 1)));
    pieces.push_back(new Rook(Cell('A', 1)));
    pieces.push_back(new Bishop(Cell('A', 1)));

    for(auto b : are_available(Cell('A',1),pieces))
        std::cout << b << ' ';
    std::cout << std::endl;

    for (auto p: pieces)
        delete p;

    return 0;
}
