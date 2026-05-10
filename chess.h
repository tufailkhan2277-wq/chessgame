#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <string>
using namespace std;
enum Color { WHITE, BLACK };
struct Position {
	int r, c;
	Position(int r = 0, int c = 0);
};
class Board;
class Piece {
protected:
	Color color;
public:
	Piece(Color c);
	virtual ~Piece();
	Color getColor();
	virtual char symbol() = 0;
	virtual bool canMove(Position, Position, Board &) = 0;
};
class Board {
public:
	Piece *grid[8][8];
	Board();
	~Board();
	Piece *get(Position p);
	bool isEmpty(Position p);
	bool isEnemy(Position p, Color c);
	void set(Position p, Piece *pc);
	void move(Position f, Position t);
	void draw();
};
int absVal(int x);
bool isInside(Position p);
bool isValidNotation(string s);
class Pawn : public Piece { public: Pawn(Color c); char symbol(); bool canMove(Position, Position, Board &); };
class Rook : public Piece { public: Rook(Color c); char symbol(); bool canMove(Position, Position, Board &); };
class Knight : public Piece { public: Knight(Color c); char symbol(); bool canMove(Position, Position, Board &); };
class Bishop : public Piece { public: Bishop(Color c); char symbol(); bool canMove(Position, Position, Board &); };
class Queen : public Piece { public: Queen(Color c); char symbol(); bool canMove(Position, Position, Board &); };
class King : public Piece { public: King(Color c); char symbol(); bool canMove(Position, Position, Board &); };
Position parse(string s);
string toNotation(Position p);
void setupBoard(Board &board);
#endif
