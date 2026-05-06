#include "chess.h"

Position::Position(int r, int c) {
	this->r = r;
	this->c = c;
}

Piece::Piece(Color c) {
	color = c;
}

Piece::~Piece() {}

Color Piece::getColor() {
	return color;
}

Board::Board() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			grid[r][c] = nullptr;
		}
	}
}

Board::~Board() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			delete grid[r][c];
		}
	}
}

Piece *Board::get(Position p) {
	if (p.r < 0 || p.r > 7 || p.c < 0 || p.c > 7) {
		return nullptr;
	}

	return grid[p.r][p.c];
}

void Board::set(Position p, Piece *pc) {
	grid[p.r][p.c] = pc;
}

void Board::move(Position f, Position t) {
	if (grid[t.r][t.c] != nullptr) {
		delete grid[t.r][t.c];
	}

	grid[t.r][t.c] = grid[f.r][f.c];
	grid[f.r][f.c] = nullptr;
}

void Board::draw() {
	cout << endl << "  a b c d e f g h" << endl;

	for (int r = 0; r < 8; r++) {
		cout << 8 - r << " ";

		for (int c = 0; c < 8; c++) {
			if (grid[r][c] != nullptr) {
				cout << grid[r][c]->symbol() << " ";
			}
			else {
				cout << ". ";
			}
		}

		cout << 8 - r << endl;
	}

	cout << "  a b c d e f g h" << endl;
}

int absVal(int x) {
	if (x < 0) {
		return -x;
	}

	return x;
}

Position parse(string s) {
	int r = 8 - (s[1] - '0');
	int c = s[0] - 'a';

	return Position(r, c);
}

string toNotation(Position p) {
	string s = "";

	s += char('a' + p.c);
	s += char('0' + (8 - p.r));

	return s;
}

void setupBoard(Board &board) {
	// pieces will be added in next commits
}
