//========================================================
//Name: Gabriel Ball
//Date: 04-01-24
//Desc: Unbeatable Tic Tac Toe AI using Mini Max Algorithm
//========================================================

#include <iostream>
#include <random> 
#include <windows.h>
#include <cctype>
#include <string>
using namespace std;

int miniMax(char board[3][3], int depth, bool maximizing, int& whoWon);
void miniMaxStart(char board[3][3], int& bestMoveR, int& bestMoveC, int& whoWon);
void displayBoard(char board[3][3]);
void whoGoesFirstAndRules(bool& playerTurn);
void userCoordToArrayCoord(int& r, int& c, char row, char col);
void arrayCoordToUserCoord(string& row, string& col, int r, int c);
bool gameOver(char board[3][3], int& whoWon);

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
	//This function is really just so that not everything is piled in main
	whoGoesFirstAndRules(playerTurn);
	displayBoard(board);

	//GAME LOOP
	int whoWon = 0;
	int i = 0;
	while (!gameOver(board, whoWon))
	{
		int r;
		int c;
		if (playerTurn)
		{
			//cout << "It is your turn. Enter a column, then enter a row." << endl;
			bool validSpot = false;

			while (!validSpot)
			{
				if (i == 0 && !validSpot)
					cout << "The Game Has Begun." << endl << endl;
				string coord;
				cout << "Enter a coordinate (ex: B2 for middle): ";
				cin >> coord;
				coord[0] = toupper(coord[0]);

				while (coord != "A1" && coord != "A2" && coord != "A3" && coord != "B1" && coord != "B2" && coord != "B3" && coord != "C1" && coord != "C2" && coord != "C3")
				{
					cout << "Invalid Input, please enter a valid coordinate: ";
					cin >> coord;
					coord[0] = toupper(coord[0]);
				}
				r = coord[1];
				c = coord[0];

				userCoordToArrayCoord(r, c, coord[1], coord[0]);
				if (board[r][c] != ' ')
				{
					cout << coord[0] << coord[1] << " is already marked with an " << board[r][c] << ". Choose another spot." << endl;
				}
				else
				{
					validSpot = true;
				}
			}
			board[r][c] = 'X';
			playerTurn = false;
			system("CLS");
		}
		else
		{
			if (i != 0)
				Sleep(1000);
			int bestMoveR = 999;
			int bestMoveC = 999;
			//Make copy board
			char boardCopy[3][3];
			for (int r = 0; r < 3; r++)
			{
				for (int c = 0; c < 3; c++)
				{
					boardCopy[r][c] = board[r][c];
				}
			}
			miniMaxStart(boardCopy, bestMoveR, bestMoveC, whoWon);
			board[bestMoveR][bestMoveC] = 'O';
			playerTurn = true;
			r = bestMoveR;
			c = bestMoveC;
			system("CLS");
		}
		i++;
		displayBoard(board);
		string row;
		string col;
		arrayCoordToUserCoord(row, col, r, c);
		if (playerTurn)
			cout << "The AI placed its 'O' at " << col << row << endl << endl;
	}
	//GAME LOOP ^^^
	//Clear screen and display who won (and the finished board state)
	system("CLS");
	displayBoard(board);

	if (whoWon == 0)
	{
		cout << "It was a draw! Nobody wins!" << endl;
	}
	else if (whoWon == 1)
	{
		cout << "The AI Wins!" << endl;
	}
	else if (whoWon == -1) //This will never happen, but it's here just in case
	{
		cout << "You Win!" << endl;
	}

	cout << endl << endl;
}

void miniMaxStart(char boardCopy[3][3], int& bestMoveR, int& bestMoveC, int& whoWon)
{
	int bestScore = 0;
	bool foundBestMove = false;

	for (int r = 0; r < 3 && !foundBestMove; r++)
	{
		for (int c = 0; c < 3 && !foundBestMove; c++)
		{
			//If spot is open, make move
			if (boardCopy[r][c] == ' ')
			{
				boardCopy[r][c] = 'O';
				int score = miniMax(boardCopy, 0, false, whoWon);
				if (score >= bestScore)
				{
					bestScore = score;
					bestMoveR = r;
					bestMoveC = c;
					//Stop loops
					foundBestMove = true;
				}
				boardCopy[r][c] = ' '; //Reset piece
			}
		}
	}
}

int miniMax(char boardCopy[3][3], int depth, bool maximizing, int& whoWon)
{
	//Base case is a board end state (someone won or draw)
	if (gameOver(boardCopy, whoWon))
	{
		return whoWon;
	}

	//AI TURN
	if (maximizing)
	{
		int bestScore = INT_MIN;

		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (boardCopy[r][c] == ' ')
				{
					//Make move
					boardCopy[r][c] = 'O';
					//Pass updated board
					int score = miniMax(boardCopy, depth + 1, false, whoWon);
					//If it's better for the AI
					if (score > bestScore)
					{
						bestScore = score;
					}
					boardCopy[r][c] = ' '; //Reset piece
				}
			}
		}
		return bestScore;
	}
	//PLAYER TURN
	else
	{
		int bestScore = INT_MAX;

		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (boardCopy[r][c] == ' ')
				{
					//Make move
					boardCopy[r][c] = 'X';
					//Pass updated board
					int score = miniMax(boardCopy, depth + 1, true, whoWon);
					//If it's better for the player
					if (score < bestScore)
					{
						bestScore = score;
					}
					boardCopy[r][c] = ' '; //Reset piece
				}
			}
		}
		return bestScore;
	}
}

bool gameOver(char boardCopy[3][3], int& whoWon)
{
	bool gameOver = false;
	//CHECK ROWS
	for (int r = 0; r < 3 && !gameOver; r++)
	{
		if (boardCopy[r][0] == boardCopy[r][1] && boardCopy[r][1] == boardCopy[r][2])
		{
			if (boardCopy[r][0] != ' ')
			{
				gameOver = true;
				if (boardCopy[r][0] == 'X') //If player's piece is in the winner's row
				{
					whoWon = -1;
				}
				else if (boardCopy[r][0] == 'O') //If AI's piece is in the winner's row
				{
					whoWon = 1;
				}
			}
		}
	}
	//CHECK COLUMNS
	for (int c = 0; c < 3 && gameOver == false; c++)
	{
		if (boardCopy[0][c] == boardCopy[1][c] && boardCopy[1][c] == boardCopy[2][c])
		{
			if (boardCopy[0][c] == 'X' || boardCopy[0][c] == 'O')
			{
				gameOver = true;
				if (boardCopy[0][c] == 'X') //If player's piece is in the winner's column
				{
					whoWon = -1;
				}
				else if (boardCopy[0][c] == 'O') //If AI's piece is in the winner's column
				{
					whoWon = 1;
				}
			}
		}
	}
	//CHECK DIAGONALS
	if (((boardCopy[1][1] == boardCopy[0][0] && boardCopy[1][1] == boardCopy[2][2]) || (boardCopy[1][1] == boardCopy[0][2] && boardCopy[1][1] == boardCopy[2][0])) && boardCopy[1][1] != ' ')
	{
		gameOver = true;
		//WHO WON
		if (boardCopy[1][1] == 'X') //If player's piece is in the winner's diagonal
		{
			whoWon = -1;
		}
		else if (boardCopy[1][1] == 'O') //If AI's piece is in the winner's diagonal
		{
			whoWon = 1;
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
				if (boardCopy[r][c] != ' ')
				{
					i++;
				}
				if (i >= 9)
				{
					//It was a draw, the game is over and nobody won
					gameOver = true;
					whoWon = 0;
				}
			}
		}
	}

	return gameOver;
}

//Takes the user's input and turns it into [0-2][0-2] so I can actually use it
void userCoordToArrayCoord(int& r, int& c, char row, char col)
{
	r = (row - '0') - 1;
	if (col == 'A' || col == 'B' || col == 'C')
	{
		c = col - 65;
	}
	else if (col == 'a' || col == 'b' || col == 'c')
	{
		c = col - 97;
	}
}

//Same thing just in reverse so I can display to the user where the AI went
void arrayCoordToUserCoord(string& row, string& col, int r, int c)
{
	r++;
	row = to_string(r);

	c += 65;
	col = char(c);
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

void whoGoesFirstAndRules(bool& playerTurn)
{
	cout << "Since I'm just so confident, you get to choose who goes first. Here are your options: " << endl;
	cout << "   Type '1' to go first" << endl;
	cout << "   Type '2' for the AI to go first" << endl;
	cout << "   Type '3' for a coin toss" << endl;
	cout << "Your decision: ";
	string ans;
	cin >> ans;

	while (ans != "1" && ans != "2" && ans != "3")
	{
		cout << "Invalid Response. Please type 1, 2, or 3: ";
		cin >> ans;
	}

	if (ans == "2")
	{
		playerTurn = false;
	}
	else if (ans == "3")
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
				Sleep(1000);
				cout << "You picked tails, so you lost the coin toss." << endl;
				playerTurn = false;
			}
			else
				cout << "You won the coin toss!" << endl;
		}
		else
		{
			cout << "The coin landed on Tails!" << endl;
			if (coinDecision == "H" || coinDecision == "h")
			{
				Sleep(1000);
				cout << "You picked heads, so you lost the coin toss." << endl;
				playerTurn = false;
			}
			else
				cout << "You won the coin toss!" << endl;
		}
		Sleep(3000);
	}

	system("CLS");
	if (playerTurn)
	{
		cout << "Ok, you will be going first." << endl;
	}
	else
	{
		cout << "Ok, the AI will be going first." << endl;
	}

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
}