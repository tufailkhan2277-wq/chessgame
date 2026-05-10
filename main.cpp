#include "chess.h"

void printCommands() {
	cout << endl << "Commands:" << endl;
	cout << "  e2 e4     : move" << endl;
	cout << "  moves e2  : show moves" << endl;
	cout << "  quit      : exit" << endl;
	cout << "  help      : commands" << endl << endl;
}

void printLegalMoves(Board &board, Position f) {
	Piece *p = board.get(f);
	cout << "Legal moves for " << p->symbol() << " at " << toNotation(f) << ": ";
	bool found = false;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Position t(r, c);
			if (p->canMove(f, t, board)) {
				cout << toNotation(t) << " ";
				found = true;
			}
		}
	}
	if (!found) cout << "(none)";
	cout << endl;
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
		if (a == "quit") break;
		if (a == "help") {
			printCommands();
			continue;
		}
		if (a == "moves") {
			cin >> b;
			Position f = parse(b);
			Piece *p = board.get(f);
			if (p != nullptr) printLegalMoves(board, f);
			continue;
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
		turn = (turn == WHITE) ? BLACK : WHITE;
	}
	return 0;
}
