#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "score.cpp"
using namespace std;
void showTeamScore(struct node *head, string teamName, int teamScore, int wickets)
{
    ifstream file("match.csv");
    if (!file)
    {
        cout << "Unable to open match.csv\n";
        return;
    }
    string line;
    getline(file, line);
    temp = head;
    while (temp != NULL)
    {
        temp->score = 0;
        temp->wicket = 0;
        temp = temp->next;
    }
    while (getline(file, line))
    {
        stringstream ss(line);
        string over;
        string ball;
        string batsman;
        string batsmanID;
        string bowler;
        string bowlerID;
        string runs;
        string event;
        getline(ss, over, ',');
        getline(ss, ball, ',');
        getline(ss, batsman, ',');
        getline(ss, batsmanID, ',');
        getline(ss, bowler, ',');
        getline(ss, bowlerID, ',');
        getline(ss, runs, ',');
        getline(ss, event, ',');
        int id = stoi(batsmanID);
        int run = stoi(runs);
        temp = head;
        while (temp != NULL)
        {
            if (temp->playernum == id)
            {
                temp->score += run;
                if (event == "WICKET")
                {
                    temp->wicket++;
                }
                break;
            }
            temp = temp->next;
        }
    }
    file.close();
    cout << "\n--------------------------------------\n";
    cout << "        " << teamName << " SCORECARD\n";
    cout << "--------------------------------------\n";
    cout << "TOTAL : " << teamScore << "-" << wickets << "\n\n";
    cout << "Player            Runs   Wickets\n";
    cout << "--------------------------------------\n";
    temp = head;
    while (temp != NULL)
    {
        cout << temp->playername;
        int nameLen = temp->playername.length();
        for (int i = nameLen; i < 18; i++)
            cout << " ";
        cout << temp->score;
        if (temp->wicket)
            cout << "     OUT";
        cout << endl;
        temp = temp->next;
    }
    cout << "--------------------------------------\n";
}
