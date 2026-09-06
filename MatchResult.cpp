#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
    string name;
    int runs;
};

string calculateWinner(string firstTeamName, int difference, string secondTeamName)
{
    if (difference > 0)
    {
        return firstTeamName;
    }
    else if (difference < 0)
    {
        return secondTeamName;
    }
    else
    {
        return "Tie";
    }
}

int calculateMargin(int difference, int secondTeamWickets)
{
    if (difference > 0)
    {
        return difference;
    }
    else if (difference < 0)
    {
        return 10 - secondTeamWickets;
    }

    return 0;
}

string getResultType(int difference)
{
    if (difference > 0)
    {
        return "runs";
    }
    else if (difference < 0)
    {
        return "wickets";
    }
    else
    {
        return "Tie";
    }
}

int findHighestScorer(Player players[], int playerCount)
{
    int highestIndex = 0;

    for (int i = 1; i < playerCount; i++)
    {
        if (players[i].runs > players[highestIndex].runs)
        {
            highestIndex = i;
        }
    }

    return highestIndex;
}

void displayMatchResult(
    string firstTeamName,
    int firstTeamScore,
    int firstTeamWickets,
    Player firstTeamPlayers[],
    int firstTeamPlayerCount,
    string secondTeamName,
    int secondTeamScore,
    int secondTeamWickets,
    Player secondTeamPlayers[],
    int secondTeamPlayerCount)
{
    int difference = firstTeamScore - secondTeamScore;

    string winner = calculateWinner(
        firstTeamName,
        difference,
        secondTeamName
    );

    int margin = calculateMargin(
        difference,
        secondTeamWickets
    );

    string resultType = getResultType(difference);

    int highestIndex1 = findHighestScorer(
        firstTeamPlayers,
        firstTeamPlayerCount
    );

    int highestIndex2 = findHighestScorer(
        secondTeamPlayers,
        secondTeamPlayerCount
    );

    cout << "\n====================================";
    cout << "\n           MATCH RESULT";
    cout << "\n====================================";

    cout << "\n\n" << firstTeamName << " : "
         << firstTeamScore << "/"
         << firstTeamWickets;

    cout << "\n" << secondTeamName << " : "
         << secondTeamScore << "/"
         << secondTeamWickets;

    cout << "\n\n------------------------------------";

    if (winner == "Tie")
    {
        cout << "\nMATCH TIED!";
    }
    else
    {
        cout << "\nWinner: " << winner;
        cout << "\n" << winner
             << " won by "
             << margin
             << " "
             << resultType;
    }

    cout << "\n\n------------------------------------";
    cout << "\n       HIGHEST SCORER";

    if (firstTeamPlayers[highestIndex1].runs >
        secondTeamPlayers[highestIndex2].runs)
    {
        cout << "\nPlayer: "
             << firstTeamPlayers[highestIndex1].name;

        cout << "\nTeam: "
             << firstTeamName;

        cout << "\nRuns: "
             << firstTeamPlayers[highestIndex1].runs;
    }
    else if (secondTeamPlayers[highestIndex2].runs >
             firstTeamPlayers[highestIndex1].runs)
    {
        cout << "\nPlayer: "
             << secondTeamPlayers[highestIndex2].name;

        cout << "\nTeam: "
             << secondTeamName;

        cout << "\nRuns: "
             << secondTeamPlayers[highestIndex2].runs;
    }
    else
    {
        cout << "\nBoth players have the same highest score.";

        cout << "\n"
             << firstTeamPlayers[highestIndex1].name
             << " : "
             << firstTeamPlayers[highestIndex1].runs
             << " runs";

        cout << "\n"
             << secondTeamPlayers[highestIndex2].name
             << " : "
             << secondTeamPlayers[highestIndex2].runs
             << " runs";
    }

    cout << "\n====================================\n";
}

int main()
{
    string firstTeamName = "India";
    int firstTeamScore = 250;
    int firstTeamWickets = 8;

    Player firstTeamPlayers[3];

    firstTeamPlayers[0].name = "Virat Kohli";
    firstTeamPlayers[0].runs = 85;

    firstTeamPlayers[1].name = "Rohit Sharma";
    firstTeamPlayers[1].runs = 70;

    firstTeamPlayers[2].name = "Hardik Pandya";
    firstTeamPlayers[2].runs = 45;

    int firstTeamPlayerCount = 3;

    string secondTeamName = "Australia";
    int secondTeamScore = 230;
    int secondTeamWickets = 10;

    Player secondTeamPlayers[3];

    secondTeamPlayers[0].name = "Steve Smith";
    secondTeamPlayers[0].runs = 90;

    secondTeamPlayers[1].name = "David Warner";
    secondTeamPlayers[1].runs = 65;

    secondTeamPlayers[2].name = "Glenn Maxwell";
    secondTeamPlayers[2].runs = 40;

    int secondTeamPlayerCount = 3;

    displayMatchResult(
        firstTeamName,
        firstTeamScore,
        firstTeamWickets,
        firstTeamPlayers,
        firstTeamPlayerCount,
        secondTeamName,
        secondTeamScore,
        secondTeamWickets,
        secondTeamPlayers,
        secondTeamPlayerCount
    );

    return 0;
}
