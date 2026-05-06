#include <iostream>
#include "chess.h"

using namespace std;

void chess::initialize()
{
	// this is for empty spaces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chessBoard[i][j] = '.';
		}
	}

	// this is for black pieces
	chessBoard[0][0] = 'R';
	chessBoard[0][1] = 'N';
	chessBoard[0][2] = 'B';
	chessBoard[0][3] = 'Q';
	chessBoard[0][4] = 'K';
	chessBoard[0][5] = 'B';
	chessBoard[0][6] = 'N';
	chessBoard[0][7] = 'R';

	for (int i = 0; i < 8; i++)
	{
		chessBoard[1][i] = 'P';
	}

	// this is for white pieces
	chessBoard[7][0] = 'r';
	chessBoard[7][1] = 'n';
	chessBoard[7][2] = 'b';
	chessBoard[7][3] = 'q';
	chessBoard[7][4] = 'k';
	chessBoard[7][5] = 'b';
	chessBoard[7][6] = 'n';
	chessBoard[7][7] = 'r';

	for (int i = 0; i < 8; i++)
	{
		chessBoard[6][i] = 'p';
	}
}

void chess::display()
{
	cout << "\nChess Board:\n" << endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << chessBoard[i][j] << " ";
		}

		cout << endl;
	}
}