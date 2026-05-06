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
Pawn::Pawn(Color c) : Piece(c) {}

char Pawn::symbol() {
	if (color == WHITE) {
		return 'P';
	}

	return 'p';
}

bool Pawn::canMove(Position f, Position t, Board &b) {
	int d;

	if (color == WHITE) {
		d = -1;
	}
	else {
		d = 1;
	}

	if (f.c == t.c && b.get(t) == nullptr && t.r == f.r + d) {
		return true;
	}

	if (f.c == t.c && b.get(t) == nullptr) {
		if (color == WHITE) {
			if (f.r == 6 && t.r == 4 && b.get(Position(5, f.c)) == nullptr) {
				return true;
			}
		}
		else {
			if (f.r == 1 && t.r == 3 && b.get(Position(2, f.c)) == nullptr) {
				return true;
			}
		}
	}

	if (absVal(f.c - t.c) == 1 && t.r == f.r + d) {
		Piece *p = b.get(t);

		if (p != nullptr && p->getColor() != color) {
			return true;
		}
	}

	return false;
}
Rook::Rook(Color c) : Piece(c) {}

char Rook::symbol() {
	if (color == WHITE) {
		return 'R';
	}

	return 'r';
}

bool Rook::canMove(Position f, Position t, Board &b) {
	if (f.r != t.r && f.c != t.c) {
		return false;
	}

	int dr = 0;
	int dc = 0;

	if (t.r > f.r) dr = 1;
	else if (t.r < f.r) dr = -1;

	if (t.c > f.c) dc = 1;
	else if (t.c < f.c) dc = -1;

	Position p(f.r + dr, f.c + dc);

	while (p.r != t.r || p.c != t.c) {
		if (b.get(p) != nullptr) {
			return false;
		}

		p.r += dr;
		p.c += dc;
	}

	Piece *q = b.get(t);

	if (q == nullptr || q->getColor() != color) {
		return true;
	}

	return false;
}
Knight::Knight(Color c) : Piece(c) {}

char Knight::symbol() {
	if (color == WHITE) {
		return 'N';
	}

	return 'n';
}

bool Knight::canMove(Position f, Position t, Board &b) {

	int dr = absVal(f.r - t.r);
	int dc = absVal(f.c - t.c);

	if (!((dr == 2 && dc == 1) ||
		(dr == 1 && dc == 2))) {

		return false;
	}

	Piece *p = b.get(t);

	if (p == nullptr ||
		p->getColor() != color) {

		return true;
	}

	return false;
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
		for (int i = 0; i < 8; i++) {
			board.set(Position(6, i), new Pawn(WHITE));
			board.set(Position(1, i), new Pawn(BLACK));
		}

		board.set(Position(7, 0), new Rook(WHITE));
		board.set(Position(7, 7), new Rook(WHITE));
		board.set(Position(0, 0), new Rook(BLACK));
		board.set(Position(0, 7), new Rook(BLACK));
		board.set(Position(7, 1), new Knight(WHITE));
		board.set(Position(7, 6), new Knight(WHITE));

		board.set(Position(0, 1), new Knight(BLACK));
		board.set(Position(0, 6), new Knight(BLACK));
	}
