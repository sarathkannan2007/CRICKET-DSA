#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "PlayerManagement.cpp"
#include "score.cpp"

using namespace std;

int team1score = 0;
int team2score = 0;

random_device rd;
mt19937 gen(rd());

int run()
{
    int outcomes[] = {0, 1, 2, 3, 4, 6, -1};
    double probability[] = {30, 25, 15, 5, 15, 5, 5};

    discrete_distribution<> dist(probability, probability + 7);

    return outcomes[dist(gen)];
}

void createCSV()
{
    ofstream file("match.csv");

    file << "Over,Ball,Batsman,BatsmanID,Bowler,BowlerID,Runs,Event\n";

    file.close();
}

void writeBall(int over, int ball, string batsman, int batsmanID, string bowler, int bowlerID, int runs, string event)
{
    ofstream file("match.csv", ios::app);

    file << over << ","
         << ball << ","
         << batsman << ","
         << batsmanID << ","
         << bowler << ","
         << bowlerID << ","
         << runs << ","
         << event << "\n";

    file.close();
}

void loadPlayersToMatch(int team1ID, string team1Name, int team2ID, string team2Name)
{
    Player *tempPlayer = head;

    while (tempPlayer != NULL)
    {
        if (tempPlayer->teamID == team1ID && !tempPlayer->isSubstitute)
        {
            addTeam1(
                tempPlayer->playerName,
                tempPlayer->playerID,
                team1Name);
        }

        if (tempPlayer->teamID == team2ID && !tempPlayer->isSubstitute)
        {
            addTeam2(
                tempPlayer->playerName,
                tempPlayer->playerID,
                team2Name);
        }

        tempPlayer = tempPlayer->next;
    }
}

int countPlayers(struct node *head)
{
    int count = 0;

    temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

struct node *getBowler(struct node *head, int index)
{
    temp = head;

    int count = 0;

    while (temp != NULL)
    {
        Player *player = getPlayerByID(temp->playernum);

        if (player != NULL)
        {
            if (player->role == "Bowler" ||
                player->role == "All-Rounder")
            {
                if (count == index)
                    return temp;

                count++;
            }
        }

        temp = temp->next;
    }

    return NULL;
}

class bat
{
public:
    string batsman;
    int batnum;
    int score;
    string team;

    void batset(string batsman, int playernum, string team)
    {
        this->batsman = batsman;
        this->batnum = playernum;
        this->team = team;
        this->score = 0;
    }
};

class bowl
{
public:
    string bowler;
    int bowlnum;
    int wicket;
    string team;

    void bowlset(string bowler, int bowlnum, string team)
    {
        this->bowler = bowler;
        this->bowlnum = bowlnum;
        this->team = team;
        this->wicket = 0;
    }

    void bowling(int r)
    {
        if (r == -1)
            wicket++;
    }
};

class batting : public bat, public bowl
{
public:
    bat b1;
    bat b2;

    bowl bw;

    int r1 = 0;
    int r2 = 0;

    int bats(
        struct node *batHead,
        struct node *bowlHead,
        string battingTeamName,
        string bowlingTeamName,
        int &currentScore,
        int start)
    {
        int striker = 1;
        int nextBatsman = 3;
        int wickets = 0;

        int bowlerIndex = 0;
        int bowlerOvers[5] = {0, 0, 0, 0, 0};

        int target;

        createCSV();

        struct node *p1 = getPlayer(batHead, 0);
        struct node *p2 = getPlayer(batHead, 1);

        if (p1 == NULL || p2 == NULL)
        {
            cout << "\nNot enough batsmen.\n";
            return wickets;
        }

        b1.batset(
            p1->playername,
            p1->playernum,
            battingTeamName);

        b2.batset(
            p2->playername,
            p2->playernum,
            battingTeamName);

        for (int j = 0; j < 20; j++)
        {
            if (start == 1)
                target = 0;
            else
                target = team1score;

            if (start != 1 && team2score > target)
                break;

            while (bowlerIndex < 5 &&
                   bowlerOvers[bowlerIndex] >= 4)
            {
                bowlerIndex++;
            }

            if (bowlerIndex >= 5)
                bowlerIndex = 0;

            struct node *bowlerNode =
                getBowler(bowlHead, bowlerIndex);

            if (bowlerNode == NULL)
            {
                cout << "\nNo suitable bowler available.\n";
                break;
            }

            bw.bowlset(
                bowlerNode->playername,
                bowlerNode->playernum,
                bowlingTeamName);

            cout << "\n========== OVER "
                 << j + 1
                 << " ==========\n";

            for (int i = 1; i <= 6; i++)
            {
                if (wickets >= 10)
                    break;

                if (start != 1 && team2score > target)
                    break;

                int r = run();

                string event;

                if (r == 0)
                    event = "DOT";
                else if (r == 4)
                    event = "FOUR";
                else if (r == 6)
                    event = "SIX";
                else if (r == -1)
                    event = "WICKET";
                else
                    event = "RUN";

                string batsmanName;
                int batsmanID;

                if (striker == 1)
                {
                    r1 = r;

                    batsmanName = b1.batsman;
                    batsmanID = b1.batnum;

                    cout << "\nBall "
                         << i
                         << " : "
                         << b1.batsman;

                    if (r != -1)
                    {
                        b1.score += r;

                        currentScore += r;

                        updateScore(
                            batHead,
                            b1.batnum,
                            r);

                        cout << " scored "
                             << r
                             << " runs";

                        cout << "\nCurrent score : "
                             << b1.score;
                    }
                    else
                    {
                        cout << " is OUT!";

                        updateWicket(
                            bowlHead,
                            bw.bowlnum);

                        bw.bowling(r);

                        wickets++;

                        cout << "\nFinal score of "
                             << b1.batsman
                             << " : "
                             << b1.score;

                        if (nextBatsman <= 11)
                        {
                            struct node *newBatsman =
                                getPlayer(
                                    batHead,
                                    nextBatsman - 1);

                            if (newBatsman != NULL)
                            {
                                b1.batset(
                                    newBatsman->playername,
                                    newBatsman->playernum,
                                    battingTeamName);

                                nextBatsman++;

                                cout << "\nNew batsman : "
                                     << b1.batsman;
                            }
                        }
                    }
                }
                else
                {
                    r2 = r;

                    batsmanName = b2.batsman;
                    batsmanID = b2.batnum;

                    cout << "\nBall "
                         << i
                         << " : "
                         << b2.batsman;

                    if (r != -1)
                    {
                        b2.score += r;

                        currentScore += r;

                        updateScore(
                            batHead,
                            b2.batnum,
                            r);

                        cout << " scored "
                             << r
                             << " runs";

                        cout << "\nCurrent score : "
                             << b2.score;
                    }
                    else
                    {
                        cout << " is OUT!";

                        updateWicket(
                            bowlHead,
                            bw.bowlnum);

                        bw.bowling(r);

                        wickets++;

                        cout << "\nFinal score of "
                             << b2.batsman
                             << " : "
                             << b2.score;

                        if (nextBatsman <= 11)
                        {
                            struct node *newBatsman =
                                getPlayer(
                                    batHead,
                                    nextBatsman - 1);

                            if (newBatsman != NULL)
                            {
                                b2.batset(
                                    newBatsman->playername,
                                    newBatsman->playernum,
                                    battingTeamName);

                                nextBatsman++;

                                cout << "\nNew batsman : "
                                     << b2.batsman;
                            }
                        }
                    }
                }

                writeBall(
                    j + 1,
                    i,
                    batsmanName,
                    batsmanID,
                    bw.bowler,
                    bw.bowlnum,
                    r == -1 ? 0 : r,
                    event);

                if (r == 1 || r == 3)
                {
                    if (striker == 1)
                        striker = 2;
                    else
                        striker = 1;
                }
            }

            bowlerOvers[bowlerIndex]++;

            cout << "\n\nTeam Score : "
                 << currentScore;

            cout << "\nBatsman 1 : "
                 << b1.batsman
                 << " - "
                 << b1.score;

            cout << "\nBatsman 2 : "
                 << b2.batsman
                 << " - "
                 << b2.score;

            cout << "\nBowler : "
                 << bw.bowler
                 << " - Wickets : "
                 << bw.wicket
                 << endl;

            if (striker == 1)
                striker = 2;
            else
                striker = 1;

            bowlerIndex++;

            if (bowlerIndex >= 5)
                bowlerIndex = 0;

            if (wickets >= 10)
                break;

            if (start != 1 && team2score > target)
                break;
        }

        return wickets;
    }
};

void displayScoreboard()
{
    cout << "\n\n========================================\n";
    cout << "             FINAL SCOREBOARD\n";
    cout << "========================================\n";

    cout << "\nTEAM 1 SCORE : "
         << team1score
         << endl;

    cout << "TEAM 2 SCORE : "
         << team2score
         << endl;

    displayTeam1();
    displayTeam2();
}

void startMatch(
    int team1ID,
    string team1Name,
    int team2ID,
    string team2Name)
{
    delTeam1();
    delTeam2();

    loadPlayersToMatch(
        team1ID,
        team1Name,
        team2ID,
        team2Name);

    if (countPlayers(hteam1) < 11 ||
        countPlayers(hteam2) < 11)
    {
        cout << "\nBoth teams must have 11 players.\n";
        return;
    }

    team1score = 0;
    team2score = 0;

    int start = 1;

    cout << "\n========================================\n";
    cout << "           FIRST INNINGS\n";
    cout << "========================================\n";

    batting innings1;

    int wickets1 = innings1.bats(
        hteam1,
        hteam2,
        team1Name,
        team2Name,
        team1score,
        start);

    cout << "\n\nFIRST INNINGS COMPLETED";

    cout << "\n"
         << team1Name
         << " Score : "
         << team1score
         << "/"
         << wickets1
         << endl;

    start = 2;

    cout << "\n========================================\n";
    cout << "           SECOND INNINGS\n";
    cout << "========================================\n";

    batting innings2;

    int wickets2 = innings2.bats(
        hteam2,
        hteam1,
        team2Name,
        team1Name,
        team2score,
        start);

    cout << "\n\nSECOND INNINGS COMPLETED";

    cout << "\n"
         << team2Name
         << " Score : "
         << team2score
         << "/"
         << wickets2
         << endl;

    cout << "\n========================================\n";
    cout << "             MATCH RESULT\n";
    cout << "========================================\n";

    if (team2score > team1score)
    {
        cout << team2Name
             << " WON BY "
             << 10 - wickets2
             << " WICKETS\n";
    }
    else if (team2score < team1score)
    {
        cout << team1Name
             << " WON BY "
             << team1score - team2score
             << " RUNS\n";
    }
    else
    {
        cout << "MATCH TIED\n";
    }

    displayScoreboard();
}

int main()
{
    readCSV();

    startMatch(
        1,
        "Team 1",
        2,
        "Team 2");

    return 0;
}