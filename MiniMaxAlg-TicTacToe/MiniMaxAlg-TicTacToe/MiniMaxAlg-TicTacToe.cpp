//========================================================
//Name: Gabriel Ball
//Date: 04-01-24
//Desc: Unbeatable Tic Tac Toe AI using Mini Max Algorithm
//========================================================

#include <iostream>
#include <random> 
#include <windows.h>
using namespace std;

void displayBoard(char board[3][3]);
void userCoordToArrayCoord(int& r, int& c, string row, string col);
bool gameOver();
void pickRandomEmptySpot(char board[3][3], int& r, int& c);
void arrayCoordToUserCoord(string& row, string& col, int r, int c);

int main()
{
	char board[3][3] = {
		{' ',' ',' '},
		{' ',' ',' '},
		{' ',' ',' '}
	};
	bool playerTurn = true; //Default to true

	cout << "This is the empty Tic-Tac-Toe Board." << endl;
	cout << "   1   2   3 " << endl
		 << "A    |   |   " << endl
		 << "  ---|---|---" << endl
		 << "B    |   |   " << endl
		 << "  ---|---|---" << endl
		 << "C    |   |   " << endl << endl;

	cout << "Since I'm just so confident, you get to choose who goes first. Here are your options: " << endl;
	cout << "   Type '0' to go first" << endl;
	cout << "   Type '1' for the AI to go first" << endl; 
	cout << "   Type '2' for a coin toss" << endl;
	cout << "Your decision: ";

	string ans;
	cin >> ans;

	while (ans != "0" && ans != "1" && ans != "2")
	{
		cout << "Invalid Response. Please type 0, 1, or 2: ";
		cin >> ans;
	}

	if (ans == "1")
	{
		playerTurn = false;
	}
	else if (ans == "2")
	{
		//Perform Coin Toss
		cout << "The coin is in the air! Type 'H' for heads or 'T' for tails: ";
		string coinDecision;
		cin >> coinDecision;

		while (coinDecision != "H" && coinDecision != "h" && coinDecision != "T" && coinDecision != "t")
		{
			cout << "Invalid Response. Please type H or T: ";
			cin >> coinDecision;
		}

		//Random number stuff idk
		random_device rand;
		mt19937 gen(rand());
		uniform_int_distribution<>dis(1, 2);
		int randomNumber = dis(gen);

		if (randomNumber == 1)
		{
			cout << "The coin landed on Heads!" << endl;
			if (coinDecision == "T" || coinDecision == "t")
			{
				playerTurn = false;
			}
		}
		else if (randomNumber == 2)
		{
			cout << "The coin landed on Tails!" << endl;
			if (coinDecision == "H" || coinDecision == "h")
			{
				playerTurn = false;
			}
		}
	}
	if (playerTurn)
	{
		cout << "Ok, you will be going first!" << endl;
	}
	else
	{
		cout << "Ok, the AI will be going first!" << endl;
	}
	Sleep(500);

	//HOW TO PLAY
	cout << "==============================HOW TO PLAY==============================" << endl;
	cout << "Here's how this will go. You will be X, the AI will be O." << endl;
	cout << "When it is your turn, you will be prompted to input a row." << endl;
	cout << "After you give the row, you will be asked for a column." << endl;
	cout << "If that space is empty, your X will be placed there." << endl;
	cout << "If that space is occupied, you will be asked for a row & column again." << endl;
	cout << "Enter anything to start the game: ";
	string cont;
	cin >> cont;
	system("CLS");

	displayBoard(board);

	//GAME LOOP
	while (!gameOver())
	{
		string row;
		string col;
		int r;
		int c;
		if (playerTurn)
		{
			cout << "It is your turn. You will be asked for a row, then a column." << endl;
			bool validSpot = false;

			while (!validSpot)
			{
				//ROW
				cout << "Row: ";
				cin >> row;
				while (row != "A" && row != "a" && row != "B" && row != "b" && row != "C" && row != "c")
				{
					cout << "Invalid Input, please enter A, B or C: ";
					cin >> row;
				}
				//COLUMN
				cout << "Column: ";
				cin >> col;
				while (col != "1" && col != "2" && col != "3")
				{
					cout << "Invalid Input, please enter 1, 2 or 3: ";
					cin >> col;
				}

				userCoordToArrayCoord(r, c, row, col);
				if (board[r][c] == 'O' || board[r][c] == 'X')
				{
					cout << row << col << " is already marked with an " << board[r][c] << ". Choose another spot." << endl;
				}
				else
				{
					validSpot = true;
				}
			}
			cout << "Placing your X at " << row << col << endl;
			board[r][c] = 'X';
			playerTurn = false;
		}
		else
		{
			cout << "It is the AI's turn now." << endl;
			pickRandomEmptySpot(board, r, c);
			board[r][c] = 'O';
			playerTurn = true;
		}
		system("CLS");
		arrayCoordToUserCoord(row, col, r, c);
		cout << "The AI placed its O at " << row << col << endl << endl;
		displayBoard(board);
	}

	cout << endl << endl;
}

void displayBoard(char board[3][3])
{
	cout << "   1   2   3" << endl
		 << "A  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl
		 << "  -----------" << endl
		 << "B  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl
		 << "  -----------" << endl
		 << "C  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

bool gameOver()
{
	return false;
}

void pickRandomEmptySpot(char board[3][3], int& r, int& c)
{
	bool validSpot = false;
	int randomRow;
	int randomCol;
	while (!validSpot)
	{
		random_device rand1;
		mt19937 gen1(rand1());
		uniform_int_distribution<>dis1(0, 2);
		randomRow = dis1(gen1);

		random_device rand2;
		mt19937 gen2(rand2());
		uniform_int_distribution<>dis2(0, 2);
		randomCol = dis2(gen2);

		if (board[randomRow][randomCol] == ' ')
		{
			validSpot = true;
			r = randomRow;
			c = randomCol;
		}
	}
}

void userCoordToArrayCoord(int& r, int& c, string row, string col)
{
	//SET ROW INT
	if (row == "A" || row == "a")
	{
		r = 0;
	}
	else if (row == "B" || row == "b")
	{
		r = 1;
	}
	else if (row == "C" || row == "c")
	{
		r = 2;
	}
	//SET COL INT
	if (col == "1")
	{
		c = 0;
	}
	else if (col == "2")
	{
		c = 1;
	}
	else if (col == "3")
	{
		c = 2;
	}
}

void arrayCoordToUserCoord(string& row, string& col, int r, int c)
{
	//SET ROW STRING
	if (r == 0)
	{
		row = "A";
	}
	else if (r == 1)
	{
		row = "B";
	}
	else if (r == 2)
	{
		row = "C";
	}
	//SET COl STRING
	if (c == 0)
	{
		col = "1";
	}
	else if (c == 1)
	{
		col = "2";
	}
	else if (c == 2)
	{
		col = "3";
	}
}


















//cout << "         |         |         " << endl
//	   << "    X    |         |         " << endl
//	   << "         |         |         " << endl
//	   << "-----------------------------" << endl
//	   << "         |         |         " << endl
//	   << "         |    X    |         " << endl
//	   << "         |         |         " << endl
//	   << "-----------------------------" << endl
//	   << "         |         |         " << endl
//	   << "         |         |    X    " << endl
//	   << "         |         |         " << endl;