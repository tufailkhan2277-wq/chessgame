#include "chess.h"

int main() {

	Board board;

	setupBoard(board);

	Color turn = WHITE;

	string a, b;

	while (true) {

		board.draw();

		if (turn == WHITE) {
			cout << "\nWhite move: ";
		}
		else {
			cout << "\nBlack move: ";
		}

		cin >> a;

		if (a == "quit") {
			break;
		}

		cin >> b;

		Position f = parse(a);
		Position t = parse(b);

		Piece *p = board.get(f);

		if (p == nullptr) {
			cout << "Invalid move" << endl;
			continue;
		}

		if (p->getColor() != turn) {
			cout << "Wrong turn" << endl;
			continue;
		}

		if (!p->canMove(f, t, board)) {
			cout << "Invalid move" << endl;
			continue;
		}

		board.move(f, t);

		if (turn == WHITE) {
			turn = BLACK;
		}
		else {
			turn = WHITE;
		}
	}

	return 0;
}
