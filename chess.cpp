#include "chess.h"

Position::Position(int r, int c) { this->r = r; this->c = c; }
Piece::Piece(Color c) { color = c; }
Piece::~Piece() {}
Color Piece::getColor() { return color; }

Board::Board() { for (int r = 0; r < 8; r++) for (int c = 0; c < 8; c++) grid[r][c] = nullptr; }
Board::~Board() { clear(); }
void Board::clear() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			delete grid[r][c];
			grid[r][c] = nullptr;
		}
	}
}

Piece *Board::get(Position p) { if (!isInside(p)) return nullptr; return grid[p.r][p.c]; }
bool Board::isEmpty(Position p) { return get(p) == nullptr; }
bool Board::isEnemy(Position p, Color c) {
	Piece *pc = get(p);
	return (pc != nullptr && pc->getColor() != c);
}

void Board::set(Position p, Piece *pc) { grid[p.r][p.c] = pc; }
void Board::move(Position f, Position t) {
	if (grid[t.r][t.c] != nullptr) delete grid[t.r][t.c];
	grid[t.r][t.c] = grid[f.r][f.c];
	grid[f.r][f.c] = nullptr;
}

void Board::draw() {
	cout << endl << "\t";
	for (char col = 'a'; col <= 'h'; col++) cout << col << "\t";
	cout << endl << endl;
	for (int r = 0; r < 8; r++) {
		cout << 8 - r << "\t";
		for (int c = 0; c < 8; c++) {
			if (grid[r][c] != nullptr) cout << grid[r][c]->symbol() << "\t";
			else cout << ".\t";
		}
		cout << 8 - r << endl << endl;
	}
	cout << "\t";
	for (char col = 'a'; col <= 'h'; col++) cout << col << "\t";
	cout << endl;
}

int absVal(int x) { return (x < 0) ? -x : x; }
bool isInside(Position p) { return (p.r >= 0 && p.r < 8 && p.c >= 0 && p.c < 8); }
bool isValidNotation(string s) {
	if (s.length() != 2) return false;
	return (s[0] >= 'a' && s[0] <= 'h' && s[1] >= '1' && s[1] <= '8');
}

Position parse(string s) {
	if (!isValidNotation(s)) return Position(-1, -1);
	return Position(8 - (s[1] - '0'), s[0] - 'a');
}

string toNotation(Position p) {
	string s = "";
	s += char('a' + p.c);
	s += char('0' + (8 - p.r));
	return s;
}

string colorName(Color c) {
	return (c == WHITE) ? "White" : "Black";
}

string pieceName(Piece *p) {
	if (p == nullptr) return "Empty";
	char s = p->symbol();
	string name;
	if (s == 'P' || s == 'p') name = "Pawn";
	else if (s == 'R' || s == 'r') name = "Rook";
	else if (s == 'N' || s == 'n') name = "Knight";
	else if (s == 'B' || s == 'b') name = "Bishop";
	else if (s == 'Q' || s == 'q') name = "Queen";
	else if (s == 'K' || s == 'k') name = "King";
	else name = "Piece";
	return colorName(p->getColor()) + " " + name;
}

// ... Piece movement classes implementation yahan aayegi ...

void setupBoard(Board &board) {
	for (int i = 0; i < 8; i++) {
		board.set(Position(6, i), new Pawn(WHITE));
		board.set(Position(1, i), new Pawn(BLACK));
	}
	board.set(Position(7, 0), new Rook(WHITE)); board.set(Position(7, 7), new Rook(WHITE));
	board.set(Position(0, 0), new Rook(BLACK)); board.set(Position(0, 7), new Rook(BLACK));
	board.set(Position(7, 1), new Knight(WHITE)); board.set(Position(7, 6), new Knight(WHITE));
	board.set(Position(0, 1), new Knight(BLACK)); board.set(Position(0, 6), new Knight(BLACK));
	board.set(Position(7, 2), new Bishop(WHITE)); board.set(Position(7, 5), new Bishop(WHITE));
	board.set(Position(0, 2), new Bishop(BLACK)); board.set(Position(0, 5), new Bishop(BLACK));
	board.set(Position(7, 3), new Queen(WHITE)); board.set(Position(0, 3), new Queen(BLACK));
	board.set(Position(7, 4), new King(WHITE)); board.set(Position(0, 4), new King(BLACK));
}
