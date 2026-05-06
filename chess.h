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
	void set(Position p, Piece *pc);
	void move(Position f, Position t);
	void draw();
};

int absVal(int x);
class Pawn : public Piece {
public:
	Pawn(Color c);

	char symbol();

	bool canMove(Position f, Position t, Board &b);
};
class Rook : public Piece {
public:
	Rook(Color c);

	char symbol();

	bool canMove(Position f, Position t, Board &b);
};
class Knight : public Piece {
public:
	Knight(Color c);

	char symbol();

	bool canMove(Position f, Position t, Board &b);
};
class Bishop : public Piece {
public:
	Bishop(Color c);

	char symbol();

	bool canMove(Position f, Position t, Board &b);
};

Position parse(string s);
string toNotation(Position p);
void setupBoard(Board &board);

#endif
