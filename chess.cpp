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
}Piece *Board::get(Position p) { if (!isInside(p)) return nullptr; return grid[p.r][p.c]; }
bool Board::isEmpty(Position p) { return get(p) == nullptr; }
bool Board::isEnemy(Position p, Color c) {
	Piece *pc = get(p);
	if (pc != nullptr && pc->getColor() != c) return true;
	return false;
}
void Board::set(Position p, Piece *pc) { grid[p.r][p.c] = pc; }
void Board::move(Position f, Position t) { if (grid[t.r][t.c] != nullptr) delete grid[t.r][t.c]; grid[t.r][t.c] = grid[f.r][f.c]; grid[f.r][f.c] = nullptr; }
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
	if (s[0] < 'a' || s[0] > 'h') return false;
	if (s[1] < '1' || s[1] > '8') return false;
	return true;
}
Position parse(string s) {
	if (!isValidNotation(s)) return Position(-1, -1);
	int r = 8 - (s[1] - '0');
	int c = s[0] - 'a';
	return Position(r, c);
}
Pawn::Pawn(Color c) : Piece(c) {}
char Pawn::symbol() { return (color == WHITE) ? 'P' : 'p'; }
bool Pawn::canMove(Position f, Position t, Board &b) {
	int d = (color == WHITE) ? -1 : 1;
	if (f.c == t.c && b.isEmpty(t) && t.r == f.r + d) return true;
	if (f.c == t.c && b.isEmpty(t)) {
		if (color == WHITE && f.r == 6 && t.r == 4 && b.isEmpty(Position(5, f.c))) return true;
		if (color == BLACK && f.r == 1 && t.r == 3 && b.isEmpty(Position(2, f.c))) return true;
	}
	if (absVal(f.c - t.c) == 1 && t.r == f.r + d && b.isEnemy(t, color)) return true;
	return false;
}
Rook::Rook(Color c) : Piece(c) {}
char Rook::symbol() { return (color == WHITE) ? 'R' : 'r'; }
bool Rook::canMove(Position f, Position t, Board &b) {
	if (f.r != t.r && f.c != t.c) return false;
	int dr = (t.r > f.r) ? 1 : (t.r < f.r ? -1 : 0);
	int dc = (t.c > f.c) ? 1 : (t.c < f.c ? -1 : 0);
	Position p(f.r + dr, f.c + dc);
	while (p.r != t.r || p.c != t.c) {
		if (!b.isEmpty(p)) return false;
		p.r += dr; p.c += dc;
	}
	return (b.isEmpty(t) || b.isEnemy(t, color));
}
Knight::Knight(Color c) : Piece(c) {}
char Knight::symbol() { return (color == WHITE) ? 'N' : 'n'; }
bool Knight::canMove(Position f, Position t, Board &b) {
	int dr = absVal(f.r - t.r);
	int dc = absVal(f.c - t.c);
	if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) return false;
	return (b.isEmpty(t) || b.isEnemy(t, color));
}
Bishop::Bishop(Color c) : Piece(c) {}
char Bishop::symbol() { return (color == WHITE) ? 'B' : 'b'; }
bool Bishop::canMove(Position f, Position t, Board &b) {
	if (absVal(f.r - t.r) != absVal(f.c - t.c)) return false;
	int dr = (t.r > f.r) ? 1 : -1;
	int dc = (t.c > f.c) ? 1 : -1;
	Position p(f.r + dr, f.c + dc);
	while (p.r != t.r) {
		if (!b.isEmpty(p)) return false;
		p.r += dr; p.c += dc;
	}
	return (b.isEmpty(t) || b.isEnemy(t, color));
}
Queen::Queen(Color c) : Piece(c) {}
char Queen::symbol() { return (color == WHITE) ? 'Q' : 'q'; }
bool Queen::canMove(Position f, Position t, Board &b) {
	Rook r(color); Bishop bp(color);
	return (r.canMove(f, t, b) || bp.canMove(f, t, b));
}
King::King(Color c) : Piece(c) {}
char King::symbol() { return (color == WHITE) ? 'K' : 'k'; }
bool King::canMove(Position f, Position t, Board &b) {
	if (absVal(f.r - t.r) <= 1 && absVal(f.c - t.c) <= 1) return (b.isEmpty(t) || b.isEnemy(t, color));
	return false;
}
string toNotation(Position p) { string s = ""; s += char('a' + p.c); s += char('0' + (8 - p.r)); return s; }
void setupBoard(Board &board) {
	for (int i = 0; i < 8; i++) { board.set(Position(6, i), new Pawn(WHITE)); board.set(Position(1, i), new Pawn(BLACK)); }
	board.set(Position(7, 0), new Rook(WHITE)); board.set(Position(7, 7), new Rook(WHITE));
	board.set(Position(0, 0), new Rook(BLACK)); board.set(Position(0, 7), new Rook(BLACK));
	board.set(Position(7, 1), new Knight(WHITE)); board.set(Position(7, 6), new Knight(WHITE));
	board.set(Position(0, 1), new Knight(BLACK)); board.set(Position(0, 6), new Knight(BLACK));
	board.set(Position(7, 2), new Bishop(WHITE)); board.set(Position(7, 5), new Bishop(WHITE));
	board.set(Position(0, 2), new Bishop(BLACK)); board.set(Position(0, 5), new Bishop(BLACK));
	board.set(Position(7, 3), new Queen(WHITE)); board.set(Position(0, 3), new Queen(BLACK));
	board.set(Position(7, 4), new King(WHITE)); board.set(Position(0, 4), new King(BLACK));
}
