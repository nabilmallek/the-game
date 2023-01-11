

#include <iostream>
#include<cstdlib>
using namespace std;

enum enGame { Stone = 1,Paper = 2 , Scissors = 3 };
enum enWinner {Player = 1 , Computer = 2, Draw = 3};



struct stRoundInfo
{
	short numberOfRound = 0;
	enGame choiceOfPlayer ;
	enGame choiceOfComputer;
	enWinner Winner;
	string nameOfWinner;
};

struct stGameResults
{
	short GameRounds = 0;
	short playerWinTimes = 0;
	short computerWinTimes = 0;
	short drawTimes = 0;
	enWinner finalWinner;
	string finalWinnerName;
};


short readRand(short From, short To)
{
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}


// choose the number of rounds
short chooseRounds()
{
	short choice = 1;
	do
	{
		cout << " Please enter the number of rounds you want from 1 to 10 :\n";
		cin >> choice;
	} while (choice < 1 || choice > 10);
		return choice;
}

enGame playerChoice()
{
	short choice = 1;
	do
	{
		cout << "your choice : Stone [1] , Paper [2]  Scissors [3] :";
		cin >> choice;
	} while (choice < 1 || choice > 3);
	return (enGame)choice;
}

enGame computerChoice()
{
	return (enGame)readRand(1, 3);
}


// determine the winner between player and computer
enWinner winnerOfRound(stRoundInfo roundInfo)
{
	if (roundInfo.choiceOfPlayer == roundInfo.choiceOfComputer)
	{
		return enWinner::Draw;
	}
	switch (roundInfo.choiceOfPlayer)
	{
	case enGame::Stone:
		if (roundInfo.choiceOfComputer == enGame::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGame::Paper:
		if (roundInfo.choiceOfComputer == enGame::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGame::Scissors:
		if (roundInfo.choiceOfComputer == enGame::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;
	
	

}
// print the name of winner
string theWinner(enWinner Winner)
{
	string arrWinner[3] = {"Player","Computer","Draw"};
	return arrWinner[Winner - 1];
}

string nameChoice(enGame choice)
{
	string arrChoice[3] = { "Stone", "Paper","Scissors" };
	return arrChoice[choice - 1];
}

void printRound(stRoundInfo roundInfo)
{
	cout << "_________________Round [" << roundInfo.numberOfRound << "]__________________\n";
	cout << "player choice :" << nameChoice(roundInfo.choiceOfPlayer) << endl;
	cout << "computer choice :" << nameChoice(roundInfo.choiceOfComputer) << endl;
	cout << "round winner :" << roundInfo.nameOfWinner << endl;
	cout << "_____________________________________________\n";
}


// color of screen after eatch round
void showColorScreenRound(stRoundInfo roundInfo)
{
	if (roundInfo.Winner == enWinner::Player)
	{
		cout << system("color 2F");
	}
	else if (roundInfo.Winner == enWinner::Computer)
	{
		cout << system("color 4F");
		cout << "\a";
	}
	else
		cout << system(" color 6F");
}

void showColorScreenGame(stGameResults results)
{
	if (results.finalWinner == enWinner::Player)
	{
		cout << system("color 2F");
	}
	else if (results.finalWinner == enWinner::Computer)
	{
		cout << system("color 4F");
		cout << "\a";
	}
	else
		cout << system(" color 6F");
}

enWinner gameWinner(int playerWin, int computerWin)
{
	if (playerWin > computerWin)
	{
		return enWinner::Player;
	}
	else if (computerWin > playerWin)
	{
		return enWinner::Computer;

	}
	else
	{
		return enWinner::Draw;
	}
}
stGameResults fillGameResults(short roundsNumber,int playerWin,int computerWin,int drawTimes)
{
	stGameResults gameResults;

	 gameResults.GameRounds = roundsNumber ;
	 gameResults.playerWinTimes = playerWin;
	 gameResults.computerWinTimes = computerWin;
	 gameResults.drawTimes = drawTimes;
	 gameResults.finalWinner = gameWinner(playerWin,computerWin);
	 gameResults.finalWinnerName = theWinner(gameResults.finalWinner);

	 return gameResults;
}

stGameResults playGame(short rounds)
{
	int playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;
	stRoundInfo roundInfo;
	
	for (int roundsNumber = 1; roundsNumber <= rounds; roundsNumber++)
	{

		cout << "Round [" << roundsNumber << "] begins :\n";
		
	
		roundInfo.numberOfRound = roundsNumber;
		roundInfo.choiceOfPlayer = playerChoice();
		roundInfo.choiceOfComputer = computerChoice();
		roundInfo.Winner = winnerOfRound(roundInfo);
		roundInfo.nameOfWinner = theWinner(roundInfo.Winner);

		if (roundInfo.Winner == enWinner::Player)
		{
			 playerWinTimes++;
		}
		else if (roundInfo.Winner == enWinner::Computer)
		{
			computerWinTimes++;
		}
		else
		{
			drawTimes++;
		}
		printRound(roundInfo);
		showColorScreenRound(roundInfo);
	}
	return fillGameResults(roundInfo.numberOfRound, playerWinTimes, computerWinTimes, drawTimes);
}

string tabe(int number)
{
	string t = " ";
	for (int i = 0; i <= number; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}


void printgameResults(stGameResults gameresults)
{
	cout <<tabe(2) << "game Rounds :" << gameresults.GameRounds << endl;
	cout << tabe(2) << " player win times :" << gameresults.playerWinTimes << endl;
	cout << tabe(2) << "computer win times :" << gameresults.computerWinTimes << endl;
	cout << tabe(2) << "draw times :" << gameresults.drawTimes << endl;
	cout << tabe(2) << "final winner : " << gameresults.finalWinnerName << endl;
	cout << tabe(2) << "______________________________________" << endl;
}




void showGameOver()
{
	cout << tabe(2) << 
	"*********************************\n";
	cout << tabe(2) << "       +++ GAME OVER +++ \n";
	cout << tabe (2) << 
	"*********************************\n";
}

void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
	string playAgain = "yes";

	do
	{
		resetScreen();
		stGameResults gameResults = playGame(chooseRounds());
		showGameOver();
		printgameResults(gameResults);
		showColorScreenGame(gameResults);
		cout << endl << tabe(5) << "do you want to play agin ? yes/ No :";
		cin >> playAgain;
		cout << endl;


			

	} while (playAgain == "yes");
}

int main()
{
	srand((unsigned)time(NULL));
	 
	 startGame();
}

