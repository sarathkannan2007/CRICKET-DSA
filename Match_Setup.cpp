#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class Team
{
public:
    string teamName;
    string captain;
    string players[11];
};

class Match
{
private:
    Team team1, team2;

    string stadium;
    string startTime;
    string endTime;

    string format;
    int overs;

    string tossWinner;
    string tossDecision;

public:

    void setTeams(Team t1, Team t2)
    {
        team1 = t1;
        team2 = t2;
    }

    void selectStadium()
    {
        cout << "Enter Stadium Name: ";
        cin >> stadium;
    }

    void selectTiming()
    {
        cout << "Enter Starting Time: ";
        cin >> startTime;

        cout << "Enter Ending Time: ";
        cin >> endTime;
    }

    void selectFormat()
    {
        int choice;

        cout << "\n1. IPL\n";
        cout << "2. T20\n";
        cout << "3. ODI\n";
        cout << "Enter format: ";
        cin >> choice;

        if (choice == 1)
        {
            format = "IPL";
            overs = 20;
        }
        else if (choice == 2)
        {
            format = "T20";
            overs = 20;
        }
        else if (choice == 3)
        {
            format = "ODI";
            overs = 50;
        }
        else
        {
            cout << "Invalid choice. IPL selected.\n";
            format = "IPL";
            overs = 20;
        }
    }

    void performToss()
    {
        int choice1, choice2;
        int randomNumber;

        cout << "\n========== TOSS ==========\n";

        cout << team1.captain << " (" << team1.teamName
             << "), choose 0 or 1: ";
        cin >> choice1;

        while (choice1 != 0 && choice1 != 1)
        {
            cout << "Choose only 0 or 1: ";
            cin >> choice1;
        }

        cout << team2.captain << " (" << team2.teamName
             << "), choose 0 or 1: ";
        cin >> choice2;

        while (choice2 != 0 && choice2 != 1)
        {
            cout << "Choose only 0 or 1: ";
            cin >> choice2;
        }

        while (choice1 == choice2)
        {
            cout << "Both captains cannot choose the same number.\n";

            cout << team2.captain << " (" << team2.teamName
                 << "), choose the other number: ";
            cin >> choice2;

            while (choice2 != 0 && choice2 != 1)
            {
                cout << "Choose only 0 or 1: ";
                cin >> choice2;
            }
        }

        randomNumber = rand() % 2;

        cout << "\n" << team1.captain << " chose: "
             << choice1 << endl;

        cout << team2.captain << " chose: "
             << choice2 << endl;

        cout << "Random number: "
             << randomNumber << endl;

        if (randomNumber == choice1)
        {
            tossWinner = team1.teamName;

            cout << team1.captain << " ("
                 << team1.teamName
                 << ") won the toss!\n";
        }
        else
        {
            tossWinner = team2.teamName;

            cout << team2.captain << " ("
                 << team2.teamName
                 << ") won the toss!\n";
        }

        int decision;

        cout << "\n" << tossWinner << " chooses:\n";
        cout << "1. Bat\n";
        cout << "2. Bowl\n";
        cout << "Enter choice: ";
        cin >> decision;

        while (decision != 1 && decision != 2)
        {
            cout << "Choose only 1 or 2: ";
            cin >> decision;
        }

        if (decision == 1)
            tossDecision = "Bat";
        else
            tossDecision = "Bowl";

        cout << tossWinner << " chose to "
             << tossDecision << ".\n";
    }

    void displayMatchDetails()
    {
        cout << "\n========== MATCH DETAILS ==========\n";

        cout << "\nStadium    : " << stadium << endl;
        cout << "Start Time : " << startTime << endl;
        cout << "End Time   : " << endTime << endl;

        cout << "\nTeams and Players (Tabulated):\n";
        cout << left << setw(20) << team1.teamName << setw(20) << team2.teamName << endl;
        cout << left << setw(20) << ("Captain: " + team1.captain) 
             << setw(20) << ("Captain: " + team2.captain) << endl;

        for (int i = 0; i < 11; i++)
        {
            string p1 = team1.players[i];
            string p2 = team2.players[i];

            if (p1 == team1.captain) p1 += " (C)";
            if (p2 == team2.captain) p2 += " (C)";

            cout << left << setw(20) << p1 << setw(20) << p2 << endl;
        }

        cout << "\nFormat      : " << format << endl;
        cout << "Overs       : " << overs << endl;
        cout << "Toss Winner : " << tossWinner << endl;
        cout << "Decision    : " << tossDecision << endl;

        // Opening batsmen and bowler based on toss decision
        cout << "\n========== OPENING PLAYERS ==========\n";

        if (tossWinner == team1.teamName && tossDecision == "Bat")
        {
            cout << "Opening Batsmen: "
                 << team1.players[0] << " and " << team1.players[1] << endl;
            cout << "Opening Bowler : "
                 << team2.players[0] << endl;
        }
        else if (tossWinner == team2.teamName && tossDecision == "Bat")
        {
            cout << "Opening Batsmen: "
                 << team2.players[0] << " and " << team2.players[1] << endl;
            cout << "Opening Bowler : "
                 << team1.players[0] << endl;
        }
        else if (tossWinner == team1.teamName && tossDecision == "Bowl")
        {
            cout << "Opening Batsmen: "
                 << team2.players[0] << " and " << team2.players[1] << endl;
            cout << "Opening Bowler : "
                 << team1.players[0] << endl;
        }
        else
        {
            cout << "Opening Batsmen: "
                 << team1.players[0] << " and " << team1.players[1] << endl;
            cout << "Opening Bowler : "
                 << team2.players[0] << endl;
        }

        cout << "\n========== MATCH READY ==========\n";
    }
};

int main()
{
    srand(time(0));

    Team team1;
    team1.teamName = "India";
    team1.captain = "Rohit";
    team1.players[0] = "Rohit";
    team1.players[1] = "Virat";
    team1.players[2] = "Gill";
    team1.players[3] = "Pant";
    team1.players[4] = "Rahul";
    team1.players[5] = "Hardik";
    team1.players[6] = "Jadeja";
    team1.players[7] = "Kuldeep";
    team1.players[8] = "Bumrah";
    team1.players[9] = "Siraj";
    team1.players[10] = "Arshdeep";

    Team team2;
    team2.teamName = "Australia";
    team2.captain = "Cummins";
    team2.players[0] = "Cummins";
    team2.players[1] = "Warner";
    team2.players[2] = "Smith";
    team2.players[3] = "Marsh";
    team2.players[4] = "Maxwell";
    team2.players[5] = "Carey";
    team2.players[6] = "Green";
    team2.players[7] = "Starc";
    team2.players[8] = "Hazlewood";
    team2.players[9] = "Zampa";
    team2.players[10] = "Head";

    Match match;
    match.setTeams(team1, team2);
    match.selectStadium();
    match.selectTiming();
    match.selectFormat();
    match.performToss();
    match.displayMatchDetails();

    return 0;
}
