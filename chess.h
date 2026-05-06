#pragma once
#ifndef chess_H
#define chess_H

class chess
{
private:
	char chessBoard[8][8];

public:
	void initialize();
	void display();
};

#endif