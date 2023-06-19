// a tic tac toe example with a s pattern scoreboard from github  https://github.com/dongwoo1005/Tic-Tac-Toe author dongwoo1005
// note, this is not all of the project, just the main and singleton files, so won't compile

#include "scoreboard.h"
#include "player.h"
#include "textdisplay.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

//#include "player.h"
//#include "textdisplay.h"

class Player;	// Forward declaration
class TextDisplay;

class ScoreBoard {
	int scoreX, scoreO;		// to count the scores
	std::string inputX, inputO; // to save the inputs (stdin or *.txt)
	int NW, N, NE, W, C, E, SW, S, SE; // to track the game board
	int round; // to count how many game was called
	TextDisplay* td;
	static ScoreBoard* instance;	// THE board
	ScoreBoard();	// ctor
	/* cleanup()
	 * Purpose: to delete the created object by getInstance() at the program termination
	 * Returns: None
	 */
	static void cleanup();

public:
	/* getInstance()
	 * Purpose: to ensure that only one ScoreBoard object is created
	 *			creates a ScoreBoard if it was never called.
	 * Returns: pointer to the ScoreBoard created or previously created.
	 */
	static ScoreBoard* getInstance();

	/* printScores()
	 * Purpose: to print out the current scores in the scoreboard
	 *			in the format of
	 *			Score is
	 *			X scoreX
	 *			O scoreO
	 * Returns: None
	 */
	void printScores();

	/* makeMove(p, move)
	 * Purpose: to register the move to the scoreboard of the Player p
	 * Returns: None
	 */
	void makeMove(Player* p, std::string move);

	/* startGame()
	 * Purpose: to restart the game
	 * 			it resets the board move values to 0, count the round up,
	 *			and receives new input from cin
	 * Returns: None
	 */
	void startGame();

	/* isOver()
	 * Purpose: to determine if the game is over according to the rule
	 *			and print out which player has won the game
	 * Returns: true if the game is over
	 * 			false otherwise
	 */
	bool isOver();

	/* isOccupied(move)
	 * Purpose: to determine if the move is already occupied in the board
	 * Returns: true if it is occupied
	 * 			false otherwise
	 */
	bool isOccupied(std::string move);

	/* getInputX()	and	   getInputO()
	 * Purpose: to return the value of inputX or inputO in the board
	 * Returns: the string value of inputX or inputO according to the functions called
	 */
	std::string getInputX();
	std::string getInputO();

	/* getRound()
	 * Purpose: to return the value of round in the board
	 * Returns: current round in integer
	 */
	int getRound();
};

#endif

//#include "scoreboard.h"
//#include "player.h"
//#include "textdisplay.h"


ScoreBoard* ScoreBoard::instance = 0;

ScoreBoard* ScoreBoard::getInstance() {
	if (!instance) {
		instance = new ScoreBoard;
		atexit(cleanup);
	} // end if
	return instance;
}

ScoreBoard::ScoreBoard() : scoreX(0), scoreO(0), inputX(""), inputO(""),
NW(0), N(0), NE(0), W(0), C(0), E(0), SW(0), S(0), SE(0), round(0) {
	td = new TextDisplay;
}

void ScoreBoard::printScores() {
	cout << "Score is" << endl;
	cout << "X " << scoreX << endl;
	cout << "O " << scoreO << endl;
}

void ScoreBoard::cleanup() {
	delete instance;
}


void ScoreBoard::startGame() {
	cin >> inputX;
	cin >> inputO;
	NW = N = NE = W = C = E = SW = S = SE = 0;
	round++;
	delete td;
	td = new TextDisplay;
	cout << *td;
}

void ScoreBoard::makeMove(Player* p, string move) {
	int marker = 0;
	if (p->isPlayerX()) { marker = 1; }
	else if (p->isPlayerO()) { marker = 2; }
	if (move == "NW" && !NW) { NW = marker; }
	else if (move == "N" && !N) { N = marker; }
	else if (move == "NE" && !NE) { NE = marker; }
	else if (move == "W" && !W) { W = marker; }
	else if (move == "C" && !C) { C = marker; }
	else if (move == "E" && !E) { E = marker; }
	else if (move == "SW" && !SW) { SW = marker; }
	else if (move == "S" && !S) { S = marker; }
	else if (move == "SE" && !SE) { SE = marker; }
	td->notify(move, marker);
	cout << *td;
}

bool ScoreBoard::isOver() {
	bool over = false;
	int winner = 0;
	if (((NW == N) && (N == NE)) && (N != 0)) { over = true; winner = N; }
	else if (((W == C) && (C == E)) && (C != 0)) { over = true; winner = C; }
	else if (((SW == S) && (S == SE)) && (S != 0)) { over = true; winner = S; }
	else if (((NW == W) && (W == SW)) && (W != 0)) { over = true; winner = W; }
	else if (((N == C) && (C == S)) && (C != 0)) { over = true; winner = C; }
	else if (((NE == E) && (E == SE)) && (E != 0)) { over = true; winner = E; }
	else if (((NW == C) && (C == SE)) && (C != 0)) { over = true; winner = C; }
	else if (((NE == C) && (C == SW)) && (C != 0)) { over = true; winner = C; }
	else if (((((NW != 0) && (N != 0)) && ((NE != 0) && (W != 0)))
		&& (((C != 0) && (E != 0)) && ((SW != 0) && (S != 0)))) && (SE != 0)) {
		over = true;
	}
	if (over) {
		if (winner == 0) {
			cout << "Draw" << endl;
		} // end if
		if (winner == 1) {
			cout << "X wins" << endl;
			scoreX++;
		} // end if
		if (winner == 2) {
			cout << "O wins" << endl;
			scoreO++;
		} // end if
		return true;
	}
	else {
		return false;
	} // end if and else
}

bool ScoreBoard::isOccupied(string move) {
	if (move == "NW") { return NW ? true : false; }
	else if (move == "N") { return N ? true : false; }
	else if (move == "NE") { return NE ? true : false; }
	else if (move == "W") { return W ? true : false; }
	else if (move == "C") { return C ? true : false; }
	else if (move == "E") { return E ? true : false; }
	else if (move == "SW") { return SW ? true : false; }
	else if (move == "S") { return S ? true : false; }
	else if (move == "SE") { return SE ? true : false; }
	return false;
}

string ScoreBoard::getInputX() {
	return inputX;
}

string ScoreBoard::getInputO() {
	return inputO;
}

int ScoreBoard::getRound() {
	return round;
}

/* C++ program to administer the game of Tic-Tac-Toe
 * refer to (http://en.wikipedia.org/wiki/Tic-Tac-Toe) for detailed rules
 * Written for CS246 A3Q4b
 * Written by Dongwoo Son on March 9th 2015
 */

 /* NOTES
  * Command descriptions:
  * game input1 input2 // starts the game from input1 stream and input2 stream
  *                             for player1 and player2 respectively.
  * quit // exits the program
  */

int main() {
	bool done = false;
	cout << "********************************************************" << endl;
	cout << "How To Start the Game:" << endl;
	cout << "Type Command: game sX sO" << endl;
	cout << "Where sX denotes the name of the file name for X's move." << endl;
	cout << "sX may be stdin to take input from cin." << endl;
	cout << "Similarly for O." << endl;
	cout << "E.g. game stdin stdin" << endl;
	cout << "Valid Moves are: NW N NE" << endl;
	cout << "                 W  C E" << endl;
	cout << "                 SW S SE" << endl;
	cout << "Type quit to exit the program." << endl;
	cout << "All inputs are assumed to be valid." << endl;
	cout << "It is considered invalid to claim a taken square." << endl;
	cout << "********************************************************" << endl;
	while (!done) {
		string command;
		string move;
		ScoreBoard* scoreboard = ScoreBoard::getInstance();
		Player* pX = Player::getInstance1();
		Player* pO = Player::getInstance2();
		cin >> command;
		if (cin.eof()) break;
		if (command == "game") {
			scoreboard->startGame(); // reads in input1 and input2 (Reads stdin or *.txt)
			pX->takeInput();
			pO->takeInput();
			while (!scoreboard->isOver()) {
				if (scoreboard->getRound() % 2) { //odd-numbered round
					move = pX->makeMove();
					if (cin.fail()) { done = true; break; }
					scoreboard->makeMove(pX, move);
					if (scoreboard->isOver()) break;
					move = pO->makeMove();
					if (cin.fail()) { done = true; break; }
					scoreboard->makeMove(pO, move);
				}
				else {					   // even-numbered round
					move = pO->makeMove();
					if (cin.fail()) { done = true; break; }
					scoreboard->makeMove(pO, move);
					if (scoreboard->isOver()) break;
					move = pX->makeMove();
					if (cin.fail()) { done = true; break; }
					scoreboard->makeMove(pX, move);
				} // end if and else
			} // end while
			scoreboard->printScores();
		} // end if
		else if (command == "quit") {
			done = true;
		} // end else if
	} // end while
}