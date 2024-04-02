//========================================================
//Name: Gabriel Ball
//Date: 04-01-24
//Desc: Unbeatable Tic Tac Toe AI using Mini Max Algorithm
//========================================================

#include <iostream>
#include <random> 
using namespace std;

void displayBoard(char board[3][3]);

int main()
{
	char board[3][3] = {
		{'-','-','-'},
		{'-','-','-'},
		{'-','-','-'}
	};
	bool playerTurn = true; //Default to true

	cout << "This is the empty Tic-Tac-Toe Board." << endl;
	cout << "   |   |   " << endl
		 << "---|---|---" << endl
		 << "   |   |   " << endl
		 << "---|---|---" << endl
		 << "   |   |   " << endl;
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

	if (ans == "0")
	{
		cout << "Ok, you go first!" << endl;
	}
	else if (ans == "1")
	{
		playerTurn = false;
		cout << "Ok, the AI will go first!" << endl;
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
			if (coinDecision == "H" || coinDecision == "h")
			{
				cout << "Ok, you go first!" << endl;
			}
			else
			{
				playerTurn = false;
				cout << "The AI will go first!" << endl;
			}
		}
		else if (randomNumber == 2)
		{
			cout << "The coin landed on Tails!" << endl;
			if (coinDecision == "T" || coinDecision == "t")
			{
				cout << "Ok, you go first!" << endl;
			}
			else
			{
				playerTurn = false;
				cout << "The AI will go first!" << endl;
			}
		}
	}

	//GAME LOOP

	cout << endl << endl;
	displayBoard(board);
}

void displayBoard(char board[3][3])
{
	cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl
		<< "-----------" << endl
		<< " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl
		<< "-----------" << endl
		<< " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}



















//cout << "         |         |         " << endl
//	 << "    X    |         |         " << endl
//	 << "         |         |         " << endl
//	 << "-----------------------------" << endl
//	 << "         |         |         " << endl
//	 << "         |    X    |         " << endl
//	 << "         |         |         " << endl
//	 << "-----------------------------" << endl
//	 << "         |         |         " << endl
//	 << "         |         |    X    " << endl
//	 << "         |         |         " << endl;