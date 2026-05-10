#include "chess.h"

void printCommands() {
	cout << endl << "Commands:" << endl;
	cout << "  e2 e4     : move" << endl;
	cout << "  moves e2  : show moves" << endl;
	cout << "  quit      : exit" << endl;
	cout << "  help      : commands" << endl << endl;
}

void printTurn(Color turn) {
	if (turn == WHITE) {
		cout << "White move: ";
	}
	else {
		cout << "Black move: ";
	}
}

int main() {

	Board board;

	setupBoard(board);

	Color turn = WHITE;

	string a, b;

	while (true) {

		board.draw();

		printCommands();

		printTurn(turn);
		
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
