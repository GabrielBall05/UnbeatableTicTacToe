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
bool gameOver(char board[3][3], string& whoWon);
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

	cout << "This is what the Tic-Tac-Toe Board looks like." << endl;
	displayBoard(board);

	cout << "Since I'm just so confident, you get to choose who goes first. Here are your options: " << endl;
	cout << "   Type 'M' to go first" << endl;
	cout << "   Type 'A' for the AI to go first" << endl; 
	cout << "   Type 'C' for a coin toss" << endl;
	cout << "Your decision: ";

	string ans;
	cin >> ans;

	while (ans != "M" && ans != "A" && ans != "C" && ans != "m" && ans != "a" && ans != "c")
	{
		cout << "Invalid Response. Please type M, A, or C: ";
		cin >> ans;
	}

	if (ans == "A" || ans == "a")
	{
		playerTurn = false;
	}
	else if (ans == "C" || ans == "c")
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

		//Random number stuff idektbh
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
		Sleep(2000);
	}

	system("CLS");
	if (playerTurn)
	{
		cout << "Ok, you will be going first!" << endl;
	}
	else
	{
		cout << "Ok, the AI will be going first!" << endl;
	}
	//Sleep(1500);

	//HOW TO PLAY
	cout << endl << "==============================HOW TO PLAY==============================" << endl;
	cout << "Here's how this will go. You will be X, the AI will be O." << endl; //Sleep(2000);
	cout << "When it is your turn, you will be prompted to input a column." << endl; //Sleep(2000);
	cout << "After you give the row, you will be asked for a row." << endl; //Sleep(2000);
	cout << "If that space is empty, your X will be placed there." << endl; //Sleep(2000);
	cout << "If that space is occupied, you will be asked for a column & row again." << endl << endl; //Sleep(2000);
	cout << "Enter anything to start the game: ";
	string cont;
	cin >> cont;
	system("CLS");

	displayBoard(board);

	//GAME LOOP
	string whoWon;
	while (!gameOver(board, whoWon))
	{
		string row;
		string col;
		int r;
		int c;
		if (playerTurn)
		{
			cout << "It is your turn. Enter a column, then enter a row." << endl;
			bool validSpot = false;

			while (!validSpot)
			{
				//COLUMN
				cout << "Column: ";
				cin >> col;
				while (col != "A" && col != "a" && col != "B" && col != "b" && col != "C" && col != "c")
				{
					cout << "Invalid Input, please enter A, B or C: ";
					cin >> col;
				}
				//ROW
				cout << "Row: ";
				cin >> row;
				while (row != "1" && row != "2" && row != "3")
				{
					cout << "Invalid Input, please enter 1, 2 or 3: ";
					cin >> row;
				}

				userCoordToArrayCoord(r, c, row, col);
				if (board[r][c] != ' ')
				{
					cout << col << row << " is already marked with an " << board[r][c] << ". Choose another spot." << endl;
				}
				else
				{
					validSpot = true;
				}
			}
			board[r][c] = 'X';
			playerTurn = false;
		}
		else
		{
			//CHANGE TO MINIMAX
			pickRandomEmptySpot(board, r, c);
			board[r][c] = 'O';
			playerTurn = true;
		}
		system("CLS");
		arrayCoordToUserCoord(row, col, r, c);
		cout << "The AI placed its 'O' at " << col << row << endl << endl;
		displayBoard(board);
	}
	system("CLS");
	displayBoard(board);
	cout << whoWon << " won the game!" << endl;

	cout << endl << endl;
}

void displayBoard(char board[3][3])
{
	cout << "   A   B   C" << endl
		<< "1  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl
		<< "  -----------" << endl
		<< "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl
		<< "  -----------" << endl
		<< "3  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

bool gameOver(char board[3][3], string& whoWon)
{
	bool gameOver = false;
	//CHECK ROWS
	for (int r = 0; r < 3 && !gameOver; r++)
	{
		if (board[r][0] == board[r][1] && board[r][1] == board[r][2])
		{
			if (board[r][0] != ' ')
			{
				gameOver = true;
				if (board[r][0] == 'X')
				{
					whoWon = "PLAYER";
				}
				else if (board[r][0] == 'O')
				{
					whoWon = "AI";
				}
			}
		}
	}
	//CHECK COLUMNS
	for (int c = 0; c < 3 && gameOver == false; c++)
	{
		if (board[0][c] == board[1][c] && board[1][c] == board[2][c])
		{
			if (board[0][c] == 'X' || board[0][c] == 'O')
			{
				gameOver = true;
				if (board[0][c] == 'X')
				{
					whoWon = "PLAYER";
				}
				else if (board[0][c] == 'O')
				{
					whoWon = "AI";
				}
			}
		}
	}
	//CHECK DIAGONALS
	if (((board[1][1] == board[0][0] && board[1][1] == board[2][2]) || (board[1][1] == board[0][2] && board[1][1] == board[2][0])) && board[1][1] != ' ')
	{
		gameOver = true;
		//WHO WON
		if (board[1][1] == 'X')
		{
			whoWon = "PLAYER";
		}
		else if (board[1][1] == 'O')
		{
			whoWon = "AI";
		}
	}
	//CHECK DRAW
	if (!gameOver)
	{
		int i = 0;
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (board[r][c] != ' ')
				{
					i++;
				}
				if (i >= 9)
				{
					gameOver = true;
					whoWon = "DRAW";
				}
			}
		}
	}

	return gameOver;
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
	if (row == "1")
	{
		r = 0;
	}
	else if (row == "2")
	{
		r = 1;
	}
	else if (row == "3")
	{
		r = 2;
	}
	//SET COL INT
	if (col == "A" || col == "a")
	{
		c = 0;
	}
	else if (col == "B" || col == "b")
	{
		c = 1;
	}
	else if (col == "C" || col == "c")
	{
		c = 2;
	}
}

void arrayCoordToUserCoord(string& row, string& col, int r, int c)
{
	//SET ROW STRING
	if (r == 0)
	{
		row = "1";
	}
	else if (r == 1)
	{
		row = "2";
	}
	else if (r == 2)
	{
		row = "3";
	}
	//SET COl STRING
	if (c == 0)
	{
		col = "A";
	}
	else if (c == 1)
	{
		col = "B";
	}
	else if (c == 2)
	{
		col = "C";
	}
}


//cout << "         1         2         3    "
//	   << "                                  " << endl
//     << "              |         |         " << endl
//	   << " A       " << board[0][0] << "    |    " << board[0][1] << "    |    " << board[0][2] << "    " << endl
//	   << "              |         |         " << endl
//	   << "     -----------------------------" << endl
//	   << "              |         |         " << endl
//	   << " B       " << board[1][0] << "    |    " << board[1][1] << "    |    " << board[1][2] << "    " << endl
//	   << "              |         |         " << endl
//	   << "     -----------------------------" << endl
//	   << "              |         |         " << endl
//	   << " C       " << board[2][0] << "    |    " << board[2][1] << "    |    " << board[2][2] << "    " << endl
//	   << "              |         |         " << endl;