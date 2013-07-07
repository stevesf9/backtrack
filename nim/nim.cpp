// backtracking.cpp : Defines the entry point for the console application.
//


/*
 * File: nim.cpp
 * -------------
 * This program simulates a simple variant of the game of nim.
 * In this version, the game starts with a pile of 13 coins
 * on a table. Players then take turns removing 1, 2, or 3
 * coins from the pile. The player who takes the last coin
 * loses. This simulation allows a human player to compete
 * against the computer.
 */
 
 /* #include "genlib.h" */
 /* #include "console.h" */
#include "simpio.h"
#include <iostream>

using namespace std;
 
 /*
 * Constants
 * ---------
 * N_COINS -- Initial number of coins
 * MAX_MOVE -- The maximum number of coins a player may take
 * NO_GOOD_MOVE -- Sentinel indicating no good move is available
 */
 
 const int N_COINS = 13;
 const int MAX_MOVE = 3;
 const int NO_GOOD_MOVE = -1;
 
 /*
 * Type: playerT
 * -------------
 * This enumeration type distinguishes the turns for the human
 * player from those for the computer.
 */
 
 enum playerT {Human, Computer};
 
 /* Private function prototypes */
 
 void GiveInstructions();
 void AnnounceWinner(int nCoins, playerT whoseTurn);
 int GetUserMove(int nCoins);
 bool MoveIsLegal(int nTaken, int nCoins);
 int ChooseComputerMove(int nCoins);
 int FindGoodMove(int nCoins);
 bool IsBadPosition(int nCoins);
 
 /*
 * Main program
 * ------------
 * This program plays the game of nim. In this implementation,
 * the human player always goes first.
 */
 
int main(int argc, char** argv) {
	int nCoins, nTaken;
	playerT whoseTurn;
	GiveInstructions();
	nCoins = N_COINS;
	whoseTurn = Human;
	while (nCoins > 1) {
		cout << "There are " << nCoins << " coins in the pile."<<endl;
		switch (whoseTurn) {
		case Human:
			nTaken = GetUserMove(nCoins);
			whoseTurn = Computer;
			break;
		case Computer:
			nTaken = ChooseComputerMove(nCoins);
			cout << "I'll take " << nTaken << "." << endl;
			whoseTurn = Human;
			break;
		}
		nCoins -= nTaken;
	}
	AnnounceWinner(nCoins, whoseTurn);
	return 0;
}

/*
 * Function: GiveInstructions
 * Usage: GiveInstructions();
 * --------------------------
 * This function explains the rules of the game to the user.
 */
void GiveInstructions() {
	cout << "Hello. Welcome to the game of nim." << endl;
	cout << "In this game, we will start with a pile of" << endl;
	cout << N_COINS << " coins on the table. " << endl;
	cout << "On each turn, you" << endl;
	cout << "and I will alternately take between 1 and" << endl;
	cout << MAX_MOVE << " coins from the table." << endl;
	cout << "The player who" << endl;
	cout << "takes the last coin loses." << endl;
	cout << endl;
}

/*
 * Function: AnnounceWinner
 * Usage: AnnounceWinner(nCoins, whoseTurn);
 * -----------------------------------------
 * This function announces the final result of the game.
 */

void AnnounceWinner(int nCoins, playerT whoseTurn) {
	if (nCoins == 0) {
		cout << "You took the last coin. You lose." << endl;
	} else {
		cout << "There is only one coin left." << endl;
		switch (whoseTurn) {
			case Human: cout << "I win." << endl; break;
			case Computer: cout << "I lose." << endl; break;
		}
	}
}

/*
 * Function: GetUserMove
 * Usage: nTaken = GetUserMove(nCoins);
 * ------------------------------------
 * This function is responsible for the human player's turn.
 * It takes the number of coins left in the pile as an argument,
 * and returns the number of coins that the player removes
 * from the pile. The function checks the move for legality
 * and gives the player repeated chances to enter a legal move.
 */

int GetUserMove(int nCoins) {
	int nTaken, limit;
	while (true) {
		nTaken = getInteger("How many would you like? ");
		if (MoveIsLegal(nTaken, nCoins)) break;
		limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
		cout << "That's cheating! Please choose a number";
		cout << " between 1 and " << limit << endl;
		cout << "There are " << nCoins << " coins in the pile."<<endl;
	}
	return nTaken;
}

/*
 * Function: MoveIsLegal
 * Usage: if (MoveIsLegal(nTaken, nCoins)) . . .
 * ---------------------------------------------
 * This predicate function returns true if it is legal to take
 * nTaken coins from a pile of nCoins.
 */

bool MoveIsLegal(int nTaken, int nCoins) {
	return (nTaken > 0 && nTaken <= MAX_MOVE && nTaken <= nCoins);
}

/*
 * Function: ChooseComputerMove
 * Usage: nTaken = ChooseComputerMove(nCoins);
 * -------------------------------------------
 * This function figures out what move is best for the computer
 * player and returns the number of coins taken. The function
 * first calls FindGoodMove to see if a winning move exists.
 * If none does, the program takes only one coin to give the
 * human player more chances to make a mistake.
 */

int ChooseComputerMove(int nCoins) {
	int nTaken = FindGoodMove(nCoins);
	if (nTaken == NO_GOOD_MOVE) nTaken = 1;
	return nTaken;
}

/*
 * Function: FindGoodMove
 * Usage: nTaken = FindGoodMove(nCoins);
 * -------------------------------------
 * This function looks for a winning move, given the specified
 * number of coins. If there is a winning move in that
 * position, the function returns that value; if not, the
 * function returns the constant NoWinningMove. This function
 * depends on the recursive insight that a good move is one
 * that leaves your opponent in a bad position and a bad
 * position is one that offers no good moves.
 */

int FindGoodMove(int nCoins) {
	for (int nTaken = 1; nTaken <= MAX_MOVE; nTaken++) {
		if (IsBadPosition(nCoins - nTaken)) return nTaken;
	}
	return NO_GOOD_MOVE;
}

/*
 * Function: IsBadPosition
 * Usage: if (IsBadPosition(nCoins)) . . .
 * ---------------------------------------
 * This function returns true if nCoins is a bad position.
 * A bad position is one in which there is no good move.
 * Being left with a single coin is clearly a bad position
 * and represents the simple case of the recursion.
 */

bool IsBadPosition(int nCoins) {
	if (nCoins == 1) return true;
	return FindGoodMove(nCoins) == NO_GOOD_MOVE;
}

